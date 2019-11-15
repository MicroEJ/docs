.. _section.stacktrace.reader.tool:

Stack Trace Reader
==================

When an application is deployed on a device, stack traces dumped on
standard output are not directly readable: non required types (see
`??? <#section.classpath.elements.types>`__) names, methods names and
methods line numbers may not have been embedded to save code space. A
stack trace dumped on the standard output can be decoded using the Stack
Trace Reader tool.

Write a new line to dump the currently executed stack trace on the
standard output.

.. figure:: png/STR_stacktracedump.png
   :alt: Code to Dump a Stack Trace
   :width: 100.0%

   Code to Dump a Stack Trace

Write a new line to dump the currently executed stack trace on the
standard output.

.. figure:: png/trace1.png
   :alt: Code to Dump a Stack Trace

   Code to Dump a Stack Trace

To be able to decode an application stack trace, the stack trace reader
tool requires the application binary file with debug information
(``application.fodbg`` in the output folder). Note that the file which
is uploaded on the device is ``application.fo`` (stripped version
without debug information).

.. figure:: png/STR_debugfofile.png
   :alt: Application Binary File with Debug Information
   :width: 100.0%

   Application Binary File with Debug Information

On successful deployment, the application is started on the device and
the following trace is dumped on standard output.

.. figure:: png/STR_tracetermite.png
   :alt: Stack Trace Output
   :width: 100.0%

   Stack Trace Output

To create a new MicroEJ Tool configuration, right-click on the
application project and click on ``Run As... > Run Configurations...``.

In ``Execution`` tab, select the ``Stack Trace Reader`` tool.

.. figure:: png/STR_selecttool.png
   :alt: Select Stack Trace Reader Tool
   :width: 100.0%

   Select Stack Trace Reader Tool

In ``Configuration`` tab, browse the previously generated application
binary file with debug information (``application.fodbg``)

.. figure:: png/STR_selectfile.png
   :alt: Stack Trace Reader Tool Configuration
   :width: 100.0%

   Stack Trace Reader Tool Configuration

In ``Configuration`` tab, browse the previously generated application
binary file with debug information (``application.out``)

.. figure:: png/trace3.png
   :alt: Stack Trace Reader Tool Configuration
   :width: 100.0%

   Stack Trace Reader Tool Configuration

Click on ``Run`` button and copy/paste the trace into the Eclipse
console. The decoded trace is dumped and the line corresponding to the
application hook is now readable.

.. figure:: png/STR_console.png
   :alt: Read the Stack Trace
   :width: 100.0%

   Read the Stack Trace

The stack trace reader can simultaneously decode heterogeneous stack
traces with lines owned by different applications and the firmware.
Other debug information files can be appended using the
``Additional object files`` option. Lines owned by the firmware can be
decoded with the firwmare debug information file (optionally made
available by your firmware provider).
