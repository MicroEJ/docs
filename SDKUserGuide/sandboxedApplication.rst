.. _sdk_sandboxed_application:

Sandboxed Application
=====================

.. toctree::
   :maxdepth: 2
   :hidden:

   sandboxedAppFirstApplication
   sandboxedAppSim
   sandboxedAppDeploy

A Sandboxed Application is an Application that can run over a Multi-Sandbox Executable.

The Application development flow requires the following elements:

- a Virtual Device, a software package including the resources and tools required for building and testing an application for a specific device.
  A Virtual Device will simulate all capabilities of the corresponding hardware board:

  - Computation and Memory
  - Communication channels (e.g., Network, USB ...)
  - Display
  - User interaction

- an hardware device that has been previously programmed with a Multi-Sandbox Executable. 
  Virtual Devices and Multi-Sandbox Executable share the same version (there is a 1:1 mapping).

The :ref:`next chapters <chapter.application.firstApplication>` explain how to create, test and publish Sandboxed Applications.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
