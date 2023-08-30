GNSS
====

Error Messages
--------------

When an exception is thrown by the implementation of the GNSS API, the
error message

``GNSS-<APIversion>:E=<messageId>``

is issued, where ``<messageId>`` meaning is defined in the next table:

.. table:: GNSS Error Messages

   +-------------+--------------------------------------------------------+
   | Message ID  | Description                                            |
   +=============+========================================================+
   | -1          | Unknown GNSS native error.                             |
   +-------------+--------------------------------------------------------+
   | -2          | An error occurred during data read.                    |
   +-------------+--------------------------------------------------------+
   | -3          | Read data is invalid.                                  |
   +-------------+--------------------------------------------------------+
   | -4          | An operation needing the GNSS engine to be started was |
   |             | attemted with the engine off.                          |
   +-------------+--------------------------------------------------------+

..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
