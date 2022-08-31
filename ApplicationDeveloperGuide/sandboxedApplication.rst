.. _sandboxed_application:

Sandboxed Application
=====================

.. toctree::
   :maxdepth: 2
   :hidden:

   sandboxedAppFirstApplication
   sandboxedAppSim
   sandboxedAppDeploy
   sandboxedAppSharedInterface

A Sandboxed Application is a Java Application that can run over a Multi-Sandbox Firmware.
Sandboxed Applications can be linked statically to the Multi-Sandbox Firmware or installed dynamically on the device.

Typical use cases for a Sandboxed Application are:

- over the air provisioning: the Application is dynamically installed or updated on a device.
- modularization: a monolithic Standalone Application is split into multiple Sandboxed Applications; each of them can be started or stopped separately.

The Application development flow requires the following elements:

- a Virtual Device, a software package including the resources and tools required for building and testing an application for a specific device.
  A Virtual Device will simulate all capabilities of the corresponding hardware board:

  - Computation and Memory
  - Communication channels (e.g. Network, USB ...)
  - Display
  - User interaction

- an hardware device that has been previously programmed with a Multi-Sandbox Firmware. 
  Virtual Devices and Multi-Sandbox Firmware share the same version (there is a 1:1 mapping).

Please refer to the :ref:`kernel-developer-guide` to learn more on Multi-Sandbox Firmware and Virtual Devices, and how to create them.

The next chapters explain how to create, test and publish Sandboxed Applications.
But before starting, there are fundamental concepts that need to be understood about Sandboxed Applications.

 |

**Fundamental Concepts**

The concepts of Sandboxed Application and Multi-Sandbox Firmware are based on the Kernel & Features semantic (KF).
It allows an application code to be split between multiples parts: 

- the main application, called the Kernel
- zero or more Sandboxed Applications called Features.

Therefore, in the next chapters, the terms **Kernel** and **Multi-Sandbox Firmware** are equivalent, as well as the terms **Sandboxed Application** and **Feature**.

Some fundamental points:

- The Kernel is mandatory. It is assumed to be reliable, trusted and cannot be modified.
- A Feature is an application "extension" managed by the Kernel.
- A Feature is fully controlled by the Kernel: it can be installed (dynamically or statically pre-installed), started, stopped and
  uninstalled at any time independent of the system state (particularly, a Feature never depends on
  another Feature to be stopped).
- A Feature is optional, potentially not-trusted, maybe unreliable and
  can be executed without jeopardizing the safety of the Kernel execution and other Features.
- Resources accesses (RAM, hardware peripherals, CPU time, ...) are under control of the Kernel.

.. note::

   You can go further by reading `the Kernel & Features Specification <_kf_specification>`.


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
