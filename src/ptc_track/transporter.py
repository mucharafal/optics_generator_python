import ptc_track.runner as mr
from data.parameters_names import ParametersNames as Parameters


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

    particles_with_t = particles.add_zeros_column(Parameters.T)

    segments = mr.compute_trajectory(particles_with_t, madx_configuration, number_of_processes)

    return segments


def apply_configuration_to_transporter(configuration):
    return lambda x: transport(configuration, x)


def get_transporter(configuration):
    return apply_configuration_to_transporter(configuration)





