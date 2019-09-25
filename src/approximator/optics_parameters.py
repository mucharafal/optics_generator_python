import approximator.particles_trajectory_generator as ptg
from data.parameters_names import ParametersNames as Parameters
import utils.differential_quotient as optical_function_calculator


def compute_v_x(approximator, particles):
    particles_with_optical_function = compute_optical_function(approximator, particles, Parameters.X, Parameters.X, 1e-5)

    return particles_with_optical_function


def compute_v_y(approximator, particles):
    particles_with_optical_function = compute_optical_function(approximator, particles, Parameters.Y, Parameters.Y, 1e-5)

    return particles_with_optical_function


def compute_l_x(approximator, particles):
    particles_with_optical_function = compute_optical_function(approximator, particles, Parameters.THETA_X, Parameters.X, 1e-5)

    return particles_with_optical_function


def compute_l_y(approximator, particles):
    particles_with_optical_function = compute_optical_function(approximator, particles, Parameters.THETA_Y, Parameters.Y, 1e-5)

    return particles_with_optical_function


def compute_d_x(approximator, particles):
    particles_with_optical_function = compute_optical_function(approximator, particles, Parameters.PT, Parameters.X, 1e-5)

    return particles_with_optical_function


def compute_d_y(approximator, particles):
    particles_with_optical_function = compute_optical_function(approximator, particles, Parameters.PT, Parameters.Y, 1e-5)
    return particles_with_optical_function


def compute_optical_function(approximator, particles, delta_parameter_name, transported_parameter_name, 
                             delta_alternative_value):
    transporter = get_transporter(approximator)
    return optical_function_calculator.compute_optical_function(transporter, particles, delta_parameter_name,
                                                                transported_parameter_name, delta_alternative_value)


def get_transporter(approximator):
    def transporter(particles):
        ptg.transport(approximator, particles)
    return transporter

