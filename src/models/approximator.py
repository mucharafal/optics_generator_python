class Approximator:
    """
    Wrapper for approximators with Transport method, to obtain compatibility with LHCOpticsApproximator object
    """
    def __init__(self, approximators):
        self.approximators = approximators

    def Transport(self, input_container, output_container):
        output_container[0] = self.approximators["x"].Eval(input_container)
        output_container[1] = self.approximators["theta x"].Eval(input_container)
        output_container[2] = self.approximators["y"].Eval(input_container)
        output_container[3] = self.approximators["theta y"].Eval(input_container)
        output_container[4] = input_container[4]