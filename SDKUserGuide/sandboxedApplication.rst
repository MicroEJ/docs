.. warning::

  This documentation is for SDK 5. The latest major version is :ref:`SDK 6 <sdk_6_user_guide>`.
  SDK 5 is in maintenance mode since the release of :ref:`SDK 5.8.0 <changelog-5.8.0>`.
  Consequently, as stated in the :ref:`SDK End User License Agreement (EULA) <sdk_eula>`, the SDK will reach the end of its life by July 2028.
  Contact :ref:`our support team <get_support>` for assistance with migrating to the new SDK, or your sales representative if you require an extension of SDK maintenance as a service.

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
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
