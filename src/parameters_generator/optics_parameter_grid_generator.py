import data.particles_trajectory_generator as ptg
import numpy as np


def compute_l_y(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                t_min, t_max, number_of_t_values,
                pt_min, pt_max, number_of_pt_values,
                path_to_configuration, delta_theta_multiplier=0.000001):
    delta_theta = (theta_y_max - theta_y_min) * delta_theta_multiplier
    delta_theta = delta_theta if delta_theta != 0 else delta_theta_multiplier
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                                       pt_min, pt_max, number_of_pt_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min + delta_theta, theta_y_max + delta_theta, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                                       pt_min, pt_max, number_of_pt_values,
                                       path_to_configuration)
    difference = (particles2["y_out"] - particles1["y_out"])
    l_y = difference / delta_theta
    result_matrix = concatenate_result_with_input(particles1, l_y)
    return result_matrix


def compute_l_x(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                t_min, t_max, number_of_t_values,
                pt_min, pt_max, number_of_pt_values,
                path_to_configuration, delta_theta_multiplier=0.000001):
    delta_theta = (theta_x_max - theta_x_min) * delta_theta_multiplier
    delta_theta = delta_theta if delta_theta != 0 else delta_theta_multiplier
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                pt_min, pt_max, number_of_pt_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min + delta_theta, theta_x_max + delta_theta, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                pt_min, pt_max, number_of_pt_values,
                                       path_to_configuration)
    difference = (particles2["x_out"] - particles1["x_out"])
    l_x = difference / delta_theta
    result_matrix = concatenate_result_with_input(particles1, l_x)
    return result_matrix


def compute_v_y(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                t_min, t_max, number_of_t_values,
                pt_min, pt_max, number_of_pt_values,
                path_to_configuration, delta_y_multiplier=0.000001):
    delta_y = (y_max - y_min) * delta_y_multiplier
    delta_y = delta_y if delta_y != 0 else delta_y_multiplier
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                                       pt_min, pt_max, number_of_pt_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min + delta_y, y_max + delta_y, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                                       pt_min, pt_max, number_of_pt_values,
                                       path_to_configuration)
    difference = (particles2["y_out"] - particles1["y_out"])
    v_y = difference / delta_y
    result_matrix = concatenate_result_with_input(particles1, v_y)
    return result_matrix


def compute_v_x(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                t_min, t_max, number_of_t_values,
                pt_min, pt_max, number_of_pt_values,
                path_to_configuration, delta_x_multiplier=0.000001):
    delta_x = (x_max - x_min) * delta_x_multiplier
    delta_x = delta_x if delta_x != 0 else delta_x_multiplier
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                                       pt_min, pt_max, number_of_pt_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min + delta_x, x_max + delta_x, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                                       pt_min, pt_max, number_of_pt_values,
                                       path_to_configuration)
    difference = (particles2["x_out"] - particles1["x_out"])
    v_x = difference / delta_x
    result_matrix = concatenate_result_with_input(particles1, v_x)
    return result_matrix


def compute_d_y(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                t_min, t_max, number_of_t_values,
                pt_min, pt_max, number_of_pt_values,
                path_to_configuration, delta_pt_multiplier=0.000001):
    delta_pt = (pt_max - pt_min) * delta_pt_multiplier
    delta_pt = delta_pt if delta_pt > 0 else delta_pt_multiplier
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                                       pt_min, pt_max, number_of_pt_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                                       pt_min + delta_pt, pt_max + delta_pt, number_of_pt_values,
                                       path_to_configuration)
    difference = (particles2["y_out"] - particles1["y_out"])
    d_y = difference / delta_pt
    result_matrix = concatenate_result_with_input(particles1, d_y)
    return result_matrix


def compute_d_x(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                t_min, t_max, number_of_t_values,
                pt_min, pt_max, number_of_pt_values,
                path_to_configuration, delta_pt_multiplier=0.000001):
    delta_pt = (pt_max - pt_min) * delta_pt_multiplier
    delta_pt = delta_pt if delta_pt > 0 else delta_pt_multiplier
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                                       pt_min, pt_max, number_of_pt_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       t_min, t_max, number_of_t_values,
                                       pt_min + delta_pt, pt_max + delta_pt, number_of_pt_values,
                                       path_to_configuration)

    print("End, parameter calc")
    print(particles1["x_out"].shape)

    difference = (particles2["x_out"] - particles1["x_out"])
    d_x = difference / delta_pt
    result_matrix = concatenate_result_with_input(particles1, d_x)
    return result_matrix


def get_grid_of_particles(x_min, x_max, number_of_x_values,
                          theta_x_min, theta_x_max, number_of_theta_x_values,
                          y_min, y_max, number_of_y_values,
                          theta_y_min, theta_y_max, number_of_theta_y_values,
                          t_min, t_max, number_of_t_values,
                          pt_min, pt_max, number_of_pt_values,
                          path_to_configuration):
    """
    Generate grid of particles with calculated position before and after passing optics.
    :param x_min:
    :param x_max:
    :param number_of_x_values:
    :param theta_x_min:
    :param theta_x_max:
    :param number_of_theta_x_values:
    :param y_min:
    :param y_max:
    :param number_of_y_values:
    :param theta_y_min:
    :param theta_y_max:
    :param number_of_theta_y_values:
    :param t_min:
    :param t_max:
    :param number_of_t_values:
    :param pt_min:
    :param pt_max:
    :param number_of_pt_values:
    :param path_to_configuration:
    :return: dict where key is name of parameter and value column matrix
    """

    beam_configuration = dict()
    beam_configuration["x_min"] = x_min
    beam_configuration["x_max"] = x_max
    beam_configuration["theta_x_min"] = theta_x_min
    beam_configuration["theta_x_max"] = theta_x_max
    beam_configuration["y_min"] = y_min
    beam_configuration["y_max"] = y_max
    beam_configuration["theta_y_min"] = theta_y_min
    beam_configuration["theta_y_max"] = theta_y_max
    beam_configuration["t_min"] = t_min
    beam_configuration["t_max"] = t_max
    beam_configuration["pt_min"] = pt_min
    beam_configuration["pt_max"] = pt_max

    number_of_particles = dict()
    number_of_particles["x"] = number_of_x_values
    number_of_particles["theta_x"] = number_of_theta_x_values
    number_of_particles["y"] = number_of_y_values
    number_of_particles["theta_y"] = number_of_theta_y_values
    number_of_particles["t"] = number_of_t_values
    number_of_particles["pt"] = number_of_pt_values

    matrices = ptg.generate_grid_particles(beam_configuration, path_to_configuration, number_of_particles)

    end_matrix = matrices["end"]
    start_matrix_in_madx_format = matrices["start"]
    custom_start_matrix = start_matrix_in_madx_format.T[2:8].T
    indexes = end_matrix.T[0].astype(int) - 1
    custom_start_matrix = custom_start_matrix[indexes]

    merged_matrix = np.append(end_matrix, custom_start_matrix, axis=1)

    return process_matrix(merged_matrix)


def process_matrix(matrix):
    rows = matrix.T
    mapping = {
        "number": rows[0],
        "turn": rows[1],
        "x_out": rows[2],
        "theta_x_out": rows[3],
        "y_out": rows[4],
        "theta_y_out": rows[5],
        "t_out": rows[6],
        "pt_out": rows[7],
        "s_out": rows[8],
        "e_out": rows[9],
        "x_in": rows[10],
        "theta_x_in": rows[11],
        "y_in": rows[12],
        "theta_y_in": rows[13],
        "t_in": rows[14],
        "pt_in": rows[15]
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
