.. _pack_overview:

=============
MicroEJ Packs
=============

Overview
============

On top of a MicroEJ Architecture can be imported MicroEJ Packs which provide additional features such as:

-  :ref:`Serial Communications <pack_ecom_comm>`,
-  :ref:`Graphical User Interface <pack_gui>`,
-  :ref:`Networking <pack_net>`,
-  :ref:`File System <pack_fs>`,
-  etc.

Each MicroEJ Pack is optional and can be selected on demand during the
:ref:`MicroEJ Platform configuration <platform_configuration_creation>` step.

Naming Convention
=================

MicroEJ Packs are distributed in two packages:

- MicroEJ Architecture Specific Pack under the `com/microej/architecture/*`_ organization.
- MicroEJ Generic Pack under the `com/microej/pack/*`_ organization.

See :ref:`pack_import` for usage.

.. _com/microej/architecture/*: https://repository.microej.com/modules/com/microej/architecture
.. _com/microej/pack/*: https://repository.microej.com/modules/com/microej/pack/

.. _pack_architecture_specific:

Architecture Specific Pack
--------------------------

MicroEJ Architecture Specific Packs contain compiled libraries
archives and are thus dependent on the MicroEJ Architecture and
toolchain used in the MicroEJ Platform.

MicroEJ Architecture Specific Packs files ends with the ``.xpfp``
extension and are classified using the following naming convention:

::

   com/microej/architecture/[ISA]/[TOOLCHAIN]/[UID]-[NAME]-pack/[VERSION]/[UID]-[NAME]-pack-[VERSION].xpfp

- ``ISA``: instruction set architecture (e.g. ``CM4`` for Arm® Cortex®-M4, ``ESP32`` for Espressif ESP32, ...).
- ``TOOLCHAIN``: C compilation toolchain (e.g. ``CM4hardfp_GCC48``).
- ``UID``: Architecture unique ID (e.g. ``flopi4G25``).
- ``NAME``: pack name (e.g. ``ui``).
- ``VERSION``: pack version (e.g. ``13.0.4``).

For example, MicroEJ Architecture Specific Pack UI versions for Arm®
Cortex®-M4 microcontrollers compiled with GNU CC toolchain are
available at
https://repository.microej.com/modules/com/microej/architecture/CM4/CM4hardfp_GCC48/flopi4G25-ui-pack/.

.. _pack_generic:

Generic Pack
------------

MicroEJ Generic Packs can be imported on top of any MicroEJ Architecture.

They are classified using the following naming convention:

::

   com/microej/pack/[NAME]/[NAME]-pack/[VERSION]/

- ``NAME``: pack name (e.g. ``bluetooth``).
- ``VERSION``: pack version (e.g. ``2.1.0``).

For example, MicroEJ Generic Pack Bluetooth versions are available at
https://repository.microej.com/modules/com/microej/pack/bluetooth/bluetooth-pack/.

.. _pack_generic_legacy:

Legacy Generic Pack
~~~~~~~~~~~~~~~~~~~

Legacy MicroEJ Generic Packs files end with the ``.xpfp`` extension.
These Packs contain one or more Platform modules. See :ref:`platform_module_configuration` for their configuration.  
They are classified using the following naming convention:

::
   
   com/microej/pack/[NAME]/[VERSION]/[NAME]-[VERSION].xpfp

- ``NAME``: pack name (e.g. ``net``).
- ``VERSION``: pack version (e.g. ``9.2.3``).

For example, the Legacy MicroEJ Generic Pack NET version ``9.2.3`` is
available at https://repository.microej.com/modules/com/microej/pack/net/9.2.3/net-9.2.3.xpfp.


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
