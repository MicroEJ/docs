ECOM
====

Error Messages
--------------

When an exception is thrown by the implementation of the ECOM API, the
error message

``ECOM-1.1:E=<messageId>``

is issued, where ``<messageId>`` meaning is defined in the next table:

.. tabularcolumns:: |p{2cm}|L|
.. table:: ECOM Error Messages

   +-------------+--------------------------------------------------------+
   | Message ID  | Description                                            |
   +=============+========================================================+
   | 1           | The connection has been closed. No more action can be  |
   |             | done on this connection.                               |
   +-------------+--------------------------------------------------------+
   | 2           | The connection has already been closed.                |
   +-------------+--------------------------------------------------------+
   | 3           | The connection description is invalid. The connection  |
   |             | cannot be opened.                                      |
   +-------------+--------------------------------------------------------+
   | 4           | The connection stream has already been opened. Only    |
   |             | one stream per kind of stream (input or output stream) |
   |             | can be opened at the same time.                        |
   +-------------+--------------------------------------------------------+
   | 5           | Too many connections have been opened at the same      |
   |             | time. The platform is not able to open a new one. Try  |
   |             | to close useless connections before trying to open the |
   |             | new connection.                                        |
   +-------------+--------------------------------------------------------+


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
