import madx_runner as mr
import particles_generator as pg
import os
import shutil
import optics_parameter_generator as opg
import numpy as np


def compute_l_y(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                ksi_min, ksi_max, number_of_ksi_values,
                path_to_configuration, delta_theta=0.000001):
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min, ksi_max, number_of_ksi_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min + delta_theta, theta_y_max + delta_theta, number_of_theta_y_values,
                                       ksi_min, ksi_max, number_of_ksi_values,
                                       path_to_configuration)
    difference = (particles2["y_out"] - particles1["y_out"])
    l_y = difference / delta_theta
    result_matrix = concatenate_result_with_input(particles1, l_y)
    return result_matrix


def compute_l_x(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                ksi_min, ksi_max, number_of_ksi_values,
                path_to_configuration, delta_theta=0.000001):
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min, ksi_max, number_of_ksi_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min + delta_theta, theta_x_max + delta_theta, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min, ksi_max, number_of_ksi_values,
                                       path_to_configuration)
    difference = (particles2["x_out"] - particles1["x_out"])
    l_x = difference / delta_theta
    result_matrix = concatenate_result_with_input(particles1, l_x)
    return result_matrix


def compute_v_y(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                ksi_min, ksi_max, number_of_ksi_values,
                path_to_configuration, delta_y=0.000001):
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min, ksi_max, number_of_ksi_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min + delta_y, y_max + delta_y, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min, ksi_max, number_of_ksi_values,
                                       path_to_configuration)
    difference = (particles2["y_out"] - particles1["y_out"])
    v_y = difference / delta_y
    result_matrix = concatenate_result_with_input(particles1, v_y)
    return result_matrix


def compute_v_x(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                ksi_min, ksi_max, number_of_ksi_values,
                path_to_configuration, delta_x=0.000001):
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min, ksi_max, number_of_ksi_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min + delta_x, x_max + delta_x, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min, ksi_max, number_of_ksi_values,
                                       path_to_configuration)
    difference = (particles2["x_out"] - particles1["x_out"])
    v_x = difference / delta_x
    result_matrix = concatenate_result_with_input(particles1, v_x)
    return result_matrix


def compute_d_y(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                ksi_min, ksi_max, number_of_ksi_values,
                path_to_configuration, delta_ksi=0.000001):
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min, ksi_max, number_of_ksi_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min + delta_ksi, ksi_max + delta_ksi, number_of_ksi_values,
                                       path_to_configuration)
    difference = (particles2["y_out"] - particles1["y_out"])
    d_y = difference / delta_ksi
    result_matrix = concatenate_result_with_input(particles1, d_y)
    return result_matrix


def compute_d_x(x_min, x_max, number_of_x_values,
                theta_x_min, theta_x_max, number_of_theta_x_values,
                y_min, y_max, number_of_y_values,
                theta_y_min, theta_y_max, number_of_theta_y_values,
                ksi_min, ksi_max, number_of_ksi_values,
                path_to_configuration, delta_ksi=0.000001):
    particles1 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min, ksi_max, number_of_ksi_values,
                                       path_to_configuration)
    particles2 = get_grid_of_particles(x_min, x_max, number_of_x_values,
                                       theta_x_min, theta_x_max, number_of_theta_x_values,
                                       y_min, y_max, number_of_y_values,
                                       theta_y_min, theta_y_max, number_of_theta_y_values,
                                       ksi_min + delta_ksi, ksi_max + delta_ksi, number_of_ksi_values,
                                       path_to_configuration)
    difference = (particles2["x_out"] - particles1["x_out"])
    d_x = difference / delta_ksi
    result_matrix = concatenate_result_with_input(particles1, d_x)
    return result_matrix


def get_grid_of_particles(x_min, x_max, number_of_x_values,
                          theta_x_min, theta_x_max, number_of_theta_x_values,
                          y_min, y_max, number_of_y_values,
                          theta_y_min, theta_y_max, number_of_theta_y_values,
                          ksi_min, ksi_max, number_of_ksi_values,
                          path_to_configuration):
    bunch_size = number_of_x_values * number_of_theta_x_values * number_of_y_values * number_of_theta_y_values \
                 * number_of_ksi_values

    current_path = os.getcwd()
    folder_name = "kali1234"

    os.mkdir(folder_name)
    os.chdir(folder_name)

    # Every ksi value need to be run with new configuration file
    ksi_vector = np.linspace(ksi_min, ksi_max, number_of_ksi_values)
    input_matrix = np.empty(shape=(0, 7))
    trajectory_matrix = np.empty(shape=(0, 10))
    counter = 0
    for ksi in ksi_vector:

        name_of_configuration_file = opg.create_madx_configuration_file(path_to_configuration, ksi, bunch_size)

        generated_matrix = pg.generate_from_range(x_min, x_max, number_of_x_values,
                                                  theta_x_min, theta_x_max, number_of_theta_x_values,
                                                  y_min, y_max, number_of_y_values,
                                                  theta_y_min, theta_y_max, number_of_theta_y_values,
                                                  0, 0, 1,
                                                  0, 0, 1)
        vector_with_ksi_to_append = np.empty(shape=(generated_matrix.shape[0], 1))
        vector_with_ksi_to_append.fill(ksi)
        supplied_input_matrix = np.append(generated_matrix, vector_with_ksi_to_append, axis=1)

        input_matrix = np.append(input_matrix, supplied_input_matrix, axis=0)

        mr.run_madx(name_of_configuration_file)
        segments = mr.read_in_madx_output_file("trackone")

        if "end" in segments.keys():
            matrix = segments["end"]
            shift = counter * bunch_size
            vector_with_shift = np.empty(shape=(matrix.shape[0]))
            vector_with_shift.fill(shift)
            matrix.T[0] += vector_with_shift
            trajectory_matrix = np.append(trajectory_matrix, matrix, axis=0)

    os.chdir(current_path)
    shutil.rmtree(folder_name)

    output_matrix = np.empty(shape=(0, 17))

    for row in trajectory_matrix:
        index = int(row[0])-1
        input_row = input_matrix[index]
        new_row = np.append(row, input_row).reshape((1, 17))
        output_matrix = np.append(output_matrix, new_row, axis=0)

    return process_matrix(output_matrix)


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
        "pt_in": rows[15],
        "ksi_in": rows[16]
    }
    return mapping


def concatenate_result_with_input(matrix, result):
    result_matrix = matrix["x_in"].reshape((-1, 1))
    result_matrix = np.append(result_matrix, matrix["theta_x_in"].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, matrix["y_in"].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, matrix["theta_y_in"].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, matrix["ksi_in"].reshape((-1, 1)), axis=1)
    result_matrix = np.append(result_matrix, result.reshape((-1, 1)), axis=1)
    return result_matrix
