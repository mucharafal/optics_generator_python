from unittest import TestCase
import data.particles_generator as pg
from tests.visualization.test_optics_parameter_visualisation import TestPlot_optical_function as Util
from data.bunch_configuration import BunchConfiguration
import numpy as np


class TestGenerate_particles_randomly(TestCase):

    @staticmethod
    def get_configuration_for_x_test():
        return BunchConfiguration(0, 1, 11, 0, 0, 1,
                                  0, 0, 1, 0, 0, 1,
                                  0, 0, 1)

    def test_simple_run(self):
        bunch_configuration = Util.get_simple_bunch_configuration()
        pg.generate_particles_randomly(bunch_configuration)

    def test_values_x(self):
        configuration = self.get_configuration_for_x_test()
        result = pg.generate_particles_randomly(configuration)
        if result.shape != (11, 5):
            self.fail("Incorrect output size")

        vector_x = result.T[0]
        x_min = np.min(vector_x)
        x_max = np.max(vector_x)
        if x_min < 0 or x_max > 1:
            self.fail("Value out of given range (0, 1)")
        for index in range(1, 5):
            vector = result.T[index]
            min = np.min(vector)
            max = np.max(vector)
            if min != 0 or max != 0:
                self.fail("Value out of given range (0, 0)")


class TestGenerate_from_range(TestCase):
    @staticmethod
    def get_configuration_for_x_test():
        return BunchConfiguration(0, 1, 11, 0, 0, 1,
                                  0, 0, 1, 0, 0, 1,
                                  0, 0, 1)

    def test_simple_run(self):
        bunch_configuration = Util.get_simple_bunch_configuration()
        pg.generate_from_range(bunch_configuration)

    def test_values_x(self):
        configuration = self.get_configuration_for_x_test()
        result = pg.generate_from_range(configuration)
        if result.shape != (11, 5):
            self.fail("Incorrect output size")

        vector_x = result.T[0]
        np.testing.assert_almost_equal(np.array([0.1 * x for x in range(11)]), vector_x)
        for index in range(1, 5):
            vector = result.T[index]
            np.testing.assert_almost_equal(np.array([0 for _ in range(11)]), vector)
