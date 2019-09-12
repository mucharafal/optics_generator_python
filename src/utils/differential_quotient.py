import numpy as np

columns_mapping = {
    "x": 0,
    "theta x": 1,
    "y": 2,
    "theta y": 3,
    "pt": 4
}


def compute_optical_function(universal_transporter, particles, delta_parameter_name, transported_parameter_name,
                             delta_alternative_value):
    """
    (x2 - x1) / delta_x
    :param universal_transporter: has to take and return numpy array with columns x, theta x, y, theta y, pt
    :param particles: numpy array with columns: x, theta x, y, theta y, pt
    :param delta_parameter_name: names has to be compatible with mapping
    :param transported_parameter_name: as above
    :param delta_alternative_value: value used if standard way of computing delta return 0
    :return:
    """
    particles_copy = np.copy(particles)
    x1 = universal_transporter(particles_copy).T[columns_mapping[transported_parameter_name]]
    delta_x = compute_delta(particles_copy, delta_parameter_name, delta_alternative_value)
    particles_copy.T[columns_mapping[delta_parameter_name]] += delta_x
    x2 = universal_transporter(particles_copy).T[columns_mapping[transported_parameter_name]]
    print(x2.shape)
    optical_function = compute_differential(x2, x1, delta_x)
    particles_with_optical_function = add_column_to(particles, optical_function)
    return particles_with_optical_function


def compute_delta(particles, delta_parameter_name, alternative_value):
    """
    (x_max - x_min) * 1e-5 or alternative value
    :param particles:
    :param delta_parameter_name:
    :param alternative_value: return if delta is equal to zero
    :return:
    """
    x = particles.T[columns_mapping[delta_parameter_name]]
    x_min = np.min(x)
    x_max = np.max(x)
    delta_x = (x_max - x_min) * 1e-5
    return delta_x if delta_x > 0 else alternative_value


def compute_differential(vector1, vector2, delta_x):
    return (vector1 - vector2) / delta_x


def add_column_to(matrix, column):
    print(matrix.shape)
    print(column.shape)
    return np.append(matrix, np.reshape(column, (-1, 1)), axis=1)

