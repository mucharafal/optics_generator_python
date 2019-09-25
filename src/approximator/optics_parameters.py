import approximator.particles_trajectory_generator as ptg
import numpy as np
import copy
from data.parameters_names import ParametersNames as Parameters


def compute_v_x(approximator, bunch_configuration):
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    x_min = internal_bunch_configuration.x_min
    x_max = internal_bunch_configuration.x_max
    delta = __get_delta(x_min, x_max)

    internal_bunch_configuration.x_min += delta
    internal_bunch_configuration.x_max += delta

    shifted_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    x_end_positions = __get_vector_of_transported_matrix(Parameters.X, end_positions)
    x_shifted_end_positions = __get_vector_of_transported_matrix(Parameters.X, shifted_end_positions)

    v_x = (x_shifted_end_positions - x_end_positions) / delta

    begin_positions_vectors = process_input_matrix(reference_particles["start"])
    result = concatenate_result_with_input(begin_positions_vectors, v_x)

    return result


def compute_v_y(approximator, bunch_configuration):
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    y_min = internal_bunch_configuration.y_min
    y_max = internal_bunch_configuration.y_max
    delta = __get_delta(y_min, y_max)

    internal_bunch_configuration.y_min += delta
    internal_bunch_configuration.y_max += delta

    shifted_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    y_end_positions = __get_vector_of_transported_matrix(Parameters.Y, end_positions)
    y_shifted_end_positions = __get_vector_of_transported_matrix(Parameters.Y, shifted_end_positions)

    v_y = (y_shifted_end_positions - y_end_positions) / delta

    begin_positions_vectors = process_input_matrix(reference_particles["start"])
    result = concatenate_result_with_input(begin_positions_vectors, v_y)

    return result


def compute_l_x(approximator, bunch_configuration):
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    theta_x_min = internal_bunch_configuration.theta_x_min
    theta_x_max = internal_bunch_configuration.theta_x_max
    delta = __get_delta(theta_x_min, theta_x_max)

    internal_bunch_configuration.theta_x_min += delta
    internal_bunch_configuration.theta_x_max += delta

    shifted_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    x_end_positions = __get_vector_of_transported_matrix(Parameters.X, end_positions)
    x_shifted_end_positions = __get_vector_of_transported_matrix(Parameters.X, shifted_end_positions)

    l_x = (x_shifted_end_positions - x_end_positions) / delta

    begin_positions_vectors = process_input_matrix(reference_particles["start"])
    result = concatenate_result_with_input(begin_positions_vectors, l_x)

    return result


def compute_l_y(approximator, bunch_configuration):
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    theta_y_min = internal_bunch_configuration.theta_y_min
    theta_y_max = internal_bunch_configuration.theta_y_max
    delta = __get_delta(theta_y_min, theta_y_max)

    internal_bunch_configuration.theta_y_min += delta
    internal_bunch_configuration.theta_y_max += delta

    shifted_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    y_end_positions = __get_vector_of_transported_matrix(Parameters.Y, end_positions)
    y_shifted_end_positions = __get_vector_of_transported_matrix(Parameters.Y, shifted_end_positions)

    l_y = (y_shifted_end_positions - y_end_positions) / delta

    begin_positions_vectors = process_input_matrix(reference_particles["start"])
    result = concatenate_result_with_input(begin_positions_vectors, l_y)

    return result


def compute_d_x(approximator, bunch_configuration):
    """
    Compute Dispersion in x axis using differential
    :param approximator: LHCOpticsApproximator object, used to transport particles
    :param bunch_configuration: BunchConfiguration object, used to generate dataset
    :return: Matrix with columns x, theta x, y, theta y, pt and D x
    """
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    pt_min = internal_bunch_configuration.pt_min
    pt_max = internal_bunch_configuration.pt_max
    delta = __get_delta(pt_min, pt_max)

    internal_bunch_configuration.pt_min += delta
    internal_bunch_configuration.pt_max += delta

    shifted_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    x_end_positions = __get_vector_of_transported_matrix(Parameters.X, end_positions)
    x_shifted_end_positions = __get_vector_of_transported_matrix(Parameters.X, shifted_end_positions)

    d_x = (x_shifted_end_positions - x_end_positions) / delta

    begin_positions_vectors = process_input_matrix(reference_particles["start"])
    result = concatenate_result_with_input(begin_positions_vectors, d_x)

    return result


def compute_d_y(approximator, bunch_configuration):
    """
    Compute Dispersion in y axis using differential
    :param approximator: LHCOpticsApproximator object, used to transport particles
    :param bunch_configuration: BunchConfiguration object, used to generate dataset
    :return: Matrix with columns x, theta x, y, theta y, pt and D y
    """
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    pt_min = internal_bunch_configuration.pt_min
    pt_max = internal_bunch_configuration.pt_max
    delta = __get_delta(pt_min, pt_max)

    internal_bunch_configuration.pt_min += delta
    internal_bunch_configuration.pt_max += delta

    shifted_particles = ptg.generate_from_range(approximator, internal_bunch_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    y_end_positions = __get_vector_of_transported_matrix(Parameters.Y, end_positions)
    y_shifted_end_positions = __get_vector_of_transported_matrix(Parameters.Y, shifted_end_positions)

    d_y = (y_shifted_end_positions - y_end_positions) / delta

    begin_positions_vectors = process_input_matrix(reference_particles["start"])
    result = concatenate_result_with_input(begin_positions_vectors, d_y)

    return result


def __get_delta(min, max):
    multiplier = 1e-5
    potential_delta = multiplier * (max - min)
    return potential_delta if potential_delta > 0 else multiplier


def __get_vector_of_transported_matrix(column_name, matrix):
    columns_mapping = {
        Parameters.X: 0,
        Parameters.THETA_X: 1,
        Parameters.Y: 2,
        Parameters.THETA_Y: 3,
        Parameters.PT: 4
    }
    index = columns_mapping[column_name]
    return matrix.T[index]


def process_input_matrix(matrix):
    rows = matrix.T
    mapping = {
        "x_in": rows[0],
        "theta_x_in": rows[1],
        "y_in": rows[2],
        "theta_y_in": rows[3],
        "pt_in": rows[4]
    }
    return mapping


def concatenate_result_with_input(matrix, result):
    """
    Create matrix with columns: x, theta x, y, theta y, pt and additional column given as result
    :param matrix: dict in form like returned by process_matrix function
    :param result: additional column concatenated to matrix with basic parameters
    :return: matrix with columns x, theta x, y, theta y, pt and result
    """
    result_matrix = matrix["x_in"].reshape((-1, 1))
    result_matrix = np.append(result_matrix, matrix["theta_x_in"].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, matrix["y_in"].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, matrix["theta_y_in"].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, matrix["pt_in"].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, result.reshape((-1, 1)), axis=1)
    return result_matrix

