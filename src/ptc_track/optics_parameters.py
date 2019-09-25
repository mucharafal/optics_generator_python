from data.parameters_names import ParametersNames as Parameters
import ptc_track.transporter as ptg
import data.particles_generator as pg
import numpy as np
import utils.differential_quotient as optical_function_as_differential


def compute_v_x(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, Parameters.X, Parameters.X, 1e-5)

    return particles_with_optical_function


def compute_v_y(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, Parameters.Y, Parameters.Y, 1e-5)

    return particles_with_optical_function


def compute_l_x(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, Parameters.THETA_X, Parameters.X, 1e-5)

    return particles_with_optical_function


def compute_l_y(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, Parameters.THETA_Y, Parameters.Y, 1e-5)

    return particles_with_optical_function


def compute_d_x(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, Parameters.PT, Parameters.X, 1e-5)

    return particles_with_optical_function


def compute_d_y(madx_configuration, grid_configuration):
    particles_with_optical_function = compute_optical_function(madx_configuration, grid_configuration, Parameters.PT, Parameters.Y, 1e-5)
    return particles_with_optical_function


def compute_optical_function(madx_configuration, grid_configuration, delta_parameter_name, transported_parameter_name, 
                             delta_alternative_value):
    particles = pg.generate_from_range(grid_configuration)

    if madx_configuration.coordinates == "geometrical":
        particles = transform_to_geometrical_coordinates(particles)

    transporter = ptg.apply_configuration_to_transporter(madx_configuration)
    normalized_transporter = ptg.normalize_ptc_track_transporter_output(transporter)

    particles_with_optical_function = optical_function_as_differential.\
        compute_optical_function(normalized_transporter, particles,
                                 delta_parameter_name, transported_parameter_name, delta_alternative_value)

    return particles_with_optical_function


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
