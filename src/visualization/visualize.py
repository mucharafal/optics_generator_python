import seaborn as sns
import numpy as np
import pandas as pd
from data.units import unit_map, multiplier_for_unit, alternative_version


def plot_from_one_matrix(x_name, y_name, matrix, mapping,
                         title_sufix="", x_name_prefix="", y_name_prefix="",
                         plot_function=sns.lineplot, **additional_plot_function_arguments):
    return plot_from_two_matrices(x_name, y_name, matrix, matrix, mapping, mapping,
                                  title_sufix, x_name_prefix, y_name_prefix,
                                  plot_function, **additional_plot_function_arguments)


def plot_from_two_matrices(x_name, y_name, x_matrix, y_matrix, x_matrix_mapping, y_matrix_mapping,
                           title_sufix="", x_name_prefix="", y_name_prefix="",
                           plot_function=sns.lineplot, **additional_plot_function_arguments):

    # Get names of axis and title of plot
    x_alternative_version = alternative_version[x_name]
    y_alternative_version = alternative_version[y_name]

    x_full_name = "x: " + x_name_prefix + x_alternative_version + unit_map[x_name]
    y_full_name = "y: " + y_name_prefix + y_alternative_version + unit_map[y_name]

    title = y_name_prefix + y_alternative_version + " vs " + x_name_prefix + x_alternative_version
    title += "\n" + title_sufix

    # Get vectors and their properties
    x_index = x_matrix_mapping[x_name]
    y_index = y_matrix_mapping[y_name]

    vector_x = x_matrix.T[x_index] * multiplier_for_unit[x_name]
    vector_y = y_matrix.T[y_index] * multiplier_for_unit[y_name]

    frame = pd.DataFrame(data={x_full_name: vector_x, y_full_name: vector_y})

    axes = plot_function(x=x_full_name, y=y_full_name, data=frame,
                         **additional_plot_function_arguments)

    axes.set_title(title)
    axes.set_xlim(np.min(vector_x), np.max(vector_x))

    return axes


def generate_dataset(x_name, y_name, hue_name, datasets):

    merged_dataframe = pd.DataFrame(data={x_name: np.empty((0,)), y_name: np.empty((0,)), hue_name: np.empty((0,))})

    for dataset_name in datasets:
        matrix, index_mapping = datasets[dataset_name]

        x_index = index_mapping[x_name]
        y_index = index_mapping[y_name]

        x = matrix.T[x_index] * multiplier_for_unit[x_name]
        y = matrix.T[y_index] * multiplier_for_unit[y_name]
        hue = np.full((len(x),), dataset_name)

        frame = pd.DataFrame(data={x_name: x, y_name: y, hue_name: hue})

        merged_dataframe = merged_dataframe.append(frame)

    return merged_dataframe


def plot_datasets(x_name, y_name, legend_title, datasets, title_sufix="",
                  plot_function=sns.lineplot,
                  **additional_plot_function_arguments):
    """
    Plot different datasets on one plot.
    :param x_name: name of x parameter in datasets
    :type x_name: str
    :param y_name: name of y parameter in datasets
    :type y_name: str
    :param legend_title: String, title in legend
    :type legend_title: str
    :param datasets: keys is name of dataset, value tuple with matrix and its mapping
    :type datasets: dict
    :param title_sufix: optional; added to title in new line
    :type title_sufix: str
    :param plot_function: function use to plot- seaborn.scatterplot or seaborn.lineplot
    """
    x_alternative_version = alternative_version[x_name]
    y_alternative_version = alternative_version[y_name]

    x_full_name = x_alternative_version + unit_map[x_name]
    y_full_name = y_alternative_version + unit_map[y_name]

    frame = generate_dataset(x_name, y_name, legend_title, datasets)

    title = y_alternative_version + " vs " + x_alternative_version
    title += "\n" + title_sufix

    axes = plot_function(x=x_name, y=y_name, hue=legend_title, data=frame, style=legend_title,
                         **additional_plot_function_arguments)

    axes.set_xlabel(x_full_name)
    axes.set_ylabel(y_full_name)

    axes.set_title(title)

    axes.set_xlim(frame[x_name].min(), frame[x_name].max())

    return axes
