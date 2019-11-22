from ROOT import gSystem, gInterpreter


was_initialised = False


def initialise():
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

        library_name = "LHCOpticsApproximator.so"

        gSystem.Load(library_name)

        # Read in approximator
        gInterpreter.ProcessLine('TFile *f;')

        was_initialised = True
