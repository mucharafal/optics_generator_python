import sys


if len(sys.argv) < 5:
    print("not enough arguments specified")
    print("arguments needed:\npath to the directory with the whole project\nname of directory containing used optic")
    print("name of the xml config file\nname of the directory where the output will be stored")
    exit()


import transporters.ptc_twiss.configuration as twiss_configuration_gen
import transporters.ptc_track.configuration as track_configuration_gen
import transporters.approximator.configuration as approximator_configuration_gen
import visualization.optics_parameter_visualisation as plotter
import data.grid_configuration as grid_configuration_module
import os
import shutil
import sys
import xml_parser.approximator_training_configuration as app_conf
import matplotlib.pyplot as plt
import seaborn as sns
from data.parameters_names import ParametersNames as Parameters


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


sns.set_style("whitegrid")
path_to_project = sys.argv[1]
folder_name = sys.argv[2]
xml_file_name = sys.argv[3]
output_dir = sys.argv[4]

output_path = os.path.join(output_dir, "Optics_plots")
if os.path.isdir(output_path):
    shutil.rmtree(output_path)
os.makedirs(output_path)

path_to_xml_file = os.path.join(path_to_project, folder_name, xml_file_name)
configurations = app_conf.get_xml_configuration_from_file(path_to_xml_file)

serialized_approximator_file_name=configurations[0].attrib.get("optics_parametrisation_file")
path_to_approximator = os.path.join(path_to_project, folder_name, serialized_approximator_file_name)

for configuration in configurations:
    approximator_name=configuration.attrib.get("optics_parametrisation_name")
    item_number=int(configuration.attrib.get("id"))-1
    s=float(configuration.attrib.get("to_marker_s_pos"))

    twiss_configuration = twiss_configuration_gen.TwissConfiguration.get_configuration_from_file(path_to_xml_file, item_number, s)
    track_configuration = track_configuration_gen.TrackConfiguration.get_track_configuration_from_xml_file(path_to_xml_file, item_number)
    approximator_configuration = approximator_configuration_gen.ApproximatorConfiguration(path_to_approximator, approximator_name)

    particles = get_particles()

    title_sufix = folder_name
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
        plotter.plot_optical_functions(particles, transporters, transported_parameter, depended_parameter, title_sufix=title_sufix)
        fig.savefig(os.path.join(stat_path, file_name))
        plt.clf()

    save_plot_of(Parameters.PT, Parameters.D_X, title_sufix + "PT_D_X")
    save_plot_of(Parameters.PT, Parameters.D_Y, title_sufix + "PT_D_Y")
    save_plot_of(Parameters.PT, Parameters.L_X, title_sufix + "PT_L_X")
    save_plot_of(Parameters.PT, Parameters.L_Y, title_sufix + "PT_L_Y")
    save_plot_of(Parameters.PT, Parameters.V_X, title_sufix + "PT_V_X")
    save_plot_of(Parameters.PT, Parameters.V_Y, title_sufix + "PT_V_Y")


