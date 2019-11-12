import transporters.ptc_twiss.runner as tr
import numpy as np
import transporters.ptc_twiss.matrix_indexes as indexes
from data.parameters_names import ParametersNames as Parameters
from data.particles import CanonicalCoordinates


def transport(madx_configuration, particles):
    raw_begin_positions = particles.get_canonical_coordinates_of(Parameters.X, Parameters.THETA_X, Parameters.Y,
                                                                 Parameters.THETA_Y, Parameters.PT)
    transported = tr.transport(madx_configuration.transport_configuration, raw_begin_positions)
    segments = dict()
    start_segments_matrix = transported[np.isclose(transported.T[indexes.ptc_twiss[Parameters.S]], 0)]
    segments["start"] = CanonicalCoordinates(start_segments_matrix, get_mapping())
    if madx_configuration.filter_by_s:
        filtered_matrix = transported[np.isclose(transported.T[indexes.ptc_twiss[Parameters.S]], madx_configuration.s)]
        segments["end"] = CanonicalCoordinates(filtered_matrix, get_mapping())
        return segments
    else:
        segments["end"] = CanonicalCoordinates(transported, get_mapping())
        return segments


def get_mapping():
    return indexes.ptc_twiss


def get_transporter(configuration):
    return lambda particles: transport(configuration, particles)
