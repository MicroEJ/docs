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

Write a new line to dump the currently executed stack trace on the
standard output.

To be able to decode an application stack trace, the stack trace reader
tool requires the application binary file with debug information
(``application.fodbg`` in the output folder). Note that the file which
is uploaded on the device is ``application.fo`` (stripped version
without debug information).

On successful deployment, the application is started on the device and
the following trace is dumped on standard output.

To create a new MicroEJ Tool configuration, right-click on the
application project and click on ``Run As... > Run Configurations...``.

In ``Execution`` tab, select the ``Stack Trace Reader`` tool.

In ``Configuration`` tab, browse the previously generated application
binary file with debug information (``application.fodbg``)

In ``Configuration`` tab, browse the previously generated application
binary file with debug information (``application.out``)

Click on ``Run`` button and copy/paste the trace into the Eclipse
console. The decoded trace is dumped and the line corresponding to the
application hook is now readable.

The stack trace reader can simultaneously decode heterogeneous stack
traces with lines owned by different applications and the firmware.
Other debug information files can be appended using the
``Additional object files`` option. Lines owned by the firmware can be
decoded with the firwmare debug information file (optionally made
available by your firmware provider).
