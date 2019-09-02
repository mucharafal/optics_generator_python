import ptc_track.particles_trajectory_generator as ptc_twiss_transporter
import ptc_track.madx_configuration as track_conf
from ptc_track.matrix_indexes import ptc_track as index_map
import numpy as np
import ROOT
from concurrent.futures import ProcessPoolExecutor
import data.bunch_configuration as buc
import utils.root_initializer as root_initializer
import models.approximator as stub_app
import xml.etree.ElementTree as ET
import data.particles_generator as pg


def train_prototype(bunch_configuration, madx_configuration, path_to_project):
    root_initializer.initialise(path_to_project)

    madx_input, madx_output = generate_training_dataset(madx_configuration, bunch_configuration)

    approximators = train_approximators(madx_input, madx_output.T, [7, 7, 7, 7, 7])

    return stub_app.Approximator(approximators)


def train_from_xml_configuration(path_to_optics, path_to_xml_file, number_of_item, path_to_sources):
    root_initializer.initialise(path_to_sources)

    # Import configuration of approximator from XML file
    tree = ET.parse(path_to_xml_file)  # load configuration from xml file
    root = tree.getroot()
    station_configuration = root[number_of_item].attrib

    polynomial_type = get_polynomial_type(station_configuration)
    max_pt_degree = [
        int(station_configuration["max_degree_x"]),
        int(station_configuration["max_degree_tx"]),
        int(station_configuration["max_degree_y"]),
        int(station_configuration["max_degree_ty"])
    ]

    # Generate data for approximator
    madx_configuration = track_conf.TrackConfiguration(path_to_xml_file, number_of_item, path_to_optics)
    bunch_configuration = get_bunch_configuration_from(station_configuration)
    madx_input, madx_output = generate_training_dataset(madx_configuration, bunch_configuration)

    # Train approximators (TMultiDimFit_wrapper)
    approximators = train_approximators(madx_input, madx_output.T, max_pt_degree)

    from ROOT import LHCOpticsApproximator
    from ROOT import TMultiDimFet

    # Get rid of additional data from TMultiDimFit and map it to TMultiDimFet
    new_approximators = {
        "x": TMultiDimFet(approximators["x"]),
        "theta x": TMultiDimFet(approximators["theta x"]),
        "y": TMultiDimFet(approximators["y"]),
        "theta y": TMultiDimFet(approximators["theta y"])
    }

    # Create LHCOpticsApproximator
    approximator = LHCOpticsApproximator(station_configuration["optics_parametrisation_name"],
                                         station_configuration["optics_parametrisation_name"],
                                         polynomial_type, station_configuration["beam"],
                                         float(station_configuration["nominal_beam_energy"]),
                                         new_approximators["x"],
                                         new_approximators["theta x"],
                                         new_approximators["y"],
                                         new_approximators["theta y"])

    return approximator


def generate_training_dataset(madx_configuration, bunch_configuration):
    # Generate beginning positions
    input_matrix = pg.generate_particles_randomly(bunch_configuration)

    output_segments = ptc_twiss_transporter.transport(madx_configuration, input_matrix)

    output_matrix = output_segments["end"]

    # If there are lost particles in output, get rid off this particles from input matrix
    indexes = output_matrix.T[0].astype(int) - 1
    input_without_lost = input_matrix[indexes]

    madx_input = input_without_lost
    madx_output = get_position_parameters_from_madx_format(output_matrix)

    return madx_input, madx_output


def get_polynomial_type(configuration):
    if configuration["polynomials_type"] == "kMonomials":
        return 0
    elif configuration["polynomials_type"] == "kChebyshev":
        return 1
    elif configuration["polynomials_type"] == "kLegendre":
        return 2
    # default
    return 0


def get_position_parameters_from_madx_format(matrix):
    x = matrix.T[index_map["x"]]
    theta_x = matrix.T[index_map["theta x"]]
    y = matrix.T[index_map["y"]]
    theta_y = matrix.T[index_map["theta y"]]
    pt = matrix.T[index_map["pt"]]

    return np.array([x, theta_x, y, theta_y, pt])


def train_approximators(input_matrix, output_matrix, max_pt_powers):
    x_output = output_matrix.T[0]
    theta_x_output = output_matrix.T[1]
    y_output = output_matrix.T[2]
    theta_y_output = output_matrix.T[3]

    output_vectors = [x_output, theta_x_output, y_output, theta_y_output]

    number_of_parameters = len(output_vectors)

    number_of_processes = 2

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
    from ROOT import TMultiDimFet
    from ROOT import TMultiDimFit_wrapper

    parameters_number = 5
    rows_number = input_matrix.shape[1]

    approximator = TMultiDimFit_wrapper(parameters_number, 0, ROOT.option)

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


def get_bunch_configuration_from(configuration):
    return buc.BunchConfiguration(
        float(configuration["x_min"]), float(configuration["x_max"]), 1,
        float(configuration["theta_x_min"]), float(configuration["theta_x_max"]), 1,
        float(configuration["y_min"]), float(configuration["y_max"]), 1,
        float(configuration["theta_y_min"]), float(configuration["theta_y_max"]), 1,
        float(configuration["ksi_min"]), float(configuration["ksi_max"]), int(configuration["tot_entries_number"])
    )


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