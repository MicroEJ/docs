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

* Freetype library for the font renderer and the font layouter in simple layout mode.
* Harfbuzz library for the font layouter in complex layout mode.
* Vivante VGLite library for the drawing of vector paths

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

Library: Vivante VGLite
=======================

This library is the official Vivante VGLite library.
The C modules use its header files to target the GPU.

.. note:: The library must be patched to be compatible with the C module "MicroUI over VGLite". Consult the C module's ReadMe file for more information.

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

This generic C module provides an implementation of MicroVG concepts: matrix, path, linear gradient and font; respectively ``LLVG_MATRIX_impl.c``, ``LLVG_PATH_impl.c``, ``LLVG_GRADIENT_impl.c`` and ``LLVG_FONT_freetype.c``.

* Matrix (see Matrix module's :ref:`section_vg_matrix_llapi`): a basic software implementation.
* Path (see Path module's :ref:`section_vg_path_llapi`): a generic implementation that manages the command buffer's life cycle and dispatches the command encoding to a 3rd-party header file ``microvg_path.h``.
* Gradient (see Gradient module's :ref:`section_vg_gradient_llapi`): a generic implementation that manages the gradient buffer's life cycle and dispatches the gradient encoding to a 3rd-party header file ``microvg_gradient.h``.
* Font (see Font module's :ref:`section_vg_font_llapi`): an implementation of vector font over Freetype: open font file and retrieve font's characteristics.
* The MicroVG painter native functions are implemented in ``LLVG_PAINTER_impl.c`` and the drawings are redirected to ``vg_drawing.h``.
* Image management is too specific to the GPU and is not implemented in this C module.

This C module is available on the :ref:`central_repository`: `com.microej.clibrary.llimpl#microvg`_.

.. _com.microej.clibrary.llimpl#microvg: https://repository.microej.com/modules/com/microej/clibrary/llimpl/microvg/

Dependencies
------------

This generic C module requires some specific modules:

* Path and Gradient require a C module specific to a VEE Port (to a GPU format).
* Font requires the Freetype library and optionally the Harfbuzz library to manage the :ref:`complex layout <section_vg_font_complex>`.

Configuration
-------------

This C module uses a configuration file.
This file (a header file with some C defines) enables (or disables) and configures some options:

* ``VG_FEATURE_PATH``: set this define to embed the full implementation of ``Path`` feature. Otherwise, a stub implementation is used, and all ``Path`` drawings are dropped.
* ``VG_FEATURE_GRADIENT``: configure this define to embed the full implementation of ``LinearGradient`` or a stub implementation that only manages one color (linear gradient's first color). The respective options are ``VG_FEATURE_GRADIENT_FULL`` and ``VG_FEATURE_GRADIENT_FIRST_COLOR``.
* ``VG_FEATURE_FONT``: configure this define to specify the Font Engine and the Font Engine's backend. Two options are currently available: the Freetype engine with a vectorial backend and the Freetype engine with a bitmap backend. The respective options are ``VG_FEATURE_FONT_FREETYPE_VECTOR`` and ``VG_FEATURE_FONT_FREETYPE_BITMAP``.
* ``VG_FEATURE_FREETYPE_TTF``: set this define to enable the support of TTF font files in Freetype.
* ``VG_FEATURE_FREETYPE_OTF``: set this define to enable the support of OTF font files in Freetype.
* ``VG_FEATURE_FREETYPE_COLORED_EMOJI``: set this define to enable the support of colored emoji in Freetype.
* ``VG_FEATURE_FONT_COMPLEX_LAYOUT``:  set this define to enable the support of :ref:`complex layout<section_vg_font_complex>`. This option is managed by the C module ``Harfbuzz`` (see upper).
* ``VG_FEATURE_FONT_EXTERNAL``: set this define to allow loading of external font files (outside the application classpath). See :ref:`chapter.microej.applicationResources`.
* ``VG_FEATURE_FREETYPE_HEAP_SIZE``: specify the Freetype engine's heap size.
* ``VG_FEATURE_FONT_COMPLEX_LAYOUT_HEAP_SIZE``: specify the Harfbuzz engine's heap size.

.. note:: This options list is not exhaustive. Please consult the C module's readme file for more information.

Library: Freetype
=================

The Freetype library compatible with MicroEJ is packaged in a C module on the :ref:`developer_repository`: `com.microej.clibrary.thirdparty#freetype`_.

.. _com.microej.clibrary.thirdparty#freetype: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/thirdparty/freetype/

This C module provides a fork of Freetype 2.11.0.

The Freetype library requires a memory Heap for Freetype internal objects allocated when a font file is loaded (see https://freetype.org/freetype2/docs/design/design-4.html). 
The size of this heap depends on the number of fonts loaded in parallel and on the fonts themselves. 
This size is defined by ``VG_FEATURE_FREETYPE_HEAP_SIZE_HEAP`` in ``microvg_configuration.h``.

All fonts do not require the same heap size. The ``MICROVG_MONITOR_HEAP`` define in ``microvg_helper.h`` and ``MEJ_LOG_MICROVG`` and ``MEJ_LOG_INFO_LEVEL`` defines in ``mej_log.h`` can be used to monitor the Freetype heap evolution.

Library: Harfbuzz
=================

The library Harfbuzz compatible with MicroEJ is packaged in a C module on the :ref:`developer_repository`: `com.microej.clibrary.thirdparty#harfbuzz`_.

.. _com.microej.clibrary.thirdparty#harfbuzz: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/thirdparty/harfbuzz/

This C module provides a fork of Harfbuzz 4.2.1.

The Harfbuzz library requires a memory Heap for Harfbuzz internal objects allocated when a font file is loaded. 
The size of this heap depends on the number of fonts loaded in parallel and on the fonts themselves. 
This size is defined by ``VG_FEATURE_HARFBUZZ_HEAP_SIZE_HEAP`` in ``microvg_configuration.h``.

All fonts do not require the same heap size. The ``MICROVG_MONITOR_HEAP`` define in ``microvg_helper.h`` and ``MEJ_LOG_MICROVG`` and ``MEJ_LOG_INFO_LEVEL`` defines in ``mej_log.h`` can be used to monitor the Harfbuzz heap evolution.

Freetype and Harfbuzz libraries are not sharing the same heap, but this could easilly be done by updating ``ft_system.c`` and ``hb-alloc.c`` files.

.. _section_vg_c_module_microvg_vglite:

C Module: MicroVG Over VGLite
=============================

This C module is a specific implementation of the VG Pack drawings over the official Vivante VGLite library (that targets some GPU with vector graphics acceleration):

* It implements the MicroVG API ``vg_drawing.h`` in ``vg_drawing_vglite.c`` and ``LLVG_PAINTER_FONT_freetype_vglite.c``.
* It implements the MicroVG Image management (draw a compile-time image, create a BufferedVectorImage, etc.): ``LLVG_RAW_impl.c``. 
* It provides an implementation of MicroVG drawings to the MicroVG BufferedVectorImage: ``vg_drawing_bvi.c``.
* It also implements MicroUI drawings to the MicroVG BufferedVectorImage: ``ui_drawing_bvi.c``.

The implementation requires:

* the concepts of the C module MicroVG,
* the concepts of the C module MicroUI over VGLite,
* the Freetype library,
* the Vivante VGLite library.

This C module is available on the :ref:`developer_repository`: `com.microej.clibrary.llimpl#microvg-vglite`_.

.. _com.microej.clibrary.llimpl#microvg-vglite: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/llimpl/microvg-vglite/

Compatibility
=============

The compatibility between the components (Packs, C modules, and Libraries) is described in the :ref:`section_vg_releasenotes`.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
