.. _managedc.communication:

Communication Between Java and Managed C
========================================

The MicroEJ Core Engine allows to communicate between Java and Managed C. Java static methods can be used from Managed C code and vice-versa.

.. _managedc.communication.java_to_managedc:

Calling Java from Managed C
---------------------------

The MicroEJ Core Engine allows to expose Java static methods to Managed C. Functions has to be declared as `extern` in the Managed C 
source code. Here is a C source code example:

.. code:: c

   /* Extern functions implemented in Java -----*/
   extern void delay(int ms);

Link between Managed C function declaration and Java static methods can be done statically using the following C macro definition:

.. code:: c

   #define __IMPORT(class, method) \
    __attribute__((__import_module__(#class), __import_name__(#method)))

* ``class``: Java fully qualified name of the class containing the Java static method.
* ``method``: Java static method name.

Here is an example:

- Java source code (``ManagedCUtil.java``):

   .. code:: java

      package com.microej.managedc;

      public class ManagedCUtil {

         public static void delay(int ms) {
            try {
               Thread.sleep(ms);
            } catch (InterruptedException e) {
               e.printStackTrace();
            }
         }

      }

- C source code (``my_app.c``):

   .. code:: c

      #define __IMPORT(class, method) \
      __attribute__((__import_module__(class), __import_name__(method)))

      /* Extern functions implemented in Java -----*/
      extern void delay(int ms) __IMPORT("com.microej.managedc.ManagedCUtils" ,"delay");

.. note:: 

   ``class`` C macro parameter can be set as empty string (``""``). In that case, Java type resolution will look at the 
   ``@ManagedCModule`` declarations in Java source code to find the Java class containing the Java static method. 
   A SOAR error will be triggered if no Java method found.

Link between Managed C function declaration and Java static methods can also be done dynamically using ``-Wl,--allow-undefined`` 
C compiler option (see :ref:`managedc.compilation.command_line_options` ). No need to declare and use ``__IMPORT(class, method)`` C macro 
in that case. Java type resolution will look at the ``@ManagedCModule`` declarations in Java source code to find the Java class 
containing the Java static method. A SOAR error will be triggered if no Java method found.

.. _managedc.communication.managedc_to_java:

Calling Managed C from Java
---------------------------

The MicroEJ Core Engine allows to expose C functions to Java. C functions has to be declared as global function (intern C function 
using ``static`` C keyword will not be exposed). On Java side, methods has to use ``@ManagedCFunction`` annotation and declared as 
`static native`.

Here is an example:

- C source code (`my_app.c`):

   .. code:: c

      int add(int a, int b) {
         return a + b;
      }

- Java source code (``ManagedCUtil.java``):

   .. code:: java

      package com.microej.managedc;

      import com.microej.managedc.ManagedCFunction;
      import com.microej.managedc.ManagedCMemory;

      @ManagedCModule("my_app.mc")
      public class ManagedCUtil {

         @ManagedCFunction
         public static native int add(int a, int b);

      }


..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
