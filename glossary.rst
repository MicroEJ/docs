.. _chapter-glossary:

MicroEJ Glossary
================

.. glossary::

   Add-On Library
      A MicroEJ Add-On Library is a pure managed code library. It runs over one or more MicroEJ Foundation Libraries.

   Application
      A MicroEJ Application is a software program that runs on a Powered by MicroEJ device. A MicroEJ Application can be a Standalone Application or Multi-Sandbox Application.

      Standalone Application
         A MicroEJ Standalone Application is statically linked to one VEE platform, to form a Firmware that can be loaded to an electronic device. A standalone Application has one unique starting point (traditionally called "main").

      Multi-Sandbox Application
         A MicroEJ Multi-Sandbox Application is a software component (often just named as "APP") that runs on a Multi-Sandbox VEE platform. Such applications are either statically or dynamically linked to the VEE. When statically linked, they are qualified as System (Multi-Sandbox) Application.  A specific System Application is named "the kernel": the Kernel controls and manages the resources grants (cpu, memory, peripherals, etc...) of the other Applications that are managed by the Multi-Sandbox VEE.

   Architecture
      A MicroEJ Architecture is a software package that includes the MicroEJ Core IP (`MEJ32 core <https://developer.microej.com/mej32-embedded-runtime-architectures>`_) ported for a specific target ISA (instruction set architecture) combined with a specific ABI (application binary interface). It embeds the minimal set of MicroEJ Foundation Libraries (EDC, :ref:`[BON], [SNI], [KF] <esr-specifications>`), along with its Virtual Device. MicroEJ Architectures are distributed as evaluation or production version, and come with various configurations such as: (N) for standard, (T) for tiny, (K) for Multi-Sandbox.

   Firmware
      A MicroEJ Firmware is monolithic sequence of 0 and 1 that can be run by a (or more) processor(s). A firmware is either executed in place when flashed in a MCU memory, or loaded into (RAM) memory before its execution by a MPU.

   Forge
      MICROEJ FORGE is a cloud service that holds and manages software assets: Applications, Libraries, Virtual Devices,… It is a white label product that is branded to the customers brand. MICROEJ FORGE is the technical component needed to build a community Applications Store. 

   Foundation Library
      A MicroEJ Foundation Library is a library that provides hardware-dependent functionalities. A Foundation Library provides doors to the "out-side" world, that is, to code that is not managed code by the VEE.

   Mock
      A MicroEJ Mock mimics a physical peripheral that is not available (by default) on the Desktop machine that runs the Virtual Device.

   Module Manager
      MicroEJ Module Manager (MMM) is a dependencies solver that validates the consistency of all the dependencies and versions required to build and publish an asset. Such build of an asset involves to download, to install, to link, to analyze, etc. based on semantic constraints specific to each asset. 

   Virtual Execution Environment (VEE) platform
      A VEE platform is made of a MicroEJ Architecture and Libraries (Foundation and Add-on). MICROEJ SDK is the preferred tool to assemble a `MICROEJ VEE <https://developer.microej.com/microej-vee-virtual-execution-environment>`_: a trusted execution environment to safely run managed code. 

   SDK
      `MICROEJ SDK <https://developer.microej.com/microej-sdk-software-development-kit>`_ features a wide range of powerful tools and libraries, built on Eclipse, to design custom VEE, software application or software components/libraries, using multiples languages such as C,Java,Javascript, XML, CSS, etc. It includes powerful compilers, debuggers and advanced code editor for a smooth and easy learning experience.

   Studio
      MICROEJ STUDIO allows developers to write portable (and potentially dynamically loadable) software component bundled as Multi-Sandboxed Application. MICROEJ STUDIO is for engineers that develop only managed code. It is a strict subset of MICROEJ SDK. MICROEJ STUDIO is often connected to a MICROEJ FORGE instance.

   Virtual Device
      A `Virtual Device <https://www.microej.com/product/vee>`_ runs on a Desktop: it is teh Digital twin of the VEE platform. It runs the same set of managed code and libraries run by a VEE. Mocks allow to simulate all the peripherals addressed by the VEE: displays, connectivity, sensors, etc. A Virtual Device is an true managed binary code accurate simulator.  

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
