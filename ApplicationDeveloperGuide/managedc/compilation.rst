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
the next step is to link them together to produce a Wasm module (``.wasm`` file).
Use ``clang`` as the linker driver to generate the final ``.wasm`` module. 
It automatically calls ``wasm-ld``, the Wasm linker.

The following options are recommended to ensure the produced ``.wasm`` binary is compatible with MICROEJ VEE:

* ``-Wl,--allow-undefined``: Allows undefined symbols, which is necessary when the Wasm module references extern symbols defined in Java.
* ``-Wl,--stack-first``: Places the stack at the begining of the linear memory. Refer to :ref:`managedc.linear.memory.layout` for more information.
* ``-z stack-size=n``: Adjusts the stack size to 'n' bytes. Consult :ref:`managedc.linear.memory.size.stack` for further information.

For example, if you have the object file ``src/main/resources/my_app.o`` that defines a ``main`` entry point,
the following command will generate a Wasm module including this entry point along with all transitive dependencies from the :ref:`WASI Libc <wasm.wasi>`.
Any unresolved symbols in the object file are expected to be provided by the Java host.

    .. code:: console

        [path_to_wasi_sdk]/bin/clang -Wl,--stack-first -z stack-size=4096 -Wl,--allow-undefined -o src/main/resources/my_app.wasm src/main/resources/my_app.o


When your object file defines a ``main`` function, the linker automatically exports a function named ``_start``. 
This function performs initialization tasks before invoking the user-defined ``main``. 
You must bind the ``_start`` function — not ``main`` — to a Java method.

Additionally, any other functions that should be callable from the Java application must be explicitly exported using the ``-Wl,--export=[function_name]`` linker option (this does not apply to ``main``, which is invoked internally by ``_start``).  

.. note::

    For convenience, you can store the list of exported functions in an options file.
    Create a file named ``exports.txt`` containing:

    .. code:: console

        --export=foo 
        --export=bar

    You can then reference this file in the command line using the ``-Wl,@exports.txt`` option. 

If your module is composed of multiple C files, make sure to append all the object files to the command line.
The resulting file, ``my_app.wasm``, will be a linked Wasm module containing all functions, globals, and constants defined across those object files.

This Wasm module can then be :ref:`bound to a Java class <managedc.bind.module>` for integration with your application.
For additional details and alternative configurations, see the :ref:`managedc.link.command_line_options` section.


.. _managedc.link.command_line_options:

Linker Options
``````````````

Here are some useful linker options you might need:

* ``-nostdlib``: Omits the standard library. See :ref:`managedc.link.nostdlib` for more details.
* ``-Wl,--no-entry``: Specifies that there is no entry point for the Wasm module (required when ``-nostdlib`` is set).
* ``-Wl,--export=[function_name]``: Exports the symbol named ``function_name``.
* ``-Wl,--allow-undefined``: Allows undefined symbols, which is necessary when the Wasm module references extern symbols defined in Java.
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
