import data.particles_generator as pg
import data.madx_runner as mr
import numpy as np


def generate_particles(beam_configuration, angles_ranges, path_to_accelerator_configuration,
                       target, number_of_particles_in_one_run):
    """
    Generate dict with matrix of particles' parameters on stations. List of stations is in madx configuration generator.
    :param beam_configuration: dict with beam parameters- x, theta x, y, theta y, t, and pt- their min and max values.
    :param angles_ranges: dict with parameters of angles- their min and max values.
    :param path_to_accelerator_configuration: path to folder with configuration of accelerator. Needed files:
    todo
    :param target: target number of parameters at end station.
    :param number_of_particles_in_one_run: number of particles generated and divided by workers in one run
    :return: dict with numpy matrix of particles' parameters on stations.
    """
    segments = {}
    counter = 0

    while len(segments.keys()) == 0 or len(segments["end"]) <= target:
        new_particles = __generate_particles(beam_configuration, angles_ranges, path_to_accelerator_configuration,
                                             number_of_particles_in_one_run)

        shift = counter * number_of_particles_in_one_run
        counter += 1
        new_particles = mr.shift_ordinal_number_in_segments(new_particles, shift)

        segments = mr.merge_segments(segments, new_particles)

    return segments


def __generate_particles(beam_configuration, angles_ranges, path_to_accelerator_configuration,
                         number_of_particles_in_one_run):
    """
    Generate dict with matrix of particles' parameters on stations. List of stations is in madx configuration generator.
    :param beam_configuration: dict with beam parameters- x, theta x, y, theta y, t, and pt- their min and max values.
    :param angles_ranges: dict with parameters of angles- their min and max values.
    :param path_to_accelerator_configuration: path to folder with configuration of accelerator. Needed files:
    todo
    :param number_of_particles_in_one_run: number of particles generated and divided by workers in one run
    :return: dict with numpy matrix of particles' parameters on stations.
    """
    particles = pg.generate_particles_randomly_with_angle(beam_configuration["x_min"], beam_configuration["x_max"],
                                              beam_configuration["theta_x_min"], beam_configuration["theta_x_max"],
                                              beam_configuration["y_min"], beam_configuration["y_max"],
                                              beam_configuration["theta_y_min"], beam_configuration["theta_y_max"],
                                              beam_configuration["t_min"], beam_configuration["t_max"],
                                              beam_configuration["pt_min"], beam_configuration["pt_max"],
                                              angles_ranges["x_min"], angles_ranges["x_max"],
                                              angles_ranges["y_min"], angles_ranges["y_max"],
                                              number_of_particles_in_one_run)

    # take only x, theta x, y, theta y, t and pt, angles are omitted
    matrix_for_madx = particles.T[:6]
    angles = particles.T[6:]

    number_of_processes = 4
    segments = mr.compute_trajectory(matrix_for_madx, path_to_accelerator_configuration, number_of_processes)

    for segment_name in segments.keys():
        segment = segments[segment_name]
        indexes = segment.T[0].astype(int)
        indexes -= 1
        angles_of_segment = angles.T[indexes]
        segment = np.append(segment, angles_of_segment, axis=1)
        segments[segment_name] = segment

    return segments




