from unittest import TestCase
from madx import particles_trajectory_generator
from data.bunch_configuration import BunchConfiguration
import mock
import numpy as np
from data import bunch_configuration


def mock_particles_generator(beam_configuration):
    if type(beam_configuration) is not bunch_configuration.BunchConfiguration:
        raise ValueError
    return np.random.rand(10, beam_configuration.get_number_of_particles())


def mock_transport(particles, path):
    segments = dict()
    number_of_particles = particles.shape[0]
    ordinal_vector = np.array([x for x in range(1, number_of_particles + 1)])
    turn_vector = np.array([1 for _ in range(number_of_particles)])
    position_matrix = particles.T[:4].T
    t_vector = np.array([0 for _ in range(number_of_particles)])
    pt_vector = particles.T[4]
    s_vector = np.array([212.55 for _ in range(number_of_particles)])
    energy_vector = np.array([6.5 for _ in range(number_of_particles)])
    end_matrix = ordinal_vector.reshape((-1, 1))
    end_matrix = np.append(end_matrix, turn_vector.reshape((-1, 1)), axis=1)
    end_matrix = np.append(end_matrix, position_matrix, axis=1)
    end_matrix = np.append(end_matrix, t_vector.reshape((-1, 1)), axis=1)
    end_matrix = np.append(end_matrix, pt_vector.reshape((-1, 1)), axis=1)
    end_matrix = np.append(end_matrix, s_vector.reshape((-1, 1)), axis=1)
    end_matrix = np.append(end_matrix, energy_vector.reshape((-1, 1)), axis=1)
    segments["start"] = end_matrix
    segments["end"] = end_matrix
    return segments


class Test__generate_random_particles(TestCase):

    @staticmethod
    def get_configuration_for_x_test():
        return BunchConfiguration(0, 1, 10, 0, 0, 1,
                                  0, 0, 1, 0, 0, 1,
                                  0, 0, 1)

    @mock.patch('data.particles_generator.generate_from_range', side_effect=mock_particles_generator)
    @mock.patch('madx.particles_trajectory_generator.__transport', side_effect=mock_transport)
    def test_simple_run(self, mock1, mock2):
        configuration = self.get_configuration_for_x_test()
        segments = particles_trajectory_generator.generate_random_particles(configuration, "some_path", 100)
        if segments["start"].shape != (100, 10):
            self.fail("Incorrect size of returned matrix")
        if segments["end"].shape != (100, 10):
            self.fail("Incorrect size of returned matrix")


class Test__generate_grid_particles(TestCase):

    @staticmethod
    def get_configuration_for_x_test():
        return BunchConfiguration(0, 1, 10, 0, 0, 1,
                                  0, 0, 1, 0, 0, 1,
                                  0, 0, 1)

    @mock.patch('data.particles_generator.generate_from_range', side_effect=mock_particles_generator)
    @mock.patch('madx.particles_trajectory_generator.__transport', side_effect=mock_transport)
    def test_simple_run(self, mock1, mock2):
        configuration = self.get_configuration_for_x_test()
        segments = particles_trajectory_generator.generate_from_range(configuration, "some_path")
        if segments["start"].shape != (10, 10):
            self.fail("Incorrect size of returned matrix: " + str(segments["start"].shape))
        if segments["end"].shape != (10, 10):
            self.fail("Incorrect size of returned matrix")
