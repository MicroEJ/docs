.. _section.stacktrace.reader.tool:

.. _stack_trace_reader:

==================
Stack Trace Reader
==================

Principle
=========

Stack Trace Reader is a MicroEJ tool that reads and decodes the MicroEJ
stack traces. When an exception occurs, the Core Engine prints
the stack trace on the standard output ``System.out``. The class names,
non-required types names(see :ref:`section.classpath.elements.types`),
and method names obtained are encoded with a MicroEJ internal format.
This internal format prevents embedding all class names and
method names in the executable image to save some memory space. The Stack
Trace Reader tool allows you to decode the stack traces by replacing the
internal class names and method names with their real names. It also
retrieves the line numbers in the MicroEJ Application.

Functional Description
======================

The Stack Trace Reader reads the debug information from the fully linked ELF
file (the ELF file that contains the Core Engine, the other
libraries, the BSP, the OS, and the compiled MicroEJ Application). It
prints the decoded stack trace.

When :ref:`Multi-Sandbox capability <multisandbox>` is enabled, 
the Stack Trace Reader can simultaneously decode heterogeneous stack
traces with lines owned by different MicroEJ Sandboxed Applications and the firmware.
Lines owned by the firmware can be decoded with the firmware debug information file
(optionally made available by your firmware provider).


Dependencies
============

No dependency.


Installation
============

This tool is a built-in Architecture tool.


Use (Standalone Application)
============================

For example, write the following new line to dump the currently executed stack trace on the
standard output.

.. figure:: images/trace1.png
   :alt: Code to Dump a Stack Trace
   :align: center
   :scale: 100%

   Code to Dump a Stack Trace

To decode an application stack trace, the Stack Trace Reader tool requires the application executable ELF file.
In the case of a platform with full BSP connection (see :ref:`BSP Connection Cases <bsp_connection_cases>`), the file is ``application.out`` in the output folder. 
In the other cases, the ELF file is generated by the C toolchain when building the BSP project (usually a ``.out`` or ``.axf`` file).

.. figure:: images/STR_application-out.png
   :alt: Application Binary File
   :align: center
   :scale: 100%

   Application Binary File

On successful deployment, the application is started on the device and
the following trace is dumped on standard output.

.. figure:: images/STR_tracetermite_standalone.png
   :alt: Stack Trace Output
   :scale: 100%
   :align: center
   
   Stack Trace Output

To create a new MicroEJ Tool configuration, right-click on the application
project and click on :guilabel:`Run As...` > :guilabel:`Run Configurations...`.

Create a new MicroEJ Tool configuration. In the :guilabel:`Execution` tab, select your target platform, then select the :guilabel:`Stack Trace Reader` tool. Set an output folder in the :guilabel:`Output folder` field.

.. figure:: images/STR_selecttool_standalone.png
   :alt: Stack Trace Reader Tool Configuration (Platform Selection)
   :align: center
   :scale: 100%

   Stack Trace Reader Tool Configuration (Platform Selection)

In :guilabel:`Configuration` tab, browse the previously generated application
binary file with debug information (``application.out`` in case of a Standalone Application with full BSP connection)

.. figure:: images/STR_configuration_standalone.png
   :alt: Stack Trace Reader Tool Configuration (Standalone Application)
   :align: center
   :scale: 100%

   Stack Trace Reader Tool Configuration (Standalone Application)

Click on :guilabel:`Run` button and copy/paste the trace into the Eclipse
console. The decoded trace is dumped and the line corresponding to the
application hook is now readable.

.. figure:: images/STR_trace-read.png
   :alt: Stack Trace Reader Console
   :scale: 100%
   :align: center
   
   Stack Trace Reader Console



Use (Sandboxed Application)
===========================

For example, write the following new line to dump the currently executed stack trace on the
standard output.

.. figure:: images/STR_stacktracedump.png
   :alt: Code to Dump a Stack Trace
   :align: center
   :scale: 100%

   Code to Dump a Stack Trace

To decode an application stack trace, the Stack Trace Reader
tool requires the application binary file with debug information
(``application.fodbg`` in the output folder). Note that the file 
uploaded on the device is ``application.fo`` (stripped version
without debug information).

.. figure:: images/STR_debugfofile.png
   :alt: Application Binary File with Debug Information
   :align: center
   :scale: 100%

   Application Binary File with Debug Information

On successful deployment, the application is started on the device and
the following trace is dumped on standard output.

.. figure:: images/STR_tracetermite_sandboxed.png
   :alt: Stack Trace Output
   :align: center
   :scale: 100%

   Stack Trace Output

To create a new MicroEJ Tool configuration, right-click on the application
project and click on :guilabel:`Run As...` > :guilabel:`Run Configurations...`.

Create a new MicroEJ Tool configuration. In the :guilabel:`Execution` tab, select your target platform, then select the :guilabel:`Stack Trace Reader` tool. Set an output folder in the :guilabel:`Output folder` field.

.. figure:: images/STR_selecttool_sandboxed.png
   :alt: Stack Trace Reader Tool Configuration (Virtual Device Selection)
   :align: center
   :scale: 100%

   Stack Trace Reader Tool Configuration (Virtual Device Selection)

In the :guilabel:`Configuration` tab, if the Kernel executable file is available to you (usually named ``firmware.out`` and located in your Virtual Device files), you can browse for it in the :guilabel:`Executable file` field,
and then add your previously generated application binary file with debug information (``application.fodbg`` in case of a Sandboxed
Application) in the :guilabel:`Additional object files` field.

.. figure:: images/STR_firmware-out.png
   :alt: Select the Kernel Executable File
   :align: center
   :scale: 100%

   Select the Kernel Executable File

To check where the Kernel executable file of your Virtual Device is located, if you have access to it, go to :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` > :guilabel:`Virtual Devices`, hover over your Virtual Device in the list and wait until an information popup appears. Press :guilabel:`F2` to get all the informations and the path to the directory of your Virtual Device should appear in the list.

.. figure:: images/STR_virtualdevice.png
   :alt: Location of the Virtual Device Directory
   :align: center
   :scale: 100%

   Location of the Virtual Device Directory

In this directory, the Kernel executable file should be named ``firmware.out`` in the ``/firmware`` sub-directory.

If you do not have access to the Kernel executable file, you can still get some information from the Stack Trace Reader using the application binary file only. In the :guilabel:`Configuration` tab, browse the previously generated application binary file with debug information (``application.fodbg`` in case of a Sandboxed Application)

.. figure:: images/STR_selectfile_sandboxed.png
   :alt: Stack Trace Reader Tool Configuration (Sandboxed Application)
   :align: center
   :scale: 100%

   Stack Trace Reader Tool Configuration (Sandboxed Application)

Click on :guilabel:`Run` button and copy/paste the trace into the Eclipse
console. The decoded trace is dumped and the line corresponding to the
application hook is now readable.


.. figure:: images/STR_console_sandboxed.png
   :alt: Stack Trace Reader Console
   :align: center
   :scale: 100%

   Stack Trace Reader Console

Other debug information files can be appended using the
:guilabel:`Additional object files` option. 

Stack Trace Reader Options
==========================

The following section explains MicroEJ tool options.

.. include:: stackTraceReader_use.rst

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
