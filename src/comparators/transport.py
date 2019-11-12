import visualization.visualize as visualize
from data.parameters_names import ParametersNames as Parameters
from data.particles import CanonicalCoordinates
import transporters.transporters_factory as transporters_factory
import seaborn as sns


def compare(input_dataset, transporters):
    # datasets["approximator"] = segments: segment_name -> segment_matrix
    datasets = __transport(input_dataset, transporters)
    list_of_datasets = __to_list(datasets)
    dict_with_differences = __compare_with_others(list_of_datasets[0], list_of_datasets[1:])
    dict_with_differences_with_beginning_positions = {key: __merge_particles(particles, input_dataset)
                                                      for key, particles in dict_with_differences.items()}
    return dict_with_differences_with_beginning_positions


def plot(datasets, transported_dimension, depended_value, **kwargs):
    return visualize.plot_datasets(depended_value, Parameters.get_delta(transported_dimension), "Compare", datasets,
                                   s=1, markers=["x"], plot_function = sns.scatterplot, **kwargs)


def __transport(dataset, transporters):
    results = {}
    for key in transporters:
        transporter_configuration = transporters[key]
        transporter = transporters_factory.get_transporter(transporter_configuration)
        results[key] = transporter(dataset)
    return results


def __to_list(map):
    result_list = []
    for key in map:
        result_list.append((key, map[key]))
    return result_list


def __compare_with_others(reference_dataset, others_datasets):
    if not others_datasets:
        return {}
    reference_dataset_name = reference_dataset[0]
    reference_values = reference_dataset[1]["end"]
    result = {}
    for dataset_pack in others_datasets:
        (dataset_name, obtained_dataset) = dataset_pack
        name = reference_dataset_name + " - " + dataset_name
        obtained_values = obtained_dataset["end"]
        difference = __subtract_particles(obtained_values, reference_values)
        result[name] = difference
    return dict(result, **__compare_with_others(others_datasets[0], others_datasets[1:]))


def __subtract_particles(particles1, particles2):
    common_keys = set(particles1.get_mapping().keys()).intersection(set(particles2.get_mapping().keys()))
    output_object = CanonicalCoordinates.empty()
    for key in common_keys:
        values_from_first  = particles1.get_canonical_coordinates_of(key)
        values_from_second = particles2.get_canonical_coordinates_of(key)
        difference = values_from_first - values_from_second
        delta_of_key = Parameters.get_delta(key)
        output_object = output_object.add_column(delta_of_key, difference)

    return output_object


def __merge_particles(particles1, particles2):
    output_particles = particles1
    for key in particles2.get_mapping():
        output_particles = output_particles.add_column(key, particles2.get_values_of(key))

    return output_particles



