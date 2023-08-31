..  _debugger_proxy:

VEE Debugger Proxy
##################

Principle
=========

The VEE debugger proxy is an implementation of the Java Debug Wire protocol (JDWP) for debugging Applications executed by MICROEJ VEE.
It consists of a TCP server implementing the JDWP protocol and acting as a proxy between the IDE (debugger) and the Executable (debuggee) running on the device.

The debugger proxy allows a postmortem debug from a core dump of a running Executable binary.

.. figure:: images/debugger_proxy1.png
   :alt: Debugger Proxy Principle
   :align: center
   :scale: 70%

   Debugger Proxy Principle


.. note::
   This feature requires Architecture version ``8.0.0`` or higher and only works for Linux and QNX.



Generate a Core Dump File on Linux using GDB
============================================

Open a shell terminal on the device and enter the following commands:

.. code-block:: sh

    # Instruct the Linux kernel to Dump file-backed private mappings.
    echo 0x37 > /proc/self/coredump_filter
    # Start GDB
    gdb ./application.out

The following GDB script can be used to generate a core dump file:

- when the signal ``SIGUSR1`` is received
- or when an out of memory error occurs 
- or when an explicit garbage collection (GC) is done.

You can run the script directly in the GDB console.

.. code-block:: sh

   ## From GBD documentation:
   ## generate-core-file [file]
   ##   Produce a core dump of the inferior process.
   ##   The optional argument file specifies the file name where to put the core dump.
   ##   If not specified, the file name defaults to 'core.pid', where pid is the inferior process ID.

   ## Generate a core dump when the signal SIGUSR1 is received
   catch signal SIGUSR1
   commands 
   silent
   generate-core-file
   cont
   end

   ## Generate a core dump when an out of memory error occurs
   break LLMJVM_on_OutOfMemoryError_thrown
   commands 
   silent
   generate-core-file
   cont
   end

   ## Generate a core dump when an explicit garbage collection (GC) is done
   break LLMJVM_on_Runtime_gc_done
   commands 
   silent
   generate-core-file
   cont
   end

Run the program:

.. code-block:: sh

    # In the GDB console:
    run


A core dump file will be generated once the Executable reach one of the breaking conditions described previously.

.. warning::
    
    The core dump should only be called when the Core Engine task is stopped on one of the specified callbacks or in a native function. 
    Otherwise, the Core Engine dump is not guarranted to be consistent, which may cause the VEE debugger to crash abruptly.

Start the Proxy
===============

Please contact :ref:`our support team <get_support>` to get the VEE Debugger Proxy tool compatible with your Architecture version.

Open a shell terminal on your workstation and run the following command

.. code-block:: sh

    java -Dloader.path=<path to runtime jars> \
        -Ddebugger.port=<8000> \
        -Ddebugger.out.path=<path to the Executable file (``application.out``)> \
        -Ddebugger.out.coredump.path=<path to the core dump file> \
        -Ddebugger.out.format=<elf> \
        -Ddebugger.out.bigEndianness=<false> \
        -jar microej-debugger-proxy.jar


* **debugger.port**: TCP server port, defaults to ``8000``
* **debugger.out.path**: Path to the Executable file (``application.out``)
* **debugger.out.coredump.path**: Path to the core dump file
* **debugger.out.format**: The Executable file format (defaults to ``elf``)
* **debugger.out.bigEndianness**: The Executable file endianness (default to ``false``: little endian)
* **loader.path**: The path to the VEE Port libraries ``soarModelReader.jar`` and ``vmModelReader.jar`` needs to be provided here.
  This option value must be a comma-separated classpath, such as ``[VEEPortDir]/tools/soarModelReader.jar,[VEEPortDir]/tools/vmModelReader.jar`` where ``[VEEPortDir]`` is your VEE Port directory.
  Earlier entries take precedence, like a regular ``-classpath`` on the javac command line. 
  Other runtime jars can be provided using this option.

Open the SDK and run a :ref:`Remote Java Application Launch <debug_on_device>` to debug your code.

..
   | Copyright 2022-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.