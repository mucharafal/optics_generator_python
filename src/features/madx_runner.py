import madxconfigurationgenerator as mc
import os
import subprocess
import sys
import xml.etree.ElementTree as ET
import re
import numpy as np
#todo
#generate part.in
#read file trackone
#run madx until number of particles on last station will statisfy configuration minimum
#run madx concurrently
def run_madx(file,config_path):
    """Run madx"""
    f=open(file)
    os.chdir(config_path)
    res=subprocess.run("madx",stdin=f, stdout = subprocess.PIPE)
    res.stdout=open(os.devnull,'w')

def generate_particles_trajectory(configuration_path, configuration_file_name):
    ready_config_path = mc.generate_configuration_file(config_path,file_config)
    xml_configuration_file_path = configuration_path + "/" + configuration_file_name

    tree = ET.parse(xml_configuration_file_path)        #load configuration from xml file
    root = tree.getroot()

    places = map(lambda x: x.attrib, list(root[0]))
    places = list(places)

    configuration = root[0].attrib
    generate_particles(configuration)
    #run_madx(ready_config_path, config_path)

def generate_particles(configuration):
    #todo save in some temp folder???
    #currently save part.in in folder, where invoked program
    with open("part.in", "w") as output:
        number_of_particles = int(configuration['number_of_part_per_sample'])
        keys = configuration.keys()
        pattern = re.compile("\w+(?=_min)") #extract from pattern with suffix _min
        #get parameters from configuration
        parameters = map(lambda x: pattern.search(x), keys)
        parameters = filter(lambda x: x != None, parameters)
        parameters = map(lambda x: x.group(0), parameters)
        parameters = list(parameters)
        number_of_parameters = len(parameters)
        # print(list(parameters))
        maxVector = np.zeros((1, number_of_parameters))
        minVector = np.zeros((1, number_of_parameters))
        for i in range(number_of_parameters):
            maxVector[0][i] = float(configuration[parameters[i] + "_max"])
            minVector[0][i] = float(configuration[parameters[i] + "_min"])
        
        matrix = (maxVector - minVector) * np.random.random_sample((number_of_particles, number_of_parameters)) + minVector
        
        write_header(output)
        output.write('$ %s ')
        for i in range(number_of_parameters):
            output.write('%le ')
        output.write("\n")
        for i in range(number_of_particles):
            line = '"' + str(i+1) + '"\t'
            for n in matrix[i]:
                line += str(n) + "\t"
            line += "\n"
            output.write(line)

def write_header(file):
    file.write('@ NAME             %07s "PARTICLES"\n')
    file.write('@ TYPE             %04s "USER"\n')
    file.write('@ TITLE            %34s "EVENT"\n')
    file.write('@ ORIGIN           %19s "MAD-X 3.00.03 Linux"\n')
    file.write('@ DATE             %08s "22/02/06"\n')  #todo add current date
    file.write('@ TIME             %08s "11.11.11"\n')
    #what is this???
    file.write("*   mken  trx      trpx       try     trpy       tt      tpt\n")

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
    config_path=sys.argv[1]
    file_config = sys.argv[2]
    generate_particles_trajectory(config_path, file_config)
