.. _section_input:

======
Inputs
======


Principle
=========

The Inputs module contains the C part of the MicroUI implementation
which manages input devices. This module is composed of two elements:

-  the C part of MicroUI input API (a built-in C archive)

-  an implementation of a low level API for the input devices (LLINPUT)
   that must be provided by the BSP (see :ref:`LLINPUT-API-SECTION`)


Functional Description
======================

The Inputs module implements the MicroUI ``int``-based event generators'
framework. ``LLINPUT`` specifies the low level API that send events to
the Java world.

Each MicroUI ``Event Generator`` represents one side of a pair of
collaborative components that communicate using a shared buffer:

-  The producer: the C driver connected to the hardware. As a producer,
   it sends its data into the communication buffer.

-  The consumer: the MicroUI ``Event Generator``. As a consumer, it
   reads (and removes) the data from the communication buffer.

.. figure:: images/drivers-microui-comms.*
   :alt: Drivers and MicroUI Event Generators Communication
   :width: 550px
   :align: center

   Drivers and MicroUI Event Generators Communication

The ``LLINPUT`` API allows multiple pairs of
``<driver - event generator>`` to use the same buffer, and associates
drivers and event generators using an int ID. The ID used is the event
generator ID held within the MicroUI global registry :ref:`[MUI] <esr-specifications>`. Apart from
sharing the ID used to "connect" one driver's data to its respective
event generator, both entities are completely decoupled.

A Java green thread, called the ``InputPump`` thread, waits for data to
be published by drivers into the "input buffer," and dispatches to the
correct (according to the ID) event generator to read the received data.
This "driver-specific-data" is then transformed into MicroUI events by
event generators and sent to objects that listen for input activity.

.. figure:: images/microui-events.png
   :alt: MicroUI Events Framework
   :align: center
   :scale: 75%

   MicroUI Events Framework


.. _section_inputs_implementation:

Implementation
==============

The implementation of the MicroUI ``Event Generator`` APIs provides some
low level APIs. The BSP has to implement these LLAPI, making the link
between the MicroUI C library ``inputs`` and the BSP input devices
drivers.

The LLAPI to implement are listed in the header file ``LLINPUT_impl.h``.
It allows events to be sent to the MicroUI implementation. The input
drivers are allowed to add events directly using the event generator's
unique ID (see :ref:`section_static_init`). The drivers are fully
dependent on the MicroEJ framework (a driver cannot be developed without
MicroEJ because it uses the header file generated during the MicroUI
initialization step).

When there is no input device on the board, a *stub* implementation of C
library is available. This C library must be linked by the third-party C
IDE when the MicroUI module is installed in the MicroEJ Platform.


.. _javaEventGenerators:

Generic Event Generators
========================

On the application side, the UI extension provides an abstract class
``GenericEventGenerator`` (package ``ej.microui.event``) that must be
implemented by clients who want to define their own event generators.
Two abstract methods must be implemented by subclasses:

-  ``eventReceived``: The event generator received an event from a C
   driver through the low level API ``sendEvent`` function.

-  ``eventsReceived``: The event generator received an event made of
   several ``int``\ s.

-  ``setProperty``: Handle a generic property (key/value pair) set from
   the static initialization file (see :ref:`muiStaticInit`)

The event generator is responsible for converting incoming data into a
MicroUI event and sending the event to its listener.


Dependencies
============

-  MicroUI module (see :ref:`section_microui`)

-  Static MicroUI initialization step (see
   `section_static_init`). This step generates a header file
   which contains some unique event generator IDs. These IDs must be
   used in the BSP to make the link between the input devices drivers
   and the MicroUI ``Event Generator``\ s.

-  ``LLINPUT_impl.h`` implementation (see
   :ref:`LLINPUT-API-SECTION`).


.. _section_inputs_installation:

Installation
============

Inputs is a sub-part of the MicroUI library. When the MicroUI module is
installed, the Inputs module must be installed in order to be able to
connect physical input devices with MicroEJ Platform. If not installed,
the *stub* module will be used. In the platform configuration file,
check :guilabel:`UI` > :guilabel:`Inputs` to install Inputs.


Use
===

The MicroUI Input APIs are available in the class
``ej.microui.EventGenerator``.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
