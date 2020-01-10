.. _section_ecomcomm_xml:

XML File
========

The Java platform has to know the maximum number of Comm ports that can
be managed by the ECOM Comm stack. It also has to know each Comm port
that can be mapped from an application port number. Such Comm port is
identified by its platform port number and by an optional nickname (The
port and its nickname will be visible in the MicroEJ launcher options,
see `??? <#workbenchLaunchOptions>`__ ).

A XML file is so required to configure the Java platform. The name of
this file must be ``ecom-comm.xml``. It has to be stored in the module
configuration folder (see `??? <#section_ecomcomm_installation>`__).

This file must start with the node ``<ecom>`` and the sub node
``<comms>``. It can contain several time this kind of line:
``<comm platformId="A_COMM_PORT_NUMBER" nickname="A_NICKNAME"/>`` where:

-  ``A_COMM_PORT_NUMBER`` refers the Comm port the Java platform user
   will be able to use (see `??? <#section_ecomcomm_mapping>`__).

-  ``A_NICKNAME`` is optional. It allows to fix a printable name of the
   Comm port.

The ``maxConnections`` attribute indicates the maximum number of
connections allowed, including static and dynamic connections. This
attribute is optional. By default, it is the number of declared Comm
Ports.

Example: <ecom> <comms maxConnections="20"> <comm platformId="2"/> <comm
platformId="3" nickname="DB9"/> <comm platformId="5"/> </comms> </ecom>
First Comm port holds the port 2, second "3" and last "5". Only the
second Comm port holds a nickname "DB9".
