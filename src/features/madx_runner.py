import MadxConfigurationGenerator as mc
import os
import subprocess
import sys


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
    config_path=sys.argv[1]
    file_config = sys.argv[2]
    generate_particles(config_path, file_config)
