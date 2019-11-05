import ptc_twiss.madx_configuration as ptc_twiss_conf
import ptc_twiss.transporter as twiss_ptg
import ptc_track.madx_configuration as ptc_track_conf
import ptc_track.transporter as track_ptg
import approximator.runner as approximator_runner
import approximator.transporter as app_ptg
import xml_parser.approximator_training_configuration as app_conf
import data.grid_configuration as buc
import data.particles_generator as pg
import os
import shutil
import sys
import seaborn as sns
import comparators.transport as transport
import matplotlib.pyplot as plt
from data.parameters_names import ParametersNames as Parameters

if len(sys.argv) < 9:
    print("not enough arguments specified")
    print("arguments needed:\npath to the directory with the whole project\nname of directory containing used optic")
    print("name of the twiss script madx file\nname of the xml config file\nname of the directory where the output will be stored")
    print("name of the serialized approximator\nname of the approximator\nname of the folder containing the source code")
    exit()

sns.set_style("whitegrid")

# path_to_project = "/home/stormtrooper/Ducttape"
path_to_project = sys.argv[1]

# optic_folder_name = "optics/new/2016"
optic_folder_name = sys.argv[2]

# ptc_twiss_script_file_name = "ptc_twiss_script.madx"
ptc_twiss_script_file_name = sys.argv[3]

# xml_file_name = "configuration_reconst_beam1.xml"
xml_file_name = sys.argv[4]

# directory where output plots will be stored
output_dir = sys.argv[5]

output_path = os.path.join(output_dir, "Error_plots")
if os.path.isdir(output_path): 
    shutil.rmtree(output_path)
os.makedirs(output_path)

# serialized_approximator_file_name = "parametrization_6500GeV_0p4_185_reco.root"
# approximator_name = "ip5_to_station_220_h_2_lhcb1"
serialized_approximator_file_name = sys.argv[6]
approximator_name = sys.argv[7]

# name_of_folder_with_sources = "optics_generator_python"
name_of_folder_with_sources = sys.argv[8]

# item_number = 2 #id from xml file -1

path_to_xml_file = os.path.join(path_to_project, optic_folder_name, xml_file_name)
configurations = app_conf.get_xml_configuration_from_file(path_to_xml_file)

path_to_optic = os.path.join(path_to_project, optic_folder_name)

path_to_sources = os.path.join(path_to_project, name_of_folder_with_sources)
path_to_approximator = os.path.join(path_to_optic, serialized_approximator_file_name)
approximator = approximator_runner.get_approximator(path_to_sources, path_to_approximator, approximator_name)
approximator_transporter = app_ptg.get_transporter(approximator)

title_sufix = r"2016"
transporter1 = "ptc_track"
transporter2 = "approximator"

for configuration in configurations:
    item_number = int(configuration.attrib.get("id"))-1
    s = float(configuration.attrib.get("to_marker_s_pos"))

    twiss_configuration = ptc_twiss_conf.TwissConfiguration.get_configuration_from_file(path_to_xml_file, item_number, s)
    twiss_transporter = twiss_ptg.get_transporter(twiss_configuration)

    track_configuration = ptc_track_conf.TrackConfiguration.get_track_configuration_from_xml_file(path_to_xml_file, item_number, path_to_optic)
    track_transporter = track_ptg.get_transporter(track_configuration)

    transporters = {
        transporter1: track_transporter,
        transporter2: approximator_transporter
    }

    test_sample_configuration = buc.GridConfiguration.get_configuration_from_xml(configuration)
    particles = pg.generate_from_range(test_sample_configuration)

    title_sufix = "2016 optics\nError over training scope\nC++ code\n"

    # beginning of title is generated automatically based on what the plot represents
    # axes = transport.compare(particles, transporters, Parameters.Y, Parameters.PT, plot_function=sns.scatterplot,
    # title_sufix=title_sufix)
    # axes.set_ylim(-4,4) #to be removed, various optics can have various ranges
    # axes.set_yticks(list(-12.5 + x * 2.5 for x in range(11)))
    axes = plt.gca()

    title_sufix += r"-450 $\mu$rad < $\theta_x < 450 \mu$rad"

    # PT -loss of momentum
    # X,Y - position
    # THETA_X, THETA_Y - angel between corresponding axis of accelerator and vectors of speed in X and Y

    stat_path = os.path.join(output_path, "Station_"+str(s))
    
    if not os.path.isdir(stat_path): 
        os.makedirs(stat_path)

    def save_plot_of(transported_parameter, depended_parameter, file_name):
        fig = plt.gcf()
        transport.compare(particles, transporters, transported_parameter, depended_parameter, title_sufix=title_sufix)
        fig.savefig(os.path.join(stat_path, file_name))
        plt.clf()

    save_plot_of(Parameters.X, Parameters.PT, title_sufix + "_X_PT")
    save_plot_of(Parameters.THETA_X, Parameters.PT, title_sufix + "_THETA_X_PT")
    save_plot_of(Parameters.Y, Parameters.PT, title_sufix + "_Y_PT")
    save_plot_of(Parameters.THETA_Y, Parameters.PT, title_sufix + "_THETA_Y_PT")
