import operator
from functools import reduce

from data.parameters_names import ParametersNames as Parameters
import data.particles_generator as particles_generator


class ParameterConfiguration:
    def __init__(self, parameter_name, min_value, max_value, resolution):
        self.parameter_name = parameter_name
        self.minimal_value = min_value
        self.maximal_value = max_value
        self.resolution = resolution


class GridConfiguration:
    def __init__(self,
                 *parameters):
        self.parameters = parameters

    def get_number_of_particles(self):
        resolutions_of_parameters = map(lambda parameter_configuration: parameter_configuration.resolution,
                                        self.parameters)
        number_of_particles = reduce(operator.mul, resolutions_of_parameters, 1)
        return number_of_particles

    def generate_randomly(self):
        return particles_generator.generate_particles_randomly(self)

    def generate_grid(self):
        return particles_generator.generate_from_range(self)

    @classmethod
    def from_delta(cls, x_mean, x_delta, x_resolution,
                   theta_x_mean, theta_x_delta, theta_x_resolution,
                   y_mean, y_delta, y_resolution,
                   theta_y_mean, theta_y_delta, theta_y_resolution,
                   pt_mean, pt_delta, pt_resolution):
        return cls.by_boundary(x_mean - x_delta, x_mean + x_delta, x_resolution,
                               theta_x_mean - theta_x_delta, theta_x_mean + theta_x_delta, theta_x_resolution,
                               y_mean - y_delta, y_mean + y_delta, y_resolution,
                               theta_y_mean - theta_y_delta, theta_y_mean + theta_y_delta, theta_y_resolution,
                               pt_mean - pt_delta, pt_mean + pt_delta, pt_resolution)

    @classmethod
    def by_boundary(cls, x_min, x_max, x_resolution,
                    theta_x_min, theta_x_max, theta_x_resolution,
                    y_min, y_max, y_resolution,
                    theta_y_min, theta_y_max, theta_y_resolution,
                    pt_min, pt_max, pt_resolution):
        x_configuration = ParameterConfiguration(Parameters.X, x_min, x_max, x_resolution)
        theta_x_configuration = ParameterConfiguration(Parameters.THETA_X, theta_x_min, theta_x_max, theta_x_resolution)
        y_configuration = ParameterConfiguration(Parameters.Y, y_min, y_max, y_resolution)
        theta_y_configuration = ParameterConfiguration(Parameters.THETA_Y, theta_y_min, theta_y_max, theta_y_resolution)
        pt_configuration = ParameterConfiguration(Parameters.PT, pt_min, pt_max, pt_resolution)
        return cls(x_configuration, theta_x_configuration, y_configuration, theta_y_configuration,
                                 pt_configuration)

    @classmethod
    def get_configuration_from_xml_object(cls, xml_root_configuration):
        xml_configuration = xml_root_configuration.attrib
        return cls.by_boundary(
            float(xml_configuration["x_min"]), float(xml_configuration["x_max"]), 1,
            float(xml_configuration["theta_x_min"]), float(xml_configuration["theta_x_max"]), 1,
            float(xml_configuration["y_min"]), float(xml_configuration["y_max"]), 1,
            float(xml_configuration["theta_y_min"]), float(xml_configuration["theta_y_max"]), 1,
            float(xml_configuration["ksi_min"]), float(xml_configuration["ksi_max"]),
            int(xml_configuration["tot_entries_number"])
        )


class CanonicalCoordinatesGridConfiguration(GridConfiguration):
    def __init__(self, *parameters):
        super().__init__(*parameters)

    @staticmethod
    def if_canonical_coordinates():
        return True


class GeometricalCoordinatesGridConfiguration(GridConfiguration):
    def __init__(self, *parameters):
        super().__init__(*parameters)

    @staticmethod
    def if_canonical_coordinates():
        return False
