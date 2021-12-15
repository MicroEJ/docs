.. _section_input:

=====
Input
=====


Principle
=========

The Input module contains the C part of the MicroUI implementation which manages input devices. This module is composed of two elements:

-  the C part of MicroUI input API (a built-in C archive) called Input Engine,

-  an implementation of a Low Level APIs for the input devices
   that must be provided by the BSP (see :ref:`LLINPUT-API-SECTION`).

Functional Description
======================

The Input module implements the MicroUI ``int``-based event generators' framework. ``LLUI_INPUT`` specifies the Low Level APIs that send events to the Java world.

Drivers for input devices must generate events that are sent, via a MicroUI `Event Generator <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/EventGenerator.html>`_, to the application. An event generator accepts notifications from devices, and generates an event in a standard format that can be handled by the application. Depending on the MicroUI configuration, there can be several different types of event generator in the system, and one or more instances of each type. 

Each MicroUI `Event Generator <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/EventGenerator.html>`_ represents one side of a pair of collaborative components that communicate using a shared buffer:

-  The producer: the C driver connected to the hardware. As a producer, it sends its data into the communication buffer.

-  The consumer: the MicroUI `Event Generator <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/EventGenerator.html>`_. As a consumer, it reads (and removes) the data from the communication buffer.

.. figure:: images/drivers-microui-comms.*
   :alt: Drivers and MicroUI Event Generators Communication
   :width: 550px
   :align: center

   Drivers and MicroUI Event Generators Communication

The ``LLUI_INPUT`` API allows multiple pairs of ``<driver - event generator>`` to use the same buffer, and associates drivers and event generators using an int ID. The ID used is the event generator ID held within the MicroUI global registry. Apart from sharing the ID used to "connect" one driver's data to its respective event generator, both entities are completely decoupled.

The `MicroUI <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/MicroUI.html>`_ thread waits for data to be published by drivers into the "input buffer", and dispatches to the correct (according to the ID) event generator to read the received data. This "driver-specific-data" is then transformed into MicroUI events by event generators and sent to objects that listen for input activity.

.. figure:: images/microui-events.png
   :alt: MicroUI Events Framework
   :align: center
   :scale: 75%

   MicroUI Events Framework

.. _section_inputs_implementation:

Driver Listener
===============

Drivers may either interface directly with event generators, or they can send their notifications to a *Listener*, also written in C, and the listener passes the notifications to the event generator. This
decoupling has two major benefits:

-  The drivers are isolated from the MicroEJ libraries – they can even
   be existing code.

-  The listener can translate the notification; so, for example, a
   joystick could generate pointer events.

.. _section_inputs_static_init:

Static Initialization
=====================

The event generators available on MicroUI startup (after the call to `MicroUI.start() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/MicroUI.html#start-->`_) are the event generators listed in the MicroUI description file (XML file). This file is a part of the MicroUI Static Initialization step (:ref:`section_static_init`). 

The order of event generators defines the unique identifier for each event generator. These identifiers are generated in a header file called ``microui_constants.h``. The input driver (or its listener) has to use these identifiers to target a specific event generator.

If an unknown identifier is used or if two identifiers are swapped, the associated event may be never received by the application or may be misinterpreted. 

Standard Event Generators
=========================

MicroUI provides a set of standard event generators: `Command <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Command.html>`_, `Buttons <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Buttons.html>`_, `Pointer <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Pointer.html>`_ and `States <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/States.html>`_. For each standard generator, the Input Engine proposes a set of functions to create and send an event to this generator.

Static Initialization proposes an additional event generator: ``Touch``. A touch event generator is a `Pointer <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Pointer.html>`_ event generator whose area size is the display size where the touch panel is placed. Furthermore, contrary to a pointer, a *press* action is required to be able to have a *move* action (and so a *drag* action). The Input Engine proposes a set of functions to target a touch event generator (equal to a pointer event generator but with some constraints). The touch event generator is identified as a standard `Pointer <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Pointer.html>`_ event generator, by consequence the Java application has to use the `Pointer <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Pointer.html>`_ API to deal with a touch event generator.

According to the event generator, one or several parameters are required. The parameter format is event generator dependant. For instance a ``Pointer`` X-coordinate is encoded on 16 bits (0-65535 pixels).

.. _section_inputs_genericEventGenerators:

Generic Event Generators
========================

MicroUI provides an abstract class `GenericEventGenerator <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/GenericEventGenerator.html>`_ (package ``ej.microui.event``). The aim of a generic event generator is to be able to send custom events from native world to the application. These events may be constituted by only one 32-bit word or by several 32-bit words (maximum 255). 

On the application side, a subclass must be implemented by clients who want to define their own event generators.  Two abstract methods must be implemented by subclasses:

-  ``eventReceived``: The event generator received an event from a C driver through the Low Level APIs ``sendEvent`` function.

-  ``eventsReceived``: The event generator received an event made of several ``int``\ s.

The event generator is responsible for converting incoming data into a MicroUI event and sending the event to its listener. It should be defined during MicroUI Static Initialization step (in the XML file, see :ref:`section_static_init`). This allows the MicroUI implementation to instantiate the event generator on startup. 

If the event generator is not available in the application classpath, a warning is thrown (with a stack trace) and the application continues. In this case, all events sent by BSP to this event generator are ignored because no event generator is able to decode them.

.. _section_input_llapi:

Low Level API
=============

The implementation of the MicroUI ``Event Generator`` APIs provides some Low Level APIs. The BSP has to implement these Low Level APIs, making the link between the MicroUI C library ``inputs`` and the BSP input devices
drivers.

The Low Level APIs to implement are listed in the header file ``LLUI_INPUT_impl.h``. It allows events to be sent to the MicroUI implementation. The input drivers are allowed to add events directly using the event generator's
unique ID (see :ref:`section_static_init`). The drivers are fully dependent on the MicroEJ framework (a driver or a driver listener cannot be developed without MicroEJ because it uses the header file generated during the MicroUI initialization step).

To send an event to the application, the driver (or its listener) has to call one of the event engine function, listed in ``LLUI_INPUT.h``. 
These functions take as parameter the MicroUI EventGenerator to target and the data. The event generator is represented by a unique ID. The data depends on the type of the event. To run correctly, the event engine requires an implementation of functions listed in ``LLUI_INPUT_impl.h``. When an event is added, the event engine notifies MicroUI library.

.. figure:: images/ui_llapi_input2.*
   :alt: MicroUI Input Low Level
   :width: 500px
   :align: center

   Input Low Level API

When there is no input device on the board, a *stub* implementation of C library is available. This C library must be linked by the third-party C IDE when the MicroUI module is installed in the MicroEJ Platform. This stub library does not provide any Low Level API files.

.. _section_inputs_eventbuffer:

Event Buffer
============

MicroUI is using a circular buffer to manage the input events. 
As soon as an event is added, removed, or replaced in the queue, the event engine calls the associated Low-Level API (LLAPI) ``LLUI_INPUT_IMPL_log_queue_xxx()``.
This LLAPI allows the BSP to log this event to dump it later thanks to a call to ``LLUI_INPUT_dump()``.

.. note:: When the functions ``LLUI_INPUT_IMPL_log_queue_xxx()`` are not implemented, a call to ``LLUI_INPUT_dump()`` has no effect (there is no default logger).

The following steps describe how the logger is called:

1. On startup, MicroUI calls ``LLUI_INPUT_IMPL_log_queue_init()``: it gives the event buffer. The implementation should prepare its logger.
2. The BSP adds or replaces an event in the queue, the event engine calls ``LLUI_INPUT_IMPL_log_queue_add()`` or ``LLUI_INPUT_IMPL_log_queue_replace()``. The implementation should store the event metadata: buffer index, event size, etc.
3. If the event cannot be added because the queue is full, the event engine calls ``LLUI_INPUT_IMPL_log_queue_full()``. The implementation can print a warning, throw an error, etc.
4. MicroUI reads an event, the event engine calls ``LLUI_INPUT_IMPL_log_queue_read()``. The implementation has to update its metadata (if required).

The following steps describe how the dump is performed:

1. The BSP calls ``LLUI_INPUT_dump()``: the event engine starts a dump of the event buffer.
2. First, the event engine dumps the older events. It calls ``LLUI_INPUT_IMPL_log_dump()`` for each old event. The log type value is ``0``; it means that all logs are the events or events' data already consumed (`past` events), and the first log is the latest event or data stored in the queue.
3. Then, the event engine dumps the `future` events (events not consumed yet by MicroUI). It calls ``LLUI_INPUT_IMPL_log_dump()`` for each new event. The log type value is ``1``; it means that all logs are the events or data not consumed yet (`future` events).
4. The `future` events can target a MicroUI object (a `Displayable` for a `requestRender` event,  a `Runnable` for a `callSerially` event, etc.). The event engine notifies the logger to print the MicroUI objects by calling ``LLUI_INPUT_IMPL_log_dump()`` with ``2`` as log type value.
5. Finally, the event engine notifies the logger about the end of the dump by calling ``LLUI_INPUT_IMPL_log_dump()`` with ``3`` as log type value.

.. warning:: The dump of MicroUI objects linked to the `future` events is only available with the MicroEJ Architectures 7.16 and higher. With older MicroEJ Architectures, nothing is dumped.
 
An implementation is available on the :ref:`C module<section_ui_releasenotes_cmodule>`. This logger is constituted with two files:

* ``LLUI_INPUT_LOG_impl.c``: this file holds some metadata for each event. When the event engine calls ``LLUI_INPUT_IMPL_log_dump()``, the logger retrieves the event metadata and calls ``microui_event_decoder.c`` functions. To enable this logger, set the define ``MICROUIEVENTDECODER_ENABLED`` in ``microui_event_decoder_conf.h``. 
* ``microui_event_decoder.c``: this file describes the MicroUI events. It has to be customized with the MicroUI event generators identifiers. See ``microui_event_decoder_conf.h``.

Example of a dump:

::

   ============================== MicroUI FIFO Dump ===============================
   ---------------------------------- Old Events ----------------------------------
   [27: 0x00000000] garbage
   [28: 0x00000000] garbage
   [...]  
   [99: 0x00000000] garbage
   [00: 0x08000000] Display SHOW Displayable (Displayable index = 0)
   [01: 0x00000008] Command HELP (event generator 0)
   [02: 0x0d000000] Display REPAINT Displayable (Displayable index = 0)
   [03: 0x07030000] Input event: Pointer pressed (event generator 3)
   [04: 0x009f0063]    at 159,99 (absolute)
   [05: 0x07030600] Input event: Pointer moved (event generator 3)
   [06: 0x00aa0064]    at 170,100 (absolute)
   [07: 0x02030700] Pointer dragged (event generator 3)
   [08: 0x0d000000] Display REPAINT Displayable (Displayable index = 0)
   [09: 0x07030600] Input event: Pointer moved (event generator 3)
   [10: 0x00b30066]    at 179,102 (absolute)
   [11: 0x02030700] Pointer dragged (event generator 3)
   [12: 0x0d000000] Display REPAINT Displayable (Displayable index = 0)
   [13: 0x07030600] Input event: Pointer moved (event generator 3)
   [14: 0x00c50067]    at 197,103 (absolute)
   [15: 0x02030700] Pointer dragged (event generator 3)
   [16: 0x0d000000] Display REPAINT Displayable (Displayable index = 0)
   [17: 0x07030600] Input event: Pointer moved (event generator 3)
   [18: 0x00d00066]    at 208,102 (absolute)
   [19: 0x02030700] Pointer dragged (event generator 3)
   [20: 0x0d000000] Display REPAINT Displayable (Displayable index = 0)
   [21: 0x07030100] Input event: Pointer released (event generator 3)
   [22: 0x00000000]    at 0,0 (absolute)
   [23: 0x00000008] Command HELP (event generator 0)
   ---------------------------------- New Events ----------------------------------
   [24: 0x0d000000] Display REPAINT Displayable (Displayable index = 0)
   [25: 0x07030000] Input event: Pointer pressed (event generator 3)
   [26: 0x002a0029]    at 42,41 (absolute)
   --------------------------- New Events' Java objects ---------------------------
   [java/lang/Object[2]@0xC000FD1C
	[0] com/microej/examples/microui/mvc/MVCDisplayable@0xC000BAC0
	[1] null
   ================================================================================

Notes:

* The event ``24`` holds an object in the events objects array (a ``Displayable``); its object index is ``0``. 
* An object is ``null`` when the memory slot has been used during the application execution but freed at the dump time.
* The object array' size is the maximum of non-null objects reached during application execution.
* The indices of old events are out-of-date: the memory slot is now null or reused by a newer event.
* The event ``25`` targets the event generator ``3``; the identifier is available in ``microui_constants.h`` (created during the MicroEJ Platform build, see :ref:`section_inputs_static_init`). 
* The events ``27`` to ``99`` cannot be identified (no metadata or partial event content due to circular queue management).
* Refers to the implementation on the :ref:`C module<section_ui_releasenotes_cmodule>` to have more information about the format of the event; this implementation is always up-to-date with the MicroUI implementation.

Dependencies
============

-  MicroUI module (see :ref:`section_microui`)

-  Static MicroUI initialization step (see :ref:`section_static_init`). This step generates a header file which contains some unique event generator IDs. These IDs must be used in the BSP to make the link between the input devices drivers and the MicroUI ``Event Generator``\ s.

-  ``LLUI_INPUT_impl.h`` implementation (see :ref:`LLINPUT-API-SECTION`).


.. _section_inputs_installation:

Installation
============

Input module is a sub-part of the MicroUI library. The Input module is installed at same time than MicroUI module. 

Use
===

The MicroUI Input APIs are available in the classes of packages ``ej.microui.event`` and ``ej.microui.event.generator``.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
