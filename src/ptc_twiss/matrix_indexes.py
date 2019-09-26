from data.parameters_names import ParametersNames as Parameters
"""
Mapping of columns for such specified columns:
column=s,x,y,px,py,betx,bety,mu1,mu2,re12,re34,disp1,disp3;
If above line in madx script is changed, adjust below map.
Last column (pt) is appended after read in from file and is always last column.
"""
ptc_twiss = {
    Parameters.S: 0,
    Parameters.X: 1,
    Parameters.Y: 2,
    Parameters.THETA_X: 3,
    Parameters.THETA_Y: 4,
    Parameters.L_X: 9,
    Parameters.L_Y: 10,
    Parameters.D_X: 11,
    Parameters.D_Y: 12,
    Parameters.PT: 13,
    Parameters.V_X: 7,
    Parameters.V_Y: 8,
}