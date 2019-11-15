def generate_madx_script(transport_configuration, number_of_particles):
    script = __get_madx_script(transport_configuration, number_of_particles)
    with open(transport_configuration.madx_script_file_name, "w") as file_object:
        file_object.write(script)
        return transport_configuration.madx_script_file_name


def __get_madx_script(transport_configuration, number_of_particles):
    script = "" + \
        __get_header() + \
        __get_call_lhc_definition(transport_configuration) + \
        __get_end_place_definition(transport_configuration) + \
        __get_use_command(transport_configuration) + \
        __get_call_errors_file(transport_configuration) + \
        __get_ptc_track_definition(transport_configuration, number_of_particles)
    return script


def __get_header():
    return "option, -echo, -info,  warn;\n"


def __get_call_lhc_definition(transport_configuration):
    return __get_call_file(transport_configuration.accelerator_definition_file_name)


def __get_call_file(path_to_file):
    call = "call, file = \"" + path_to_file + "\";\n"
    return call


def __get_end_place_definition(transport_configuration):
    end_place = transport_configuration.get_end_place_configuration()

    command = end_place.name + " : marker;\n"
    command += "seqedit,sequence=" + end_place.beam + ";\n"
    command += "install,element=" + end_place.name + ",at=" + str(end_place.distance) + ",from= " \
               + end_place.name_of_place_from + ";\n"
    command += "endedit;\n"
    return command


def __get_use_command(transport_configuration):
    end_place = transport_configuration.get_end_place_configuration()

    command = "use, sequence = " + end_place.beam + ", range = " \
              + end_place.name_of_place_from + "/" + end_place.name + ";\n"

    return command


def __get_call_errors_file(transport_configuration):
    return __get_call_file(transport_configuration.errors_definition_file_name)


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
                     "deltap=(DELTADELTAP+ DDELTADELTAP_B1+ TOTEMDELTAP),file=\"" + \
                     madx_output_file_name + "\",maxaper={100, 100, 100, 100, 1.0, 1.0}; \n" \
                                             "ptc_track_end; \n" \
                                             "ptc_end;\n" \
                                             "return;\n" \
                                             "stop;\n"
    return track_and_rest


