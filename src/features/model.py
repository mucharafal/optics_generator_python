import numpy as np


def fit_polynomial(input_parameters, output_values):
    pseudo_vandermonde_matrix = calculate_polynomials(input_parameters)
    coefficients = np.linalg.lstsq(pseudo_vandermonde_matrix, output_values, rcond=None)
    return coefficients


def calculate_polynomials(input_values):

    return vandermonde_multi_dimensional(input_values)


def vandermonde_multi_dimensional(parameters):
    max_degree = 2
    begin_parameter = np.polynomial.polynomial.polyvander(parameters[0], max_degree)
    n = begin_parameter.shape[0]
    for parameter in parameters[1:]:
        temp = []
        for case in range(n):
            p = []
            # print(begin_parameter)
            for element in begin_parameter[case]:
                k = np.polynomial.polynomial.polyvander2d(element, parameter[case], [1, max_degree])
                # print(k.shape)
                without_redundant_columns = np.delete(k, range(0, int(k.shape[1]/2)), 1)
                p.append(without_redundant_columns)
            temp.append(np.array(p).reshape((-1,)))

        begin_parameter = np.array(temp)
    print(begin_parameter.shape)
    return begin_parameter


if __name__ == "__main__":
    """ for test only """
    x = np.array([1, 2, 3, 1, 2, 3, 5])
    y = np.array([1, 3, 9, 0, 0, 0, 0])
    z = np.array([0, 0, 0, 10, 10, 10, 10])
    x = fit_polynomial([x, y, z], x)
    print(x)

