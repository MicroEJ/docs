.. _managedc.troubleshooting:

Troubleshooting
===============

SOAR Errors
~~~~~~~~~~~~

-----------------------------------------------------------------
SOAR-L ERROR "Unknown module ..."
-----------------------------------------------------------------

When using the ``@WasmModule`` annotation on a Java class, ensure there's a corresponding WebAssembly file in the classpath. 

An error in SOAR-L might occur if the WebAssembly file is missing. 

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M403] - Unknown module 'my_module.wasm' (module is referenced by the annotation '@WasmModule' on the type 'com.mycompany.MyWebAssemblyModule').
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

-------------------------------------
SOAR-L ERROR "Unknown method '...'
-------------------------------------

Java methods called from C source code has to follow the right Java method signature convention. An error in 
SOAR-L might occur if the Java method is not found.

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 4 : SOAR-S ERROR :
      [soar2-r] [M57] - Unknown method 'com.mycompany.MyWebAssemblyModule.delay(long)void' (caused by an import function in the Wasm module 'my_module.wasm' bound to the class 'com.mycompany.MyWebAssemblyModule').

----------------------------------------------------------------------
SOAR-L ERROR "Cannot find the exported function '...' bound to ..."
----------------------------------------------------------------------

When using the ``@WasmFunction`` annotation on a Java method, ensure there's a corresponding WebAssembly function with the right signature in the associated WebAssembly module.
An error in SOAR-L might occur if no function matching the annotated Java method signature is found.

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M407] - Cannot find the exported function 'factorial' bound to the method 'com.mycompany.MyApp.factorial(int)int'.

-----------------------------------------------------------------
SOAR-L ERROR "'...' is not a byte array"
-----------------------------------------------------------------

When using the ``@WasmMemory`` annotation on a Java static field, ensure that corresponding type is a Java byte array (`byte[]`).

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
      [soar2-r] 1 : SOAR-L ERROR :
      [soar2-r] [M81] - WASM: 'com/mycompany/MyApp.Memory' is not a byte array

-----------------------------------------------------------------
S3 ERROR "Inconsistent Mock implementation:  ...."
-----------------------------------------------------------------

Please be aware that Managed C code is not currently supported in simulations. 

Running code containing Managed C in a simulation will prompt an error similar to this:

.. code:: console

    ERROR: Inconsistent Mock implementation: the type 'com/mycompany/Module' cannot be loaded from the HIL classpath (java.lang.ClassNotFoundException:com.mycompany.Module).

Runtime Errors
~~~~~~~~~~~~~~

-----------------------------
java.lang.AssertionError
-----------------------------

If you encounter a stack trace like the following, you are executing an `unreachable instruction <https://www.w3.org/TR/wasm-core-1/#syntax-instr-control>`_.

.. code:: console

  Exception in thread "main" java.lang.AssertionError
        at com.mycompany.myapplication.TestUnreachable.wasm:sync:foo(Unknown Source)
        at com.mycompany.myapplication.TestUnreachable.foo(Unknown Source)
        at com.mycompany.myapplication.TestUnreachable.main(TestUnreachable.java:11)
        at java.lang.MainThread.run(Thread.java:856)
        at java.lang.Thread.runWrapper(Thread.java:465)

-----------------------------------------------------------------------
java.lang.ArrayIndexOutOfBoundsException when using a pointer
-----------------------------------------------------------------------

If you encounter a stack trace like the following, you are trying to access an address outside of the linear memory, which results in an out-of-bounds exception.

.. code:: console

  Exception in thread "main" java.lang.ArrayIndexOutOfBoundsException
          at com.mycompany.myapplication.TestOutOfBounds.wasm:sync:oob(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.oob(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.main(TestOutOfBounds.java:11)
          at java.lang.MainThread.run(Thread.java:856)
          at java.lang.Thread.runWrapper(Thread.java:465)

-----------------------------------------------------------------
java.lang.ArrayIndexOutOfBoundsException in malloc
-----------------------------------------------------------------

If you encounter a stack trace like the following, you have likely reached the upper bound of linear memory. 
The ``dlmalloc`` function attempted to expand memory using ``memory.grow`` but accessed memory that was not allocated, resulting in an out-of-bounds exception.

.. code:: console

  Exception in thread "main" java.lang.ArrayIndexOutOfBoundsException
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$dlmalloc(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$malloc(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$allocate_too_much_memory(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:sync:call(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.call(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.main(TestOutOfBounds.java:23)
          at java.lang.MainThread.run(Thread.java:856)
          at java.lang.Thread.runWrapper(Thread.java:465)

------------------------------------------------------------------------
Unexpected java.lang.ArrayIndexOutOfBoundsException in call stack trace
------------------------------------------------------------------------

If you encounter a stack trace like the following, you have likely reached the lower bound of the linear memory.
The code execution stops while attempting to load or store data in the stack due to a computed negative unsigned offset.

.. code:: console

  Exception in thread "main" java.lang.ArrayIndexOutOfBoundsException
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$recursiveCall0(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$recursiveCall0(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$recursiveCall0(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$recursiveCall0(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$recursiveCall0(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$recursiveCall0(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$recursiveCall0(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$recursiveCall0(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$recursiveCall0(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:$recursiveCall0(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.wasm:sync:recursiveCall(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.recursiveCall(Unknown Source)
          at com.mycompany.myapplication.TestOutOfBounds.main(TestOutOfBounds.java:34)
          at java.lang.MainThread.run(Thread.java:856)
          at java.lang.Thread.runWrapper(Thread.java:465)


..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
