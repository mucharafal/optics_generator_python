import transporters.transporters_factory as transporters_factory
from data.parameters_names import ParametersNames as Parameters


def get_d_x(configuration):
    return get_optical_function(Parameters.D_X, configuration)


def get_d_y(configuration):
    return get_optical_function(Parameters.D_Y, configuration)


def get_l_x(configuration):
    return get_optical_function(Parameters.L_X, configuration)


def get_l_y(configuration):
    return get_optical_function(Parameters.L_Y, configuration)


def get_v_x(configuration):
    return get_optical_function(Parameters.V_X, configuration)


def get_v_y(configuration):
    return get_optical_function(Parameters.V_Y, configuration)


def get_optical_function(optical_function_name, configuration):
    module = configuration.get_module_with_optical_functions()
    transporter = transporters_factory.get_transporter(configuration)

    optical_functions_mapping = __get_optical_functions_mapping(module)
    uninitialized_optical_function = optical_functions_mapping[optical_function_name]

    def initialized_optical_function(particles):
        return uninitialized_optical_function(transporter, particles)

    return initialized_optical_function


def __get_optical_functions_mapping(module):
    mapping = {
        Parameters.D_X: module.compute_d_x,
        Parameters.D_Y: module.compute_d_y,
        Parameters.L_X: module.compute_l_x,
        Parameters.L_Y: module.compute_l_y,
        Parameters.V_X: module.compute_v_x,
        Parameters.V_Y: module.compute_v_y
    }
    return mapping
