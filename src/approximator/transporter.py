import approximator.runner as ra
from data.parameters_names import ParametersNames as Parameters
from data.particles import Particles


def transport(approximator, particles):
    """matrix in format returned by data.particles_generator functions"""

    segments = dict()

    segments["start"] = particles

    matrix_for_transporter = particles.get_coordinates_of(Parameters.X, Parameters.THETA_X, Parameters.Y,
                                                          Parameters.THETA_Y, Parameters.PT)

    transported_particles = ra.transport(approximator, matrix_for_transporter)
    segments["end"] = Particles(transported_particles, get_mapping())

    return segments


def get_mapping():
    mapping = {
        Parameters.X: 0,
        Parameters.THETA_X: 1,
        Parameters.Y: 2,
        Parameters.THETA_Y: 3,
        Parameters.PT: 4
    }
    return mapping


def get_transporter(approximator):
    def transporter(particles):
        return transport(approximator, particles)
    return transporter
