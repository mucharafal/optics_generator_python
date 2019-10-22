import xml_parser.approximator_training_configuration as xml_parser


class TwissConfiguration:
    def __init__(self, transport_configuration, s=-1):
        """
        Constructor of TwissConfiguration object.
        :param transport_configuration: object with configuration
        set on values: ptc_twiss, ..., X=x, PX=px, Y=y, PY=py, PT=pt...
        :param s: if different from -1, values at end station are filtered for this value of s. If is set on -1 segment
        end contains all records from input file
        """
        self.transport_configuration = transport_configuration
        self.s = s
        if s == -1:
            self.filter_by_s = False
        else:
            self.filter_by_s = True

    @staticmethod
    def get_configuration_from_file(path_to_xml_configuration, item_number, s=-1):
        configurations = xml_parser.get_approximator_configurations_from(path_to_xml_configuration)
        return TwissConfiguration(configurations[item_number].transport_configuration, s)
