.. _section_vg_font:

====
Font
====

Principle
=========

The Font module contains the C part of the MicroVG implementation which manages fonts.
This module is composed of two elements: 

* an implementation of Low Level APIs to manipulate font files,
* an implementation of Low Level APIs for MicroVG drawings.

.. _section_vg_font_implementation:

Functional Description
======================

The Font module implements the MicroVG `VectorFont <zzz_javadocurl_zzz/ej/microvg/VectorFont.html>`_ framework. 
It provides Low Level APIs that consist to open and decode a font file and to get font's characteristics. 

A font file:

* is either a TTF or an OTF,
* is identified by the resource name,
* can be stored as internal resource or external (see :ref:`chapter.microej.applicationResources`).

No data is stored in the Java heap . 
The implementation is responsible about font's cycle life: allocation and release.

A font is used to draw a string with a color or with a :ref:`linear gradient<section_vg_gradient>`.

.. _section_vg_font_llapi:

Low Level API
=============

There are two distinct Low Level API header files (see :ref:`LLVG-FONT-API-SECTION`):

* ``LLVG_FONT_impl.h`` specifies the Low Level APIs used to open and retrieve font's characteristics.
* ``LLVG_FONT_PAINTER_impl.h`` lists the Low Level APIs called by  `VectorGraphicsPainter <zzz_javadocurl_zzz/ej/microvg/VectorGraphicsPainter.html>`_ to draw a string with the font.

.. figure:: images/vg_llapi_font.*
   :alt: MicroVG Font Low Level
   :width: 200px
   :align: center

   Font Low Level API

Use
===

The MicroVG Font APIs are available in the class `ej.microvg.VectorFont <zzz_javadocurl_zzz/ej/microvg/VectorFont.html>`_.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
