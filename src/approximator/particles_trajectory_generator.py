import approximator.run_approximator as ra
import data.particles_generator as pg
import data.madx_runner as mr       # expand function from this file used here
import numpy as np


def generate_random_particles(beam_configuration, angles_ranges, approximator,
                              target, number_of_particles_in_one_run):
    """
    Generate dict with matrix of particles' parameters on stations. List of stations is in madx configuration generator.
    Take angles into account.
    :param beam_configuration: dict with beam parameters- x, theta x, y, theta y, t, and pt- their min and max values.
    :param angles_ranges: dict with parameters of angles- their min and max values.
    :param target: target number of parameters at end station.
    :param number_of_particles_in_one_run: number of particles generated and divided by workers in one run
    :return: dict with numpy matrix of particles' parameters on stations, matrix format:
    ordinal number, turn, x, theta x, y, theta y, t, pt, e, s, angle x, angle y
    """
    segments = {}
    counter = 0

    while ("end" not in segments.keys()) or ("end" in segments.keys() and len(segments["end"]) < target):
        new_particles = __generate_random_particles(beam_configuration, angles_ranges, number_of_particles_in_one_run,
                                                    approximator)

        shift = counter * number_of_particles_in_one_run
        counter += 1
        new_particles = mr.shift_ordinal_number_in_segments(new_particles, shift)

        segments = mr.merge_segments(segments, new_particles)

        if "end" not in segments.keys():
            print("0")
        else:
            print(len(segments["end"]))

    return segments


def __generate_random_particles(beam_configuration, angles_ranges, number_of_particles_in_one_run, approximator):
    """
    todo Outdate
    Generate dict with matrix of particles' parameters on stations. List of stations is in madx configuration generator.
    :param beam_configuration: dict with beam parameters- x, theta x, y, theta y, t, and pt- their min and max values.
    :param angles_ranges: dict with parameters of angles- their min and max values.
    :param number_of_particles_in_one_run: number of particles generated and divided by workers in one run
    :return: dict with numpy matrix of particles' parameters on stations, matrix format:
    ordinal number, turn, x, theta x, y, theta y, t, pt, e, s, angle x, angle y
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

    matrix_for_madx = particles.T[:6].T
    angles = particles.T[6:]

    segments = dict()
    segments["start"] = matrix_for_madx

    matrix_for_approximator = np.delete(matrix_for_madx, 4, 1)

    transported_particles_parameters = ra.transport(approximator, matrix_for_approximator)
    wip_matrix = np.append(transported_particles_parameters.T[:4].T,
                           np.full((transported_particles_parameters.shape[0], 1), 0), axis=1)
    segments["end"] = np.append(wip_matrix, transported_particles_parameters.T[4].reshape((-1, 1)), axis=1)

    for segment_name in segments.keys():
        segment = segments[segment_name]
        indexes = segment.T[0].astype(int)
        indexes -= 1
        angles_of_segment = angles.T[indexes]
        segment = np.append(segment, angles_of_segment, axis=1)
        segments[segment_name] = segment

    return segments
