import ptc_track.particles_trajectory_generator as ptg
import data.particles_generator as pg
import numpy as np
import ptc_track.matrix_indexes as ptc_track_indexes
import utils.differential_quotient as optical_function_as_differential


def compute_v_x(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, "x", "x", 1e-5)

    return particles_with_optical_function


def compute_v_y(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, "y", "y", 1e-5)

    return particles_with_optical_function


def compute_l_x(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, "theta x", "x", 1e-5)

    return particles_with_optical_function


def compute_l_y(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, "theta y", "y", 1e-5)

    return particles_with_optical_function


def compute_d_x(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, "pt", "x", 1e-5)

    return particles_with_optical_function


def compute_d_y(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, "pt", "y", 1e-5)
    return particles_with_optical_function


def compute_optical_function(madx_configuration, grid_configuration, delta_parameter_name, transported_parameter_name, 
                             delta_alternative_value):
    particles = pg.generate_from_range(grid_configuration)
    particles_in_geometrical_coordinates = transform_to_geometrical_coordinates(particles)
    transporter = apply_configuration_to_transporter(madx_configuration)
    normalized_transporter = normalize_ptc_track_transporter_output(transporter)

    particles_with_optical_function = optical_function_as_differential.\
        compute_optical_function(normalized_transporter, particles_in_geometrical_coordinates, 
                                 delta_parameter_name, transported_parameter_name, delta_alternative_value)

    return particles_with_optical_function


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


def transform_to_geometrical_coordinates(particles):
    new_particles = np.copy(particles)
    new_particles.T[1] /= 1 + new_particles.T[4]
    new_particles.T[3] /= 1 + new_particles.T[4]
    return new_particles


def __merge_stations(stations):
    merged_stations = np.empty((0, stations["start"].shape[1]))
    for station in stations:
        if station == "end":
            print(stations[station].T[8][0])
        merged_stations = np.append(merged_stations, stations[station], axis=0)
    return merged_stations
