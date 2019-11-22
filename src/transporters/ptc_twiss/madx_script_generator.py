from data.parameters_names import ParametersNames as Parameters


def generate_configuration_file(madx_configuration, row):
    """
    Create in current directory file "twiss_madx_script", which base on specified in configuration, but at begin add
    lines which specify values x, theta x, y, theta y, pt with values from row
    :param madx_configuration: PtcTwissConfiguration object
    :param row: map with keys x, theta x, y, theta y, pt
    :return: name of created file
    """
    # todo Beaware, that THETA_X = CROSSING_ANGLE!!! Have big impact on nominal optics
    file_name = "twiss_madx_script"
    with open(file_name, "w") as file_object:
        file_object.write("x = " + str(row[Parameters.X]) + ";\n")
        file_object.write("theta_x = " + str(row[Parameters.THETA_X]) + ";\n")
        file_object.write("y = " + str(row[Parameters.Y]) + ";\n")
        file_object.write("theta_y = " + str(row[Parameters.THETA_Y]) + ";\n")
        file_object.write("crossing_angle = " + str(row[Parameters.THETA_X]) + ";\n")
        file_object.write("pt = " + str(row[Parameters.PT]) + ";\n")
        with open(madx_configuration.path_to_madx_script) as source_file_object:
            for line in source_file_object:
                file_object.write(line)
    return file_name
