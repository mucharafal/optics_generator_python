import unittest
import data.particles_generator as pg
import numpy as np
import mock


class TestGenerateRandomParticle(unittest.TestCase):
    @staticmethod
    def __generate_random_particles_mock(beam_configuration, angles_ranges, path_to_accelerator_configuration,
                                         number_of_particles_in_one_run):
        configuration_keys = beam_configuration.keys()
        parameters = ["x", "theta_x", "y", "theta_y", "pt"]
        suffixes = ["_min", "_max"]
        desired_keys = [parameter_name + suffix for parameter_name in parameters for suffix in suffixes]
        if configuration_keys != desired_keys:
            raise ValueError
        angles_keys = [name + suffix for name in []]

    def test_simple_run(self):
        beam_configuration = dict()
        beam_configuration["x_min"] = 0
        beam_configuration["x_max"] = 1
        beam_configuration["y_min"] = 0
        beam_configuration["y_max"] = 1
        beam_configuration["theta_x_min"] = 0
        beam_configuration["theta_x_max"] = 1
        beam_configuration["theta_y_min"] = 0
        beam_configuration["theta_y_max"] = 1
        beam_configuration["pt_min"] = 0
        beam_configuration["pt_max"] = 1


