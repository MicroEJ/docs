.. _pack_event:

===========
Event Queue
===========


Principle
=========

The Event Queue module provides an asynchronous communication interface between the native world and the Java world based on events.


Functional Description
======================


Overview
--------

The Event Queue Foundation Library allows the user to send events from the native world to the Java world. It is composed of a Java API that provides mechanisms to register to specific events notifications and a native API that allows to send events in the queue.

.. figure:: images/event-queue-overview.png
   :alt: Event Queue Overview
   :align: center
   :scale: 65%

   Event Queue Overview

A FIFO mechanism is implemented in the native side and is system specific. The user can offer events to this FIFO by using the native API. 

Events notifications are handled using event listeners (Observer design pattern). Application code has to register event listeners to event handler (provided by the Foundation Library) to be notified when new events are coming.

Then the pump is in charge of retrieving new events pushed in the FIFO and notify the application and the event listeners. 

Architecture
------------

The Event Queue Foundation Library use a dedicated Java thread to forward and process events. Application event listeners calls are done in the context of the Event Queue thread. 

.. figure:: images/event-queue-architecture.png
   :alt: Event Queue Architecture
   :align: center
   :scale: 65%

   Event Queue Architecture


Events reading operations are done using SNI mechanism. Event Queue Java thread is suspended if an event read is called and the events FIFO is empty. Event Queue Java thread resume is done by native part when a new event is sent if the events FIFO was previously empty.

.. figure:: images/event-queue-synchronization.png
   :alt: Event Queue Task Synchronization
   :align: center
   :scale: 65%

   Event Queue Task Synchronization


Event format
------------
Only integers (4 bytes) are sent through the FIFO, so there is two kind of events that can be sent over the Event Queue:

- Non-extended event: event that fits on 4 bytes.
- Extended event: event that do not fit on 4 bytes. 

.. code-block:: java

    +--------------+----------+---------------------------------------------------+
    | Extended (1) | Type (7) | Data (if Extended=0), Length (if Extended=1) (24) |
    +--------------+----------+---------------------------------------------------+
    ...
    +-----------------------------------------------------------------------------+
    |                  Extended Data for extended events (32)                     | (x integers)
    +-----------------------------------------------------------------------------+

Format explanation:

- `Extended`: extended event flag, give the kind of event sent. (1 bit) 
- `Type`: event type that allows to find the corresponding event listener. (7 bits)
- `Length`: length of the data in bytes, only if it is an extended event. (24 bits)
- `Data`: data for non-extended events. (24 bits)
- `Extended data`: data for extended events. (Length bytes)

Event listener
--------------

The user can register some listeners to the Event Queue. 
Each listener is registered with an event type.
A listener can be registered for several event types but each event type can only have one listener. 
When the queue will receive an event from the FIFO, it will get the event type and check if it is an extended event. 
Then it will check if there is a listener registered for this event type.
If so, it will call its handle method depending on the extended event flag. 
If there is no listener corresponding to the event type, it will call the defaultListener. 

You can create your own Event listener by implementing the EventListener interface. 
It contains two methods that are used to handle non-extended and extended events. 

Before registering your listener, you have to get a valid type using ``getNewType()`` method from EventQueue API. 
Then you can register your listener using ``registerListener(EventListener listener, int type)`` method from the EventQueue API. 

To set the defaultListener, you have to use ``setDefaultListener(EventListener listener)`` from the EventQueue API. 

Non-extended event
------------------

Non-extended events are events that can stands on 32 bits.

.. code-block:: java

    +-------+----------+-----------+
    | 0 (1) | Type (7) | Data (24) |
    +-------+----------+-----------+

The first bit is equal to 0 saying that this is a non-extended event.

Then there is the event type that stands on 7 bits. 

To finish there is the data that you want to send through the Event Queue. 
It stands on 24 bits. 

Offer the event
^^^^^^^^^^^^^^^

There is two ways to send a non-extended event through the Event Queue: from the native API or the Java API. 

From C API
""""""""""

To send a non-extended event through the Event Queue using the native API, you have to use ``LLEVENT_offerEvent(int32_t type, int32_t data)`` method from LLEVENT.h.

For example: 

.. code-block:: c

   int type = 1;
   int data = 12;

   LLEVENT_offerEvent(type, data);


From Java API
"""""""""""""

To send a non-extended event through the Event Queue using the Java API, you have to use ``offerEvent(int type, int data)`` method from EventQueue API.

For example: 

.. code-block:: java

   EventQueue eventQueue = EventQueue.getInstance();

   int type = 1;
   int data = 12;

   eventQueue.offerEvent(type, data);


Handle the event
^^^^^^^^^^^^^^^^

To handle a non-extended event, you have to implement the ``handleEvent(int type, int data)`` method of your listener. 
You can process the data received by the Event Queue on this method. 

For example: 

.. code-block:: java

   public class MyListener implements EventListener{
      @Override
      public void handleEvent(int type, int data) {
         System.out.println("My data is equal to: " + data);
      }
   }


Extended event
--------------

Extended events are events that can not stands on 32 bits.

.. code-block:: java

    +-------+----------+-------------+
    | 1 (1) | Type (7) | Length (24) |
    +-------+----------+-------------+
    ...
    +--------------------------------+
    |       Extended Data  (32)      | (x integers)
    +--------------------------------+

On the first 32 bits of the events you will have: 

- First bit is equal to 1 saying that this is an extended event,
- The event type that stands on 7 bits,
- The length of the data in bytes that stands on 24 bits.

Then you will have the data. 
The number of bytes of the data depends on the length. 

Data alignment
^^^^^^^^^^^^^^

To process the data from an extended event, you will use the EventDataReader API.
You will see it more in details in the :ref:`Handle the event <handle_extended_event_section>` section.

With EventDataReader API, there is two way to read an event:

- Read the data with ``read(byte[] b, int off, int len)`` or ``readFully(byte[] b)`` methods. 

   - You will get the data in a byte array and can process it in your ``handleExtendedEvent`` method.
   - You can **choose your own alignment** when sending extended event through the Event Queue. 

- Read the data with the methods related to the primitive types such as ``readBoolean()`` or ``readByte()``. 

   - It is the easiest way to process your data because you don't have to deal with the byte arrays. 
   - Your **must use the following data alignment** when sending extended event through the Event Queue: 

      - A **boolean** (1 byte) will be 1-byte aligned.
      - A **byte** (1 byte) will be 1-byte aligned.
      - A **char** (2 bytes) will be 2-byte aligned.
      - A **double** (8 bytes) will be 8-byte aligned.
      - A **float** (4 bytes) will be 4-byte aligned.
      - An **int** (4 bytes) will be 4-byte aligned.
      - A **long** (8 bytes) will be 8-byte aligned.
      - A **short** (2 bytes) will be 2-byte aligned.
      - An **unsigned byte** (1 bytes) will be 1-byte aligned.
      - A **unsigned short** (2 bytes) will be 2-byte aligned.

Offer the event
^^^^^^^^^^^^^^^

There is two ways to send an extended event through the Event Queue: from the native API or the Java API. 

From C API
""""""""""

To send an extended event through the Event Queue using the native API, you have to use ``LLEVENT_offerExtendedEvent(int32_t type, void* data, int32_t data_length)`` method from LLEVENT.h.

For example: 

.. code-block:: c

   struct accelerometer_data {
      int x;
      int y;
      int z;
   }

   int type = 1;

   struct accelerometer_data data;
   data.x = 42;
   data.y = 72;
   data.z = 21;

   LLEVENT_offerExtendedEvent(type, (void*)&data, sizeof(data));


From Java API
"""""""""""""

To send an extended event through the Event Queue using the Java API, you have to use ``offerExtendedEvent(int type, byte[] data)`` method from EventQueue API.

For example: 

.. code-block:: java

   EventQueue eventQueue = EventQueue.getInstance();

   int type = 1;

   // Array of 3 integers. Each integer is stored in 4 bytes.
   byte[] accelerometerData = new byte[3*4];

   // Write integers into the byte array using ByteArray API.
   ByteArray.writeInt(accelerometerData, 0, 42);
   ByteArray.writeInt(accelerometerData, 4, 72);
   ByteArray.writeInt(accelerometerData, 8, 21);

   eventQueue.offerExtendedEvent(type, accelerometerData);


.. _handle_extended_event_section:

Handle the event
^^^^^^^^^^^^^^^^

To handle an extended event, you have to implement the ``handleExtendedEvent(int type, EventDataReader eventDataReader)`` method of your listener. 
You can process the data received by the Event Queue on this method. 

It provides an EventDataReader that contains the methods needed to read the data of an extended event. 

For example: 

.. code-block:: java

   public class MyListener implements EventListener{
      @Override
      public void handleExtendedEvent(int type, EventDataReader eventDataReader) {
         int x = 0;
         int y = 0;
         int z = 0;

         try {
            x = eventDataReader.readInt();
            y = eventDataReader.readInt();
            z = eventDataReader.readInt();
         } catch (IOException e) {
            System.out.println("IOException while reading accelerometer values from the EventDataReader.");
         }

         System.out.println("Accelerometer values: X = " + x + ", Y = " + y + ", Z = " + z + ".");
      }
   }


Dependencies
============

-  ``LLEVENT_impl.h`` and ``LLEVENT.h`` implementations (see
   :ref:`LLEVENT-API-SECTION`).

.. _pack_event_installation:

Installation
============

The Event Queue :ref:`Pack <pack_overview>` module must be installed in your VEE Port.

In the Platform configuration project, (``-configuration`` suffix), add
the following dependency to the :ref:`module.ivy <mmm_module_description>` file:

::

	<dependency org="com.microej.pack.event" name="event-pack" rev="1.0.0" transitive="false"/>

The Platform project must be rebuilt (:ref:`platform_build`).

Use
===

The `Event Queue API Module`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project to use the Event Queue Foundation Library.

.. code-block:: xml

   <dependency org="ej.api" name="event" rev="1.0.0"/>

.. _Event Queue API Module: https://repository.microej.com/modules/ej/api/
..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
