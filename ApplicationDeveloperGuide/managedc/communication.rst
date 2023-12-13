.. _managedc.communication:

Communication Between Java and Managed C
========================================

The MicroEJ Core Engine allows to communicate between Java and Managed C. Java static methods can be used from Managed C code and vice-versa.

.. _managedc.communication.java_to_managedc:

Calling Java from Managed C
---------------------------

The MicroEJ Core Engine allows to expose Java static methods to Managed C. Functions has to be declared as ``extern`` in the Managed C 
source code. Here is a C source code example:

.. code:: c

   /* Extern functions implemented in Java -----*/
   extern void delay(int ms);

Link between Managed C function declaration and Java static methods can be done explicitly using the following C macro definition:

.. code:: c

   #define __IMPORT(class, method) \
    __attribute__((__import_module__(#class), __import_name__(#method)))

* ``class``: 

  * Java `fully qualified name <https://docs.oracle.com/javase/specs/jls/se11/html/jls-6.html#jls-6.7>`__ of the class containing the Java static method (e.g: ``com.mycompany.MyApp``).
  * An empty string (``""``) or ``"env"``. In that case, Java static method is searched in the current annotated ``@ManagedCModule`` Java class.

* ``method``: Java static method name.

.. note:: 
   
   A SOAR error will be triggered if no Java class or method found (see :ref:`managedc.troubleshooting`).

.. note:: 

   Java static methods called by Managed C can only use Java base types ``int``, ``long``, ``float``, ``double`` as parameters and return types. Here is a matching table:
   
   .. tabularcolumns:: |p{2.5cm}|p{4cm}|p{2.7cm}|p{2.5cm}|p{2.7cm}|

   .. table:: Managed C Types / Java Type matching

      +------------------------+-----------------+ 
      | Managed C Type         | Java Type       |
      +========================+=================+
      | int (32 bit)           | int (32 bit)    |
      +------------------------+-----------------+
      | long long int (64 bit) | long (64 bit)   |
      +------------------------+-----------------+
      | float (32 bit)         | float (32 bit)  |
      +------------------------+-----------------+
      | double (64 bit)        | double (64 bit) |
      +------------------------+-----------------+

   A SOAR error will be triggered in case of Managed C function parameter(s) and return types do not matched excatly the same Java method parameter(s) and return types.  

Here is an example showing how to write Java and C source code when C macro parameters ``class`` and ``method`` are specified:

- Java source code (``MyApp.java``):

   .. code:: java

      package com.mycompany;

      public class MyApp {

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
      extern void delay(int ms) __IMPORT("com.mycompany.MyApp" ,"delay");

.. note:: 

   Java annotation ``@ManagedCModule("my_app.mc")`` should be put some where, in this class or in another class.

Here is an example showing how to write Java and C source code when the C macro parameter ``class`` is an empty string:

- Java source code (``MyApp.java``): same as previous example

   .. code:: java

      package com.mycompany;

      @ManagedCModule("my_app.mc")
      public class MyApp {

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
      extern void delay(int ms) __IMPORT("" ,"delay");


Link between Managed C function declaration and Java static methods can also be done dynamically using ``-Wl,--allow-undefined`` 
C compiler option (see :ref:`managedc.compilation.command_line_options` ). No need to declare and use ``__IMPORT(class, method)`` C macro 
in that case. Java type resolution will look at the ``@ManagedCModule`` declarations in Java source code to find the Java class 
containing the Java static method. A SOAR error will be triggered if no Java method found.

.. _managedc.communication.managedc_to_java:

Calling Managed C from Java
---------------------------

The MicroEJ Core Engine allows to expose C functions to Java. C functions has to be declared as global function (intern C function 
using ``static`` C keyword will not be exposed). 

On Java side, use ``@ManagedCModule`` annotation with Managed C compiled file path passed as parameter on the Java class. This 
declaration will link a Java class to Managed C module. File path put as annotation parameter has to follow 
`Java resources naming convention <https://docs.oracle.com/javase/7/docs/technotes/guides/lang/resources.html#res_name_context>`__ .

.. note:: 
   Managed C compiled files are seen as resources and has to be available in the Java classpath.

Use ``@ManagedCFunction`` annotation to link a Java method to a Managed C module function. Java method has to be declared as `static native` and only use 
``int``, ``long``, ``float`` or ``double`` Java base type as method parameters or return types. 

Here is an example:

- C source code (``my_app.c``):

   .. code:: c

      int add(int a, int b) {
         return a + b;
      }

- Java source code (``MyApp.java``):

   .. code:: java

      package com.mycompany;

      import com.microej.managedc.ManagedCFunction;
      import com.microej.managedc.ManagedCModule;

      @ManagedCModule("my_app.mc")
      public class MyApp {

         public static void main(String[] args) {
            int a = 1;
            int b = 2;
            // Call and return result of the "add" Managed C function
            System.out.println(a + " + " + b + " = "+ add(a, b));
         }

         @ManagedCFunction
         public static native int add(int a, int b);

      }

.. note:: 

   A SOAR error will be triggered if no Java method or Managed C function found (see :ref:`managedc.troubleshooting`).

You should see the following output when launching the Java application:

   .. code:: console

          1 + 2 = 3


.. _managedc.communication.managedc_memory:

Manipulate Managed C Memory from Java
-------------------------------------

The MicroEJ Core Engine allows to expose Managed C memory to Java. A Managed C module contains 
one (and only one) memory. This Managed C module memory is automatically generated by the C compiler 
according to C source code and C compiler options. On Java side, Managed C module memory can be seen by
using ``@ManagedCMemory`` annotation on a Java static byte array field declaration. 

.. note:: 
   A SOAR error will occurred if ``@ManagedCMemory`` is not strictly followed by a Java static byte array declaration (see :ref:`managedc.troubleshooting`).

Here is a Java example:

.. code:: java

   package com.microej.managedc;

   import com.microej.managedc.ManagedCFunction;
   import com.microej.managedc.ManagedCMemory;

   @ManagedCModule("my_app.mc")
   public class ManagedCUtil {

      ...

      @ManagedCMemory
      private static byte[] Memory;

      ...
   }


Here is a full C/Java example manipulating Managed C module memory in Java:

- C source code (``my_app.c``):

   .. code:: c

      /* Extern function implemented in Java -----*/
      extern void printManagedCMemoryValues(int* ptr);

      /* Global variable -------------------------*/
      int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

      /* Managed C function called by Java -------*/
      void app_main() {
         printManagedCMemoryValues(&array[0], sizeof(array));
      }

- Java source code (``MyApp.java``):

   .. code:: java

      package com.mycompany;

      import com.microej.managedc.ManagedCFunction;
      import com.microej.managedc.ManagedCMemory;
      import com.microej.managedc.ManagedCModule;

      @ManagedCModule("my_app.mc")
      public class MyApp {

         public static void main(String[] args) {
            // Call Managed C entry point
            app_main();
         }

         @ManagedCMemory
         private static byte[] Memory;

         /**
         * Managed C entry point
         */
         @ManagedCFunction
         public static native void app_main();

         /**
         * Method call from Managed C which print Managed C Memory values.
         * @param ptr index on the Managed C memory
         * @param length memory length to print
         */
         public static void printManagedCMemoryValues(int ptr, int length) {
            System.out.println("Managed C Memory values from " + ptr + " to " + (ptr + length) + ":");
            for (int i = 0; i < length - 1; i++) {
               System.out.print(Memory[ptr + i] + ", ");
            }
            System.out.println(Memory[ptr + (length - 1)]);
         }

      }

You should see the following output when launching the Java application:

   .. code:: console

      Managed C Memory values from 1024 to 1034:
      1, 2, 3, 4, 5, 6, 7, 8, 9, 10

Multi-Sandboxed Context
-----------------------

Managed C modules and functions can be called in a Multi-Sandboxed context. Use of ``static native`` Java declaration is allowed in that case.

..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
