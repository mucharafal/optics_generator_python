from unittest import TestCase
import numpy as np
from data.particles import Particles


class TestParticles(TestCase):
    def test_get_values_of(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        m = np.array([3, 4, 5]).reshape((-1, 1))
        n = np.array([4, 5, 6]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        self.assertTrue(np.allclose(particles.get_values_of("x"), k))

    def test_constructor_should_copy_particles(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        array[0][0] = 100
        self.assertFalse(np.allclose(particles.get_values_of("x"), array.T[0].reshape((-1, 1))))

    def test_get_values_of_should_return_copy_of_vector(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        cp = particles.get_values_of("x")
        cp[0][0] = 100
        self.assertFalse(np.allclose(particles.get_values_of("x"), cp))

    def test_get_number_of_particles(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        self.assertTrue(particles.get_number_of_particles() == 3)

    def test_get_first_parameter_with_get_coordinates_of(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        received_x = particles.get_default_coordinates_of("x")
        assert np.allclose(received_x, k)

    def test_get_second_parameter_with_get_coordinates_of(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        received_y = particles.get_default_coordinates_of("y")
        assert np.allclose(received_y, l)

    def test_get_all_parameters_with_get_coordinates_of(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        received_x_and_y = particles.get_default_coordinates_of("x", "y")
        assert np.allclose(received_x_and_y, array)

    def test_get_all_parameters_in_different_order_with_get_coordinates_of(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        received_y_and_x = particles.get_default_coordinates_of("y", "x")
        l_and_k = np.append(l, k, axis=1)
        assert np.allclose(received_y_and_x, l_and_k)

    def test_add_zeros_column(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        m = np.array([0, 0, 0]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        particles_with_zeros_column = particles.add_zeros_column("z")
        array_with_zeros_column = np.append(array, m, axis=1)
        assert np.allclose(particles_with_zeros_column.particles, array_with_zeros_column)

    def test_filter_equals(self):
        k = np.array([1, 2, 1]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        particles_with_x_eq_1 = particles.filter_equals("x", 1)
        assert np.allclose(particles_with_x_eq_1.particles, np.array([[1, 2], [1, 4]]))

    def test_get_matrix(self):
        k = np.array([1, 2, 1]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        array1 = particles.get_matrix()
        array1[0][0] = -1
        assert np.allclose(array1, particles.particles)

    def test_get_mapping(self):
        k = np.array([1, 2, 1]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        mapping1 = particles.get_mapping()
        mapping1["t"] = 1
        assert mapping1 == particles.mapping

    def test_shift_parameter(self):
        k = np.array([1, 2, 1]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        l_shifted = l + 1
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        particles_with_shifted_y = particles.shift_parameter("y", 1)
        assert np.allclose(particles_with_shifted_y.get_values_of("y"), l_shifted)

    def test_add_column(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        m = np.array([3, 4, 5]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        particles_with_m = particles.add_column("m", m)
        self.assertTrue(np.allclose(particles_with_m.get_values_of("m"), m))

    def test_add_columns(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        m = np.array([3, 4, 5]).reshape((-1, 1))
        n = np.array([4, 5, 6]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        particles_with_m_and_n = particles.add_column("m", m).add_column("n", n)
        self.assertTrue(np.allclose(particles_with_m_and_n.get_values_of("m"), m))
        self.assertTrue(np.allclose(particles_with_m_and_n.get_values_of("n"), n))

    def test_constructor(self):
        k = np.array([1, 2, 3]).reshape((-1, 1))
        l = np.array([2, 3, 4]).reshape((-1, 1))
        array = np.append(k, l, axis=1)
        particles = Particles(array, {"x": 0, "y": 1})
        Particles(particles.particles, particles.mapping)
