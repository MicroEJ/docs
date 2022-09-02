.. _section_vg_font:

====
Font
====

Principle
=========

The Font module contains the C part of the MicroVG implementation, which manages vectorial fonts.
This module is composed of two elements: 

* an implementation of Low-Level APIs to manipulate font files,
* an implementation of Low-Level APIs for MicroVG drawings.

.. _section_vg_font_implementation:

Functional Description
======================

The Font module implements the MicroVG `VectorFont <zzz_javadocurl_zzz/ej/microvg/VectorFont.html>`_ framework. 
It provides Low-Level APIs that consist of opening and decoding a font file and getting the font's characteristics. 

A font file:

* is either a TTF or an OTF,
* is identified by the resource name,
* can be stored as internal resource or external (see :ref:`chapter.microej.applicationResources`).

No data is stored in the Java heap. 
The implementation is responsible for the font's cycle life: allocation and release.

A font is used to draw a string with a color or with a :ref:`linear gradient<section_vg_gradient>`.

.. _section_vg_font_llapi:

Low-Level API
=============

There are two separate Low-Level API header files (see :ref:`LLVG-FONT-API-SECTION`):

* ``LLVG_FONT_impl.h`` specifies the Low-Level APIs used to open and retrieve the font's characteristics.
* ``LLVG_FONT_PAINTER_impl.h`` lists the Low-Level APIs called by  `VectorGraphicsPainter <zzz_javadocurl_zzz/ej/microvg/VectorGraphicsPainter.html>`_ to draw a string with the font.

.. figure:: images/vg_llapi_font.*
   :alt: MicroVG Font Low Level
   :width: 400px
   :align: center

   Font Low-Level API

* MicroVG library calls the BSP functions through the header files ``LLVG_FONT_impl.h`` and ``LLVG_FONT_PAINTER_impl.h``.
* The :ref:`C module MicroVG <section_vg_c_module_microvg>` provides a default implementation of ``LLVG_FONT_impl.h`` over Freetype.
* The :ref:`C module Freetype <section_vg_c_module_microvg>` provides an implementation of ``LLVG_FONT_PAINTER_impl.h`` over the Vivante VGLite library. It also redirects the :ref:`complex layout <section_vg_font_complex>` to a third party C module. 
* The drawer also manages the :ref:`section_vg_gradient`.
* The :ref:`C module Harfbuzz <section_vg_c_module_microvg>` provides an implementation of :ref:`complex layout <section_vg_font_complex>`.
* These files are automatically copied in the BSP project when fetching the C modules during the platform build.


Use
===

The MicroVG Font APIs are available in the class `ej.microvg.VectorFont <zzz_javadocurl_zzz/ej/microvg/VectorFont.html>`_.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
