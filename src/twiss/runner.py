import ptc_track.runner as mr
import numpy as np
from concurrent.futures import ProcessPoolExecutor
from twiss.madx_script_generator import generate_configuration_file
from utils import working_directory
import os


def transport(madx_configuration, dataset):
    """
    Transport particles using twiss
    :param madx_configuration:
    :param dataset:
    :return:
    """
    result_matrix = np.empty((0, 30))
    number_of_workers = 4
    with ProcessPoolExecutor(number_of_workers) as executor:
        futures = []
        for i, raw_row in enumerate(dataset):
            processed_row = process_row(raw_row)
            futures.append(executor.submit(run_worker, madx_configuration, processed_row, i))

        for future in futures:
            result_matrix = np.append(result_matrix, future.result(), axis=0)
    return result_matrix


def run_worker(madx_configuration, row, process_number):
    current_directory = os.getcwd()
    working_directory_name = os.path.join(current_directory, "twiss" + str(process_number))
    begin_directory = working_directory.create_and_get_into(working_directory_name)
    path_to_madx_script = generate_configuration_file(madx_configuration, row)
    mr.__run_madx(path_to_madx_script)
    matrix = read_in_twiss_output_file("twiss_output")
    matrix_with_pt = np.append(matrix, np.full((matrix.shape[0], 1), row["pt"]), axis=1)
    working_directory.leave_and_delete(begin_directory)
    return matrix_with_pt


def process_row(raw_row):
    row = {
        "x": raw_row[0],
        "theta x": raw_row[1],
        "y": raw_row[2],
        "theta y": raw_row[3],
        "pt": raw_row[4]
    }
    return row


def read_in_twiss_output_file(file_name):
    with open(file_name) as file_object:
        # skip header
        line = file_object.readline()
        while line[0] != "*":
            line = file_object.readline()
        parameters = line.split()
        parameters = parameters[1:]
        # skip '*'
        file_object.readline()
        number_of_positions = 43
        columns_number = len(parameters)
        values_vector = np.fromfile(file_object, count=number_of_positions * columns_number, sep=" ")
        matrix = np.reshape(values_vector, (number_of_positions, columns_number))
        return matrix



