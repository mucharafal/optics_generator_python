millimeters = " [mm]"
meters = " [m]"
radians = " [μrad]"
seconds = " [s]"
energy = " [TeV]"
no_unit = " "
centimeters = " [cm]"
unit_map = {
    "x": millimeters,
    "theta x": radians,
    "y": millimeters,
    "theta y": radians,
    "t": seconds,
    "pt": no_unit,
    "s": meters,
    "e": energy,
    "D x": centimeters,
    "D y": centimeters,
    "V x": no_unit,
    "V y": no_unit,
    "L x": meters,
    "L y": meters
}
multiplier_for_unit = {
    "x": 1000,
    "theta x": 1e6,
    "y": 1000,
    "theta y": 1e6,
    "t": 1,
    "pt": 1,
    "D x": 100,
    "D y": 100,
    "s": 1,
    "V x": 1,
    "V y": 1,
    "L x": 1,
    "L y": 1
}
alternative_version = {
    "x": r"x",
    "theta x": r"$\theta_x$",
    "y": r"y",
    "theta y": r"$\theta_y$",
    "pt": r"$\xi$",
    "D x": r"$D_x$",
    "D y": r"$D_y$",
    "L x": r"$L_x$",
    "L y": r"$L_y$",
    "V x": r"$V_x$",
    "V y": r"$V_y$",
    "s": r"s"
}
