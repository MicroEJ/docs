.. _section_vg_font:

====
Font
====

Principle
=========

The Font module contains the C part of the MicroVG implementation, which manages vectorial fonts.
This module is composed of two elements: 

* an implementation of Abstraction Layer APIs to manipulate font files,
* an implementation of Abstraction Layer APIs for MicroVG drawings.

.. _section_vg_font_implementation:

Functional Description
======================

The Font module implements the MicroVG `VectorFont`_ framework. 
It provides Abstraction Layer APIs that consist of opening and decoding a font file and getting the font's characteristics. 

A font file:

* is either a TTF or an OTF,
* is identified by the resource name,
* can be stored as internal resource or external (see :ref:`chapter.microej.applicationResources`).

No data is stored in the Java heap. 
The implementation is responsible for the font's cycle life: allocation and release.

A font is used to draw a string with a color or with a :ref:`linear gradient<section_vg_gradient>`.

.. _VectorFont: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorFont.html

.. _section_vg_font_llapi:

Abstraction Layer API
=====================

There are two separate Abstraction Layer API header files (see :ref:`LLVG-FONT-API-SECTION`):

* ``LLVG_FONT_impl.h`` specifies the Abstraction Layer APIs used to open and retrieve the font's characteristics.
* ``LLVG_PAINTER_impl.h`` lists the Abstraction Layer APIs called by  `VectorGraphicsPainter`_ to draw a string with the font.

.. figure:: images/vg_llapi_font.*
   :alt: MicroVG Font Abstraction Layer
   :width: 400px
   :align: center

   Font Abstraction Layer API

* MicroVG library calls the BSP functions through the header files ``LLVG_FONT_impl.h`` and ``LLVG_PAINTER_impl.h``.
* The :ref:`C module MicroVG <section_vg_c_module_microvg>` provides a default implementation of ``LLVG_FONT_impl.h`` over Freetype.
* This C module also provides an implementation of ``LLVG_PAINTER_impl.c`` that synchronizes the drawing with the MicroUI Graphics Engine and redirects the drawing itself to a third-party drawer.
* A C module dedicated to a GPU provides an implementation of this drawer. It also redirects the :ref:`complex layout <section_vg_font_complex>` to a third party C module. 
* The drawer also manages the :ref:`section_vg_gradient`.
* The :ref:`C module Harfbuzz <section_vg_c_module_microvg>` provides an implementation of :ref:`complex layout <section_vg_font_complex>`.
* These files are automatically copied in the BSP project when fetching the C modules during the platform build.

.. _VectorGraphicsPainter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorGraphicsPainter.html

Use
===

The MicroVG Font APIs are available in the class ``ej.microvg.`` `VectorFont`_.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
