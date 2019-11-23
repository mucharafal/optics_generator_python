import transporters.madx.ptc_track.runner as mr
from data.parameters_names import ParametersNames as Parameters
from data.particles import CanonicalCoordinates


def transport(madx_configuration, particles):
    """
    Transport particles described in matrix. Coordinates of input must be canonical- they will be transformed to
    geometrical. Matrix format: x, theta x, y, theta y, pt
    :param particles:
    :param madx_configuration:
    :return: dict with matrices describing position of particles on stations
    """
    number_of_processes = 4

    particles_with_t = particles.add_zeros_column(Parameters.T)

    raw_begin_positions = particles_with_t.get_canonical_coordinates_of(Parameters.X, Parameters.THETA_X, Parameters.Y,
                                                                        Parameters.THETA_Y, Parameters.T, Parameters.PT)

    raw_segments = mr.compute_trajectory(raw_begin_positions, madx_configuration, number_of_processes)

    segments = {segment_name: CanonicalCoordinates(segment, get_mapping()) for segment_name, segment in raw_segments.items()}

    return segments


def apply_configuration_to_transporter(configuration):
    return lambda x: transport(configuration, x)


def get_transporter(configuration):
    return apply_configuration_to_transporter(configuration)


def get_mapping():
    ptc_track = {
        "number": 0,
        Parameters.TURN: 1,
        Parameters.X: 2,
        Parameters.THETA_X: 3,
        Parameters.Y: 4,
        Parameters.THETA_Y: 5,
        Parameters.T: 6,
        Parameters.PT: 7,
        Parameters.S: 8,
        Parameters.E: 9
    }
    return ptc_track





