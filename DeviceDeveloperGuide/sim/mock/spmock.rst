Shielded Plug Mock
==================

General Architecture
--------------------

The Shielded Plug Mock simulates a Shielded Plug [SP] on desktop
computer. This mock can be accessed from the SIMJPF, the hardware
platform or a Java J2SE application.

.. figure:: sim/mock/images/hil5.svg
   :alt: Shielded Plug Mock General Architecture
   :width: 80.0%

   Shielded Plug Mock General Architecture

Configuration
-------------

The mock socket port can be customized for J2SE clients, even though
several Shielded Plug mocks with the same socket port cannot run at the
same time. The default socket port is 10082.

The Shielded Plug mock is a standard MicroEJ application. It can be
configured using Java properties:

-  ``sp.connection.address``

-  ``sp.connection.port``
