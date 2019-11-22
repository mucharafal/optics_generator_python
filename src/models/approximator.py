from data.parameters_names import ParametersNames as Parameters


class Approximator:
    """
    Wrapper for approximators with Transport method, to obtain compatibility with LHCOpticsApproximator object
    """
    def __init__(self, approximators):
        self.approximators = approximators

    def Transport(self, input_container, output_container):
        output_container[0] = self.approximators[Parameters.X].Eval(input_container)
        output_container[1] = self.approximators[Parameters.THETA_X].Eval(input_container)
        output_container[2] = self.approximators[Parameters.Y].Eval(input_container)
        output_container[3] = self.approximators[Parameters.THETA_Y].Eval(input_container)
        output_container[4] = input_container[4]