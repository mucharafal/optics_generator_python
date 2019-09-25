class Particles:
    def __init__(self, particles, mapping):
        self.particles = particles
        self.mapping = mapping

    def get_values_of(self, parameter_name):
        index = self.mapping[parameter_name]
        return self.particles.T[index]

    def get_number_of_particles(self):
        return self.particles.shape()[0]
