.. _managedc.compilation:

Compilation
===========

MicroEJ supports Managed C through WebAssembly, so Managed C code needs to be compiled to WebAssembly first. 

You can use any toolchain that compiles C code to WebAssembly, but the main supported tool is ``wasi-sdk``.

Please download the `wasi-sdk 20 or higher <https://github.com/WebAssembly/wasi-sdk/releases>`__ and extract it at a location of your choice on your machine. Add the ``bin`` directory of the previously extracted ``wasi-sdk`` to the ``PATH`` environment variable of your machine.

Compile a simple C file
-----------------------

Let's assume we have a file named ``my_app.c`` in the folder ``src/main/c``.

In the terminal, navigate to the ``src/main/c`` directory and execute the following command:

.. code:: console

    clang -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -nostdlib -mcpu=mvp -O3 my_app.c -o my_app.mc

.. _managedc.compilation.command_line_options:

Command Line Options
--------------------

For a comprehensive understanding of command line options, please consult the official documentation for `clang <https://clang.llvm.org/docs/ClangCommandLineReference.html>`_ and `wasm-ld <https://lld.llvm.org/WebAssembly.html>`_. 

Here are some useful options:

* ``-nostdlib``: Omits the standard library.
* ``-Wl,--no-entry``: Specifies no entry point for the WebAssembly module.
* ``-Wl,--export=foo``: Exports a symbol named 'foo'.
* ``-Wl,--export-all``: Exports all symbols.
* ``-Wl,--allow-undefined``: Allow undefined symbols.
* ``-Wl,--global-base=n``: Sets the global base to 'n'.
* ``-z stack-size=n``: Adjusts the stack size to 'n'.
* ``-mcpu=mvp``: Restrict generation to WebAssembly MVP specification.


..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
