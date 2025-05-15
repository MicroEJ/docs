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
It provides Abstraction Layer APIs that consist in opening and decoding a font file and getting the font's characteristics. 

A font file:

* is either a TTF or an OTF,
* is identified by the resource name,
* can be stored as internal resource or external (see :ref:`vectorfont_external`).

No data is stored in the Managed heap. 
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
* The :ref:`C module MicroVG <section_vg_c_module_microvg>` provides a default implementation of ``LLVG_FONT_impl.h`` over FreeType. It also redirects the :ref:`complex layout <section_vg_font_complex>` to a third party C module. 
* This C module also provides an implementation of ``LLVG_PAINTER_impl.c`` that synchronizes the drawing with the MicroUI Graphics Engine and redirects the drawing itself to a third-party drawer through ``vg_drawing.h``.
* A C module dedicated to a GPU provides an implementation of this drawer (``vg_drawing_gpu.c``) that implements the drawings over the GPU library.
* The :ref:`C module Harfbuzz <section_vg_c_module_microvg>` provides an implementation of :ref:`complex layout <section_vg_font_complex>`.
* These files are automatically copied in the BSP project when fetching the C modules during the VEE Port build.

.. _VectorGraphicsPainter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorGraphicsPainter.html

.. _section_vg_font_external:

External Memory
===============

Principle
~~~~~~~~~

MicroVG does not provide some Low Level API to make the distinction between a font loaded from different kind of memories (internal or external, byte-addressable or not).
The Low Level implementation (:ref:`C Modules MicroVG and FreeType<section_vg_cco>`) features the font management from an external memory which is not byte-addressable when the VEE Port provides an implementation of the :ref:`section_externalresourceloader`.

Configuration File
~~~~~~~~~~~~~~~~~~

A Vector Font file is a *simple* resource.
To specify this resource as an external resource, the font file path must be listed in a ``.externresources.list`` file in addition with the ``.resources.list`` file (see :ref:`chapter.microej.applicationResources`).

Process
~~~~~~~

The following steps describe how to setup the loading of an external resource from the application:

1. Add the font to the application project resources (typically in the source folder ``src/main/resources`` and in the package ``fonts``).
2. Create / open the configuration files (e.g. ``application.resources.list`` and ``application.externresources.list``).
3. In both files, add the relative path of the font (e.g. ``/fonts/myFont.ttf``).
4. Build the application: the processed external resources are copied into the external resources folder (``[application_output_folder]/externalResources``).
5. Deploy the external resources to the external memory (SDCard, flash, etc.) of the device.
6. (optional) Configure the :ref:`section_externalresourceloader` to load from this source.
7. Build the application and run it on the device.
8. The application loads the external resource using `ej.microvg.VectorFont.loadFont()`_.
9. FreeType (:ref:`section_vg_cco`) recognizes this resource as external resource; it configures itself to manage this resource differently than an internal resource (see :ref:`section_vg_c_module_freetype` to have more details).
10. The application can use the font.

Simulation
~~~~~~~~~~

The Simulator automatically manages the external resources like internal resources.
All images listed in ``*.externresources.list`` files are copied in the external resources folder, and this folder is added to the Simulator's classpath.

Use
===

The MicroVG Font APIs are available in the class ``ej.microvg.`` `VectorFont`_.

.. _ej.microvg.VectorFont.loadFont(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorFont.html#loadFont-java.lang.String-

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
