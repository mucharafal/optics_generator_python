import visualization.visualize as visualize
import pandas as pd
import numpy as np
import seaborn as sns
import data.units as units
import data.particles_generator as pg


def compare(dataset_configuration, transporters, transported_dimension, depended_value,
            title_sufix="", plot_axes=None, plot_x_pos=None, plot_y_pos=None,
            plot_function=sns.lineplot, x_axis_configuration=None, y_axis_configuration=None):
    # datasets["approximator"] = segments: segment_name -> segment_matrix
    input_matrix = pg.generate_particles_randomly(dataset_configuration)
    datasets = transport(input_matrix, transporters)
    list_of_datasets = to_list(datasets)
    compared = compare_with_others(list_of_datasets[0], list_of_datasets[1:], transported_dimension,
                                   depended_value)
    axes = visualize.plot_datasets(depended_value, "delta " + transported_dimension, "Compare", compared,
                                   title_sufix, plot_axes, plot_x_pos, plot_y_pos, plot_function, x_axis_configuration,
                                   y_axis_configuration)
    return axes


def compare_heatmap(dataset_configuration, reference_transporter, compared_transporter, transported_dimension,
                    depended_value, title_sufix="", plot_axes=None, plot_x_pos=None, plot_y_pos=None,
                    plot_function=sns.lineplot, x_axis_configuration=None, y_axis_configuration=None):
    # datasets["approximator"] = segments: segment_name -> segment_matrix
    transporters = {reference_transporter[0]: reference_transporter[1],
                    compared_transporter[0]: compared_transporter[1]}
    datasets = transport(dataset_configuration, transporters)
    list_of_datasets = to_list(datasets)
    compared = compare_with_others(list_of_datasets[0], list_of_datasets[1:], transported_dimension,
                                   depended_value)
    (matrix, mapping) = compared[list(compared.keys())[0]]
    dataframe = pd.DataFrame({transported_dimension:
                                  matrix.T[mapping["delta " + transported_dimension]] *
                                  units.multiplier_for_unit[transported_dimension] * 1e6,
                              depended_value: matrix.T[mapping[depended_value]] *
                                              units.multiplier_for_unit[depended_value] * 1e6})
    print(dataframe)
    return dataframe
    axes = sns.heatmap(dataframe, vmin=0, vmax=1)
    axes.set_yscale("log")


def transport(dataset_configuration, transporters):
    results = {}
    for key in transporters:
        (transporter, configuration, mapping) = transporters[key]
        results[key] = (transporter(configuration, dataset_configuration), mapping)
    return results


def to_list(map):
    result_list = []
    for key in map:
        result_list.append((key, map[key]))
    return result_list


def compare_with_others(reference_dataset, others_datasets, transported_dimension, depended_value):
    if not others_datasets:
        return {}
    reference_dataset_name = reference_dataset[0]
    (dataset, mapping) = reference_dataset[1]
    reference_values = dataset["end"].T[mapping[transported_dimension]]
    result = {}
    for dataset_pack in others_datasets:
        (dataset_name, obtained_pack) = dataset_pack
        name = reference_dataset_name + " - " + dataset_name
        (obtained_dataset, obtained_mapping) = obtained_pack
        obtained_values = obtained_dataset["end"].T[obtained_mapping[transported_dimension]]
        absolute_difference = obtained_values - reference_values
        matrix = np.append(absolute_difference.reshape((-1, 1)),
                           dataset["start"].T[mapping[depended_value]].reshape((-1, 1)),
                           axis=1)
        new_matrix_mapping = {"delta " + transported_dimension: 0, depended_value: 1}
        result[name] = (matrix, new_matrix_mapping)
    return dict(result, **compare_with_others(others_datasets[0], others_datasets[1:], transported_dimension,
                                              depended_value))



