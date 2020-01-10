ECOM Comm
=========

Error Messages
--------------

When an exception is thrown by the implementation of the ECOM-COMM API,
the error message

ECOM-COMM:E=<messageId>

is issued, where <messageId> meaning is defined in the next table:

.. table:: ECOM-COMM error messages

   +-------------+--------------------------------------------------------+
   | Message  ID | Description                                            |
   +=============+========================================================+
   | 1           | The connection descriptor must start with ``"comm:"``  |
   +-------------+--------------------------------------------------------+
   | 2           | Reserved.                                              |
   +-------------+--------------------------------------------------------+
   | 3           | The Comm port is unknown.                              |
   +-------------+--------------------------------------------------------+
   | 4           | The connection descriptor is invalid.                  |
   +-------------+--------------------------------------------------------+
   | 5           | The Comm port is already open.                         |
   +-------------+--------------------------------------------------------+
   | 6           | The baudrate is unsupported.                           |
   +-------------+--------------------------------------------------------+
   | 7           | The number of bits per character is unsupported.       |
   +-------------+--------------------------------------------------------+
   | 8           | The number of stop bits is unsupported.                |
   +-------------+--------------------------------------------------------+
   | 9           | The parity is unsupported.                             |
   +-------------+--------------------------------------------------------+
   | 10          | The input stream cannot be opened because native       |
   |             | driver is not able to create a RX buffer to store the  |
   |             | incoming data.                                         |
   +-------------+--------------------------------------------------------+
   | 11          | The output stream cannot be opened because native      |
   |             | driver is not able to create a TX buffer to store the  |
   |             | outgoing data.                                         |
   +-------------+--------------------------------------------------------+
   | 12          | The given connection descriptor option cannot be       |
   |             | parsed.                                                |
   +-------------+--------------------------------------------------------+
