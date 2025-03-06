.. _sdk6.section.stacktrace.reader.tool:

==================
Stack Trace Reader
==================

Principle
=========

Stack Trace Reader is a MicroEJ tool that reads and decodes the MicroEJ
stack traces. When an exception occurs, the :ref:`Core Engine <core_engine>` prints
the stack trace on the standard output ``System.out``. The class names,
non-required types names(see :ref:`section.classpath.elements.types`),
and method names obtained are encoded with a MicroEJ internal format.
This internal format prevents embedding all class names and
method names in the executable image to save some memory space. The Stack
Trace Reader tool allows you to decode the stack traces by replacing the
internal class names and method names with their real names. It also
retrieves the line numbers in the Application.

Functional Description
======================

The Stack Trace Reader reads the debug information from the fully linked ELF
file (the ELF file that contains the Core Engine, the other
libraries, the BSP, the OS, and the compiled Application). It
prints the decoded stack trace.

When :ref:`Multi-Sandbox capability <multisandbox>` is enabled, 
the Stack Trace Reader can simultaneously decode heterogeneous stack
traces with lines owned by different Sandboxed Applications and the Kernel.
Lines owned by the Kernel can be decoded with the Executable debug information file
(optionally made available by your Kernel provider).


Usage
=====

To decode an Application stack trace, the Stack Trace Reader tool requires the Application Executable file.

In an Application project
^^^^^^^^^^^^^^^^^^^^^^^^^

If you have an Application project and want to decode a stack trace for this Application, you can execute the tool in the project.

.. tip::

    .. collapse:: Click here if you don't have an Application to test yet and want to quickly test the Stack Trace Reader tool.

        If you don't have an Application to test yet, you can create an :ref:`Application project <sdk_6_create_project>` with the following example main class:

        .. code:: java

            package com.mycompany;
            
            public class MyApp {
                public static void main(String[] args) {
                    System.out.println("Hello, World!");
                    new Exception().printStackTrace();
                }
            }

        On successful deployment (by executing the ``runOnDevice`` task), 
        the Application is started on the device and the trace is dumped on the standard output.

        .. code:: console

            VM START
            Hello, World!
            Exception in thread "main" @C:0x8070c30@
                at @C:0x8070c60@.@M:0x8075850:0x807585a@
                at @C:0x8070c30@.@M:0x80769a4:0x80769ba@
                at @C:0x8070c30@.@M:0x807857c:0x8078596@
                at @C:0x8070c00@.@M:0x8074e04:0x8074e1a@
                at @C:0x8070ce0@.@M:0x807601c:0x807603c@
                at @C:0x806fe10@.@M:0x807779c:0x80777b0@
                at @C:0x8070c00@.@M:0x8077b40:0x8077b4c@
                at @C:0x8070c00@.@M:0x80779b0:0x80779bb@

Follow these steps:

- Make sure to build the Executable before executing the tool, by running either the ``buildExecutable`` or the ``runOnDevice`` task.
  The Executable file produced by the Application project is automatically used if it exists.
- When the Executable of the Application project is built, execute the ``stackTraceReader`` task, either from your IDE, or as a command line::

    ./gradlew stackTraceReader

- When the message ``[INFO] Paste the MicroEJ core engine stack trace here.`` is displayed, paste the encoded stacktrace into the console.
  The Stack Trace Reader immediately displays the decoded stack trace:

.. code:: console

    =============== [ MicroEJ Core Engine Trace ] ===============
    console:
    [INFO] Paste the MicroEJ core engine stack trace here.
        VM START
        Hello, World!
        Exception in thread "main" @C:0x8070c30@
             at @C:0x8070c60@.@M:0x8075850:0x807585a@
             at @C:0x8070c30@.@M:0x80769a4:0x80769ba@
             at @C:0x8070c30@.@M:0x807857c:0x8078596@
             at @C:0x8070c00@.@M:0x8074e04:0x8074e1a@
             at @C:0x8070ce0@.@M:0x807601c:0x807603c@
             at @C:0x806fe10@.@M:0x807779c:0x80777b0@
             at @C:0x8070c00@.@M:0x8077b40:0x8077b4c@
             at @C:0x8070c00@.@M:0x80779b0:0x80779bb@
        VM START
        Hello, World!
        Exception in thread "main" java.lang.Throwable
             at java.lang.System.getStackTrace(Unknown Source)
             at java.lang.Throwable.fillInStackTrace(Throwable.java:82)
             at java.lang.Throwable.<init>(Throwable.java:32)
             at java.lang.Thread.dumpStack(Thread.java:573)
             at com.microej.Main.main(Main.java:22)
             at java.lang.MainThread.run(Thread.java:855)
             at java.lang.Thread.runWrapper(Thread.java:464)
             at java.lang.Thread.callWrapper(Thread.java:449)

The Stack Trace Reader tool interacts with the console by default.
See the :ref:`sdk6.section.stacktrace.reader.tool.configure` chapter to learn about the other modes and configurations available.

Custom Executable File Location
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you want to decode a stack trace of a different Executable file than the Application project one, 
you must set the ``application.file`` System Property to define the Executable file location::

   ./gradlew stackTraceReader -D"application.file"="/path/to/my/application.out"

.. _sdk6.section.stacktrace.reader.tool.configure:

Configure
^^^^^^^^^

The Stack Trace Reader tool uses by default the console to communicate with the device, 
but this can be changed by setting the ``stackTraceReaderConnectionMode`` property in the ``microej`` block in the ``build.gradle.kts`` file::

    microej {
        stackTraceReaderConnectionMode = "file"
        stackTraceReaderFilePath = "/path/to/input/file"
        stackTraceReaderFileResultPath = "/path/to/output/file"
    }

Each mode has dedicated additional options.
The list of the available modes, with their dedicated options, are:

- ``console`` (default mode): use the standard input/output.
- ``file``: use files.
    - ``stackTraceReaderFilePath``: Path to the file containing the encoded stack trace.
    - ``stackTraceReaderFileResultPath``: Path to the output file for the decoded stack trace.
- ``uart``: use Serial communication.
    - ``stackTraceReaderUartPort``: PC COM port (example for Windows: ``COM1``, example for Linux: ``/dev/ttyS1``).
    - ``stackTraceReaderUartBaudRate``: COM baudrate for PC-Device communication.
- ``socket``: use a socket.
    - ``stackTraceReaderSocketAddress``: IP address.
    - ``stackTraceReaderSocketPort``: IP port.

For example, here is the configuration to use the ``socket`` mode on the address ``192.168.1.17`` and the port ``4000``::

    microej {
        stackTraceReaderConnectionMode = "socket"
        stackTraceReaderUartPort = "192.168.1.17"
        stackTraceReaderUartBaudRate = "4000"
    }

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
