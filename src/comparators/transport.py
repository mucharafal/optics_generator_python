import visualization.visualize as visualize
import numpy as np
import seaborn as sns
from data.parameters_names import ParametersNames as Parameters
from data.particles import Particles


def compare(input_dataset, transporters, transported_dimension, depended_value,
            title_sufix="", plot_function=sns.scatterplot, **kwargs):
    # datasets["approximator"] = segments: segment_name -> segment_matrix
    datasets = transport(input_dataset, transporters)
    list_of_datasets = to_list(datasets)
    compared = compare_with_others(list_of_datasets[0], list_of_datasets[1:], transported_dimension,
                                   depended_value)
    axes = visualize.plot_datasets(depended_value, Parameters.get_delta(transported_dimension), "Compare", compared,
                                   title_sufix, plot_function, s=1, markers=["x"], **kwargs)
    return axes


def transport(dataset, transporters):
    results = {}
    for key in transporters:
        transporter = transporters[key]
        results[key] = transporter(dataset)
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
    dataset = reference_dataset[1]
    reference_values = dataset["end"].get_coordinates_of(transported_dimension)
    result = {}
    for dataset_pack in others_datasets:
        (dataset_name, obtained_dataset) = dataset_pack
        name = reference_dataset_name + " - " + dataset_name
        obtained_values = obtained_dataset["end"].get_coordinates_of(transported_dimension)
        absolute_difference = obtained_values - reference_values
        matrix = np.append(absolute_difference.reshape((-1, 1)),
                           dataset["start"].get_coordinates_of(depended_value),
                           axis=1)
        new_matrix_mapping = {Parameters.get_delta(transported_dimension): 0, depended_value: 1}
        result[name] = Particles(matrix, new_matrix_mapping)
    return dict(result, **compare_with_others(others_datasets[0], others_datasets[1:], transported_dimension,
                                              depended_value))



