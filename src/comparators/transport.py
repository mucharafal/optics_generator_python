import visualization.visualize as visualize
import numpy as np
import seaborn as sns
import data.particles_generator as pg
from data.parameters_names import ParametersNames as Parameters


def compare(dataset_configuration, transporters, transported_dimension, depended_value,
            title_sufix="", plot_function=sns.scatterplot, **kwargs):
    # datasets["approximator"] = segments: segment_name -> segment_matrix
    input_matrix = pg.generate_particles_randomly(dataset_configuration)
    datasets = transport(input_matrix, transporters)
    list_of_datasets = to_list(datasets)
    compared = compare_with_others(list_of_datasets[0], list_of_datasets[1:], transported_dimension,
                                   depended_value)
    axes = visualize.plot_datasets(depended_value, "delta " + transported_dimension, "Compare", compared,
                                   title_sufix, plot_function, s=1, markers=[Parameters.X], **kwargs)
    return axes


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



