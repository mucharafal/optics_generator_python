import os
import subprocess
import numpy as np
import utils.working_directory as working_directory
from concurrent.futures import ProcessPoolExecutor
from datetime import date


def compute_trajectory(particles, madx_configuration, number_of_workers):
    """
    Compute trajectory for particles in matrix
    :param particles: numpy matrix with parameters of particles. Rows of matrix: x, theta x, y, theta y, t, pt
    :param madx_configuration
    :param number_of_workers: number of processes use in computing
    :return: dict with matrix for every point in script
    """
    trajectory_matrix = __run_parallel(particles, madx_configuration, number_of_workers)
    return trajectory_matrix


def __run_madx(path_to_madx_script):
    """
    Run ptc_track in current folder. As stdin for ptc_track given content of file, whose path is specified in argument
    """
    with open(path_to_madx_script) as f:
        res = subprocess.run("madx", stdin=f, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        # print(res.stdout) # if output from madx is needed
        res.stdout = open(os.devnull, 'w')


def __read_in_madx_output_file(filename):
    """
    Read in ptc_track output file
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
            (segment_name, matrix) = __read_in_segment(line, input_file, len(parameters))
            segments[segment_name] = matrix
            line = input_file.readline()
        return segments


def __read_in_segment(header, input_file, columns_number):
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


def __merge_output_from_workers(futures):
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


def __run_worker(particles, working_directory_name, madx_configuration, shift):
    """
    Function of worker which run ptc_track. It prepare working directory, run ptc_track,
    read in result and return it. It must be another process not thread because it changes working directory
    of interpreter.
    :param particles: matrix with parameters of particles
    :param working_directory_name: name of directory in which process should work
    :param madx_configuration:
    :param shift: shift of ordinal numbers of particles
    :return:
    """
    path_to_working_directory = os.path.join(os.getcwd(), working_directory_name)
    beginning_directory = working_directory.create_and_get_into(path_to_working_directory)

    __save_particles_to_file(particles)

    number_of_particles = particles.shape[0]

    configuration_file_name = madx_configuration.generate_madx_script(number_of_particles)

    __run_madx(configuration_file_name)

    raw_segments = __read_in_madx_output_file("trackone")

    working_directory.leave_and_delete(beginning_directory)

    segments = shift_ordinal_number_in_segments(raw_segments, shift)

    return segments


def __save_particles_to_file(particles,
                             ordinal_number_name="mken",
                             x_name="trx",
                             theta_x_name="trpx",
                             y_name="try",
                             theta_y_name="trpy",
                             t_name="tt",
                             pt_name="trpt"):
    """
    Save particles in part.in file in ptc_track format.
    :param particles: numpy matrix with particles parameters
    :param ordinal_number_name: name of first parameter- ordinal number
    :param x_name: name of second parameter in file part.in- x
    :param theta_x_name: name of theta x parameter in file part.in
    :param y_name: name of y parameter in file part.in
    :param theta_y_name: name of theta y parameter in file part.in
    :param t_name: name of t parameter in file part.in
    :param pt_name: name of pt parameter in file part.in
    :return: None
    """
    with open("part.in", "w") as output_file:
        __write_header(output_file)
        # disclaimer: trx = x ; trpx = px ; try = y ...
        names = [ordinal_number_name, x_name, theta_x_name, y_name, theta_y_name, t_name, pt_name]
        types = [str, float, float, float, float, float, float]
        __write_specification_of_row(names, types, output_file)
        __save_matrix_to_file(particles, output_file)


def __write_header(file_object):
    """
    Write a header in ptc_track format to file object given as parameter. Helper function for generate_particles
    :param file_object: file to which header would be added
    """
    file_object.write('@ NAME             %07s "PARTICLES"\n')
    file_object.write('@ TYPE             %04s "USER"\n')
    file_object.write('@ TITLE            %34s "EVENT"\n')
    file_object.write('@ ORIGIN           %19s "MAD-X 3.00.03 Linux"\n')
    file_object.write('@ DATE             %08s "' + date.today().strftime("%d/%m/%Y") + '"\n')
    file_object.write('@ TIME             %08s "11.11.11"\n')


def __write_specification_of_row(names, types, file_object):
    """
    Every column in ptc_track file has to be properly described. It has two parameters: name and type.
    This function write to file two lines which describe this parameters.
    :param names: names of columns
    :param types: types of columns
    :param file_object: file to which description should be written
    :return: None
    """
    # Write names of columns
    file_object.write("*")
    for name in names:
        file_object.write(" "+name)
    file_object.write("\n")

    # todo complete this map
    type_names = {
        str: '%s',
        float: '%le'
    }

    # Write names of types
    file_object.write("$")
    for column_type in types:
        file_object.write(" "+type_names[column_type])
    file_object.write("\n")


def __save_matrix_to_file(matrix, file_object):
    """
    Save matrix to file with counting every particle, so it is '"ordinary number" rest of row'
    :param matrix: matrix which rows should be saved
    :param file_object: file to which it should be saved
    :return: None
    """
    grid_size = len(matrix)
    for i in range(grid_size - 1):
        line = '"' + str(i + 1) + '" '
        for n in matrix[i]:
            line += str(n) + " "
        line += "\n"
        file_object.write(line)

    i = grid_size - 1
    line = '"' + str(i + 1) + '" '
    for n in matrix[i]:
        line += str(n) + " "
    file_object.write(line)


def __run_parallel(particles, madx_configuration, number_of_workers=4):
    """
    Execute parallel threads which every:
    - create its own working directory
    - copy configuration file from to its working directory
    - generate particles trajectory and return it
    :param particles: matrix with particles' parameters
    :param madx_configuration:
    :param number_of_workers: max number of workers
    :return: dictionary with segments- every segment is one matrix with particles
    """
    parts = []
    particles = particles.T
    part_size = int(particles.shape[0]/number_of_workers)
    for index in range(number_of_workers-1):
        begin = index * part_size
        end = begin + part_size
        part = particles[begin:end]
        parts.append(part)

    parts.append(particles[(number_of_workers-1)*part_size:])

    with ProcessPoolExecutor(number_of_workers) as executor:
        segments = {}
        futures = []
        for worker_number in range(number_of_workers):
            worker_directory_name = "dir" + str(worker_number)
            shift = part_size * worker_number
            futures.append(executor.submit(__run_worker,
                                           parts[worker_number], worker_directory_name,
                                           madx_configuration, shift))
        new_particles = __merge_output_from_workers(futures)
        segments = merge_segments(segments, new_particles)
        return segments


def shift_ordinal_number_in_segments(segments, shift):
    for segment_name in segments.keys():
        segment = segments[segment_name]
        segment.T[0] = segment.T[0] + shift
        segments[segment_name] = segment
    return segments
