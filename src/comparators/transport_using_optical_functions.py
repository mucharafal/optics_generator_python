import visualization.visualize as visualize
from data.parameters_names import ParametersNames as Parameters
from data.particles import Particles
import numpy as np
import transporters.transporters_factory as transporters_factory
import transporters.optical_functions_factory as optical_functions_factory


def compare_transport_by_optical_functions_with(particles, reference_transporter_configuration,
                                                optical_functions_base_configuration, transported_dimension,
                                                depended_value):
    particles_with_optical_functions = __get_optical_functions(particles, optical_functions_base_configuration)

    reference_transporter = transporters_factory.get_transporter(reference_transporter_configuration)
    particles_transported_using_reference_transporter = reference_transporter(particles)["end"]
    particles_transported_using_optical_function = __transport_using_optical_functions(particles_with_optical_functions,
                                                                                       reference_transporter)
    difference = __compute_difference(particles_transported_using_optical_function,
                                      particles_transported_using_reference_transporter)
    particles_and_difference = __append_difference(particles, difference)
    axes = visualize.plot_datasets(depended_value, Parameters.get_delta(transported_dimension), "Transporter",
                                   {"diff": particles_and_difference})
    return axes


def __get_optical_functions(particles, transporter_configuration):

    optical_functions = [Parameters.D_X, Parameters.D_Y, Parameters.L_X, Parameters.L_Y, Parameters.V_X, Parameters.V_Y]
    particles_with_optical_functions = particles
    for optical_function_name in optical_functions:
        optical_function = optical_functions_factory.get_optical_function(optical_function_name,
                                                                          transporter_configuration)
        optical_function_values = optical_function(particles).get_coordinates_of(optical_function_name)
        particles_with_optical_functions = particles_with_optical_functions.add_column(optical_function_name,
                                                                                       optical_function_values)

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
