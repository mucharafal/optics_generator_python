import numpy as np


class Particles:
    def __init__(self, particles, mapping):
        if particles.shape[0] == len(mapping.keys()):
            self.particles = particles.T
        elif particles.shape[1] == len(mapping.keys()):
            self.particles = particles
        else:
            raise Exception("Incorrect sth")
        self.mapping = mapping

    def get_values_of(self, parameter_name):
        index = self.mapping[parameter_name]
        return self.particles.T[index].reshape(-1, 1)

    def get_number_of_particles(self):
        return self.particles.shape[0]

    def get_coordinates_of(self, *parameters):
        result_matrix = None
        for parameter in parameters:
            result_matrix = self.get_values_of(parameter) if result_matrix is None else \
                np.append(result_matrix, self.get_values_of(parameter), axis=1)

        return result_matrix

    def get_canonical_parameters(self, *parameters):
        return self.get_coordinates_of(*parameters)

    def add_zeros_column(self, parameter):
        particles = np.append(self.particles, np.zeros((self.particles.shape[0], 1)), axis=1)
        mapping = self.mapping.copy()
        mapping[parameter] = particles.shape[1] - 1
        return Particles(particles, mapping)


def transform_to_geometrical_coordinates(particles):
    new_particles = np.copy(particles)
    new_particles.T[1] /= 1 + new_particles.T[4]
    new_particles.T[3] /= 1 + new_particles.T[4]
    return new_particles