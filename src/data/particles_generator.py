import numpy as np
"""
File include some methods to generate matrix with parameters of particles.
There is two ways generating:
- random with values from given range
- with given step from given range
"""


def generate_from_range(x_min, x_max, number_of_x_in_grid,
                        theta_x_min, theta_x_max, number_of_theta_x_in_grid,
                        y_min, y_max, number_of_y_in_grid,
                        theta_y_min, theta_y_max, number_of_theta_y_in_grid,
                        t_min, t_max, number_of_t_in_grid,
                        pt_min, pt_max, number_of_pt_in_grid):
    """
    Generate carthesian product of parameters of given range.
    :param x_min: begin of x range
    :param x_max: end of x range
    :param number_of_x_in_grid:
    :param theta_x_min: begin of theta x range
    :param theta_x_max: end of theta x range
    :param number_of_theta_x_in_grid:
    :param y_min:
    :param y_max:
    :param number_of_y_in_grid:
    :param theta_y_min:
    :param theta_y_max:
    :param number_of_theta_y_in_grid:
    :param t_min:
    :param t_max:
    :param number_of_t_in_grid:
    :param pt_min:
    :param pt_max:
    :param number_of_pt_in_grid:
    :return:
    """
    # Create and initialize vectors with coordinates of particles in grid
    x_vector = np.linspace(x_min, x_max, number_of_x_in_grid)
    theta_x_vector = np.linspace(theta_x_min, theta_x_max, number_of_theta_x_in_grid)
    y_vector = np.linspace(y_min, y_max, number_of_y_in_grid)
    theta_y_vector = np.linspace(theta_y_min, theta_y_max, number_of_theta_y_in_grid)
    t_vector = np.linspace(t_min, t_max, number_of_t_in_grid)
    pt_vector = np.linspace(pt_min, pt_max, number_of_pt_in_grid)

    # Create grid, which is carthesian product of above coordinates vectors
    grid = np.array(np.meshgrid(x_vector, theta_x_vector, y_vector, theta_y_vector, t_vector, pt_vector))\
        .T.reshape(-1, 6)

    return grid


def generate_particles_randomly_with_angle(x_min, x_max,
                                           theta_x_min, theta_x_max,
                                           y_min, y_max,
                                           theta_y_min, theta_y_max,
                                           t_min, t_max,
                                           pt_min, pt_max,
                                           x_angle_min, x_angle_max,
                                           y_angle_min, y_angle_max,
                                           number_of_particles):
    """
    Deprecated. Remove t parameter. Angles in such form are useless for madx.
    Generate matrix. WARNING- to file part.in are saved only parameters: x, theta x,
    y, theta y, t, pt. Angles should be only in returned matrix.
    :param x_min: begin of x range
    :param x_max: end of x range
    :param theta_x_min: begin of theta x range
    :param theta_x_max: end of theta x range
    :param y_min: begin of y range
    :param y_max: end of y range
    :param theta_y_min: begin of theta y range
    :param theta_y_max: end of theta y range
    :param t_min: begin of t range
    :param t_max: end of t range
    :param pt_min: begin of pt range
    :param pt_max: end of pt range
    :param x_angle_min: begin of angle x range
    :param x_angle_max: end of angle x range
    :param y_angle_min: begin of angle y range
    :param y_angle_max: end of angle y range
    :param number_of_particles: number of generated rows
    :return: matrix with columns
    """
    grid = generate_particles_randomly(x_min, x_max,
                                       theta_x_min, theta_x_max,
                                       y_min, y_max,
                                       theta_y_min, theta_y_max,
                                       t_min, t_max,
                                       pt_min, pt_max,
                                       number_of_particles)
    max_vector = np.array([[x_angle_max, y_angle_max]])
    min_vector = np.array([[x_angle_min, y_angle_min]])
    angles = (max_vector - min_vector) * np.random.random_sample((number_of_particles, 2)) + min_vector

    # add values of x angle to theta x
    grid.T[1] += angles.T[0]
    # add values of y angle to theta y
    grid.T[3] += angles.T[1]

    grid = np.append(grid, angles, axis=1)

    return grid


def generate_particles_randomly(x_min, x_max,
                                  theta_x_min, theta_x_max,
                                  y_min, y_max,
                                  theta_y_min, theta_y_max,
                                  t_min, t_max,
                                  pt_min, pt_max,
                                  number_of_particles):
    """
    Generate matrix with random values of parameters from given ranges
    :param x_min: begin of x range
    :param x_max: end of x range
    :param theta_x_min: begin of theta x range
    :param theta_x_max: end of theta x range
    :param y_min: begin of y range
    :param y_max: end of y range
    :param theta_y_min: begin of theta y range
    :param theta_y_max: end of theta y range
    :param t_min: begin of t range
    :param t_max: end of t range
    :param pt_min: begin of pt range
    :param pt_max: end of pt range
    :param number_of_particles: number of generated rows
    :return: numpy matrix with number_of_particles x 6 shape
    """
    min_values = [x_min, theta_x_min, y_min, theta_y_min, t_min, pt_min]
    max_values = [x_max, theta_x_max, y_max, theta_y_max, t_max, pt_max]
    number_of_parameters = 6
    max_vector = np.zeros((1, number_of_parameters))
    min_vector = np.zeros((1, number_of_parameters))
    for i in range(number_of_parameters):
        max_vector[0][i] = max_values[i]
        min_vector[0][i] = min_values[i]

    grid = (max_vector - min_vector) * np.random.random_sample((number_of_particles, number_of_parameters)) + min_vector
    return grid


