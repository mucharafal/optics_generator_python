import madx.particles_trajectory_generator as ptg
from madx.matrix_indexes import index_map
import numpy as np
from ROOT import TMultiDimFit


def train():
    # todo Outdate, WIP
    path_to_configuration = "/home/rafalmucha/Pobrane/optic/s/"
    # Parameters of bunch

    configuration = get_configuration()

    x_angle_min = 0.0000
    x_angle_max = 0.0000
    y_angle_min = 0.0000
    y_angle_max = 0.000

    number_of_particles_in_one_run = 10000
    target = 10000

    output = ptg.generate_random_particles(configuration, {"x_min": x_angle_min, "x_max": x_angle_max, "y_min": y_angle_min,
                                                    "y_max": y_angle_max}, path_to_configuration, target,
                                           number_of_particles_in_one_run)

    input_parameters = ["x", "theta x", "y", "theta y"]

    approximator = TMultiDimFit(len(input_parameters), TMultiDimFit.kChebyshev)
    mPowers = np.array([2, 4, 2, 4], dtype=np.int32)
    approximator.SetMaxPowers(mPowers)
    approximator.SetMaxFunctions(200)
    approximator.SetMaxStudy(220)
    approximator.SetMaxTerms(200)
    approximator.SetPowerLimit(1.8)
    approximator.SetMinRelativeError(1e-13)

    output_matrix = output["end"]
    input_matrix = output["start"]
    print("piora")
    sample_size = len(output["end"])
    for counter in range(sample_size):
        index_in_input_matrix = int(output_matrix[counter][0]) - 1
        input_row = process_input_row(input_matrix[index_in_input_matrix], input_parameters)
        # print("Hola")
        # print(input_row)
        approximator.AddRow(input_row, output_matrix[counter][2], 0)
        # print("ole")

    print("start")
    approximator.FindParameterization()
    print("end")
    return approximator


def process_input_row(row, parameters):
    new_row = list()
    for parameter in parameters:
        index = index_map[parameter]
        new_row.append(row[index])
    return np.array(new_row)


def get_configuration():
    x_mean = 0.0
    sigma_x = 0.0002
    theta_x_mean = 0.000
    sigma_theta_x = 0.000003
    y_mean = 0.0
    sigma_y = 0.0002
    theta_y_mean = 0.00
    sigma_theta_y = 0.000003
    t_mean = 0
    sigma_t = 0
    pt_mean = 0
    sigma_pt = 0

    configuration = dict()

    configuration["x_min"] = x_mean - sigma_x
    configuration["x_max"] = x_mean + sigma_x
    configuration["y_min"] = y_mean - sigma_y
    configuration["y_max"] = y_mean + sigma_y
    configuration["t_min"] = t_mean - sigma_t
    configuration["t_max"] = t_mean + sigma_t

    configuration["theta_x_min"] = theta_x_mean - sigma_theta_x
    configuration["theta_x_max"] = theta_x_mean + sigma_theta_x
    configuration["theta_y_min"] = theta_y_mean - sigma_theta_y
    configuration["theta_y_max"] = theta_y_mean + sigma_theta_y
    configuration["pt_min"] = pt_mean - sigma_pt
    configuration["pt_max"] = pt_mean + sigma_pt

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


def __run_test(approximator):
    path_to_configuration = "/home/rafalmucha/Pobrane/optic/s/"
    # Parameters of bunch

    configuration = get_configuration()

    x_angle_min = 0.0000
    x_angle_max = 0.0000
    y_angle_min = 0.0000
    y_angle_max = 0.000

    number_of_particles_in_one_run = 1000
    target = 1000

    output = ptg.generate_random_particles(configuration, {"x_min": x_angle_min, "x_max": x_angle_max, "y_min": y_angle_min,
                                                    "y_max": y_angle_max}, path_to_configuration, target,
                                           number_of_particles_in_one_run)

    input_parameters = ["x", "theta x", "y", "theta y"]

    output_matrix = output["end"]
    output_vector = output_matrix.T[2]
    input_matrix = output["start"]
    input_indexes = np.array([index_map[x] for x in input_parameters])
    print(input_indexes)
    input_matrix = input_matrix.T[input_indexes]
    print(input_matrix.shape)
    return test(approximator, input_matrix.T, output_vector)
