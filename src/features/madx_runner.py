import madxconfigurationgenerator as mc
import os
import subprocess
import sys
import xml.etree.ElementTree as ET
import re
import numpy as np
import shutil
import threading
import time
from concurrent.futures import ThreadPoolExecutor,wait,ALL_COMPLETED
# todo
# run madx concurrently

executor=ThreadPoolExecutor(max_workers=10)
lock=threading.Lock()
die=False

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
    for type in root.findall('item'): target=type.get('tot_entries_number')
    # generate part.in file for input madx
    generate_particles(configuration,"")
    # run madx in current working directory
    print("Generated, start processing...")
    run_madx(ready_config_path)
    # read in trackone file generated by madx
    segments = read_in_madx_output_file("trackone")
    # return it
    return (segments,target,ready_config_path,configuration)


def read_in_madx_output_file(filename):
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
            (segment_name,matrix)=read_in_segment(line, input_file, len(parameters))
            segments[segment_name]=matrix
            line = input_file.readline()
        return segments


def read_in_segment(header, input_file, columns_number):
    parameters = header.split()[1:]
    number_of_particles = int(parameters[2])
    segment_name = parameters[4]
    values_vector = np.fromfile(input_file, count=number_of_particles*columns_number, sep=" ")
    matrix = np.reshape(values_vector, (number_of_particles, columns_number))
    return segment_name, matrix


def generate_particles(configuration,path):
    with open(path+"part.in", "w") as output:
        number_of_particles = int(configuration['number_of_part_per_sample'])
        keys = configuration.keys()
        pattern = re.compile("\w+(?=_min)")     # extract from pattern with suffix _min
        # get parameters from configuration
        extract_parameters = [pattern.search(x) for x in keys]
        parameters = [x.group(0) for x in extract_parameters if x is not None]
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

def resupply(target,ready_config_path,segments,configuration,dir):
    global lock
    global die
    while not die:
        if not os.path.exists(config_path+"/"+dir): os.mkdir(config_path+"/"+dir)
        work=os.getcwd()
        path=os.path.dirname(config_path+"/"+dir)+"/"+dir
        generate_particles(configuration,path+"/")

        lock.acquire()
        shutil.copy(work+"/conf_b1_processed",path)
        lock.release()

        lock.acquire()
        os.chdir(path)
        run_madx(path+"/conf_b1_processed")
        os.chdir(work)
        lock.release()

    #shutil.copy(path+"/trackone",work)
    #s=read_in_madx_output_file("trackone")

    #lock.acquire()
    #output_len+=len(s['end'])
    #print(output_len)
    #lock.release()
    #if output_len<target: executor.submit(resupply,target,ready_config_path,s,configuration,dir)
    #for key in segments:
    #    if key in s: segments[key]=np.concatenate((segments[key],s[key]),axis=0)

    #for key in s:
    #    if key not in segments: segments[key]=s[key]
    #return segments

def merge_all(segments,target):
    global die
    while True:
        for i in range(10):
            dir="dir"+str(i)
            path=os.path.dirname(config_path+"/"+dir)+"/"+dir

            if os.path.isfile(path+"/trackone"):
                s=read_in_madx_output_file(path+"/trackone")
                os.remove(path+"/trackone")

                for key in segments:
                    if key in s: segments[key]=np.concatenate((segments[key],s[key]),axis=0)

                for key in s:
                    if key not in segments: segments[key]=s[key]
            print(len(segments['end']))
            if len(segments['end'])>=target:
                die=True
                return segments
            else: time.sleep(1)


#def run_paralell(output,target,ready_config_path,configuration):
#    futures=[]
#    while len(output['end'])<target:
#        print(len(output['end']))
#        for i in range(5):
#            futures.append(executor.submit(resupply,target,ready_config_path,output,configuration,"dir"+str(i)))
#        wait(futures,timeout=None,return_when=ALL_COMPLETED)
#        output=merge_all(output)
#    return output

def run_paralell(output,target,ready_config_path,configuration):
    futures=[]
    for i in range(5): futures.append(executor.submit(resupply,target,ready_config_path,output,configuration,"dir"+str(i)))
    futures.append(executor.submit(merge_all,output,target))
    output=futures[-1].result()
    for i in futures: i.cancel()
    return output

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
    needed:"optics_generator_python/src/features"+dir
    1. madx in PATH
        - you can download it from: http://madx.web.cern.ch/madx/
        - add to PATH folder with madx: export PATH=$PATH:/absolute/path/to/folder/with/madx in terminal
        - later in the same terminal you can run this file
        when you quit terminal, changes in PATH are lost
    """
    config_path = sys.argv[1]
    file_config = sys.argv[2]
    (output,target,ready_config_path,configuration) = generate_particles_trajectory(config_path, file_config)

    output=run_paralell(output,int(target),ready_config_path,configuration)
    #    for future in as_completed(futures):
    #        print(future.result())

    #i=0
    #while(len(output['end'])<int(target)):
    #    output=resupply(int(target),ready_config_path,output,configuration,"dir"+str(i))
    #    i+=1

print(output['end'])
print(len(output['end']))
