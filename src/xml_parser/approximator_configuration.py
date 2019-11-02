from data.parameters_names import ParametersNames as Parameters


class ApproximatorConfiguration:
    def __init__(self, polynomials_type, parameters_configurations, term_selection_mode, common_terms,
                 name_of_approximator, beam_name, beam_energy):
        self.polynomials_type = polynomials_type
        self.parameters_configurations = parameters_configurations
        self.term_selection_mode = term_selection_mode
        self.common_terms = common_terms
        self.name_of_approximator = name_of_approximator
        self.beam_name = beam_name
        self.beam_energy = beam_energy

    @staticmethod
    def get_configuration_from_xml(xml_root_configuration):
        xml_configuration = xml_root_configuration.attrib
        parameters = [Parameters.X, Parameters.THETA_X, Parameters.Y, Parameters.THETA_Y]
        parameters_configurations = [ParameterApproximationConfiguration.get_configuration_from_xml(xml_configuration,
                                                                                                    parameter)
                                     for parameter in parameters]
        terms_selection_mode = xml_configuration["terms_selection_mode"]
        common_terms = xml_configuration["common_terms"]
        name_of_approximator = xml_configuration["optics_parametrisation_name"]
        polynomials_type = xml_configuration["polynomials_type"]
        beam_name = xml_configuration["beam"]
        beam_energy = float(xml_configuration["nominal_beam_energy"])
        return ApproximatorConfiguration(polynomials_type, parameters_configurations, terms_selection_mode,
                                         common_terms, name_of_approximator, beam_name, beam_energy)


class ParameterApproximationConfiguration:
    def __init__(self, parameter, max_degree, precision):
        self.parameter = parameter
        self.max_degree = max_degree
        self.precision = precision

    @staticmethod
    def get_configuration_from_xml(xml_configuration, parameter):
        parameter_string = Parameters.get_name_in_xml(parameter)

        # Max degree of pt term in polynomial
        parameter_max_degree_key = "max_degree_" + parameter_string
        # Precision to reduce number of terms in polynomial
        parameter_precision_key = "precision_" + parameter_string

        max_degree = int(xml_configuration[parameter_max_degree_key])
        precision = float(xml_configuration[parameter_precision_key])

        return ParameterApproximationConfiguration(parameter, max_degree, precision)
