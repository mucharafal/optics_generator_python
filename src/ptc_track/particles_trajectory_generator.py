import data.particles_generator as pg
import ptc_track.runner as mr
import numpy as np
import ptc_track.matrix_indexes as ptc_track_indexes


def generate_random_particles(madx_configuration, bunch_configuration, target):
    """
    Generate dict with matrix of particles' parameters on stations. List of stations is in ptc_track configuration generator.
    Take angles into account.
    :param bunch_configuration: dict with beam parameters- x, theta x, y, theta y, t, and pt- their min and max values.
    :param madx_configuration: todo
    :param target: target number of parameters at end station.
    :return: dict with numpy matrix of particles' parameters on stations, matrix format:
    ordinal number, turn, x, theta x, y, theta y, t, pt, e, s, angle x, angle y
    """
    segments = {}
    counter = 0
    number_of_particles_in_one_run = bunch_configuration.get_number_of_particles()

    while ("end" not in segments.keys()) or ("end" in segments.keys() and len(segments["end"]) < target):
        new_particles = __generate_random_particles(madx_configuration, bunch_configuration)

        shift = counter * number_of_particles_in_one_run
        counter += 1
        new_particles = mr.shift_ordinal_number_in_segments(new_particles, shift)

        segments = mr.merge_segments(segments, new_particles)

    return segments


def __generate_random_particles(madx_configuration, bunch_configuration):
    """
    Generate dict with matrix of particles' parameters on stations. List of stations is in ptc_track configuration generator.
    :param bunch_configuration: dict with beam parameters- x, theta x, y, theta y, t, and pt- their min and max values.
    :param madx_configuration:
    :return: dict with numpy matrix of particles' parameters on stations, matrix format:
    ordinal number, turn, x, theta x, y, theta y, t, pt, e, s, angle x, angle y
    """
    particles = pg.generate_particles_randomly(bunch_configuration)

    segments = transport(madx_configuration, particles)

    return segments


def generate_from_range(madx_configuration, bunch_configuration):
    """
    Generate dict with matrices of particles' parameters on stations. List of stations is in ptc_track configuration generator.
    :param bunch_configuration: dict with beam parameters- x, theta x, y, theta y, t, and pt- their min and max values
    :param madx_configuration: todo
    :return: dict with numpy matrix of particles' parameters on stations, matrix format:
    ordinal number, turn, x, theta x, y, theta y, t, pt, e, s, angle x, angle y
    """

    particles = pg.generate_from_range(bunch_configuration)

    segments = transport(madx_configuration, particles)

    return segments


def transport(madx_configuration, particles):
    """
    Transport particles described in matrix. Coordinates of input must be canonical- they will be transformed to
    geometrical. Matrix format: x, theta x, y, theta y, pt
    :param particles:
    :param madx_configuration:
    :return: dict with matrices describing position of particles on stations, matrix format:
    ordinal number, turn, x, theta x, y, theta y, t, pt, e, s
    """
    number_of_processes = 4

    particles_with_t = np.insert(particles, 4, 0, axis=1)

    segments = mr.compute_trajectory(particles_with_t.T, madx_configuration, number_of_processes)

    return segments


def apply_configuration_to_transporter(configuration):
    return lambda x: transport(configuration, x)


def normalize_ptc_track_transporter_output(transporter):
    def normalize_matrix(ptc_track_output):
        columns_indexes = [ptc_track_indexes.ptc_track[column_name] for column_name in ["x", "theta x", "y", "theta y", "pt"]]
        return ptc_track_output.T[columns_indexes].T

    def normalized_transporter(particles):
        segments = transporter(particles)
        last_segment = segments["end"]
        return normalize_matrix(last_segment)

    return normalized_transporter






