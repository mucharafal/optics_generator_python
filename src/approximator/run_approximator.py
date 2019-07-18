import ROOT
from ROOT import gSystem, gInterpreter
import numpy as np
import sys
import root_numpy as rn
# before use you have to set LD_LIBRARY_PATH to folder root_libs!!!


def get_approximator_from_file(file_name):
    project_dir = "/home/rafalmucha/Pobrane/optic/optics_generator_python"

    gInterpreter.ProcessLine(".include " + project_dir + "/src/root_classes/include")
    gSystem.Load("LHCOpticsApproximator")
    gInterpreter.ProcessLine('TFile *f=TFile::Open("/home/rafalmucha/Pobrane/optic/opticsGenerator/src/parametrization_6500GeV_0p4_185_transp.root ");')
    gInterpreter.ProcessLine('std::auto_ptr<LHCOpticsApproximator> apr_near150 = std::auto_ptr<LHCOpticsApproximator>((LHCOpticsApproximator*) f->Get("ip5_to_beg_150_station_lhcb1"));')
    gInterpreter.ProcessLine("f->Close()")
    aperture = ROOT.apr_near150
    return aperture


def transport(approximator, matrix):
    end_positions = np.empty((matrix.shape[0], 5))
    for index, row in enumerate(matrix):
        approximator.Transport(row, end_positions[index])
    return end_positions


def dict_to_ttree(dictionary):
    in_arr = dictionary["start"]
    print(in_arr.shape)
    names = ["number", "inout", "x_in", "theta_x_in", "y_in", "theta_y_in", "t", "ksi_in", "s_in", "e"]
    formats = [np.float64, np.float64, np.float64, np.float64, np.float64, np.float64, np.float64, np.float64, np.float64, np.float64]
    prefix = "def_"
    out_names = ["number", "inout", "x_out", "theta_x_out", "y_out", "theta_y_out", "t", "ksi_out", "s_out", "e"]
    better_out_names = [prefix + x for x in out_names]
    out_arr = dictionary["end"]
    print(out_arr.shape)
    dtypes = np.dtype(list(zip(names, formats)))
    in_arr = [tuple(row) for row in in_arr]
    out_arr = [tuple(row) for row in out_arr]
    out_arr = np.array(out_arr, dtype=np.dtype(list(zip(better_out_names, formats))))
    in_arr = np.array(in_arr, dtype=dtypes)
    in_tree = rn.array2tree(in_arr, "tree")
    in_tree.Print()
    out_tree = rn.array2tree(out_arr, "tree")
    trees = ROOT.TList()
    trees.Add(out_tree)
    result_tree = in_tree.Merge(trees)
    in_tree.Print()
    return in_tree

