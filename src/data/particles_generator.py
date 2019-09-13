import numpy as np
"""
File include some methods to generate matrix with parameters of particles.
There is two ways generating:
- random with values from given range
- with given step from given range
"""


def generate_from_range(beam_configuration):
    """
    Generate carthesian product of parameters of given range.
    :param: BunchConfiguration beam_configuration
    :return:
    """
    # Create and initialize vectors with coordinates of particles in grid
    conf = beam_configuration
    x_vector = np.linspace(conf.x_min, conf.x_max, conf.number_of_x_values)
    theta_x_vector = np.linspace(conf.theta_x_min, conf.theta_x_max, conf.number_of_theta_x_values)
    y_vector = np.linspace(conf.y_min, conf.y_max, conf.number_of_y_values)
    theta_y_vector = np.linspace(conf.theta_y_min, conf.theta_y_max, conf.number_of_theta_y_values)
    pt_vector = np.linspace(conf.pt_min, conf.pt_max, conf.number_of_pt_values)

    # Create grid, which is carthesian product of above coordinates vectors
    grid = np.array(np.meshgrid(x_vector, theta_x_vector, y_vector, theta_y_vector, pt_vector))\
        .T.reshape(-1, 5)

    return grid


def generate_particles_randomly_with_angle(beam_configuration, x_angle_min, x_angle_max, y_angle_min, y_angle_max):
    """
    Deprecated. Remove t parameter. Angles in such form are useless for ptc_track.
    Generate matrix. WARNING- to file part.in are saved only parameters: x, theta x,
    y, theta y, t, pt. Angles should be only in returned matrix.
    :param beam_configuration- configuration of beam- min and max values of parameters, number of particles
    :return: matrix with columns
    """
    grid = generate_particles_randomly(beam_configuration)
    max_vector = np.array([[x_angle_max, y_angle_max]])
    min_vector = np.array([[x_angle_min, y_angle_min]])
    angles = (max_vector - min_vector) * np.random.random_sample((beam_configuration.get_number_of_particles(), 2)) + \
             min_vector

    # add values of x angle to theta x
    grid.T[1] += angles.T[0]
    # add values of y angle to theta y
    grid.T[3] += angles.T[1]

    grid = np.append(grid, angles, axis=1)

    return grid


def generate_particles_randomly(beam_configuration):
    """
    Generate matrix with random values of parameters from given ranges
    :param beam_configuration
    :return: numpy matrix with number_of_particles x 5 shape
    """
    min_vector = np.array([beam_configuration.x_min, beam_configuration.theta_x_min, beam_configuration.y_min,
                           beam_configuration.theta_y_min, beam_configuration.pt_min])
    max_vector = np.array([beam_configuration.x_max, beam_configuration.theta_x_max, beam_configuration.y_max,
                           beam_configuration.theta_y_max, beam_configuration.pt_max])

    number_of_parameters = 5
    number_of_particles = beam_configuration.get_number_of_particles()

    grid = (max_vector - min_vector) * np.random.random_sample((number_of_particles, number_of_parameters)) + min_vector
    return grid
