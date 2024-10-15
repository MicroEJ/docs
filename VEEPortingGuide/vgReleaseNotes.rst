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
| 1.7.0         | 14.1.1          | MicroUI Font extensibility       |
+---------------+-----------------+----------------------------------+
| [1.5.0-1.6.0] | [14.0.0-15.0.0[ | UI Pack major version            |
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

.. XXX_TODO link

.. list-table:: MicroVG API Implementation
   :widths: 20 10
   :header-rows: 1

   * - VG Pack Range
     - MicroVG
   * - 1.7.0
     - `1.5.0 <https://repository.microej.com/modules/ej/api/microvg/1.4.0/>`_
   * - [1.4.0-1.6.0]
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
In addition to generic C modules, the specific implementations of the VG Pack over Vivante VGLite and Think Silicon NemaVG extend the main MicroVG C module.
They override the default implementation to use a GPU to perform the drawings.
Contrary to the main MicroVG C module, they are optional: when they are not available, the default implementation of drawings is used.
The default implementation does nothing (no drawing) and throws the :ref:`drawing log<section.veeport.ui.drawings.drawing_logs>` ``DRAWING_LOG_NOT_IMPLEMENTED``.

These C Modules fetches automatically by transitivity the generic MicroUI and MicroVG C modules and the :ref:`Extended C Module<section_ui_releasenotes_cmodule_extended>` for the selected GPU.

The next tables summarizes the VG Packs with:

* the UI Pack (see upper),
* the specific C module that implements MicroVG over the GPU (called ``VG-xxx`` in next tables),
* the specific C module that implements MicroUI over the GPU (called ``UI-xxx`` in next tables), see :ref:`section_ui_releasenotes_cmodule_extended`,
* the VG Pack C module,
* the UI Pack C module: see :ref:`UI Pack <section_display_llapi>`,
* Freetype and HarfBuzz

.. warning:: Compatible versions are more restrictive than for use of the UI pack (and its C modules) alone.

**Vivante VGLite**

The :ref:`VGLite C module <section_vg_c_module_microvg_vglite>` targets the NXP CPU that provides the Vivante VGLite accelerator.

The following table describes the version compatibility between the MicroEJ VG Packs, the UI Packs, the generic C modules and the VGLite C modules:

+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| VG Pack       | UI Pack         | VG-VGLite     | UI-VGLite | MicroVG C Module | MicroUI C Module | FreeType      | HarfBuzz      | Comment                    |
+===============+=================+===============+===========+==================+==================+===============+===============+============================+
| [1.5.0-1.7.0] | 14.1.1          | 9.0.0         | 10.0.0    | 7.0.0            | 14.1.1           | [3.0.0-4.0.0] | [2.0.0-3.0.0] | MicroUI Font extensibility |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| 1.6.0         | [14.0.1-14.0.2] | 8.0.1         | 9.0.0     | 6.0.1            | 4.1.0            | [3.0.0-4.0.0] | [2.0.0-3.0.0] | VG Pack extensibility      |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| 1.5.1         | [14.0.0-14.0.2] | 7.0.1         | 8.0.1     | 5.0.0            | 4.0.1            | 2.0.2         | 1.0.2         | Scissor issue              |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| 1.5.0         | [14.0.1-14.0.2] | 7.0.1         | 8.0.1     | 5.0.0            | 4.0.1            | 2.0.2         | 1.0.2         | C modules harmonization    |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| 1.5.0         | 14.0.0          | 7.0.0         | 8.0.0     | 5.0.0            | 4.0.0            | 2.0.2         | 1.0.2         | UI Pack major version      |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| 1.4.2         | [13.7.0-13.7.2] | 6.1.1         | 7.2.0     | 4.0.0            | 3.1.1            | 2.0.2         | 1.0.2         | Very long paths            |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| [1.4.0-1.4.1] | [13.7.0-13.7.2] | [6.0.0-6.1.0] | 7.2.0     | 3.0.1            | 3.1.0            | 2.0.2         | 1.0.2         | Free image resources       |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| [1.4.0-1.4.1] | [13.5.1-13.6.2] | 6.1.0         | 7.1.0     | 3.0.1            | 3.0.0            | 2.0.2         | 1.0.2         | VGLite `3.0.15_rev7`       |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| 1.4.0         | [13.5.1-13.6.2] | 6.0.0         | 7.0.0     | 3.0.1            | 3.0.0            | 2.0.2         | 1.0.2         | Blend modes                |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| 1.3.0         | [13.5.1-13.6.2] | 5.0.1         | 6.0.1     | 3.0.0            | 3.0.0            | 2.0.2         | 1.0.2         | Buffered vector image      |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| 1.2.1         | [13.3.0-13.4.1] | 4.0.3         | 5.0.1     | 2.1.0            | 2.0.1            | 2.0.2         | 1.0.2         | Image raw format           |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+
| 1.1.1         | [13.3.0-13.4.1] | 3.0.2         | 3.0.0     | 2.0.0            | 2.0.0            | 2.0.2         | 1.0.2         |                            |
+---------------+-----------------+---------------+-----------+------------------+------------------+---------------+---------------+----------------------------+

**Think Silicon NemaGFX**

The :ref:`NemaVG C module <section_vg_c_module_microvg_nema>` targets the CPU that provides the NemaVG accelerator.

The following table describes the version compatibility between the MicroEJ VG Packs and the C modules:

+---------------+-----------------+-----------+---------+------------------+------------------+---------------+---------------+----------------------------+
| VG Pack       | UI Pack         | VG-NemaVG | UI-Nema | MicroVG C Module | MicroUI C Module | FreeType      | HarfBuzz      | Comment                    |
+===============+=================+===========+=========+==================+==================+===============+===============+============================+
| [1.6.0-1.7.0] | 14.1.1          | 2.0.0     | 4.0.0   | 7.0.0            | 14.1.1           | [3.0.0-4.0.0] | [2.0.0-3.0.0] | MicroUI Font extensibility |
+---------------+-----------------+-----------+---------+------------------+------------------+---------------+---------------+----------------------------+
| 1.6.0         | [14.0.1-14.0.2] | 1.0.1     | 3.0.0   | 6.0.1            | 4.1.0            | [3.0.0-4.0.0] | [2.0.0-3.0.0] |                            |
+---------------+-----------------+-----------+---------+------------------+------------------+---------------+---------------+----------------------------+

**FreeType**

The :ref:`FreeType C module <section_vg_c_module_freetype>` provides a fork of FreeType.

The following table describes the version of FreeType included in the C module:

+----------------+----------+
| C Module Range | FreeType |
+================+==========+
| 4.0.0          | 2.13.3   |
+----------------+----------+
| 3.0.0          | 2.11.0   |
+----------------+----------+

**HarfBuzz**

The :ref:`FreeType C module <section_vg_c_module_harfbuzz>` provides HarfBuzz with additional source files.

The following table describes the version of HarfBuzz included in the C module:

+----------------+----------+
| C Module Range | HarfBuzz |
+================+==========+
| 3.0.0          | 10.0.1   |
+----------------+----------+
| 2.0.0          | 4.2.1    |
+----------------+----------+

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.
