import seaborn as sns
import visualization.visualize as visualize
from data.parameters_names import ParametersNames as Parameters


def plot_optical_functions(particles, optics_functions,
                           vector_x_name, optic_parameter_name, title="",
                           plot_function=sns.lineplot, **kwargs):
    """
    Plot optical functions specified in configuration
    :param particles: configuration of dataset
    :param optics_functions: map where key is name of transported (ie ptc_track) and value is tuple:
    (optical function, transporter_configuration (for ptc_track, for approximator it is approximator object))
    :param vector_x_name: name of x axis parameter
    :param optic_parameter_name: name of optical function
    :param title: subtitle, optional
    :param plot_function: plot function used to plot ie seaborn.lineplot or scatterplot
    :return:
    """
    return plot_optical_functions_with_different_datasets({"": particles}, optics_functions,
                                                          vector_x_name, optic_parameter_name, title,
                                                          plot_function, **kwargs)


def plot_optical_functions_with_different_datasets(datasets, optics_functions_with_configurations,
                                                   vector_x_name, optic_parameter_name, title="",
                                                   plot_function=sns.lineplot, **kwargs):
    """
    Plot optical functions specified in configuration
    :param datasets: map, where key is name of dataset, value- configuration of dataset
    :param optics_functions_with_configurations: map where key is name of transported (ie ptc_track) and value is tuple:
    (optical function, transporter_configuration (for ptc_track, for approximator it is approximator object))
    :param vector_x_name: name of x axis parameter
    :param optic_parameter_name: name of optical function
    :param title: subtitle, optional
    :param plot_function: plot function used to plot ie seaborn.lineplot or scatterplot
    :return:
    """

    def create_dataset(configuration, particles_):
        optical_function, transporter = configuration
        result_matrix = optical_function(transporter, particles_)
        return result_matrix

    new_datasets = {}
    for dataset_name in datasets:
        particles = datasets[dataset_name]
        for transporter_name in optics_functions_with_configurations:
            key = dataset_name + transporter_name
            new_datasets[key] = create_dataset(optics_functions_with_configurations[transporter_name],
                                               particles)

    return visualize.plot_datasets(vector_x_name, optic_parameter_name, "transporters", new_datasets, title,
                                   plot_function, **kwargs)


