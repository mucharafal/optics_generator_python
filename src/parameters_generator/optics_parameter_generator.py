import madx_runner as mr
import particles_generator as pg
import os
import shutil
"""
Module include functions to obtain parameters of optics such like dispersion or magnetism.
They are calculated using madx to obtain particle trajectory and then they are obtained using numerical derivative.
None of them is thread safe.
"""


def compute_l_y(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_theta=0.000001):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x, theta_x, y, theta_y + delta_theta, ksi, path_to_configuration)
    return (particle2["y"] - particle1["y"]) / delta_theta


def compute_l_x(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_theta=0.000001):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x, theta_x + delta_theta, y, theta_y, ksi, path_to_configuration)
    return (particle2["x"] - particle1["x"]) / delta_theta


def compute_v_x(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_x):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x + delta_x, theta_x, y, theta_y, ksi, path_to_configuration)
    return (particle2["x"] - particle1["x"]) / delta_x


def compute_v_y(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_y):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x, theta_x, y + delta_y, theta_y, ksi, path_to_configuration)
    return (particle2["y"] - particle1["y"]) / delta_y


def compute_d_x(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_ksi):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x, theta_x, y, theta_y, ksi + delta_ksi, path_to_configuration)
    return (particle2["x"] - particle1["x"]) / delta_ksi


def compute_d_y(x, theta_x, y, theta_y, ksi, path_to_configuration, delta_ksi):
    particle1 = get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration)
    particle2 = get_one_particle(x, theta_x, y, theta_y, ksi + delta_ksi, path_to_configuration)
    return (particle2["y"] - particle1["y"]) / delta_ksi


def get_one_particle(x, theta_x, y, theta_y, ksi, path_to_configuration):
    """
    Transport particle with given parameter.
    Generate input file for madx, invoke it and read in its input.
    Raise error ParticleNotArrivedError if particle do not arrive at the end station.
    :param x:
    :param theta_x:
    :param y:
    :param theta_y:
    :param ksi:
    :param path_to_configuration: path to configuration of accelerator. Needed files:
    /2016/lhc_as-built.seq
    /2016/opt_inj_colltunes.madx
    temporary_perturbation.madx
    temporary_perturbation_b1.madx
    LSA.str
    :return: map with parameters of particle
    """
    bunch_size = 1
    current_path = os.getcwd()
    folder_name = "kali1234"
    os.mkdir(folder_name)
    os.chdir(folder_name)

    name_of_configuration_file = create_madx_configuration_file(path_to_configuration, ksi, bunch_size)

    pg.generate_from_range(x, x, bunch_size,
                           theta_x, theta_x, 1,
                           y, y, 1,
                           theta_y, theta_y, 1,
                           0, 0, 1,
                           0, 0, 1)

    mr.run_madx(name_of_configuration_file)
    segments = mr.read_in_madx_output_file("trackone")

    if "end" in segments.keys():
        matrix = segments["end"]
    else:
        os.chdir(current_path)
        shutil.rmtree(folder_name)
        raise ParticleNotArrivedError()

    os.chdir(current_path)
    shutil.rmtree(folder_name)

    return process_row(matrix[0])


def process_row(row):
    mapping = {
        "number": row[0],
        "turn": row[1],
        "x": row[2],
        "theta_x": row[3],
        "y": row[4],
        "theta_y": row[5],
        "t": row[6],
        "pt": row[7],
        "s": row[8],
        "e": row[9]
    }
    return mapping


class ParticleNotArrivedError(Exception):
    pass


def create_madx_configuration_file(path_to_configuration,
                                   ksi,
                                   number_of_particles_on_input):
    file_name = "configuration.madx"
    with open(file_name, "w") as configuration_file:
        configuration_file.write('''option, -echo, -info,  -warn;

! defines a macro to read initial coordinates
getpart(nx): macro = {
 ex   = table(myevent,nx,trx);
 epx   = table(myevent,nx,trpx);
 ey   = table(myevent,nx,try);
 epy   = table(myevent,nx,trpy);
 et    = table(myevent,nx,trt);
 ept    = table(myevent,nx,trpt);
 value,ex,epx,ey,epy,et,ept;
}


set,format="4.12e";''')
        configuration_file.write('call, file = "' + path_to_configuration + '/2016/lhc_as-built.seq";')
        configuration_file.write('call, file = "' + path_to_configuration + '/2016/opt_inj_colltunes.madx";')
        configuration_file.write("DELTA_AP = " + str(ksi) + ";")
        configuration_file.write("bunch_size = " + str(number_of_particles_on_input) + ";")
        configuration_file.write('''on_sep5=0;
px.ip5=185e-6;
!y.ip5=5.500000000000000e-04;
beta.ip5=0.400 ;

! Beam definition
beam, sequence=lhcb1, bv= 1, energy=6500,  particle=proton,
  npart=1.2e11,kbunch=2748, ex=7.29767146889e-09,ey=7.29767146889e-09;
beam, sequence=lhcb2, bv=-1, energy=6500,  particle=proton,
  npart=1.2e11,kbunch=2748, ex=7.29767146889e-09,ey=7.29767146889e-09;

use,sequence=lhcb1;
''')
        configuration_file.write('call, file="' + path_to_configuration + 'temporary_perturbation.madx";')
        configuration_file.write('call, file="' + path_to_configuration + 'temporary_perturbation_b1.madx";')

        configuration_file.write('''

! Matching part start

MQXA.1R5, K1 := ((LSA.MQXA.1R5)*(PERTSTRMQXA.1R5 + DMQXA.1R5)) * (1), polarity=1;

select, flag=error, clear;
select,flag=error, pattern=MQXA.1R5;
ealign, dpsi= PERTDPSIMQXA.1R5 + DPSIMQXA.1R5   ;
MCBXH.1R5, KICK := (LSA.MCBXH.1R5*(1.0 + DELTA_K_MCBXH.1R5)) * (1), polarity=1;
MCBXV.1R5, KICK := (LSA.MCBXV.1R5*(1.0 + 0)) * (1), polarity=1;
MQXB.A2R5, K1 := ((LSA.MQXB.A2R5)*(PERTSTRMQXB.A2R5 + DMQXB.A2R5)) * (1), polarity=-1;

select, flag=error, clear;
select,flag=error, pattern=MQXB.A2R5;
ealign, dpsi= PERTDPSIMQXB.A2R5 + DPSIMQXB.A2R5   ;
MCBXH.2R5, KICK := (LSA.MCBXH.2R5*(1.0 + DELTA_K_MCBXH.2R5)) * (1), polarity=1;
MCBXV.2R5, KICK := (LSA.MCBXV.2R5*(1.0 + 0)) * (1), polarity=1;
MQXB.B2R5, K1 := ((LSA.MQXB.B2R5)*(PERTSTRMQXB.B2R5 + DMQXB.B2R5)) * (1), polarity=-1;

select, flag=error, clear;
select,flag=error, pattern=MQXB.B2R5;
ealign, dpsi= PERTDPSIMQXB.B2R5 + DPSIMQXB.B2R5   ;
MQSX.3R5, K1S := (LSA.MQSX.3R5*(1.0 + 0)) * (1), polarity=1;
MQXA.3R5, K1 := ((LSA.MQXA.3R5)*(PERTSTRMQXA.3R5 + DMQXA.3R5)) * (1), polarity=1;

select, flag=error, clear;
select,flag=error, pattern=MQXA.3R5;
ealign, dpsi= PERTDPSIMQXA.3R5 + DPSIMQXA.3R5   ;
MCBXH.3R5, KICK := (LSA.MCBXH.3R5*(1.0 + DELTA_K_MCBXH.3R5)) * (1), polarity=1;
MCBXV.3R5, KICK := (LSA.MCBXV.3R5*(1.0 + 0)) * (1), polarity=1;
MCSX.3R5, KNL := {0, 0, (LSA.MCSX.3R5*(1.0 + 0)) * (1)*l.MCSX, 0, 0, 0}, polarity=1;
MCTX.3R5, KNL := {0, 0, 0, 0, 0, (LSA.MCTX.3R5*(1.0 + 0)) * (1)*l.MCTX}, polarity=1;
MCOSX.3R5, KSL := {0, 0, 0, (LSA.MCOSX.3R5*(1.0 + 0)) * (1)*l.MCOSX}, polarity=1;
MCOX.3R5, KNL := {0, 0, 0, (LSA.MCOX.3R5*(1.0 + 0)) * (1)*l.MCOX}, polarity=1;
MCSSX.3R5, KSL := {0, 0, (LSA.MCSSX.3R5*(1.0 + 0)) * (1)*l.MCSSX, 0}, polarity=1;
MBXW.A4R5, K0 := (((LSA.MBXW.A4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.A4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBXW.B4R5, K0 := (((LSA.MBXW.B4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.B4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBXW.C4R5, K0 := (((LSA.MBXW.C4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.C4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBXW.D4R5, K0 := (((LSA.MBXW.D4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.D4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBXW.E4R5, K0 := (((LSA.MBXW.E4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.E4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBXW.F4R5, K0 := (((LSA.MBXW.F4R5)*(1.0 + 0)) * (-1)) , ANGLE := ( ((LSA.MBXW.F4R5)*(1.0 + 0)) * (-1) * l.MBXW ), polarity=-1;
MBRC.4R5.B1, K0 := (((LSA.MBRC.4R5.B1)*(1.0 + 0)) * (1)) , ANGLE := ( ((LSA.MBRC.4R5.B1)*(1.0 + 0)) * (1) * l.MBRC ), polarity=1;
MCBYV.A4R5.B1, KICK := (LSA.MCBYV.A4R5.B1*(1.0 + 0)) * (1), polarity=1;
MCBYH.4R5.B1, KICK := (LSA.MCBYH.4R5.B1*(1.0 + 0)) * (1), polarity=1;
MCBYV.B4R5.B1, KICK := (LSA.MCBYV.B4R5.B1*(1.0 + 0)) * (1), polarity=1;
MQY.4R5.B1, K1 := ((LSA.MQY.4R5.B1)*(PERTSTRMQY.4R5.B1 + DMQY.4R5.B1)) * (1), polarity=-1;

select, flag=error, clear;
select,flag=error, pattern=MQY.4R5.B1;
ealign, dpsi= PERTDPSIMQY.4R5.B1 + DPSIMQY.4R5.B1   ;
MQML.5R5.B1, K1 := ((LSA.MQML.5R5.B1)*(PERTSTRMQML.5R5.B1 + DMQML.5R5.B1)) * (1), polarity=1;

select, flag=error, clear;
select,flag=error, pattern=MQML.5R5.B1;
ealign, dpsi= PERTDPSIMQML.5R5.B1 + DPSIMQML.5R5.B1   ;
MCBCH.5R5.B1, KICK := (LSA.MCBCH.5R5.B1*(1.0 + 0)) * (1), polarity=1;

! Matching part end''')
        configuration_file.write('call, file="' + path_to_configuration + 'LSA.str";')
        configuration_file.write('''! Cycle
seqedit,sequence=lhcb1;flatten;cycle,start=IP5;endedit;

PI=3.141592654;
NORM_TRANS_EMITTANCE_M_RAD=3.5e-6;
PROTON_GAMMA=(6500/9.382720460000000e-01);


beg_150_station : marker;
seqedit,sequence=lhcb1;
install,element=beg_150_station,at=202.769,from=ip5;
endedit;



seqedit, sequence=lhcb1;flatten;cycle, start=IP5;endedit;

use,sequence=lhcb1;
!use,period=lhcb1,range=ip5/MQML.6R5.B1;
use,period=lhcb1,range=ip5/beg_150_station;''')
        # Probably above line is redundant
        configuration_file.write('call, file="' + path_to_configuration + 'temporary_perturbation_b1.madx";')

        configuration_file.write('''readmytable,file=part.in,table=myevent;


ptc_create_universe;
ptc_create_layout,model=2,method=6,nst=10,exact;
ptc_align;

! read in initial coordinates at set for tracking
   n=1;
   while ( n < bunch_size + 1 ) {
      exec,getpart($n);
      ptc_start,x=ex,px=epx,y=ey,py=epy,t=et,pt=ept;
      n = n + 1;
   } !ok

!ptc_start,x=x.ip5,px=DELTA_PX_B1,y=y.ip5,py=py.ip5;

ptc_observe,place=beg_150_station;
ptc_observe,place=mqxb.b2r5;
ptc_observe,place=mcbxh.3r5;
ptc_observe,place=tanc.4r5;
ptc_observe,place=mcbxh.2r5;
ptc_observe,place=mqxa.3r5;
ptc_observe,place=mqml.5r5.b1;
ptc_observe,place=mcbch.5r5.b1;
ptc_observe,place=mcbyv.b4r5.b1;
ptc_observe,place=tcl.4r5.b2;
ptc_observe,place=tcl.5r5.b2;
 !ok

ptc_track,icase=5,element_by_element,dump,onetable,deltap=(DELTA_AP + DELTADELTAP + DDELTADELTAP_B1 + TOTEMDELTAP),file="track";

ptc_track_end;
ptc_end;

return;
stop;''')
        return file_name




