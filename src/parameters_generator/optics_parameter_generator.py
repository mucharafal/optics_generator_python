import madx_runner as mr
import particles_generator as pg
import os
import shutil
"""
Module include functions to obtain parameters of optics such like dispersion or magnetism.
They are calculated using madx to obtain particle trajectory and then they are obtained using numerical derivative.
None of them is thread safe.
"""


def compute_l_y(x, theta_x, y, theta_y, ksi, delta_theta=0.000001):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi)
    particle2 = get_one_particle(x, theta_x, y, theta_y + delta_theta, ksi)
    return (particle2["y"] - particle1["y"]) / delta_theta


def compute_l_x(x, theta_x, y, theta_y, ksi, delta_theta=0.000001):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi)
    particle2 = get_one_particle(x, theta_x + delta_theta, y, theta_y, ksi)
    return (particle2["x"] - particle1["x"]) / delta_theta


def compute_v_x(x, theta_x, y, theta_y, ksi, delta_x):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi)
    particle2 = get_one_particle(x + delta_x, theta_x, y, theta_y, ksi)
    return (particle2["x"] - particle1["x"]) / delta_x


def compute_v_y(x, theta_x, y, theta_y, ksi, delta_y):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi)
    particle2 = get_one_particle(x, theta_x, y + delta_y, theta_y, ksi)
    return (particle2["y"] - particle1["y"]) / delta_y


def compute_d_x(x, theta_x, y, theta_y, ksi, delta_ksi):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi)
    particle2 = get_one_particle(x, theta_x, y, theta_y, ksi + delta_ksi)
    return (particle2["x"] - particle1["x"]) / delta_ksi


def compute_d_y(x, theta_x, y, theta_y, ksi, delta_ksi):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi)
    particle2 = get_one_particle(x, theta_x, y, theta_y, ksi + delta_ksi)
    return (particle2["y"] - particle1["y"]) / delta_ksi


def get_one_particle(x, theta_x, y, theta_y, ksi):
    """
    Transport particle with given parameter.
    Generate input file for madx, invoke it and read in its input.
    Raise error ParticleNotArrivedError if particle do not arrive at the end station.
    :param x:
    :param theta_x:
    :param y:
    :param theta_y:
    :param ksi:
    :return:
    """
    bunch_size = 1
    current_path = os.getcwd()
    folder_name = "kali1234"
    os.mkdir(folder_name)
    os.chdir(folder_name)

    path_to_madx_script = "./configuration.madx"

    with open("ready_config", "w") as output_file:
        with open(path_to_madx_script) as input_file:
            output_file.write("bunch_size = " + str(bunch_size) + ";\n")
            output_file.write("DELTA_AP = " + str(ksi) + ";\n")
            for i in input_file:
                output_file.write(i)

    pg.generate_from_range(x, x, bunch_size + 1,
                           theta_x, theta_x, 1,
                           y, y, 1,
                           theta_y, theta_y, 1,
                           0, 0, 1,
                           ksi, ksi, 1)

    mr.run_madx("ready_config")
    segments = mr.read_in_madx_output_file("trackone")

    if "end" in segments.keys():
        matrix = segments["end"]
    else:
        os.chdir(current_path)
        shutil.rmtree(folder_name)
        raise ParticleNotArrivedError()

    return process_row(matrix[0])


def process_row(row):
    mapping = {
        "number": row[0],
        "turn"  : row[1],
        "x"     : row[2],
        "theta_x" : row[3],
        "y"     : row[4],
        "theta_y" : row[5],
        "t"     : row[6],
        "pt"    : row[7],
        "s"     : row[8],
        "e"     : row[9]
    }
    return mapping


class ParticleNotArrivedError(Exception):
    pass

