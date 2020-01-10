FS
==

Error Messages
--------------

When an exception is thrown by the implementation of the FS API, the
error message

FS:E=<messageId>

is issued, where <messageId> meaning is defined in the next table:

.. table:: File System Error Messages

   +-------------+--------------------------------------------------------+
   | Message  ID | Description                                            |
   +=============+========================================================+
   | -1          | End of File (EOF).                                     |
   +-------------+--------------------------------------------------------+
   | -2          | An error occurred during a File System operation.      |
   +-------------+--------------------------------------------------------+
   | -3          | File System not initialized.                           |
   +-------------+--------------------------------------------------------+
