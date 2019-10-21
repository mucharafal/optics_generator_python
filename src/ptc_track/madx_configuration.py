import ptc_track.madx_script_generator as msg
import xml_parser.approximator_training_configuration as xml_parser


class TrackConfiguration:
    def __init__(self, path_to_xml_file, item_number, path_to_accelerator_configuration, coordinates="canonical"):
        self.path_to_xml_file = path_to_xml_file
        self.item_number = item_number
        self.path_to_accelerator_configuration = path_to_accelerator_configuration
        self.coordinates = coordinates

    def generate_madx_script(self, number_of_particles):
        approximator_training_configuration = \
            xml_parser.get_approximator_configurations_from(self.path_to_xml_file)[self.item_number]
        return msg.generate_madx_script(approximator_training_configuration.transport_configuration, number_of_particles)
