from data.parameters_names import ParametersNames as Parameters
import ptc_twiss.particles_trajectory_generator as ptg
import ptc_twiss.matrix_indexes as tmi
import numpy as np
import copy


def compute_v_x(madx_configuration, bunch_configuration):
    """
    Compute values of V x on grid specified in bunch configuration
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, V x
    """
    return __compute_optical_function(madx_configuration, bunch_configuration, Parameters.V_X)


def compute_v_y(madx_configuration, bunch_configuration):
    """
    Compute values of V y on grid specified in bunch configuration
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, V y
    """
    return __compute_optical_function(madx_configuration, bunch_configuration, Parameters.V_Y)


def compute_l_x(madx_configuration, bunch_configuration):
    """
    Compute values of L x on grid specified in bunch configuration
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, L x
    """
    return __compute_optical_function(madx_configuration, bunch_configuration, Parameters.L_X)


def compute_l_y(madx_configuration, bunch_configuration):
    """
    Compute values of L y on grid specified in bunch configuration
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, L y
    """
    return __compute_optical_function(madx_configuration, bunch_configuration, Parameters.L_Y)


def compute_d_x(madx_configuration, bunch_configuration):
    """
    Compute values of D x on grid specified in bunch configuration
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, D x
    """
    return __compute_optical_function(madx_configuration, bunch_configuration, Parameters.D_X)


def compute_d_y(madx_configuration, bunch_configuration):
    """
    Compute values of D y on grid specified in bunch configuration
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, D y
    """
    return __compute_optical_function(madx_configuration, bunch_configuration, Parameters.D_Y)


def __compute_optical_function(madx_configuration, bunch_configuration, optical_function_name):
    """
    Compute values of optical function on grid specified in bunch configuration
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object, specification of grid
    :param optical_function_name: name of optical function, ie Parameters.D_X
    :return: matrix with columns: x, theta_x, y, theta_y, pt, optical function
    """
    particles = ptg.generate_from_range(madx_configuration, bunch_configuration)
    result = prepare_matrix(particles, optical_function_name)
    return result


def compute_d_x_vs_s(madx_configuration, bunch_configuration):
    """
    Compute values of optical function vs s for one particle, which coordinates are x_min, theta_x_min, ...
    or x_mean - delta_x, ...
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object
    :return: matrix with rows: s and D x
    """
    return __compute_optical_function_vs_s(madx_configuration, bunch_configuration, Parameters.D_X)


def compute_d_y_vs_s(madx_configuration, bunch_configuration):
    """
    Compute values of optical function vs s for one particle, which coordinates are x_min, theta_x_min, ...
    or x_mean - delta_x, ...
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object
    :return: matrix with rows: s and D y
    """
    return __compute_optical_function_vs_s(madx_configuration, bunch_configuration, Parameters.D_Y)


def __compute_optical_function_vs_s(madx_configuration, bunch_configuration, optical_function_name):
    """
    Compute values of optical function vs s for one particle, which coordinates are x_min, theta_x_min, ...
    or x_mean - delta_x, ...
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object
    :param optical_function_name: String, name of optical function, as specified in matrix_indexes
    :return: matrix with rows: s and optical function
    """
    internal_madx_configuration = copy.copy(madx_configuration)
    internal_madx_configuration.s = -1
    particles = ptg.generate_from_range(internal_madx_configuration, bunch_configuration)
    result = np.append(particles["end"].T[tmi.ptc_twiss[Parameters.S]].reshape((-1, 1)),
                       particles["end"].T[tmi.ptc_twiss[optical_function_name]].reshape((-1, 1)),
                       axis=1)
    return result


def prepare_matrix(particles, parameter_name):
    """
    Create matrix with columns: x, theta x, y, theta y, pt and additional column given as result
    :param particles: matrix returned by transport function
    :param parameter_name: name of optic parameter which should be taken
    :return: matrix with columns x, theta x, y, theta y, pt and optic parameter
    """
    begin_parameters = particles["start"]
    end_parameters = particles["end"]
    result_matrix = begin_parameters.T[tmi.ptc_twiss[Parameters.X]].reshape((-1, 1))
    result_matrix = np.append(result_matrix, begin_parameters.T[tmi.ptc_twiss[Parameters.THETA_X]].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, begin_parameters.T[tmi.ptc_twiss[Parameters.Y]].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, begin_parameters.T[tmi.ptc_twiss[Parameters.THETA_Y]].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, begin_parameters.T[tmi.ptc_twiss[Parameters.CROSSING_ANGLE]].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, begin_parameters.T[tmi.ptc_twiss[Parameters.PT]].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, end_parameters.T[tmi.ptc_twiss[parameter_name]].reshape((-1, 1)), axis=1)
    return result_matrix
