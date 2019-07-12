import numpy as np
import xml.etree.ElementTree as ET
import os


def fit_polynomial(input_parameters, output_values):
    pseudo_vandermonde_matrix = calculate_polynomials(input_parameters)
    coefficients = np.linalg.lstsq(pseudo_vandermonde_matrix, output_values, rcond=None)
    return coefficients


def calculate_polynomials(input_values):

    return vandermonde_multi_dimensional(input_values)


def vandermonde_multi_dimensional(parameters):
    max_degree = 2
    begin_parameter = np.polynomial.polynomial.polyvander(parameters[0], max_degree)
    n = begin_parameter.shape[0]
    for parameter in parameters[1:]:
        temp = []
        for case in range(n):
            p = []
            # print(begin_parameter)
            for element in begin_parameter[case]:
                k = np.polynomial.polynomial.polyvander2d(element, parameter[case], [1, max_degree])
                # print(k.shape)
                without_redundant_columns = np.delete(k, range(0, int(k.shape[1]/2)), 1)
                p.append(without_redundant_columns)
            temp.append(np.array(p).reshape((-1,)))

        begin_parameter = np.array(temp)
    print(begin_parameter.shape)
    return begin_parameter


if __name__ == "__main__":
    """ for test only """
    x = np.array([1, 2, 3, 1, 2, 3, 5])
    y = np.array([1, 3, 9, 0, 0, 0, 0])
    z = np.array([0, 0, 0, 10, 10, 10, 10])
    x = fit_polynomial([x, y, z], x)
    print(x)


def load_configuration(path_to_configuration):
    """
    Load configuration from xml file, which name is given as argument
    :param path_to_configuration: path to configuration file in xml format
    :return: dictionary with configuration
    """
    tree = ET.parse(path_to_configuration)  # load configuration from xml file
    root = tree.getroot()
    configuration = root[0].attrib
    return configuration


def generate_particles(configuration, path):
    """
    Function to generate file part.in. Parameters of particles are taken from configuration. Every parameter whose
    values should be generated is describe by keys in configuration: parameter_name_min and parameter_name_max.
    Warn- non thread safe. Changes working directory.
    :param configuration: dictionary with needed parameters
    :param path: path to directory, where file part.in should be generated
    :return:
    """
    # Save current path.
    previous_path = os.getcwd()
    # Change for specified.
    os.chdir(path)

    # Get parameters from configuration
    number_of_particles = int(configuration['number_of_part_per_sample'])
    x_min = float(configuration['x_min'])
    x_max = float(configuration['x_max'])
    theta_x_min = float(configuration['px_min'])
    theta_x_max = float(configuration['px_max'])
    y_min = float(configuration['y_min'])
    y_max = float(configuration['y_max'])
    theta_y_min = float(configuration['py_min'])
    theta_y_max = float(configuration['py_max'])
    t_min = float(configuration['t_min'])
    t_max = float(configuration['t_max'])
    pt_min = float(configuration['pt_min'])
    pt_max = float(configuration['pt_max'])

    pg.generate_particles_randomly(x_min, x_max, theta_x_min, theta_x_max, y_min, y_max, theta_y_min, theta_y_max,
                                   t_min, t_max, pt_min, pt_max, number_of_particles)

    # Recover previous working path.
    os.chdir(previous_path)

