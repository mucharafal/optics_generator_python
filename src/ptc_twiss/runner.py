import numpy as np
from concurrent.futures import ProcessPoolExecutor
from data.parameters_names import ParametersNames as Parameters
from ptc_track.runner import split_on
from cpymad.madx import Madx


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
    madx_interpreter = __initialize_madx_interpreter(transport_configuration)
    return __transport_particles(madx_interpreter, particles)


def __initialize_madx_interpreter(transport_configuration):
    end_place = transport_configuration.get_end_place_configuration()

    madx = Madx(stdout=False, command_log="log.madx")
    __define_accelerator(madx, transport_configuration)
    __define_end_place(madx, end_place)
    __use_only_part_from_ip_to_station(madx, transport_configuration)
    __include_errors_corrections(madx, transport_configuration)
    __create_universe(madx)
    __observe_places(madx, transport_configuration.get_scoring_place_names())
    return madx


def __define_accelerator(madx_interpreter, transport_configuration):
    madx_interpreter.call(transport_configuration.accelerator_definition_file_name, chdir=True)


def __define_end_place(madx_interpreter, end_place_configuration):
    madx_interpreter.input(end_place_configuration.name + ": marker;")
    madx_interpreter.input("seqedit, sequence=" + end_place_configuration.beam + ";")
    madx_interpreter.input("install, element=" + end_place_configuration.name + ", at="
                           + str(end_place_configuration.distance) + ", from=" +
                           end_place_configuration.name_of_place_from + ";")
    madx_interpreter.input("endedit;")


def __use_only_part_from_ip_to_station(madx_interpreter, transport_configuration):
    end_place = transport_configuration.get_end_place_configuration()
    madx_interpreter.use(transport_configuration.get_end_place_configuration().beam,
                         range=end_place.name_of_place_from + "/" + end_place.name)


def __include_errors_corrections(madx_interpreter, transport_configuration):
    madx_interpreter.call(transport_configuration.errors_definition_file_name, chdir=True)


def __create_universe(madx_interpreter):
    madx_interpreter.command.ptc_create_universe()
    madx_interpreter.command.ptc_create_layout(model=2, method=6, nst=1, exact=True, resplit=True, thin=0.0005,
                                               xbend=0.0005)
    madx_interpreter.command.ptc_align()


def __observe_places(madx_interpreter, places):
    # madx_interpreter.input("select,flag=ptc_twiss,clear;")
    #
    # madx_interpreter.input("select, flag=ptc_twiss, pattern=\"^" + places[0] + "\";")
    #
    # places_hardcoded = ["IP5", "tcl*", "MCB.*", "MQ.*", "MB.*", "bmp*"]
    # for place in places_hardcoded:
    #     madx_interpreter.input("select, flag=ptc_twiss, pattern=\"^" + place + "\";")
    #     print(place)
    pass


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
    return process_output_matrix(madx_interpreter.table.get("ptc_twiss"))


def process_row(raw_row):
    row = {
        Parameters.X: raw_row[0],
        Parameters.THETA_X: raw_row[1],
        Parameters.Y: raw_row[2],
        Parameters.THETA_Y: raw_row[3],
        Parameters.PT: raw_row[4]
    }
    return row


def process_output_matrix(output_matrix):
    matrix = np.array([output_matrix.s, output_matrix.x, output_matrix.y, output_matrix.px, output_matrix.py,
                       output_matrix.x, output_matrix.y, output_matrix.re11, output_matrix.re33,
                       output_matrix.re12, output_matrix.re34, output_matrix.disp1, output_matrix.disp3,
                       output_matrix.pt]).T
    return matrix


def __remove_duplicates(matrix_with_duplicate_rows):
    filtered_matrix = np.unique(matrix_with_duplicate_rows, axis=0)
    return filtered_matrix

