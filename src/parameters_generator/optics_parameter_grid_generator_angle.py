import parameters_generator.optics_parameter_grid_generator as opgg


def compute_d_x(x, delta_x, number_of_x_values,
                theta_x, delta_theta_x, number_of_theta_x_values,
                y, delta_y, number_of_y_values,
                theta_y, delta_theta_y, number_of_theta_y_values,
                ksi, delta_ksi, number_of_ksi_values,
                path_to_configuration, delta_ksi_multiplier=0.000001, number_of_processes=4):
    return opgg.compute_d_x(x-delta_x, x+delta_x, number_of_x_values,
                            theta_x-delta_theta_x, theta_x+delta_theta_x, number_of_theta_x_values,
                            y - delta_y, y + delta_y, number_of_y_values,
                            theta_y - delta_theta_y, theta_y + delta_theta_y, number_of_theta_y_values,
                            ksi - delta_ksi, ksi + delta_ksi, number_of_ksi_values,
                            path_to_configuration, delta_ksi_multiplier, number_of_processes)


def compute_d_y(x, delta_x, number_of_x_values,
                theta_x, delta_theta_x, number_of_theta_x_values,
                y, delta_y, number_of_y_values,
                theta_y, delta_theta_y, number_of_theta_y_values,
                ksi, delta_ksi, number_of_ksi_values,
                path_to_configuration, delta_ksi_multiplier=0.000001, number_of_processes=4):
    return opgg.compute_d_y(x-delta_x, x+delta_x, number_of_x_values,
                            theta_x-delta_theta_x, theta_x+delta_theta_x, number_of_theta_x_values,
                            y - delta_y, y + delta_y, number_of_y_values,
                            theta_y - delta_theta_y, theta_y + delta_theta_y, number_of_theta_y_values,
                            ksi - delta_ksi, ksi + delta_ksi, number_of_ksi_values,
                            path_to_configuration, delta_ksi_multiplier, number_of_processes)


def compute_l_x(x, delta_x, number_of_x_values,
                theta_x, delta_theta_x, number_of_theta_x_values,
                y, delta_y, number_of_y_values,
                theta_y, delta_theta_y, number_of_theta_y_values,
                ksi, delta_ksi, number_of_ksi_values,
                path_to_configuration, delta_theta_multiplier=0.000001, number_of_processes=4):
    return opgg.compute_l_x(x-delta_x, x+delta_x, number_of_x_values,
                            theta_x-delta_theta_x, theta_x+delta_theta_x, number_of_theta_x_values,
                            y - delta_y, y + delta_y, number_of_y_values,
                            theta_y - delta_theta_y, theta_y + delta_theta_y, number_of_theta_y_values,
                            ksi - delta_ksi, ksi + delta_ksi, number_of_ksi_values,
                            path_to_configuration, delta_theta_multiplier, number_of_processes)


def compute_l_y(x, delta_x, number_of_x_values,
                theta_x, delta_theta_x, number_of_theta_x_values,
                y, delta_y, number_of_y_values,
                theta_y, delta_theta_y, number_of_theta_y_values,
                ksi, delta_ksi, number_of_ksi_values,
                path_to_configuration, delta_theta_multiplier=0.000001, number_of_processes=4):
    return opgg.compute_l_y(x-delta_x, x+delta_x, number_of_x_values,
                            theta_x-delta_theta_x, theta_x+delta_theta_x, number_of_theta_x_values,
                            y - delta_y, y + delta_y, number_of_y_values,
                            theta_y - delta_theta_y, theta_y + delta_theta_y, number_of_theta_y_values,
                            ksi - delta_ksi, ksi + delta_ksi, number_of_ksi_values,
                            path_to_configuration, delta_theta_multiplier, number_of_processes)


def compute_v_x(x, delta_x, number_of_x_values,
                theta_x, delta_theta_x, number_of_theta_x_values,
                y, delta_y, number_of_y_values,
                theta_y, delta_theta_y, number_of_theta_y_values,
                ksi, delta_ksi, number_of_ksi_values,
                path_to_configuration, delta_x_multiplier=0.000001, number_of_processes=4):
    return opgg.compute_v_x(x-delta_x, x+delta_x, number_of_x_values,
                            theta_x-delta_theta_x, theta_x+delta_theta_x, number_of_theta_x_values,
                            y - delta_y, y + delta_y, number_of_y_values,
                            theta_y - delta_theta_y, theta_y + delta_theta_y, number_of_theta_y_values,
                            ksi - delta_ksi, ksi + delta_ksi, number_of_ksi_values,
                            path_to_configuration, delta_x_multiplier, number_of_processes)


def compute_v_y(x, delta_x, number_of_x_values,
                theta_x, delta_theta_x, number_of_theta_x_values,
                y, delta_y, number_of_y_values,
                theta_y, delta_theta_y, number_of_theta_y_values,
                ksi, delta_ksi, number_of_ksi_values,
                path_to_configuration, delta_y_multiplier=0.000001, number_of_processes=4):
    return opgg.compute_v_y(x-delta_x, x+delta_x, number_of_x_values,
                            theta_x-delta_theta_x, theta_x+delta_theta_x, number_of_theta_x_values,
                            y - delta_y, y + delta_y, number_of_y_values,
                            theta_y - delta_theta_y, theta_y + delta_theta_y, number_of_theta_y_values,
                            ksi - delta_ksi, ksi + delta_ksi, number_of_ksi_values,
                            path_to_configuration, delta_y_multiplier, number_of_processes)
