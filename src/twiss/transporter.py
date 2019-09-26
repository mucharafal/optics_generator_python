import twiss.runner as runner


def get_transporter(madx_configuration):
    def transporter(particles):
        return runner.transport(madx_configuration, particles)
    return transporter
