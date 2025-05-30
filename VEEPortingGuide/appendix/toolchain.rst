.. _architectures_toolchains:

============================
Architectures MCU / Compiler
============================

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
including the Core Engine, use the hard ABI.


.. _appendix_matrixcapabilities:

Supported Core Engine Capabilities by Architecture Matrix
=========================================================

The following table lists the supported Core Engine capabilities
by MicroEJ Architectures.

.. tabularcolumns:: |p{2.5cm}|p{4cm}|p{2.7cm}|p{2.5cm}|p{2.7cm}|

.. table:: Supported Core Engine Capabilities by MicroEJ Architecture Matrix

   +-----------------+------------------------+-------------+-------------+--------------+
   | Core Engine Architectures                | Capabilities                             |
   +-----------------+------------------------+-------------+-------------+--------------+
   | MCU             | Compiler               | Mono-       | Tiny-       | Multi-       |
   |                 |                        | Sandbox     | Sandbox     | Sandbox      |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M0   | GCC                    | YES         | YES         | NO           |
   |                 |                        |             |             |              |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M33  | IAR Embedded Workbench | YES         | YES         | YES          |
   |                 | for ARM                |             |             |              |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARM Cortex-M33  | GCC                    | YES         | NO          | YES          |
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
   | ARMv7A   	     | GCC                    | YES         | YES         | YES          |
   +-----------------+------------------------+-------------+-------------+--------------+
   | ARMv7VE  	     | GCC                    | YES         | YES         | YES          |
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
     - `flopi0G22 <https://repository.microej.com/modules/com/microej/architecture/CM0/CM0_GCC48/flopi0G22/>`__

ARM Cortex-M33
==============

MicroEJ supports Cortex-M33 core with DSP extension using :ref:`Cortex-M4 architectures <architectures_toolchains_cm4>`.


.. _architectures_toolchains_cm4:

ARM Cortex-M4
=============

.. list-table:: ARM Cortex-M4 Compilers
   :widths: 10 10 30 50 10
   :header-rows: 1

   * - Compiler
     - Build Version
     - Known Compatible Versions
     - Flags and Options
     - Module
   * - Keil uVision
     - 5.18.0.0
     - 5.x
     - ``--cpu Cortex-M4.fp --apcs=/hardfp --fpmode=ieee_no_fenv``
     - `flopi4A20 <https://repository.microej.com/modules/com/microej/architecture/CM4/CM4hardfp_ARMCC5/flopi4A20/>`__
   * - GCC
     - 4.8
     - 4.x, 5.x, 6.x, 7.x, 8.x, 9.x
     - ``-mabi=aapcs -mcpu=cortex-m4 -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb``
     - `flopi4G25 <https://repository.microej.com/modules/com/microej/architecture/CM4/CM4hardfp_GCC48/flopi4G25/>`__
   * - IAR Embedded Workbench for ARM
     - 8.32.1.18631
     - 8.x, 9.x
     - ``--cpu Cortex-M4F --fpu VFPv4_sp``
     - `flopi4I35 <https://repository.microej.com/modules/com/microej/architecture/CM4/CM4hardfp_IAR83/flopi4I35/>`__

.. note::
  
  -  Cortex-M4 architectures are compiled using ``hardfp`` convention call.

ARM Cortex-M7
=============

.. list-table:: ARM Cortex-M7 Compilers
   :widths: 10 10 30 50 10
   :header-rows: 1

   * - Compiler
     - Build Version
     - Known Compatible Versions
     - Flags and Options
     - Module
   * - Keil uVision
     - 5.18.0.0
     - 5.x
     - ``--cpu Cortex-M7.fp.sp --apcs=/hardfp --fpmode=ieee_no_fenv``
     - `flopi7A21 <https://repository.microej.com/modules/com/microej/architecture/CM7/CM7hardfp_ARMCC5/flopi7A21/>`__
   * - GCC
     - 4.8
     - 4.x, 5.x, 6.x, 7.x, 8.x, 9.x
     - ``-mabi=aapcs -mcpu=cortex-m7 -mlittle-endian -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumbb``
     - `flopi7G26 <https://repository.microej.com/modules/com/microej/architecture/CM7/CM7hardfp_GCC48/flopi7G26/>`__
   * - IAR Embedded Workbench for ARM
     - 8.32.1.18631
     - 8.x, 9.x
     - ``--cpu Cortex-M7 --fpu VFPv5_sp``
     - `flopi7I36 <https://repository.microej.com/modules/com/microej/architecture/CM7/CM7hardfp_IAR83/flopi7I36/>`__

ARMv7A (ARMv7-A without integer division extension: Cortex-A5/Cortex-A8/Cortex-A9)
================================================================================================

.. list-table:: ARMv7A Compilers
   :widths: 10 10 30 50 10
   :header-rows: 1

   * - Compiler
     - Build Version
     - Known Compatible Versions
     - Flags and Options
     - Module
   * - GCC
     - 10.3
     - 4.x, 5.x, 6.x, 7.x, 8.x, 9.x, 10.x
     - ``-mabi=aapcs-linux -march=armv7-a -mlittle-endian -mfpu=vfp -mfloat-abi=hard -mthumb``
     - ``oliveARMv7A_2``

ARMv7VE (ARMv7-A with integer division extension: Cortex-A7/Cortex-A15)
=====================================================================================

.. list-table:: ARMv7VE Compilers
   :widths: 10 10 30 50 10
   :header-rows: 1

   * - Compiler
     - Build Version
     - Known Compatible Versions
     - Flags and Options
     - Module
   * - GCC
     - 10.3
     - 4.x, 5.x, 6.x, 7.x, 8.x, 9.x, 10.x
     - ``-mabi=aapcs-linux -march=armv7ve -mlittle-endian -mfpu=vfp -mfloat-abi=hard -mthumb``
     - ``oliveARMv7VE_1``

ESP32
=====

.. list-table:: Espressif ESP32 Compilers
   :widths: 10 10 50 10 20
   :header-rows: 1

   * - Compiler
     - Version
     - Flags and Options
     - Module Name
     - Module Version
   * - GCC (ESP-IDF)
     - 5.2.0 (crosstool-ng-1.22.0-80-g6c4433a)
     - ``-mlongcalls``
     - `simikou1 <https://repository.microej.com/modules/com/microej/architecture/ESP32/GNUv52_xtensa-esp32/simikou1/>`__
     - Any
   * - GCC (ESP-IDF)
     - 5.2.0 (crosstool-ng-1.22.0-80-g6c4433a)
     - ``-mlongcalls -mfix-esp32-psram-cache-issue``
     - `simikou2 <https://repository.microej.com/modules/com/microej/architecture/ESP32/GNUv52_xtensa-esp32-psram/simikou2/>`__
     - Up to ``7.13.0`` (included)
   * - GCC (ESP-IDF)
     - 5.2.0 (crosstool-ng-1.22.0-96-g2852398)
     - ``-mlongcalls -mfix-esp32-psram-cache-issue``
     - `simikou2 <https://repository.microej.com/modules/com/microej/architecture/ESP32/GNUv52b96_xtensa-esp32-psram/simikou2/>`__
     - ``7.12.2`` or higher
   * - GCC (ESP-IDF)
     - 8.2.0 (crosstool-NG esp-2019r2)
     - ``-mlongcalls``
     - `simikou3 <https://repository.microej.com/modules/com/microej/architecture/ESP32/GNUv82_xtensa-esp32s2/simikou3/>`__
     - ``7.16.0`` or higher
   * - GCC (ESP-IDF)
     - 5.2.0 (crosstool-ng-1.22.0-97-gc752ad5)
     - ``-mlongcalls -mfix-esp32-psram-cache-issue``
     - ``simikou4``
     - ``7.12.2`` or higher
   * - GCC (ESP-IDF)
     - 8.4.0 (crosstool-NG esp-2021r1)
     - ``-mlongcalls``
     - ``simikou5``
     - ``7.16.1`` or higher
   * - GCC (ESP-IDF)
     - 8.4.0 (crosstool-NG esp-2021r1)
     - ``-mlongcalls -mfix-esp32-psram-cache-issue -mfix-esp32-psram-cache-strategy=memw``
     - `simikou6 <https://repository.microej.com/architectures/com/microej/architecture/ESP32/GNUv84_xtensa-esp32-psram/simikou6/>`__
     - ``7.16.1`` or higher
   * - GCC (ESP-IDF)
     - 11.2.0 (crosstool-NG esp-2022r1)
     - ``-mlongcalls``
     - `simikou7 <https://repository.microej.com/architectures/com/microej/architecture/ESP32/GNUv112_xtensa-esp32s3/simikou7/>`__
     - ``7.20.1`` or higher
     
.. _toolchain_iar:

IAR Linker Specific Options
===========================

This section lists options that must be passed to IAR linker for
correctly linking the MicroEJ object file (``microejapp.o``) generated
by the SOAR.

``--no_range_reservations``
---------------------------

MicroEJ SOAR generates ELF absolute symbols to define some
:ref:`link_time_option` (0 based values). By default, IAR linker allocates a 1
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

.. _toolchain_gcc:

GNU LD Specific Options
=======================

``--start-group --end-group``
-----------------------------

By default the GNU linker does not search unresolved symbols in previously loaded files and can cause undefined reference errors.
To solve this issue, either change the load order of libraries (put ``microejapp.o`` first) or guard the libraries with the
options ``--start-group`` and ``--end-group``.

.. _toolchain_armcc:

ARM Linker Specific Options
===========================

ARM linker (``armlink``) is the linker included in ARM Compiler and Keil MDK-ARM development tools.

Fix Unexpected Undefined Symbol
-------------------------------

The ARM linker requires to resolve all symbols before detecting some that are not transitively required for linking the Executable. 
This typically happen when linking ELF object files containing dead code or debug functions that are compiled but not intended to be linked.
If such functions refer to unresolved symbols, you may need to define a fake symbol to make the linker happy.
You can declare it in your BSP project or directly in your VEE Port as following:

- Create a file ``MICROJVM/link/armlink-weak.lscf`` in the :ref:`dropins <platformCustomization>` directory of your VEE Port configuration project.
- Edit the file and declare as many symbols as required. See also the :ref:`microej_linker` chapter for more details on the MicroEJ linker file syntax.
  
  .. code-block:: xml

    <lscFragment>
      <defSymbol name="[symbolName]" value="0" rootSymbol="true" weak="true"/>
    </lscFragment>

The weak symbol(s) will be directly defined in the application object file (``microejapp.o``).

.. _soar_debug_infos_post_linker:

Link the SOAR Debug Section
---------------------------

When building an Application, the :ref:`SOAR <soar>` generates a dedicated ELF debug section named ``.debug.soar`` in the application object file (``microejapp.o``).
This section is used by debug tools such as the :ref:`Stack Trace Reader <stack_trace_reader>` or the :ref:`Heap Dumper <heapdumper>`.
It is also used by the SOAR itself for :ref:`building Features <build_feature_off_board>` on a Kernel.

Unfortunately, the ARM linker does not link this section in the output ELF executable, even with debug mode enabled.
If you try to load the raw executable produced by the ARM linker, the tools will fail with a `no debug section` error.
Here is an example with the :ref:`stack_trace_reader`:

.. code-block:: console

  =============== [ MicroEJ Core Engine Trace ] ===============
  [INFO] Paste the MicroEJ core engine stack trace here.
  1 : PROXY ERROR
    [M8] - The file XXX is not a valid image file or has no debug informations (can't read file: XXX (no debug section)).

To be able to use debug tools, the debug section must be manually linked and injected in the Executable.
This is done using the `SOAR debug infos post-linker` :ref:`tool <MicroEJToolsSection>`.

.. figure:: ../images/soarDebugInfosPostLinker-tabExecution.png
   :align: center
   :scale: 100%

   SOAR debug infos post-linker tool Selection

This tool takes two file options:

- ``soar.object.file``: the internal object file produced by the SOAR when building the Application. It can be found in the :ref:`Launch Output Folder <application_output_folder>` at ``soar/[application_main_class].o``.
- ``output.executable.file``: the Executable file produced by the ARM linker that includes the linked Application.

.. figure:: ../images/soarDebugInfosPostLinker-tabConfiguration.png
   :align: center
   :scale: 100%

   SOAR debug infos post-linker tool Configuration

Once executed, it produces a new Executable file beside the original one with the ``.microej`` extension suffix

.. code-block:: console

    =============== [ SOARDebugInfosPostLinker ] ===============
    Successfully generated c:\myExecutable.axf.microej.

    SUCCESS

This file now contains the linked ``.debug.soar`` section so that it can be used by the debug tools.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
