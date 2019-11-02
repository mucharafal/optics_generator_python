import ptc_twiss.madx_configuration as ptc_twiss_conf
import ptc_twiss.optical_functions as twiss_optics_parameters
import ptc_twiss.transporter as twiss_ptg
import ptc_track.madx_configuration as ptc_track_conf
import ptc_track.optical_functions as track_optics_parameters
import ptc_track.transporter as track_ptg
import visualization.optics_parameter_visualisation as plotter
import approximator.runner as approximator_runner
import approximator.optical_functions as app_op
import approximator.transporter as app_ptg
import xml_parser.approximator_training_configuration as app_conf
import data.grid_configuration as buc
import data.particles_generator as pg
import os
import shutil
import sys
import matplotlib.pyplot as plt
import seaborn as sns
import comparators.transport as transport
import models.train_model as tram
import models.approximator as stub_app
import matplotlib.pyplot as plt
from data.parameters_names import ParametersNames as Parameters

if len(sys.argv)<9:
    print("not enough arguments specified")
    print("arguments needed:\npath to the directory with the whole project\nname of directory containing used optic")
    print("name of the twiss script madx file\nname of the xml config file\nname of the directory where the output will be stored")
    print("name of the serialized approximator\nname of the approximator\nname of the folder containing the source code")
    exit()

sns.set_style("whitegrid")

#path_to_project = "/home/stormtrooper/Ducttape"
path_to_project=sys.argv[1]

#optic_folder_name = "optics/new/2016"
optic_folder_name=sys.argv[2]

#ptc_twiss_script_file_name = "ptc_twiss_script.madx"
ptc_twiss_script_file_name=sys.argv[3]

#xml_file_name = "configuration_reconst_beam1.xml"
xml_file_name=sys.argv[4]

#directory where output plots will be stored
output_dir=sys.argv[5]

output_path=os.path.join(output_dir,"Error_plots")
if os.path.isdir(output_path): shutil.rmtree(output_path)
os.makedirs(output_path)

#item_number = 2

#serialized_approximator_file_name = "parametrization_6500GeV_0p4_185_reco.root"
#approximator_name = "ip5_to_station_220_h_2_lhcb1"
serialized_approximator_file_name=sys.argv[6]
approximator_name=sys.argv[7]

#name_of_folder_with_sources = "optics_generator_python"
name_of_folder_with_sources=sys.argv[8]

#s = 219.55 #position of station ip5 station_220_h_2 from id=3 in xml, redundant and can be removed after implementing reading from config
#item_number = 2 #id from xml file -1

path_to_xml_file = os.path.join(path_to_project, optic_folder_name, xml_file_name)
config=app_conf.get_xml_configuration_from_file(path_to_xml_file)

path_to_optic = os.path.join(path_to_project, optic_folder_name)

path_to_sources = os.path.join(path_to_project, name_of_folder_with_sources)
path_to_approximator = os.path.join(path_to_optic, serialized_approximator_file_name)
approximator = approximator_runner.get_approximator(path_to_sources, path_to_approximator, approximator_name)
approximator_transporter = app_ptg.get_transporter(approximator)

title_sufix = r"2016"
transporter1 = "ptc_track"
transporter2 = "approximator"

for child in config:
    item_number=int(child.attrib.get("id"))-1
    s=float(child.attrib.get("to_marker_s_pos"))

    twiss_configuration = ptc_twiss_conf.TwissConfiguration.get_configuration_from_file(path_to_xml_file, item_number, s)
    #print(twiss_configuration.transport_configuration.madx_script_file_name)
    twiss_transporter = twiss_ptg.get_transporter(twiss_configuration)

    track_configuration = ptc_track_conf.TrackConfiguration.get_track_configuration_from_xml_file(path_to_xml_file, item_number, path_to_optic)
    track_transporter = track_ptg.get_transporter(track_configuration)

    transporters = {
        transporter1: track_transporter,
        transporter2: approximator_transporter
    }

    # Parameters of training
    # x_min = x_mean - delta_x
    # x_max = x_mean + delta_x
    x_mean = 0.0
    delta_x = 4e-3
    theta_x_mean = 0.000
    delta_theta_x = 1.3e-3
    y_mean = 0.0
    delta_y = 4e-3
    theta_y_mean = 0.00
    delta_theta_y = 1.3e-3
    pt_mean = -0.15
    delta_pt = 0.2

    number_of_x_values = 1
    number_of_theta_x_values = 1
    number_of_y_values = 1
    number_of_theta_y_values = 1
    number_of_pt_values = 12000

    bunch_configuration = buc.GridConfiguration.from_sigma(x_mean, delta_x, number_of_x_values,
                                                            theta_x_mean, delta_theta_x, number_of_theta_x_values,
                                                            y_mean, delta_y, number_of_y_values,
                                                            theta_y_mean, delta_theta_y, number_of_theta_y_values,
                                                            pt_mean, delta_pt, number_of_pt_values)

    #bunch_configuration=buc.GridConfiguration.get_configuration_from_xml(config)
    particles = pg.generate_from_range(bunch_configuration)

    x_mean = 0.0
    delta_x = 4e-3
    theta_x_mean = 0.000
    delta_theta_x = 1.3e-3
    y_mean = 0.0
    delta_y = 4e-3
    theta_y_mean = 0.00
    delta_theta_y = 1.3e-3
    pt_mean = -0.15
    delta_pt = 0.15

    number_of_x_values = 1
    number_of_theta_x_values = 1
    number_of_y_values = 1
    number_of_theta_y_values = 1
    number_of_pt_values = 12000

    bunch_configuration = buc.GridConfiguration.from_sigma(x_mean, delta_x, number_of_x_values,
                                                            theta_x_mean, delta_theta_x, number_of_theta_x_values,
                                                            y_mean, delta_y, number_of_y_values,
                                                            theta_y_mean, delta_theta_y, number_of_theta_y_values,
                                                            pt_mean, delta_pt, number_of_pt_values)

    #bunch_configuration=buc.GridConfiguration.get_configuration_from_xml(config)
    particles = pg.generate_from_range(bunch_configuration)

    #fig = plt.gcf()
    #fig.set_size_inches(5, 5)

    title_sufix = "2016 optics\nError over training scope\nC++ code"

    #beginning of title is geberated automatically based on what the plot represents
    #axes = transport.compare(particles, transporters, Parameters.Y, Parameters.PT, plot_function=sns.scatterplot, title_sufix=title_sufix)
    #axes.set_ylim(-4,4) #to be removed, various optics can have various ranges
    # axes.set_yticks(list(-12.5 + x * 2.5 for x in range(11)))
    axes = plt.gca()

    #fig = plt.gcf()
    #fig.set_size_inches(40,20) #to be removed, various optics can have various ranges

    title_sufix = r"-450 $\mu$rad < $\theta_x < 450 \mu$rad"

    #PT -loss of momentum
    #X,Y - position
    #THETA_X, THETA_Y - angel between corresponding axis of accelerator and vectors of speed in X and Y
    '''
    transport.compare(particles, transporters, Parameters.X, Parameters.PT, title_sufix=title_sufix, ax=axes[0][0])
    transport.compare(particles, transporters, Parameters.THETA_X, Parameters.PT, title_sufix=title_sufix, ax=axes[0][1])
    transport.compare(particles, transporters, Parameters.Y, Parameters.PT, title_sufix=title_sufix, ax=axes[1][0])
    transport.compare(particles, transporters, Parameters.THETA_Y, Parameters.PT, title_sufix=title_sufix, ax=axes[1][1])
    '''

    stat_path=os.path.join(output_path,"Station_"+str(s))
    if not os.path.isdir(stat_path): os.makedirs(stat_path)

    fig = plt.gcf()
    #fig.set_size_inches(5, 5)
    axes = transport.compare(particles, transporters, Parameters.X, Parameters.PT, title_sufix=title_sufix)
    fig.savefig(os.path.join(stat_path,title_sufix+"_X_PT"))
    plt.clf()
    #axes.set_ylim(-2, 2)

    fig = plt.gcf()
    #fig.set_size_inches(5, 5)
    axes = transport.compare(particles, transporters, Parameters.THETA_X, Parameters.PT, title_sufix=title_sufix)
    fig.savefig(os.path.join(stat_path,title_sufix+"_THETA_X_PT"))
    plt.clf()
    #axes.set_ylim(-10, 10)

    fig = plt.gcf()
    #fig.set_size_inches(5, 5)
    axes = transport.compare(particles, transporters, Parameters.Y, Parameters.PT, title_sufix=title_sufix)
    fig.savefig(os.path.join(stat_path,title_sufix+"_Y_PT"))
    plt.clf()
    #axes.set_ylim(-4, 4)

    fig = plt.gcf()
    #fig.set_size_inches(5, 5)
    axes = transport.compare(particles, transporters, Parameters.THETA_Y, Parameters.PT, title_sufix=title_sufix)
    fig.savefig(os.path.join(stat_path,title_sufix+"_THETA_Y_PT"))
    plt.clf()
    #axes.set_ylim(-40, 40)
