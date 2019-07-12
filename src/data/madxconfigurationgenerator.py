import xml.etree.ElementTree as ET
import re
import os


def __get_tokens(conf, places):
    tokens = dict()
    tokens["header_placement"] = "! defines a macro to read initial coordinates\n"
    tokens["header_placement"] += "getpart(nx): macro = {\n"
    tokens["header_placement"] += " ex   = table(myevent,nx,trx);\n"
    tokens["header_placement"] += " epx   = table(myevent,nx,trpx);\n"
    tokens["header_placement"] += " ey   = table(myevent,nx,try);\n"
    tokens["header_placement"] += " epy   = table(myevent,nx,trpy);\n"
    tokens["header_placement"] += " et    = table(myevent,nx,trt);\n"
    tokens["header_placement"] += " ept    = table(myevent,nx,trpt);\n"
    tokens["header_placement"] += " value,ex,epx,ey,epy,et,ept;\n"
    tokens["header_placement"] += "}\n"

    def scoring_plane_definition():
        def generate_string(marker_name, beam, marker_pos):
            string = marker_name + " : marker;\n"
            string += "seqedit,sequence=" + beam + ";\n"
            string += "install,element=" + marker_name + ",at=" + marker_pos + ",from=ip5;\n"
            string += "endedit;\n"
            return string
        result = ""
        if conf['define_from'] == '1':
            result += generate_string(conf['from_marker_name'], conf["beam"], conf["from_marker_s_pos"])
        if conf['define_to'] == '1':
            result += generate_string(conf['to_marker_name'], conf["beam"], conf["to_marker_s_pos"])
        return result

    tokens["scoring_plane_definition"] = scoring_plane_definition()
    tokens["start_point"] = conf["from_marker_name"]
    tokens["end_point"] = conf["to_marker_name"]

    def ptc_prefix():
        if conf["aperture_limit"] != '0':
            return ""
        else:
            return "ptc_"

    def scoring_plane_placement():
        result = ""
        prefix = ptc_prefix()
        result += prefix + "observe,place=" + conf["to_marker_name"] + ";\n"
        for place in places:
            result += prefix + "observe,place=" + place["to_marker_name"] + ";\n"
        return result

    tokens["scoring_plane_placement"] = scoring_plane_placement()
    tokens["import_particles"] = "readmytable,file=part.in,table=myevent;\n"
    tokens["insert_particles"] = "! read in initial coordinates at set for tracking\n"
    tokens["insert_particles"] += "   n=1;\n"
    tokens["insert_particles"] += "   while ( n < " + conf["number_of_part_per_sample"] + " + 1 ) {\n"
    tokens["insert_particles"] += "      exec,getpart($n);\n"
    tokens["insert_particles"] += "      " + ptc_prefix() + "start,x=ex,px=epx,y=ey,py=epy,t=et,pt=ept;\n"
    tokens["insert_particles"] += "      n = n + 1;\n"
    tokens["insert_particles"] += "   }"
    tokens["output_mad_file"] = "track"

    def options():
        result = ""
        if conf["aperture_limit"] != '0':
            result += ",aperture"
            result += ",recloss"
        return result

    tokens["options"] = options()
    tokens["save_lost_particles"] = "write,table=trackloss,file=\"trackloss\"\n" if conf["aperture_limit"] != 0 else "\n"
    tokens["beam_type"] = "lhcb2" if conf["beam"] == "lhcb2" else "lhcb1"
    tokens["beam_bv"] = "-1" if conf["beam"] == "lhcb2" else "+1"
    return tokens


def generate_configuration_file_from_source(path_to_configuration, xml_configuration_file_name):
    """
    Generate configuration file for madx using configuration in xml file.
    File is generated in folder with configuration.
    Parameters
    ----------
    path_to_configuration- path to folder with configuration files- xml and rest files needed to create configuration-
    check xml file.
    xml_configuration_file_name- name of file with configuration to create madx script.
    Returns
    -------
    Path to generated file.
    """
    xml_configuration_file_path = os.path.join(path_to_configuration, xml_configuration_file_name)

    tree = ET.parse(xml_configuration_file_path)        # load configuration from xml file
    root = tree.getroot()

    places = [x.attrib for x in root[0]]

    configuration = root[0].attrib

    sourcePath = path_to_configuration + "/" + configuration['base_mad_conf_file']
    sourceFile = open(sourcePath, 'r')

    destinyFile = open(sourcePath + "_processed", "w")
    source_path = path_to_configuration + "/" + configuration['base_mad_conf_file']
    destiny_path = path_to_configuration + "/" + configuration['processed_mad_conf_file']

    with open(source_path, 'r') as sourceFile:
        with open(destiny_path, "w") as destinyFile:
            token_dict = __get_tokens(configuration, places)

            for line in sourceFile:
                tokens_in_line = re.findall("#[a-z_A-Z0-9]*#", line)
                for i in tokens_in_line:
                    index = i.replace("#", "")
                    line = line.replace(i, token_dict[index])
                destinyFile.write(line)

    destinyFile.close()
    sourceFile.close()
    return destiny_path


def generate_configuration_file(path_to_configuration,
                                ksi,
                                number_of_particles_on_input):
    file_name = "configuration.madx"
    with open(file_name, "w") as configuration_file:
        configuration_file.write('''option, -echo, -info,  -warn;

! defines a macro to read initial coordinates
getpart(nx): macro = {
 ex   = table(myevent,nx,trx);
 epx   = table(myevent,nx,trpx);
 ey   = table(myevent,nx,try);
 epy   = table(myevent,nx,trpy);
 et    = table(myevent,nx,trt);
 ept    = table(myevent,nx,trpt);
 value,ex,epx,ey,epy,et,ept;
}


set,format="4.12e";''')
        configuration_file.write('call, file = "' + path_to_configuration + '/2016/lhc_as-built.seq";')
        configuration_file.write('call, file = "' + path_to_configuration + '/2016/opt_inj_colltunes.madx";')
        configuration_file.write("DELTA_AP = " + str(ksi) + ";")
        configuration_file.write("bunch_size = " + str(number_of_particles_on_input) + ";")
        configuration_file.write('''on_sep5=0;
px.ip5=185e-6;
!y.ip5=5.500000000000000e-04;
beta.ip5=0.400 ;

! Beam definition
beam, sequence=lhcb1, bv= 1, energy=6500,  particle=proton,
  npart=1.2e11,kbunch=2748, ex=7.29767146889e-09,ey=7.29767146889e-09;
beam, sequence=lhcb2, bv=-1, energy=6500,  particle=proton,
  npart=1.2e11,kbunch=2748, ex=7.29767146889e-09,ey=7.29767146889e-09;

use,sequence=lhcb1;
''')
        configuration_file.write('call, file="' + path_to_configuration + 'temporary_perturbation.madx";')
        configuration_file.write('call, file="' + path_to_configuration + 'temporary_perturbation_b1.madx";')

        configuration_file.write('''

! Matching part start

MQXA.1R5, K1 := ((LSA.MQXA.1R5)*(PERTSTRMQXA.1R5 + DMQXA.1R5)) * (1), polarity=1;

select, flag=error, clear;
select,flag=error, pattern=MQXA.1R5;
ealign, dpsi= PERTDPSIMQXA.1R5 + DPSIMQXA.1R5   ;
MCBXH.1R5, KICK := (LSA.MCBXH.1R5*(1.0 + DELTA_K_MCBXH.1R5)) * (1), polarity=1;
MCBXV.1R5, KICK := (LSA.MCBXV.1R5*(1.0 + 0)) * (1), polarity=1;
MQXB.A2R5, K1 := ((LSA.MQXB.A2R5)*(PERTSTRMQXB.A2R5 + DMQXB.A2R5)) * (1), polarity=-1;

select, flag=error, clear;
select,flag=error, pattern=MQXB.A2R5;
ealign, dpsi= PERTDPSIMQXB.A2R5 + DPSIMQXB.A2R5   ;
MCBXH.2R5, KICK := (LSA.MCBXH.2R5*(1.0 + DELTA_K_MCBXH.2R5)) * (1), polarity=1;
MCBXV.2R5, KICK := (LSA.MCBXV.2R5*(1.0 + 0)) * (1), polarity=1;
MQXB.B2R5, K1 := ((LSA.MQXB.B2R5)*(PERTSTRMQXB.B2R5 + DMQXB.B2R5)) * (1), polarity=-1;

select, flag=error, clear;
select,flag=error, pattern=MQXB.B2R5;
ealign, dpsi= PERTDPSIMQXB.B2R5 + DPSIMQXB.B2R5   ;
MQSX.3R5, K1S := (LSA.MQSX.3R5*(1.0 + 0)) * (1), polarity=1;
MQXA.3R5, K1 := ((LSA.MQXA.3R5)*(PERTSTRMQXA.3R5 + DMQXA.3R5)) * (1), polarity=1;

select, flag=error, clear;
select,flag=error, pattern=MQXA.3R5;
ealign, dpsi= PERTDPSIMQXA.3R5 + DPSIMQXA.3R5   ;
MCBXH.3R5, KICK := (LSA.MCBXH.3R5*(1.0 + DELTA_K_MCBXH.3R5)) * (1), polarity=1;
MCBXV.3R5, KICK := (LSA.MCBXV.3R5*(1.0 + 0)) * (1), polarity=1;
MCSX.3R5, KNL := {0, 0, (LSA.MCSX.3R5*(1.0 + 0)) * (1)*l.MCSX, 0, 0, 0}, polarity=1;
MCTX.3R5, KNL := {0, 0, 0, 0, 0, (LSA.MCTX.3R5*(1.0 + 0)) * (1)*l.MCTX}, polarity=1;
MCOSX.3R5, KSL := {0, 0, 0, (LSA.MCOSX.3R5*(1.0 + 0)) * (1)*l.MCOSX}, polarity=1;
MCOX.3R5, KNL := {0, 0, 0, (LSA.MCOX.3R5*(1.0 + 0)) * (1)*l.MCOX}, polarity=1;
MCSSX.3R5, KSL := {0, 0, (LSA.MCSSX.3R5*(1.0 + 0)) * (1)*l.MCSSX, 0}, polarity=1;
MBXW.A4R5, K0 := (((LSA.MBXW.A4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.A4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBXW.B4R5, K0 := (((LSA.MBXW.B4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.B4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBXW.C4R5, K0 := (((LSA.MBXW.C4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.C4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBXW.D4R5, K0 := (((LSA.MBXW.D4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.D4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBXW.E4R5, K0 := (((LSA.MBXW.E4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.E4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBXW.F4R5, K0 := (((LSA.MBXW.F4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.F4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBRC.4R5.B1, K0 := (((LSA.MBRC.4R5.B1)*(1.0 + 0)) * (1)) , ANGLE := ( ((LSA.MBRC.4R5.B1)*(1.0 + 0)) * (1) * l.MBRC ), polarity=1;
MCBYV.A4R5.B1, KICK := (LSA.MCBYV.A4R5.B1*(1.0 + 0)) * (1), polarity=1;
MCBYH.4R5.B1, KICK := (LSA.MCBYH.4R5.B1*(1.0 + 0)) * (1), polarity=1;
MCBYV.B4R5.B1, KICK := (LSA.MCBYV.B4R5.B1*(1.0 + 0)) * (1), polarity=1;
MQY.4R5.B1, K1 := ((LSA.MQY.4R5.B1)*(PERTSTRMQY.4R5.B1 + DMQY.4R5.B1)) * (1), polarity=-1;

select, flag=error, clear;
select,flag=error, pattern=MQY.4R5.B1;
ealign, dpsi= PERTDPSIMQY.4R5.B1 + DPSIMQY.4R5.B1   ;
MQML.5R5.B1, K1 := ((LSA.MQML.5R5.B1)*(PERTSTRMQML.5R5.B1 + DMQML.5R5.B1)) * (1), polarity=1;

select, flag=error, clear;
select,flag=error, pattern=MQML.5R5.B1;
ealign, dpsi= PERTDPSIMQML.5R5.B1 + DPSIMQML.5R5.B1   ;
MCBCH.5R5.B1, KICK := (LSA.MCBCH.5R5.B1*(1.0 + 0)) * (1), polarity=1;

! Matching part end''')
        configuration_file.write('call, file="' + path_to_configuration + 'LSA.str";')
        configuration_file.write('''! Cycle
seqedit,sequence=lhcb1;flatten;cycle,start=IP5;endedit;

PI=3.141592654;
NORM_TRANS_EMITTANCE_M_RAD=3.5e-6;
PROTON_GAMMA=(6500/9.382720460000000e-01);


beg_150_station : marker;
seqedit,sequence=lhcb1;
install,element=beg_150_station,at=202.769,from=ip5;
endedit;



seqedit, sequence=lhcb1;flatten;cycle, start=IP5;endedit;

use,sequence=lhcb1;
!use,period=lhcb1,range=ip5/MQML.6R5.B1;
use,period=lhcb1,range=ip5/beg_150_station;''')
        # Probably above line is redundant
        configuration_file.write('call, file="' + path_to_configuration + 'temporary_perturbation_b1.madx";')

        configuration_file.write('''readmytable,file=part.in,table=myevent;


ptc_create_universe;
ptc_create_layout,model=2,method=6,nst=10,exact;
ptc_align;

! read in initial coordinates at set for tracking
   n=1;
   while ( n < bunch_size + 1 ) {
      exec,getpart($n);
      ptc_start,x=ex,px=epx,y=ey,py=epy,t=et,pt=ept;
      n = n + 1;
   } !ok

!ptc_start,x=x.ip5,px=DELTA_PX_B1,y=y.ip5,py=py.ip5;

ptc_observe,place=beg_150_station;
ptc_observe,place=mqxb.b2r5;
ptc_observe,place=mcbxh.3r5;
ptc_observe,place=tanc.4r5;
ptc_observe,place=mcbxh.2r5;
ptc_observe,place=mqxa.3r5;
ptc_observe,place=mqml.5r5.b1;
ptc_observe,place=mcbch.5r5.b1;
ptc_observe,place=mcbyv.b4r5.b1;
ptc_observe,place=tcl.4r5.b2;
ptc_observe,place=tcl.5r5.b2;
 !ok

ptc_track,icase=5,element_by_element,dump,onetable,deltap=(DELTA_AP + DELTADELTAP + DDELTADELTAP_B1 + TOTEMDELTAP),file="track";

ptc_track_end;
ptc_end;

return;
stop;''')
        return file_name

