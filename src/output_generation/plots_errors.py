import transporters.ptc_track.configuration as track_configuration_gen
import transporters.approximator.configuration as approximator_configuration_gen
import data.grid_configuration as grid_configuration_module
import os
import shutil
import sys
import xml_parser.approximator_training_configuration as app_conf
import seaborn as sns
import comparators.transport as transport
import matplotlib.pyplot as plt
from data.parameters_names import ParametersNames as Parameters

if len(sys.argv) < 5:
    print("not enough arguments specified")
    print("arguments needed:\npath to the directory with the whole project\nname of directory containing used optic")
    print("name of the xml config file\nname of the directory where the output will be stored")
    exit()

sns.set_style("whitegrid")
path_to_project = sys.argv[1]
optic_folder_name = sys.argv[2]
xml_file_name = sys.argv[3]
output_dir = sys.argv[4]

output_path = os.path.join(output_dir, "Error_plots")
if os.path.isdir(output_path):
    shutil.rmtree(output_path)
os.makedirs(output_path)

path_to_xml_file = os.path.join(path_to_project, optic_folder_name, xml_file_name)
configurations = app_conf.get_xml_configuration_from_file(path_to_xml_file)

serialized_approximator_file_name=configurations[0].attrib.get("optics_parametrisation_file")
path_to_approximator = os.path.join(path_to_project, optic_folder_name, serialized_approximator_file_name)

path_to_optic = os.path.join(path_to_project, optic_folder_name)

transporter1 = "ptc_track"
transporter2 = "approximator"

for configuration in configurations:
    approximator_name=configuration.attrib.get("optics_parametrisation_name")
    item_number=int(configuration.attrib.get("id"))-1
    s=float(configuration.attrib.get("to_marker_s_pos"))

    track_configuration = track_configuration_gen.TrackConfiguration.get_track_configuration_from_xml_file(path_to_xml_file, item_number)
    approximator_configuration = approximator_configuration_gen.ApproximatorConfiguration(path_to_approximator, approximator_name)

    transporters = {
        transporter1: track_configuration,
        transporter2: approximator_configuration
    }

    test_sample_configuration = grid_configuration_module.GridConfiguration.get_configuration_from_xml(configuration)
    particles = test_sample_configuration.generate_randomly()

    title_sufix = optic_folder_name + "\nError over training scope\n"
    title_sufix += configuration.attrib.get("to_marker_name") + "; s = " + str(s)

    stat_path = os.path.join(output_path, "Station_"+str(s))

    if not os.path.isdir(stat_path):
        os.makedirs(stat_path)

    errors = transport.compare(particles, transporters)

    def save_plot_of(transported_parameter, depended_parameter, file_name):
        fig = plt.gcf()
        transport.plot(errors, transported_parameter, depended_parameter, title_sufix=title_sufix)
        fig.savefig(os.path.join(stat_path, file_name + ".jpg"))
        plt.clf()

    file_name_begin = title_sufix.replace("\n", "_") + "DELTA_"
    save_plot_of(Parameters.X, Parameters.PT, file_name_begin + "_X_vs_PT")
    save_plot_of(Parameters.THETA_X, Parameters.PT, file_name_begin + "_THETA_X_vs_PT")
    save_plot_of(Parameters.Y, Parameters.PT, file_name_begin + "_Y_vs_PT")
    save_plot_of(Parameters.THETA_Y, Parameters.PT, file_name_begin + "_THETA_Y_vs_PT")
