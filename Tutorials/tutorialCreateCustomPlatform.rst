Create a MicroEJ Platform for a custom device
=============================================

Introduction
------------

A MicroEJ Architecture is a software package that includes the MicroEJ Runtime port to a specific target Instruction Set Architecture (ISA) and C compiler.
It contains a set of libraries, tools and C header files. The MicroEJ Architectures are provided by MicroEJ SDK.

A MicroEJ Platform is a MicroEJ Architecture port for a custom device.
It contains the MicroEJ configuration and the BSP (C source files).
MicroEJ Corp. provides example of MicroEJ Platforms for various evaluation boards on https://repository.microej.com/architectures/.

We recommend reading the :ref:`section.firmware` section to get an overview of MicroEJ Firmware build flow.

The following document assumes the reader is familiar with the :ref:`platform-developer-guide`.

Each MicroEJ Platform is specific to:

* a MicroEJ Architecture (MCU ISA and C compiler)
* an optional RTOS (e.g. FreeRTOS - note: the MicroEJ OS can run bare metal)
* a device: the OS bring up code that is device specific (e.g. the MCU specific code/IO/RAM/Clock/Middleware… configurations)

In this document we will address the following items:

* MicroEJ Platform Configuration project (in MicroEJ SDK)
* MicroEJ Simulator (in MicroEJ SDK)
* Platform BSP (in a C IDE/Compiler like GCC/KEIL/IAR)

The MicroEJ Platform relies on C drivers (aka low level LL drivers) for each of the platform feature.
These drivers are implemented in the platform BSP project. This project is edited in the C compiler IDE/dev environment (e.g. KEIL, GCC, IAR).
E.g. the MicroUI library LED feature will require a ``LLLEDS.c`` that implements the native on/off IO drive.

The following sections explain how to create a MicroEJ Platform for a custom device starting from an existing MicroEJ Platform.
In the following, we assume that the new device hardware is validated and at least a trace output is available.
It is also a good idea to run basic hardware test like:

* Internal and external flash programming and verification
* RAM 8/16/32 -bit read/write operations (internal and external if any)
* EEMBC Coremark benchmark to verify the CPU/buses/memory/compiler configuration
* See the `Platform Qualification Tools <https://github.com/MicroEJ/PlatformQualificationTools>`_ used to qualify MicroEJ Platforms.

Several use cases are presented:

A MicroEJ Platform is already available for the same MCU/RTOS/C Compiler
------------------------------------------------------------------------

This is the fastest way: the MicroEJ Platform is usually provided for a silicon vendor evaluation board.
Import this platform in MicroEJ SDK.

As the MCU, RTOS and compiler are the same, only the device specific code needs to be changed (external RAM, external oscillator, communication interfaces).

Platform
::::::::

In MicroEJ SDK

* modify the ``.platform`` from the MicroEJ Platform (``xxx-configuration`` project) to match the device features and its associated configuration (e.g. ``UI->Display``).

  .. image:: images/tuto_microej_platform_how_to_select_modules.PNG

  More details on available modules can be found in the :ref:`platform-developer-guide`.


BSP
:::

Required actions:

* modify the BSP C project to match the device specification

  * edit the scatter file/link options
  * edit the compilation options

* create/review/change the platform Low Level C drivers. 
  They must match the device components and the MCU IO pin assignment
  
  .. note::
    
    A number of ``LL*.h`` files are referenced from the project. 
    Implement the function prototypes declared there so that the JVM can delegate the relevant operations to the provided BSP C functions.

Simulator
:::::::::

In MicroEJ SDK

* modify the existing Simulator front panel ``xxx-fp`` project

A MicroEJ Platform is not available
-----------------------------------

Look for an available MicroEJ Platform that will match in order of priority:

* same MCU part number
* same RTOS
* same C compiler

At this point, consider either to modify the closest MicroEJ Platform

* In MicroEJ SDK: modify the platform configuration.
* in the C IDE: start from an empty project that match with the MCU.

Or to start from scratch a new MicroEJ Platform

* In MicroEJ SDK: create the MicroEJ Platform and refer to the selected MicroEJ Platform as a model for implementation. (refer to :ref:`platform_creation`)
* in the C IDE: start from an empty project and implement the drivers of each of the LL drivers API. 
  
  Make sure to link with:

  * the ``microejruntime.a`` that runs the JVM for the MCU Architecture
  * the ``microejapp.o`` that contains the compiled Java application

MCU
:::

The MCU specific code can be found:

* in the C project IDE properties
* in the linker file
* the IO configuration
* in the low level driver (these drivers are usually provided by the silicon vendor)

RTOS
::::

The LL driver is named ``LLMJVM_RTOS.c/.h``. Modify this file to match the selected RTOS.

C Compiler
::::::::::

The BSP project is provided for a specific compiler (that matches the selected platform architecture).
Start a new project with the compiler IDE that includes the LL drivers and start the MicroEJ Platform in the ``main()`` function.

Platform Validation
-------------------

Use the `Platform Qualification Tools <https://github.com/MicroEJ/PlatformQualificationTools>`_ to qualify the MicroEJ Platform built.

Further assistance needed
-------------------------

Please note that porting MicroEJ to a new device is also something that is part of our engineering services. Consider contacting sales@microej.com to request a quote.