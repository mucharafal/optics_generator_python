import ROOT
from ROOT import gSystem, gInterpreter
import os


was_initialised = False


def initialise(path_to_project):
    # This lines should be invoked only once during program run
    # It initialize ROOT variables using in train and transport
    global was_initialised
    if not was_initialised:

        # Transport
        gInterpreter.ProcessLine("double input[5];")
        gInterpreter.ProcessLine("double output[5];")

        # Train
        gInterpreter.ProcessLine("double x_in[5];")
        gInterpreter.ProcessLine("Int_t mPowers[5];")
        gInterpreter.ProcessLine('char option[] = "k";')
        gInterpreter.ProcessLine('std::string dummy_name = "approximator";')

        # Load LHCOpticsApproximator class to ROOT
        os.environ['LD_LIBRARY_PATH'] = path_to_project + "/root_libs"
        gInterpreter.ProcessLine(".include " + path_to_project + "/src/root_classes/include")

        library_name = "LHCOpticsApproximator.so"
        path_to_library = os.path.join(path_to_project, "root_libs", library_name)

        gSystem.Load(path_to_library)

        # Read in approximator
        gInterpreter.ProcessLine('TFile *f;')

        was_initialised = True
