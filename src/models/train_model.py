import madx.particles_trajectory_generator as ptg
from madx.matrix_indexes import index_map
import numpy as np
from ROOT import TMultiDimFit, gInterpreter, gSystem
import ROOT
from concurrent.futures import ProcessPoolExecutor
import os
import data.bunch_configuration as buc
import madx.madx_configuration as mac
import utils.root_initializer as ri
import utils.working_directory as working_directory


def train(bunch_configuration, madx_configuration, path_to_project):
    ri.initialise(path_to_project)

    particles = ptg.generate_random_particles(madx_configuration, bunch_configuration,
                                              bunch_configuration.get_number_of_particles())

    output_matrix = particles["end"]

    print(output_matrix)

    input_matrix = particles["start"]

    indexes = output_matrix.T[0].astype(int) - 1
    input_without_lost = input_matrix[indexes]

    madx_input = get_position_parameters_from_madx_format(input_without_lost)

    madx_output = get_position_parameters_from_madx_format(output_matrix)

    print("Madx run")

    approximators = train_approximator(madx_input.T, madx_output.T, "dir", [7, 7, 7, 7, 7])

    print("Trained")

    print(approximators["x"])



    print("Created")

    return approximators


def get_position_parameters_from_madx_format(matrix):
    x = matrix.T[index_map["x"]]
    theta_x = matrix.T[index_map["theta x"]]
    y = matrix.T[index_map["y"]]
    theta_y = matrix.T[index_map["theta y"]]
    pt = matrix.T[index_map["pt"]]

    return np.array([x, theta_x, y, theta_y, pt])


def train_approximator(input_matrix, output_matrix, working_directory_name, max_pt_powers):

    print(input_matrix.shape)

    working_path = os.path.join(os.getcwd(), working_directory_name)
    previous_directory = working_directory.create_and_get_into(working_path)

    x_output = output_matrix.T[0]
    print(x_output)
    theta_x_output = output_matrix.T[1]
    y_output = output_matrix.T[2]
    theta_y_output = output_matrix.T[3]

    output_vectors = [x_output, theta_x_output, y_output, theta_y_output]

    number_of_parameters = len(output_vectors)

    number_of_processes = 1

    with ProcessPoolExecutor(number_of_processes) as executor:
        futures = []
        for worker_number in range(number_of_parameters):
            worker_directory_name = "dir" + str(worker_number)
            futures.append(executor.submit(train_tmultidimfit,
                                           input_matrix.T, output_vectors[worker_number], worker_directory_name,
                                           max_pt_powers[worker_number]))

        print("ole")
        approximators = {
            "x": futures[0].result(),
            "theta x": futures[1].result(),
            "y": futures[2].result(),
            "theta y": futures[3].result()
        }
        print("Guappa")
    # lhc_optics_approximator = approximator.Approximator(approximators)
    print("start leaving")
    working_directory.leave_and_delete(previous_directory)

    return approximators


def train_tmultidimfit(input_matrix, output_vector, working_directory_name, max_pt_power):
    from ROOT import TMultiDimFet
    print(working_directory_name)

    parameters_number = 5
    rows_number = input_matrix.shape[1]

    working_path = os.path.join(os.getcwd(), working_directory_name)
    previous_directory = working_directory.create_and_get_into(working_path)

    approximator = TMultiDimFet(parameters_number, TMultiDimFit.kMonomials, ROOT.option)

    ROOT.mPowers[0] = 2
    ROOT.mPowers[1] = 4
    ROOT.mPowers[2] = 2
    ROOT.mPowers[3] = 4
    ROOT.mPowers[4] = max_pt_power

    approximator.SetMaxPowers(ROOT.mPowers)
    approximator.SetMaxFunctions(3000)
    approximator.SetMaxStudy(3000)
    approximator.SetMaxTerms(3000)
    approximator.SetPowerLimit(1.6)
    approximator.SetMinRelativeError(1e-13)

    for counter in range(rows_number):
        for i in range(parameters_number):
            ROOT.x_in[i] = input_matrix[i][counter]

        approximator.AddRow(ROOT.x_in, output_vector[counter], 0)

    print("Start param")
    approximator.FindParameterization(1e-8)
    print("End!. finally...")
    working_directory.leave_and_delete(previous_directory)
    print("Left")

    return approximator


def get_bunch_configuration():

    number_of_particles = 1000

    x_mean = 0.0
    sigma_x = 4e-3
    theta_x_mean = 0.000
    sigma_theta_x = 1.3e-3
    y_mean = 0.0
    sigma_y = 4e-3
    theta_y_mean = 0.00
    sigma_theta_y = 1.3e-3
    pt_mean = -0.15
    sigma_pt = 0.2

    configuration = buc.BunchConfiguration.from_sigma(
        x_mean, sigma_x, 1, theta_x_mean, sigma_theta_x, 1,
        y_mean, sigma_y, 1, theta_y_mean, sigma_theta_y, 1,
        pt_mean, sigma_pt, number_of_particles
    )

    return configuration


def get_madx_configuration():

    path_to_xml_file = "/home/rafalmucha/Pobrane/optic/2016/configuration_reconst_beam1.xml"
    item_number = 0
    path_to_configuration = "/home/rafalmucha/Pobrane/optic/2016/"

    return mac.MadxConfiguration(path_to_xml_file, item_number, path_to_configuration)


def test(approximator, input_matrix, output_row):
    errors = list()
    for index, input_row in enumerate(input_matrix):
        input_row = np.array(input_row)
        print(input_row.shape)
        approximated_value = approximator.Eval(input_row)
        error = abs(approximated_value - output_row[index])
        print(error)
        errors.append(error)

    return errors


def __run_test():
    # Parameters of bunch

    bunch_configuration = get_bunch_configuration()

    madx_configuration = get_madx_configuration()

    approximators = train(bunch_configuration, madx_configuration)

    return approximators


if __name__ == "__main__":
    __run_test()