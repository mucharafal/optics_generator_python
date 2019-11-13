import transporters.ptc_track.madx_script_generator as msg
import xml_parser.approximator_training_configuration as xml_parser
import transporters.ptc_track.optical_functions as optical_functions_module
import transporters.ptc_track.transporter as transporter_module


class PtcTrackConfiguration:
    def __init__(self, approximator_transport_configuration, coordinates="canonical"):
        self.approximator_transport_configuration = approximator_transport_configuration
        self.coordinates = coordinates

    def generate_madx_script(self, number_of_particles):
        return msg.generate_madx_script(self.approximator_transport_configuration, number_of_particles)

    @staticmethod
    def get_track_configuration_from_xml_file(path_to_xml_file, item_number, coordinates="canonical"):
        approximator_configuration = xml_parser.get_approximator_configurations_from(path_to_xml_file)[item_number]
        approximator_transport_configuration = approximator_configuration.transport_configuration
        return PtcTrackConfiguration(approximator_transport_configuration, coordinates)

    def get_configuration(self):
        return self

    @staticmethod
    def get_module_with_optical_functions():
        return optical_functions_module

    @staticmethod
    def get_module_transporter():
        return transporter_module
