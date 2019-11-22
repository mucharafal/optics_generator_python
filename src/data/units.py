import data.parameters_names as parameters

millimeters = " [mm]"
meters = " [m]"
microradians = " [μrad]"
energy = " [TeV]"
no_unit = " "
centimeters = " [cm]"
nanometers = " [nm]"
micrometers = " [μm]"
nanoradians = " [nrad]"
unit_map = {
    parameters.ParametersNames.X:               millimeters,
    parameters.ParametersNames.THETA_X:         microradians,
    parameters.ParametersNames.Y:               millimeters,
    parameters.ParametersNames.THETA_Y:         microradians,
    parameters.ParametersNames.PT:              no_unit,
    parameters.ParametersNames.S:               meters,
    parameters.ParametersNames.E:               energy,
    parameters.ParametersNames.D_X:             centimeters,
    parameters.ParametersNames.D_Y:             centimeters,
    parameters.ParametersNames.V_X:             no_unit,
    parameters.ParametersNames.V_Y:             no_unit,
    parameters.ParametersNames.L_X:             meters,
    parameters.ParametersNames.L_Y:             meters,
    parameters.ParametersNames.DELTA_X:         micrometers,
    parameters.ParametersNames.DELTA_THETA_X:   nanoradians,
    parameters.ParametersNames.DELTA_Y:         micrometers,
    parameters.ParametersNames.DELTA_THETA_Y:   nanoradians,
    parameters.ParametersNames.DELTA_PT:        no_unit,
    parameters.ParametersNames.CROSSING_ANGLE:  microradians
}
multiplier_for_unit = {
    parameters.ParametersNames.X:               1000,
    parameters.ParametersNames.THETA_X:         1e6,
    parameters.ParametersNames.Y:               1000,
    parameters.ParametersNames.THETA_Y:         1e6,
    parameters.ParametersNames.PT:              1,
    parameters.ParametersNames.D_X:             100,
    parameters.ParametersNames.D_Y:             100,
    parameters.ParametersNames.S:               1,
    parameters.ParametersNames.V_X:             1,
    parameters.ParametersNames.V_Y:             1,
    parameters.ParametersNames.L_X:             1,
    parameters.ParametersNames.L_Y:             1,
    parameters.ParametersNames.DELTA_X:         1e6,
    parameters.ParametersNames.DELTA_THETA_X:   1e9,
    parameters.ParametersNames.DELTA_Y:         1e6,
    parameters.ParametersNames.DELTA_THETA_Y:   1e9,
    parameters.ParametersNames.DELTA_PT:        1,
    parameters.ParametersNames.CROSSING_ANGLE:  1e6
}
alternative_version = {
    parameters.ParametersNames.X:               r"x",
    parameters.ParametersNames.THETA_X:         r"$\theta_x$",
    parameters.ParametersNames.Y:               r"y",
    parameters.ParametersNames.THETA_Y:         r"$\theta_y$",
    parameters.ParametersNames.PT:              r"$\xi$",
    parameters.ParametersNames.D_X:             r"$D_x$",
    parameters.ParametersNames.D_Y:             r"$D_y$",
    parameters.ParametersNames.L_X:             r"$L_x$",
    parameters.ParametersNames.L_Y:             r"$L_y$",
    parameters.ParametersNames.V_X:             r"$V_x$",
    parameters.ParametersNames.V_Y:             r"$V_y$",
    parameters.ParametersNames.S:               r"s",
    parameters.ParametersNames.DELTA_X:         r"$\Delta x$",
    parameters.ParametersNames.DELTA_THETA_X:   r"$\Delta \theta_x$",
    parameters.ParametersNames.DELTA_Y:         r"$\Delta y$",
    parameters.ParametersNames.DELTA_THETA_Y:   r"$\Delta \theta_y$",
    parameters.ParametersNames.DELTA_PT:        r"$\Delta \xi$",
    parameters.ParametersNames.CROSSING_ANGLE:  r"XA"
}
