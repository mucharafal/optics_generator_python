from data.parameters_names import ParametersNames as Parameters
"""
Mapping of columns for such specified columns:
column=s,x,y,px,py,betx,bety,mu1,mu2,re12,re34,disp1,disp3;
If above line in madx script is changed, adjust below map.
Last column (pt) is appended after read in from file and is always last column.
"""
ptc_twiss = {
    "s": 0,
    Parameters.X: 1,
    Parameters.Y: 2,
    Parameters.THETA_X: 3,
    Parameters.THETA_Y: 4,
    "L x": 9,
    "L y": 10,
    "D x": 11,
    "D y": 12,
    Parameters.PT: 14,
    "V x": 7,
    "V y": 8,
    "crossing angle": 13
}