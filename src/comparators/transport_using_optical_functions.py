import visualization.visualize as visualize
from data.parameters_names import ParametersNames as Parameters
from data.particles import Particles
import numpy as np


def compare_with(particles, reference_transporter,
                 dx_function, dy_function, lx_function, ly_function, vx_function, vy_function,
                 transported_dimension, depended_value):
    particles_with_optical_functions = __get_optical_functions(particles, dx_function, dy_function, lx_function,
                                                               ly_function, vx_function, vy_function)

    particles_transported_using_reference_transporter = reference_transporter(particles)["end"]
    particles_transported_using_optical_function = __transport_using_optical_functions(particles_with_optical_functions,
                                                                                       reference_transporter)
    difference = __compute_difference(particles_transported_using_optical_function,
                                      particles_transported_using_reference_transporter)
    particles_and_difference = __append_difference(particles, difference)
    axes = visualize.plot_datasets(depended_value, Parameters.get_delta(transported_dimension), "Transporter",
                                   {"diff": particles_and_difference})
    print("Reference dataset")
    print(particles_transported_using_reference_transporter.particles)
    print("Transported")
    print(particles_transported_using_optical_function.particles)
    print("Error")
    print(particles_and_difference.particles)
    return axes


def __get_optical_functions(particles, dx_function, dy_function, lx_function,
                            ly_function, vx_function, vy_function):
    # todo refactor
    print(particles.particles)
    dx = dx_function(particles).get_coordinates_of(Parameters.D_X)
    dy = dy_function(particles).get_coordinates_of(Parameters.D_Y)
    lx = lx_function(particles).get_coordinates_of(Parameters.L_X)
    ly = ly_function(particles).get_coordinates_of(Parameters.L_Y)
    vx = vx_function(particles).get_coordinates_of(Parameters.V_X)
    vy = vy_function(particles).get_coordinates_of(Parameters.V_Y)

    print("Dx, Lx, Vy")
    print(dx)
    print(lx)
    print(vx)

    particles_with_optical_functions = \
        particles.add_column(Parameters.D_X, dx).add_column(Parameters.D_Y, dy).add_column(Parameters.L_X, lx).\
        add_column(Parameters.L_Y, ly).add_column(Parameters.V_X, vx).add_column(Parameters.V_Y, vy)

    return particles_with_optical_functions


def __transport_using_optical_functions(particles_with_optical_functions, reference_transporter):
    x = particles_with_optical_functions.get_values_of(Parameters.X)
    theta_x = particles_with_optical_functions.get_values_of(Parameters.THETA_X)

    y = particles_with_optical_functions.get_values_of(Parameters.Y)
    theta_y = particles_with_optical_functions.get_values_of(Parameters.THETA_Y)

    ksi = particles_with_optical_functions.get_values_of(Parameters.PT)

    v_x = particles_with_optical_functions.get_values_of(Parameters.V_X)
    l_x = particles_with_optical_functions.get_values_of(Parameters.L_X)
    d_x = particles_with_optical_functions.get_values_of(Parameters.D_X)

    v_y = particles_with_optical_functions.get_values_of(Parameters.V_Y)
    l_y = particles_with_optical_functions.get_values_of(Parameters.L_Y)
    d_y = particles_with_optical_functions.get_values_of(Parameters.D_Y)

    print("Ksi")
    print(ksi)
    print("Dx")
    print(d_x)

    values_in_zero = reference_transporter(Particles(np.array([[0, 0, 0, 0, 0]]), {Parameters.X: 0,
                                                                                   Parameters.THETA_X: 1,
                                                                                   Parameters.Y: 2,
                                                                                   Parameters.THETA_Y: 3,
                                                                                   Parameters.PT: 4}))["end"]

    new_x = x * v_x + theta_x * l_x + ksi * d_x + values_in_zero.get_values_of(Parameters.X)[0]
    new_y = y * v_y + theta_y * l_y + ksi * d_y + values_in_zero.get_values_of(Parameters.Y)[0]

    array_with_positions = np.append(new_x, new_y, axis=1)

    return Particles(array_with_positions, {Parameters.X: 0, Parameters.Y: 1})


def __compute_difference(first_particles, second_particles):
    difference_x = first_particles.get_values_of(Parameters.X) - second_particles.get_values_of(Parameters.X)
    difference_y = first_particles.get_values_of(Parameters.Y) - second_particles.get_values_of(Parameters.Y)

    array_with_positions = np.append(difference_x, difference_y, axis=1)

    return Particles(array_with_positions, {Parameters.DELTA_X: 0, Parameters.DELTA_Y: 1})


def __append_difference(particles, difference):
    return particles.add_column(Parameters.DELTA_X, difference.get_values_of(Parameters.DELTA_X)).\
        add_column(Parameters.DELTA_Y, difference.get_values_of(Parameters.DELTA_Y))
