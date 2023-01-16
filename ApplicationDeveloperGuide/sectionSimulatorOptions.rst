.. _simulator_options:

Group: Advanced Simulation Options
----------------------------------

When running large applications, the Simulator can abruptly reach a memory limit with the following trace:

.. code-block:: console

   [...] An error message [...]
   "Internal limits reached. Please contact support@microej.com"
   See error log file: /tmp/microej/s3/s3_1616489929186.log


Depending on the error message, one of the following options must be set to increase the size of the memory area which is full.

Option: Objects Heap Size
^^^^^^^^^^^^^^^^^^^^^^^^^

*Error Message*: ``java.lang.OutOfMemoryError`` exception thrown

*Option Name*: ``S3.JavaMemory.HeapSize``

*Default value*: ``4096`` (kilobytes)

*Description*:

This memory area contains any kind of objects (regular, immortal and immutable objects). 
If you get a ``java.lang.OutOfMemoryError`` exception but your Java Heap is not full, most likely you should augment this option.
It must be greater than the sum of :ref:`Java Heap <option_java_heap>` and :ref:`Immortal Heap <option_immortal_heap>`.

Option: System Chars Size
^^^^^^^^^^^^^^^^^^^^^^^^^

*Error Message*: ``Failed to allocate internString.``

*Option Name*: ``S3.JavaMemory.SystemCharsSize``

*Default value*: ``1024`` (kilobytes)

*Description*:

This memory area contains system interned strings. System interned strings are likely allocated by the debugger.
If you get a ``Failed to allocate internString.`` message while debugging an Application, most likely you should augment this option.


Option: Application Chars Size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Error Message*: ``Failed to allocate internString.``

*Option Name*: ``S3.JavaMemory.ApplicationCharsSize``

*Default value*: ``4096`` (kilobytes)

*Description*:

This memory area contains Application interned strings (String literals).
If you get a ``Failed to allocate internString.`` message while the Simulator is starting the Application, most likely you should augment this option.

Option: Methods Size
^^^^^^^^^^^^^^^^^^^^

*Error Message*: ``Failed to allocate method's code.``

*Option Name*: ``S3.JavaMemory.MethodsSize``

*Default value*: ``10000`` (kilobytes)

*Description*:

This memory area contains loaded methods code.


Option: Thread Stack Size
^^^^^^^^^^^^^^^^^^^^^^^^^

*Error Message*: ``The simulator has encountered a stack overflow error while analyzing method [...]``

*Option Name*: ``S3.JavaMemory.ThreadStackSize``
 
*Default value*: ``300`` (kilobytes)

*Description*:

This memory area contains all Application threads stacks.

Option: Icetea Heap End
^^^^^^^^^^^^^^^^^^^^^^^

*Error Message*: ``S3 internal heap is full.``

*Option Name*: ``IceteaRuntimeSupport.S3.HeapEnd``

*Default value*: ``64000000`` (bytes)

*Description*:

This is the overall Simulator memory limit. It includes fixed sizes internal structures and all memory areas.
The value must be greater than the size of the memory areas that can be parameterized above.

Option: Symbol Table Size
^^^^^^^^^^^^^^^^^^^^^^^^^

*Error Message*: ``Symbols table area is full.``

*Option Name*: ``S3.SymbolTable.MaxNbState``

*Default value*: ``500000``

*Description*:
 
This is the number of symbols that can be handled by the internal symbol table (any kind of names: class names, method names, ...).

..
   | Copyright 2022-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
