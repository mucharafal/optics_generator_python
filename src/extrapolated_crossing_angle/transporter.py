import transporters.ptc_track.transporter as ptg
from data.particles import Particles


def transport(particles, wanted_xa, configuration_madx_xa1, xa1,
              configuration_madx_xa2, xa2):
    segments_xa_1 = ptg.transport(configuration_madx_xa1, particles)
    segments_xa_2 = ptg.transport(configuration_madx_xa2, particles)

    new_places = {}
    for place in segments_xa_1.keys():
        # (X1 - X2) / (XA1 - XA2) * XA + X2
        # todo refactor, it break isolation of Particles object
        particles_xa_1 = segments_xa_1[place].get_matrix()
        particles_xa_2 = segments_xa_2[place].get_matrix()
        ax = (particles_xa_1 - particles_xa_2) / (xa1 - xa2) * (wanted_xa - xa2)
        b = particles_xa_2
        particles_with_xa = ax + b
        new_places[place] = Particles(particles_with_xa, segments_xa_1[place].get_mapping())

    return new_places


def get_transporter(wanted_xa, configuration_first_optic, xa_first_optics, configuration_second_optics,
                    xa_second_optics):
    def transporter(particles):
        return transport(particles, wanted_xa, configuration_first_optic, xa_first_optics, configuration_second_optics,
                         xa_second_optics)
    return transporter
