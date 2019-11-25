import transporters.madx.parser as madx_script_parser


def generate_madx_script(transport_configuration, number_of_particles):
    script = __get_madx_script(transport_configuration, number_of_particles)
    with open(transport_configuration.madx_output_script_file_name, "w") as file_object:
        file_object.write(script)
        return transport_configuration.madx_output_script_file_name


def __get_madx_script(transport_configuration, number_of_particles):
    base_script = madx_script_parser.get_configuration(transport_configuration)
    script = "" + \
        __get_header() + \
        base_script + \
        __get_ptc_track_definition(transport_configuration, number_of_particles)
    return script


def __get_header():
    return "option, -echo, -info,  warn;\n"


def __get_ptc_track_definition(transport_configuration, number_of_particles):
    definition = __create_universe() + \
        __import_particles(number_of_particles) + \
        __scoring_plane_placement(transport_configuration.get_scoring_place_names()) + \
        __track_and_end("track")    # todo it should not be hardcoded
    return definition


def __create_universe():
    universe_definition = "ptc_create_universe; \n" \
                          "ptc_create_layout,model=2,method=6,nst=10,exact;\n" \
                          "ptc_align;\n"
    return universe_definition


def __import_particles(number_of_particles_per_sample):
    macro = __macro_get_particles()
    reader = __read_particles_from_file(number_of_particles_per_sample)
    return macro + reader


def __macro_get_particles():
    macro = """! defines a macro to read initial coordinates
    getpart(nx): macro = {
     ex   = table(myevent,nx,trx);
     epx   = table(myevent,nx,trpx);
     ey   = table(myevent,nx,try);
     epy   = table(myevent,nx,trpy);
     et    = table(myevent,nx,trt);
     ept    = table(myevent,nx,trpt);
     value,ex,epx,ey,epy,et,ept;
    }\n"""
    return macro


def __read_particles_from_file(number_of_particles_per_sample):
    read_particles_part = "readmytable,file=part.in,table=myevent;\n" + \
        "! read in initial coordinates at set for tracking\n" + \
        "   n=1;\n" + \
        "   while ( n < " + str(number_of_particles_per_sample) + " + 1 ) {\n" + \
        "      exec,getpart($n);\n" + \
        "      ptc_start,x=ex,px=epx,y=ey,py=epy,t=et,pt=ept;\n" + \
        "      n = n + 1;\n" + \
        "   }\n"
    return read_particles_part


def __scoring_plane_placement(places):
    result = ""
    for place in places:
        result += "ptc_observe,place=" + place + ";\n"
    return result


def __track_and_end(madx_output_file_name):
    track_and_rest = "ptc_track,icase=5,px=1,element_by_element,dump,onetable," \
                     "deltap=delta_p,file=\"" + \
                     madx_output_file_name + "\",maxaper={100, 100, 100, 100, 1.0, 1.0}; \n" \
                                             "ptc_track_end; \n" \
                                             "ptc_end;\n" \
                                             "return;\n" \
                                             "stop;\n"
    return track_and_rest


