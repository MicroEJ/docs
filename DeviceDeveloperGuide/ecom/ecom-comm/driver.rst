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
file, for example [1]_:

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

When opening a port from the MicroEJ application, each connection
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

The Buffered Comm stream
------------------------

In Buffered mode, two buffers are allocated by the driver for sending
and receiving data. The ECOM Comm C module will fill the transmit
buffer, and get bytes from the receive buffer. There is no flow control.

When the transmit buffer is full, an attempt to write more bytes from
the MicroEJ application will block the Java thread trying to write,
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

.. [1]
   The following examples use Buffered connections, but Custom
   connections follow the same pattern.
