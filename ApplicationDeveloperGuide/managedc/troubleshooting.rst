.. _managedc.troubleshooting:

Troubleshooting
===============

-----------------------------------------------------------------
SOAR-L ERROR "Unknown module ..."
-----------------------------------------------------------------

When using the ``@ManagedCModule`` annotation on a Java class, ensure there's a corresponding WebAssembly file in the classpath. 

An error in SOAR-L might occur if the WebAssembly file is missing. 

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M403] - Unknown module 'my_module.wasm' (module is referenced by the annotation '@ManagedCModule' on the type 'com.mycompany.MyWebAssemblyModule').
      [soar2-r]

-----------------------------------------------------------------
SOAR-L ERROR "Unsupported WebAssembly instruction ..."
-----------------------------------------------------------------

Not all WebAssembly instructions are supported. 

If your WebAssembly file uses an unsupported instruction, you might encounter a SOAR-L error, for example:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M401] - Unsupported WebAssembly instruction: '0xc0' (i32.lt_s) in function 'my_function' in module '/path/to/mymodule.wasm'.

-----------------------------------------------------------------
SOAR-L ERROR "Cannot resolved this import '...'"
-----------------------------------------------------------------

Java methods called from C source code has to follow the right Java method signature convention. An error in 
SOAR-L might occur if the Java method is not found.

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M81] - ManagedC error Cannot resolved this import com.mycompany.MyApp.delay(int)void

-----------------------------------------------------------------
SOAR-L ERROR "Cannot find an exported function '...'"
-----------------------------------------------------------------

When using the ``@ManagedCFunction`` annotation on a Java method, ensure there's a corresponding WebAssembly function with the right signature in the associated WebAssembly module.
An error in SOAR-L might occur if no function matching the annotated Java method signature is found.

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M81] - ManagedC error cannot find an exported function for com.mycompany.MyApp.factorial(int)int method

-----------------------------------------------------------------
SOAR-L ERROR "'...' is not a byte array"
-----------------------------------------------------------------

When using the ``@ManagedCMemory`` annotation on a Java static field, ensure that corresponding type is a Java byte array (`byte[]`).

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M81] - ManagedC error 'com/mycompany/MyApp.Memory' is not a byte array

-----------------------------------------------------------------
S3 ERROR "Inconsistent Mock implementation:  ...."
-----------------------------------------------------------------

Please be aware that Managed C code is not currently supported in simulations. 

Running code containing Managed C in a simulation will prompt an error similar to this:

.. code:: console

    ERROR: Inconsistent Mock implementation: the type 'com/mycompany/Module' cannot be loaded from the HIL classpath (java.lang.ClassNotFoundException:com.mycompany.Module).


..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
