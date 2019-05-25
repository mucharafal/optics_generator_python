import madxconfigurationgenerator as mc
import os
import subprocess
import sys
import xml.etree.ElementTree as ET
import re
import numpy as np
import shutil
# todo
# read file trackone
# run madx until number of particles on last station will statisfy configuration minimum
# run madx concurrently


def run_madx(path_to_madx_configuration_file):
    """Run madx"""
    f = open(path_to_madx_configuration_file)
    res = subprocess.run("madx", stdin=f, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    res.stdout = open(os.devnull, 'w')


def generate_particles_trajectory(configuration_path, configuration_file_name):
    # generate conf_*_processed file
    ready_config_path = mc.generate_configuration_file(config_path, file_config)
    # copy to current working directory
    shutil.copy2(ready_config_path, os.getcwd())
    # get configuration of program from xml file
    xml_configuration_file_path = os.path.join(configuration_path, configuration_file_name)
    tree = ET.parse(xml_configuration_file_path)        # load configuration from xml file
    root = tree.getroot()
    configuration = root[0].attrib
    # generate part.in file for input madx
    generate_particles(configuration)
    # run madx in current working directory
    print("Generated, start processing...")
    run_madx(ready_config_path)
    # read in trackone file generated by madx
    segments = read_in_madx_output_file("trackone")
    # return it
    return segments


def read_in_madx_output_file(filename):
    with open(filename, "r") as input_file:
        # skip header
        line = input_file.readline()
        while line[0] != "*":
            line = input_file.readline()
        parameters = line.split()
        # skip '*'
        parameters = parameters[1:]
        segments = []
        while line[0] != "#":
            line = input_file.readline()
        
        while len(line) > 0 and line[0] == "#":
            segments += [read_in_segment(line, input_file, len(parameters))]
            line = input_file.readline()
        return segments


def read_in_segment(header, input_file, columns_number):
    parameters = header.split()[1:]
    number_of_particles = int(parameters[2])
    segment_name = parameters[4]
    values_vector = np.fromfile(input_file, count=number_of_particles*columns_number, sep=" ")
    matrix = np.reshape(values_vector, (number_of_particles, columns_number))
    return segment_name, matrix


def generate_particles(configuration):
    with open("part.in", "w") as output:
        number_of_particles = int(configuration['number_of_part_per_sample'])
        keys = configuration.keys()
        pattern = re.compile("\w+(?=_min)")     # extract from pattern with suffix _min
        # get parameters from configuration
        parameters = map(lambda x: pattern.search(x), keys)
        parameters = filter(lambda x: x is not None, parameters)
        parameters = map(lambda x: x.group(0), parameters)
        parameters = list(parameters)
        number_of_parameters = len(parameters)
        # print(list(parameters))
        max_vector = np.zeros((1, number_of_parameters))
        min_vector = np.zeros((1, number_of_parameters))
        for i in range(number_of_parameters):
            max_vector[0][i] = float(configuration[parameters[i] + "_max"])
            min_vector[0][i] = float(configuration[parameters[i] + "_min"])
        
        matrix = (max_vector - min_vector) * np.random.random_sample((number_of_particles, number_of_parameters)) \
            + min_vector
        
        write_header(output)
        # disclaimer: trx = x ; trpx = px ; try = y ...
        output.write('* mken ')
        for parameter in parameters:
            output.write("tr" + parameter + " ")
        output.write("\n")
        output.write('$ %s ')
        for i in range(number_of_parameters):
            output.write('%le ')
        output.write("\n")
        for i in range(number_of_particles):
            line = '"' + str(i+1) + '" '
            for n in matrix[i]:
                line += str(n) + " "
            line += "\n"
            output.write(line)


def write_header(file_object):
    file_object.write('@ NAME             %07s "PARTICLES"\n')
    file_object.write('@ TYPE             %04s "USER"\n')
    file_object.write('@ TITLE            %34s "EVENT"\n')
    file_object.write('@ ORIGIN           %19s "MAD-X 3.00.03 Linux"\n')
    file_object.write('@ DATE             %08s "22/02/06"\n')      # todo add current date
    file_object.write('@ TIME             %08s "11.11.11"\n')


if __name__ == "__main__":
    """
    command: python3 madx_runner.py path_to_folder_with_configuration configuration_file_name.xml
    needed: 
    1. madx in PATH
        - you can download it from: http://madx.web.cern.ch/madx/
        - add to PATH folder with madx: export PATH=$PATH:/absolute/path/to/folder/with/madx in terminal
        - later in the same terminal you can run this file
        when you quit terminal, changes in PATH are lost
    """
    config_path = sys.argv[1]
    file_config = sys.argv[2]
    output = generate_particles_trajectory(config_path, file_config)
    print(output)
