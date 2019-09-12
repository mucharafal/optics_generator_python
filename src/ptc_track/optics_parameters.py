import ptc_track.particles_trajectory_generator as ptg
import data.particles_generator as pg
import numpy as np
import ptc_track.matrix_indexes as ptc_track_indexes
import utils.differential_quotient as optical_function_as_differential


def apply_configuration_to_transporter(configuration):
    return lambda x: ptg.transport(configuration, x)


def normalize_ptc_track_transporter_output(transporter):
    def normalize_matrix(ptc_track_output):
        columns_indexes = [ptc_track_indexes.ptc_track[column_name] for column_name in ["x", "theta x", "y", "theta y", "pt"]]
        return ptc_track_output.T[columns_indexes].T

    def normalized_transporter(particles):
        segments = transporter(particles)
        last_segment = segments["end"]
        return normalize_matrix(last_segment)

    return normalized_transporter


def compute_v_x(madx_configuration, grid_configuration):
    particles = pg.generate_from_range(grid_configuration)

    transporter = apply_configuration_to_transporter(madx_configuration)
    normalized_transporter = normalize_ptc_track_transporter_output(transporter)

    particles_with_optical_function = optical_function_as_differential.compute_optical_function(normalized_transporter,
                                                                                                particles,
                                                                                                "x", "x", 1e-5)

    return particles_with_optical_function


def compute_v_y(madx_configuration, grid_configuration):
    particles = pg.generate_from_range(grid_configuration)

    transporter = apply_configuration_to_transporter(madx_configuration)
    normalized_transporter = normalize_ptc_track_transporter_output(transporter)

    particles_with_optical_function = optical_function_as_differential.compute_optical_function(normalized_transporter,
                                                                                                particles,
                                                                                                "y", "y", 1e-5)

    return particles_with_optical_function


def compute_l_x(madx_configuration, grid_configuration):
    particles = pg.generate_from_range(grid_configuration)

    transporter = apply_configuration_to_transporter(madx_configuration)
    normalized_transporter = normalize_ptc_track_transporter_output(transporter)

    particles_with_optical_function = optical_function_as_differential.compute_optical_function(normalized_transporter,
                                                                                                particles,
                                                                                                "theta x", "x", 1e-5)

    return particles_with_optical_function


def compute_l_y(madx_configuration, grid_configuration):
    particles = pg.generate_from_range(grid_configuration)

    transporter = apply_configuration_to_transporter(madx_configuration)
    normalized_transporter = normalize_ptc_track_transporter_output(transporter)

    particles_with_optical_function = optical_function_as_differential.compute_optical_function(normalized_transporter,
                                                                                                particles,
                                                                                                "theta y", "y", 1e-5)

    return particles_with_optical_function


def compute_d_x(madx_configuration, grid_configuration):
    particles = pg.generate_from_range(grid_configuration)

    transporter = apply_configuration_to_transporter(madx_configuration)
    normalized_transporter = normalize_ptc_track_transporter_output(transporter)

    particles_with_optical_function = optical_function_as_differential.compute_optical_function(normalized_transporter,
                                                                                                particles,
                                                                                                "pt", "x", 1e-5)

    return particles_with_optical_function


def transform_to_geometrical_coordinates(particles):
    new_particles = np.copy(particles)
    new_particles.T[1] /= 1 + new_particles.T[4]
    new_particles.T[3] /= 1 + new_particles.T[4]
    return new_particles


def compute_d_y(madx_configuration, grid_configuration):
    particles = pg.generate_from_range(grid_configuration)

    transporter = apply_configuration_to_transporter(madx_configuration)
    normalized_transporter = normalize_ptc_track_transporter_output(transporter)

    particles_with_optical_function = optical_function_as_differential.compute_optical_function(normalized_transporter,
                                                                                                particles,
                                                                                                "pt", "y", 1e-5)

    return particles_with_optical_function


def __merge_stations(stations):
    merged_stations = np.empty((0, stations["start"].shape[1]))
    for station in stations:
        if station == "end":
            print(stations[station].T[8][0])
        merged_stations = np.append(merged_stations, stations[station], axis=0)
    return merged_stations


def __get_delta(min, max):
    multiplier = 1e-5
    potential_delta = multiplier * (max - min)
    return potential_delta if potential_delta > 0 else multiplier


def __get_vector_of_transported_matrix(column_name, matrix):
    columns_mapping = {
        "s": 8,
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
    first_indexes_set = set(end_positions.T[0].astype(int))
    second_indexes_set = set(shifted_end_positions.T[0].astype(int))
    intersection = first_indexes_set.intersection(second_indexes_set)
    begin_vector_indexes = np.array([x for x in begin_positions.T[0].astype(int) if x in intersection]) - 1
    begin_positions = begin_positions[begin_vector_indexes]
    end_vector_indexes = np.array([x for x in end_positions.T[0].astype(int) if x in intersection]) - 1
    end_positions = end_positions[end_vector_indexes]
    shifted_end_vector_indexes = np.array([x for x in shifted_end_positions.T[0].astype(int) if x in intersection]) - 1
    shifted_end_positions = shifted_end_positions[shifted_end_vector_indexes]
    return begin_positions, end_positions, shifted_end_positions
