.. _managedc.communication:

Communication Between Java and Managed C
========================================

The Core Engine allows to communicate between Java and Managed C using direct calls between Java methods and Managed C functions. 
Also, the Java code can directly access the Managed C linear memory through a Java ``byte`` array.

Principle
---------

The following figure illustrates the link between a Java method and a C function with a first code example.
Basically, a Java static method declared ``native`` can be mapped to a Managed C function.
Conversely, a Managed C function declared ``extern`` can be mapped to a Java static method.

.. figure:: ../images/managedc-communication-example.png
   :scale: 70%
   :align: center

The next figure illustrates the call stack of the Core Engine main thread:

.. figure:: ../images/managedc-communication-callstack.png
   :scale: 70%
   :align: center

You can notice that from Core Engine execution point of view, there is no distinction between Java methods and C functions.
The execution of the main entry point produces the following stack trace:

.. code:: console

   Exception in thread "main" java.lang.RuntimeException: Core Engine Stack Trace
      [...]
      at java.lang.RuntimeException.<init>(RuntimeException.java:18)
      at example.JavaCode.method2(JavaCode.java:13)
      at example.JavaCode.method1(Unknown Source)
      at example.JavaCode.main(JavaCode.java:26)
      at java.lang.MainThread.run(Thread.java:856)
      at java.lang.Thread.runWrapper(Thread.java:465)
      [...]

The line ``example.JavaCode.method1`` represents the execution of the C function named ``function1``.

.. note::
   
   The Core Engine prints ``Unknown Source`` because the retrieval of line numbers in C files is no yet available.

.. _managedc.communication.java_to_managedc:

Calling Java from Managed C
---------------------------

The Core Engine allows to expose Java static methods to Managed C. Functions have to be declared as ``extern`` in the Managed C 
source code. Here is a C source code example:

.. code:: c

   /* Extern functions implemented in Java -----*/
   extern void delay(int ms);

Link between Managed C function declaration and Java static methods can be done explicitly using the following C macro definition:

.. code:: c

   #define __IMPORT(class, method) \
    __attribute__((__import_module__(class), __import_name__(method)))

* ``class``: 

  * Java `fully qualified name <https://docs.oracle.com/javase/specs/jls/se11/html/jls-6.html#jls-6.7>`__ of the class containing the Java static method (e.g: ``com.mycompany.MyApp``).
  * An empty string (``""``) or ``"env"``. In that case, Java static method is searched in the current annotated ``@WasmModule`` Java class.

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

   Java annotation ``@WasmModule("my_app")`` should be put some where, in this class or in another class.

Here is an example showing how to write Java and C source code when the C macro parameter ``class`` is an empty string:

- Java source code (``MyApp.java``): same as previous example

   .. code:: java

      package com.mycompany;

      @WasmModule("my_app")
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


Link between Managed C function declaration and Java static methods can also be done implicitly using ``-Wl,--allow-undefined`` 
C compiler option (see :ref:`managedc.compilation.command_line_options` ). No need to declare and use ``__IMPORT(class, method)`` C macro 
in that case.  Java static method is searched in the Java class which refers to the current Managed C module
containing the Java static method. A SOAR error will be triggered if no Java method found.

.. _managedc.communication.managedc_to_java:

Calling Managed C from Java
---------------------------

The Core Engine allows to expose C functions to Java. C functions has to be declared as global function (intern C function 
using ``static`` C keyword will not be exposed). 

On Java side, use ``@WasmModule`` annotation with Managed C compiled file path passed as parameter on the Java class. This 
declaration will link a Java class to Managed C module. File path put as annotation parameter has to follow 
`Java resources naming convention <https://docs.oracle.com/javase/7/docs/technotes/guides/lang/resources.html#res_name_context>`__ .

.. note:: 
   Managed C compiled files are seen as resources and has to be available in the Java classpath.

Use ``@WasmFunction`` annotation to link a Java method to a Managed C module function. The Java method has to be declared as `static native synchronized` and only use 
``int``, ``long``, ``float`` or ``double`` Java base type as method parameters or return types.
The annotated Java native method signature must match the Managed C function signature. 

Here is an example:

- C source code (``my_app.c``):

   .. code:: c

      int add(int a, int b) {
         return a + b;
      }

- Java source code (``MyApp.java``):

   .. code:: java

      package com.mycompany;

      import ej.wasm.WasmFunction;
      import ej.wasm.WasmModule;

      @WasmModule("my_app")
      public class MyApp {

         public static void main(String[] args) {
            int a = 1;
            int b = 2;
            // Call and return result of the "add" Managed C function
            System.out.println(a + " + " + b + " = "+ add(a, b));
         }

         @WasmFunction
         public static native synchronized int add(int a, int b);

      }

.. note:: 

   A SOAR error will be triggered if no Java method or Managed C function is found (see :ref:`managedc.troubleshooting`).

You should see the following output when launching the Java application:

   .. code:: console

          1 + 2 = 3

.. note:: 

   You can give the Java method a different name than the C function.
   In that case, you must provide the name of the corresponding C function as a parameter in the ``@WasmFunction`` annotation.
   This is especially useful if you want to write a Java method in camel case while mapping it to a C function written in snake case.

   .. code-block:: java
      :emphasize-lines: 11,12

      @WasmModule("my_app")
      public class Main {

         public static void main(String[] args) {
            int a = 1;
            int b = 2;
            // Call and return result of the "add" Managed C function
            System.out.println(a + " + " + b + " = "+ myManagedCAdd(a, b));
         }

         @WasmFunction("add")
         public static native synchronized int myManagedCAdd(int a, int b);
      }

   .. code-block:: c
      :emphasize-lines: 1

      int add(int a, int b) {
         return a + b;
      }

.. _managedc.communication.managedc_memory:

Manipulate Managed C Memory from Java
-------------------------------------

The Core Engine allows to expose Managed C memory to Java. A Managed C module contains 
at most one memory. This Managed C module memory is automatically generated by the C compiler 
according to C source code and C compiler options. On Java side, Managed C module memory can be seen by
using ``@WasmMemory`` annotation on a Java static byte array field declaration (mapping automatically 
done by the :ref:`soar`).

Managed C module memory is zero-initialiazed (once) when the :ref:`soar_clinit` of the Java class annotated with ``@WasmMemory`` is executed.

.. note:: 
   A SOAR error will occurred if ``@WasmMemory`` is not strictly followed by a Java static byte array declaration (see :ref:`managedc.troubleshooting`).

To use the annotation ``@WasmMemory``, create the file ``WasmMemory.java`` in ``src/main/java/com/microej/wasm`` with the following content:

.. code:: java

   package ej.wasm;

   import java.lang.annotation.ElementType;
   import java.lang.annotation.Target;

   @Target(ElementType.FIELD)
   public @interface WasmMemory {
      String value() default "";
   }


Here is a Java example:

.. code:: java

   package com.mycompany;
   
   import ej.wasm.WasmFunction;
   import ej.wasm.WasmMemory;

   @WasmModule("my_app")
   public class MyApp {

      ...

      @WasmMemory
      private static byte[] Memory;

      ...
   }


Here is a full C/Java example manipulating Managed C module memory in Java:

- C source code (``my_app.c``):

   .. code:: c

      typedef unsigned char uint8_t;
      /* Extern function implemented in Java -----*/
      extern void printWasmMemoryValues(uint8_t* ptr, int size);

      /* Global variable -------------------------*/
      uint8_t array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

      /* Managed C function called by Java -------*/
      void app_main() {
         printManagedCMemoryValues(&array[0], sizeof(array));
      }

- Java source code (``MyApp.java``):

   .. code:: java

      package com.mycompany;

      import ej.wasm.WasmFunction;
      import ej.wasm.WasmMemory;
      import ej.wasm.WasmModule;

      @WasmModule("my_app")
      public class MyApp {

         public static void main(String[] args) {
            // Call Managed C entry point
            app_main();
         }

         @WasmMemory
         private static byte[] Memory;

         /**
         * Managed C entry point
         */
         @WasmFunction
         public static native synchronized void app_main();

         /**
         * Method call from Managed C which print Managed C Memory values.
         * @param ptr index on the Managed C memory
         * @param length memory length to print
         */
          public static void printWasmMemoryValues(int ptr, int length) {
              System.out.println("Wasm Memory values from " + ptr + " to " + (ptr + length) + ":");
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
