import transporters.approximator.runner as approximator_utils
import transporters.approximator.optical_functions as optical_functions_module
import transporters.approximator.transporter as approximator_transporter


class ApproximatorConfiguration:
    def __init__(self, path_to_root_file, name_of_approximator):
        self.approximator = approximator_utils.get_approximator(path_to_root_file, name_of_approximator)

    @staticmethod
    def get_module_with_optical_functions():
        return optical_functions_module

    @staticmethod
    def get_module_transporter():
        return approximator_transporter

    def get_configuration(self):
        return self.approximator
