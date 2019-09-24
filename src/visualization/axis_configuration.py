import numpy as np


class AxisConfiguration:
    def __init__(self, start, end, step):
        self.start = start
        self.end = end
        self.step = step

    def get_ticks(self):
        return np.arange(self.start, self.end, self.step)