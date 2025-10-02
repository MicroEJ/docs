.. _section_vg_low_level:

=====================
Abstraction Layer API
=====================

Principle
=========

The MicroVG implementation for MicroEJ requires an Abstraction Layer implementation.
The Abstraction Layer implementation consists of a set of header files to implement in C to target the hardware drivers.

The VG Pack's embedded Front Panel extension implements all MicroVG features for the simulator.

Embedded VEE Port
=================

.. figure:: images/vg_llapi_emb.*
   :alt: MicroVG Abstraction Layer
   :width: 100.0%
   :align: center

   MicroVG Embedded Abstraction Layer API

The specification of header files names is:

- Name starts with ``LLVG_``.
- Second part's name refers to the VG engine: ``MATRIX``, ``PATH``, ``GRADIENT``, ``BVI`` (image), ``FONT``.
- All file's name ends with ``_impl``:  all functions must be implemented over hardware or in software.

A *master* header file initializes the native Vector Graphics engine: see :ref:`LLVG-API-SECTION`.
All other header files and their aims are described in next VG engines chapters:  :ref:`Matrix<section_vg_matrix_llapi>`, :ref:`Path<section_vg_path_llapi>`, :ref:`Gradient<section_vg_gradient_llapi>`, :ref:`Image<section_vg_image_llapi>` and :ref:`Font<section_vg_font_llapi>`.

Simulator
=========

.. figure:: images/vg_llapi_sim.*
   :alt: MicroVG Abstraction Layer
   :width: 70.0%
   :align: center

   MicroVG Simulator Abstraction Layer API

The Simulator's five VG engines are grouped in a :ref:`Front Panel extension <section_ui_simulation>`.

This engine provides the compatibility with Vivante VGLite and Think Silicon Nema VG GPUs and it can be extended to fit another GPU.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.
