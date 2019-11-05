#!/bin/python3
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
    if len(sys.argv) == 3:
        main(sys.argv[1], sys.argv[2])
    else:
        print("Help:\n"
              "./make_parametrisation.py arg1 arg2 arg3\n"
              "arg1- path to xml file\n"
              "arg2- path to folder with optics (2017_matched ie)\n")
