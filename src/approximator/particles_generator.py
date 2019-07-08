import numpy as np
"""
File include some methods to generate file "part.in" as input for madx.
There is two ways generating:
- random with values from given range
- with given step from given range
"""


def generate_from_range(x_min, x_max, number_of_x_in_grid,
                        theta_x_min, theta_x_max, number_of_theta_x_in_grid,
                        y_min, y_max, number_of_y_in_grid,
                        theta_y_min, theta_y_max, number_of_theta_y_in_grid,
                        t_min, t_max, number_of_t_in_grid,
                        pt_min, pt_max, number_of_pt_in_grid,
                        oridinal_number_name="mken",
                        x_name="trx",
                        theta_x_name="trpx",
                        y_name="try",
                        theta_y_name="trpy",
                        t_name="tt",
                        pt_name="tpt"):
    with open("part.in", "w") as output_file:
        write_header(output_file)   # Write header needed by madx

        names = [oridinal_number_name, x_name, theta_x_name, y_name, theta_y_name, t_name, pt_name]
        types = [str, float, float, float, float, float, float]
        write_specification_of_row(names, types, output_file)

        # Create and initialize vectors with coordinates of particles in grid
        x_vector = np.linspace(x_min, x_max, number_of_x_in_grid)
        theta_x_vector = np.linspace(theta_x_min, theta_x_max, number_of_theta_x_in_grid)
        y_vector = np.linspace(y_min, y_max, number_of_y_in_grid)
        theta_y_vector = np.linspace(theta_y_min, theta_y_max, number_of_theta_y_in_grid)
        t_vector = np.linspace(t_min, t_max, number_of_t_in_grid)
        pt_vector = np.linspace(pt_min, pt_max, number_of_pt_in_grid)

        # Create grid, which is carthesian product of above coordinates vectors
        grid = np.array(np.meshgrid(x_vector, theta_x_vector, y_vector, theta_y_vector, t_vector, pt_vector))\
            .T.reshape(-1, 6)

        print(grid)

        save_matrix_to_file(grid, output_file)


def generate_particles_randomly(x_min, x_max,
                                theta_x_min, theta_x_max,
                                y_min, y_max,
                                theta_y_min, theta_y_max,
                                t_min, t_max,
                                pt_min, pt_max,
                                number_of_particles,
                                oridinal_number_name="mken",
                                x_name="trx",
                                theta_x_name="trpx",
                                y_name="try",
                                theta_y_name="trpy",
                                t_name="tt",
                                pt_name="tpt"):
    """
    Function to generate file part.in. Range of values of every particles is specified as input.
    """
    with open("part.in", "w") as output_file:
        min_values = [x_min, theta_x_min, y_min, theta_y_min, t_min, pt_min]
        max_values = [x_max, theta_x_max, y_max, theta_y_max, t_max, pt_max]
        number_of_parameters = 6
        max_vector = np.zeros((1, number_of_parameters))
        min_vector = np.zeros((1, number_of_parameters))
        for i in range(number_of_parameters):
            max_vector[0][i] = max_values[i]
            min_vector[0][i] = min_values[i]

        grid = (max_vector - min_vector) * np.random.random_sample((number_of_particles, number_of_parameters)) \
            + min_vector

        write_header(output_file)
        # disclaimer: trx = x ; trpx = px ; try = y ...
        names = [oridinal_number_name, x_name, theta_x_name, y_name, theta_y_name, t_name, pt_name]
        types = [str, float, float, float, float, float, float]
        write_specification_of_row(names, types, output_file)
        save_matrix_to_file(grid, output_file)


def write_header(file_object):
    """
    Write a header in madx format to file object given as parameter. Helper function for generate_particles
    :param file_object: file to which header would be added
    """
    file_object.write('@ NAME             %07s "PARTICLES"\n')
    file_object.write('@ TYPE             %04s "USER"\n')
    file_object.write('@ TITLE            %34s "EVENT"\n')
    file_object.write('@ ORIGIN           %19s "MAD-X 3.00.03 Linux"\n')
    file_object.write('@ DATE             %08s "22/02/06"\n')  # todo add current date
    file_object.write('@ TIME             %08s "11.11.11"\n')


def write_specification_of_row(names, types, file_object):
    # Write names of columns
    file_object.write("*")
    for name in names:
        file_object.write("\t"+name)
    file_object.write("\n")

    # todo complete this map
    type_names = {
        str: '%s',
        float: '%le'
    }

    # Write names of types
    file_object.write("$")
    for column_type in types:
        file_object.write("\t"+type_names[column_type])
    file_object.write("\n")


def save_matrix_to_file(matrix, file_object):
    grid_size = len(matrix)
    for i in range(grid_size):
        line = '"' + str(i + 1) + '" '
        for n in matrix[i]:
            line += str(n) + " "
        line += "\n"
        file_object.write(line)

