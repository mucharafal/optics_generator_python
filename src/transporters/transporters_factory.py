def get_transporter(configuration):
    transporter_module = configuration.get_module_transporter()
    transporter_configuration = configuration.get_configuration()
    return transporter_module.get_transporter(transporter_configuration)