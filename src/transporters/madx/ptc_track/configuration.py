import transporters.madx.ptc_track.madx_script_generator as msg
import xml_parser.approximator_training_configuration as xml_parser
import transporters.madx.ptc_track.optical_functions as optical_functions_module
import transporters.madx.ptc_track.transporter as transporter_module
from transporters.madx.configuration import MadxConfiguration


class PtcTrackConfiguration(MadxConfiguration):
    def __init__(self, end_place_name,
                 end_place_distance,
                 start_place_name,
                 beam_name,
                 madx_input_script_file_name,
                 madx_output_script_file_name,
                 observed_places_names):
        super().__init__(end_place_name, end_place_distance, start_place_name, beam_name, madx_input_script_file_name)
        self.madx_output_script_file_name = madx_output_script_file_name
        self.observed_places_names = observed_places_names

    def generate_madx_script(self, number_of_particles):
        return msg.generate_madx_script(self, number_of_particles)

    @staticmethod
    def get_track_configuration_from_xml_file(path_to_xml_file, item_number):
        approximator_configuration = xml_parser.get_approximator_configurations_from(path_to_xml_file)[item_number]
        approximator_transport_configuration = approximator_configuration.transport_configuration
        return PtcTrackConfiguration.get_track_configuration_from_xml_configuration_object(approximator_transport_configuration)

    @staticmethod
    def get_track_configuration_from_xml_configuration_object(approximator_transport_configuration):
        atc = approximator_transport_configuration  # for shorter name
        return PtcTrackConfiguration(atc.end_place.name,
                                     atc.end_place.distance,
                                     atc.end_place.name_of_place_from,
                                     atc.end_place.beam,
                                     atc.madx_input_script_file_name,
                                     atc.madx_output_script_file_name,
                                     atc.observed_places_names)

    def get_configuration(self):
        return self

    @staticmethod
    def get_module_with_optical_functions():
        return optical_functions_module

    @staticmethod
    def get_module_transporter():
        return transporter_module
