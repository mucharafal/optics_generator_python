import os
import shutil
import logging


def create_and_get_into(path_to_working_directory):
    previous_directory = os.getcwd()
    if not os.path.exists(path_to_working_directory):
        os.mkdir(path_to_working_directory)

    os.chdir(path_to_working_directory)
    return previous_directory


def leave_and_delete(previous_directory):
    logger = logging.getLogger()
    if logger.isEnabledFor(logging.DEBUG):
        os.chdir(previous_directory)
    else:
        working_directory = os.getcwd()
        os.chdir(previous_directory)
        shutil.rmtree(working_directory)
