.. _LLINPUT-API-SECTION:

LLINPUT: Inputs
===============

``LLINPUT`` API is composed of the following files:

-  the file ``LLINPUT_impl.h`` that defines the functions to be
   implemented

-  the file ``LLINPUT.h`` that provides the functions for sending events

Implementation
--------------

``LLINPUT_IMPL_initialize`` is the first function called by the input
stack, and it may be used to initialize the underlying devices and bind
them to event generator IDs.

``LLINPUT_IMPL_enterCriticalSection`` and
``LLINPUT_IMPL_exitCriticalSection``  need to provide the stack with a
critical section mechanism for synchronizing devices when sending events
to the internal event queue. The mechanism used to implement the
synchronization will depend on the platform configuration (with or
without RTOS), and whether or not events are sent from an interrupt
context.

``LLINPUT_IMPL_getInitialStateValue`` allows the input stack to get the
current state for devices connected to the MicroUI States event
generator, such as switch selector, coding wheels, etc.

Sending Events
--------------

The ``LLINPUT`` API provides two generic functions for a C driver to
send data to its associated event generator:

-  ``LLINPUT_sendEvent``:  Sends a 32-bit encoded event to a specific
   event generator, specified by its ID. If the input buffer is full,
   the event is not added, and the function returns 0; otherwise it
   returns 1.

-  ``LLINPUT_sendEvents``: Sends event data to a specific event
   generator, specified by its ID. If the input buffer cannot receive
   the whole data, the event is not added, and the function returns 0;
   otherwise it returns 1.

Events will be dispatched to the associated event generator that will be
responsible for decoding them (see `??? <#javaEventGenerators>`__).

The UI extension provides an implementation for each of MicroUI's
built-in event generators. Each one has dedicated functions that allows
a driver to send them structured data without needing to understand the
underlying protocol to encode/decode the data.
`table_title <#llinputApiEvtGen>`__ shows the functions provided to send
structured events to the predefined event generators:

.. table:: LLINPUT API for predefined event generators

   +-----------------------------+---------+-----------------------------+
   | Function name               | Default | Comments                    |
   |                             | event   |                             |
   |                             | ge      |                             |
   |                             | nerator |                             |
   |                             | ki      |                             |
   |                             | nd [1]_ |                             |
   +=============================+=========+=============================+
   | `                           | Command | Constants are provided that |
   | `LLINPUT_sendCommandEvent`` |         | define all standard MicroUI |
   |                             |         | commands [MUI].             |
   +-----------------------------+---------+-----------------------------+
   | ``LLINP                     | Buttons | In the case of              |
   | UT_sendButtonPressedEvent`` |         | chronological sequences     |
   |                             |         | (for example, a RELEASE     |
   | ``LLINPU                    |         | that may occur only after a |
   | T_sendButtonReleasedEvent`` |         | PRESSED), it is the         |
   |                             |         | responsibility of the       |
   | ``LLINPU                    |         | driver to ensure the        |
   | T_sendButtonRepeatedEvent`` |         | integrity of such           |
   |                             |         | sequences.                  |
   +-----------------------------+---------+-----------------------------+
   | ``LLINPU                    | Pointer | In the case of              |
   | T_sendPointerPressedEvent`` |         | chronological sequences     |
   |                             |         | (for example, a RELEASE     |
   | ``LLINPUT                   |         | that may occur only after a |
   | _sendPointerReleasedEvent`` |         | PRESSED), it is the         |
   |                             |         | responsibility of the       |
   | ``LLIN                      |         | driver to ensure the        |
   | PUT_sendPointerMovedEvent`` |         | integrity of such           |
   |                             |         | sequences. Depending on     |
   |                             |         | whether a button of the     |
   |                             |         | pointer is pressed while    |
   |                             |         | moving, a DRAG and/or a     |
   |                             |         | MOVE MicroUI event is       |
   |                             |         | generated.                  |
   +-----------------------------+---------+-----------------------------+
   | ``LLINPUT_sendStateEvent``  | States  | The initial value of each   |
   |                             |         | state machine (of a States) |
   |                             |         | is retrieved by a call to   |
   |                             |         | ``LLINPUT_                  |
   |                             |         | IMPL_getInitialStateValue`` |
   |                             |         | that must be implemented by |
   |                             |         | the device. Alternatively,  |
   |                             |         | the initial value can be    |
   |                             |         | specified in the XML static |
   |                             |         | configuration.              |
   +-----------------------------+---------+-----------------------------+
   | ``LLIN                      | Pointer | In the case of              |
   | PUT_sendTouchPressedEvent`` |         | chronological sequences     |
   |                             |         | (for example, a RELEASE     |
   | ``LLINP                     |         | that may only occur after a |
   | UT_sendTouchReleasedEvent`` |         | PRESSED), it is the         |
   |                             |         | responsibility of the       |
   | ``LL                        |         | driver to ensure the        |
   | INPUT_sendTouchMovedEvent`` |         | integrity of such           |
   |                             |         | sequences. These APIs will  |
   |                             |         | generate a DRAG MicroUI     |
   |                             |         | event instead of a MOVE     |
   |                             |         | while they represent a      |
   |                             |         | touch pad over a display.   |
   +-----------------------------+---------+-----------------------------+

Event Buffer
------------

The maximum usage of the internal event buffer may be retrieved at
runtime using the ``LLINPUT_getMaxEventsBufferUsage`` function. This is
useful for tuning the size of the buffer.

.. [1]
   The implementation class is a subclass of the MicroUI class of the
   column.
