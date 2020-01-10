Installation
============

Network is an additional module. In the platform configuration file,
check ``GROUP.NET`` to install this module. When checked, the properties
file ``net > net.properties`` is required during platform creation to
configure the module. This configuration step is used to customize the
kind of TCP/IP native stack used and the Domain Name System (DNS)
implementation.

The properties file must / can contain the following properties:

-  ``stack`` [optional, default value is "custom"]: Defines the kind of
   TCP/IP interface used in the C project.

   -  ``custom``: Select this configuration to make a "from scratch"
      implementation glue between the C Network Core Engine and the C
      project TCP/IP interface.

   -  ``bsd``: Select this configuration to use a BSD-like library
      helper to implement the glue between the C Network Core Engine and
      the C project TCP/IP interface. This property requires that the C
      project provides a TCP/IP native stack with a Berkeley Sockets API
      and a ``select`` mechanism.

-  ``dns`` [optional, default value is "native"]: Defines the kind of
   Domain Name System implementation used.

   -  ``native``: Select this configuration to implement the glue
      between the C Network Core Engine DNS part and the C project
      TCP/IP interface.

   -  ``soft``: Select this configuration if you want a software
      implementation of the DNS part. Only the IPs list of the DNS
      server must be provided by the C Network Core Engine glue.
