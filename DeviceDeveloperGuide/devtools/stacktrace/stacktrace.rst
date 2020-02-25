.. _stack_trace_reader:

==================
Stack Trace Reader
==================


Principle
=========

Stack Trace Reader is a MicroEJ tool which reads and decodes the MicroEJ
stack traces. When an exception occurs, the MicroEJ core engine prints
the stack trace on the standard output ``System.out``. The class names
and method names obtained are encoded with a MicroEJ internal format.
This internal format prevents the embedding of all class names and
method names in the flash, in order to save some memory space. The Stack
Trace Reader tool allows you to decode the stack traces by replacing the
internal class names and method names with their real names. It also
retrieves the line number in the MicroEJ application.


Functional Description
======================

The Stack Trace Reader reads the debug info from the fully linked ELF
file (the ELF file that contains the MicroEJ core engine, the other
libraries, the BSP, the OS, and the compiled MicroEJ application). It
prints the decoded stack trace.


Dependencies
============

No dependency.


Installation
============

This tool is a built-in platform tool.


Use
===

This chapter explains MicroEJ tool options.


.. include:: stacktrace_use.rst
