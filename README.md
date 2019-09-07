Optics generator
==============================

Program to make and verify parametrisation of optics.

Project Organization
------------

    ├── LICENSE
    ├── README.md          <- The top-level README for developers using this project.
    │
    ├── docs               <- A default Sphinx project; see sphinx-doc.org for details
    │
    ├── notebooks          <- Jupyter notebooks with analyze
    │
    ├── references         <- Data dictionaries, manuals, and all other explanatory materials.
    │
    ├── requirements.txt   <- The requirements file for reproducing the analysis environment, e.g.
    │                         generated with `pip freeze > requirements.txt`
    │
    ├── setup.py           <- makes project pip installable (pip install -e .) so src can be imported
    ├── src                <- Source code for use in this project.
    |   ├── approximator   <- Library for generating data unsing serialized LHCOpticsApproximator objects.
    |   ├── comparators    <- Package with functions to visualize differences/errors in transport and optical functions.
    │   ├── data           <- Functions to generate input datasets for other generators.
    |   ├── ptc_track      <- Library for generating data unsing scripts with ptc_track command (MAD-X).
    │   ├── ptc_twiss      <- Library for generating data unsing scripts with ptc_twiss command (MAD-X).
    │   ├── root_classes   <- Folder with sources of LHCOpticsApproximator to generate libraries for ROOT.
    │   ├── twiss          <- Library for generating data unsing scripts with twiss command (MAD-X).    
    │   ├── utils          <- Package with some commonly used functions
    │   └── visualization  <- Package with functions to visualize parameters computed by generators
    │
    └── tox.ini            <- tox file with settings for running tox; see tox.testrun.org
  
--------
# How to run
## SWAN
### Download project

Download zip from https://gitlab.cern.ch/rmucha/optics_generator_python/tree/v0.1.2-SWAN   
move it to folder SWAN_projects on cernbox
Unzip it and change name on optics_generator_python   
You can do this by terminal (button '>_' in right upper corner)
```
unzip optics_generator_python-v0.1.2-SWAN.zip
mv optics_generator_python-v0.1.2-SWAN optics_generator_python
```

### First run
Setup SWAN:   
stack: 96 python 3   
start script: /eos/user/firstLetterOfCernLogin/CernLogin/SWAN_projects/optics_generator_python/swan_start_script   
It is also advised to choose 4 cores
After starting session:   
Compile library:   
Open terminal (button '>_' in right upper corner)
```
cd SWAN_projects/optics_generator_python/src/root_classes/src
make shared
```

Library has to be compiled only once. If you start SWAN another time all you need is properly set stack and start script

### Adding optics

Folder with optics should be in SWAN_projects folder.   
Example optics you can copy from: https://cernbox.cern.ch/index.php/s/OykQjwp3L5TJN4z

### Using

Take a look on notebooks folder. It contain some examples to use visualization function.   
To make parametrisation run script: src/models/make_parametrisation.py
