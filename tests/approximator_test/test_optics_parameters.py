from unittest import TestCase
import tests.visualization.test_optics_parameter_visualisation as prev_test
import approximator.optics_parameters as opfa
import mock
import numpy as np
from data import bunch_configuration


def mock_particles_generator(beam_configuration):
    if type(beam_configuration) is not bunch_configuration.BunchConfiguration:
        raise ValueError
    return np.random.rand(6, beam_configuration.get_number_of_particles())


def mock_transport(approximator, begin_positions):
    return np.random.rand(begin_positions.shape[0], 5)


class TestCompute_compute_optical_functions(TestCase):

    optical_functions = [opfa.compute_v_x, opfa.compute_v_y, opfa.compute_d_x, opfa.compute_d_y, opfa.compute_l_x, opfa.compute_l_y]

    @mock.patch('data.particles_generator.generate_from_range', side_effect=mock_particles_generator)
    @mock.patch('approximator.runner.transport', side_effect=mock_transport)
    def test_simple_run(self, mocked_function, another_mock):
        simple_bunch_configuration = prev_test.TestPlot_optical_function.get_simple_bunch_configuration()
        for optical_function in self.optical_functions:
            optical_function(None, simple_bunch_configuration)

    @mock.patch('approximator.runner.transport', side_effect=mock_transport)
    def test_with_data_generator(self, another_mock):
        simple_bunch_configuration = prev_test.TestPlot_optical_function.get_simple_bunch_configuration()
        for optical_function in self.optical_functions:
            optical_function(None, simple_bunch_configuration)