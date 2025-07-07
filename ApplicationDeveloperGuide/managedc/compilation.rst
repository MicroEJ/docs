.. _managedc.compilation:

Compiling your Project
========================

MicroEJ supports Managed C through WebAssembly, meaning your Managed C or C++ code must be compiled to WebAssembly first. 

The supported toolchain for this process is `WASI SDK <https://github.com/WebAssembly/wasi-sdk/>`__.

Installing the Toolchain
------------------------

Download the `WASI SDK version 20 or higher <https://github.com/WebAssembly/wasi-sdk/releases>`__ and extract it at the location of your choice on your machine.
This location will be referred to as ``[path_to_wasi_sdk]`` in the rest of this documentation.

.. _managedc.compilation.file:

Compiling a Simple C File
-------------------------

Assuming you have a file named ``my_app.c`` located in the ``src/main/c`` folder, follow these steps:

* Open your terminal and navigate to your project root directory.
* Execute the following command:

   .. code:: console

       [path_to_wasi_sdk]/bin/clang -mcpu=mvp -O3 -c -o src/main/resources/my_app.o src/main/c/my_app.c


The compilation option ``-mcpu=mvp`` ensures that the output adheres to the WebAssembly MVP specification. 
For a detailed explanation of the compiler options, please consult the official documentation for `clang <https://clang.llvm.org/docs/ClangCommandLineReference.html>`_.


.. _managedc.link.module:

Linking a Wasm Module
---------------------

Once the C files are compiled into object files (``.o`` files),
you need to link them to create a Wasm module (``.wasm`` file).

During linking, specify the functions that need to be exposed to the Java application using 
the ``--export=[function_name]`` option for each function. 

For instance, if you have an object file named ``my_app.o`` in the ``src/main/resources`` folder 
and you want to build a Wasm module that exports the C functions ``foo`` and ``bar``, 
run the following command:

.. code:: console

    [path_to_wasi_sdk]/bin/clang -Wl,--no-entry -Wl,--stack-first -z stack-size=4096 -mcpu=mvp -O3 -Wl,--export=foo -Wl,--export=bar -o src/main/resources/my_app.wasm src/main/resources/my_app.o


.. note::

    For convenience, you can store the list of exported functions in an options file.
    Create a file named ``exports.txt`` containing:

    .. code:: console

        --export=foo 
        --export=bar

    You can then reference this file in the command line using the ``-Wl,@exports.txt`` option. 
    
If your module consists of multiple C files, make sure to append all the object files to the command line.

The resulting file, ``my_app.wasm``, will be a linked Wasm module consisting of all content from the object files (functions, globals, constants). 
This module can now be bound to a :ref:`Java @WasmModule <managedc.bind.module>`.

.. _managedc.link.command_line_options:

Linker Options
``````````````

Here are some useful linker options you might need:

* ``-nostdlib``: Omits the standard library. See :ref:`managedc.link.nostdlib` for more details.
* ``-Wl,--no-entry``: Specifies that there is no entry point for the Wasm module.
* ``-Wl,--export=[function_name]``: Exports the symbol named ``function_name``.
* ``-Wl,--allow-undefined``: Allows undefined symbols, which is necessary when the Wasm module references extern symbols defined in the Java code.
* ``-Wl,--stack-first``: Places the stack at the begining of linear memory. Refer to :ref:`managedc.linear.memory.layout` for more information.
* ``-Wl,--initial-memory=n``: Sets the initial size of the linear memory to ``n`` bytes. See :ref:`managedc.linear.memory.size.configuration` for additional details.
* ``-z stack-size=n``: Adjusts the stack size to 'n' bytes. Consult :ref:`managedc.linear.memory.size.stack` for further information.

For an in-depth understanding of the linker options, please refer to the official documentation for `wasm-ld <https://lld.llvm.org/WebAssembly.html>`_. 

Compiling C++ Code
-------------------

The WASI SDK also includes a C++ compiler, ``clang++``, which you can use to compile and link C++ code using similar options.

.. code:: console

    # To compile:
    [path_to_wasi_sdk]/bin/clang++ [...] -fno-exceptions -c -o my_app.o my_app.cc
    # To link:
    [path_to_wasi_sdk]/bin/clang++ [...] -fno-exceptions -o my_app.wasm my_app.o

.. note::
    C++ exceptions are not supported, so you'll need to build your C++ code with the `-fno-exceptions` flag.

.. _managedc.link.nostdlib:

Building Without The Standard Library
-------------------------------------

The ``-nostdlib`` flag is a linker option used to exclude the standard library when building a program. 
It prevents the compiler and linker from automatically linking with the standard system libraries (such as ``libc`` in C or the C++ Standard Library), 
and the :ref:`startup code <managedc.bind.start.function>` that initializes the runtime environment.
This is particularly useful for building a Wasm module that contains only its own code, with all dependencies :ref:`bound to Java methods <managedc.bind.method>`.

..
   | Copyright 2023-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
