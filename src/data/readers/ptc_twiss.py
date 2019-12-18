import numpy as np
from data.parameters_names import ParametersNames as Parameters
from data.particles import CanonicalCoordinates


def read_in_file(file_name):
    with open(file_name) as file_object:
        # skip header
        line_with_parameters = __skip_header(file_object)
        # Line with * has types of columns
        parameters_mapping = __process_line_with_parameters(line_with_parameters)
        # skip '*'
        file_object.readline()
        matrix = __get_matrix_from_file_object(file_object, len(parameters_mapping))

        return CanonicalCoordinates(matrix, parameters_mapping)


def __skip_header(file_object):
    line = file_object.readline()
    while line[0] != "*":
        line = file_object.readline()
    return line


def __process_line_with_parameters(line):
    parameters = line.split()
    parameters = parameters[1:]
    mapping = __get_mapping_from_parameters_list(parameters)
    return mapping


def __get_mapping_from_parameters_list(parameters_as_strings):
    mapping = {}
    for index in range(len(parameters_as_strings)):
        parameter_object = __map_string_to_parameter_object_if_possible(parameters_as_strings[index])
        mapping[parameter_object] = index

    return mapping


def __map_string_to_parameter_object_if_possible(string):
    mapping = __get_dict()
    if string in mapping:
        return mapping[string]
    else:
        return string


def __get_dict():
    """
    Return dict where:
    - key is name of column in ptc_twiss output file
    - value- appropriate ParametersNames value
    :return:
    """
    return {
        "X": Parameters.X,
        "Y": Parameters.Y,
        "PX": Parameters.THETA_X,
        "PY": Parameters.THETA_Y,
        "PT": Parameters.PT,
        "S": Parameters.S,
        "RE11": Parameters.V_X,
        "RE12": Parameters.L_X,
        "RE16": Parameters.D_X,
        "RE33": Parameters.V_Y,
        "RE34": Parameters.L_Y,
        "RE36": Parameters.D_Y,
        "DISP1": Parameters.D_X,
        "DISP3": Parameters.D_Y,
    }


def __get_matrix_from_file_object(file_object, number_of_columns):
    matrix = None
    values_vector = np.fromfile(file_object, count=number_of_columns, sep=" ")
    while len(values_vector) > 0:
        matrix = np.append(matrix, values_vector.reshape((-1, number_of_columns)), axis=0) if \
            matrix is not None else \
            values_vector.reshape((-1, number_of_columns))
        values_vector = np.fromfile(file_object, count=number_of_columns, sep=" ")
    return matrix
