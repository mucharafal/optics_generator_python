class ApertureConfiguration:
    def __init__(self, name, aperture_type, rect_rx, rect_ry, el_rx, el_ry):
        self.name = name
        self.type = aperture_type
        self.rect_rx = rect_rx
        self.rect_ry = rect_ry
        self.el_rx = el_rx
        self.el_ry = el_ry

    @staticmethod
    def get_configuration_from_xml(xml_configuration):
        return ApertureConfiguration(
            xml_configuration["to_marker_name"],
            xml_configuration["ap_type"],
            float(xml_configuration["rect_rx"]),
            float(xml_configuration["rect_ry"]),
            float(xml_configuration["el_rx"]),
            float(xml_configuration["el_ry"])
        )

    @staticmethod
    def get_configurations_from_xml(xml_configuration):
        configurations = [ApertureConfiguration.get_configuration_from_xml(configuration.attrib)
                          for configuration in xml_configuration]
        return configurations
