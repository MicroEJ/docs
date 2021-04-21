.. _chapter-glossary:

MicroEJ Glossary
================

This glossary defines the technical terms upon which the `MicroEJ Virtual Execution Environment <https://developer.microej.com/microej-vee-virtual-execution-environment>`_ is built.

.. glossary::

   Add-On Library
      A MicroEJ Add-On Library is a pure `managed code <https://en.wikipedia.org/wiki/Managed_code>`_ (Java) library. It runs over one or more MicroEJ Foundation Libraries.

   Abstraction Layer
      An Abstraction Layer is the C code that implements a Foundation Library's low-level APIs over a board support package (BSP) or a C library.

   Application
      A MicroEJ Application is a software program that runs on a Powered by MicroEJ device.

         Standalone Application
            MicroEJ Standalone Application is a MicroEJ Application that is directly linked to the C code to produce a MicroEJ Mono-Sandbox Firmware. It is edited using MicroEJ SDK.

         Sandboxed Application
            A MicroEJ Sandboxed Application is a MicroEJ Application that can run over a MicroEJ Multi-Sandbox Firmware. It can be linked either statically or dynamically.

         System Application
            A MicroEJ System Application is a MicroEJ Sandboxed Application that is statically linked to a MicroEJ Multi-Sandbox Firmware, as it is part of the initial image and cannot be removed.

         Kernel Application
            A MicroEJ Kernel Application is a MicroEJ Standalone Application that implements the ability to be extended to produce a MicroEJ Multi-Sandbox Firmware.

   Architecture
      A MicroEJ Architecture is a software package that includes the MicroEJ Core Engine port to a target instruction set and a C compiler, core MicroEJ Foundation Libraries (EDC, :ref:`[BON], [SNI], [KF] <esr-specifications>`) and the MicroEJ Simulator. MicroEJ Architectures are distributed either as evaluation or production version.

   Core Engine
      MicroEJ Core Engine is a scalable runtime for resource-constrained embedded devices running on 32-bit microcontrollers or microprocessors. MicroEJ Core Engine allows devices to run multiple and mixed Java and C software applications.

   Firmware
      A MicroEJ Firmware is the result of the binary link of a MicroEJ Standalone Application with a MicroEJ Platform. The firmware is a binary  program that can be programmed into the flash memory of a device. 

         Mono-Sandbox Firmware
            A MicroEJ Mono-Sandbox Firmware is a MicroEJ Firmware that implements an unmodifiable set of functions. (previously MicroEJ Single-app Firmware)

         Multi-Sandbox Firmware
            A MicroEJ Multi-Sandbox Firmware is a MicroEJ Firmware that implements the ability to be extended, by exposing a set of APIs and a memory space to link MicroEJ Sandboxed Applications. (previously MicroEJ Multi-app Firmware) 

   Foundation Library
      A MicroEJ Foundation Library is a library that provides core or hardware-dependent functionalities. A Foundation Library combines `managed code <https://en.wikipedia.org/wiki/Managed_code>`_ (Java) and low-level APIs (C) implemented by one or more Abstraction Layers through a native interface (:ref:`SNI <sni>`).

   Mock
      A MicroEJ Mock is a mockup of a Board Support Package capability that mimics an hardware functionality for the MicroEJ Simulator.

   Module Manager
      MicroEJ Module Manager downloads, installs and controls the consistency of all the dependencies and versions required to build and publish a MicroEJ asset. It is based on `Semantic Versioning <https://semver.org>`_ specification.

   Platform
      A MicroEJ Platform integrates a MicroEJ Architecture, one or more Foundation Libraries with their respective Abstraction Layers and the board support package (BSP) for the target Device. It also includes associated MicroEJ Mocks for the MicroEJ Simulator.

   SDK
      MicroEJ SDK allows MicroEJ Firmware developers to build a MicroEJ-ready device, by integrating a MicroEJ Architecture with both Java and C software on their device.

   Simulator
      MicroEJ Simulator allows running MicroEJ Applications on a target hardware simulator on the developer’s desktop computer. The MicroEJ Simulator runs one or more MicroEJ mock that mimics the hardware functionality. It enables developers to develop their MicroEJ Applications without the need of hardware.

   Studio
      MicroEJ Studio allows application developers to write a MicroEJ Sandboxed Application, run it on a Virtual Device, deploy it on a MicroEJ-ready device, and publish it to a `MicroEJ Forge <https://www.microej.com/product/forge/>`_ instance.

   Virtual Device
      A MicroEJ Virtual Device is a software package that includes the simulation part of a MicroEJ Firmware: runtime, libraries and application(s). It can be run on any PC without the need of MicroEJ Studio. In case a MicroEJ Multi-Sandbox Firmware, it is also used for testing a MicroEJ Sandboxed Application in MicroEJ Studio. 

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
