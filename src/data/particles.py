class Particles:
    def __init__(self, particles, mapping):
        self.particles = particles
        self.mapping = mapping

    def get_values_of(self, parameter_name):
        index = self.mapping[parameter_name]
        return self.particles.T[index]

    def get_number_of_particles(self):
        return self.particles.shape()[0]


def transform_to_geometrical_coordinates(particles):
    new_particles = np.copy(particles)
    new_particles.T[1] /= 1 + new_particles.T[4]
    new_particles.T[3] /= 1 + new_particles.T[4]
    return new_particles