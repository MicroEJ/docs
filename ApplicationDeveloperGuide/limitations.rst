.. _limitations:

Limitations
===========

The following table lists the limitations of MicroEJ Architectures version ``7.14.0`` or higher, for both Evaluation and Production usage.
Please consult :ref:`architecture_changelog` for limitations changes on former versions.

.. note::
 
   The term `unlimited` means there is no Architecture specific limitation. However, there may be limitations driven by device memory layout.   
   Please refer to Platform specific documentation to get the memory mapping of :ref:`MicroEJ Core Engine sections <core_engine_link>`.


.. list-table:: Architecture Limitations
   :widths: 60 20 20
   :header-rows: 1

   * - Item
     - EVAL
     - PROD
   * - [Mono-Sandbox] Number of concrete types [1]_
     - 8192
     - 8192
   * - [Multi-Sandbox] Number of concrete types per context [1]_
     - 4096
     - 4096
   * - Number of abstract classes and interfaces
     - unlimited
     - unlimited
   * - Class or Interface hierarchy depth
     - 127
     - 127
   * - Number of methods
     - unlimited
     - unlimited
   * - Method size in bytes
     - 65536
     - 65536
   * - Numbers of exception handlers per method
     - 63
     - 63
   * - Number of parameters for an SNI method
     - 15
     - 15
   * - Number of instance fields [2]_ (Base type)
     - 4096
     - 4096
   * - Number of instance fields [2]_ (References)
     - 31
     - 31
   * - Number of static fields (boolean + byte)
     - 65536
     - 65536
   * - Number of static fields (short + char)
     - 65536
     - 65536
   * - Number of static fields (int + float)
     - 65536
     - 65536
   * - Number of static fields (long + double)
     - 65536
     - 65536
   * - Number of static fields (References)
     - 65536
     - 65536
   * - Number of threads
     - 63
     - 63
   * - Number of held monitors [3]_
     - 63
     - 63
   * - Time limit
     - 60 minutes
     - unlimited
   * - Number of methods and constructors calls
     - 500000000
     - unlimited
   * - Number of Java heap Garbage Collection
     - 3000 [4]_
     - unlimited


.. [1]
   Concrete types are classes and arrays that can be instantiated.
   
.. [2]
   All instance fields declared in the class and its super classes.

.. [3]
   The maximum number of different monitors that can be held by one thread at any
   time is defined by the :ref:`maximum number of monitors per thread Application option <option_maximum_number_of_monitors_per_thread>`.

.. [4]
   The Java heap Garbage Collection limit may throw unexpected cascading `java.lang.OutOfMemoryError`_ exceptions before the MicroEJ Core Engine exits.

.. _java.lang.OutOfMemoryError: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/OutOfMemoryError.html

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
