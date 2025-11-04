Event Queue
===========

Error Messages
--------------

When an exception is thrown by the implementation of the Event Queue API, the
error message

``EVENT-<APIversion>:E=<messageId>``

is issued, where ``<messageId>`` meaning is defined in the next table:

.. table:: Event Queue Error Messages

   +-------------+-------------------------------------------------------------+
   | Message ID  | Description                                                 |
   +=============+=============================================================+
   | -1          | Invalid event type.                                         |
   +-------------+-------------------------------------------------------------+
   | -2          | FIFO buffer is full.                                        |
   +-------------+-------------------------------------------------------------+
   | -3          | Data or data buffer value exceeds 24 bits.                  |
   +-------------+-------------------------------------------------------------+
   | -4          | Maximum number of types has already been registered.        |
   +-------------+-------------------------------------------------------------+
   | -5          | No listener is registered for the provided type.            |
   +-------------+-------------------------------------------------------------+
   | -6          | Default listener cannot be null.                            |
   +-------------+-------------------------------------------------------------+
   | -7          | Not enough bytes remaining in the extended event.           |
   +-------------+-------------------------------------------------------------+
   | -8          | Less than 2 bytes remaining in the extended data.           |
   +-------------+-------------------------------------------------------------+
   | -9          | Less than 4 bytes remaining in the extended data.           |
   +-------------+-------------------------------------------------------------+
   | -10         | Less than 8 bytes remaining in the extended data.           |
   +-------------+-------------------------------------------------------------+
   | -11         | The buffer is too small to store the extended event data.   |
   +-------------+-------------------------------------------------------------+
   | -12         | No byte remaining in the data of the extended event.        |
   +-------------+-------------------------------------------------------------+

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
