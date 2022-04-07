.. _sdk_user_guide:

SDK User Guide
==============

MICROEJ SDK is an integrated environment to create software applications for MicroEJ-ready devices.
The SDK provides tools to write applications and run them on a virtual (simulated) or real device.
The capability to execute an application in a simulated environment allows to quickly test changes done 
in the application code and hence provide a short development feedback loop.

Since the purpose of the SDK is to develop for targeted MCU/MPU computers (IoT, wearable, etc.), it is a cross-development tool.
But unlike standard low-level cross-development tools, 
the SDK offers unique services like hardware simulation and local deployment to the target hardware.

.. figure:: images/1_overview.png
   :alt: MicroEJ Application Development Overview
   :align: center
   :scale: 50%

   MicroEJ Application Development Overview

The SDK is composed of:

- **SDK** an Integrated Development Environment for writing Applications and Firmwares.
  It is based on Eclipse Java edition and relies on the integrated Java compiler (JDT).
  Besides all the Eclipse capabilities, it provides additional tools such as a dependency manager 
  for managing MicroEJ Libraries (see :ref:`mmm`), a Memory Map Analyzer or a Heap Analyzer.
  The current distribution of MicroEJ Studio (``21.03``) is built on top 
  of `Eclipse 2020-06 <https://www.eclipse.org/downloads/packages/release/2020-06/r/eclipse-ide-java-developers>`_.

- **MicroEJ Module Manager**, the module and build manager used to compile and package Applications and Firmware.
  It provided a Command Line Interface allowing to build and run Applications with the Simulator.
  This is the privileged tool to build applications in a Continuous Integration environment.

- **MicroEJ Architecture**, the software package that includes the MEJ32 port to a target instruction set and a C compiler, SOAR, core libraries and Simulator.

The SDK is connected to:

- **Central and Developer Repository**, the modules repositories containing all the libraries required to
  develop an Application.

- **Github Repositories**, repositories with sources and examples.

.. figure:: images/sdk_content.png
   :alt: SDK Content
   :align: center
   :scale: 80%

   SDK Content

.. toctree::
   :hidden:
   :maxdepth: 1

   install
   systemRequirements
   workspace
   version
   licenses
   mmm
   sdkReleaseNotes
   sdkChangeLog
   sdkMigrationNotes
   troubleshooting
   
..
   | Copyright 2021-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
