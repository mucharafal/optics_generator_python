import ptc_track.runner as mr
import numpy as np
from concurrent.futures import ProcessPoolExecutor
from ptc_twiss.madx_script_generator import generate_configuration_file
from utilities import working_directory
import os
from data.parameters_names import ParametersNames as Parameters


def transport(madx_configuration, dataset):
    """
    Transport particles using ptc_twiss
    :param madx_configuration: configuration for run madx with ptc_twiss command
    :type madx_configuration: TwissConfiguration
    :param dataset: matrix with columns: x, theta x, y, theta y, pt
    :type dataset: np.array
    :return: matrix returned by ptc_twiss- results from processing next lines of
    """
    result_matrix = None
    number_of_workers = 4
    with ProcessPoolExecutor(number_of_workers) as executor:
        futures = []
        for i, raw_row in enumerate(dataset):
            processed_row = process_row(raw_row)
            futures.append(executor.submit(run_worker, madx_configuration, processed_row, i))
        for future in futures:
            result_matrix = future.result() if result_matrix is None else \
                np.append(result_matrix, future.result(), axis=0)
    return result_matrix


def run_worker(madx_configuration, row, process_number):
    # Create and get into working directory
    current_directory = os.getcwd()
    working_directory_name = os.path.join(current_directory, "twiss" + str(process_number))
    begin_directory = working_directory.create_and_get_into(working_directory_name)

    path_to_madx_script = generate_configuration_file(madx_configuration, row)

    mr.__run_madx(path_to_madx_script)

    matrix = read_in_twiss_output_file("twiss_output")
    matrix_with_pt = np.append(matrix, np.full((matrix.shape[0], 1), row[Parameters.PT]), axis=1)
    working_directory.leave_and_delete(begin_directory)

    return matrix_with_pt


def process_row(raw_row):
    row = {
        Parameters.X: raw_row[0],
        Parameters.THETA_X: raw_row[1],
        Parameters.Y: raw_row[2],
        Parameters.THETA_Y: raw_row[3],
        Parameters.PT: raw_row[4]
    }
    return row


def read_in_twiss_output_file(file_name):
    with open(file_name) as file_object:
        # skip header
        line = file_object.readline()
        while line[0] != "*":
            line = file_object.readline()
        # Line with * has types of columns
        parameters = line.split()
        parameters = parameters[1:]
        # skip '*'
        file_object.readline()

        matrix = None
        columns_number = len(parameters)
        values_vector = np.fromfile(file_object, count=columns_number, sep=" ")
        while len(values_vector) > 0:
            matrix = np.append(matrix, values_vector.reshape((-1, columns_number)), axis=0) if \
                matrix is not None else \
                values_vector.reshape((-1, columns_number))
            values_vector = np.fromfile(file_object, count=columns_number, sep=" ")

        return matrix



