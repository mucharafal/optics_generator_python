def get_configuration(transport_configuration):
    madx_template_file_name = transport_configuration.madx_template_name
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
    end_place = transport_configuration.get_end_place_configuration()

    command = end_place.name + " : marker;\n"
    command += "seqedit,sequence=" + end_place.beam + ";\n"
    command += "install,element=" + end_place.name + ",at=" + str(end_place.distance) + ",from= " \
               + end_place.name_of_place_from + ";\n"
    command += "endedit;\n"
    return command


def __get_use_command(transport_configuration):
    end_place = transport_configuration.get_end_place_configuration()

    command = "use, sequence = " + end_place.beam + ", range = " \
              + end_place.name_of_place_from + "/" + end_place.name + ";\n"

    return command
