import transporters.madx.ptc_track.transporter as ptc_track_transporter
import ROOT
from concurrent.futures import ProcessPoolExecutor
import utils.root_initializer as root_initializer
import data.particles_generator as pg
from data.parameters_names import ParametersNames as Parameters
from transporters.madx.ptc_track.configuration import PtcTrackConfiguration


def train_from_configuration(configuration_object):
    """
    Train approximator defined in configuration_object. Return trained LHCOpticsApproximator object.
    For more details about approximator, please look into root_classes package.
    :param configuration_object: configuration object of training
    :type configuration_object: ApproximatorTrainingConfiguration
    :return: trained LHCOpticsApproximator object
    """
    root_initializer.initialise()

    # Generate data for approximator
    madx_configuration = PtcTrackConfiguration.get_track_configuration_from_xml_configuration_object(configuration_object.transport_configuration)
    training_sample_configuration = configuration_object.training_sample_configuration
    approximator_dataset, apertures_datasets = __generate_training_dataset(madx_configuration,
                                                                           training_sample_configuration)

    approximator_dataset.name = configuration_object.approximator_configuration.name_of_approximator

    approximator = __train_lhc_optics_approximator_with_apertures(configuration_object.approximator_configuration,
                                                                  configuration_object.apertures_configurations,
                                                                  approximator_dataset, apertures_datasets)

    return approximator


def __generate_training_dataset(madx_configuration, training_sample_configuration):
    # Generate beginning positions
    input_particles = pg.generate_particles_randomly(training_sample_configuration)

    output_segments = ptc_track_transporter.transport(madx_configuration, input_particles)

    approximator_segment_name = madx_configuration.end_place_name

    approximator_dataset = TrainingDataset(input_particles, output_segments["end"], approximator_segment_name)
    apertures_datasets = [TrainingDataset(input_particles, aperture_segment, aperture_name)
                          for aperture_name, aperture_segment in output_segments.items()
                          if aperture_name not in ["start", "end", approximator_segment_name, approximator_segment_name.upper()]]

    return approximator_dataset, apertures_datasets


class TrainingDataset:
    def __init__(self, input_particles, output_particles, name):
        self.input_particles = input_particles
        self.output_particles = output_particles
        self.name = name


def __train_lhc_optics_approximator_with_apertures(approximator_configuration, apertures_configurations,
                                                   approximator_training_dataset, apertures_training_datasets):
    approximator = __train_lhc_optics_approximator(approximator_configuration, approximator_training_dataset)

    apertures = [__train_lhc_optics_approximator(approximator_configuration, aperture_dataset)
                 for aperture_dataset in apertures_training_datasets]

    for aperture_configuration in apertures_configurations:
        print(aperture_configuration.name.upper())
        aperture = [aperture for aperture in apertures
                    if aperture_configuration.name.upper() == aperture.GetName().upper()][0]
        approximator.AddRectEllipseAperture(aperture, aperture_configuration.rect_rx, aperture_configuration.rect_ry,
                                            aperture_configuration.el_rx, aperture_configuration.el_ry)

    return approximator


def __train_lhc_optics_approximator(approximator_configuration, approximator_training_dataset):
    parameters_approximators = __train_approximators(approximator_training_dataset.input_particles,
                                                     approximator_training_dataset.output_particles,
                                                     approximator_configuration)

    # Create LHCOpticsApproximator

    approximator = __compose_lhc_optics_approximator(parameters_approximators, approximator_configuration,
                                                     approximator_training_dataset.name)

    return approximator


def __train_approximators(input_particles, output_particles, approximator_configuration):
    input_parameters = [Parameters.X, Parameters.THETA_X, Parameters.Y, Parameters.THETA_Y, Parameters.PT]
    input_vectors = [input_particles.get_column(parameter) for parameter in input_parameters]

    output_parameters = [Parameters.X, Parameters.THETA_X, Parameters.Y, Parameters.THETA_Y]

    number_of_processes = 4

    with ProcessPoolExecutor(number_of_processes) as executor:
        futures = []
        for parameter in output_parameters:
            output_vector = output_particles.get_column(parameter)
            parameter_configuration = [configuration for configuration in
                                       approximator_configuration.parameters_configurations
                                       if configuration.parameter == parameter][0]
            futures.append(executor.submit(__train_multidimensionalfitter,
                                           input_vectors, output_vector,
                                           parameter_configuration))

        approximators = {
            Parameters.X: futures[0].result(),
            Parameters.THETA_X: futures[1].result(),
            Parameters.Y: futures[2].result(),
            Parameters.THETA_Y: futures[3].result()
        }
    return approximators


def __train_multidimensionalfitter(input_vectors, output_vector, parameter_configuration):
    number_of_input_parameters = len(input_vectors)
    approximator = __initialize_multidimensionalfitter(number_of_input_parameters, parameter_configuration.max_degree)
    __insert_data_to_approximator(approximator, input_vectors, output_vector)
    approximator.FindParameterization(parameter_configuration.precision)
    return approximator


def __initialize_multidimensionalfitter(parameters_number, max_pt_power):
    # Need initialized ROOT (previous invoking utils.root_initializer.initialise)
    from ROOT import MultiDimensionalFitter

    approximator = MultiDimensionalFitter(parameters_number, 0, ROOT.option)

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

    return approximator


def __insert_data_to_approximator(approximator, input_vectors, expected_output):
    rows_number = len(expected_output)
    parameters_number = len(input_vectors)
    for counter in range(rows_number):
        for i in range(parameters_number):
            ROOT.x_in[i] = input_vectors[i][counter]

        approximator.AddRow(ROOT.x_in, expected_output[counter], 0)


def __compose_lhc_optics_approximator(approximators, approximator_configuration, approximator_name):
    from ROOT import LHCOpticsApproximator

    polynomial_type = __map_polynomial_type(approximator_configuration.polynomials_type)

    approximator = LHCOpticsApproximator(approximator_name, approximator_name,
                                         polynomial_type,
                                         approximator_configuration.beam_name,
                                         approximator_configuration.beam_energy,
                                         approximators[Parameters.X],
                                         approximators[Parameters.THETA_X],
                                         approximators[Parameters.Y],
                                         approximators[Parameters.THETA_Y])

    return approximator


def __map_polynomial_type(polynomial_type):
    mapping = {
        "kMonomials": 0,
        "kChebychev": 1,
        "kLegendre": 2
    }
    return mapping[polynomial_type] if polynomial_type in mapping else 0
