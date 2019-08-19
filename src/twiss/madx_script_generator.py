def generate_configuration_file(madx_configuration, row):
    """
    Create in current directory file "twiss_madx_script", which base on specified in configuration, but at begin add
    lines which specify values x, theta x, y, theta y, pt with values from row
    :param madx_configuration: TwissConfiguration object
    :param row: map with keys x, theta x, y, theta y, pt
    :return: name of created file
    """
    file_name = "twiss_madx_script"
    with open(file_name, "w") as file_object:
        file_object.write("x = " + str(row["x"]) + ";\n")
        file_object.write("theta_x = " + str(row["theta x"]) + ";\n")
        file_object.write("y = " + str(row["y"]) + ";\n")
        file_object.write("theta_y = " + str(row["theta y"]) + ";\n")
        file_object.write("pt = " + str(row["pt"]) + ";\n")
        with open(madx_configuration.path_to_madx_script) as source_file_object:
            for line in source_file_object:
                file_object.write(line)
    return file_name
