========================================
Appendix D: Architectures MCU / Compiler
========================================

Principle
=========

The MicroEJ C libraries have been built for a specific processor (a
specific MCU architecture) with a specific C compiler. The third-party
linker must make sure to link C libraries compatible with the MicroEJ C
libraries. This chapter details the compiler version, flags and options
used to build MicroEJ C libraries for each processor.

Some processors include an optional floating point unit (FPU). This FPU
is single precision (32 bits) and is compliant with IEEE 754 standard.
It can be disabled when not in use, thus reducing power consumption.
There are two steps to use the FPU in an application. The first step is
to tell the compiler and the linker that the microcontroller has an FPU
available so that they will produce compatible binary code. The second
step is to enable the FPU during execution. This is done by writing to
CPAR in the SystemInit() function. Even if there is an FPU in the
processor, the linker may still need to use runtime library functions to
deal with advanced operations. A program may also define calculation
functions with floating numbers, either as parameters or return values.
There are several Application Binary Interfaces (ABI) to handle floating
point calculations. Hence, most compilers provide options to select one
of these ABIs. This will affect how parameters are passed between caller
functions and callee functions, and whether the FPU is used or not.
There are three ABIs:

-  Soft ABI without FPU hardware. Values are passed via integer
   registers.

-  Soft ABI with FPU hardware. The FPU is accessed directly for simple
   operations, but when a function is called, the integer registers are
   used.

-  Hard ABI. The FPU is accessed directly for simple operations, and
   FPU-specific registers are used when a function is called, for both
   parameters and the return value.

It is important to note that code compiled with a particular ABI might
not be compatible with code compiled with another ABI. MicroEJ modules,
including the MicroEJ core engine, use the hard ABI.


.. _appendix_matrixcapabilities:

Supported MicroEJ core engine Capabilities by Architecture Matrix
=================================================================

The following table lists the supported MicroEJ core engine capabilities
by MicroEJ architectures.

.. table:: Supported MicroEJ core engine Capabilities by MicroEJ
architecture Matrix

   +-----------------+------------------------+-------------+-------------+--------------+
   | MicroEJ core engine Architectures        | Capabilities                             |
   +-----------------+------------------------+-------------+-------------+--------------+
   | MCU             | Compiler               | Single      | Tiny        | Multi        |
   |                 |                        | application | application | applications |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M0+  | IAR Embedded Workbench | YES         | YES         | NO           |
   |                 | for ARM                |             |             |              |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M4   | IAR Embedded Workbench | YES         | YES         | YES          |
   |                 | for ARM                |             |             |              |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M4   | GCC                    | YES         | NO          | YES          |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M4   | Keil uVision           | YES         | NO          | YES          |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M7   | Keil uVision           | YES         | NO          | YES          |
   +-----------------+------------------------+-------------+-------------+--------------+


ARM Cortex-M0+
==============

.. table:: ARM Cortex-M0+ Compilers

   +---------------------+-----------+-----------------------------------+
   | Compiler            | Version   | Flags and Options                 |
   +=====================+===========+===================================+
   | IAR C/C++ Compiler  | 7.        | ``--cpu Cortex-M0+ --fpu None``   |
   | for ARM             | 40.3.8902 |                                   |
   +---------------------+-----------+-----------------------------------+


ARM Cortex-M4
=============

.. table:: ARM Cortex-M4 Compilers

   +---------------------+-------------+-------------------------------------+
   | Compiler            | Version     | Flags and Options                   |
   +=====================+=============+=====================================+
   | Keil uVision        | 5.18.0.0    | ``--cpu Cortex-M4.fp --apcs=/hardfp |
   |                     |             | --fpmode=ieee_no_fenv``             |
   +---------------------+-------------+-------------------------------------+
   | GCC                 | 4.8         | ``-mabi=aapcs -mcpu=cortex-m4       |
   |                     |             | -mlittle-endian -mfpu=fpv4-sp-d16   |
   |                     |             | -mfloat-abi=hard -mthumb``          |
   +---------------------+-------------+-------------------------------------+
   | IAR Embedded        | 7.40.3.8938 | ``--cpu Cortex-M4F --fpu VFPv4_sp`` |
   | Workbench for ARM   |             |                                     |
   +---------------------+-------------+-------------------------------------+

Note: Since MicroEJ 4.0, Cortex-M4 architectures are compiled using
``hardfp`` convention call.


ARM Cortex-M7
=============

.. table:: ARM Cortex-M7 Compilers

   +-------------------+----------+----------------------------------------+
   | Compiler          | Version  | Flags and Options                      |
   +===================+==========+========================================+
   | Keil uVision      | 5.18.0.0 | ``--cpu Cortex-M7.fp.sp                |
   |                   |          | --apcs=/hardfp --fpmode=ieee_no_fenv`` |
   +-------------------+----------+----------------------------------------+


IAR Linker Specific Options
===========================

This section lists options that must be passed to IAR linker for
correctly linking the MicroEJ object file (``microejapp.o``) generated
by the Smart Linker.

``--no_range_reservations``
---------------------------

MicroEJ Smart Linker generates ELF absolute symbols to define some
link-time options (0 based values). By default, IAR linker allocates a 1
byte section on the fly, which may cause silent sections placement side
effects or a section overlap error when multiple symbols are generated
with the same absolute value:

``Error[Lp023]: absolute placement (in [0x00000000-0x000000db]) overlaps with absolute symbol […]``

The option ``--no_range_reservations`` tells IAR linker to manage an
absolute symbol as described by the ELF specification.

``--diag_suppress=Lp029``
-------------------------

MicroEJ Smart Linker generates internal veneers that may be interpreted
as illegal code by IAR linker, causing the following error:

``Error[Lp029]: instruction validation failure in section "C:\xxx\microejapp.o[.text.__icetea__virtual___1xxx#1126]": nested IT blocks. Code in wrong mode?``

The option ``--diag_suppress=Lp029`` tells IAR linker to ignore
instructions validation errors.
