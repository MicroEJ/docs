Comm Port Identifier
====================

Each serial port available for use in ECOM Comm can be identified in
three ways:

-  An application port number. This identifier is specific to the
   application, and should be used to identify the data stream that the
   port will carry (for example, "debug traces" or "GPS data").

-  A platform port number. This is specific to the platform, and may
   directly identify an hardware device  [1]_ .

-  A platform port name. This is mostly used for dynamic connections or
   on platforms having a file-system based device mapping.

When the Comm Port is identified by a number, its string identifier is
the concatenation of "com" and the number (e.g. com11).

Opening Sequence
----------------

The following flow chart explains Comm Port opening sequence according
to the given Comm Port identifier.

.. [1]
   Some drivers may reuse the same UART device for different ECOM ports
   with a hardware multiplexer. Drivers can even treat the platform port
   number as a logical id and map the ids to various I/O channels.
