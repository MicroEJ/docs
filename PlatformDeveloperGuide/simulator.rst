Principle
=========

The MicroEJ Platform provides an accurate MicroEJ Simulator that runs on
workstations. Applications execute in an almost identical manner on both
the workstation and on target devices. The MicroEJ Simulator features IO
simulation, JDWP debug coupled with Eclipse, accurate Java heap dump,
and an accurate Java scheduling policy (the same as the embedded one). [1]_


Functional Description
======================

In order to simulate external stimuli that come from the native world
(that is, "the C world"), the MicroEJ Simulator has a Hardware In the
Loop interface, HIL, which performs the simulation of Java-to-C calls.
All Java-to-C calls are rerouted to an HIL engine. Indeed HIL is a
replacement for the :ref:`[SNI] <esr-specifications>` interface.

.. figure:: images/hil1.*
   :alt: The HIL Connects the MicroEJ Simulator to the Workstation.
   :width: 80.0%
   :align: center

   The HIL Connects the MicroEJ Simulator to the Workstation.

The "simulated C world" is made of Mocks that simulate native code (such
as drivers and any other kind of C libraries), so that the MicroEJ
Application can behave the same as the device using the MicroEJ
Platform.

The MicroEJ Simulator and the HIL are two processes that run in
parallel:  the communication between them is through a socket
connection. Mocks run inside the process that runs the HIL engine.

.. figure:: images/hil2.*
   :alt: A MicroEJ Simulator connected to its HIL Engine via a socket.
   :width: 80.0%
   :align: center

   A MicroEJ Simulator connected to its HIL Engine via a socket.


.. [1]
   Only the execution speed is not accurate. The Simulator speed can be
   set to match the average MicroEJ Platform speed in order to adapt the
   Simulator speed to the desktop speed.

Dependencies
============

No dependency.


Installation
============

The Simulator is a built-in feature of MicroEJ Platform architecture.


Use
===

To run an application in the Simulator, create a MicroEJ launch
configuration by right-clicking on the main class of the application,
and selecting :guilabel:`Run As` > :guilabel:`MicroEJ Application`.

This will create a launch configuration configured for the Simulator,
and will run it.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
