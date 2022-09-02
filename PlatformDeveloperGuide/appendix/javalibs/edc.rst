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

is issued, where ``<messageId>`` meaning is defined in the following table:

.. list-table:: EDC Error Messages
   :widths: 1 10
   :header-rows: 1

   * - Message ID
     - Description
   * - -4
     - No native stack found to execute the Java native method.
   * - -3
     - Maximum stack size for a thread has been reached. Increase the maximum size of the thread stack parameter.
   * - -2
     - No Java stack block could be allocated with the given size. Increase the Java stack block size.
   * - -1
     - The Java stack space is full. Increase the Java stack size or the number of Java stack blocks.
   * - 1
     - A closed stream is being written/read.
   * - 2 
     - The operation `Reader.mark()`_ is not supported. 
   * - 3
     - ``lock`` is ``null`` in `Reader(Object lock)`_.
   * - 4
     - String index is out of range.
   * - 5
     - Argument must be a positive number.
   * - 6
     - Invalid radix used. Must be from `Character.MIN_RADIX`_ to `Character.MAX_RADIX`_.

.. _Reader.mark(): https://repository.microej.com/javadoc/microej_5.x/apis/java/io/Reader.html#mark-int-
.. _Reader(Object lock): https://repository.microej.com/javadoc/microej_5.x/apis/java/io/Reader.html#Reader-java.lang.Object-
.. _Character.MIN_RADIX: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Character.html#MIN_RADIX
.. _Character.MAX_RADIX: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Character.html#MAX_RADIX

.. _edc_exit_codes:

Exit Codes
----------

The MicroEJ Application can stop its execution by calling the method 
`System.exit()`_. 
To retrieve the appplication exit code (or exit status), use the C function 
``SNI_getExitCode()`` after the end of ``SNI_startVM()`` (see ``sni.h`` 
header file). 
If the MicroEJ Application ended without calling `System.exit()`_ then 
``SNI_getExitCode()`` returns ``0``.

The error codes returned by ``SNI_startVM()`` are defined in the section 
:ref:`core_engine_error_codes`.

.. _System.exit(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#exit-int-

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
