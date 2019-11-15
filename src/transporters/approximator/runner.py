import ROOT
from ROOT import gSystem, gInterpreter
import numpy as np
import utils.root_initializer as root_initializer


approximators_counter = 0


def get_approximator(path_to_file, approximator_name):
    """
    Get approximator_test from file.
    :param path_to_file: path to file with serialized LHCOpticsApproximator object
    :param approximator_name: name of approximator_test in ROOT file
    :return: approximator_test object
    """
    root_initializer.initialise()

    global approximators_counter
    root_pointer_name = "apr" + str(approximators_counter)
    approximators_counter += 1

    gInterpreter.ProcessLine('f=TFile::Open("' + path_to_file + '");')
    gInterpreter.ProcessLine(
        'std::auto_ptr<LHCOpticsApproximator> ' + root_pointer_name + ' = std::auto_ptr<LHCOpticsApproximator>((LHCOpticsApproximator*) f->Get("' + approximator_name + '"));')
    gInterpreter.ProcessLine("f->Close()")
    approximator = getattr(ROOT, root_pointer_name)
    return approximator


def transport(approximator, matrix):
    """
    Transport particles described in matrix
    :param approximator: LHCOpticsApproximator object
    :param matrix: each row should contain begining position of particle- x, theta x, y, theta y, pt
    :return: matrix with result of transport, where each row contain x, theta x, y, theta y, t, pt
    """
    # Using such containers is probably the easiest way to work with root objects
    # It will contain input values and output values will be stored in them
    input_container = ROOT.input
    output_container = ROOT.output
    end_positions = list()
    for index, row in enumerate(matrix):
        for i, value in enumerate(row):
            input_container[i] = value
        approximator.Transport(input_container, output_container)
        end_position = []
        for i, value in enumerate(output_container):
            end_position.append(value)
        end_positions.append(end_position)
    return np.array(end_positions)
