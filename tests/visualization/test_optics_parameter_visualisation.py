from unittest import TestCase
import numpy as np
from data import bunch_configuration as buc
import visualization.optics_parameter_visualisation as opv


class TestPlot_optical_function(TestCase):
    @staticmethod
    def get_simple_bunch_configuration():

        x_mean = 0.0
        sigma_x = 0.0000
        theta_x_mean = 0.000
        sigma_theta_x = 0.00000
        y_mean = 0.0
        sigma_y = 0.0000
        theta_y_mean = 0.00
        sigma_theta_y = 0.00000
        pt_mean = -0.075
        sigma_pt = 0.075

        number_of_x_values = 1
        number_of_theta_x_values = 1
        number_of_y_values = 1
        number_of_theta_y_values = 1
        number_of_pt_values = 100

        configuration = buc.BunchConfiguration.from_sigma(x_mean, sigma_x, number_of_x_values,
                                                          theta_x_mean, sigma_theta_x,
                                                          number_of_theta_x_values,
                                                          y_mean, sigma_y, number_of_y_values,
                                                          theta_y_mean, sigma_theta_y,
                                                          number_of_theta_y_values,
                                                          pt_mean, sigma_pt, number_of_pt_values)
        return configuration

    @staticmethod
    def mock_optical_function_approximator(approximator, bunch_configuration):
        number_of_particles = bunch_configuration.get_number_of_particles()
        return np.random.rand(6, number_of_particles)

    @staticmethod
    def mock_optical_function_madx(bunch_configuration, madx_configuration):
        number_of_particles = bunch_configuration.get_number_of_particles()
        return np.random.rand(6, number_of_particles)

    def test_simple_run_approximator(self):
        basic_configuration = self.get_simple_bunch_configuration()
        opv.plot_optical_function_of_approximator(None, basic_configuration, self.mock_optical_function_approximator,
                                                  "x", "D x", "title")

    def test_simple_run_madx(self):
        basic_configuration = self.get_simple_bunch_configuration()
        opv.plot_optical_function_of_madx(None, basic_configuration, self.mock_optical_function_madx
                                          , "x", "D x", "title")
