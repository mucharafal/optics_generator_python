from unittest import TestCase
import tests.visualization.test_optics_parameter_visualisation as prev_test
from data import bunch_configuration as buc
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


def v_x_transport(approximator, begin_positions):
    v_x = 100
    x = begin_positions[0][0]
    begin_positions[0][0] = x * v_x
    return begin_positions


def v_y_transport(approximator, begin_positions):
    v_y = 100
    y = begin_positions[0][2]
    begin_positions[0][2] = y * v_y
    return begin_positions


def l_x_transport(approximator, begin_positions):
    l_x = 100
    theta_x = begin_positions[0][1]
    begin_positions[0][0] = theta_x * l_x
    return begin_positions


def l_y_transport(approximator, begin_positions):
    l_y = 100
    y = begin_positions[0][3]
    begin_positions[0][2] = y * l_y
    return begin_positions


def d_x_transport(approximator, begin_positions):
    d_x = 100
    ksi = begin_positions[0][4]
    begin_positions[0][0] = ksi * d_x
    return begin_positions


def d_y_transport(approximator, begin_positions):
    d_y = 100
    ksi = begin_positions[0][4]
    begin_positions[0][2] = ksi * d_y
    return begin_positions


class TestCompute_compute_optical_functions(TestCase):
    @staticmethod
    def get_bunch_configuration_to_optics_test():
        x_mean = 10e-3
        sigma_x = 10e-4
        theta_x_mean = 10e-6
        sigma_theta_x = 10e-7
        y_mean = 10e-3
        sigma_y = 10e-4
        theta_y_mean = 10e-6
        sigma_theta_y = 10e-7
        pt_mean = -0.1
        sigma_pt = 10e-3

        number_of_x_values = 1
        number_of_theta_x_values = 1
        number_of_y_values = 1
        number_of_theta_y_values = 1
        number_of_pt_values = 1

        configuration = buc.BunchConfiguration.from_sigma(x_mean, sigma_x, number_of_x_values,
                                                          theta_x_mean, sigma_theta_x,
                                                          number_of_theta_x_values,
                                                          y_mean, sigma_y, number_of_y_values,
                                                          theta_y_mean, sigma_theta_y,
                                                          number_of_theta_y_values,
                                                          pt_mean, sigma_pt, number_of_pt_values)
        return configuration

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

    @mock.patch('approximator.runner.transport', side_effect=v_x_transport)
    def test_v_x(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = opfa.compute_v_x(None, simple_bunch_configuration)
        v_x = matrix[0][5]
        self.assertAlmostEqual(v_x, 100, msg="value of v_x is incorrect")

    @mock.patch('approximator.runner.transport', side_effect=v_y_transport)
    def test_v_y(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = opfa.compute_v_y(None, simple_bunch_configuration)
        v_y = matrix[0][5]
        self.assertAlmostEqual(v_y, 100, msg="value of v_y is incorrect")

    @mock.patch('approximator.runner.transport', side_effect=l_x_transport)
    def test_l_x(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = opfa.compute_l_x(None, simple_bunch_configuration)
        l_x = matrix[0][5]
        self.assertAlmostEqual(l_x, 100, msg="value of l_x is incorrect")

    @mock.patch('approximator.runner.transport', side_effect=l_y_transport)
    def test_l_y(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = opfa.compute_l_y(None, simple_bunch_configuration)
        l_y = matrix[0][5]
        self.assertAlmostEqual(l_y, 100, msg="value of l_y is incorrect")

    @mock.patch('approximator.runner.transport', side_effect=d_x_transport)
    def test_d_x(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = opfa.compute_d_x(None, simple_bunch_configuration)
        d_x = matrix[0][5]
        self.assertAlmostEqual(d_x, 100, msg="value of l_x is incorrect")

    @mock.patch('approximator.runner.transport', side_effect=d_y_transport)
    def test_d_y(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = opfa.compute_d_y(None, simple_bunch_configuration)
        d_y = matrix[0][5]
        self.assertAlmostEqual(d_y, 100, msg="value of l_y is incorrect")


