Net
===

Error Messages
--------------

When an exception is thrown by the implementation of the Net API, the
error message

``NET-1.1:E=<messageId>``

is issued, where ``<messageId>`` meaning is defined in the next table:

.. table:: Net Error Messages

   +-------------+--------------------------------------------------------+
   | Message ID  | Description                                            |
   +=============+========================================================+
   | -2          | Permission denied.                                     |
   +-------------+--------------------------------------------------------+
   | -3          | Bad socket file descriptor.                            |
   +-------------+--------------------------------------------------------+
   | -4          | Host is down.                                          |
   +-------------+--------------------------------------------------------+
   | -5          | Network is down.                                       |
   +-------------+--------------------------------------------------------+
   | -6          | Network is unreachable.                                |
   +-------------+--------------------------------------------------------+
   | -7          | Address already in use.                                |
   +-------------+--------------------------------------------------------+
   | -8          | Connection abort.                                      |
   +-------------+--------------------------------------------------------+
   | -9          | Invalid argument.                                      |
   +-------------+--------------------------------------------------------+
   | -10         | Socket option not available.                           |
   +-------------+--------------------------------------------------------+
   | -11         | Socket not connected.                                  |
   +-------------+--------------------------------------------------------+
   | -12         | Unsupported network address family.                    |
   +-------------+--------------------------------------------------------+
   | -13         | Connection refused.                                    |
   +-------------+--------------------------------------------------------+
   | -14         | Socket already connected.                              |
   +-------------+--------------------------------------------------------+
   | -15         | Connection reset by peer.                              |
   +-------------+--------------------------------------------------------+
   | -16         | Message size to be sent is too long.                   |
   +-------------+--------------------------------------------------------+
   | -17         | Broken pipe.                                           |
   +-------------+--------------------------------------------------------+
   | -18         | Connection timed out.                                  |
   +-------------+--------------------------------------------------------+
   | -19         | Not enough free memory.                                |
   +-------------+--------------------------------------------------------+
   | -20         | No route to host.                                      |
   +-------------+--------------------------------------------------------+
   | -21         | Unknown host.                                          |
   +-------------+--------------------------------------------------------+
   | -23         | Native method not implemented.                         |
   +-------------+--------------------------------------------------------+
   | -24         | The blocking request queue is full, and a new request  |
   |             | cannot be added now.                                   |
   +-------------+--------------------------------------------------------+
   | -25         | Network not initialized.                               |
   +-------------+--------------------------------------------------------+
   | -255        | Unknown error.                                         |
   +-------------+--------------------------------------------------------+

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
