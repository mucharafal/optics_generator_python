import ptc_track.particles_trajectory_generator as ptg
import numpy as np
import copy


def compute_v_x(madx_configuration, bunch_configuration):
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

    x_min = internal_bunch_configuration.x_min
    x_max = internal_bunch_configuration.x_max
    delta = __get_delta(x_min, x_max)

    internal_bunch_configuration.x_min += delta
    internal_bunch_configuration.x_max += delta

    shifted_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

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


def compute_v_y(madx_configuration, bunch_configuration):
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

    y_min = internal_bunch_configuration.y_min
    y_max = internal_bunch_configuration.y_max
    delta = __get_delta(y_min, y_max)

    internal_bunch_configuration.y_min += delta
    internal_bunch_configuration.y_max += delta

    shifted_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

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


def compute_l_x(madx_configuration, bunch_configuration):
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

    theta_x_min = internal_bunch_configuration.theta_x_min
    theta_x_max = internal_bunch_configuration.theta_x_max
    delta = __get_delta(theta_x_min, theta_x_max)

    internal_bunch_configuration.theta_x_min += delta
    internal_bunch_configuration.theta_x_max += delta

    shifted_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

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


def compute_l_y(madx_configuration, bunch_configuration):
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

    theta_y_min = internal_bunch_configuration.theta_y_min
    theta_y_max = internal_bunch_configuration.theta_y_max
    delta = __get_delta(theta_y_min, theta_y_max)

    internal_bunch_configuration.theta_y_min += delta
    internal_bunch_configuration.theta_y_max += delta

    shifted_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

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


def compute_d_x(madx_configuration, bunch_configuration):
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

    pt_min = internal_bunch_configuration.pt_min
    pt_max = internal_bunch_configuration.pt_max
    delta = __get_delta(pt_min, pt_max)

    internal_bunch_configuration.pt_min += delta
    internal_bunch_configuration.pt_max += delta

    shifted_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

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


def compute_d_y(madx_configuration, bunch_configuration):
    internal_bunch_configuration = copy.copy(bunch_configuration)
    reference_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

    pt_min = internal_bunch_configuration.pt_min
    pt_max = internal_bunch_configuration.pt_max
    delta = __get_delta(pt_min, pt_max)

    internal_bunch_configuration.pt_min += delta
    internal_bunch_configuration.pt_max += delta

    shifted_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

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


def compute_d_x_vs_s(madx_configuration, bunch_configuration):
    number_of_stations = madx_configuration.item_number     # todo change it!!! this is indirect passing number of stations
    merged_stations = np.empty((0, 10))
    shifted_positions_merged_station = np.empty((0, 10))
    for i in range(number_of_stations):
        madx_configuration.item_number = i
        internal_bunch_configuration = copy.copy(bunch_configuration)

        internal_bunch_configuration.number_of_x_values = 1
        internal_bunch_configuration.number_of_theta_x_values = 1
        internal_bunch_configuration.number_of_y_values = 1
        internal_bunch_configuration.number_of_theta_y_values = 1
        internal_bunch_configuration.number_of_pt_values = 1

        reference_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

        pt_min = internal_bunch_configuration.pt_min
        pt_max = internal_bunch_configuration.pt_max
        delta = __get_delta(pt_min, pt_max)

        internal_bunch_configuration.pt_min += delta
        internal_bunch_configuration.pt_max += delta

        shifted_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

        end_positions = __merge_stations(reference_particles)
        shifted_end_positions = __merge_stations(shifted_particles)

        merged_stations = np.append(merged_stations, end_positions, axis=0)
        shifted_positions_merged_station = np.append(shifted_positions_merged_station, shifted_end_positions, axis=0)

    x_end_positions = __get_vector_of_transported_matrix("x", merged_stations)
    x_shifted_end_positions = __get_vector_of_transported_matrix("x", shifted_positions_merged_station)

    d_x = (x_shifted_end_positions - x_end_positions) / delta

    result = np.append(__get_vector_of_transported_matrix("s", merged_stations).reshape((-1, 1)), d_x.reshape((-1, 1)), axis=1)

    return result


def compute_d_y_vs_s(madx_configuration, bunch_configuration):
    number_of_stations = madx_configuration.item_number  # todo change it!!! this is indirect passing number of stations
    merged_stations = np.empty((0, 10))
    shifted_positions_merged_station = np.empty((0, 10))
    for i in range(number_of_stations):
        madx_configuration.item_number = i
        internal_bunch_configuration = copy.copy(bunch_configuration)

        internal_bunch_configuration.number_of_x_values = 1
        internal_bunch_configuration.number_of_theta_x_values = 1
        internal_bunch_configuration.number_of_y_values = 1
        internal_bunch_configuration.number_of_theta_y_values = 1
        internal_bunch_configuration.number_of_pt_values = 1

        reference_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

        pt_min = internal_bunch_configuration.pt_min
        pt_max = internal_bunch_configuration.pt_max
        delta = __get_delta(pt_min, pt_max)

        internal_bunch_configuration.pt_min += delta
        internal_bunch_configuration.pt_max += delta

        shifted_particles = ptg.generate_from_range(madx_configuration, internal_bunch_configuration)

        end_positions = __merge_stations(reference_particles)
        shifted_end_positions = __merge_stations(shifted_particles)

        merged_stations = np.append(merged_stations, end_positions, axis=0)
        shifted_positions_merged_station = np.append(shifted_positions_merged_station, shifted_end_positions, axis=0)

    y_end_positions = __get_vector_of_transported_matrix("y", merged_stations)
    y_shifted_end_positions = __get_vector_of_transported_matrix("y", shifted_positions_merged_station)

    d_y = (y_shifted_end_positions - y_end_positions) / delta

    result = np.append(__get_vector_of_transported_matrix("s", merged_stations).reshape((-1, 1)), d_y.reshape((-1, 1)), axis=1)

    return result


def __merge_stations(stations):
    merged_stations = np.empty((0, stations["start"].shape[1]))
    for station in stations:
        if station == "end":
            print(stations[station].T[8][0])
        merged_stations = np.append(merged_stations, stations[station], axis=0)
    return merged_stations


def __get_delta(min, max):
    multiplier = 1e-3
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
