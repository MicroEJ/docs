.. _managedc.compilation:

Compilation
===========

MicroEJ supports Managed C through WebAssembly, so Managed C code needs to be compiled to WebAssembly first. 

The supported toolchain for compiling C code to WebAssembly is `WASI SDK <https://github.com/WebAssembly/wasi-sdk/>`__.

Install the Toolchain
---------------------

Download the `WASI SDK version 20 or higher <https://github.com/WebAssembly/wasi-sdk/releases>`__ and extract it at a location of your choice on your machine, named ``[path_to_wasi_sdk]`` in the rest of the documentation.

Compile a simple C file
-----------------------

Let's assume we have a file named ``my_app.c`` in the folder ``src/main/c``.

In the terminal, navigate to the ``src/main/c`` directory and execute the following command:

.. code:: console

    [path_to_wasi_sdk]/bin/clang -mcpu=mvp -O3 -o my_app.o -c my_app.c

.. _managedc.compilation.command_line_options:

Link object file
----------------

Let's assume we have now an object file named ``my_app.o`` in the folder ``src/main/c``.

In the terminal, navigate to the ``src/main/c`` directory and execute the following command:

.. code:: console

    [path_to_wasi_sdk]/bin/clang -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -o my_app.wasm my_appp.o

.. note::
    
    If your module is composed of multiple C files, append all object files to the command line.

The generated file ``my_app.wasm`` is the result of the link of all the content of the object file(s) (functions, globals, constants) in a single WebAssembly module.
This linked WebAssembly module can now be mapped to a :ref:`@ManagedCModule <managedc.communication.managedc_to_java>`.

.. _managedc.link.command_line_options:

Command Line Options
--------------------

For a comprehensive understanding of command line options, please consult the official documentation for `clang <https://clang.llvm.org/docs/ClangCommandLineReference.html>`_ and `wasm-ld <https://lld.llvm.org/WebAssembly.html>`_. 

Here are some useful compilation options:

* ``-mcpu=mvp``: Restrict generation to WebAssembly MVP specification.

Here are some useful link options:

* ``-nostdlib``: Omits the standard library.
* ``-Wl,--no-entry``: Specifies no entry point for the WebAssembly module.
* ``-Wl,--export=foo``: Exports a symbol named 'foo'.
* ``-Wl,--export-all``: Exports all symbols.
* ``-Wl,--allow-undefined``: Allow undefined symbols.
* ``-Wl,--global-base=n``: Sets the global base to 'n'.
* ``-z stack-size=n``: Adjusts the stack size to 'n'.

..
   | Copyright 2023-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
