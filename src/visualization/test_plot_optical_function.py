from unittest import TestCase
import numpy as np
import visualization.optics_parameter_visualisation as opv


class TestPlot_optical_function(TestCase):
    @staticmethod
    def get_simple_configuration():
        approximator = None

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

        configuration = opv.ApproximatorAndBunchConfiguration.get_using_sigma(approximator,
                                                                              x_mean, sigma_x, number_of_x_values,
                                                                              theta_x_mean, sigma_theta_x,
                                                                              number_of_theta_x_values,
                                                                              y_mean, sigma_y, number_of_y_values,
                                                                              theta_y_mean, sigma_theta_y,
                                                                              number_of_theta_y_values,
                                                                              pt_mean, sigma_pt, number_of_pt_values)
        return configuration

    @staticmethod
    def mock_optical_function(approximator,
                                     x_min, x_max,
                                     number_of_x_values,
                                     theta_x_min, theta_x_max,
                                     number_of_theta_x_values,
                                     y_min, y_max,
                                     number_of_y_values,
                                     theta_y_min, theta_y_max,
                                     number_of_theta_y_values,
                                     pt_min, pt_max,
                                     number_of_pt_values):
        number_of_particles = number_of_pt_values * number_of_x_values * number_of_theta_x_values * number_of_y_values\
                                * number_of_theta_y_values
        return np.random.rand(6, number_of_particles)

    def test_simple_run(self):
        basic_configuration = self.get_simple_configuration()
        opv.plot_optical_function(basic_configuration, self.mock_optical_function, "x", "D x", "title")
