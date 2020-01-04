from data.particles import CanonicalCoordinates
import pandas


def read_in(file_name, *columns_parameters):
    """
    Read in csv file in format like from page https://apps.automeris.io/wpd/
    Numbers separator is ";", decimal point is ","
    :param file_name: name of file to read in
    :param columns_parameters: names of columns
    :type columns_parameters: data.parameters_names.ParametersNames
    :return: Particles object with columns like
    """
    matrix = __read_in_matrix(file_name)
    mapping = __generate_mapping(columns_parameters)
    return CanonicalCoordinates(matrix, mapping)


def __read_in_matrix(file_name):
    pandas_data_frame = pandas.read_csv(file_name, sep=";", header=None, decimal=",")
    numpy_matrix = pandas_data_frame.values
    return numpy_matrix


def __generate_mapping(columns_names):
    mapping = {columns_names[index]: index for index in range(len(columns_names))}
    return mapping
