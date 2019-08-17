from unittest import TestCase
import ptc_track.optics_parameters as op
from data import bunch_configuration as buc
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
    """
    This function simulate loosing particles by ptc_track. Sometimes it occurs and can lead to errors.
    :param particles: matrix with particles positions
    :param path: path to configuration, take it as mock
    :return: matrix with positions of particles
    """
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


def v_x_transport(begin_positions, path):
    segments = add_other_parameters(begin_positions)
    v_x = 100
    x = segments["start"][0][2]
    segments["end"][0][2] = x * v_x
    return segments


def v_y_transport(begin_positions, path):
    segments = add_other_parameters(begin_positions)
    v_y = 100
    y = segments["start"][0][4]
    segments["end"][0][4] = y * v_y
    return segments


def l_x_transport(begin_positions, path):
    segments = add_other_parameters(begin_positions)
    l_x = 100
    theta_x = segments["start"][0][3]
    segments["end"][0][2] = theta_x * l_x
    return segments


def l_y_transport(begin_positions, path):
    segments = add_other_parameters(begin_positions)
    l_y = 100
    theta_y = segments["start"][0][5]
    segments["end"][0][4] = theta_y * l_y
    return segments


def d_x_transport(begin_positions, path):
    segments = add_other_parameters(begin_positions)
    d_x = 100
    ksi = segments["start"][0][7]
    segments["end"][0][2] = d_x * ksi
    return segments


def d_y_transport(begin_positions, path):
    segments = add_other_parameters(begin_positions)
    d_y = 100
    ksi = segments["start"][0][7]
    segments["end"][0][4] = d_y * ksi
    return segments


def add_other_parameters(particles):
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


class TestCompute_optics_parameters(TestCase):

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

    optical_functions = [op.compute_v_x, op.compute_v_y, op.compute_d_x, op.compute_d_y, op.compute_l_x,
                         op.compute_l_y]

    @mock.patch('data.particles_generator.generate_from_range', side_effect=mock_particles_generator)
    @mock.patch('ptc_track.particles_trajectory_generator.__transport', side_effect=mock_transport)
    def test_simple_run(self, mocked_function, another_mock):
        simple_bunch_configuration = prev_test.TestPlot_optical_function.get_simple_bunch_configuration()
        for optical_function in self.optical_functions:
            optical_function(simple_bunch_configuration, "path")

    @mock.patch('ptc_track.particles_trajectory_generator.__transport', side_effect=mock_transport)
    def test_with_data_generator(self, another_mock):
        simple_bunch_configuration = prev_test.TestPlot_optical_function.get_simple_bunch_configuration()
        for optical_function in self.optical_functions:
            optical_function(simple_bunch_configuration, "path")

    @mock.patch('ptc_track.particles_trajectory_generator.__transport', side_effect=transport_with_loose)
    def test_with_data_lost_transport(self, another_mock):
        simple_bunch_configuration = prev_test.TestPlot_optical_function.get_simple_bunch_configuration()
        begin_number_of_particles = simple_bunch_configuration.get_number_of_particles()
        for optical_function in self.optical_functions:
            output = optical_function(simple_bunch_configuration, "path")
            if output.shape != (begin_number_of_particles - 2, 6):
                self.fail("Incorrect output size: " + str(output.shape))

    @mock.patch('ptc_track.particles_trajectory_generator.__transport', side_effect=v_x_transport)
    def test_v_x(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = op.compute_v_x(simple_bunch_configuration, "")
        v_x = matrix[0][5]
        self.assertAlmostEqual(v_x, 100, msg="value of v_x is incorrect")

    @mock.patch('ptc_track.particles_trajectory_generator.__transport', side_effect=v_y_transport)
    def test_v_y(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = op.compute_v_y(simple_bunch_configuration, "")
        v_y = matrix[0][5]
        self.assertAlmostEqual(v_y, 100, msg="value of v_y is incorrect")

    @mock.patch('ptc_track.particles_trajectory_generator.__transport', side_effect=l_x_transport)
    def test_l_x(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = op.compute_l_x(simple_bunch_configuration, "")
        l_x = matrix[0][5]
        self.assertAlmostEqual(l_x, 100, msg="value of l_x is incorrect")

    @mock.patch('ptc_track.particles_trajectory_generator.__transport', side_effect=l_y_transport)
    def test_l_y(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = op.compute_l_y(simple_bunch_configuration, "")
        l_y = matrix[0][5]
        self.assertAlmostEqual(l_y, 100, msg="value of l_y is incorrect")

    @mock.patch('ptc_track.particles_trajectory_generator.__transport', side_effect=d_x_transport)
    def test_d_x(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = op.compute_d_x(simple_bunch_configuration, "")
        d_x = matrix[0][5]
        self.assertAlmostEqual(d_x, 100, msg="value of l_x is incorrect")

    @mock.patch('ptc_track.particles_trajectory_generator.__transport', side_effect=d_y_transport)
    def test_d_y(self, transport_function_mock):
        simple_bunch_configuration = self.get_bunch_configuration_to_optics_test()
        matrix = op.compute_d_y(simple_bunch_configuration, "")
        d_y = matrix[0][5]
        self.assertAlmostEqual(d_y, 100, msg="value of l_y is incorrect")