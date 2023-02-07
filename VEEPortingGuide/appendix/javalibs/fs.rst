FS
==

Error Messages
--------------

When an exception is thrown by the implementation of the FS API, the
error message

``FS:E=<messageId>``

is issued, where ``<messageId>`` meaning is defined in the next table:

.. table:: File System Error Messages

   +-------------+--------------------------------------------------------+
   | Message ID  | Description                                            |
   +=============+========================================================+
   | -1          | End of File (EOF).                                     |
   +-------------+--------------------------------------------------------+
   | -2          | An error occurred during a File System operation.      |
   +-------------+--------------------------------------------------------+
   | -3          | File System not initialized.                           |
   +-------------+--------------------------------------------------------+

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
