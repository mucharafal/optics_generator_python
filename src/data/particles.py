import numpy as np
from data.parameters_names import ParametersNames as Parameters
from pandas import DataFrame
import visualization.visualize as plotter


class Particles:
    def __init__(self, particles, mapping):
        if particles is None:
            self.particles = None
        elif particles.shape[1] == len(mapping.keys()):
            self.particles = np.copy(particles)
        elif particles.shape[0] == len(mapping.keys()):
            self.particles = np.copy(particles.T)
        else:
            raise Exception("Incorrect mapping")
        self.mapping = mapping

    def get_values_of(self, parameter_name):
        index = self.mapping[parameter_name]
        return np.copy(self.particles.T[index].reshape(-1, 1))

    def get_number_of_particles(self):
        return self.particles.shape[0]

    def get_coordinates_of(self, *parameters):
        result_matrix = None
        for parameter in parameters:
            result_matrix = self.get_values_of(parameter) if result_matrix is None else \
                np.append(result_matrix, self.get_values_of(parameter), axis=1)

        return result_matrix

    def add_zeros_column(self, parameter):
        vector_to_add = np.zeros((self.particles.shape[0], 1))
        return self.add_column(parameter, vector_to_add)

    def filter_equals(self, parameter, value):
        particles = self.particles[np.isclose(self.particles.T[self.mapping[parameter]], value)]
        return Particles(particles, self.mapping)

    def get_matrix(self):
        return self.particles

    def get_mapping(self):
        return self.mapping

    def shift_parameter(self, parameter_name, shift_value):
        particles = np.copy(self.particles)
        parameter_index = self.mapping[parameter_name]
        particles.T[parameter_index] = particles.T[parameter_index] + shift_value
        return Particles(particles, self.mapping)

    def add_column(self, parameter_name, values):
        if self.particles is None:
            particles = values.reshape((-1, 1))
        else:
            particles = np.append(self.particles, values, axis=1)
        mapping = self.mapping.copy()
        mapping[parameter_name] = particles.shape[1] - 1
        return Particles(particles, mapping)

    def override_column(self, parameter_name, values):
        matrix = np.copy(self.particles)
        parameter_index = self.mapping[parameter_name]
        matrix[parameter_index] = values
        return Particles(matrix, self.mapping)

    def to_pandas_data_frame(self):
        columns = {parameter_name: self.get_values_of(parameter_name).reshape((-1,)) for parameter_name in self.mapping}
        data_frame = DataFrame(columns)
        return data_frame

    def plot(self, x, y, *args, **kwargs):
        return plotter.plot_from_one_matrix(x, y, self, *args, **kwargs)

    @staticmethod
    def empty():
        return Particles(None, dict())


def transform_to_geometrical_coordinates(particles):
    theta_x = particles.get_values_of(Parameters.THETA_X)
    theta_y = particles.get_values_of(Parameters.THETA_Y)
    ksi = particles.get_values_of(Parameters.PT)

    theta_x /= 1 + ksi
    theta_y /= 1 + ksi

    new_particles = particles\
        .override_column(Parameters.THETA_X, theta_x)\
        .override_column(Parameters.THETA_Y, theta_y)

    return new_particles
