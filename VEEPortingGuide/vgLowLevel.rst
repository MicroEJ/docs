.. _section_vg_low_level:

=============
Low-Level API
=============

Principle
=========

The MicroVG implementation for MicroEJ requires a Low-Level implementation. 
The Low-Level implementation consists of a set of header files to implement in C to target the hardware drivers.

The VG Pack's embedded Front Panel extension implements all MicroVG features for the simulator.

Embedded Platform
=================

.. figure:: images/vg_llapi_emb.*
   :alt: MicroVG Low Level
   :width: 70.0%
   :align: center

   MicroVG Embedded Low-Level API

The specification of header files names is:

- Name starts with ``LLVG_``.
- Second part's name refers to the VG engine: ``MATRIX``, ``PATH``, ``GRADIENT``, ``FONT``.
- All file's name ends with ``_impl``:  all functions must be implemented over hardware or in software.

A *master* header file initializes the native Vector Graphics engine: see :ref:`LLVG-API-SECTION`.
All other header files and their aims are described in next VG engines chapters:  :ref:`Matrix<section_vg_matrix_llapi>`, :ref:`Path<section_vg_path_llapi>`, :ref:`Gradient<section_vg_gradient_llapi>` and :ref:`Font<section_vg_font_llapi>`.

Simulator
=========

.. figure:: images/vg_llapi_sim.*
   :alt: MicroVG Low Level
   :width: 70.0%
   :align: center

   MicroVG Simulator Low-Level API

The Simulator's four VG engines are grouped in a :ref:`Front Panel extension <section_ui_simulation>`. 

.. note:: The current implementation is built-in in the VG Pack and is only compatible with the i.MX RT595 MCU (see :ref:`VG Pack note<pack_vg>`).

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
