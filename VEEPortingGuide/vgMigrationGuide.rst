.. include:: uiReplaces.rst

.. _section_vg_migrationguide:

===============
Migration Guide
===============

From 1.7.2 to 1.8.1
===================

VEE Port Configuration project
""""""""""""""""""""""""""""""

* Update the UI Pack to version 14.4.1 or higher.

Application
"""""""""""

The font cache has been removed.
Each call to ``VectorFont.loadFont()`` creates a new instance of the font.
Consequently, a font should not be loaded during rendering but rather in the initialization phase (for example, in the `attach` method of a widget).
It is also essential to close the font when it is no longer in use (for example, in the `detach` method of a widget).

.. _section_vg_migrationguide_pack_1.8.1_bsp:

BSP
"""

The C Module's options configuration file ``vg_configuration.h`` must not be modified anymore.
Before installing the new C Module: 

* Create (if it doesn't exist already) the global `VEE Port configuration file`_.
* Move your own configuration from ``vg_configuration.h`` to ``veeport_configuration.h``.
* Install the `C Module MicroVG 8.0.0`_.

The following options (see ``vg_configuration.h``) have now a value (not just commented/uncommented); check (and adjust) whether they are used outside the VG C Modules:

* ``VG_FEATURE_FREETYPE_TTF``
* ``VG_FEATURE_FREETYPE_OTF``
* ``VG_FEATURE_FREETYPE_COLORED_EMOJI``
* ``VG_FEATURE_FONT_COMPLEX_LAYOUT``
* ``VG_FEATURE_FONT_EXTERNAL``
* ``VG_FEATURE_BUFFERED_VECTOR_IMAGE``
	
.. _VEE Port configuration file: https://github.com/MicroEJ/Tool-Project-Template-VEEPort/tree/master/bsp/vee/port/config

BSP with VGLite
"""""""""""""""

* **Prerequisite:** follow the migration steps of :ref:`section_vg_migrationguide_pack_1.8.1_bsp`.
* Delete the file ``LLVG_impl_vglite.c``
* Install the `C Module MicroVG over VGLite 10.0.0`_.

BSP with NemaVG
"""""""""""""""

* **Prerequisite:** follow the migration steps of :ref:`section_vg_migrationguide_pack_1.8.1_bsp`.
* Delete the file ``LLVG_impl_nema.c``
* Install the `C Module MicroVG over NemaVG 3.0.0`_.

FreeType
""""""""

* **Prerequisite:** follow the migration steps of :ref:`section_vg_migrationguide_pack_1.8.1_bsp`.
* Install the `C Module Freetype 5.0.0`_.
* Update the file ``[...]/freetype/config/ftmodule.h``: 

    * Replace ``#ifdef VG_FEATURE_FREETYPE_TTF`` by ``#if defined VG_FEATURE_FREETYPE_TTF && (VG_FEATURE_FREETYPE_TTF == 1)``
    * Replace ``#ifdef VG_FEATURE_FREETYPE_OTF`` by ``#if defined VG_FEATURE_FREETYPE_OTF && (VG_FEATURE_FREETYPE_OTF == 1)``

* In case of standalone library: include the folder of the configuration file ``vg_configuration.h`` in the include directives and rebuild the library.

.. note:: The update of FreeType (from the version 2.13.3 to the version 2.14.1) is optional. In that case, update the files ``ft_ttf_wrapper.c``, ``ft_otf_wrapper.c`` and ``ftmodule.h``:

    * Replace ``#ifdef VG_FEATURE_FREETYPE_TTF`` by ``#if defined VG_FEATURE_FREETYPE_TTF && (VG_FEATURE_FREETYPE_TTF == 1)``
    * Replace ``#ifdef VG_FEATURE_FREETYPE_OTF`` by ``#if defined VG_FEATURE_FREETYPE_OTF && (VG_FEATURE_FREETYPE_OTF == 1)``

HarfBuzz
""""""""

* **Prerequisite:** follow the migration steps of :ref:`section_vg_migrationguide_pack_1.8.1_bsp`.
* Install the `C Module Harfbuzz 4.0.0`_.
* Rebuild the library.

.. note:: The update of HarfBuzz (from the version 10.0.1 to the version 12.3.0) is optional. In that case, update the file ``hb-alloc.c``:

    * Replace ``#if defined(VG_FEATURE_FONT_COMPLEX_LAYOUT)`` by ``#if defined VG_FEATURE_FONT_COMPLEX_LAYOUT && (VG_FEATURE_FONT_COMPLEX_LAYOUT == 1)``

From 1.7.1 to 1.7.2
===================

BSP with VGLite
"""""""""""""""

* Install the `C Module MicroVG 7.0.2`_.
* Install the `C Module MicroVG over VGLite 9.0.2`_.

BSP with NemaVG
"""""""""""""""

* Install the `C Module MicroVG 7.0.2`_.
* Install the `C Module MicroVG over NemaVG 2.0.2`_.
* Add the defines ``RESX`` and ``RESY`` in ``vg/inc/vg_configuration.h`` or in the C project global options.

From 1.7.0 to 1.7.1
===================

BSP with VGLite
"""""""""""""""

* Install the `C Module MicroVG over VGLite 9.0.1`_.

BSP with NemaVG
"""""""""""""""

* Install the `C Module MicroVG over NemaVG 2.0.1`_.

From 1.6.0 to 1.7.0
===================

VEE Port Configuration project
""""""""""""""""""""""""""""""

* Update the UI Pack to version 14.1.1 or higher.

BSP with VGLite
"""""""""""""""

* Follow the migration steps of :ref:`BSP with VGLite <section_ui_migrationguide_14.1_vglite>` for the new UI Pack.
* Install the `C Module MicroVG over VGLite 9.0.0`_.
* Set the define ``UI_GC_SUPPORTED_FORMATS`` to ``2`` or more in ``ui_configuration.h``.
* Set the define ``UI_FEATURE_FONT_CUSTOM_FORMATS`` in ``ui_configuration.h``.

BSP with NemaVG
"""""""""""""""

* Follow the migration steps of :ref:`BSP with NemaGFX <section_ui_migrationguide_14.1_nemagfx>` for the new UI Pack.
* Install the `C Module MicroVG over NemaVG 2.0.0`_.
* Set the define ``UI_GC_SUPPORTED_FORMATS`` to ``2`` or more in ``ui_configuration.h``.
* Set the define ``UI_FEATURE_FONT_CUSTOM_FORMATS`` in ``ui_configuration.h``.

FreeType
""""""""

Optionally, update the :ref:`C Module FreeType <section_vg_c_module_freetype>` to use FreeType version 2.13.3:

* Delete the directory ``thirdparty/freetype``.
* Remove ``thirdparty/freetype/inc`` and ``thirdparty/freetype/inc/ftvector`` from your include path.
* Add ``thirdparty/freetype/include``, ``thirdparty/freetype/src`` and ``freetype_support/src`` to your include path.
* Remove ``thirdparty/freetype/lib/freetype.a`` from your build path.
* Build FreeType and add the library and support files following the `C Module FreeType's instructions`_.

.. _C Module FreeType's instructions: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/thirdparty/freetype/4.0.0/README-4.0.0.md

HarfBuzz
""""""""

Optionally, update the :ref:`C Module HarfBuzz <section_vg_c_module_harfbuzz>` to use HarfBuzz version 10.0.1:

* Delete the directory ``thirdparty/harfbuzz``.
* Remove ``thirdparty/harfbuzz/inc`` from your include path.
* Add ``thirdparty/harfbuzz/src`` to your include path.
* Remove ``thirdparty/harfbuzz/lib/harfbuzz.a`` and ``thirdparty/harfbuzz/src/hb-alloc.c`` from your build path.
* Build HarfBuzz and add the library and support files following `C Module HarfBuzz's instructions`_.

.. _C Module HarfBuzz's instructions: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/thirdparty/harfbuzz/3.0.0/README-3.0.0.md

From 1.5.x to 1.6.0
===================

VEE Port Configuration project
""""""""""""""""""""""""""""""

* Update the UI Pack to version 14.0.1 or higher.
* Specify the ``implementation`` property, as written in the section :ref:`section_microvg_installation`.

BSP
"""

* Update your implementation of the following functions to match the signature changes.

    * ``LLVG_GRADIENT_IMPL_initializeGradient``,
    * ``LLVG_MATRIX_IMPL_copy``,
    * ``LLVG_MATRIX_IMPL_multiply``,
    * ``LLVG_MATRIX_IMPL_setConcat``,
    * ``LLVG_MATRIX_IMPL_concatenate``,
    * ``LLVG_MATRIX_IMPL_postConcat``,
    * ``LLVG_BVI_IMPL_map_context``,
    * ``LLVG_PAINTER_IMPL_drawImage``.

BSP with VGLite
"""""""""""""""

* Follow the migration steps of :ref:`BSP with VGLite <section_ui_migrationguide_pack_14.0.3>` for the new UI Pack.
* Install the `C Module MicroVG over VGLite 8.0.1`_.
* Delete the following file in the ``ui`` directory:

    * ``src/ui_drawing_bvi.c``.

* Delete the following files in the ``vg`` directory:

    * ``inc/microvg_font_freetype.h``,
    * ``inc/microvg_gradient.h``,
    * ``inc/microvg_helper.h``,
    * ``inc/microvg_path.h``,
    * ``inc/microvg_trace.h``,
    * ``src/LLVG_BVI_stub.c``,
    * ``src/LLVG_FONT_freetype.c``,
    * ``src/LLVG_FONT_stub.c``,
    * ``src/LLVG_GRADIENT_impl.c``,
    * ``src/LLVG_impl.c``,
    * ``src/LLVG_PATH_impl.c``,
    * ``src/LLVG_PATH_stub.c``,
    * ``src/microvg_helper.c``,

    * ``inc/vg_bvi_vglite.h``,
    * ``inc/vg_drawing_vglite.h``,
    * ``inc/vg_vglite_helper.h``,
    * ``src/LLVG_GRADIENT_impl_vglite.c``,
    * ``src/LLVG_impl_vglite.c``,
    * ``src/vg_drawing_bvi.c``,
    * ``src/vg_drawing_vglite_image.c``,
    * ``src/vg_drawing_vglite.c``,
    * ``src/vg_path_vglite.c``,
    * ``src/vg_vglite_helper.c``.

* Delete the properties files ``cco_microvg.properties`` and ``cco_microvg-vglite.properties``.
* Build the VEE Port.
* Configure the C Module MicroVG in ``vg/inc/vg_configuration.h``, based on your previous settings in ``vg/inc/microvg_configuration.h``.
* Delete ``vg/inc/microvg_configuration.h``.
* Add the source files in ``vg/src`` and ``vg_vglite/src`` to the project.
* Add the path ``vg_vglite/inc`` to the include path.

From 1.4.x to 1.5.1
===================

VEE Port Configuration Project
""""""""""""""""""""""""""""""

* Update UI Pack version: 14.0.0 or higher.

BSP with VGLite
""""""""""""""""

* Follow the migration steps of :ref:`BSP with VGLite <section_ui_migrationguide_14.0_vglite>` for the new UI Pack.
* Install the C Modules MicroVG 5.0.0 and MicroVG-VGLite 7.0.1.

From 1.3.x to 1.4.2
===================

BSP with VGLite
""""""""""""""""

* Follow the migration steps of :ref:`BSP with VGLite <section_ui_migrationguide_13.6_vglite>` for the new UI Pack.
* Install the C Modules MicroVG 4.0.0 and MicroVG-VGLite 6.1.1.
* Delete the content of ``dropins/include`` folder.
* Build the FreeType library (in case of a dedicated project), and then the BSP.

From 1.2.x to 1.3.0
===================

VEE Port Configuration Project
""""""""""""""""""""""""""""""

* Update UI Pack version: 13.5.0 or higher.

BSP with VGLite
""""""""""""""""

* Follow the migration steps :ref:`BSP with VGLite <section_ui_migrationguide_13.5_vglite>` for the new UI Pack.
* Install the C Modules MicroVG 3.0.0 and MicroVG-VGLite 5.0.1.
* Delete the content of ``dropins/include`` folder.
* Delete the C files ``freetype_bitmap_helper.h``, ``freetype_bitmap_helper.c``, ``LLVG_BVI_impl.c``, ``LLVG_FONT_PAINTER_freetype_bitmap.c`` and ``LLVG_PATH_PAINTER_vglite.c`` and remove them from the C project configuration.
* In the C project configuration, include the new C files ``ui_drawing_bvi.c``, ``LLVG_BVI_stub.c``, ``LLVG_PAINTER_impl.c``, ``vg_drawing_bvi.c``, ``vg_drawing_stub.c``, ``vg_drawing_vglite.c`` and ``vg_drawing.c``.
* In the C project configuration, set the define ``LLUI_GC_SUPPORTED_FORMATS=2`` to enable the BufferedVectorImage support.
* Verify the options in ``microvg_configuration.h``.
* Build the FreeType library (in case of a dedicated project), and then the BSP.

..
   | Copyright 2021-2025, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.
