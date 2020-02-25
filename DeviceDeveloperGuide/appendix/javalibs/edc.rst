EDC
===

Error Messages
--------------

When an exception is thrown by the runtime, the error message

``Generic:E=<messageId>``

is issued, where ``<messageId>`` meaning is defined in the next table:

.. table:: Generic Error Messages

   +-------------+--------------------------------------------------------+
   | Message  ID | Description                                            |
   +=============+========================================================+
   | 1           | Negative offset.                                       |
   +-------------+--------------------------------------------------------+
   | 2           | Negative length.                                       |
   +-------------+--------------------------------------------------------+
   | 3           | Offset + length > object length.                       |
   +-------------+--------------------------------------------------------+

When an exception is thrown by the implementation of the EDC API, the
error message

``EDC-1.2:E=<messageId>``

is issued, where ``<messageId>`` meaning is defined in the next table:

.. table:: EDC Error Messages

   +-------------+--------------------------------------------------------+
   | Message  ID | Description                                            |
   +=============+========================================================+
   | -4          | No native stack found to execute the Java native       |
   |             | method.                                                |
   +-------------+--------------------------------------------------------+
   | -3          | Maximum stack size for a thread has been reached.      |
   |             | Increase the maximum size of the thread stack          |
   |             | parameter.                                             |
   +-------------+--------------------------------------------------------+
   | -2          | No Java stack block could be allocated with the given  |
   |             | size. Increase the Java stack block size.              |
   +-------------+--------------------------------------------------------+
   | -1          | The Java stack space is full. Increase the Java stack  |
   |             | size or the number of Java stack blocks.               |
   +-------------+--------------------------------------------------------+
   | 1           | A closed stream is being written/read.                 |
   +-------------+--------------------------------------------------------+
   | 2           | The operation ``Reader.mark()`` is not supported.      |
   +-------------+--------------------------------------------------------+
   | 3           | ``lock`` is ``null`` in ``Reader(Object lock)``.       |
   +-------------+--------------------------------------------------------+
   | 4           | String index is out of range.                          |
   +-------------+--------------------------------------------------------+
   | 5           | Argument must be a positive number.                    |
   +-------------+--------------------------------------------------------+
   | 6           | Invalid radix used. Must be from                       |
   |             | ``Character.MIN_RADIX`` to ``Character.MAX_RADIX``.    |
   +-------------+--------------------------------------------------------+

Exit Codes
----------

The RTOS task that runs the MicroEJ runtime may end, especially when the
MicroEJ application calls ``System.exit`` method [EDC]. By convention, a
negative value indicates abnormal termination.  

.. table:: MicroEJ Platform exit codes

   +-------------+--------------------------------------------------------+
   | Message  ID | Meaning                                                |
   +=============+========================================================+
   | 0           | The MicroEJ application ended normally.                |
   +-------------+--------------------------------------------------------+
   | -1          | The SOAR and the MicroEJ Platform are not compatible.  |
   +-------------+--------------------------------------------------------+
   | -2          | Incompatible link configuration (``lsc`` file) with    |
   |             | either the SOAR or the MicroEJ Platform.               |
   +-------------+--------------------------------------------------------+
   | -3          | Evaluation version limitations reached: termination of |
   |             | the application.                                       |
   +-------------+--------------------------------------------------------+
   | -5          | Not enough resources to start the very first MicroEJ   |
   |             | thread that executes ``main`` method.                  |
   +-------------+--------------------------------------------------------+
   | -12         | Maximum number of threads reached.                     |
   +-------------+--------------------------------------------------------+
   | -13         | Fail to start the MicroEJ Platform because the         |
   |             | specified MicroEJ heap is too large.                   |
   +-------------+--------------------------------------------------------+
   | -14         | Invalid stack space due to a link placement error.     |
   +-------------+--------------------------------------------------------+
   | -15         | The application has too many static (the requested     |
   |             | static head is too large).                             |
   +-------------+--------------------------------------------------------+
   | -16         | The MicroEJ core engine cannot be restarted.           |
   +-------------+--------------------------------------------------------+

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
