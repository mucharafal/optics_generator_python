def get_configuration(transport_configuration):
    madx_template_file_name = transport_configuration.madx_input_script_file_name
    marker_definition_and_use_command = __get_command(transport_configuration)
    with open(madx_template_file_name, "r") as madx_file:
        return __parse(madx_file, marker_definition_and_use_command)


def __parse(file_object, use_command):
    file_content = file_object.read()
    parsed_file_content = file_content.replace("#marker_and_use_command#", use_command)
    return parsed_file_content


def __get_command(transport_configuration):
    marker_definition = __get_end_place_definition(transport_configuration)
    use_command = __get_use_command(transport_configuration)
    return marker_definition + use_command


def __get_end_place_definition(transport_configuration):
    command = transport_configuration.end_place_name + " : marker;\n"
    command += "seqedit,sequence=" + transport_configuration.beam_name + ";\n"
    command += "install,element=" + transport_configuration.end_place_name + ",at=" + \
               str(transport_configuration.end_place_distance) + ",from= " \
               + transport_configuration.start_place_name + ";\n"
    command += "endedit;\n"
    return command


def __get_use_command(transport_configuration):
    command = "use, sequence = " + transport_configuration.beam_name + ", range = " \
              + transport_configuration.start_place_name + "/" + transport_configuration.end_place_name + ";\n"

    return command
