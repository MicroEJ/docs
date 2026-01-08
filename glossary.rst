.. _chapter-glossary:

MicroEJ Glossary
================

.. glossary::

   Add-On Library
      An Add-On Library is a pure Managed Code (Java code, C code or Javascript code) library. It runs over one or more Foundation Libraries.

   Abstraction Layer
      An Abstraction Layer is the native code (C code, Assembly code, etc.) that implements a Foundation Library's low-level APIs over a board support package (BSP) or a C library.

   Application
      An Application is a software program that runs on a MICROEJ VEE.

         Standalone Application
            A Standalone Application is the main application that is executed by MICROEJ VEE. It is linked statically to produce a Mono-Sandbox Executable.

         Sandboxed Application
            A Sandboxed Application is an Application that can run over a Multi-Sandbox Executable. It is linked dynamically.

         Kernel Application
            A Kernel Application is a Standalone Application that implements the ability to be extended to produce a Multi-Sandbox Executable.

   Architecture
      An Architecture is a software package that includes the Core Engine port to a target instruction set and a C compiler, core Foundation Libraries (:ref:`[EDC], [BON], [SNI], [KF] <runtime_core_libraries>`) and the Simulator. Architectures are distributed either as evaluation or production version.

   C Module
      A C Module is a collection of C source files packaged together with its own versioning and delivery lifecycle. A C Module represents an Abstraction Layer, a third-party library integration, or a set of reusable generic C code intended to be shared across different VEE Ports.

   Core Engine
      `The Core Engine, also named MEJ32, is a scalable 32-bit core <https://developer.microej.com/mej32-virtual-machine-for-embedded-systems/>`_ for resource-constrained embedded devices. It is delivered in various flavors, mostly as a binary software package. The Core Engine allows applications written in various languages to run in a safe container.

   Executable
      An Executable is the result of the binary link of a Standalone Application with a VEE Port. It can be programmed into the flash memory of a device.

         Mono-Sandbox Executable
            A Mono-Sandbox Executable is an Executable that implements an unmodifiable set of functions.

         Multi-Sandbox Executable
            A Multi-Sandbox Executable is an Executable that implements the ability to be extended, by exposing a Runtime Environment and a memory space to link Sandboxed Applications.

   Foundation Library
      A Foundation Library is a library that provides core or hardware-dependent functionalities. A Foundation Library combines `Managed Code`_ (Java code, C code or Javascript code) and low-level APIs (C code, Assembly code, etc.) implemented by one or more Abstraction Layers through a native interface (:ref:`SNI <sni_specification>`).

   Managed Code
      `Managed Code`_ is code that is executed under the supervision of a virtual processor, rather than directly by the hardware processor. 
      In the context of MicroEJ, the runtime responsible for managing code execution is called MICROEJ VEE.
      This approach ensures consistent execution behavior, portability across different hardware platforms, and secure memory isolation (sandboxing).       
   
   MICROEJ SDK
      MICROEJ SDK is a comprehensive tools suite for developers to build VEE Ports for their devices, create Applications, build Executable, and run Virtual Devices.

   MICROEJ VEE
      MICROEJ VEE is an application container. VEE stands for Virtual Execution Environment, and refers to the first implementation that embeds a virtual 32-bit processor, hence the term "Virtual". MICROEJ VEE runs on any OS/RTOS commonly used in embedded systems (FreeRTOS, QP/C, uc/OS, ThreadX, embOS, Mbed OS, Zephyr OS, VxWorks, PikeOS, Integrity, Linux, QNX, …) and can also run without RTOS (bare-metal) or proprietary RTOS. MICROEJ VEE includes the small MEJ32, along with a wide range of libraries (Add-On Libraries and Foundation Libraries).

   Mock
      A Mock is a mockup of a board support package (BSP) capability that mimics a hardware functionality for the Simulator.

   Runtime Environment
      A Runtime Environment is a custom set of APIs exposed by a Multi-Sandbox Executable, designed to support the development and execution of compatible Sandboxed Applications.
      It typically serves as the base component for building an ecosystem of applications within a specific domain.

   Simulator
      The Simulator allows running Applications on a target hardware simulator on the developer’s desktop computer. The Simulator runs one or more Mock that mimics the hardware functionality. It enables developers to develop their Applications without the need of hardware.

   VEE Port
      A VEE Port is an implementation of MICROEJ VEE tailored to run on a particular device (hardware board including both the processor and the peripherals). It integrates an Architecture, one or more Foundation Libraries with their respective Abstraction Layers, and the board support package (BSP). It also includes associated Mocks for the Simulator.

   Virtual Device
      A Virtual Device is a software package that includes the simulation part of an Executable: runtime, libraries and application(s). It can be run on any desktop computer without the need of the SDK.
      
.. _Managed Code: https://developer.microej.com/managed-code/


..
   | Copyright 2008-2026, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
