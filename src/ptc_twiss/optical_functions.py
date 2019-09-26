from data.parameters_names import ParametersNames as Parameters
import ptc_twiss.transporter as ptg
import ptc_twiss.matrix_indexes as tmi
import numpy as np
from data.particles import Particles


def compute_v_x(transporter, particles):
    """
    Compute values of V x on grid specified in bunch configuration
    :param transporter: transport function
    :param particles: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, V x
    """
    return __compute_optical_function(transporter, particles, Parameters.V_X)


def compute_v_y(transporter, particles):
    """
    Compute values of V y on grid specified in bunch configuration
    :param transporter: transport function
    :param particles: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, V y
    """
    return __compute_optical_function(transporter, particles, Parameters.V_Y)


def compute_l_x(transporter, particles):
    """
    Compute values of L x on grid specified in bunch configuration
    :param transporter: transport function
    :param particles: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, L x
    """
    return __compute_optical_function(transporter, particles, Parameters.L_X)


def compute_l_y(transporter, particles):
    """
    Compute values of L y on grid specified in bunch configuration
    :param transporter: transport function
    :param particles: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, L y
    """
    return __compute_optical_function(transporter, particles, Parameters.L_Y)


def compute_d_x(transporter, particles):
    """
    Compute values of D x on grid specified in bunch configuration
    :param transporter: transport function
    :param particles: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, D x
    """
    return __compute_optical_function(transporter, particles, Parameters.D_X)


def compute_d_y(transporter, particles):
    """
    Compute values of D y on grid specified in bunch configuration
    :param transporter: transport function
    :param particles: BunchConfiguration object, specification of grid
    :return: matrix with columns: x, theta_x, y, theta_y, pt, D y
    """
    return __compute_optical_function(transporter, particles, Parameters.D_Y)


def __compute_optical_function(transporter, particles, optical_function_name):
    """
    Compute values of optical function on grid specified in bunch configuration
    :param transporter: transport function
    :param particles: BunchConfiguration object, specification of grid
    :param optical_function_name: name of optical function, ie Parameters.D_X
    :return: matrix with columns: x, theta_x, y, theta_y, pt, optical function
    """
    segments = ptg.transport(transporter, particles)
    result = prepare_matrix(segments, optical_function_name)
    return result


def compute_d_x_vs_s(transporter, particles):
    """
    Compute values of optical function vs s for one particle, which coordinates are x_min, theta_x_min, ...
    or x_mean - delta_x, ...
    :param transporter: transport function
    :param particles: BunchConfiguration object
    :return: matrix with rows: s and D x
    """
    return __compute_optical_function_vs_s(transporter, particles, Parameters.D_X)


def compute_d_y_vs_s(transporter, particles):
    """
    Compute values of optical function vs s for one particle, which coordinates are x_min, theta_x_min, ...
    or x_mean - delta_x, ...
    :param transporter: transport function
    :param particles: BunchConfiguration object
    :return: matrix with rows: s and D y
    """
    return __compute_optical_function_vs_s(transporter, particles, Parameters.D_Y)


def __compute_optical_function_vs_s(transporter, particles, optical_function_name):
    # todo Adjust
    """
    Compute values of optical function vs s for one particle, which coordinates are x_min, theta_x_min, ...
    or x_mean - delta_x, ...
    :param transporter: transport function
    :param particles: BunchConfiguration object
    :param optical_function_name: String, name of optical function, as specified in matrix_indexes
    :return: matrix with rows: s and optical function
    """
    particles = transporter(particles)
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
    result_matrix = begin_parameters.get_canonical_parameters(Parameters.X, Parameters.THETA_X, Parameters.Y,
                                                              Parameters.THETA_Y, Parameters.PT)
    optical_function_values = end_parameters.get_canonical_parameters(parameter_name)
    result_matrix = np.append(result_matrix, optical_function_values, axis=1)
    return Particles(result_matrix, get_mapping(parameter_name))


def get_mapping(parameter_name):
    mapping = {
        Parameters.X: 0,
        Parameters.THETA_X: 1,
        Parameters.Y: 2,
        Parameters.THETA_Y: 3,
        Parameters.PT: 4,
        parameter_name: 5
    }
    return mapping
