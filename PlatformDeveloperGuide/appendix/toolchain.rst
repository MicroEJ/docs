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
CPAR in the ``SystemInit()`` function. Even if there is an FPU in the
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
including the MicroEJ Core Engine, use the hard ABI.


.. _appendix_matrixcapabilities:

Supported MicroEJ Core Engine Capabilities by Architecture Matrix
=================================================================

The following table lists the supported MicroEJ Core Engine capabilities
by MicroEJ Architectures.

.. tabularcolumns:: |p{2.5cm}|p{4cm}|p{2.7cm}|p{2.5cm}|p{2.7cm}|

.. table:: Supported MicroEJ Core Engine Capabilities by MicroEJ Architecture Matrix

   +-----------------+------------------------+-------------+-------------+--------------+
   | MicroEJ Core Engine Architectures        | Capabilities                             |
   +-----------------+------------------------+-------------+-------------+--------------+
   | MCU             | Compiler               | Single      | Tiny        | Multi        |
   |                 |                        | application | application | applications |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M0   | GCC                    | YES         | YES         | NO           |
   |                 |                        |             |             |              |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M4   | IAR Embedded Workbench | YES         | YES         | YES          |
   |                 | for ARM                |             |             |              |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M4   | GCC                    | YES         | NO          | YES          |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M4   | Keil uVision           | YES         | NO          | YES          |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M7   | IAR Embedded Workbench | YES         | NO          | YES          |
   |                 | for ARM                |             |             |              |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M7   | GCC                    | YES         | NO          | YES          |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M7   | Keil uVision           | YES         | NO          | YES          |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ESP32           | ESP-IDF                | YES         | NO          | YES          |
   +-----------------+------------------------+-------------+-------------+--------------+


ARM Cortex-M0
=============

.. list-table:: ARM Cortex-M0 Compilers
   :widths: 10 10 50 10
   :header-rows: 1

   * - Compiler
     - Version
     - Flags and Options
     - Module
   * - GCC
     - 4.8
     - ``-mabi=aapcs -mcpu=cortex-m0 -mlittle-endian -mthumb``
     - `flopi0G22 <https://repository.microej.com/architectures/com/microej/architecture/CM0/CM0_GCC48/flopi0G22/>`_

ARM Cortex-M4
=============

.. list-table:: ARM Cortex-M4 Compilers
   :widths: 10 10 50 10
   :header-rows: 1

   * - Compiler
     - Version
     - Flags and Options
     - Module
   * - Keil uVision
     - 5.18.0.0
     - ``--cpu Cortex-M4.fp --apcs=/hardfp --fpmode=ieee_no_fenv``
     - `flopi4A20 <https://repository.microej.com/architectures/com/microej/architecture/CM4/CM4hardfp_ARMCC5/flopi4A20/>`_
   * - GCC
     - 4.8
     - ``-mabi=aapcs -mcpu=cortex-m4 -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb``
     - `flopi4G25 <https://repository.microej.com/architectures/com/microej/architecture/CM4/CM4hardfp_GCC48/flopi4G25/>`_
   * - IAR Embedded Workbench for ARM
     - 8.32.1.18631
     - ``--cpu Cortex-M4F --fpu VFPv4_sp``
     - `flopi4I35 <https://repository.microej.com/architectures/com/microej/architecture/CM4/CM4hardfp_IAR83/flopi4I35/>`_

Note: Since MicroEJ 4.0, Cortex-M4 architectures are compiled using
``hardfp`` convention call.


ARM Cortex-M7
=============

.. list-table:: ARM Cortex-M7 Compilers
   :widths: 10 10 50 10
   :header-rows: 1

   * - Compiler
     - Version
     - Flags and Options
     - Module
   * - Keil uVision
     - 5.18.0.0
     - ``--cpu Cortex-M7.fp.sp --apcs=/hardfp --fpmode=ieee_no_fenv``
     - `flopi7A21 <https://repository.microej.com/architectures/com/microej/architecture/CM7/CM7hardfp_ARMCC5/flopi7A21/>`_
   * - GCC
     - 4.8
     - ``-mabi=aapcs -mcpu=cortex-m7 -mlittle-endian -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumbb``
     - `flopi7G26 <https://repository.microej.com/architectures/com/microej/architecture/CM7/CM7hardfp_GCC48/flopi7G26/>`_
   * - IAR Embedded Workbench for ARM
     - 8.32.1.18631
     - ``--cpu Cortex-M7 --fpu VFPv5_sp``
     - `flopi7I36 <https://repository.microej.com/architectures/com/microej/architecture/CM7/CM7hardfp_IAR83/flopi7I36/>`_

ESP32
=====

.. list-table:: Espressif ESP32 Compilers
   :widths: 10 10 50 10
   :header-rows: 1

   * - Compiler
     - Version
     - Flags and Options
     - Module
   * - GCC (ESP-IDF)
     - 5.2.0 (crosstool-NG crosstool-ng-1.22.0-80-g6c4433a)
     - ``-mlongcalls``
     - `simikou1 <https://repository.microej.com/architectures/com/microej/architecture/ESP32/GNUv52_xtensa-esp32/simikou1/>`_
   * - GCC (ESP-IDF)
     - 5.2.0 (crosstool-NG crosstool-ng-1.22.0-80-g6c4433a)
     - ``-mlongcalls -mfix-esp32-psram-cache-issue``
     - `simikou2 <https://repository.microej.com/architectures/com/microej/architecture/ESP32/GNUv52_xtensa-esp32-psram/simikou2/>`_


IAR Linker Specific Options
===========================

This section lists options that must be passed to IAR linker for
correctly linking the MicroEJ object file (``microejapp.o``) generated
by the SOAR.

``--no_range_reservations``
---------------------------

MicroEJ SOAR generates ELF absolute symbols to define some
link-time options (0 based values). By default, IAR linker allocates a 1
byte section on the fly, which may cause silent sections placement side
effects or a section overlap error when multiple symbols are generated
with the same absolute value:

``Error[Lp023]: absolute placement (in [0x00000000-0x000000db]) overlaps with absolute symbol […]``

The option ``--no_range_reservations`` tells IAR linker to manage an
absolute symbol as described by the ELF specification.

``--diag_suppress=Lp029``
-------------------------

MicroEJ SOAR generates internal veneers that may be interpreted
as illegal code by IAR linker, causing the following error:

``Error[Lp029]: instruction validation failure in section "C:\xxx\microejapp.o[.text.__icetea__virtual___1xxx#1126]": nested IT blocks. Code in wrong mode?``

The option ``--diag_suppress=Lp029`` tells IAR linker to ignore
instructions validation errors.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
