import ROOT
import data.particles_generator as pg
import numpy as np


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
    end_positions = transport_particles(approximator, begin_positions)
    shifted_end_positions = transport_particles(approximator, shifted_begin_positions)

    x_end_positions = get_vector_of("x", end_positions)
    x_shifted_end_positions = get_vector_of("x", shifted_end_positions)

    x_begin_positions = get_vector_of("x", begin_positions)

    v_x = (x_shifted_end_positions - x_end_positions) / delta
    return x_begin_positions, v_x


def get_vector_of(column_name, matrix):
    pass


def transport_particles(approximator, begin_positions):
    end_positions = list()
    for row in begin_positions:
        end_position = approximator.Transport(row)
        end_positions.append(end_position)
    return np.array(end_positions)
