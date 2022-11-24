..  _MicroEJ-Debugger-Proxy:

MicroEJ Debugger Proxy
######################

Principle
=========

The MicroEJ debugger proxy is a Java Debug Wire protocol implementation on top of MicroEJ VEE enabling on board debugging.
It consists of a TCP server implementing the JDWP protocol and acting as a proxy between the debugger and the VEE running on the board.

.. figure:: images/debugger_proxy1.png
   :alt: MicroEJ Development Tools Overview of the Debugger on Simulator
   :align: center

   MicroEJ Development Tools Overview of the Debugger on Simulator


.. note::
   This feature requires Architecture version ``8.0.0`` or higher.

The MicroeEJ debugger proxy only allow a postmortem debug now so it requires among other things a core dump file of a running MicroEJ VEE process.

Generate a coredump file with GDB
=================================

Open a shell terminal and enter the following commands:

.. code-block:: sh

    # instruct the Linux kernel to Dump file-backed private mappings.
    echo 0x37 > /proc/self/coredump_filter
    gdb ./application.out
    # in the gdb console run you program by typing
    r
    # when you want to generate the coredump file suspend you program by typing Ctrl-C
    # and run
    generate-core-file [core dump filename]


Run the MicroEJ Debugger proxy
================================

Open  a shell terminal and run the following command

.. code-block:: sh

    java -Dloader.path=<Path to runtime jars> \
        -Ddebugger.port=<8000> \
        -Ddebugger.out.path=<Path to VEE .out file> \
        -Ddebugger.out.coredump.path=<Path to VEE .out coredump file> \
        -Ddebugger.out.format=<elf> \
        -Ddebugger.out.bigEndianness=<false> \
        -jar jdwp-server-0.0.1-SNAPSHOT-boot.jar


* **debugger.port**: TCP server port, default to 8000
* **debugger.out.path**: path to VEE .out file
* **debugger.out.coredump.path**: path to VEE .out coredump file
* **debugger.out.format**: VEE .out file format, default to elf
*  **debugger.out.bigEndianness**: is the VEE .out file big endian, default to false
* **loader.path**: The path to the platform ``soarModelReader.jar`` and ``vmModelReader.jar`` needs to be provided hear.
  This is a Comma-separated Classpath, such as `lib,${HOME}/app/lib`.
  Earlier entries take precedence, like a regular -classpath on the javac command line. 
  Other runtime jars can be provided using this property.



..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.