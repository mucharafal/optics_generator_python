class MadxConfiguration:
    def __init__(self, end_place_name,
                 end_place_distance,
                 start_place_name,
                 beam_name,
                 madx_input_script_file_name):
        self.end_place_name = end_place_name
        self.end_place_distance = end_place_distance
        self.start_place_name = start_place_name
        self.beam_name = beam_name
        self.madx_input_script_file_name = madx_input_script_file_name
