from unittest import TestCase
from approximator import particles_trajectory_generator
from data.bunch_configuration import BunchConfiguration
from approximator_test.test_optics_parameters import mock_particles_generator, mock_transport
import mock


class Test__generate_random_particles(TestCase):

    @staticmethod
    def get_configuration_for_x_test():
        return BunchConfiguration(0, 1, 11, 0, 0, 1,
                                  0, 0, 1, 0, 0, 1,
                                  0, 0, 1)

    @mock.patch('data.particles_generator.generate_from_range', side_effect=mock_particles_generator)
    @mock.patch('approximator.runner.transport', side_effect=mock_transport)
    def test_simple_run(self, mock1, mock2):
        configuration = self.get_configuration_for_x_test()
        particles_trajectory_generator.generate_random_particles(None, configuration)


class Test__generate_from_range(TestCase):

    @staticmethod
    def get_configuration_for_x_test():
        return BunchConfiguration(0, 1, 11, 0, 0, 1,
                                  0, 0, 1, 0, 0, 1,
                                  0, 0, 1)

    @mock.patch('data.particles_generator.generate_from_range', side_effect=mock_particles_generator)
    @mock.patch('approximator.runner.transport', side_effect=mock_transport)
    def test_simple_run(self, mock1, mock2):
        configuration = self.get_configuration_for_x_test()
        particles_trajectory_generator.generate_random_particles(None, configuration)
