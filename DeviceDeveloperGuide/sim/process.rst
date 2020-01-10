Functional Description
======================

In order to simulate external stimuli that come from the native world
(that is, "the C world"), the SIMJPF has a Hardware In the Loop
interface, HIL, which performs the simulation of Java-to-C calls. All
Java-to-C calls are rerouted to an HIL engine. Indeed HIL is a
replacement for the [SNI] interface.

.. figure:: sim/images/hil1.svg
   :alt: The HIL Connects the SIMJPF to the Workstation.
   :width: 80.0%

   The HIL Connects the SIMJPF to the Workstation.

The "simulated C world" is made of mocks that simulate native code (such
as drivers and any other kind of C libraries), so that the MicroEJ
application can behave the same as the device using the EMBJPF.

The SIMJPF and the HIL are two processes that run in parallel:  the
communication between them is through a socket connection. Mocks run
inside the process that runs the HIL engine.

.. figure:: sim/images/hil2.svg
   :alt: A SIMJPF connected to its HIL Engine via a socket.
   :width: 80.0%

   A SIMJPF connected to its HIL Engine via a socket.
