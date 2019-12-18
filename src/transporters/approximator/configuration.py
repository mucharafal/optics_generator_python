import transporters.approximator.runner as approximator_utils
import transporters.approximator.optical_functions as optical_functions_module
import transporters.approximator.transporter as approximator_transporter
import xml_parser.approximator_training_configuration as configuration_package
import os


class ApproximatorConfiguration:
    def __init__(self, path_to_root_file, name_of_approximator):
        self.approximator = approximator_utils.get_approximator(path_to_root_file, name_of_approximator)

    @staticmethod
    def get_from_xml_file(path_to_xml_file, approximator_number):
        configurations = configuration_package.get_approximator_configurations_from(path_to_xml_file)
        approximator_training_configuration = configurations[approximator_number]
        return ApproximatorConfiguration.get_from_xml_configuration_object(approximator_training_configuration,
                                                                           path_to_xml_file)

    @staticmethod
    def get_from_xml_configuration_object(approximator_training_configuration_object,
                                          path_to_xml_file):
        (path_to_folder_with_optics, xml_file_name) = os.path.split(path_to_xml_file)
        approximator_file_name = approximator_training_configuration_object.destination_file_name
        approximator_name = approximator_training_configuration_object.approximator_configuration.name_of_approximator
        path_to_root_file = os.path.join(path_to_folder_with_optics, approximator_file_name)
        return ApproximatorConfiguration(path_to_root_file, approximator_name)

    @staticmethod
    def get_module_with_optical_functions():
        return optical_functions_module

    @staticmethod
    def get_module_transporter():
        return approximator_transporter

    def get_configuration(self):
        return self.approximator
