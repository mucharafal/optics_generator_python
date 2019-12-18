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

    def get_column(self, parameter_name):
        index = self.mapping[parameter_name]
        return np.copy(self.particles.T[index].reshape(-1, 1))

    def get_number_of_particles(self):
        return self.particles.shape[0]

    def get_default_coordinates_of(self, *parameters):
        result_matrix = None
        for parameter in parameters:
            result_matrix = self.get_column(parameter) if result_matrix is None else \
                np.append(result_matrix, self.get_column(parameter), axis=1)

        return result_matrix

    def add_zeros_column(self, parameter):
        vector_to_add = np.zeros((self.particles.shape[0], 1))
        return self.add_column(parameter, vector_to_add)

    def filter_equals(self, parameter, value):
        particles = self.particles[np.isclose(self.particles.T[self.mapping[parameter]], value)]
        return self.__class__(particles, self.mapping)

    def get_matrix(self):
        return self.particles

    def get_mapping(self):
        return self.mapping

    def shift_parameter(self, parameter_name, shift_value):
        particles = np.copy(self.particles)
        parameter_index = self.mapping[parameter_name]
        particles.T[parameter_index] = particles.T[parameter_index] + shift_value
        return self.__class__(particles, self.mapping)

    def add_column(self, parameter_name, values):
        if self.particles is None:
            particles = values.reshape((-1, 1))
        else:
            particles = np.append(self.particles, values, axis=1)
        mapping = self.mapping.copy()
        mapping[parameter_name] = particles.shape[1] - 1
        return self.__class__(particles, mapping)

    def override_column(self, parameter_name, values):
        matrix = np.copy(self.particles)
        parameter_index = self.mapping[parameter_name]
        matrix[parameter_index] = values
        return self.__class__(matrix, self.mapping)

    def to_pandas_data_frame(self):
        columns = {parameter_name: self.get_column(parameter_name).reshape((-1,)) for parameter_name in self.mapping}
        data_frame = DataFrame(columns)
        return data_frame

    def plot(self, x, y, *args, **kwargs):
        return plotter.plot_from_one_matrix(x, y, self, *args, **kwargs)

    @classmethod
    def empty(cls):
        return cls(None, dict())


class GeometricalCoordinates(Particles):
    def __init__(self, particles, mapping):
        super().__init__(particles, mapping)

    def get_canonical_coordinates_of(self, *parameters):
        result_matrix = None
        for parameter in parameters:
            vector_to_add = None
            if parameter == Parameters.THETA_X or parameter == Parameters.THETA_Y:
                vector_in_geometrical_coordinates = self.get_column(parameter)
                vector_of_pt = self.get_column(Parameters.PT)
                vector_to_add = transform_from_geometrical_coordinates(vector_in_geometrical_coordinates, vector_of_pt)
            else:
                vector_to_add = self.get_column(parameter)
            result_matrix = vector_to_add if result_matrix is None else \
                np.append(result_matrix, vector_to_add, axis=1)

        return result_matrix

    def get_geometrical_coordinates_of(self, *parameters):
        return self.get_default_coordinates_of(*parameters)

    def transform_to_canonical_coordinates(self):
        parameters = self.mapping.keys()
        matrix = self.get_canonical_coordinates_of(*parameters)
        return CanonicalCoordinates(matrix, self.mapping)


class CanonicalCoordinates(Particles):
    def __init__(self, particles, mapping):
        super().__init__(particles, mapping)

    def get_canonical_coordinates_of(self, *parameters):
        return self.get_default_coordinates_of(*parameters)

    def get_geometrical_coordinates_of(self, *parameters):
        result_matrix = None
        for parameter in parameters:
            vector_to_add = None
            if parameter == Parameters.THETA_X or parameter == Parameters.THETA_Y:
                vector_in_canonical_coordinates = self.get_column(parameter)
                vector_of_pt = self.get_column(Parameters.PT)
                vector_to_add = transform_to_geometrical_coordinates(vector_in_canonical_coordinates, vector_of_pt)
            else:
                vector_to_add = self.get_column(parameter)
            result_matrix = vector_to_add if result_matrix is None else \
                np.append(result_matrix, vector_to_add, axis=1)

        return result_matrix

    def transform_to_canonical_coordinates(self):
        return self


def transform_to_geometrical_coordinates(vector_with_angle, vector_with_pt):
    vector_in_geometrical_coordinates = vector_with_angle / (1 + vector_with_pt)
    return vector_in_geometrical_coordinates


def transform_from_geometrical_coordinates(angle_vector, pt_vector):
    angle_in_canonical_coordinates = angle_vector * (1 + pt_vector)
    return angle_in_canonical_coordinates
