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

.. figure:: inputs/images/drivers-microui-comms.svg
   :alt: Drivers and MicroUI Event Generators Communication
   :width: 80.0%

   Drivers and MicroUI Event Generators Communication

The ``LLINPUT`` API allows multiple pairs of
``<driver - event generator>`` to use the same buffer, and associates
drivers and event generators using an int ID. The ID used is the event
generator ID held within the MicroUI global registry [MUI]. Apart from
sharing the ID used to "connect" one driver's data to its respective
event generator, both entities are completely decoupled.

A Java green thread, called the ``InputPump`` thread, waits for data to
be published by drivers into the "input buffer," and dispatches to the
correct (according to the ID) event generator to read the received data.
This "driver-specific-data" is then transformed into MicroUI events by
event generators and sent to objects that listen for input activity.

.. figure:: inputs/images/microui-events.png
   :alt: MicroUI Events Framework
   :width: 90.0%

   MicroUI Events Framework
