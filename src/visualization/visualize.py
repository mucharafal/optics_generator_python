import seaborn as sns
import numpy as np
import pandas as pd
from data.units import unit_map, multiplier_for_unit


def plot_from_one_matrix(x_name, y_name, matrix, mapping,
                         plot_axes=None, plot_x_pos=-1, plot_y_pos=-1,
                         title_sufix="", x_name_prefix="", y_name_prefix="",
                         plot_function=sns.lineplot, color="b",
                         x_axis_configuration=None, y_axis_configuration=None):
    return plot_from_two_matrices(x_name, y_name, matrix, matrix, mapping, mapping,
                                  plot_axes, plot_x_pos, plot_y_pos,
                                  title_sufix, x_name_prefix, y_name_prefix,
                                  plot_function, color,
                                  x_axis_configuration, y_axis_configuration)


def plot_from_two_matrices(x_name, y_name, x_matrix, y_matrix, x_matrix_mapping, y_matrix_mapping,
                           plot_axes=None, plot_x_pos=-1, plot_y_pos=-1,
                           title_sufix="", x_name_prefix="", y_name_prefix="",
                           plot_function=sns.lineplot, color="b",
                           x_axis_configuration=None, y_axis_configuration=None):
    # Get names of axis and title of plot

    x_full_name = x_name_prefix + x_name + unit_map[x_name]
    y_full_name = y_name_prefix + y_name + unit_map[y_name]

    title = y_name_prefix + y_name + " from " + x_name_prefix + x_name
    title += "\n" + title_sufix

    # Get vectors and their properties
    x_index = x_matrix_mapping[x_name]
    y_index = y_matrix_mapping[y_name]

    vector_x = x_matrix.T[x_index] * multiplier_for_unit[x_name]
    vector_y = y_matrix.T[y_index] * multiplier_for_unit[y_name]

    frame = pd.DataFrame(data={x_full_name: vector_x, y_full_name: vector_y})

    if plot_axes is None:
        axes = plot_function(x=x_full_name, y=y_full_name, data=frame, color=color)
    elif plot_x_pos == -1:
        axes = plot_function(x=x_full_name, y=y_full_name, data=frame, ax=plot_axes, color=color)
    elif plot_y_pos == -1:
        axes = plot_function(x=x_full_name, y=y_full_name, data=frame, ax=plot_axes[plot_x_pos], color=color)
    else:
        axes = plot_function(x=x_full_name, y=y_full_name, data=frame, ax=plot_axes[plot_x_pos][plot_y_pos], color=color)

    axes.set_title(title)

    if x_axis_configuration is not None:
        axes.xaxis.set_ticks(x_axis_configuration.get_ticks())

    if y_axis_configuration is not None:
        axes.yaxis.set_ticks(y_axis_configuration.get_ticks())


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


def plot_with_turn(x_name, y_name, hue_name, datasets, title_sufix="",
                   plot_axes=None, plot_x_pos=-1, plot_y_pos=-1,
                   plot_function=sns.lineplot, x_axis_configuration=None, y_axis_configuration=None):

    x_full_name = x_name + unit_map[x_name]
    y_full_name = y_name + unit_map[y_name]

    frame = generate_dataset(x_name, y_name, hue_name, datasets)

    title = y_name + " from " + x_name
    title += "\n" + title_sufix

    if plot_axes is None:
        axes = plot_function(x=x_name, y=y_name, hue=hue_name, data=frame)
    elif plot_x_pos == -1:
        axes = plot_function(x=x_name, y=y_name, hue=hue_name, data=frame, ax=plot_axes, style=hue_name, size=hue_name)
    elif plot_y_pos == -1:
        axes = plot_function(x=x_name, y=y_name, hue=hue_name, data=frame, ax=plot_axes[plot_x_pos], style=hue_name, size=hue_name)
    else:
        axes = plot_function(x=x_name, y=y_name, hue=hue_name, data=frame, ax=plot_axes[plot_x_pos][plot_y_pos], style=hue_name, size=hue_name)

    axes.set_xlabel(x_full_name)
    axes.set_ylabel(y_full_name)

    axes.set_title(title)

    if x_axis_configuration is not None:
        axes.xaxis.set_ticks(x_axis_configuration.get_ticks())

    if y_axis_configuration is not None:
        axes.yaxis.set_ticks(y_axis_configuration.get_ticks())
