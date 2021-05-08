TEMPLATE = subdirs

SUBDIRS = application \
          protocol \
          server_fake \
          server_sense_hat \
          server_sensor_hub \

application.depends = protocol
server_fake.depends = protocol
server_sense_hat.depends = protocol
server_sensor_hub.depends = protocol
