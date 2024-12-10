.. _managedc.communication:

Communication Between Java and Wasm
===================================

The Core Engine allows to communicate between Java and Wasm. Java static methods can be used from Wasm code and vice-versa.

.. _managedc.communication.java_to_managedc:

Calling Java from Wasm
----------------------

The Core Engine allows to expose Java static methods to Wasm. Functions has to be declared as ``extern`` in the Wasm 
source code. Here is a C source code example:

.. code:: c

   /* Extern functions implemented in Java -----*/
   extern void delay(int ms);

Link between Wasm function declaration and Java static methods can be done explicitly using the following C macro definition:

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

   Java static methods called by Wasm can only use Java base types ``int``, ``long``, ``float``, ``double`` as parameters and return types. Here is a matching table:
   
   .. tabularcolumns:: |p{2.5cm}|p{4cm}|p{2.7cm}|p{2.5cm}|p{2.7cm}|

   .. table:: Wasm Types / Java Type matching

      +------------------------+-----------------+ 
      | Wasm Type              | Java Type       |
      +========================+=================+
      | int (32 bit)           | int (32 bit)    |
      +------------------------+-----------------+
      | long long int (64 bit) | long (64 bit)   |
      +------------------------+-----------------+
      | float (32 bit)         | float (32 bit)  |
      +------------------------+-----------------+
      | double (64 bit)        | double (64 bit) |
      +------------------------+-----------------+

   A SOAR error will be triggered in case of Wasm function parameter(s) and return types do not matched excatly the same Java method parameter(s) and return types.  

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


Link between Wasm function declaration and Java static methods can also be done implicitly using ``-Wl,--allow-undefined`` 
C compiler option (see :ref:`managedc.compilation.command_line_options` ). No need to declare and use ``__IMPORT(class, method)`` C macro 
in that case.  Java static method is searched in the Java class which refers to the current Wasm module
containing the Java static method. A SOAR error will be triggered if no Java method found.

.. _managedc.communication.managedc_to_java:

Calling Wasm from Java
----------------------

The Core Engine allows to expose C functions to Java. C functions has to be declared as global function (intern C function 
using ``static`` C keyword will not be exposed). 

On Java side, use ``@WasmModule`` annotation with Wasm compiled file path passed as parameter on the Java class. This 
declaration will link a Java class to Wasm module. File path put as annotation parameter has to follow 
`Java resources naming convention <https://docs.oracle.com/javase/7/docs/technotes/guides/lang/resources.html#res_name_context>`__ .

.. note:: 
   Wasm compiled files are seen as resources and has to be available in the Java classpath.

Use ``@WasmFunction`` annotation to link a Java method to a Wasm module function. The Java method has to be declared as `static native` and only use 
``int``, ``long``, ``float`` or ``double`` Java base type as method parameters or return types.
The annotated Java native method signature must match the Wasm function signature. 

Here is an example:

- C source code (``my_app.c``):

   .. code:: c

      int add(int a, int b) {
         return a + b;
      }

- Java source code (``MyApp.java``):

   .. code:: java

      package com.mycompany;

      import com.microej.managedc.WasmFunction;
      import com.microej.managedc.WasmModule;

      @WasmModule("my_app")
      public class MyApp {

         public static void main(String[] args) {
            int a = 1;
            int b = 2;
            // Call and return result of the "add" Wasm function
            System.out.println(a + " + " + b + " = "+ add(a, b));
         }

         @WasmFunction
         public static native int add(int a, int b);

      }

.. note:: 

   A SOAR error will be triggered if no Java method or Wasm function is found (see :ref:`managedc.troubleshooting`).

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
            // Call and return result of the "add" Wasm function
            System.out.println(a + " + " + b + " = "+ myWasmAdd(a, b));
         }

         @WasmFunction("add")
         public static native int myWasmAdd(int a, int b);
      }

   .. code-block:: c
      :emphasize-lines: 1

      int add(int a, int b) {
         return a + b;
      }

.. _managedc.communication.managedc_memory:

Manipulate Wasm Memory from Java
--------------------------------

The Core Engine allows to expose Wasm memory to Java. A Wasm module contains 
at most one memory. This Wasm module memory is automatically generated by the C compiler 
according to C source code and C compiler options. On Java side, Wasm module memory can be seen by
using ``@WasmMemory`` annotation on a Java static byte array field declaration (mapping automatically 
done by the :ref:`soar`).

Wasm module memory is zero-initialiazed (once) when the :ref:`soar_clinit` of the Java class annotated with ``@WasmModule`` is executed.

.. note:: 
   A SOAR error will occurred if ``@WasmMemory`` is not strictly followed by a Java static byte array declaration (see :ref:`managedc.troubleshooting`).

Here is a Java example:

.. code:: java

   package com.microej.managedc;

   import com.microej.managedc.WasmFunction;
   import com.microej.managedc.WasmMemory;

   @WasmModule("my_app")
   public class WasmUtil {

      ...

      @WasmMemory
      private static byte[] Memory;

      ...
   }


Here is a full C/Java example manipulating Wasm module memory in Java:

- C source code (``my_app.c``):

   .. code:: c

      /* Extern function implemented in Java -----*/
      extern void printWasmMemoryValues(int* ptr);

      /* Global variable -------------------------*/
      int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

      /* Wasm function called by Java -------*/
      void app_main() {
         printWasmMemoryValues(&array[0], sizeof(array));
      }

- Java source code (``MyApp.java``):

   .. code:: java

      package com.mycompany;

      import com.microej.managedc.WasmFunction;
      import com.microej.managedc.WasmMemory;
      import com.microej.managedc.WasmModule;

      @WasmModule("my_app")
      public class MyApp {

         public static void main(String[] args) {
            // Call Wasm entry point
            app_main();
         }

         @WasmMemory
         private static byte[] Memory;

         /**
         * Wasm entry point
         */
         @WasmFunction
         public static native void app_main();

         /**
         * Method call from Wasm which print Wasm Memory values.
         * @param ptr index on the Wasm memory
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

      Wasm Memory values from 1024 to 1034:
      1, 2, 3, 4, 5, 6, 7, 8, 9, 10

Multi-Sandboxed Context
-----------------------

Wasm modules and functions can be called in a Multi-Sandboxed context. Use of ``static native`` Java declaration is allowed in that case.

..
   | Copyright 2023-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
