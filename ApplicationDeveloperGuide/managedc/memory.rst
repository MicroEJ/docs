.. _managedc.linear.memory:

Configure the Linear Memory
===========================

The WebAssembly specification defines the linear memory as a contiguous, byte-addressable memory region used by Wasm programs to read and write data.
The linear memory is available as an array of bytes (``byte[]``) in the :ref:`the host <managedc.communication.managedc_memory>`.

.. _managedc.linear.memory.layout:

Configure the Linear Memory Layout
----------------------------------

The Wasm linear memory is composed of the following sections:

* **Main Stack**: Used for temporary allocations and to store some local variables. The stack grows downward (toward lower memory addresses).
* **Static Data**: Contains statically linked constants and global variables.
* **Heap**: Used for dynamic memory allocations. The heap grows upward (toward upper memory addresses).

MicroEJ recommends linking a Wasm module using the ``-Wl,--stack-first`` :ref:`linker option <managedc.link.command_line_options>`.

Thus, you will get the following memory layout:

.. figure:: ../images/linear_memory_layout.png
   :scale: 75%
   :align: center

   Wasm Linear Memory Layout

This ensures that both stack overflows and heap overflows trigger an exception when accessing out-of-bounds memory.

.. _managedc.linear.memory.size.configuration:

Configure the Linear Memory Size
--------------------------------

The WebAssembly specification organizes the linear memory in pages, where each page is 64 KB (65,536 bytes).
This page-based structure has been designed for efficient memory allocation and potential growth during runtime for large environments.
However, the minimum page size (64KB) is not suitable for constrained embedded environments, where memory resources are limited.

MicroEJ implementation allocates the linear memory once at module startup and is not dynamically resized.

By default, the size of the linear memory is initialized with the Wasm module initial number of pages.
The Wasm module initial number of pages can be configured using the ``-Wl,--initial-memory=[size_in_bytes]`` :ref:`linker option <managedc.link.command_line_options>`. 
The given size must be a multiple of 64KB, i.e. a number of pages.

The size of the linear memory can be reduced below 64KB if both of the following conditions are met:

* the Wasm module does not embed neither the ``memory.size`` nor the ``memory.grow`` instructions. This is the case if the C code does not transitively calls the ``malloc`` implementation declared in WASI libc.
* the Wasm module exports the ``__heap_base`` global using the ``-Wl,--export=__heap_base`` :ref:`linker option <managedc.link.command_line_options>`.

In this case, the linear memory is initialized to the value of the ``__heap_base`` global, which represents the sum of the stack size and the static data size.

.. _managedc.linear.memory.size.stack:

Configure the Main Stack Size
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, the main stack size is initialized to ``65536``.
You can adjust the linear memory stack size to using the ``-z stack-size=[size_in_bytes]`` :ref:`linker option <managedc.link.command_line_options>`.

Configuration Examples
~~~~~~~~~~~~~~~~~~~~~~

The following Managed C code declares a static array of ``100`` bytes, and does not embed neither the ``memory.size`` nor the ``memory.grow`` instructions.

.. code:: c

    char my_static_data[100];


The C code is compiled with the following options: ``-Wl,--no-entry -nostdlib -Wl,--export-all -Wl,--stack-first``.

The next table shows the impacts of additionnal options on the allocated linear memory size:

.. list-table::
   :widths: 40 10 11 39

   * - **Extra Options**
     - **Required Size**
       
       **(bytes)**
     - **Allocated Size**
       
       **(bytes)**
     - **Comments**
   * - `none`
     - ``65636``
     - ``131072``
     - By default, the main stack size is initialized to ``65536``.
       The required linear memory size is greater than one page, so it is aligned on ``2`` pages.
   * - ``-Wl,--initial-memory=262144``
     - ``262144``
     - ``262144``
     - The linear memory size is set to the Wasm module initial number of pages (``4`` pages).
   * - ``-z stack-size=512``
     - ``612``
     - ``65536``
     - The main stack size is initialized to ``512``, but the Wasm module does not export the ``__heap_base`` symbol.
       The linear memory size is aligned on ``1`` page. 
   * - ``-z stack-size=512 -Wl,--export=__heap_base``
     - ``612``
     - ``612``
     - The linear memory size is set to the value of the ``__heap_base`` global (``512`` bytes of stack + ``100`` bytes of static data).
   