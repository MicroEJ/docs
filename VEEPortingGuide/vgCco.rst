.. _section_vg_cco:

=========
C Modules
=========

Principle
=========

Several C modules implement the VG Pack's Abstraction Layer APIs.
Some are generic, and some are VEE Port dependent (more precisely: GPU dependent).
The generic modules provide header files to be extended by the specific modules.
The generic C modules are available on the :ref:`central_repository` and the specific C modules on the :ref:`developer_repository`.

The following picture illustrates the available C modules and their relations for an implementation that uses:

* FreeType library for the font renderer and the font layouter in simple layout mode.
* Harfbuzz library for the font layouter in complex layout mode.
* *GPU* library symbolizes the library for the drawing of vector paths over a GPU.

The following chapters explain the aim and relations of each C module.

.. note:: It is a simplified view: all sources and headers files of each C module are not visible.

.. figure:: images/vg_cco.*
   :alt: MicroVG C Modules
   :width: 100%
   :align: center

   MicroVG C Modules

UI Pack & MicroUI C Modules
===========================

The UI Pack provides a header file to implement the MicroUI drawings: ``LLUI_PAINTER_impl.h``.
See :ref:`section_ui_cco` chapter to have more information.

VG Pack
=======

The VG Pack provides a set of header files to implement the MicroVG concepts.
The header files are described in the dedicated chapters: :ref:`Matrix module <section_vg_matrix>`, :ref:`Path module <section_vg_path>`, :ref:`Gradient module <section_vg_gradient>`, :ref:`Image module <section_vg_image>` and :ref:`Font module <section_vg_font>`.

The VG Pack is an extension of the UI Pack.
The VG Pack's header files require the UI Pack's header files to manipulate the MicroUI concepts.
Consequently, the VG Pack must be installed on a VEE Port that fetches a UI Pack.

The VG Pack and its header files are available on the :ref:`central_repository`: `com.microej.pack.vg#vg-pack`_.

.. _com.microej.pack.vg#vg-pack: https://repository.microej.com/modules/com/microej/pack/vg/vg-pack/

.. _section_vg_c_module_microvg:

C Module: MicroVG
=================

Description
-----------

This generic C module provides an implementation of MicroVG concepts: matrix, path, gradient and font; respectively ``LLVG_MATRIX_impl.c``, ``LLVG_PATH_impl_single.c``/``LLVG_PATH_impl_dual.c``, ``LLVG_GRADIENT_impl_stub.c`` and ``LLVG_FONT_impl_freetype.c``.

* Matrix (see Matrix module's :ref:`section_vg_matrix_llapi`): a basic software implementation.
* Path (see Path module's :ref:`section_vg_path_llapi`): a generic implementation that manages the command buffer's life cycle and dispatches the command encoding to a 3rd-party header file ``vg_path.h``.
* Gradient (see Gradient module's :ref:`section_vg_gradient_llapi`): a generic minimal implementation that only handles a single color (resulting in filling paths with a solid color). To fully handle linear gradients, the API from ``LLVG_GRADIENT_impl.h`` must be implemented.
* Font (see Font module's :ref:`section_vg_font_llapi`): an implementation of vector font over FreeType: open font file and retrieve font's characteristics.
* The MicroVG painter native functions are implemented in ``LLVG_PAINTER_impl.c`` and the drawings are redirected to ``vg_drawing.h``.
* Image management is too specific to the GPU and is not implemented in this C module.

This C module is available on the :ref:`central_repository`: `com.microej.clibrary.llimpl#microvg`_.

.. _com.microej.clibrary.llimpl#microvg: https://repository.microej.com/modules/com/microej/clibrary/llimpl/microvg/

Dependencies
------------

This generic C module requires some specific modules:

* Path and Gradient require a C module specific to a VEE Port (to a GPU format).
* Font requires the FreeType library and optionally the Harfbuzz library to manage the :ref:`complex layout <section_vg_font_complex>`.

Usage
-----

1. This C module transitively fetches the :ref:`C Module for MicroUI<section_ui_cco>`, follow its implementation rules.
2. Add all C files in the BSP project.
3. Configure the options in the header file ``vg_configuration.h``.

.. _section_vg_c_module_freetype:

Library: FreeType
=================

Description
-----------

The FreeType library compatible with MicroEJ is packaged in a C module on the :ref:`developer_repository`: `com.microej.clibrary.thirdparty#freetype`_.

.. _com.microej.clibrary.thirdparty#freetype: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/thirdparty/freetype/

This C module provides a fork of FreeType 2.11.0.

Memory Heap Configuration
-------------------------

The FreeType library requires a memory Heap for FreeType internal objects allocated when a font file is loaded (see https://freetype.org/freetype2/docs/design/design-4.html).
The size of this heap depends on the number of fonts loaded in parallel and on the fonts themselves.
This size is defined by ``VG_FEATURE_FREETYPE_HEAP_SIZE`` in ``vg_configuration.h``.

All fonts do not require the same heap size. FreeType heap usage can be monitored using the following configurations:

* ``MICROVG_MONITOR_HEAP`` defined in ``vg_helper.h``
* ``MEJ_LOG_MICROVG`` and ``MEJ_LOG_INFO_LEVEL`` defined in ``mej_log.h``

Principle
---------

#. The Application loads a font with `ej.microvg.VectorFont.loadFont()`_.

   * If the resource is internal or external from byte-addressable memory, the FreeType library is configured to read directly from that resource memory section.
   * Else, if the resource is external from non-byte-addressable memory, the FreeType library is configured to use the :ref:`external loader<section_externalresourceloader>` to read from that memory.
   * At this point, the font resources are allocated and the font generic data (including baseline & height metrics) is loaded on the FreeType dedicated heap.

#. The Application requests metrics.

   * For generic metrics, already loaded data is directly used (and scaled to the font size used).
   * For text-dependent metrics: computed by loading metrics of every glyph required by the input string (the glyphs bitmaps are not actually rendered here).

#. The Application requests drawings.

   * For every character to draw:

     * the associated glyph is loaded,
     * the bitmap is rendered for the given font size and
     * the character is drawn in the given graphic context.

#. The Application unloads the font with `ej.microvg.VectorFont.close()`_.

   * Any resource associated with the font is released.
   * At this point, any attempt to use the font will result in an exception.

Library: Harfbuzz
=================

The library Harfbuzz compatible with MicroEJ is packaged in a C module on the :ref:`developer_repository`: `com.microej.clibrary.thirdparty#harfbuzz`_.

.. _com.microej.clibrary.thirdparty#harfbuzz: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/thirdparty/harfbuzz/

This C module provides a fork of Harfbuzz 4.2.1.

The Harfbuzz library requires a memory Heap for Harfbuzz internal objects allocated when a font file is loaded.
The size of this heap depends on the number of fonts loaded in parallel and on the fonts themselves.
This size is defined by ``VG_FEATURE_HARFBUZZ_HEAP_SIZE_HEAP`` in ``vg_configuration.h``.

All fonts do not require the same heap size. The ``MICROVG_MONITOR_HEAP`` define in ``vg_helper.h`` and ``MEJ_LOG_MICROVG`` and ``MEJ_LOG_INFO_LEVEL`` defines in ``mej_log.h`` can be used to monitor the Harfbuzz heap evolution.

FreeType and Harfbuzz libraries are not sharing the same heap, but this could easilly be done by updating ``ft_system.c`` and ``hb-alloc.c`` files.

.. _section_vg_c_module_microvg_vglite:

C Module: MicroVG Over VGLite
=============================

Overview
--------

This C module is a specific implementation of the VG Pack drawings over the official Vivante VGLite library (that targets some GPU with vector graphics acceleration):

* It implements the MicroVG API ``LLVG_impl.h`` in ``LLVG_impl_vglite.c``.
* It implements the MicroVG API ``LLVG_GRADIENT_impl.h`` in ``LLVG_GRADIENT_impl_vglite.c``.
* It implements the MicroVG API ``vg_drawing.h`` in ``vg_drawing_vglite.c``.
* It implements the MicroVG API ``vg_path.h`` in ``vg_path_vglite.c``.
* It implements the MicroVG Image management (draw a compile-time image, create a BufferedVectorImage, etc.) in ``vg_drawing_vglite_image.c``.
* It provides an implementation of MicroVG drawings to the MicroVG BufferedVectorImage: ``vg_drawing_bvi.c``.
* It also implements MicroUI drawings to the MicroVG BufferedVectorImage: ``ui_drawing_bvi.c``.

The implementation requires:

* the concepts of the C module MicroVG,
* the concepts of the C module MicroUI over VGLite,
* the FreeType library,
* the Vivante VGLite library.

This C module is available on the :ref:`developer_repository`: `com.microej.clibrary.llimpl#microvg-vglite`_.

.. warning:: The library must be patched to be compatible with the C module "MicroUI over VGLite". Consult the C module's ReadMe file for more information.

Usage
-----

1. This C module transitively fetches the :ref:`C Module for MicroUI for VGLite<section_ui_cco>`, follow its implementation rules.
2. Add all C files in the BSP project.

.. _com.microej.clibrary.llimpl#microvg-vglite: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/llimpl/microvg-vglite/


.. _section_vg_c_module_microvg_nema:

C Module: MicroVG Over NemaVG
=============================

Overview
--------

This C module is a specific implementation of the VG Pack drawings over the official Think Silicon Nema VG library (that targets some GPU with vector graphics acceleration):

* It implements the MicroVG API ``vg_drawing.h`` in ``vg_drawing_nema.c``.
* It implements the MicroVG Image management (draw a compile-time image, create a BufferedVectorImage, etc.): ``vg_drawing_nema_image.c``.
* It provides an implementation of MicroVG drawings to the MicroVG BufferedVectorImage: ``vg_drawing_bvi.c``.
* It also implements MicroUI drawings to the MicroVG BufferedVectorImage: ``ui_drawing_bvi.c``.

The implementation requires:

* the concepts of the C module MicroVG,
* the concepts of the C module MicroUI over NemaVG,
* the FreeType library,
* the Think Silicon NemaVG library.

This C module is available on the :ref:`developer_repository`: `com.microej.clibrary.llimpl#microvg-nema`_.

Usage
-----

1. This C module transitively fetches the :ref:`C Module for MicroUI for NemaGFX<section_ui_cco>`, follow its implementation rules.
2. Add all C files in the BSP project.


.. XXX_TODO wrong link
.. _com.microej.clibrary.llimpl#microvg-nema: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/llimpl/microvg-vglite/


Compatibility
=============

The compatibility between the components (Packs, C modules, and Libraries) is described in the :ref:`section_vg_releasenotes`.


.. _ej.microvg.VectorFont.loadFont(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorFont.html#loadFont-java.lang.String-
.. _ej.microvg.VectorFont.close(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorFont.html#close--

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.
