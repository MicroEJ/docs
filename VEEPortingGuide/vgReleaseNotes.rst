.. include:: uiReplaces.rst

.. _section_vg_releasenotes:

=============
Release Notes
=============

UI Pack Compatibility Version
=============================

The current VG Pack version is |VGPACKVERSION|.
The following table describes the compatibility ranges between VG and UI Packs. 

+---------------+-----------------+----------------------------------+
| VG Pack Range | UI Pack Range   | Comment                          |
+===============+=================+==================================+
| [1.5.0-1.5.1] | [14.0.0-15.0.0[ | UI Pack major version            |
+---------------+-----------------+----------------------------------+
| [1.3.0-1.4.2] | [13.5.0-14.0.0[ | BufferedImage with custom format |
+---------------+-----------------+----------------------------------+
| [1.1.0-1.2.1] | [13.3.0-14.0.0[ | Internal feature                 |
+---------------+-----------------+----------------------------------+
| [1.0.0-1.0.1] | [13.2.0-14.0.0[ |                                  |
+---------------+-----------------+----------------------------------+

.. _section_vg_api:

Foundation Libraries
====================

The following table describes Foundation Libraries API versions implemented in MicroEJ VG Packs.

.. list-table:: MicroVG API Implementation
   :widths: 20 10
   :header-rows: 1

   * - VG Pack Range
     - MicroVG
   * - [1.4.0-1.5.1]
     - `1.4.0 <https://repository.microej.com/modules/ej/api/microvg/1.4.0/>`_
   * - 1.3.0
     - `1.3.0 <https://repository.microej.com/modules/ej/api/microvg/1.3.0/>`_
   * - 1.2.1
     - `1.2.0 <https://repository.microej.com/modules/ej/api/microvg/1.2.0/>`_
   * - 1.1.0
     - `1.1.0 <https://repository.microej.com/modules/ej/api/microvg/1.1.0/>`_
   * - [1.0.0-1.0.1]
     - 1.0.0

C Modules Compatibility Version
===============================

The C modules are described :ref:`here <section_vg_cco>`.

Several generic C modules are available for a given version of the VG Pack.
In addition to generic C modules, the specific implementation of the VG Pack over Vivante VGLite depends on:

* the UI Pack (see upper),
* the UI Pack C module: see :ref:`UI Pack <section_display_llapi>`,
* and by consequence, the specific C module MicroUI over VGLite: see :ref:`section_ui_c_module_microui_vglite`.

The following table describes the compatibility ranges between the VG Packs and the C modules (generic and specific):

+---------------+---------+----------+----------+----------------+----------------+
| VG Pack       | MicroVG | FreeType | Harfbuzz | MicroUI-VGLite | MicroVG-VGLite |
+===============+=========+==========+==========+================+================+
| 1.5.1         | 5.0.0   | 2.0.2    | 1.0.2    | [8.0.0-8.0.1]  | 7.0.1          |
+---------------+---------+----------+----------+----------------+----------------+
| 1.5.0         | 5.0.0   | 2.0.2    | 1.0.2    | [8.0.0-8.0.1]  | 7.0.0          |
+---------------+---------+----------+----------+----------------+----------------+
| 1.4.2         | 4.0.0   | 2.0.2    | 1.0.2    | 7.2.0          | 6.1.1          |
+---------------+---------+----------+----------+----------------+----------------+
| [1.4.0-1.4.1] | 3.0.1   | 2.0.2    | 1.0.2    | [7.0.0-7.1.0]  | [6.0.0-6.1.0]  |
+---------------+---------+----------+----------+----------------+----------------+
| 1.3.0         | 3.0.0   | 2.0.2    | 1.0.2    | 6.0.1          | 5.0.1          |
+---------------+---------+----------+----------+----------------+----------------+
| [1.2.0-1.2.1[ | 2.1.0   | 2.0.2    | 1.0.2    | 5.0.1          | 4.0.4          |
+---------------+---------+----------+----------+----------------+----------------+
| [1.1.0-1.1.1[ | 2.0.0   | 2.0.2    | 1.0.2    | 3.0.0          | 3.0.2          |
+---------------+---------+----------+----------+----------------+----------------+
| [1.0.0-1.1.0[ | n/a     | n/a      | n/a      | n/a            | n/a            |
+---------------+---------+----------+----------+----------------+----------------+

.. note:: The C module ``MicroVG over VGLite`` fetches automatically by transitivity the other C modules. No need to fetch explicitly the different modules (except the C module ``Harfbuzz``). An update of this C module also updates (if necessary) the other C modules.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
