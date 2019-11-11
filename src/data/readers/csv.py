from data.particles import Particles
import pandas


def read_in(file_name, *columns_parameters):
    matrix = __read_in_matrix(file_name)
    mapping = __generate_mapping(columns_parameters)
    return Particles(matrix, mapping)


def __read_in_matrix(file_name):
    pandas_data_frame = pandas.read_csv(file_name, sep=";", header=None, decimal=",")
    numpy_matrix = pandas_data_frame.values
    return numpy_matrix


def __generate_mapping(columns_names):
    mapping = {columns_names[index]: index for index in range(len(columns_names))}
    return mapping
