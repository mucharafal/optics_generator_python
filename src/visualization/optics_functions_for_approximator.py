import data.particles_generator as pg
import approximator.run_approximator as ra


def compute_v_x(approximator,
                x_min, x_max, number_of_x_values,
                theta_x, y, theta_y, t, pt):
    begin_positions = pg.generate_from_range(x_min, x_max, number_of_x_values,
                                             theta_x, theta_x, 1,
                                             y, y, 1,
                                             theta_y, theta_y, 1,
                                             t, t, 1,
                                             pt, pt, 1)
    potential_delta = 0.000001 * (x_max - x_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x_min + delta, x_max + delta, number_of_x_values,
                                                     theta_x, theta_x, 1,
                                                     y, y, 1,
                                                     theta_y, theta_y, 1,
                                                     t, t, 1,
                                                     pt, pt, 1)
    end_positions = ra.transport(approximator, begin_positions)
    shifted_end_positions = ra.transport(approximator, shifted_begin_positions)

    x_end_positions = __get_vector_of("x", end_positions)
    x_shifted_end_positions = __get_vector_of("x", shifted_end_positions)

    x_begin_positions = __get_vector_of("x", begin_positions)

    v_x = (x_shifted_end_positions - x_end_positions) / delta
    return x_begin_positions, v_x


def compute_v_y(approximator,
                x, theta_x,
                y_min, y_max, number_of_y_values,
                theta_y, t, pt):
    begin_positions = pg.generate_from_range(x, x, 1,
                                             theta_x, theta_x, 1,
                                             y_min, y_max, number_of_y_values,
                                             theta_y, theta_y, 1,
                                             t, t, 1,
                                             pt, pt, 1)
    potential_delta = 0.000001 * (y_max - y_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x, x, 1,
                                                     theta_x, theta_x, 1,
                                                     y_min + delta, y_max + delta, number_of_y_values,
                                                     theta_y, theta_y, 1,
                                                     t, t, 1,
                                                     pt, pt, 1)
    end_positions = ra.transport(approximator, begin_positions)
    shifted_end_positions = ra.transport(approximator, shifted_begin_positions)

    y_end_positions = __get_vector_of("y", end_positions)
    y_shifted_end_positions = __get_vector_of("y", shifted_end_positions)

    y_begin_positions = __get_vector_of("y", begin_positions)

    v_y = (y_shifted_end_positions - y_end_positions) / delta
    return y_begin_positions, v_y


def compute_l_y(approximator,
                x, theta_x,
                y, theta_y_min, theta_y_max, number_of_theta_y_values,
                t, pt):
    begin_positions = pg.generate_from_range(x, x, 1,
                                             theta_x, theta_x, 1,
                                             y, y, 1,
                                             theta_y_min, theta_y_max, number_of_theta_y_values,
                                             t, t, 1,
                                             pt, pt, 1)
    potential_delta = 0.000001 * (theta_y_max - theta_y_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x, x, 1,
                                                     theta_x, theta_x, 1,
                                                     y, y, 1,
                                                     theta_y_min + delta, theta_y_max + delta, number_of_theta_y_values,
                                                     t, t, 1,
                                                     pt, pt, 1)
    end_positions = ra.transport(approximator, begin_positions)
    shifted_end_positions = ra.transport(approximator, shifted_begin_positions)

    y_end_positions = __get_vector_of("y", end_positions)
    y_shifted_end_positions = __get_vector_of("y", shifted_end_positions)

    theta_y_begin_positions = __get_vector_of("theta y", begin_positions)

    l_y = (y_shifted_end_positions - y_end_positions) / delta
    return theta_y_begin_positions, l_y


def compute_l_x(approximator,
                x, theta_x_min, theta_x_max, number_of_theta_x_values,
                y, theta_y,
                t, pt):
    begin_positions = pg.generate_from_range(x, x, 1,
                                             theta_x_min, theta_x_max, number_of_theta_x_values,
                                             y, y, 1,
                                             theta_y, theta_y, 1,
                                             t, t, 1,
                                             pt, pt, 1)
    potential_delta = 0.000001 * (theta_x_max - theta_x_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x, x, 1,
                                                     theta_x_min + delta, theta_x_max + delta, number_of_theta_x_values,
                                                     y, y, 1,
                                                     theta_y, theta_y, 1,
                                                     t, t, 1,
                                                     pt, pt, 1)
    end_positions = ra.transport(approximator, begin_positions)
    shifted_end_positions = ra.transport(approximator, shifted_begin_positions)

    x_end_positions = __get_vector_of("x", end_positions)
    x_shifted_end_positions = __get_vector_of("x", shifted_end_positions)

    theta_x_begin_positions = __get_vector_of("theta x", begin_positions)

    l_x = (x_shifted_end_positions - x_end_positions) / delta
    return theta_x_begin_positions, l_x


def compute_d_x(approximator,
                x, theta_x, y, theta_y, t, pt_min, pt_max, number_of_pt_values):
    begin_positions = pg.generate_from_range(x, x, 1,
                                             theta_x, theta_x, 1,
                                             y, y, 1,
                                             theta_y, theta_y, 1,
                                             t, t, 1,
                                             pt_min, pt_max, number_of_pt_values)
    potential_delta = 0.000001 * (pt_max - pt_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x, x, 1,
                                                     theta_x, theta_x, 1,
                                                     y, y, 1,
                                                     theta_y, theta_y, 1,
                                                     t, t, 1,
                                                     pt_min + delta, pt_max + delta, 1)
    end_positions = ra.transport(approximator, begin_positions)
    shifted_end_positions = ra.transport(approximator, shifted_begin_positions)

    x_end_positions = __get_vector_of("x", end_positions)
    x_shifted_end_positions = __get_vector_of("x", shifted_end_positions)

    pt_begin_positions = __get_vector_of("pt", begin_positions)

    d_x = (x_shifted_end_positions - x_end_positions) / delta
    return pt_begin_positions, d_x


def compute_d_y(approximator,
                x, theta_x, y, theta_y, t, pt_min, pt_max, number_of_pt_values):
    begin_positions = pg.generate_from_range(x, x, 1,
                                             theta_x, theta_x, 1,
                                             y, y, 1,
                                             theta_y, theta_y, 1,
                                             t, t, 1,
                                             pt_min, pt_max, number_of_pt_values)
    potential_delta = 0.000001 * (pt_max - pt_min)
    delta = potential_delta if potential_delta > 0 else 0.0000001
    shifted_begin_positions = pg.generate_from_range(x, x, 1,
                                                     theta_x, theta_x, 1,
                                                     y, y, 1,
                                                     theta_y, theta_y, 1,
                                                     t, t, 1,
                                                     pt_min + delta, pt_max + delta, 1)
    end_positions = ra.transport(approximator, begin_positions)
    shifted_end_positions = ra.transport(approximator, shifted_begin_positions)

    y_end_positions = __get_vector_of("y", end_positions)
    y_shifted_end_positions = __get_vector_of("y", shifted_end_positions)

    pt_begin_positions = __get_vector_of("pt", begin_positions)

    d_y = (y_shifted_end_positions - y_end_positions) / delta
    return pt_begin_positions, d_y


def __get_vector_of(column_name, matrix):
    columns_mapping = {
        "x": 0,
        "theta x": 1,
        "y": 2,
        "theta y": 3,
        "t": 4,
        "pt": 5
    }
    index = columns_mapping[column_name]
    return matrix.T[index]
