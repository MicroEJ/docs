.. _managedc.troubleshooting:

Troubleshooting
===============

-----------------------------------------------------------------
SOAR-L ERROR "Unknown classpath entry ...."
-----------------------------------------------------------------

When using the ``ManagedCFunction`` annotation on a Java native methods, ensure there's a corresponding WebAssembly file in the classpath. 

An error in SOAR-L might occur if the WebAssembly file is missing. 

For instance, having a ``factorial`` Java native method requires a ``factorial.wasm`` file at the root of your classpath. 

Failure to do so may result in the following error:

.. code:: console

    soar2-r/do:
       [soar2-r] 1 : SOAR-L ERROR :
       [soar2-r] [M74] - Unknown classpath entry 'factorial.wasm' (managedc module).
       [soar2-r]

-----------------------------------------------------------------
SOAR-L ERROR "Unsupported wasm instruction '...'  ...."
-----------------------------------------------------------------

Not all WebAssembly instructions are supported. 

If your WebAssembly file uses an unsupported instruction, you might encounter a SOAR-L error, for example:

.. code:: console

    soar2-r/do:
       [soar2-r] 1 : SOAR-L ERROR :
     BUILD FAILED
       [soar2-r] [M81] - ManagedC error Unsupported wasm instruction 'i32.lt_s' in 'factorial' function

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
