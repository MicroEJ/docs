=========
ECOM Comm
=========


Principle
=========

The ECOM Comm Java library provides support for serial communication.
ECOM Comm extends ECOM to allow stream communication via serial
communication ports (typically UARTs). In the MicroEJ Application, the
connection is established using the ``Connector.open()`` method. The
returned connection is a ``ej.ecom.io.CommConnection`` , and the input
and output streams can be used for full duplex communication.

The use of ECOM Comm in a custom platform requires the implementation of
an UART driver. There are two different modes of communication:

-  In Buffered mode, ECOM Comm manages software FIFO buffers for
   transmission and reception of data. The driver copies data between
   the buffers and the UART device.

-  In Custom mode, the buffering of characters is not managed by ECOM
   Comm. The driver has to manage its own buffers to make sure no data
   is lost in serial communications because of buffer overruns.

This ECOM Comm implementation also allows dynamic add or remove of a
connection to the pool of available connections (typically hot-plug of a
USB Comm port).


Functional Description
======================

The ECOM Comm process respects the ECOM process. Please refer to the
illustration :ref:`"ECOM flow" <fig_ecom-flow>`.


Component architecture
======================

The ECOM Comm C module relies on a native driver to perform actual
communication on the serial ports. Each port can be bound to a different
driver implementation, but most of the time, it is possible to use the
same implementation (i.e. same code) for multiple ports. Exceptions are
the use of different hardware UART types, or the need for different
behaviors.

Five C header files are provided:

-  ``LLCOMM_impl.h``

   Defines the set of functions that the driver must implement for the
   global ECOM comm stack, such as synchronization of accesses to the
   connections pool.

-  ``LLCOMM_BUFFERED_CONNECTION_impl.h``

   Defines the set of functions that the driver must implement to
   provide a Buffered connection

-  ``LLCOMM_BUFFERED_CONNECTION.h``

   Defines the set of functions provided by ECOM Comm that can be called
   by the driver (or other C code) when using a Buffered connection

-  ``LLCOMM_CUSTOM_CONNECTION_impl.h``

   Defines the set of functions that the driver must implement to
   provide a Custom connection

-  ``LLCOMM_CUSTOM_CONNECTION.h``

   Defines the set of functions provided by ECOM Comm that can be called
   by the driver (or other C code) when using a Custom connection

The ECOM Comm drivers are implemented using standard LLAPI features. The
diagram below shows an example of the objects (both Java and C) that
exist to support a Buffered connection.

.. figure:: images/architecture.*
   :alt: ECOM Comm components
   :width: 80.0%
   :align: center

   ECOM Comm components

The connection is implemented with three objects  [1]_ :

-  The Java object used by the application; an instance of
   ``ej.ecom.io.CommConnection``

-  The connection object within the ECOM Comm C module

-  The connection object within the driver

Each driver implementation provides one or more connections. Each
connection typically corresponds to a physical UART.

.. [1]
   This is a conceptual description to aid understanding - the reality
   is somewhat different, although that is largely invisible to the
   implementor of the driver.


Comm Port Identifier
====================

Each serial port available for use in ECOM Comm can be identified in
three ways:

-  An application port number. This identifier is specific to the
   application, and should be used to identify the data stream that the
   port will carry (for example, "debug traces" or "GPS data").

-  A platform port number. This is specific to the platform, and may
   directly identify an hardware device  [2]_ .

-  A platform port name. This is mostly used for dynamic connections or
   on platforms having a file-system based device mapping.

When the Comm Port is identified by a number, its string identifier is
the concatenation of "com" and the number (e.g. com11).

.. [2]
   Some drivers may reuse the same UART device for different ECOM ports
   with a hardware multiplexer. Drivers can even treat the platform port
   number as a logical id and map the ids to various I/O channels.

.. _section_ecomcomm_mapping:

Application port mapping
------------------------

The mapping from application port numbers to platform ports is done in
the application launch configuration. This way, the application can
refer only to the application port number, and the data stream can be
directed to the matching I/O port on different versions of the hardware.

Ultimately, the application port number is only visible to the
application. The platform identifier will be sent to the driver.


Opening Sequence
----------------

The following flow chart explains Comm Port opening sequence according
to the given Comm Port identifier.

.. figure:: images/comm_open.*
    :alt: Comm Port Open Sequence
    :width: 80.0%
    :align: center

    Comm Port Open Sequence


.. _section_ecomcomm_dynamic_connections:

Dynamic Connections
===================

The ECOM Comm stack allows to dynamically add and remove connections
from the :ref:`section_ecomcomm_driver`. When a connection is added,
it can be immediately open by the application. When a connection is
removed, the connection cannot be open anymore and
``java.io.IOException`` is thrown in threads that are using it.

In addition, a dynamic connection can be registered and unregistered in
ECOM device manager (see :ref:`section_ecom_dm`). The registration
mechanism is done in dedicated thread. It can be enabled or disabled,
see :ref:`workbenchLaunchOptions`.

A removed connection is alive until it is closed by the application and,
if enabled, unregistered from ECOM device manager. A connection is
effectively uninstalled (and thus eligible to be reused) only when it is
released by the stack.

The following sequence diagram shows the lifecycle of a dynamic
connection with ECOM registration mechanism enabled.

.. figure:: images/dyn_sequence.*
    :alt: Dynamic Connection Lifecycle
    :width: 100.0%
    :align: center

    Dynamic Connection Lifecycle


Java API
========

Opening a connection is done using
``ej.ecom.io.Connector.open(String name)`` . The connection string (the
``name`` parameter) must start with "comm:", followed by the Comm port
identifier, and a semicolon-separated list of options. Options are the
baudrate, the parity, the number of bits per character, and the number
of stop bits:

-  baudrate=n (9600 by default)

-  bitsperchar=n where n is in the range 5 to 9 (8 by default)

-  stopbits=n where n is 1, 2, or 1.5 (1 by default)

-  parity=x where x is odd, even or none (none by default)

All of these are optional. Illegal or unrecognized parameters cause an
``IllegalArgumentException`` .


.. _section_ecomcomm_driver:

Driver API
==========

The ECOM Comm Low Level API is designed to allow multiple
implementations (e.g. drivers that support different UART hardware) and
connection instances (see Low Level API Pattern chapter). Each ECOM Comm
driver defines a data structure that holds information about a
connection, and functions take an instance of this data structure as the
first parameter.

The name of the implementation must be set at the top of the driver C
file, for example [3]_:

::

   #define LLCOMM_BUFFERED_CONNECTION MY_LLCOMM

This defines the name of this implementation of the
``LLCOMM_BUFFERED_CONNECTION`` interface to be ``MY_LLCOMM``.

The data structure managed by the implementation must look like this:

::

   typedef struct MY_LLCOMM{
       struct LLCOMM_BUFFERED_CONNECTION header;
       // extra data goes here
   } MY_LLCOMM;

   void MY_LLCOMM_new(MY_LLCOMM* env);

In this example the structure contains only the default data, in the
header field. Note that the header must be the first field in the
structure. The name of this structure must be the same as the
implementation name (``MY_LLCOMM`` in this example).

The driver must also declare the "new" function used to initialize
connection instances. The name of this function must be the
implementation name with ``_new`` appended, and it takes as its sole
argument a pointer to an instance of the connection data structure, as
shown above.

The driver needs to implement the functions specified in the
``LLCOMM_impl.h`` file and for each kind of connection, the
``LLCOMM_BUFFERED_CONNECTION_impl.h`` (or
``LLCOMM_CUSTOM_CONNECTION_impl.h``) file.

The driver defines the connections it provides by adding connection
objects using ``LLCOMM_addConnection``. Connections can be added to the
stack as soon as the ``LLCOMM_initialize`` function is called.
Connections added during the call of the ``LLCOMM_impl_initialize``
function are static connections. A static connection is registered to
the ECOM registry and cannot be removed. When a connection is
dynamically added outside the MicroJVM task context, a suitable
reentrant synchronization mechanism must be implemented (see
``LLCOMM_IMPL_syncConnectionsEnter`` and
``LLCOMM_IMPL_syncConnectionsExit``).

When opening a port from the MicroEJ Application, each connection
declared in the connections pool will be asked about its platform port
number (using the ``getPlatformId`` method) or its name (using the
``getName`` method) depending on the requested port identifier. The
first matching connection is used.

The life of a connection starts with the call to ``getPlatformId()`` or
``getName()`` method. If the the connection matches the port identifier,
the connection will be initialized, configured and enabled.
Notifications and interrupts are then used to keep the stream of data
going. When the connection is closed by the application, interrupts are
disabled and the driver will not receive any more notifications. It is
important to remember that the transmit and receive sides of the
connection are separate Java stream objects, thus, they may have a
different life cycle and one side may be closed long before the other.

.. [3]
   The following examples use Buffered connections, but Custom
   connections follow the same pattern.

The Buffered Comm stream
------------------------

In Buffered mode, two buffers are allocated by the driver for sending
and receiving data. The ECOM Comm C module will fill the transmit
buffer, and get bytes from the receive buffer. There is no flow control.

When the transmit buffer is full, an attempt to write more bytes from
the MicroEJ Application will block the Java thread trying to write,
until some characters are sent on the serial line and space in the
buffer is available again.

When the receive buffer is full, characters coming from the serial line
will be discarded. The driver must allocate a buffer big enough to avoid
this, according to the UART baudrate, the expected amount of data to
receive, and the speed at which the application can handle it.

The Buffered C module manages the characters sent by the application and
stores them in the transmit buffer. On notification of available space
in the hardware transmit buffer, it handles removing characters from
this buffer and putting them in the hardware buffer. On the other side,
the driver notifies the C module of data availability, and the C module
will get the incoming character. This character is added to the receive
buffer and stays there until the application reads it.

The driver should take care of the following:

-  Setting up interrupt handlers on reception of a character, and
   availability of space in the transmit buffer. The C module may mask
   these interrupts when it needs exclusive access to the buffers. If no
   interrupt is available from the hardware or underlying software
   layers, it may be faked using a polling thread that will notify the C
   module.

-  Initialization of the I/O pins, clocks, and other things needed to
   get the UART working.

-  Configuration of the UART baudrate, character size, flow control and
   stop bits according to the settings given by the C module.

-  Allocation of memory for the transmit and receive buffers.

-  Getting the state of the hardware: is it running, is there space left
   in the TX and RX hardware buffers, is it busy sending or receiving
   bytes?

The driver is notified on the following events:

-  Opening and closing a connection: the driver must activate the UART
   and enable interrupts for it.

-  A new byte is waiting in the transmit buffer and should be copied
   immediately to the hardware transmit unit. The C module makes sure
   the transmit unit is not busy before sending the notification, so it
   is not needed to check for that again.

The driver must notify the C module on the following events:

-  Data has arrived that should be added to the receive buffer (using
   the ``LLCOMM_BUFFERED_CONNECTION_dataReceived`` function)

-  Space available in the transmit buffer (using the
   ``LLCOMM_BUFFERED_CONNECTION_transmitBufferReady`` function)

The Custom Comm stream
----------------------

In custom mode, the ECOM Comm C module will not do any buffering. Read
and write requests from the application are immediately forwarded to the
driver.

Since there is no buffer on the C module side when using this mode, the
driver has to define a strategy to store received bytes that were not
handed to the C module yet. This could be a fixed or variable side FIFO,
the older received but unread bytes may be dropped, or a more complex
priority arbitration could be set up. On the transmit side, if the
driver does not do any buffering, the Java thread waiting to send
something will be blocked and wait for the UART to send all the data.

In Custom mode flow control (eg. RTS/CTS or XON/XOFF) can be used to
notify the device connected to the serial line and so avoid losing
characters.


BSP File
========

The ECOM Comm C module needs to know, when the MicroEJ Application is
built, the name of the implementation. This mapping is defined in a BSP
definition file. The name of this file must be ``bsp.xml`` and must be
written in the ECOM comm module configuration folder (near the
``ecom-comm.xml`` file). In previous example the ``bsp.xml`` file would
contain:

.. code-block:: xml
   :caption: ECOM Comm Driver Declaration (bsp.xml)

   <bsp>
       <nativeImplementation
           name="MY_LLCOMM"
           nativeName="LLCOMM_BUFFERED_CONNECTION"
       />
   </bsp>


where ``nativeName`` is the name of the interface, and ``name`` is the
name of the implementation.


.. _section_ecomcomm_xml:

XML File
========

The Java platform has to know the maximum number of Comm ports that can
be managed by the ECOM Comm stack. It also has to know each Comm port
that can be mapped from an application port number. Such Comm port is
identified by its platform port number and by an optional nickname (The
port and its nickname will be visible in the MicroEJ launcher options,
see :ref:`workbenchLaunchOptions` ).

A XML file is so required to configure the Java platform. The name of
this file must be ``ecom-comm.xml``. It has to be stored in the module
configuration folder (see :ref:`section_ecomcomm_installation`).

This file must start with the node ``<ecom>`` and the sub node
``<comms>``. It can contain several time this kind of line:
``<comm platformId="A_COMM_PORT_NUMBER" nickname="A_NICKNAME"/>`` where:

-  ``A_COMM_PORT_NUMBER`` refers the Comm port the Java platform user
   will be able to use (see :ref:`section_ecomcomm_mapping`).

-  ``A_NICKNAME`` is optional. It allows to fix a printable name of the
   Comm port.

The ``maxConnections`` attribute indicates the maximum number of
connections allowed, including static and dynamic connections. This
attribute is optional. By default, it is the number of declared Comm
Ports.

Example: 

.. code-block:: xml
    :caption: ECOM Comm Module Configuration (ecom-comm.xml)

    <ecom>
        <comms maxConnections="20">
            <comm platformId="2"/>
            <comm platformId="3" nickname="DB9"/>
            <comm platformId="5"/>
        </comms>
    </ecom>

First Comm port holds the port 2, second "3" and last "5". Only the
second Comm port holds a nickname "DB9".


ECOM Comm Mock
==============

In the simulation environment, no driver is required. The ECOM Comm mock
handles communication for all the serial ports and can redirect each
port to one of the following:

-  An actual serial port on the host computer: any serial port
   identified by your operating system can be used. The baudrate and
   flow control settings are forwarded to the actual port.

-  A TCP socket. You can connect to a socket on the local machine and
   use netcat or telnet to see the output, or you can forward the data
   to a remote device.

-  Files. You can redirect the input and output each to a different
   file. This is useful for sending precomputed data and looking at the
   output later on for offline analysis.

When using the socket and file modes, there is no simulation of an UART
baudrate or flow control. On a file, data will always be available for
reading and will be written without any delay. On a socket, you can
reach the maximal speed allowed by the network interface.


Dependencies
============

-  ECOM (see :ref:`ecom_`).

-  ``LLCOMM_impl.h`` and ``LLCOMM_xxx_CONNECTION_impl.h`` implmentations
   (see :ref:`LLCOMM-API-SECTION`).


.. _section_ecomcomm_installation:

Installation
============

ECOM-Comm Java library is an additional library. In the platform
configuration file, check :guilabel:`Serial Communication` > :guilabel:`ECOM-COMM` to
install it. When checked, the xml file :guilabel:`ecom-comm` > :guilabel:`ecom-comm.xml`
is required during platform creation to configure the module (see
:ref:`section_ecomcomm_xml`).


Use
===

A classpath variable named ``ECOM-COMM-1.1`` is available. This
foundation library is always required when developing a MicroEJ
application which communicates with some external devices using the
serial communication mode.

This library provides a set of options. Refer to the chapter
:ref:`workbenchLaunchOptions` which lists all available options.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
