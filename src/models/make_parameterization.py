#!/bin/python3
import argparse
import logging

parser = argparse.ArgumentParser(description="Generator plots of optical functions")
parser.add_argument("path to xml", metavar='path', type=str, help="Path to xml file")
parser.add_argument("-v", "--verbose", dest='logging-level', action='store_const', const=logging.DEBUG, default=logging.INFO, help="Verbosity of program, if set, logs from madx will be created")
args = parser.parse_args()


logger = logging.getLogger()
logger.setLevel(getattr(args, "logging-level"))


import models.train_model as trainer
from ROOT import TObject, TFile
import os
import sys
import xml_parser.approximator_training_configuration as xml_parser


def main(path_to_xml_file, path_to_optics):
    training_configurations = xml_parser.get_approximator_configurations_from(path_to_xml_file)

    for training_configuration in training_configurations:
        approximator = trainer.train_from_configuration(training_configuration)
        path_to_parametrization = os.path.join(path_to_optics, training_configuration.destination_file_name)
        file = TFile.Open(path_to_parametrization, "update")
        approximator.Write(training_configuration.approximator_configuration.name_of_approximator, TObject.kOverwrite)
        file.Close()


if __name__ == "__main__":
    path_to_xml_file = getattr(args, "path to xml")
    path_to_optic = os.path.split(path_to_xml_file)[0]
    main(path_to_xml_file, path_to_optic)

