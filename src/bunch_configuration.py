class BunchConfiguration:
    def __init__(self,
                 x_min, x_max, number_of_x_values,
                 theta_x_min, theta_x_max, number_of_theta_x_values,
                 y_min, y_max, number_of_y_values,
                 theta_y_min, theta_y_max, number_of_theta_y_values,
                 pt_min, pt_max, number_of_pt_values):
        self.x_min = x_min
        self.x_max = x_max
        self.number_of_x_values = number_of_x_values
        self.y_min = y_min
        self.y_max = y_max
        self.number_of_y_values = number_of_y_values
        self.theta_x_min = theta_x_min
        self.theta_x_max = theta_x_max
        self.number_of_theta_x_values = number_of_theta_x_values
        self.theta_y_min = theta_y_min
        self.theta_y_max = theta_y_max
        self.number_of_theta_y_values = number_of_theta_y_values
        self.pt_min = pt_min
        self.pt_max = pt_max
        self.number_of_pt_values = number_of_pt_values

    @staticmethod
    def from_sigma(x_mean, sigma_x, number_of_x_values,
                   theta_x_mean, sigma_theta_x, number_of_theta_x_values,
                   y_mean, sigma_y, number_of_y_values,
                   theta_y_mean, sigma_theta_y, number_of_theta_y_values,
                   pt_mean, sigma_pt, number_of_pt_values):
        return BunchConfiguration(x_mean - sigma_x, x_mean + sigma_x, number_of_x_values,
                                  theta_x_mean - sigma_theta_x, theta_x_mean + sigma_theta_x, number_of_theta_x_values,
                                  y_mean - sigma_y, y_mean + sigma_y, number_of_y_values,
                                  theta_y_mean - sigma_theta_y, theta_y_mean + sigma_theta_y, number_of_theta_y_values,
                                  pt_mean - sigma_pt, pt_mean + sigma_pt, number_of_pt_values)


class ApproximatorAndBunchConfiguration(BunchConfiguration):
    def __init__(self, approximator,
                 x_min, x_max, number_of_x_values,
                 theta_x_min, theta_x_max, number_of_theta_x_values,
                 y_min, y_max, number_of_y_values,
                 theta_y_min, theta_y_max, number_of_theta_y_values,
                 pt_min, pt_max, number_of_pt_values):
        super().__init__(x_min, x_max, number_of_x_values, theta_x_min, theta_x_max, number_of_theta_x_values,
                         y_min, y_max, number_of_y_values, theta_y_min, theta_y_max, number_of_theta_y_values,
                         pt_min, pt_max, number_of_pt_values)
        self.approximator = approximator

    @staticmethod
    def get_using_sigma(approximator,
                        x_mean, sigma_x, number_of_x_values,
                        theta_x_mean, sigma_theta_x, number_of_theta_x_values,
                        y_mean, sigma_y, number_of_y_values,
                        theta_y_mean, sigma_theta_y, number_of_theta_y_values,
                        pt_mean, sigma_pt, number_of_pt_values):
        return ApproximatorAndBunchConfiguration(approximator, x_mean - sigma_x, x_mean + sigma_x, number_of_x_values,
                                                 theta_x_mean - sigma_theta_x, theta_x_mean + sigma_theta_x, number_of_theta_x_values,
                                                 y_mean - sigma_y, y_mean + sigma_y, number_of_y_values,
                                                 theta_y_mean - sigma_theta_y, theta_y_mean + sigma_theta_y, number_of_theta_y_values,
                                                 pt_mean - sigma_pt, pt_mean + sigma_pt, number_of_pt_values)
