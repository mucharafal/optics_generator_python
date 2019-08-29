import models.train_model as trainer
import xml.etree.ElementTree as ET
from ROOT import TObject, TFile
import os


def main(path_to_xml_file, path_to_project, path_to_optics):
    tree = ET.parse(path_to_xml_file)  # load configuration from xml file
    root = tree.getroot()

    number_of_stations = len(root)

    for number_of_station in range(number_of_stations):
        approximator = trainer.train_from_xml_configuration(path_to_optics, path_to_xml_file, number_of_station,
                                                            path_to_project)
        path_to_parametrization = os.path.join(path_to_optics, root[number_of_station].attrib["optics_parametrisation_file"])
        file = TFile.Open(path_to_parametrization, "update")
        approximator.Write(root[number_of_station].attrib["optics_parametrisation_name"], TObject.kOverwrite)
        file.Close()

