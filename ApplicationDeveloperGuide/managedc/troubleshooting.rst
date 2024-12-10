.. _managedc.troubleshooting:

Troubleshooting
===============

-----------------------------------------------------------------
SOAR-L ERROR "Unknown module ..."
-----------------------------------------------------------------

When using the ``@WasmModule`` annotation on a Java class, ensure there's a corresponding Wasm file in the classpath. 

An error in SOAR-L might occur if the Wasm file is missing. 

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M403] - Unknown module 'my_module.wasm' (module is referenced by the annotation '@WasmModule' on the type 'com.mycompany.MyWasmModule').
      [soar2-r]

-----------------------------------------------------------------
SOAR-L ERROR "Unsupported Wasm instruction ..."
-----------------------------------------------------------------

Not all Wasm instructions are supported. 

If your Wasm file uses an unsupported instruction, you might encounter a SOAR-L error, for example:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M401] - Unsupported Wasm instruction: '0xc0' (i32.lt_s) in function 'my_function' in module '/path/to/mymodule.wasm'.

-----------------------------------------------------------------
SOAR-L ERROR "Cannot resolved this import '...'"
-----------------------------------------------------------------

Java methods called from C source code has to follow the right Java method signature convention. An error in 
SOAR-L might occur if the Java method is not found.

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M81] - Wasm error Cannot resolved this import com.mycompany.MyApp.delay(int)void

-----------------------------------------------------------------
SOAR-L ERROR "Cannot find an exported function '...'"
-----------------------------------------------------------------

When using the ``@WasmFunction`` annotation on a Java method, ensure there's a corresponding Wasm function with the right signature in the associated Wasm module.
An error in SOAR-L might occur if no function matching the annotated Java method signature is found.

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M81] - Wasm error cannot find an exported function for com.mycompany.MyApp.factorial(int)int method

-----------------------------------------------------------------
SOAR-L ERROR "'...' is not a byte array"
-----------------------------------------------------------------

When using the ``@WasmMemory`` annotation on a Java static field, ensure that corresponding type is a Java byte array (`byte[]`).

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M81] - Wasm error 'com/mycompany/MyApp.Memory' is not a byte array

-----------------------------------------------------------------
S3 ERROR "Inconsistent Mock implementation:  ...."
-----------------------------------------------------------------

Please be aware that Wasm code is not currently supported in simulations. 

Running code containing Wasm in a simulation will prompt an error similar to this:

.. code:: console

    ERROR: Inconsistent Mock implementation: the type 'com/mycompany/Module' cannot be loaded from the HIL classpath (java.lang.ClassNotFoundException:com.mycompany.Module).


..
   | Copyright 2023-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
