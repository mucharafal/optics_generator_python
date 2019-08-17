import approximator.optics_parameters as aop
import ptc_track.optics_parameters as mop
import numpy as np


def compare_d_x(bunch_configuration, approximator, madx_configuration):
    approximator_result = aop.compute_d_x(approximator, bunch_configuration)
    madx_result = mop.compute_d_x(madx_configuration, bunch_configuration)

    approximator_d_x = approximator_result.T[5]
    madx_d_x = madx_result.T[5]

    difference = (approximator_d_x - madx_d_x).reshape((-1, 1))

    return compute_norm(difference, madx_d_x, madx_result, approximator_result)


def compare_d_y(bunch_configuration, approximator, madx_configuration):
    approximator_result = aop.compute_d_y(approximator, bunch_configuration)
    madx_result = mop.compute_d_y(madx_configuration, bunch_configuration)

    approximator_d_y = approximator_result.T[5]
    madx_d_y = madx_result.T[5]

    difference = (approximator_d_y - madx_d_y).reshape((-1, 1))

    return compute_norm(difference, madx_d_y, madx_result, approximator_result)


def compare_l_x(bunch_configuration, approximator, madx_configuration):
    approximator_result = aop.compute_l_x(approximator, bunch_configuration)
    madx_result = mop.compute_l_x(madx_configuration, bunch_configuration)

    approximator_l_x = approximator_result.T[5]
    madx_l_x = madx_result.T[5]

    difference = (approximator_l_x - madx_l_x).reshape((-1, 1))

    return compute_norm(difference, madx_l_x, madx_result, approximator_result)


def compare_l_y(bunch_configuration, approximator, madx_configuration):
    approximator_result = aop.compute_l_y(approximator, bunch_configuration)
    madx_result = mop.compute_l_y(madx_configuration, bunch_configuration)

    approximator_l_y = approximator_result.T[5]
    madx_l_y = madx_result.T[5]

    difference = (approximator_l_y - madx_l_y).reshape((-1, 1))

    return compute_norm(difference, madx_l_y, madx_result, approximator_result)


def compare_v_x(bunch_configuration, approximator, madx_configuration):
    approximator_result = aop.compute_v_x(approximator, bunch_configuration)
    madx_result = mop.compute_v_x(madx_configuration, bunch_configuration)

    approximator_v_x = approximator_result.T[5]
    madx_v_x = madx_result.T[5]

    difference = (approximator_v_x - madx_v_x).reshape((-1, 1))

    return compute_norm(difference, madx_v_x, madx_result, approximator_result)


def compare_v_y(bunch_configuration, approximator, madx_configuration):
    approximator_result = aop.compute_v_y(approximator, bunch_configuration)
    madx_result = mop.compute_v_y(madx_configuration, bunch_configuration)

    approximator_v_y = approximator_result.T[5]
    madx_v_y = madx_result.T[5]

    difference = (approximator_v_y - madx_v_y).reshape((-1, 1))

    return compute_norm(difference, madx_v_y, madx_result, approximator_result)


def compute_norm(diff, values, madx_matrix, approximator_matrix):
    print(diff.shape, values.shape)
    relative_diff = np.divide(diff, values.reshape((-1, 1)))
    abs_val_of__rel_diff = np.absolute(relative_diff)
    print(abs_val_of__rel_diff.shape)
    max_diff = np.max(abs_val_of__rel_diff)
    return abs_val_of__rel_diff, madx_matrix, approximator_matrix


def compare_all(bunch_configuration, approximator, madx_configuration):
    return {
        "D x": compare_d_x(bunch_configuration, approximator, madx_configuration),
        "D y": compare_d_y(bunch_configuration, approximator, madx_configuration),
        "L x": compare_l_x(bunch_configuration, approximator, madx_configuration),
        "L y": compare_l_y(bunch_configuration, approximator, madx_configuration),
        "V x": compare_v_x(bunch_configuration, approximator, madx_configuration),
        "V y": compare_v_y(bunch_configuration, approximator, madx_configuration)
    }
