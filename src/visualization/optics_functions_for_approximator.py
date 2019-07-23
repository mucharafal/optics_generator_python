import data.particles_generator as pg
import approximator.run_approximator as ra
import numpy as np


def compute_v_x(approximator,
                x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min, pt_max, number_of_pt_values):
    begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                                             theta_x_min, theta_x_max, number_of_theta_x_values,
                                             y_min, y_max, number_of_y_values,
                                             theta_y_min, theta_y_max, number_of_theta_y_values,
                                             pt_min, pt_max, number_of_pt_values,
                                             0, 0, 1)
    potential_delta = 0.000001 * (x_max - x_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x_min + delta, x_max + delta, number_of_x_values,
                                                     theta_x_min, theta_x_max, number_of_theta_x_values,
                                                     y_min, y_max, number_of_y_values,
                                                     theta_y_min, theta_y_max, number_of_theta_y_values,
                                                     pt_min, pt_max, number_of_pt_values,
                                                     0, 0, 1)
    end_positions = ra.transport(approximator, begin_positions)
    shifted_end_positions = ra.transport(approximator, shifted_begin_positions)

    x_end_positions = __get_vector_of_transported_matrix("x", end_positions)
    x_shifted_end_positions = __get_vector_of_transported_matrix("x", shifted_end_positions)

    v_x = (x_shifted_end_positions - x_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, v_x)

    return result


def compute_v_y(approximator,
                x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min, pt_max, number_of_pt_values):
    begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                                            theta_x_min, theta_x_max, number_of_theta_x_values,
                                            y_min, y_max, number_of_y_values,
                                            theta_y_min, theta_y_max, number_of_theta_y_values,
                                            pt_min, pt_max, number_of_pt_values,
                                             0, 0, 1)
    potential_delta = 0.000001 * (y_max - y_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                                                     theta_x_min, theta_x_max, number_of_theta_x_values,
                                                     y_min + delta, y_max + delta, number_of_y_values,
                                                     theta_y_min, theta_y_max, number_of_theta_y_values,
                                                     pt_min, pt_max, number_of_pt_values,
                                                     0, 0, 1)
    end_positions = ra.transport(approximator, begin_positions)
    shifted_end_positions = ra.transport(approximator, shifted_begin_positions)

    y_end_positions = __get_vector_of_transported_matrix("y", end_positions)
    y_shifted_end_positions = __get_vector_of_transported_matrix("y", shifted_end_positions)

    v_y = (y_shifted_end_positions - y_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, v_y)

    return result


def compute_l_y(approximator,
                x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min, pt_max, number_of_pt_values):
    begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                                            theta_x_min, theta_x_max, number_of_theta_x_values,
                                            y_min, y_max, number_of_y_values,
                                            theta_y_min, theta_y_max, number_of_theta_y_values,
                                            pt_min, pt_max, number_of_pt_values,
                                             0, 0, 1)
    potential_delta = 0.000001 * (theta_y_max - theta_y_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                                                     theta_x_min, theta_x_max, number_of_theta_x_values,
                                                     y_min, y_max, number_of_y_values,
                                                     theta_y_min + delta, theta_y_max + delta, number_of_theta_y_values,
                                                     pt_min, pt_max, number_of_pt_values,
                                                     0, 0, 1)
    end_positions = ra.transport(approximator, begin_positions)
    shifted_end_positions = ra.transport(approximator, shifted_begin_positions)

    y_end_positions = __get_vector_of_transported_matrix("y", end_positions)
    y_shifted_end_positions = __get_vector_of_transported_matrix("y", shifted_end_positions)

    l_y = (y_shifted_end_positions - y_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, l_y)

    return result


def compute_l_x(approximator,
                x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min, pt_max, number_of_pt_values):
    begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min, pt_max, number_of_pt_values,
                0, 0, 1)
    potential_delta = 0.000001 * (theta_x_max - theta_x_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                                                     theta_x_min + delta, theta_x_max + delta, number_of_theta_x_values,
                                                     y_min, y_max, number_of_y_values,
                                                     theta_y_min, theta_y_max, number_of_theta_y_values,
                                                     pt_min, pt_max, number_of_pt_values,
                                                     0, 0, 1)
    end_positions = ra.transport(approximator, begin_positions)
    shifted_end_positions = ra.transport(approximator, shifted_begin_positions)

    x_end_positions = __get_vector_of_transported_matrix("x", end_positions)
    x_shifted_end_positions = __get_vector_of_transported_matrix("x", shifted_end_positions)

    l_x = (x_shifted_end_positions - x_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, l_x)

    return result


def compute_d_x(approximator,
                x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min, pt_max, number_of_pt_values):
    begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min, pt_max, number_of_pt_values,
                                             0, 0, 1)
    potential_delta = 0.000001 * (pt_max - pt_min)
    delta = potential_delta if potential_delta > 0 else 0.000001
    shifted_begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min + delta, pt_max + delta, number_of_pt_values,
                                                     0, 0, 1)

    matrix_for_approximator = np.delete(begin_positions, 4, 1)
    end_positions = ra.transport(approximator, matrix_for_approximator)
    matrix_for_approximator = np.delete(shifted_begin_positions, 4, 1)
    shifted_end_positions = ra.transport(approximator, matrix_for_approximator)

    x_end_positions = __get_vector_of_transported_matrix("x", end_positions)
    x_shifted_end_positions = __get_vector_of_transported_matrix("x", shifted_end_positions)

    d_x = (x_shifted_end_positions - x_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, d_x)

    return result


def compute_d_y(approximator,
                x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min, pt_max, number_of_pt_values):
    begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min, pt_max, number_of_pt_values,
                                             0, 0, 1)
    potential_delta = 0.000001 * (pt_max - pt_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                pt_min + delta, pt_max + delta, number_of_pt_values,
                                                     0, 0, 1)
    matrix_for_approximator = np.delete(begin_positions, 4, 1)
    end_positions = ra.transport(approximator, matrix_for_approximator)
    matrix_for_approximator = np.delete(shifted_begin_positions, 4, 1)
    shifted_end_positions = ra.transport(approximator, matrix_for_approximator)

    y_end_positions = __get_vector_of_transported_matrix("y", end_positions)
    y_shifted_end_positions = __get_vector_of_transported_matrix("y", shifted_end_positions)

    d_y = (y_shifted_end_positions - y_end_positions) / delta

    begin_positions_vectors = process_input_matrix(begin_positions)
    result = concatenate_result_with_input(begin_positions_vectors, d_y)

    return result


def __get_vector_of_transported_matrix(column_name, matrix):
    columns_mapping = {
        "x": 0,
        "theta x": 1,
        "y": 2,
        "theta y": 3,
        "pt": 4
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

