.. _chapter-glossary:

MicroEJ Glossary
================

.. glossary::

   Add-On Library
      A MicroEJ Add-On Library is a pure Java library that is implemented on top of one or more MicroEJ Foundation Libraries.

   Application
      A MicroEJ Application is a software program that runs on a MicroEJ-ready device. A MicroEJ Application is called a MicroEJ Standalone Application or a MicroEJ Sandboxed Application depending the way it is linked.

         Standalone Application
            MicroEJ Standalone Application is a MicroEJ Application that is directly linked to the C code to produce a MicroEJ Firmware. It is edited using MicroEJ SDK.

         Sandboxed Application
            A MicroEJ Sandboxed Application is a MicroEJ Application that can run over a MicroEJ Multi-Sandbox Firmware. It can be linked either statically or dynamically.

         System Application
            A MicroEJ System Application is a MicroEJ Sandboxed Application that is statically linked to the MicroEJ Firmware, as it is part of the initial image and cannot be removed.

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

   Forge
      MicroEJ Forge is a cloud server that manages MicroEJ software assets: Applications, Libraries, Virtual Devices,... It is based on JFrog Artifactory PRO. It is a white label product that is branded to the customers brand.

   Foundation Library
      A MicroEJ Foundation Library is a MicroEJ library that provides core runtime APIs or hardware-dependent functionality. It is often connected to underlying C low-level APIs.

   Mock
      A MicroEJ Mock is a mockup of a Board Support Package capability that mimics an hardware functionality for the MicroEJ Simulator.

   Module Manager
      MicroEJ Module Manager downloads, installs and controls the consistency of all the dependencies and versions required to build and publish a MicroEJ asset. It is based on `Semantic Versioning <https://semver.org>`_ specification.

   Platform
      A MicroEJ Platform is a software package integrating a C board support package (BSP, with or without RTOS), a MicroEJ Architecture, abstraction layers for the target Device, and its associated MicroEJ Mocks for the MicroEJ Simulator. It is edited using MicroEJ SDK.

   SDK
      MicroEJ SDK allows MicroEJ Firmware developers to build a MicroEJ-ready device, by integrating a MicroEJ Architecture with both Java and C software on their device.

   Simulator
      MicroEJ Simulator allows running MicroEJ Applications on a target hardware simulator on the developer’s desktop computer. The MicroEJ Simulator runs one or more MicroEJ mock that mimics the hardware functionality. It enables developers to develop their MicroEJ Applications without the need of hardware.

   Studio
      MicroEJ Studio allows application developers to write a MicroEJ Sandboxed Application, run it on a Virtual Device, deploy it on a MicroEJ-ready device, and publish it to a MicroEJ Forge instance.

   Virtual Device
      A MicroEJ Virtual Device is a software package that includes the simulation part of a MicroEJ Firmware: runtime, libraries and application(s). It can be run on any PC without the need of MicroEJ Studio. In case a MicroEJ Multi-Sandbox Firmware, it is also used for testing a MicroEJ Sandboxed Application in MicroEJ Studio. 

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
