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
