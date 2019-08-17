import approximator.runner as ra
import data.particles_generator as pg
import ptc_track.runner as mr       # expand function from this file used here
import numpy as np


def generate_random_particles(approximator, bunch_configuration):
    """
    Generate dict with matrix of particles' parameters on stations. List of stations is in ptc_track configuration generator.
    :param approximator- LHCOpticsApproximator object
    :param bunch_configuration: dict with bunch parameters- x, theta x, y, theta y, t, and pt- their min and max values.
    :return: dict with numpy matrix of particles' parameters on begin and end, with columns: x, theta x, y, theta y, pt
    """

    particles = pg.generate_particles_randomly(bunch_configuration)

    segments = dict()

    segments["start"] = particles

    transported_particles = ra.transport(approximator, particles)
    segments["end"] = transported_particles

    return segments


def generate_from_range(approximator, bunch_configuration):
    """
    Generate dict with matrix of particles' parameters on begin and end. Begin positions are selected as specified in
    bunch configuration.
    :param approximator- LHCOpticsApproximator object
    :param bunch_configuration: dict with bunch parameters- x, theta x, y, theta y, t, and pt- their min and max values.
    :return: dict with numpy matrix of particles' parameters on begin and end, with columns: x, theta x, y, theta y, pt
    """

    particles = pg.generate_from_range(bunch_configuration)

    segments = dict()

    segments["start"] = particles

    transported_particles = ra.transport(approximator, particles)
    segments["end"] = transported_particles

    return segments
