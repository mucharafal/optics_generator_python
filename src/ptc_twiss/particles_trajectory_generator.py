import ptc_twiss.runner as tr
import data.particles_generator as pg
import numpy as np
import ptc_twiss.matrix_indexes as indexes


def generate_from_range(madx_configuration, bunch_configuration):
    """
    Generate map with matrices:
    "start"- begining position of particles (x, theta x, y, theta y, pt)
    "end"- all parameters returned by twiss + pt
    Positions of particles are as specified in grid
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object, grid of particles specification
    :return: map with two matrices
    """
    dataset = pg.generate_from_range(bunch_configuration)
    transported = tr.transport(madx_configuration, dataset)
    segments = dict()
    segments["start"] = transported[np.isclose(transported.T[indexes.ptc_twiss["s"]], 0)]
    if madx_configuration.s != -1:
        filtered_matrix = transported[np.isclose(transported.T[indexes.ptc_twiss["s"]], madx_configuration.s)]
        segments["end"] = filtered_matrix
        return segments
    else:
        segments["end"] = transported
        return segments


def generate_random_particles(madx_configuration, bunch_configuration):
    """
    Generate map with matrices:
    "start"- begining position of particles (x, theta x, y, theta y, pt)
    "end"- all parameters returned by twiss + pt
    Positions of particles are chosen randomly within boundaries specified in configuration
    :param madx_configuration: TwissConfiguration object
    :param bunch_configuration: BunchConfiguration object, grid of particles specification
    :return: map with two matrices
    """
    dataset = pg.generate_particles_randomly(bunch_configuration)
    transported = tr.transport(madx_configuration, dataset)
    segments = dict()
    segments["start"] = transported[np.isclose(transported.T[indexes.ptc_twiss["s"]], 0)]
    if madx_configuration.s != -1:
        filtered_matrix = transported[np.isclose(transported.T[indexes.ptc_twiss["s"]], madx_configuration.s)]
        segments["end"] = filtered_matrix
        return segments
    else:
        segments["end"] = transported
        return segments
