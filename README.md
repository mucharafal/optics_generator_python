Optics generator
==============================

Description here

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
    │   ├── data           <- Functions to generate input datasets for other generators.
    |   ├── ptc_track      <- Library for generating data unsing scripts with ptc_track command (MAD-X).
    │   ├── ptc_twiss      <- Library for generating data unsing scripts with ptc_twiss command (MAD-X).
    │   ├── root_classes   <- Folder with sources of LHCOpticsApproximator to generate libraries for ROOT.
    │   |   ├── tmultidimfet_version    <- Version of LHCOpticsApproximator which use TMultiDimFet class (old)
    |   |   └── tmultidimfit_version    <- Version of LHCOpticsApproximator which use TMultiDimFit class (new)
    │   ├── twiss          <- Library for generating data unsing scripts with twiss command (MAD-X).    
    │   ├── features       <- Scripts to turn raw data into features for modeling
    │   │   └── build_features.py
    │   │
    │   ├── utils          <- Package with some commonly used functions
    │   │
    │   └── visualization  <- Package with functions to visualize parameters computed by generators
    │
    └── tox.ini            <- tox file with settings for running tox; see tox.testrun.org

------
1. Requirements:   
python3 (command "python3" in terminal)  
ROOT (command "import ROOT" in python3)   
seaborn ("import seaborn" in python3)   
--------




<p><small>Project based on the <a target="_blank" href="https://drivendata.github.io/cookiecutter-data-science/">cookiecutter data science project template</a>. #cookiecutterdatascience</small></p>
