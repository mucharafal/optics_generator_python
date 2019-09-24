class TwissConfiguration:
    def __init__(self, path_to_madx_script, s=-1):
        """
        Constructor of TwissConfiguration object.
        :param path_to_madx_script: path to script. In script values of x, px, y, py, pt in ptc_twiss command has to be
        set on values: ptc_twiss, ..., X=x, PX=px, Y=y, PY=py, PT=pt...
        :param s: if different from -1, values at end station are filtered for this value of s. If is set on -1 segment
        end contains all records from input file
        """
        self.path_to_madx_script = path_to_madx_script
        self.s = s
