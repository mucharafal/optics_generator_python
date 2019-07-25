import unittest
import data.particles_generator as pg
import numpy as np


class TestDataGenerator(unittest.TestCase):

    def test_generate_from_range_simple_x(self):
        generated_particles = pg.generate_from_range(1, 4, 4,
                                                     0, 0, 1,
                                                     0, 0, 1,
                                                     0, 0, 1,
                                                     0, 0, 1)
        matrix = np.array([[1, 0, 0, 0, 0],
                           [2, 0, 0, 0, 0],
                           [3, 0, 0, 0, 0],
                           [4, 0, 0, 0, 0]])
        np.testing.assert_almost_equal(generated_particles, matrix)

    def test_generate_from_range_simple_y(self):
        generated_particles = pg.generate_from_range(0, 0, 1,
                                                     0, 0, 1,
                                                     0, 3, 4,
                                                     0, 0, 1,
                                                     0, 0, 1)
        matrix = np.array([[0, 0, 0, 0, 0],
                           [0, 0, 1, 0, 0],
                           [0, 0, 2, 0, 0],
                           [0, 0, 3, 0, 0]])
        np.testing.assert_almost_equal(generated_particles, matrix)

    def test_generate_from_range_simple_theta_x(self):
        generated_particles = pg.generate_from_range(0, 0, 1,
                                                     0, 3, 4,
                                                     0, 0, 1,
                                                     0, 0, 1,
                                                     0, 0, 1)
        matrix = np.array([[0, 0, 0, 0, 0],
                           [0, 1, 0, 0, 0],
                           [0, 2, 0, 0, 0],
                           [0, 3, 0, 0, 0]])
        np.testing.assert_almost_equal(generated_particles, matrix)

    def test_generate_from_range_simple_theta_y(self):
        generated_particles = pg.generate_from_range(0, 0, 1,
                                                     0, 0, 1,
                                                     0, 0, 1,
                                                     0, 3, 4,
                                                     0, 0, 1)
        matrix = np.array([[0, 0, 0, 0, 0],
                           [0, 0, 0, 1, 0],
                           [0, 0, 0, 2, 0],
                           [0, 0, 0, 3, 0]])
        np.testing.assert_almost_equal(generated_particles, matrix)

    def test_generate_from_range_simple_pt(self):
        generated_particles = pg.generate_from_range(0, 0, 1,
                                                     0, 0, 1,
                                                     0, 0, 1,
                                                     0, 0, 1,
                                                     0, 1, 5)
        matrix = np.array([[0, 0, 0, 0, 0],
                           [0, 0, 0, 0, 0.25],
                           [0, 0, 0, 0, 0.5],
                           [0, 0, 0, 0, 0.75]])
        np.testing.assert_almost_equal(generated_particles, matrix)


class TestGenerateRandomly(unittest.TestCase):

    def test_if_run(self):
        try:
            pg.generate_particles_randomly(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
        except Exception:
            self.fail("generate_particles_randomly() raised Exception unexpectedly!")

    def test_size(self):
        generated_matrix = pg.generate_particles_randomly(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
        self.assertEqual(generated_matrix.shape, (5, 1))

    def test_size2(self):
        desired_size = 100
        generated_matrix = pg.generate_particles_randomly(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, desired_size)
        self.assertEqual(generated_matrix.shape, (5, desired_size))

    def test_boundary_x(self):
        desired_size = 10000
        generated_matrix = pg.generate_particles_randomly(0, 0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, desired_size)
        min_x = np.min(generated_matrix.T[0])
        max_x = np.max(generated_matrix.T[0])
        self.assertTrue(min_x > 0 and max_x < 0.5)

    def test_boundary_y(self):
        desired_size = 10000
        generated_matrix = pg.generate_particles_randomly(0, 0, 0, 0, 0.5, 1, 0, 0, 0, 0, desired_size)
        min_y = np.min(generated_matrix.T[2])
        max_y = np.max(generated_matrix.T[2])
        self.assertTrue(min_y > 0.5 and max_y < 1)
