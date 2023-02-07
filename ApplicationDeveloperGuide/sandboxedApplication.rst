.. _sandboxed_application:

Sandboxed Application
=====================

.. toctree::
   :maxdepth: 2
   :hidden:

   sandboxedAppFirstApplication
   sandboxedAppSim
   sandboxedAppDeploy
   sandboxedAppFundamentalConcepts
   sandboxedAppSharedInterface

A Sandboxed Application is a Java Application that can run over a Multi-Sandbox Executable.
Sandboxed Applications can be linked statically to the Multi-Sandbox Executable or installed dynamically on the device.

Typical use cases for a Sandboxed Application are:

- over the air provisioning: the Application is dynamically installed or updated on a fleet of heterogenous devices.
- modularization: a monolithic application is split into multiple Sandboxed Applications; each of them can be started or stopped separately.

The Application development flow requires the following elements:

- a Virtual Device, a software package including the resources and tools required for building and testing an application for a specific device.
  A Virtual Device will simulate all capabilities of the corresponding hardware board:

  - Computation and Memory
  - Communication channels (e.g. Network, USB ...)
  - Display
  - User interaction

- an hardware device that has been previously programmed with a Multi-Sandbox Executable. 
  Virtual Devices and Multi-Sandbox Executable share the same version (there is a 1:1 mapping).

Please refer to the :ref:`kernel-developer-guide` to learn more on writing Kernel Applications and building Multi-Sandbox Executable and Virtual Devices.

The :ref:`next chapters <chapter.application.firstApplication>` explain how to create, test and publish Sandboxed Applications.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
