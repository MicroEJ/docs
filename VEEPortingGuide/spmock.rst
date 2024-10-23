Shielded Plug Mock
==================

General Architecture
--------------------

The Shielded Plug Mock simulates a Shielded Plug :ref:`[SP] <sp>` on desktop
computer. This mock can be accessed from the MicroEJ Simulator, the
hardware platform or a Java SE application.

.. figure:: images/hil5.*
   :alt: Shielded Plug Mock General Architecture
   :align: center
   :scale: 75%

   Shielded Plug Mock General Architecture

Configuration
-------------

The mock socket port can be customized for Java SE clients, even though
several Shielded Plug mocks with the same socket port cannot run at the
same time. The default socket port is 10082.

The Shielded Plug mock is a standard MicroEJ Application. It can be
configured using Java properties:

-  ``sp.connection.address``

-  ``sp.connection.port``

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
