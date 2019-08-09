import madx.runner as mr
import data.particles_generator as pg
import numpy as np


def generate_parameters_from_dataset(madx_configuration, bunch_configuration):
    data = pg.generate_from_range(bunch_configuration)
    result_matrix = np.empty((0, 14))
    for raw_row in data:
        row = process_row(raw_row)
        path_to_madx_script = generate_configuration_file(madx_configuration, row)
        mr.__run_madx(path_to_madx_script)
        matrix = read_in_twiss_output_file("twiss_output")
        matrix_with_pt = np.append(matrix, np.full((matrix.shape[0], 1), row["pt"]), axis=1)
        result_matrix = np.append(result_matrix, matrix_with_pt, axis=0)
    return result_matrix


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
        number_of_positions = 49
        columns_number = len(parameters)
        values_vector = np.fromfile(file_object, count=number_of_positions * columns_number, sep=" ")
        matrix = np.reshape(values_vector, (number_of_positions, columns_number))
        return matrix


def generate_configuration_file(madx_configuration, row):
    file_name = "twiss_madx_script"
    with open(file_name, "w") as file_object:
        file_object.write("x = " + str(row["x"]) + ";\n")
        file_object.write("theta_x = " + str(row["theta x"]) + ";\n")
        file_object.write("y = " + str(row["y"]) + ";\n")
        file_object.write("theta_y = " + str(row["theta y"]) + ";\n")
        file_object.write("pt = " + str(row["pt"]) + ";\n")
        with open(madx_configuration.path_to_madx_script) as source_file_object:
            for line in source_file_object:
                file_object.write(line)
    return file_name
