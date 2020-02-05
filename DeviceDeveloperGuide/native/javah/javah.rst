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
   :width: 60.0%
   :align: center

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
