import ROOT
from ROOT import gSystem, gInterpreter
import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

mapping = {
    "x": 0,
    "theta x": 1,
    "y": 2,
    "theta y": 3,
    "pt": 4,
    "result": 5
}


def plot_optical_function_of_approximator(approximator, bunch_configuration, optical_function, vector_x_name, optic_parameter_name,
                          title, x_unit="", y_unit="",
                          x_unit_multiplier=1, y_unit_multiplier=1, plot_size=5, grid_x_resolution=5,
                          grid_y_resolution=7):
    result_matrix = optical_function(approximator, bunch_configuration)
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
    axes = sns.lineplot(data=data_frame, x=x_name, y=y_name)

    axes.set_xlim(x_min - 0.25 * delta_x, x_max + 0.25 * delta_x)
    axes.set_ylim(y_min - 0.25 * delta_y, y_max + 0.25 * delta_y)

    plt.xticks(np.arange(x_min, x_max + delta_x / grid_x_resolution, delta_x / grid_x_resolution))
    plt.yticks(np.arange(y_min, y_max + delta_y / grid_y_resolution, delta_y / grid_y_resolution))

    axes.set_title(optic_parameter_name + " from " + vector_x_name + "\n" + title)


def plot_optical_function_of_madx(madx_configuration, bunch_configuration, optical_function, vector_x_name,
                                  optic_parameter_name, title, x_unit="", y_unit="",
                                  x_unit_multiplier=1, y_unit_multiplier=1, plot_size=10, grid_x_resolution=5,
                                  grid_y_resolution=7, axes=None):
    fig = plt.gcf()
    fig.set_size_inches(plot_size, plot_size)

    result_matrix = optical_function(bunch_configuration, madx_configuration)
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
    if axes is None:
        axes = sns.lineplot(data=data_frame, x=x_name, y=y_name)
    else:
        sns.lineplot(data=data_frame, x=x_name, y=y_name, axes = axes)

    axes.set_xlim(x_min - 0.25 * delta_x, x_max + 0.25 * delta_x)
    axes.set_ylim(y_min - 0.25 * delta_y, y_max + 0.25 * delta_y)

    plt.xticks(np.arange(x_min, x_max + delta_x / grid_x_resolution, delta_x / grid_x_resolution))
    plt.yticks(np.arange(y_min, y_max + delta_y / grid_y_resolution, delta_y / grid_y_resolution))

    axes.set_title(optic_parameter_name + " from " + vector_x_name + "\n" + title)


def plot_optical_functions(bunch_configuration,
                           optics_functions_with_configurations,
                           vector_x_name, optic_parameter_name, title,
                           x_unit="", y_unit="", x_unit_multiplier=1, y_unit_multiplier=1,
                           plot_size=5, grid_x_resolution=5, grid_y_resolution=7):

    fig = plt.gcf()
    fig.set_size_inches(plot_size, plot_size)

    transporters = optics_functions_with_configurations.keys()

    x_name = vector_x_name + x_unit
    y_name = optic_parameter_name + y_unit
    turn_name = "transporter"

    x_index = mapping[vector_x_name]
    y_index = mapping["result"]

    merged_frame = pd.DataFrame(data={x_name: np.empty((0,)), y_name: np.empty((0,)),
                                turn_name: np.empty((0,))})

    for transporter_name in transporters:
        optical_function, transporter_configuration = optics_functions_with_configurations[transporter_name]
        result_matrix = optical_function(transporter_configuration, bunch_configuration)
        x_vector = result_matrix.T[x_index] * x_unit_multiplier
        y_vector = result_matrix.T[y_index] * y_unit_multiplier
        turn_vector = np.full(x_vector.shape, transporter_name)

        obtained_frame = pd.DataFrame(data={x_name: x_vector, y_name: y_vector,
                                      turn_name: turn_vector})

        merged_frame = pd.concat([merged_frame, obtained_frame])

    x_min = merged_frame[x_name].min()
    x_max = merged_frame[x_name].max()

    y_min = merged_frame[y_name].min()
    y_max = merged_frame[y_name].max()

    delta_x = x_max - x_min
    delta_y = y_max - y_min

    axes = sns.lineplot(data=merged_frame, x=x_name, y=y_name, hue=turn_name)

    axes.set_xlim(x_min - 0.25 * delta_x, x_max + 0.25 * delta_x)
    axes.set_ylim(y_min - 0.25 * delta_y, y_max + 0.25 * delta_y)

    plt.xticks(np.arange(x_min, x_max + delta_x / grid_x_resolution, delta_x / grid_x_resolution))
    plt.yticks(np.arange(y_min, y_max + delta_y / grid_y_resolution, delta_y / grid_y_resolution))

    axes.set_title(optic_parameter_name + " from " + vector_x_name + "\n" + title)
