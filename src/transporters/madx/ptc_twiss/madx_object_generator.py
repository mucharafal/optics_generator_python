from cpymad.madx import Madx
import transporters.madx.parser as madx_script_parser
import uuid
import logging


def generate_madx_object(transport_configuration):
    madx_object = __initialize_madx_interpreter(transport_configuration)
    return madx_object


def __get_header():
    return "option, -echo, -info,  warn;\n"


def __initialize_madx_interpreter(transport_configuration):
    command_log = __get_command_log_name()
    madx = Madx(stdout=False, command_log=command_log)
    __define_accelerator(madx, transport_configuration)
    __create_universe(madx)
    return madx


def __get_command_log_name():
    logger = logging.getLogger()
    if logger.isEnabledFor(logging.DEBUG):
        random_sequence = str(uuid.uuid4())
        command_log = random_sequence + "log.madx"
    else:
        command_log = "/dev/null"
    return command_log


def __define_accelerator(madx_interpreter, transport_configuration):
    base_script = madx_script_parser.get_configuration(transport_configuration)
    madx_interpreter.input(base_script)


def __create_universe(madx_interpreter):
    madx_interpreter.command.ptc_create_universe()
    madx_interpreter.command.ptc_create_layout(model=2, method=6, nst=1, exact=True, resplit=True, thin=0.0005,
                                               xbend=0.0005)
    madx_interpreter.command.ptc_align()
