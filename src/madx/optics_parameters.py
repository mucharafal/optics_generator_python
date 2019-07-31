import madx.particles_trajectory_generator as ptg
import numpy as np


def compute_v_x(bunch_configuration, madx_configuration):
    reference_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    print(reference_particles["start"])

    x_min = bunch_configuration.x_min
    x_max = bunch_configuration.x_max
    delta = __get_delta(x_min, x_max)

    bunch_configuration.x_min += delta
    bunch_configuration.x_max += delta

    shifted_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    begin_positions, end_positions, shifted_end_positions = adjust_particles_numbers(reference_particles["start"],
                                                                                     end_positions,
                                                                                     shifted_end_positions)

    x_end_positions = __get_vector_of_transported_matrix("x", end_positions)
    x_shifted_end_positions = __get_vector_of_transported_matrix("x", shifted_end_positions)

    v_x = (x_shifted_end_positions - x_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, v_x)

    return result


def compute_v_y(bunch_configuration, madx_configuration):
    reference_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    y_min = bunch_configuration.y_min
    y_max = bunch_configuration.y_max
    delta = __get_delta(y_min, y_max)

    bunch_configuration.y_min += delta
    bunch_configuration.y_max += delta

    shifted_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    begin_positions, end_positions, shifted_end_positions = adjust_particles_numbers(reference_particles["start"],
                                                                                     end_positions,
                                                                                     shifted_end_positions)

    y_end_positions = __get_vector_of_transported_matrix("y", end_positions)
    y_shifted_end_positions = __get_vector_of_transported_matrix("y", shifted_end_positions)

    v_y = (y_shifted_end_positions - y_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, v_y)

    return result


def compute_l_x(bunch_configuration, madx_configuration):
    reference_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    theta_x_min = bunch_configuration.theta_x_min
    theta_x_max = bunch_configuration.theta_x_max
    delta = __get_delta(theta_x_min, theta_x_max)

    bunch_configuration.theta_x_min += delta
    bunch_configuration.theta_x_max += delta

    shifted_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    begin_positions, end_positions, shifted_end_positions = adjust_particles_numbers(reference_particles["start"],
                                                                                     end_positions,
                                                                                     shifted_end_positions)

    x_end_positions = __get_vector_of_transported_matrix("x", end_positions)
    x_shifted_end_positions = __get_vector_of_transported_matrix("x", shifted_end_positions)

    l_x = (x_shifted_end_positions - x_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, l_x)

    return result


def compute_l_y(bunch_configuration, madx_configuration):
    reference_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    theta_y_min = bunch_configuration.theta_y_min
    theta_y_max = bunch_configuration.theta_y_max
    delta = __get_delta(theta_y_min, theta_y_max)

    bunch_configuration.theta_y_min += delta
    bunch_configuration.theta_y_max += delta

    shifted_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    begin_positions, end_positions, shifted_end_positions = adjust_particles_numbers(reference_particles["start"],
                                                                                     end_positions,
                                                                                     shifted_end_positions)

    y_end_positions = __get_vector_of_transported_matrix("y", end_positions)
    y_shifted_end_positions = __get_vector_of_transported_matrix("y", shifted_end_positions)

    l_y = (y_shifted_end_positions - y_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, l_y)

    return result


def compute_d_x(bunch_configuration, madx_configuration):
    reference_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    pt_min = bunch_configuration.pt_min
    pt_max = bunch_configuration.pt_max
    delta = __get_delta(pt_min, pt_max)

    bunch_configuration.pt_min += delta
    bunch_configuration.pt_max += delta

    shifted_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    begin_positions, end_positions, shifted_end_positions = adjust_particles_numbers(reference_particles["start"],
                                                                                     end_positions,
                                                                                     shifted_end_positions)

    x_end_positions = __get_vector_of_transported_matrix("x", end_positions)
    x_shifted_end_positions = __get_vector_of_transported_matrix("x", shifted_end_positions)

    d_x = (x_shifted_end_positions - x_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, d_x)

    return result


def compute_d_y(bunch_configuration, madx_configuration):
    reference_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    pt_min = bunch_configuration.pt_min
    pt_max = bunch_configuration.pt_max
    delta = __get_delta(pt_min, pt_max)

    bunch_configuration.pt_min += delta
    bunch_configuration.pt_max += delta

    shifted_particles = ptg.generate_from_range(bunch_configuration, madx_configuration)

    end_positions = reference_particles["end"]
    shifted_end_positions = shifted_particles["end"]

    begin_positions, end_positions, shifted_end_positions = adjust_particles_numbers(reference_particles["start"],
                                                                                     end_positions,
                                                                                     shifted_end_positions)

    y_end_positions = __get_vector_of_transported_matrix("y", end_positions)
    y_shifted_end_positions = __get_vector_of_transported_matrix("y", shifted_end_positions)

    d_y = (y_shifted_end_positions - y_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, d_y)

    return result


def __get_delta(min, max):
    multiplier = 1e-4
    potential_delta = multiplier * (max - min)
    return potential_delta if potential_delta > 0 else multiplier


def __get_vector_of_transported_matrix(column_name, matrix):
    columns_mapping = {
        "x": 2,
        "theta x": 3,
        "y": 4,
        "theta y": 5,
        "pt": 7
    }
    index = columns_mapping[column_name]
    return matrix.T[index]


def process_input_matrix(matrix):
    mapping = {
        "x_in": __get_vector_of_transported_matrix("x", matrix),
        "theta_x_in": __get_vector_of_transported_matrix("theta x", matrix),
        "y_in": __get_vector_of_transported_matrix("y", matrix),
        "theta_y_in": __get_vector_of_transported_matrix("theta y", matrix),
        "pt_in": __get_vector_of_transported_matrix("pt", matrix),
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


def adjust_particles_numbers(begin_positions, end_positions, shifted_end_positions):
    first_indexes_set = set(end_positions.T[0].astype(int) - 1)
    second_indexes_set = set(shifted_end_positions.T[0].astype(int) - 1)
    intersection = first_indexes_set.intersection(second_indexes_set)
    begin_vector_indexes = np.array([x in intersection for x in begin_positions.T[0].astype(int)])
    begin_positions = begin_positions[begin_vector_indexes]
    end_vector_indexes = np.array([x in intersection for x in end_positions.T[0].astype(int)])
    end_positions = end_positions[end_vector_indexes]
    shifted_end_vector_indexes = np.array([x in intersection for x in shifted_end_positions.T[0].astype(int)])
    shifted_end_positions = shifted_end_positions[shifted_end_vector_indexes]
    return begin_positions, end_positions, shifted_end_positions
