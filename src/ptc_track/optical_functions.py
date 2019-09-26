from data.parameters_names import ParametersNames as Parameters
import utils.differential_quotient as optical_function_as_differential


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

    particles_with_optical_function = optical_function_as_differential.\
        compute_optical_function(transporter, particles,
                                 delta_parameter_name, transported_parameter_name, delta_alternative_value)

    return particles_with_optical_function



