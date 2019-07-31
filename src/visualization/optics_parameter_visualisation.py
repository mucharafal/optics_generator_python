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
    axes = sns.scatterplot(data=data_frame, x=x_name, y=y_name)

    axes.set_xlim(x_min - 0.25 * delta_x, x_max + 0.25 * delta_x)
    axes.set_ylim(y_min - 0.25 * delta_y, y_max + 0.25 * delta_y)

    plt.xticks(np.arange(x_min, x_max + delta_x / grid_x_resolution, delta_x / grid_x_resolution))
    plt.yticks(np.arange(y_min, y_max + delta_y / grid_y_resolution, delta_y / grid_y_resolution))

    axes.set_title(y_name + " from " + x_name + "\n" + title)


def plot_optical_function_of_madx(madx_configuration, bunch_configuration, optical_function, vector_x_name,
                                  optic_parameter_name, title, x_unit="", y_unit="",
                                  x_unit_multiplier=1, y_unit_multiplier=1, plot_size=5, grid_x_resolution=5,
                                  grid_y_resolution=7):
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
    axes = sns.scatterplot(data=data_frame, x=x_name, y=y_name)

    axes.set_xlim(x_min - 0.25 * delta_x, x_max + 0.25 * delta_x)
    axes.set_ylim(y_min - 0.25 * delta_y, y_max + 0.25 * delta_y)

    plt.xticks(np.arange(x_min, x_max + delta_x / grid_x_resolution, delta_x / grid_x_resolution))
    plt.yticks(np.arange(y_min, y_max + delta_y / grid_y_resolution, delta_y / grid_y_resolution))

    axes.set_title(y_name + " from " + x_name + "\n" + title)


def plot_optical_functions(bunch_configuration,
                           madx_configuration, madx_optical_function,
                           approximator, approximator_optical_function,
                           vector_x_name, optic_parameter_name, title,
                           x_unit="", y_unit="", x_unit_multiplier=1, y_unit_multiplier=1,
                           plot_size=5, grid_x_resolution=5, grid_y_resolution=7):
    madx_result_matrix = madx_optical_function(bunch_configuration, madx_configuration)
    approximator_result_matrix = approximator_optical_function(approximator, bunch_configuration)

    x_index = mapping[vector_x_name]
    y_index = mapping["result"]

    madx_x_vector = madx_result_matrix.T[x_index] * x_unit_multiplier
    madx_y_vector = madx_result_matrix.T[y_index] * y_unit_multiplier
    madx_turn_vector = np.full(madx_x_vector.shape, 0)

    approximator_x_vector = approximator_result_matrix.T[x_index] * x_unit_multiplier
    approximator_y_vector = approximator_result_matrix.T[y_index] * y_unit_multiplier
    approximator_turn_vector = np.full(approximator_x_vector.shape, 1)

    x_name = vector_x_name + x_unit
    y_name = optic_parameter_name + y_unit
    turn_name = "turn"

    madx_frame = pd.DataFrame(data={x_name: madx_x_vector, y_name: madx_y_vector,
                                    turn_name: madx_turn_vector})

    approximator_frame = pd.DataFrame(data={x_name: approximator_x_vector, y_name: approximator_y_vector,
                                            turn_name: approximator_turn_vector})

    merged_frame = pd.concat([madx_frame, approximator_frame])

    x_min = merged_frame[x_name].min()
    x_max = merged_frame[x_name].max()

    y_min = merged_frame[y_name].min()
    y_max = merged_frame[y_name].max()

    delta_x = x_max - x_min
    delta_y = y_max - y_min

    axes = sns.scatterplot(data=merged_frame, x=x_name, y=y_name, hue=turn_name)

    axes.set_xlim(x_min - 0.25 * delta_x, x_max + 0.25 * delta_x)
    axes.set_ylim(y_min - 0.25 * delta_y, y_max + 0.25 * delta_y)

    plt.xticks(np.arange(x_min, x_max + delta_x / grid_x_resolution, delta_x / grid_x_resolution))
    plt.yticks(np.arange(y_min, y_max + delta_y / grid_y_resolution, delta_y / grid_y_resolution))

    axes.set_title(y_name + " from " + x_name + "\n" + title)
