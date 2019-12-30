import numpy as np
import transporters.madx.ptc_twiss.matrix_indexes as indexes
import transporters.madx.ptc_twiss.madx_object_generator as madx_object_generator
from concurrent.futures import ProcessPoolExecutor
from data.parameters_names import ParametersNames as Parameters
from transporters.madx.ptc_track.runner import split_on
from data.particles import CanonicalCoordinates


def transport(transport_configuration, particles):
    """
    Transport particles using ptc_twiss
    :param transport_configuration: configuration for run madx with ptc_twiss command
    :type transport_configuration: TransportConfiguration
    :param particles: matrix with columns: x, theta x, y, theta y, pt
    :type particles: np.array
    :return: matrix returned by ptc_twiss- results from processing next lines of
    """
    result_matrix_with_duplicates = None
    number_of_workers = 4

    parts, part_size = split_on(number_of_workers, particles)

    with ProcessPoolExecutor(number_of_workers) as executor:
        futures = []
        for worker_number in range(number_of_workers):
            futures.append(executor.submit(run_worker, transport_configuration, parts[worker_number]))
        for future in futures:
            result_matrix_with_duplicates = future.result() if result_matrix_with_duplicates is None else \
                np.append(result_matrix_with_duplicates, future.result(), axis=0)

    result_matrix = __remove_duplicates(result_matrix_with_duplicates)

    return result_matrix


def run_worker(transport_configuration, particles):
    # Create and get into working directory
    madx_interpreter = madx_object_generator.generate_madx_object(transport_configuration)
    return __transport_particles(madx_interpreter, particles)


def __transport_particles(madx_interpreter, particles):
    result_matrix = None
    for row in particles:
        transported_row = __transport_by_ptc_twiss(madx_interpreter, row)
        result_matrix = transported_row if result_matrix is None else \
            np.append(result_matrix, transported_row, axis=0)
    return result_matrix


def __transport_by_ptc_twiss(madx_interpreter, raw_row):
    row = process_row(raw_row)
    beta_ip5 = madx_interpreter.globals.beta_ip5     # todo get it from madx interpreter, should be in optics
    delta_p = madx_interpreter.globals.delta_p
    madx_interpreter.command.ptc_twiss(x=row[Parameters.X], px=row[Parameters.THETA_X], y=row[Parameters.Y],
                                       py=row[Parameters.THETA_Y], pt=row[Parameters.PT], icase=5, no=6,
                                       deltap_dependency=True, rmatrix=True, betx=beta_ip5, bety=beta_ip5,
                                       deltap=delta_p)
    return __process_output_matrix(madx_interpreter.table.get("ptc_twiss"))


def process_row(raw_row):
    row = {
        Parameters.X: raw_row[0],
        Parameters.THETA_X: raw_row[1],
        Parameters.Y: raw_row[2],
        Parameters.THETA_Y: raw_row[3],
        Parameters.PT: raw_row[4]
    }
    return row


def __process_output_matrix(output_matrix):
    matrix = np.array([output_matrix.s, output_matrix.x, output_matrix.y, output_matrix.px, output_matrix.py,
                       output_matrix.x, output_matrix.y, output_matrix.re11, output_matrix.re33,
                       output_matrix.re12, output_matrix.re34, output_matrix.disp1, output_matrix.disp3,
                       output_matrix.pt]).T
    return matrix


def __remove_duplicates(matrix_with_duplicate_rows):
    filtered_matrix = np.unique(matrix_with_duplicate_rows, axis=0)
    return filtered_matrix


def get_initialized_madx(twiss_configuration):
    return madx_object_generator.generate_madx_object(twiss_configuration)


def get_particles_object_from_output(ptc_twiss_like_output):
    matrix = __process_output_matrix(ptc_twiss_like_output)
    mapping = indexes.ptc_twiss
    return CanonicalCoordinates(matrix, mapping)
