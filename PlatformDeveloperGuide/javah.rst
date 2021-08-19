.. _tool_javah:

==============
MicroEJ Java H
==============


Principle
=========

This MicroEJ tool is useful for creating the skeleton of a C file, to
which some Java native implementation functions will later be written.
This tool helps prevent misses of some ``#include`` files, and helps
ensure that function signatures are correct.


Functional Description
======================

MicroEJ Java H tool takes as input one or several Java class files 
(\*.class) from directories and / or JAR files. It looks for Java native
methods declared in these class files, and generates a skeleton(s) of
the C file(s).

.. figure:: images/javah_process.*
   :alt: MicroEJ Java H Process
   :align: center
   :scale: 75%

   MicroEJ Java H Process


Dependencies
============

No dependency.


Installation
============

This is an additional tool. In the platform configuration file, check
:guilabel:`Java to C Interface` > :guilabel:`MicroEJ Java H` to install the tool.


Use
===

This chapter explains the MicroEJ tool options.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
