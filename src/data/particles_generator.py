import numpy as np
from data.particles import Particles
"""
File include some methods to generate matrix with parameters of particles.
There is two ways generating:
- random with values from given range
- with given step from given range
"""


def generate_from_range(grid_configuration):
    """
    Generate carthesian product of parameters of given range.
    :param: GridConfiguration grid_configuration
    :return:
    """
    # Create and initialize vectors with coordinates of particles in grid

    vectors = [__get_vector(parameter) for parameter in grid_configuration.parameters]

    # Create grid, which is carthesian product of above coordinates vectors
    grid = np.array(np.meshgrid(*vectors)).T.reshape((-1, 5))

    mapping = __get_mapping(grid_configuration.parameters)

    particles_object = Particles(grid, mapping)

    return particles_object


def generate_particles_randomly(grid_configuration):
    """
    Generate matrix with random values of parameters from given ranges
    :param grid_configuration
    :return: numpy matrix with number_of_particles x 5 shape
    """
    parameters = grid_configuration.parameters

    min_values = [parameter.minimal_value for parameter in parameters]
    max_values = [parameter.maximal_value for parameter in parameters]

    min_values_vector = np.array(min_values)
    max_values_vector = np.array(max_values)

    number_of_parameters = len(parameters)
    number_of_particles = grid_configuration.get_number_of_particles()

    grid = (max_values_vector - min_values_vector) * np.random.random_sample((number_of_particles, number_of_parameters)) + min_values_vector

    particles_object = Particles(grid, __get_mapping(parameters))

    return particles_object


def __get_mapping(parameters):
    mapping = {}
    for index in range(len(parameters)):
        mapping[parameters[index].parameter_name] = index
    return mapping


def __get_vector(parameter_configuration):
    min = parameter_configuration.minimal_value
    max = parameter_configuration.maximal_value
    resolution = parameter_configuration.resolution
    return np.linspace(min, max, resolution)



