from data.parameters_names import ParametersNames as Parameters
import utilities.differential_quotient as optical_function_calculator


def compute_v_x(transporter, particles):
    particles_with_optical_function = compute_optical_function(transporter, particles, Parameters.X, Parameters.X, 1e-5)

    return particles_with_optical_function


def compute_v_y(transporter, particles):
    particles_with_optical_function = compute_optical_function(transporter, particles, Parameters.Y, Parameters.Y, 1e-5)

    return particles_with_optical_function


def compute_l_x(transporter, particles):
    particles_with_optical_function = compute_optical_function(transporter, particles, Parameters.THETA_X, Parameters.X, 1e-5)

    return particles_with_optical_function


def compute_l_y(transporter, particles):
    particles_with_optical_function = compute_optical_function(transporter, particles, Parameters.THETA_Y, Parameters.Y, 1e-5)

    return particles_with_optical_function


def compute_d_x(transporter, particles):
    particles_with_optical_function = compute_optical_function(transporter, particles, Parameters.PT, Parameters.X, 1e-5)

    return particles_with_optical_function


def compute_d_y(transporter, particles):
    particles_with_optical_function = compute_optical_function(transporter, particles, Parameters.PT, Parameters.Y, 1e-5)
    return particles_with_optical_function


def compute_optical_function(transporter, particles, delta_parameter_name, transported_parameter_name,
                             delta_alternative_value):
    return optical_function_calculator.compute_optical_function(transporter, particles, delta_parameter_name,
                                                                transported_parameter_name, delta_alternative_value)


