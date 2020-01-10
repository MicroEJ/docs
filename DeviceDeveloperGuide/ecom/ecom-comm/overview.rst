Principle
=========

The ECOM Comm Java library provides support for serial communication.
ECOM Comm extends ECOM to allow stream communication via serial
communication ports (typically UARTs). In the MicroEJ application, the
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
