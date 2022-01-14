

Introduction
------------

A MicroEJ Platform includes development tools and a runtime environment.

The runtime environment consists of:

-  A MicroEJ Core Engine.

-  Some Foundation Libraries.

-  Some C libraries.

The development tools are composed of:

-  Java APIs to compile MicroEJ Application code.

-  Documentation: this guide, library specifications, etc.

-  Tools for development and compilation.

-  Launch scripts to run the simulation or build the binary file.

-  Eclipse plugins.

.. _build_process_overview:

Build Process
-------------

This section summarizes the steps required to build a MicroEJ Platform
and obtain a binary file to deploy on a board.

:ref:`The following figure <fig_overall-process>` shows the overall process. The first
three steps are performed within the MicroEJ Platform builder. The
remaining steps are performed within the C IDE.

.. _fig_overall-process:
.. figure:: images/process-overview5.*
   :alt: Overall Process
   :scale: 80%
   :align: center

   Overall Process

The steps are as follow:

1. Create a new MicroEJ Platform configuration project. This project
   describes the MicroEJ Platform to build (MicroEJ Architecture,
   metadata, etc.).

2. Select which modules provided by the MicroEJ Architecture will be
   installed in the MicroEJ Platform.

3. Build the MicroEJ Platform according to the choices made in steps 1
   and 2.

4. Compile a MicroEJ Application against the MicroEJ Platform in order
   to obtain an application file to link in the BSP.

5. Compile the BSP and link it with the MicroEJ Application that was
   built previously in step 4 to produce a MicroEJ Firmware.

6. Final step: Deploy MicroEJ Firmware (i.e. the binary application)
   onto a board.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
