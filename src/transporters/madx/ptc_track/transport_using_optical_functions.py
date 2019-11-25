import transporters.madx.ptc_track.optical_functions as optical_functions
import numpy as np


def transport(madx_configuration, bunch_configuration):
    # todo
    # Change matrix on own type- matrix + mapping in one object
    matrix_with_v_x = optical_functions.compute_v_x(madx_configuration, bunch_configuration)
    matrix_with_l_x = optical_functions.compute_l_x(madx_configuration, bunch_configuration)
    matrix_with_d_x = optical_functions.compute_d_x(madx_configuration, bunch_configuration)

    v_x = matrix_with_v_x.T[5]
    l_x = matrix_with_l_x.T[5]
    d_x = matrix_with_d_x.T[5]

    begin_x = matrix_with_v_x.T[0]
    begin_theta_x = matrix_with_v_x.T[2]
    begin_pt = matrix_with_v_x.T[4]
    transported_x = v_x * begin_x + l_x * begin_theta_x + d_x * begin_pt

    matrix_with_v_y = optical_functions.compute_v_y(madx_configuration, bunch_configuration)
    matrix_with_l_y = optical_functions.compute_l_y(madx_configuration, bunch_configuration)
    matrix_with_d_y = optical_functions.compute_d_y(madx_configuration, bunch_configuration)

    v_y = matrix_with_v_y.T[5]
    l_y = matrix_with_l_y.T[5]
    d_y = matrix_with_d_y.T[5]

    begin_y = matrix_with_v_y.T[1]
    begin_theta_y = matrix_with_v_y.T[3]
    begin_pt = matrix_with_v_y.T[4]
    transported_y = v_y * begin_y + l_y * begin_theta_y + d_y * begin_pt

    segments = {
        "start": matrix_with_d_x.T[:5].T,
        "end": np.array([transported_x, transported_y, begin_pt]).T
    }

    return segments
