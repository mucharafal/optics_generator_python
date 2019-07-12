import data.madx_runner as mr
import data.particles_generator as pg
import data.madxconfigurationgenerator as mcg
import os
import shutil
"""
Module include functions to obtain parameters of optics such like dispersion or magnetism.
They are calculated using madx to obtain particle trajectory and then they are obtained using numerical derivative.
None of them is thread safe.
"""


def compute_l_y(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_theta=0.000001):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x, theta_x, y, theta_y + delta_theta, ksi, path_to_configuration)
    return (particle2["y"] - particle1["y"]) / delta_theta


def compute_l_x(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_theta=0.000001):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x, theta_x + delta_theta, y, theta_y, ksi, path_to_configuration)
    return (particle2["x"] - particle1["x"]) / delta_theta


def compute_v_x(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_x):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x + delta_x, theta_x, y, theta_y, ksi, path_to_configuration)
    return (particle2["x"] - particle1["x"]) / delta_x


def compute_v_y(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_y):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x, theta_x, y + delta_y, theta_y, ksi, path_to_configuration)
    return (particle2["y"] - particle1["y"]) / delta_y


def compute_d_x(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_ksi):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x, theta_x, y, theta_y, ksi + delta_ksi, path_to_configuration)
    return (particle2["x"] - particle1["x"]) / delta_ksi


def compute_d_y(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_ksi):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x, theta_x, y, theta_y, ksi + delta_ksi, path_to_configuration)
    return (particle2["y"] - particle1["y"]) / delta_ksi


def get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration):
    """
    Transport particle with given parameter.
    Generate input file for madx, invoke it and read in its input.
    Raise error ParticleNotArrivedError if particle do not arrive at the end station.
    :param x:
    :param theta_x:
    :param y:
    :param theta_y:
    :param ksi:
    :param path_to_configuration: path to configuration of accelerator. Needed files:
    /2016/lhc_as-built.seq
    /2016/opt_inj_colltunes.madx
    temporary_perturbation.madx
    temporary_perturbation_b1.madx
    LSA.str
    :return: map with parameters of particle
    """
    bunch_size = 1
    current_path = os.getcwd()
    folder_name = "kali1234"
    os.mkdir(folder_name)
    os.chdir(folder_name)

    name_of_configuration_file = mcg.generate_configuration_file(path_to_configuration, ksi, bunch_size)

    pg.generate_from_range(x, x, bunch_size,
                           theta_x, theta_x, 1,
                           y, y, 1,
                           theta_y, theta_y, 1,
                           0, 0, 1,
                           0, 0, 1)

    mr.__run_madx(name_of_configuration_file)
    segments = mr.__read_in_madx_output_file("trackone")

    if "end" in segments.keys():
        matrix = segments["end"]
    else:
        os.chdir(current_path)
        shutil.rmtree(folder_name)
        raise ParticleNotArrivedError()

    os.chdir(current_path)
    shutil.rmtree(folder_name)

    return process_row(matrix[0])


def process_row(row):
    mapping = {
        "number": row[0],
        "turn": row[1],
        "x": row[2],
        "theta_x": row[3],
        "y": row[4],
        "theta_y": row[5],
        "t": row[6],
        "pt": row[7],
        "s": row[8],
        "e": row[9]
    }
    return mapping


class ParticleNotArrivedError(Exception):
    pass



