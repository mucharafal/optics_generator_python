import os


class TransportConfiguration:
    def __init__(self, end_place, observed_places_names, madx_output_script_file_name, madx_input_script_file_name):
        self.end_place = end_place
        self.observed_places_names = observed_places_names
        self.madx_output_script_file_name = madx_output_script_file_name
        self.madx_input_script_file_name = madx_input_script_file_name

    def get_scoring_place_names(self):
        return self.observed_places_names

    def get_end_place_configuration(self):
        return self.end_place

    @staticmethod
    def get_configuration_from_xml(xml_configuration, path_to_folder_with_optic):
        end_place = EndPlace.get_end_place_from(xml_configuration.attrib)
        observed_places_names = [end_place.name] + [aperture_xml_configuration.attrib["to_marker_name"]
                                                    for aperture_xml_configuration in xml_configuration]
        madx_template_file_name = xml_configuration.attrib["base_mad_conf_file"]
        path_to_madx_template = os.path.join(path_to_folder_with_optic, madx_template_file_name)
        return TransportConfiguration(end_place, observed_places_names,
                                      xml_configuration.attrib["processed_mad_conf_file"],
                                      path_to_madx_template)


class EndPlace:
    def __init__(self, name, distance, name_of_place_from, beam):
        self.name = name
        self.distance = distance
        self.name_of_place_from = name_of_place_from
        self.beam = beam

    @staticmethod
    def get_end_place_from(xml_configuration):
        return EndPlace(
            xml_configuration["to_marker_name"],
            float(xml_configuration["to_marker_s_pos"]),
            xml_configuration["from_marker_name"],
            xml_configuration["beam"])
