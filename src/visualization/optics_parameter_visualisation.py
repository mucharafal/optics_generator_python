import ROOT
from ROOT import gSystem, gInterpreter
import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import visualization.visualize as visualize

mapping = {
    "x": 0,
    "theta x": 1,
    "y": 2,
    "theta y": 3,
    "pt": 4,
    "result": 5,
    "D x": 5,
    "D y": 5,
    "L x": 5,
    "L y": 5,
    "V x": 5,
    "V y": 5
}


def plot_optical_function_of_approximator(approximator, bunch_configuration, optical_function, vector_x_name, optic_parameter_name,
                          title, x_unit="", y_unit="",
                          x_unit_multiplier=1, y_unit_multiplier=1, plot_size=5):
    # todo remove it
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

    axes.set_title(optic_parameter_name + " from " + vector_x_name + "\n" + title)


def plot_optical_function_of_madx(madx_configuration, bunch_configuration, optical_function, vector_x_name,
                                  optic_parameter_name, title, x_unit="", y_unit="",
                                  x_unit_multiplier=1, y_unit_multiplier=1, plot_size=10, grid_x_resolution=5,
                                  grid_y_resolution=7, axes=None):
    # todo remove it
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
                           vector_x_name, optic_parameter_name, title="",
                           plot_size=5, plot_axes=None, plot_x_pos=-1, plot_y_pos=-1, plot_function=sns.lineplot,
                           custom_mapping = mapping, x_axis_configuration=None, y_axis_configuration=None):
    """
    Plot optical functions specified in configuration
    :param bunch_configuration: configuration of dataset
    :param optics_functions_with_configurations: map where key is name of transported (ie ptc_track) and value is tuple:
    (optical function, transporter_configuration (for ptc_track, for approximator it is approximator object))
    :param vector_x_name: name of x axis parameter
    :param optic_parameter_name: name of optical function
    :param title: subtitle, optional
    :param plot_size: optional, size of plot. Only if plot axes is not specified, otherwise behaviour is not checked
    :param plot_axes: axes object
    :param plot_x_pos: x position on axes
    :param plot_y_pos: y position on axes
    :param plot_function: plot function used to plot ie seaborn.lineplot or scatterplot
    :return:
    """
    plot_optical_functions_with_different_datasets({"": bunch_configuration}, optics_functions_with_configurations,
                                                   vector_x_name, optic_parameter_name, title, plot_size,
                                                   plot_axes, plot_x_pos, plot_y_pos, plot_function, custom_mapping,
                                                   x_axis_configuration, y_axis_configuration)


def plot_optical_functions_with_different_datasets(bunch_configurations, optics_functions_with_configurations,
                                                   vector_x_name, optic_parameter_name, title="", plot_size=5,
                                                   plot_axes=None, plot_x_pos=-1, plot_y_pos=-1,
                                                   plot_function=sns.lineplot, custom_mapping=mapping,
                                                   x_axis_configuration=None, y_axis_configuration=None):
    """
    Plot optical functions specified in configuration
    :param bunch_configurations: map, where key is name of dataset, value- configuration of dataset
    :param optics_functions_with_configurations: map where key is name of transported (ie ptc_track) and value is tuple:
    (optical function, transporter_configuration (for ptc_track, for approximator it is approximator object))
    :param vector_x_name: name of x axis parameter
    :param optic_parameter_name: name of optical function
    :param title: subtitle, optional
    :param plot_size: optional, size of plot. Only if plot axes is not specified, otherwise behaviour is not checked
    :param plot_axes: axes object
    :param plot_x_pos: x position on axes
    :param plot_y_pos: y position on axes
    :param plot_function: plot function used to plot ie seaborn.lineplot or scatterplot
    :return:
    """
    fig = plt.gcf()
    fig.set_size_inches(plot_size, plot_size)

    def create_dataset(configuration, bunch_configuration):
        optical_function, transporter_configuration = configuration
        result_matrix = optical_function(transporter_configuration, bunch_configuration)
        return result_matrix, custom_mapping

    datasets = {}
    for dataset_name in bunch_configurations:
        bunch_configuration = bunch_configurations[dataset_name]
        for transporter_name in optics_functions_with_configurations:
            key = dataset_name + transporter_name
            datasets[key] = create_dataset(optics_functions_with_configurations[transporter_name],
                                           bunch_configuration)

    visualize.plot_with_turn(vector_x_name, optic_parameter_name, "transporters", datasets, title,
                             plot_axes, plot_x_pos, plot_y_pos, plot_function, x_axis_configuration=x_axis_configuration,
                             y_axis_configuration=y_axis_configuration)


