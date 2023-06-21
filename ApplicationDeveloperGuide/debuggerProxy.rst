..  _debugger_proxy:

VEE Debugger Proxy
######################

Principle
=========

The MicroEJ debugger proxy is a Java Debug Wire protocol implementation (JDWP) on top of MicroEJ VEE enabling on board debugging.
It consists of a TCP server implementing the JDWP protocol and acting as a proxy between the IDE (debugger) and the VEE (debuggee) running on the board.
This tool can be used to load and inspect a core dump file generated when a process crashes to get a postmortem view of the VEE state when the crache occurred.

.. figure:: images/debugger_proxy1.png
   :alt: MicroEJ Development Tools Overview of the Debugger on Board
   :align: center

   MicroEJ Development Tools Overview of the Debugger on Board


.. note::
   This feature requires Architecture version ``8.0.0`` or higher.

The MicroeEJ debugger proxy only allows a postmortem debug now so it requires among other things a core dump file of a running MicroEJ VEE process.


Generate a coredump file for MicroEJ VEE Linux using GDB
========================================================

Open a shell terminal and enter the following commands:

.. code-block:: sh

    # Instruct the Linux kernel to Dump file-backed private mappings.
    echo 0x37 > /proc/self/coredump_filter
    # Stard gdb.
    gdb ./application.out

Suppose we want to generate a corefile when the the signal ``SIGUSR1`` is received, or when a out of memory error occurs, or when a garbage collection (GC) is done, enter the following commands:

.. code-block:: sh

   # In the gdb console.
   catch signal SIGUSR1 # catch the SIGUSR1 signal
   commands 
   silent
   generate-core-file [file] # the argument `file` specifies the file name where to put the core dump
   cont
   end

   break LLMJVM_on_OutOfMemoryError_thrown # break in the LLMJVM_on_OutOfMemoryError_thrown, this function is called when an out of memory error occurs
   commands 
   silent
   generate-core-file [file] # the argument `file` specifies the file name where to put the core dump
   cont
   end

   break LLMJVM_on_Runtime_gc_done # break in the LLMJVM_on_Runtime_gc_done function
   commands 
   silent
   generate-core-file [file] # the argument `file` specifies the file name where to put the core dump
   cont
   end

Run the program:

.. code-block:: sh

    # In the gdb console.
    run


A coredump file will be generated automatically when the ``LLMJVM_on_Runtime_gc_done`` function is called or the ``SIGUSR1`` signal is received.
You can also suspend the process and generate the core dump file yourself:

.. code-block:: sh

    # In the gdb console.
    # suspend first the process with Ctrl-C and then generate the core dump file.
    generate-core-file [file] # the argument `file` specifies the file name where to put the core dump


Run the VEE Debugger proxy
==============================

Please contact :ref:`our support team <get_support>` to get the VEE Debugger Proxy program.

Open a shell terminal and run the following command

.. code-block:: sh

    java -Dloader.path=<Path to runtime jars> \
        -Ddebugger.port=<8000> \
        -Ddebugger.out.path=<Path to VEE .out file> \
        -Ddebugger.out.coredump.path=<Path to VEE .out coredump file> \
        -Ddebugger.out.format=<elf> \
        -Ddebugger.out.bigEndianness=<false> \
        -jar microej-debugger-proxy.jar


* **debugger.port**: TCP server port, default to 8000
* **debugger.out.path**: path to VEE .out file
* **debugger.out.coredump.path**: path to VEE .out coredump file
* **debugger.out.format**: VEE .out file format, default to elf
*  **debugger.out.bigEndianness**: VEE .out file big endian, default to false
* **loader.path**: The path to the platform ``soarModelReader.jar`` and ``vmModelReader.jar`` needs to be provided here.
  This is a Comma-separated Classpath, such as `${PLATFORM}/tools/soarModelReader.jar,${PLATFORM}/tools/soarModelReader.jar`.
  Earlier entries take precedence, like a regular -classpath on the javac command line. 
  Other runtime jars can be provided using this property.

Open the MicroEJ SDK and run a :ref:`Remote Java Application Launch <debug_on_device>` to debug your code.

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.