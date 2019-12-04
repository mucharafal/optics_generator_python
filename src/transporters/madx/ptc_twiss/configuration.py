import xml_parser.approximator_training_configuration as xml_parser
import transporters.madx.ptc_twiss.optical_functions as optical_functions_module
import transporters.madx.ptc_twiss.transporter as transporter_module
from transporters.madx.configuration import MadxConfiguration


class PtcTwissConfiguration(MadxConfiguration):
    def __init__(self, end_place_name,
                 end_place_distance,
                 start_place_name,
                 beam_name,
                 madx_input_script_file_name,
                 if_filter_by_s=False):
        super().__init__(end_place_name, end_place_distance, start_place_name, beam_name, madx_input_script_file_name)
        self.filter_by_s = if_filter_by_s

    @staticmethod
    def get_configuration_from_file(path_to_xml_configuration, item_number, if_filter_by_s=False):
        configurations = xml_parser.get_approximator_configurations_from(path_to_xml_configuration)
        approximator_transport_configuration = configurations.transport_configuration
        atc = approximator_transport_configuration  # for shorter name
        return PtcTwissConfiguration(atc.end_place.name,
                                     atc.end_place.distance,
                                     atc.end_place.name_of_place_from,
                                     atc.end_place.beam,
                                     atc.madx_input_script_file_name,
                                     if_filter_by_s)

    def get_configuration(self):
        return self

    @staticmethod
    def get_module_with_optical_functions():
        return optical_functions_module

    @staticmethod
    def get_module_transporter():
        return transporter_module

    @property
    def s(self):
        return self.end_place_distance
