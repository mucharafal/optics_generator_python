import ROOT
from ROOT import gSystem, gInterpreter
import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd


def get_approximator(path_to_project, path_to_file, approximator_name):
    """
    Get approximator from file. Use only once, since it initialize variables in ROOT, so with second use it is going
    to explode. Sorry.
    :param path_to_project: path to optics_generator_python. Needed files from it:
    - properly initialized folder root_libs
    - src/root_classes/include
    :param path_to_file: path to file with serialized LHCOpticsApproximator object
    :param approximator_name: name of approximator in ROOT file
    :return: approximator object
    """
    os.environ['LD_LIBRARY_PATH'] = path_to_project + "/root_libs"
    gInterpreter.ProcessLine(".include " + path_to_project + "/src/root_classes/include")
    gSystem.Load("LHCOpticsApproximator")
    gInterpreter.ProcessLine('TFile *f=TFile::Open("' + path_to_file + '");')
    gInterpreter.ProcessLine(
        'std::auto_ptr<LHCOpticsApproximator> apr = std::auto_ptr<LHCOpticsApproximator>((LHCOpticsApproximator*) f->Get("' + approximator_name + '"));')
    gInterpreter.ProcessLine("f->Close()")
    gInterpreter.ProcessLine("double input[5];")
    gInterpreter.ProcessLine("double output[5];")
    approximator = ROOT.apr
    return approximator


mapping = {
    "x": 0,
    "theta x": 1,
    "y": 2,
    "theta y": 3,
    "pt": 4,
    "result": 5
}


def plot_optical_function(approximator_configuration, optical_function, vector_x_name, optic_parameter_name, title,
                          x_unit="", y_unit="",
                          x_unit_multiplier=1, y_unit_multiplier=1, plot_size=5, grid_x_resolution=5,
                          grid_y_resolution=7):
    result_matrix = optical_function(approximator_configuration.approximator,
                                     approximator_configuration.x_min, approximator_configuration.x_max,
                                     approximator_configuration.number_of_x_values,
                                     approximator_configuration.theta_x_min, approximator_configuration.theta_x_max,
                                     approximator_configuration.number_of_theta_x_values,
                                     approximator_configuration.y_min, approximator_configuration.y_max,
                                     approximator_configuration.number_of_y_values,
                                     approximator_configuration.theta_y_min, approximator_configuration.theta_y_max,
                                     approximator_configuration.number_of_theta_y_values,
                                     approximator_configuration.pt_min, approximator_configuration.pt_max,
                                     approximator_configuration.number_of_pt_values)
    x_index = mapping[vector_x_name]
    y_index = mapping["result"]

    vector_x = result_matrix.T[x_index] * x_unit_multiplier
    vector_y = result_matrix.T[y_index] * y_unit_multiplier

    x_name = vector_x_name + x_unit
    y_name = optic_parameter_name + y_unit

    fig = plt.gcf()
    fig.set_size_inches(plot_size, plot_size)

    x_min = np.min(vector_x)
    x_max = np.max(vector_x)

    y_min = np.min(vector_y)
    y_max = np.max(vector_y)

    delta_x = x_max - x_min
    delta_y = y_max - y_min

    data_frame = pd.DataFrame(data={x_name: vector_x, y_name: vector_y})
    axes = sns.scatterplot(data=data_frame, x=x_name, y=y_name)

    axes.set_xlim(x_min - 0.25 * delta_x, x_max + 0.25 * delta_x)
    axes.set_ylim(y_min - 0.25 * delta_y, y_max + 0.25 * delta_y)

    plt.xticks(np.arange(x_min, x_max + delta_x / grid_x_resolution, delta_x / grid_x_resolution))
    plt.yticks(np.arange(y_min, y_max + delta_y / grid_y_resolution, delta_y / grid_y_resolution))

    axes.set_title(y_name + " from " + x_name + "\n" + title)
