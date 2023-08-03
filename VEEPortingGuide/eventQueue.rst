.. _pack_event:

===========
Event Queue
===========


Principle
=========

The Event Queue Foundation Library provides an asynchronous communication interface between the native world and the Java world based on events.


Functional Description
======================


Overview
--------

The Event Queue Foundation Library allows users to send events from the native world to the Java world. It is composed of a Java API that provides mechanisms to register specific event notifications and a C API that allows someone to send events in the queue.

.. figure:: images/event-queue-overview.png
   :alt: Event Queue Overview
   :align: center
   :scale: 65%

   Event Queue Overview

A FIFO mechanism is implemented on the native side and is system specific. The user can offer events to this FIFO by using the C or the Java API. 

Event notifications are handled using event listeners (Observer design pattern). The application code has to register event listeners to be notified when new events are coming.

Then the Event Pump automatically retrieves new events pushed in the FIFO and notifies the event listeners. 

Architecture
------------

The Event Queue Foundation Library uses a dedicated Java thread to forward and process events. Application event listener's calls are done in the context of the Event Queue thread. 

.. figure:: images/event-queue-architecture.png
   :alt: Event Queue Architecture
   :align: center
   :scale: 65%

   Event Queue Architecture


Events reading operations are done using the SNI mechanism. Event Queue Java thread is suspended when the events FIFO is empty and resumed when a new event is sent.

Event format
------------
An event is composed of a type and, optionally, data. The type identifies the listener that will handle the event. 
The data is application specific and passed to the listener as a raw byte array.

The items stored in the FIFO buffer are integers (4 bytes). There are two kinds of events that can be sent over the Event Queue:

- Standard event: an event with data that fits on 24 bits. The event is stored in the FIFO as a single 4 bytes item.
- Extended event: an event with data that does not fit on 24 bits. The event is stored in the FIFO as multiple 4 bytes items.


.. code-block:: java

    +--------------+----------+---------------------------------------------------+
    | Extended (1) | Type (7) | Data (if Extended==0), Length (if Extended==1) (24) |
    +--------------+----------+---------------------------------------------------+
    ...
    +-----------------------------------------------------------------------------+
    |                  Extended Data for extended events (32)                     | (Length bytes)
    +-----------------------------------------------------------------------------+

Format explanation:

- `Extended` (1 bit): event kind flag (0 for standard event, 1 for extended event).
- `Type` (7 bits): event type, which allows to find the corresponding event queue listener.
- `Length` (24 bits): length of the data in bytes (for extended events only).
- `Data` (24 bits): standard event data (for standard events only).
- `Extended data` (``Length`` bytes): extended event data (for extended events only).

.. _event_queue_listener:

Event Queue listener
--------------------

An application can register listeners to the Event Queue. 
Each listener is registered for a specific event type.
The same listener can be registered several times for different event types, but each event type can only have one listener. 

When the queue receives an event from the FIFO, it will get the event type and check if it is an extended event. 
Then it will check if a listener is registered for this event type.
If so, it will call its handle method depending on the extended event flag. 
It will call the default listener if no listener corresponds to the event type. 

You can create your Event Queue listener by implementing the ``EventQueueListener`` interface.
It contains two methods that are used to handle standard and extended events. 

Before registering your listener, you must get a valid unique type using the ``getNewType()`` method from the ``EventQueue`` class.
Then you can register your listener using the ``registerListener(EventQueueListener listener, int type)`` method from the ``EventQueue`` class.

The unique type your listener uses could be stored on the Java world and passed/stored to the C world.
One way to do it is to create a native method that sends the event type to the C world during the initialization phase.

To set the default listener, you must use ``EventQueue.setDefaultListener(EventQueueListener listener)``.

For example: 

.. code-block:: java

   public static int eventType;

   public static void main(String[] args) throws InterruptedException {
      EventQueue eventQueue = EventQueue.getInstance();

      // Get the unique type to register your listener.
      // eventType must be stored if you want to offer an event from the Java API.
      eventType = eventQueue.getNewType();

      // Create and register a listener.
      eventQueue.registerListener(new ExampleListener(), eventType);

      // Send eventType to the C world.
      initialize(eventType);
   }

   /**
   * This native method will take the event type as an entry and store it in the C world. 
   */ 
   public static native void initialize(int type);


Standard event
--------------

Standard events are events with data that can be stored on 24 bits.

.. code-block:: java

    +-------+----------+-----------+
    | 0 (1) | Type (7) | Data (24) |
    +-------+----------+-----------+

The first bit equals 0, indicating that this is a standard event.

Then there is the event type stored on 7 bits.

To finish, there is the data that you want to send to the application event listener. 
It is stored on 24 bits. 

Offer the event
^^^^^^^^^^^^^^^

There are two ways to send a standard event through the Event Queue: from the C API or the Java API. 

From C API
""""""""""

To send a standard event through the Event Queue using the C API, you must use the ``LLEVENT_offerEvent(int32_t type, int32_t data)`` method from ``LLEVENT.h``.

For example: 

.. code-block:: c

   // Assuming that event_type has been passed from the Java world through a native method after registering your listener.
   int type = event_type;
   int data = 12;

   LLEVENT_offerEvent(type, data);


From Java API
"""""""""""""

To send a standard event through the Event Queue using the Java API, you must use the ``offerEvent(int type, int data)`` method from the ``EventQueue`` class.

For example: 

.. code-block:: java

   EventQueue eventQueue = EventQueue.getInstance();

   // Assuming that eventType has been stored in the Java world when you registered the listener.
   int type = eventType;
   int data = 12;

   eventQueue.offerEvent(type, data);


Handle the event
^^^^^^^^^^^^^^^^

To handle a standard event, you must implement your listener ``handleEvent(int type, int data)`` method. 
You can process the data received by the Event Queue in this method. 

First, you have to register your listener as explained :ref:`Event Queue listener <event_queue_listener>` in section.

For example: 

.. code-block:: java

   EventQueue queue = EventQueue.getInstance();
   int type = queue.getNewType();
   initialize(type);
   queue.registerListener(type, new EventQueueListener() {
      @Override
      public void handleEvent(int type, int data) {
         System.out.println("My data is equal to: " + data);
      }
      @Override
      public void handleExtendedEvent(int type, EventDataReader eventDataReader) {
         throw new RuntimeException();
      }
   });


Extended event
--------------

Extended events are events with data that can not be stored on 24 bits.

.. code-block:: java

    +-------+----------+-------------+
    | 1 (1) | Type (7) | Length (24) |
    +-------+----------+-------------+
    ...
    +--------------------------------+
    |       Extended Data  (32)      | (Length bytes)
    +--------------------------------+

On the first 32 bits of the events, you will have: 

- First bit is equal to 1, saying that this is an extended event,
- The event type stored on 7 bits,
- The length of the data following the header in bytes stored on 24 bits.

Then you will have the data. 
The number of bytes of the data depends on the length. 

Data Alignment
^^^^^^^^^^^^^^

To process the data from an extended event, you will use an ``EventDataReader`` object.
You will see it more in detail in the :ref:`Handle the event <handle_extended_event_section>` section.

With ``EventDataReader`` API, there are two ways to read an event:

- Read the data with ``read(byte[] b, int off, int len)`` or ``readFully(byte[] b)`` methods. 

   - You will get the data in a byte array and can process it on your own in your ``handleExtendedEvent(int type, EventDataReader eventDataReader)`` method.

- Read the data with the methods related to the primitive types such as ``readBoolean()`` or ``readByte()``. 

   - The reader is designed to parse C-struct data.
   - To use the methods, **your fields must follow this alignment:**

      - A **boolean** (1 byte) will be 1-byte aligned.
      - A **byte** (1 byte) will be 1-byte aligned.
      - A **char** (2 bytes) will be 2-byte aligned.
      - A **double** (8 bytes) will be 8-byte aligned.
      - A **float** (4 bytes) will be 4-byte aligned.
      - An **int** (4 bytes) will be 4-byte aligned.
      - A **long** (8 bytes) will be 8-byte aligned.
      - A **short** (2 bytes) will be 2-byte aligned.
      - An **unsigned byte** (1 byte) will be 1-byte aligned.
      - A **unsigned short** (2 bytes) will be 2-byte aligned.

Offer the event
^^^^^^^^^^^^^^^

There are two ways to send an extended event through the Event Queue: from the C API or the Java API. 

From C API
""""""""""

To send an extended event through the Event Queue using the C API, you have to use the ``LLEVENT_offerExtendedEvent(int32_t type, void* data, int32_t data_length)`` method from ``LLEVENT.h``.

For example: 

.. code-block:: c

   struct accelerometer_data {
      int x;
      int y;
      int z;
   }

   // Assuming that event_type has been passed from the Java world through a native method after registering your listener.
   int type = event_type;

   struct accelerometer_data data;
   data.x = 42;
   data.y = 72;
   data.z = 21;

   LLEVENT_offerExtendedEvent(type, (void*)&data, sizeof(data));


From Java API
"""""""""""""

To send an extended event through the Event Queue using the Java API, you must use the ``offerExtendedEvent(int type, byte[] data)`` method from the EventQueue API.

For example: 

.. code-block:: java

   EventQueue eventQueue = EventQueue.getInstance();

   // Assuming that eventType has been stored in the Java world when you registered the listener.
   int type = eventType;

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

To handle an extended event, you must implement your listener's ``handleExtendedEvent(int type, EventDataReader eventDataReader)`` method. 
You can process the data received by the Event Queue on this method. 

It provides an EventDataReader that contains the methods needed to read the data of an extended event. 

First, you have to register your listener as explained :ref:`Event Queue listener <event_queue_listener>` in section.

For example: 

.. code-block:: java

   EventQueue queue = EventQueue.getInstance();
   int type = queue.getNewType();
   initialize(type);
   queue.registerListener(type, new EventQueueListener() {
      @Override
      public void handleEvent(int type, int data) {
         throw new RuntimeException();
      }
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
   });

Mock the Event Queue
--------------------

To simulate event that are normally sent through the C API, use the Event Queue Mock API from your mock.

The Event Queue Mock API dependency must be added to the :ref:`module.ivy <mmm_module_description>` of your MicroEJ Mock project.

.. code-block:: xml

   <dependency org="com.microej.pack.event" name="event-pack" rev="2.0.0" conf="provided->mockAPI"/>

It provides two methods: 

- ``EventQueueMock.offerEvent(int type, int data)`` is the equivalent of ``LLEVENT_offerEvent(int32_t type, int32_t data)`` method from ``LLEVENT.h``.
- ``EventQueueMock.offerExtendedEvent(int type, byte[] data, int dataLength)`` is the equivalent of ``LLEVENT_offerExtendedEvent(int32_t type, void* data, int32_t data_length)`` method from ``LLEVENT.h``.

Example of use:

.. code-block:: java

   // Assuming that event_type has been passed from your Application through a native method after registering your listener.
   int type = event_type;
   int data = 12;

   EventQueueMock.offerEvent(type, data);

Dependencies
============

-  ``LLEVENT_impl.h`` and ``LLEVENT.h`` implementations (see
   :ref:`LLEVENT-API-SECTION`).

.. _pack_event_installation:

Installation
============

The Event Queue :ref:`Pack <pack_overview>` module must be installed in your VEE Port.

In the VEE Port configuration project, add the following dependency to the :ref:`module.ivy <mmm_module_description>` file:

::

   <dependency org="com.microej.pack.event" name="event-pack" rev="1.0.0" transitive="false"/>


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
