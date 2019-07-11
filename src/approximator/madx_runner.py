import approximator.madxconfigurationgenerator as mc
import os
import subprocess
import sys
import xml.etree.ElementTree as ET
import numpy as np
import shutil
import approximator.particles_generator as pg
from concurrent.futures import ProcessPoolExecutor


def run_madx(path_to_madx_configuration_file):
    """
    Run madx in current folder. As stdin for madx given content of file, whose path is specified in argument
    """
    with open(path_to_madx_configuration_file) as f:
        res = subprocess.run("madx", stdin=f, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        res.stdout = open(os.devnull, 'w')


def load_configuration(path_to_configuration):
    """
    Load configuration from xml file, which name is given as argument
    :param path_to_configuration: path to configuration file in xml format
    :return: dictionary with configuration
    """
    tree = ET.parse(path_to_configuration)  # load configuration from xml file
    root = tree.getroot()
    configuration = root[0].attrib
    return configuration


def read_in_madx_output_file(filename):
    """
    Read in madx output file
    :param filename: filename if it is in current directory or path to file
    :return: dictionary, where keys are names of segments and values are numpy matrix with data
    """
    with open(filename, "r") as input_file:
        # skip header
        line = input_file.readline()
        while line[0] != "*":
            line = input_file.readline()
        parameters = line.split()
        # skip '*'
        parameters = parameters[1:]
        segments = {}
        while line[0] != "#":
            line = input_file.readline()

        while len(line) > 0 and line[0] == "#":
            (segment_name, matrix) = read_in_segment(line, input_file, len(parameters))
            segments[segment_name] = matrix
            line = input_file.readline()
        return segments


def read_in_segment(header, input_file, columns_number):
    """
    Read in one segment from file.
    :param header: header of segment, it should be read in before
    :param input_file: object of the file, cursor should be set after header
    :param columns_number: number of columns
    :return: numpy matrix with data from this segment
    """
    parameters = header.split()[1:]
    number_of_particles = int(parameters[2])
    segment_name = parameters[4]
    values_vector = np.fromfile(input_file, count=number_of_particles*columns_number, sep=" ")
    matrix = np.reshape(values_vector, (number_of_particles, columns_number))
    return segment_name, matrix


def generate_particles(configuration, path):
    """
    Function to generate file part.in. Parameters of particles are taken from configuration. Every parameter whose
    values should be generated is describe by keys in configuration: parameter_name_min and parameter_name_max.
    Warn- non thread safe. Changes working directory.
    :param configuration: dictionary with needed parameters
    :param path: path to directory, where file part.in should be generated
    :return:
    """
    # Save current path.
    previous_path = os.getcwd()
    # Change for specified.
    os.chdir(path)

    # Get parameters from configuration
    number_of_particles = int(configuration['number_of_part_per_sample'])
    x_min = float(configuration['x_min'])
    x_max = float(configuration['x_max'])
    theta_x_min = float(configuration['px_min'])
    theta_x_max = float(configuration['px_max'])
    y_min = float(configuration['y_min'])
    y_max = float(configuration['y_max'])
    theta_y_min = float(configuration['py_min'])
    theta_y_max = float(configuration['py_max'])
    t_min = float(configuration['t_min'])
    t_max = float(configuration['t_max'])
    pt_min = float(configuration['pt_min'])
    pt_max = float(configuration['pt_max'])

    pg.generate_particles_randomly(x_min, x_max, theta_x_min, theta_x_max, y_min, y_max, theta_y_min, theta_y_max,
                                   t_min, t_max, pt_min, pt_max, number_of_particles)

    # Recover previous working path.
    os.chdir(previous_path)


def merge_segments(destiny_segments, source_segments):
    """
    Merge two dicts with segments. Values in dicts must be numpy matrix. If keys in both dicts are the same,
    their matrixs are merged
    :param destiny_segments: dict to which elements will be added
    :param source_segments: dict from which elements will be added to destiny
    :return: destiny_segments dict after merge
    """
    destiny_keys = set(destiny_segments.keys())
    source_keys = set(source_segments.keys())
    intersection = destiny_keys.intersection(source_keys)
    new_keys = source_keys.difference(destiny_keys)
    for key in intersection:
        segment1 = destiny_segments[key]
        segment2 = source_segments[key]
        destiny_segments[key] = np.concatenate((segment1, segment2), axis=0)
    for key in new_keys:
        destiny_segments[key] = source_segments[key]
    return destiny_segments


def merge_output_from_workers(futures):
    """
    Wait until every worker finish its work, then merge theirs results and return it
    :param futures: list with future objects, which expected value are dict with segments
    :return: dict with segments
    """
    segments = {}
    for future in futures:
        try:
            new_particles = future.result()
            segments = merge_segments(segments, new_particles)
        except Exception as e:
            print(e)
            pass    # if sth go wrong, just skip it
    return segments


def run_worker(path_to_config_file, configuration, working_directory_name):
    """
    Function of worker which run madx. It prepare working directory, run madx,
    read in result and return it. It must be another process not thread because it changes working directory
    of interpreter.
    :param path_to_config_file: path to file with ready script for madx
    :param configuration: dict with begining parameters of program
    :param working_directory_name: name of directory in which process should work
    :return:
    """
    directory_before = os.getcwd()
    path_to_working_directory = os.path.join(os.getcwd(), working_directory_name)
    if not os.path.exists(path_to_working_directory):
        os.mkdir(path_to_working_directory)

    os.chdir(path_to_working_directory)

    generate_particles(configuration, path_to_working_directory)
    configuration_file_name = configuration["processed_mad_conf_file"]
    shutil.copy(path_to_config_file, configuration_file_name)

    run_madx(configuration_file_name)

    segments = read_in_madx_output_file("trackone")

    os.chdir(directory_before)

    return segments


def run_parallel(target, ready_config_path, configuration, number_of_workers=4):
    """
    Execute parallel threads which every:
    - create its own working directory
    - copy configuration file from to its working directory
    - generate particles trajectory and return it
    :param target: number of particles to generate
    :param ready_config_path: path to ready configuration file
    :param configuration: dictionary with configuration
    :param number_of_workers: max number of workers
    :return: dictionary with segments- every segment is one matrix with particles
    """
    with ProcessPoolExecutor(number_of_workers) as executor:
        segments = {}
        while len(segments.keys()) == 0 or len(segments["end"]) <= target:
            futures = []
            for worker_number in range(number_of_workers):
                worker_directory_name = "dir" + str(worker_number)
                futures.append(executor.submit(run_worker,
                                               ready_config_path, configuration, worker_directory_name))
            new_particles = merge_output_from_workers(futures)
            segments = merge_segments(segments, new_particles)
            print(len(segments["end"]))
        return segments


def __run_test():
    """
    run test which run. Need parameters of invoke program:
     - first is path to folder with configuration files
     - second is name of xml file in folder specified above
     """
    config_path = sys.argv[1]
    file_config = sys.argv[2]

    path_to_xml_configuration_file = os.path.join(config_path, file_config)
    configuration = load_configuration(path_to_xml_configuration_file)

    target = int(configuration["tot_entries_number"])
    ready_config_path = mc.generate_configuration_file(config_path, file_config)
    output = run_parallel(target, ready_config_path, configuration, 4)

    print(output['end'])
    print(len(output['end']))


if __name__ == "__main__":
    """
    command: python3 madx_runner.py path_to_folder_with_configuration configuration_file_name.xml
    needed:"optics_generator_python/src/approximator"+dir
    1. madx in PATH
        - you can download it from: http://madx.web.cern.ch/madx/
        - add to PATH folder with madx: export PATH=$PATH:/absolute/path/to/folder/with/madx in terminal
        - later in the same terminal you can run this file
        when you quit terminal, changes in PATH are lost
    """
    __run_test()
