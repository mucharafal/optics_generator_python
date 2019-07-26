from unittest import TestCase
import madx.optics_parameters as op
import mock
import numpy as np
from data import bunch_configuration
import tests.visualization.test_optics_parameter_visualisation as prev_test


def mock_particles_generator(beam_configuration):
    if type(beam_configuration) is not bunch_configuration.BunchConfiguration:
        raise ValueError
    return np.random.rand(5, beam_configuration.get_number_of_particles())


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


counter = 0


def transport_with_loose(particles, path):
    global counter
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
    end_matrix = np.delete(end_matrix, counter, 0)
    counter += 1
    counter %= number_of_particles
    segments["end"] = end_matrix
    return segments


class TestCompute_optics_parameters(TestCase):

    optical_functions = [op.compute_v_x, op.compute_v_y, op.compute_d_x, op.compute_d_y, op.compute_l_x,
                         op.compute_l_y]

    @mock.patch('data.particles_generator.generate_from_range', side_effect=mock_particles_generator)
    @mock.patch('madx.particles_trajectory_generator.__transport', side_effect=mock_transport)
    def test_simple_run(self, mocked_function, another_mock):
        simple_bunch_configuration = prev_test.TestPlot_optical_function.get_simple_bunch_configuration()
        for optical_function in self.optical_functions:
            optical_function(simple_bunch_configuration, "path")

    @mock.patch('madx.particles_trajectory_generator.__transport', side_effect=mock_transport)
    def test_with_data_generator(self, another_mock):
        simple_bunch_configuration = prev_test.TestPlot_optical_function.get_simple_bunch_configuration()
        for optical_function in self.optical_functions:
            optical_function(simple_bunch_configuration, "path")

    @mock.patch('madx.particles_trajectory_generator.__transport', side_effect=transport_with_loose)
    def test_with_data_lost_transport(self, another_mock):
        simple_bunch_configuration = prev_test.TestPlot_optical_function.get_simple_bunch_configuration()
        for optical_function in self.optical_functions:
            output = optical_function(simple_bunch_configuration, "path")
            if output.shape != (3, 6):
                self.fail("Incorrect output size: " + str(output.shape))
