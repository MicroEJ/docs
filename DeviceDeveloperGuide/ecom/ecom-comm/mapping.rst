.. _section_ecomcomm_mapping:

Application port mapping
========================

The mapping from application port numbers to platform ports is done in
the application launch configuration. This way, the application can
refer only to the application port number, and the data stream can be
directed to the matching I/O port on different versions of the hardware.

Ultimately, the application port number is only visible to the
application. The platform identifier will be sent to the driver.
