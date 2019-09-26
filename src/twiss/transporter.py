import twiss.runner as runner
from data.particles import Particles
from data.parameters_names import ParametersNames as Parameters
import twiss.matrix_indexes


def get_transporter(madx_configuration):
    def transporter(particles):
        raw_particles = particles.get_coordinates(Parameters.X, Parameters.THETA_X, Parameters.Y, Parameters.THETA_Y,
                                                  Parameters.PT)
        result_particles_object = Particles(runner.transport(madx_configuration, raw_particles), get_mapping())
        return result_particles_object
    return transporter


def get_mapping():
    return twiss.matrix_indexes.twiss
