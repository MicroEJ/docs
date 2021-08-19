.. _architecture_naming_convention:

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

See :ref:`platform_configuration_creation` for usage.

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
