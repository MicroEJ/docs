.. _architecture_overview:

====================
MicroEJ Architecture
====================

Overview
============

MicroEJ Architecture features the MicroEJ Core Engine built for a specific instructions set (ISA) and compiler.

The MicroEJ Core Engine is a tiny and fast runtime associated with a Scheduler and a Garbage Collector. 

MicroEJ Architecture provides implementations of the following Foundation Libraries :

-  `EDC <https://repository.microej.com/modules/ej/api/edc/>`_: Embedded Device Configuration.
-  `BON <https://repository.microej.com/modules/ej/api/bon/>`_ Beyond Profile (see :ref:`[BON] <esr-specifications>`).
-  `SNI <https://repository.microej.com/modules/ej/api/sni/>`_ Simple Native Interface (:ref:`[SNI] <esr-specifications>`).
-  `SP <https://repository.microej.com/modules/ej/api/sni/>`_ Shielded Plug (:ref:`[SP] <esr-specifications>`).
-  `KF <https://repository.microej.com/modules/ej/api/sni/>`_ Kernel & Features (:ref:`[KF] <esr-specifications>`).

:ref:`The following figure <fig_jpf-runtime-components>` shows the components involved.

.. _fig_jpf-runtime-components:
.. figure:: images/jpf-runtime-components.*
   :alt: MicroEJ Architecture Runtime Modules: Tools, Libraries and APIs
   :align: center
   :scale: 75%

   MicroEJ Architecture Modules

Three Low Level APIs allow the MicroEJ Architecture to link with (and port
to) external code, such as any kind of RTOS or legacy C libraries: 

-  Simple Native Interface (see :ref:`[SNI] <esr-specifications>`)
-  Low Level MicroEJ Core Engine (see :ref:`LLMJVM <LLMJVM-API-SECTION>`)
-  Low Level Shielded Plug (see :ref:`LLSP <LLSP-API-SECTION>`)

Naming Convention
=================

MicroEJ Architecture files ends with the ``.xpf`` extension, and are classified using the following naming convention:

:: 

  com/microej/architecture/[ISA]/[TOOLCHAIN]/[UID]/[VERSION]/[UID]-[VERSION]-[USAGE].xpf

- ``ISA``: instruction set architecture (e.g. ``CM4`` for Arm® Cortex®-M4, ``ESP32`` for Espressif ESP32, ...).
- ``TOOLCHAIN``: C compilation toolchain (e.g. ``CM4hardfp_GCC48``).
- ``UID``: Architecture unique ID (e.g. ``flopi4G25``).
- ``VERSION``: module version (e.g. ``7.12.0``).
- ``USAGE`` = ``eval`` for evaluation Architectures, ``prod`` for production Architectures.

For example, MicroEJ Architecture versions for Arm® Cortex®-M4 microcontrollers compiled with GNU CC toolchain are available at
https://repository.microej.com/modules/com/microej/architecture/CM4/CM4hardfp_GCC48/flopi4G25/.

See :ref:`architecture_import` for usage.

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
