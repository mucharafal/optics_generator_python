import xml.etree.ElementTree as ET
from xml_parser.approximator_configuration import ApproximatorConfiguration
from data.grid_configuration import CanonicalCoordinatesGridConfiguration
from xml_parser.transport_configuration import TransportConfiguration
from xml_parser.aperture_configuration import ApertureConfiguration


class ApproximatorTrainingConfiguration:
    def __init__(self, approximator_configuration,
                 training_sample_configuration,
                 transport_configuration,
                 apertures_configurations,
                 destination_file_name):
        self.approximator_configuration = approximator_configuration
        self.training_sample_configuration = training_sample_configuration
        self.transport_configuration = transport_configuration
        self.apertures_configurations = apertures_configurations
        self.destination_file_name = destination_file_name

    @staticmethod
    def get_configuration_from(xml_configuration):
        approximator_configuration = ApproximatorConfiguration.get_configuration_from_xml(xml_configuration)
        training_sample_configuration = CanonicalCoordinatesGridConfiguration.\
            get_configuration_from_xml(xml_configuration)
        transport_configuration = TransportConfiguration.get_configuration_from_xml(xml_configuration)
        apertures_configurations = ApertureConfiguration.get_configurations_from_xml(xml_configuration)
        destination_file_name = xml_configuration.attrib["optics_parametrisation_file"]
        return ApproximatorTrainingConfiguration(approximator_configuration, training_sample_configuration,
                                                 transport_configuration, apertures_configurations,
                                                 destination_file_name)


def get_xml_configuration_from_file(path_to_xml_file):
    tree = ET.parse(path_to_xml_file)  # load configuration from xml file
    return tree.getroot()


def get_approximator_configurations_from(path_to_xml_file):
    configurations = get_xml_configuration_from_file(path_to_xml_file)
    approximator_configurations = [ApproximatorTrainingConfiguration.get_configuration_from(configuration)
                                   for configuration in configurations]
    return approximator_configurations
