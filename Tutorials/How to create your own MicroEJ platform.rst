How to create your own MicroEJ platform on a custom board
=========================================================

Introduction
------------

A MicroEJ architecture is a software package that includes the MicroEJ Runtime port to a specific target Instruction Set Architecture (ISA) and C compiler.
It contains a set of libraries, tools and C header files. The MicroEJ architectures are provided by MicroEJ SDK.

A MicroEJ platform reference implementation (RI) is a MicroEJ port for a custom board.
It contains the MicroEJ configuration and the BSP (C source files).
The MicroEJ platform RI can be found on https://developer.microej.com.

We recommend reading the :ref:`section.firmware` section to get an overview of the firmware build flow.

The following document assumes the reader is familiar with the :ref:`platform-developer-guide`.

Each platform reference implementation is specific to:

* a MicroEJ architecture (MCU ISA and C compiler)
* an optional RTOS (e.g. FreeRTOS - note: the MicroEJ OS can run bare metal)
* a board: the OS bring up code that is board specific (e.g. the MCU specific code/IO/RAM/Clock/Middleware… configurations)

In this document we will address the following items:

* Platform configuration (in MicroEJ SDK)
* Platform simulator (in MicroEJ SDK)
* Platform BSP (in a C IDE/Compiler like GCC/KEIL/IAR)

The MicroEJ platform relies on C drivers (aka low level LL drivers) for each of the platform feature.
These drivers are implemented in the platform BSP project. This project is edited in the C compiler IDE/dev environment (e.g. KEIL, GCC, IAR).
E.g. the MicroUI library LED feature will require a ``LLLEDS.c`` that implements the native on/off IO drive.

The following sections explain how to create your own platform for a custom board from an existing platform RI.
In the following, we assume that the new board hardware is validated and at least a trace output is available.
It is also a good idea to run basic hardware test like:

* Internal and external flash programming and verification
* RAM 8/16/32 -bit read/write operations (internal and external if any)
* EEMBC Coremark benchmark to verify the CPU/buses/memory/compiler configuration

Several use cases are presented:

A MicroEJ platform Reference Implementation (RI) is already available for the same MCU/RTOS/C Compiler
------------------------------------------------------------------------------------------------------

This is the fastest way: the RI is usually provided for a silicon vendor evaluation board.
Import this platform in MicroEJ SDK.

As the MCU, RTOS and compiler are the same, only the board specific code needs to be changed (external RAM, external oscillator, communication interfaces).

Platform
::::::::

Required actions:

* modify the .platform from the RI (``xxx-configuration`` project) in MicroEJ SDK to match your board features and its associated configuration (e.g. ``UI->Display``).
  More details on which module does what may be gathered from the :ref:`platform-developer-guide`.

BSP
:::

Required actions:

* modify the BSP C project to match the board specification

  * edit the scatter file/link options
  * edit the compilation options

* create/review/change the platform Low Level C drivers. 
  They must match the board components and the MCU IO pin assignment
  (a number of ``LL*.h`` files are referenced from the project, you will need to provide relevant implementations for the function prototypes declared there so that the JVM can delegate the relevant operations to the provided BSP C functions)

Simulator
:::::::::

Required actions:

* modify the existing simulator front panel in MicroEJ SDK ``xxx-fp`` project

A MicroEJ platform Reference Implementation (RI) is not available
-----------------------------------------------------------------

Look for an available RI that will match in order of priority:

* same MCU part number
* same RTOS
* same C compiler

At this point, consider either to modify the closest platform RI

* In MicroEJ SDK: modify the platform configuration.
* in the C IDE: start from an empty project that match with your MCU.

Or to start from scratch a new MicroEJ platform

* In MicroEJ SDK: create your platform and edit (refer to the RI as a model for implementation)
* in the C IDE: start from an empty project and implement the drivers of each of the LL drivers API. 
  
  You will need to make sure that you :

  * link with the ``microejruntime.lib`` that runs the JVM for your MCU Architecture
  * link with the ``microejapp.o`` that contains your compiled Java application

MCU
:::

The MCU specific code can be found:

* in the C project IDE properties
* in the linker file
* the IO configuration
* in the low level driver (these drivers are usually provided by the silicon vendor)

RTOS
::::

The LL driver is named ``LLMJVM_RTOS.c/.h``. Modify this file to match your selected RTOS.

C Compiler
::::::::::

The BSP project is provided for a specific compiler (that matches the selected platform architecture).
Start a new project with your compiler IDE that includes the LL drivers and start the MicroEJ platform in the ``main()`` function.

Further assistance needed
-------------------------

Please note that porting MicroEJ to a new board is also something that is part of our engineering services.
You may consider contacting sales@microej.com to request a quote.