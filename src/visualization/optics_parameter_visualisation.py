import seaborn as sns
import visualization.visualize as visualize
from data.parameters_names import ParametersNames as Parameters


optical_functions_matrix_mapping = {
    Parameters.X: 0,
    Parameters.THETA_X: 1,
    Parameters.Y: 2,
    Parameters.THETA_Y: 3,
    Parameters.CROSSING_ANGLE: 4,
    Parameters.PT: 5,
    Parameters.D_X: 6,
    Parameters.D_Y: 6,
    Parameters.L_X: 6,
    Parameters.L_Y: 6,
    Parameters.V_X: 6,
    Parameters.V_Y: 6
}


def plot_optical_functions(bunch_configuration,
                           optics_functions_with_configurations,
                           vector_x_name, optic_parameter_name, title="",
                           plot_function=sns.lineplot, custom_mapping = optical_functions_matrix_mapping, **kwargs):
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
    return plot_optical_functions_with_different_datasets({"": bunch_configuration}, optics_functions_with_configurations,
                                                          vector_x_name, optic_parameter_name, title,
                                                          plot_function, custom_mapping, **kwargs)


def plot_optical_functions_with_different_datasets(bunch_configurations, optics_functions_with_configurations,
                                                   vector_x_name, optic_parameter_name, title="",
                                                   plot_function=sns.lineplot,
                                                   custom_mapping=optical_functions_matrix_mapping, **kwargs):
    """
    Plot optical functions specified in configuration
    :param bunch_configurations: map, where key is name of dataset, value- configuration of dataset
    :param optics_functions_with_configurations: map where key is name of transported (ie ptc_track) and value is tuple:
    (optical function, transporter_configuration (for ptc_track, for approximator it is approximator object))
    :param vector_x_name: name of x axis parameter
    :param optic_parameter_name: name of optical function
    :param title: subtitle, optional
    :param plot_function: plot function used to plot ie seaborn.lineplot or scatterplot
    :return:
    """

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

    return visualize.plot_datasets(vector_x_name, optic_parameter_name, "transporters", datasets, title, plot_function,
                                   **kwargs)


