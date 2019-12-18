import argparse
import logging

parser = argparse.ArgumentParser(description="Generator plots of optical functions")
parser.add_argument("path to xml", metavar='path', type=str, help="Path to xml file")
parser.add_argument("name of folder with plots", metavar='folder name', type=str, help="Name of folder where plots will be stored")
parser.add_argument("-v", "--verbose", dest='logging-level', action='store_const', const=logging.DEBUG, default=logging.INFO, help="Verbosity of program, if set, logs from madx will be created")
args = parser.parse_args()


logger = logging.getLogger()
logger.setLevel(getattr(args, "logging-level"))


import visualization.optics_parameter_visualisation as plotter
import data.grid_configuration as grid_configuration_module
import os
import shutil
import xml_parser.approximator_training_configuration as app_conf
import matplotlib.pyplot as plt
import seaborn as sns
from data.parameters_names import ParametersNames as Parameters
from transporters.madx.ptc_twiss.configuration import PtcTwissConfiguration
from transporters.madx.ptc_track.configuration import PtcTrackConfiguration
from transporters.approximator.configuration import ApproximatorConfiguration


sns.set_style("whitegrid")


def get_particles():
    x_min = 0
    x_max = 0
    x_resolution = 1

    theta_x_min = 0
    theta_x_max = 0
    theta_x_resolution = 1

    y_min = 0
    y_max = 0
    y_resolution = 1

    theta_y_min = 0
    theta_y_max = 0
    theta_y_resolution = 1

    pt_min = -0.15
    pt_max = 0
    pt_resolution = 11

    grid_configuration = grid_configuration_module.CanonicalCoordinatesGridConfiguration.by_boundary(
        x_min, x_max, x_resolution,
        theta_x_min, theta_x_max, theta_x_resolution,
        y_min, y_max, y_resolution,
        theta_y_min, theta_y_max, theta_y_resolution,
        pt_min, pt_max, pt_resolution)

    particles = grid_configuration.generate_grid()
    return particles


path_to_xml_file = getattr(args, "path to xml")
path_to_optic = os.path.split(path_to_xml_file)[0]
output_dir = getattr(args, "name of folder with plots")

output_path = os.path.join(output_dir, "Optics_plots")
if os.path.isdir(output_path):
    shutil.rmtree(output_path)
os.makedirs(output_path)

configurations = app_conf.get_approximator_configurations_from(path_to_xml_file)

serialized_approximator_file_name = configurations[0].destination_file_name
path_to_approximator = os.path.join(path_to_optic, serialized_approximator_file_name)

for configuration in configurations:

    approximator_name = configuration.approximator_configuration.name_of_approximator
    s = configuration.transport_configuration.end_place.distance

    track_configuration = PtcTrackConfiguration.get_track_configuration_from_xml_configuration_object(
        configuration.transport_configuration)
    twiss_configuration = PtcTwissConfiguration.get_configuration_from_approximator_training_configuration_object(
        configuration.transport_configuration, True)
    approximator_configuration = ApproximatorConfiguration(path_to_approximator, approximator_name)

    particles = get_particles()

    title_sufix = ""
    stat_path = os.path.join(output_path, "Station_"+str(s))

    if not os.path.isdir(stat_path):
        os.makedirs(stat_path)

    transporter1_name = "ptc_twiss; madx 5.05.02"
    transporter2_name = "ptc_track"
    transporter3_name = "approximator"

    transporters = {
        transporter1_name: twiss_configuration,
        transporter2_name: track_configuration,
        transporter3_name: approximator_configuration
    }

    def save_plot_of(transported_parameter, depended_parameter, file_name):
        fig = plt.gcf()
        plotter.generate_and_plot_optical_functions(particles, transporters, transported_parameter, depended_parameter,
                                                    title_sufix=title_sufix)
        fig.savefig(os.path.join(stat_path, file_name))
        plt.clf()

    save_plot_of(Parameters.PT, Parameters.D_X, title_sufix + "PT_vs_D_X")
    save_plot_of(Parameters.PT, Parameters.D_Y, title_sufix + "PT_vs_D_Y")
    save_plot_of(Parameters.PT, Parameters.L_X, title_sufix + "PT_vs_L_X")
    save_plot_of(Parameters.PT, Parameters.L_Y, title_sufix + "PT_vs_L_Y")
    save_plot_of(Parameters.PT, Parameters.V_X, title_sufix + "PT_vs_V_X")
    save_plot_of(Parameters.PT, Parameters.V_Y, title_sufix + "PT_vs_V_Y")


