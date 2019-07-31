import data.particles_generator as pg
import madx.runner as mr
import numpy as np


def generate_random_particles(bunch_configuration, madx_configuration, target):
    """
    Generate dict with matrix of particles' parameters on stations. List of stations is in madx configuration generator.
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
        new_particles = __generate_random_particles(bunch_configuration, madx_configuration)

        shift = counter * number_of_particles_in_one_run
        counter += 1
        new_particles = mr.shift_ordinal_number_in_segments(new_particles, shift)

        segments = mr.merge_segments(segments, new_particles)

    return segments


def __generate_random_particles(bunch_configuration, madx_configuration):
    """
    Generate dict with matrix of particles' parameters on stations. List of stations is in madx configuration generator.
    :param bunch_configuration: dict with beam parameters- x, theta x, y, theta y, t, and pt- their min and max values.
    :param madx_configuration:
    :return: dict with numpy matrix of particles' parameters on stations, matrix format:
    ordinal number, turn, x, theta x, y, theta y, t, pt, e, s, angle x, angle y
    """
    particles = pg.generate_particles_randomly(bunch_configuration)

    segments = __transport(particles, madx_configuration)

    return segments


def generate_from_range(bunch_configuration, madx_configuration):
    """
    Generate dict with matrices of particles' parameters on stations. List of stations is in madx configuration generator.
    :param bunch_configuration: dict with beam parameters- x, theta x, y, theta y, t, and pt- their min and max values
    :param madx_configuration: todo
    :return: dict with numpy matrix of particles' parameters on stations, matrix format:
    ordinal number, turn, x, theta x, y, theta y, t, pt, e, s, angle x, angle y
    """

    particles = pg.generate_from_range(bunch_configuration)

    segments = __transport(particles, madx_configuration)

    return segments


def __transport(particles, madx_configuration):
    """
    Transport particles described in matrix. Matrix format: x, theta x, y, theta y, pt
    :param particles:
    :param madx_configuration:
    :return: dict with matrices describing position of particles on stations, matrix format:
    ordinal number, turn, x, theta x, y, theta y, t, pt, e, s
    """
    number_of_processes = 1

    particles_with_t = np.insert(particles, 4, 0, axis=1)

    segments = mr.compute_trajectory(particles_with_t.T, madx_configuration, number_of_processes)
    return segments



