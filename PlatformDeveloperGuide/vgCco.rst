.. _section_vg_cco:

=========
C Modules
=========

Principle
=========

Several C modules implement the VG Pack's Low Level APIs.
Some on them are generic, some on them are platform specific dependent (more specifically: GPU dependent).
The generic modules provide some header files to be extended by the specific modules. 
The generic C modules are available on `MicroEJ Central Repository <zzz_centralrepourl_zzz/modules>`_  and the specific C modules on the `Developer Repository <zzz_devrepourl_zzz/microej-developer-repository-release>`_.

The following picture illustrates the available C modules and their relations. 
It is a simplified view: all sources and headers files of each C module are not visible.
The next chapters explain the aim and relations of each C module.

.. figure:: images/vg_cco.*
   :alt: MicroVG C Modules
   :width: 100%
   :align: center

   MicroVG C Modules

UI Pack
=======

The UI Pack provides a header file to implement the MicroUI drawings: ``LLUI_PAINTER_impl.h``.
See :ref:`UI Pack <section_display_llapi>` chapter to have more information.

The UI Pack and its header files are available on the Central Repository: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/. 

C Module: MicroUI
=================

This generic C module provides an implementation of all MicroUI drawings (``LLUI_PAINTER_impl.c``).
It manages the synchronization with the Graphics Engine and redirects all drawings to an implementation of ``ui_drawing.h``.
See :ref:`UI Pack <section_display_llapi>` chapter to have more information.

This C module is available on the Central Repository: https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui/.

.. _section_vg_c_module_microui_vglite:

C Module: MicroUI Over VGLite
=============================

This C module is a specific implementation of the C module MicroUI over Vivante VGLite.
It implements a set of drawings over the official Vivante VGLite library (that targets some GPU with vector graphics acceleration): ``drawing_vglite.c``.

This C module also provides a set of header files (and their implementations) to manipulate some MicroUI concepts over the VGLite library: image management, path format, etc.: ``display_vglite.h`` and ``vglite_path.h``.

This C module is available on the Developer Repository: XXXX_zzzz_link.

Library: Vivante VGLite
=======================

This library symbolizes the official Vivante VGLite library.
The C modules use its header files to target the GPU.

.. note:: The library must be patched to be compatible with the C module "MicroUI over VGLite". Consult the C module's ReadMe file to have more information.

VG Pack
=======

The VG Pack provides a set of header files to implement the MicroVG concepts.
The header files are described in the dedicated chapters: :ref:`Matrix module <section_vg_matrix>`, :ref:`Path module <section_vg_path>`, :ref:`Gradient module <section_vg_gradient>` and :ref:`Font module <section_vg_font>`.

The VG Pack is an extension of the UI Pack.
The VG Pack's header files require the UI Pack's header files to manipulate the MicroUI concepts.
By consequence, the VG Pack requires to be installed on a platform that fetches an UI Pack.

The VG Pack and its header files are available on the Central Repository: XXXX_zzzz_link.

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

This C module is available on the Central Repository: XXXX_zzzz_link.

Dependencies
------------

This generic C module require some specific modules:

* Path and Gradient require a C module specific to a platform (to a GPU format).
* Font requires the Freetype library and optionally the Harfbuzz library to manage the :ref:`complex layout <section_vg_font_complex>`.

Configuration
-------------

This C module uses a configuration file.
This file (a header file with some C defines) enables (or disables) and configures some options:

* ``VG_FEATURE_PATH``: set this define to embed the full implementation of ``Path`` feature. Otherwise a stub implementation is used and all ``Path`` drawings are dropped.
* ``VG_FEATURE_GRADIENT``: configure this define to embed the full implementation of ``LinearGradient`` or a stub implementation that only manages one color (linear gradient's first color). The respective options are ``VG_FEATURE_GRADIENT_FULL`` and ``VG_FEATURE_GRADIENT_FIRST_COLOR``.
* ``VG_FEATURE_FONT``: configure this define to specify the Font Engine and the Font Engine's backend. Two options are currently available: the Freetype engine with a vectotial backend and the Freetype engine with a bitmap backend. The respective options are ``VG_FEATURE_FONT_FREETYPE_VECTOR`` and ``VG_FEATURE_FONT_FREETYPE_BITMAP``.
* ``VG_FEATURE_FREETYPE_TTF``: set this define to enable the support of TTF font files in Freetype.
* ``VG_FEATURE_FREETYPE_OTF``: set this define to enable the support of OTF font files in Freetype.
* ``VG_FEATURE_FREETYPE_COLORED_EMOJI``: set this define to enable the support of colored emoji in Freetype.
* ``VG_FEATURE_FONT_COMPLEX_LAYOUT``:  set this define to enable the support of :ref:`complex layout<section_vg_font_complex>`. This option is managed by the C module ``Harfbuzz`` (see upper).
* ``VG_FEATURE_FONT_EXTERNAL``: set this define to allow to load external font files (outside the application classpath). See :ref:`chapter.microej.applicationResources`.
* ``VG_FEATURE_FREETYPE_HEAP_SIZE``: specify the Freetype engine's heap size.
* ``VG_FEATURE_FONT_COMPLEX_LAYOUT_HEAP_SIZE``: specify the Harfbuzz engine's heap size.

.. note:: This option list is not exhaustive. Please consult the C module's readme file for more information.

Library: Freetype
=================

The library Freetype compatible with MicroEJ is packaged in a C module: `<zzz_centralrepourl_zzz/modules/com/microej/clibrary/thirdparty/freetype>`_.
This C module provides a fork of Freetype 2.11.0.

Library: Harfbuzz
=================

The library Harfbuzz compatible with MicroEJ is packaged in a C module `<zzz_centralrepourl_zzz/modules/com/microej/clibrary/thirdparty/harfbuzz>`_. 
This C module provides a fork of Harfbuzz 4.2.1.

.. _section_vg_c_module_microvg_vglite:

C Module: MicroVG Over VGLite
=============================

This C module is a specific implementation of the VG Pack drawing LLAPIs: ``LLVG_PAINTER_PATH_impl.h`` and ``LLVG_PAINTER_FONT_impl.h``.
It implements a set of drawings over the official Vivante VGLite library (that targets some GPU with vector graphics acceleration): ``LLVG_PAINTER_PATH_vglite.c`` and ``LLVG_PAINTER_FONT_freetype_vglite.c``.

The implementation require:

* the concepts of the C module MicroVG,
* the concepts of the C module MicroUI over VGLite,
* the Freetype library,
* the Vivante VGLite library.

This C module is available on the Developer Repository: `<zzz_devrepourl_zzz/com/microej/clibrary/llimpl/microvg-vglite>`_.

Compatibility
=============

The compatibility between the different components (Packs, C modules and Libraries) are described in the :ref:`section_vg_releasenotes`.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
