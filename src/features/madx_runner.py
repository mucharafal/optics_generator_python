import MadxConfigurationGenerator as mc
import os
import subprocess

def remove_at(i,s):
    return s[:i]+s[i+1:]

def run_madx(file,config_path):
    path=config_path+"/2016/"
    f=open(file)
    data=f.readlines()
    i=0
    data2=[]

    for line in data:
        if "call,file" in line or "call, file" in line:
            count=0
            for i in range(len(line)-1,-1,-1):
                if line[i]=="/": break
                else: count+=1

            file_name=line[len(line)-count:-3]
            line="call,file=\""+path+file_name+"\";\n"
        data2.append(line)
        i+=1

    with open(file,'w') as new:
        new.writelines(data2)

    res=subprocess.run("madx",stdin=f,stdout=subprocess.PIPE)
    res.stdout=open(os.devnull,'w')

def find_project_path():
    for root,dirs,files in os.walk(r'/home'):
        for name in dirs:
            if name=="optics_generator_python": return os.path.abspath(os.path.join(root,name))

def find_conf():
    for root,dirs,files in os.walk(r'/home'):
        for name in files:
            if "_processed" in name: return os.path.abspath(os.path.join(root,name))

project_dir=find_project_path()
config_path=project_dir+"/src/data/config"
config="configuration_beam_1_ip_150_90m.xml"
mc.generate_configuration_file(config_path,config)
run_madx(find_conf(),config_path)
