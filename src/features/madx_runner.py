import madxconfigurationgenerator as mc
import os
import subprocess
import sys

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

def generate_particles(configuration_path, configuration_file_name):
    ready_config_path = mc.generate_configuration_file(config_path,file_config)
    run_madx(ready_config_path, config_path)

if __name__ == "__main__":
    """
    to run: python3 madx_runner.py path_to_folder_with_configuration configuration_file_name.xml
    needed: 
    1. madx in PATH
        - you can download it from: http://madx.web.cern.ch/madx/
        - add to PATH folder with madx: export PATH=$PATH:/absolute/path/to/folder/with/madx in terminal
        - later in the same terminal you can run this file
        when you quit terminal, changes in PATH are lost
    """
    config_path=sys.argv[1]
    file_config = sys.argv[2]
    generate_particles(config_path, file_config)
