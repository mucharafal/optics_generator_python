import xml_parser.approximator_training_configuration as xml_parser
import transporters.ptc_twiss.optical_functions as optical_functions_module
import transporters.ptc_twiss.transporter as transporter_module


class PtcTwissConfiguration:
    def __init__(self, transport_configuration, if_filter_by_s=False):
        """
        Constructor of TwissConfiguration object.
        :param transport_configuration: object with configuration
        set on values: ptc_twiss, ..., X=x, PX=px, Y=y, PY=py, PT=pt...
        :param s: if different from -1, values at end station are filtered for this value of s. If is set on -1 segment
        end contains all records from input file
        """
        self.transport_configuration = transport_configuration
        self.filter_by_s = if_filter_by_s
        self.s = transport_configuration.end_place.distance

    @staticmethod
    def get_configuration_from_file(path_to_xml_configuration, item_number, if_filter_by_s=False):
        configurations = xml_parser.get_approximator_configurations_from(path_to_xml_configuration)
        return PtcTwissConfiguration(configurations[item_number].transport_configuration, if_filter_by_s)

    def get_configuration(self):
        return self

    @staticmethod
    def get_module_with_optical_functions():
        return optical_functions_module

    @staticmethod
    def get_module_transporter():
        return transporter_module
