import xml.etree.ElementTree as ET
import re

def get_tokens(conf, places):
    tokens = {}
    tokens["header_placement"] = "! defines a macro to read initial coordinates\n"
    tokens["header_placement"] += "getpart(nx): macro = {\n"
    tokens["header_placement"] += " ex   = table(myevent,nx,trx);\n"
    tokens["header_placement"] += " epx   = table(myevent,nx,trpx);\n"
    tokens["header_placement"] += " ey   = table(myevent,nx,try);\n"
    tokens["header_placement"] += " epy   = table(myevent,nx,trpy);\n"
    tokens["header_placement"] += " et    = table(myevent,nx,tt);\n"
    tokens["header_placement"] += " ept    = table(myevent,nx,tpt);\n"
    tokens["header_placement"] += " value,ex,epx,ey,epy,et,ept;\n"
    tokens["header_placement"] += "}\n"
    def scoring_plane_definition(conf):
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

    tokens["scoring_plane_definition"] = scoring_plane_definition(conf)
    tokens["start_point"] = conf["from_marker_name"]
    tokens["end_point"] = conf["to_marker_name"]
    def ptcPrefix(conf):
        if conf["aperture_limit"] != '0':
            return ""
        else:
            return "ptc_"
    def scoring_plane_placement(conf):
        result = ""
        prefix = ptcPrefix(conf)
        result += prefix + "observe,place=" + conf["to_marker_name"] + ";\n"
        for place in places:
            result += prefix + "observe,place=" + place["to_marker_name"] + ";\n"
        return result

    tokens["scoring_plane_placement"] = scoring_plane_placement(conf)
    tokens["import_particles"] = "readmytable,file=part.in,table=myevent;\n"
    tokens["insert_particles"] = "! read in initial coordinates at set for tracking\n"
    tokens["insert_particles"] += "   n=1;\n"
    tokens["insert_particles"] += "   while ( n < " + conf["number_of_part_per_sample"] + " + 1 ) {\n"
    tokens["insert_particles"] += "      exec,getpart($n);\n"
    tokens["insert_particles"] += "      " + ptcPrefix(conf) + "start,x=ex,px=epx,y=ey,py=epy,t=et,pt=ept;\n"
    tokens["insert_particles"] += "      n = n + 1;\n"
    tokens["insert_particles"] += "   }"
    tokens["output_mad_file"] = "track"

    def options(conf):
        result = ""
        if conf["aperture_limit"] != '0':
            result += ",aperture"
            result += ",recloss"
        return result

    tokens["options"] = options(conf)
    tokens["save_lost_particles"] =     "write,table=trackloss,file=\"trackloss\"\n"     if conf["aperture_limit"] != 0     else "\n"
    tokens["beam_type"] = "lhcb2" if conf["beam"] == "lhcb2" else "lhcb1"
    tokens["beam_bv"] = "-1" if conf["beam"] == "lhcb2" else "+1"
    return tokens

def generate_configuration_file(path_to_configuration, xml_configuration_file_name):
    """
    Generate configuration file for madx using configuration in xml file.

    File is generated in folder with configuration.

    Parameters
    ----------
    path_to_configuration- path to folder with configuration files- xml and rest files needed to create configuration- check xml file.

    xml_configuration_file_name- name of file with configuration to create madx script.

    Returns
    -------
    Path to generated file.
    """
    xml_configuration_file_path = path_to_configuration + "/" + xml_configuration_file_name

    tree = ET.parse(xml_configuration_file_path)        #load configuration from xml file
    root = tree.getroot()

    places = map(lambda x: x.attrib, list(root[0]))
    places = list(places)

    configuration = root[0].attrib

    sourcePath = path_to_configuration + "/" + configuration['base_mad_conf_file']
    destinyPath = path_to_configuration + "/" + configuration['processed_mad_conf_file']

    with open(sourcePath, 'r') as sourceFile:
        with open(destinyPath, "w") as destinyFile:
            token_dict = get_tokens(configuration, places)

            for line in sourceFile:
                tokens_in_line = re.findall("#[a-z_A-Z0-9]*#", line)
                for i in tokens_in_line:
                    index = i.replace("#", "")
                    line = line.replace(i, token_dict[index])
                destinyFile.write(line)

    return destinyPath