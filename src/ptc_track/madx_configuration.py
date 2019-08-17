import ptc_track.madx_script_generator as msg


class TrackConfiguration:
    def __init__(self, path_to_xml_file, item_number, path_to_accelerator_configuration):
        self.path_to_xml_file = path_to_xml_file
        self.item_number = item_number
        self.path_to_accelerator_configuration = path_to_accelerator_configuration

    def generate_madx_script(self, number_of_particles):
        return msg.generate_configuration_file_from_source(self.path_to_xml_file, self.item_number,
                                                           self.path_to_accelerator_configuration, number_of_particles)
