.. _libraries:

MicroEJ Libraries
=================

A MicroEJ Foundation Library is a MicroEJ Core library that provides
core runtime APIs or hardware-dependent functionality. A Foundation
library is divided into an API and an implementation. A Foundation
library API is composed of a name and a 2 digits version (e.g.
``EDC-1.3``) and follows the semantic versioning (`<http://semver.org>`_)
specification. A Foundation Library API only contains prototypes without
code. Foundation Library implementations are provided by MicroEJ
Platforms. From a MicroEJ Classpath, Foundation Library APIs
dependencies are automatically mapped to the associated implementations
provided by the Platform or the Virtual Device on which the application
is being executed.

A MicroEJ Add-On Library is a MicroEJ library that is implemented on top
of MicroEJ Foundation Libraries (100% full Java code). A MicroEJ Add-On
Library is distributed in a single JAR file, with a 3 digits version and
provides its associated source code.

Foundation and Add-On Libraries are added to MicroEJ Classpath by the
application developer as module dependencies (see :ref:`mmm`).

.. figure:: images/ClassPath_2.png
   :alt: MicroEJ Foundation Libraries and Add-On Libraries
   :align: center
   :scale: 67%

   MicroEJ Foundation Libraries and Add-On Libraries

MicroEJ Corp. provides a large number of libraries through the :ref:`MicroEJ Central Repository <central_repository>`.
To consult its libraries APIs documentation, please visit `<https://developer.microej.com/microej-apis/>`_.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
