import ptc_track.particles_trajectory_generator as ptg
from ptc_track.matrix_indexes import ptc_track as index_map
import numpy as np
import ROOT
from concurrent.futures import ProcessPoolExecutor
import data.bunch_configuration as buc
import utils.root_initializer as ri
import models.approximator as stub_app


def train_prototype(bunch_configuration, madx_configuration, path_to_project):
    ri.initialise(path_to_project)

    particles = ptg.generate_random_particles(madx_configuration, bunch_configuration,
                                              bunch_configuration.get_number_of_particles())

    output_matrix = particles["end"]
    input_matrix = particles["start"]

    indexes = output_matrix.T[0].astype(int) - 1
    input_without_lost = input_matrix[indexes]

    madx_input = get_position_parameters_from_madx_format(input_without_lost)

    madx_output = get_position_parameters_from_madx_format(output_matrix)

    approximators = train_approximator(madx_input.T, madx_output.T, [7, 7, 7, 7, 7])

    return stub_app.Approximator(approximators)


def get_position_parameters_from_madx_format(matrix):
    x = matrix.T[index_map["x"]]
    theta_x = matrix.T[index_map["theta x"]]
    y = matrix.T[index_map["y"]]
    theta_y = matrix.T[index_map["theta y"]]
    pt = matrix.T[index_map["pt"]]

    return np.array([x, theta_x, y, theta_y, pt])


def train_approximator(input_matrix, output_matrix, max_pt_powers):
    x_output = output_matrix.T[0]
    theta_x_output = output_matrix.T[1]
    y_output = output_matrix.T[2]
    theta_y_output = output_matrix.T[3]

    output_vectors = [x_output, theta_x_output, y_output, theta_y_output]

    number_of_parameters = len(output_vectors)

    number_of_processes = 4

    with ProcessPoolExecutor(number_of_processes) as executor:
        futures = []
        for worker_number in range(number_of_parameters):
            futures.append(executor.submit(train_tmultidimfit,
                                           input_matrix.T, output_vectors[worker_number],
                                           max_pt_powers[worker_number]))

        approximators = {
            "x": futures[0].result(),
            "theta x": futures[1].result(),
            "y": futures[2].result(),
            "theta y": futures[3].result()
        }
    return approximators


def train_tmultidimfit(input_matrix, output_vector, max_pt_power):
    from ROOT import TMultiDimFit_wrapper
    from ROOT import TMultiDimFet

    parameters_number = 5
    rows_number = input_matrix.shape[1]

    approximator = TMultiDimFit_wrapper(parameters_number)

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

    approximator.FindParameterization()
    alternative_approximator = TMultiDimFet(approximator)

    return alternative_approximator


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