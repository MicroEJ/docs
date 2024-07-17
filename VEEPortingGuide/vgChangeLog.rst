.. _section_vg_changelog:

=========
Changelog
=========

[1.6.0] - RC
====================

MicroVG Implementation
""""""""""""""""""""""

**Added**

* Allow the ``nema`` value for the MicroVG implementation.

**Changed**

* Compatible with UI Pack 14.0.1.

Front Panel
"""""""""""

**Added**

* Support ``nema`` image format and limitations (blend modes ``SCREEN`` and ``MULTIPLY`` are not supported).

LLAPIs
""""""

**Added**

* Add the LLAPI ``LLVG_MATRIX_IMPL_transformPoint``.
* Add the new type ``MICROVG_Image``.

**Changed**

* Change the semantic of the LLAPI ``LLVG_GRADIENT_IMPL_initializeGradient``: the positions array cannot be ``NULL``.
* Add ``const`` modifiers for parameters of the following functions:

    * ``LLVG_GRADIENT_IMPL_initializeGradient``,
    * ``LLVG_MATRIX_IMPL_copy``,
    * ``LLVG_MATRIX_IMPL_multiply``,
    * ``LLVG_MATRIX_IMPL_setConcat``,
    * ``LLVG_MATRIX_IMPL_concatenate``,
    * ``LLVG_MATRIX_IMPL_postConcat``.

* Use the new type ``MICROVG_Image`` in the signature of the following functions:

    * ``LLVG_BVI_IMPL_map_context``,
    * ``LLVG_PAINTER_IMPL_drawImage``.

[1.5.1] - 2024-04-11
====================

Front Panel
"""""""""""

**Fixed**

* Fix the drawing of a BufferedVectorImage in a BufferedVectorImage with a clip.
* Fix the drawing of a glyph with path overlap.

C Module VGLite
"""""""""""""""

**Fixed**

* Fix the drawing of a VG RAW image in a BufferedVectorImage with a clip.

[1.5.0] - 2024-02-15
====================

UI Pack
"""""""

**Changed**

* Compatible with UI Pack 14.0.0 (Major version).

MicroVG
"""""""

**Fixed**

* Fix the exception when loading a font or an image with an empty path.
* Fix the release of the ``BufferedVectorImage`` resources.

Front Panel
"""""""""""

**Fixed**

* Fix the memory leak on images (ResourceVectorImage and BufferedVectorImage).

LLAPIs
""""""

**Fixed**

* Fix comment in header file ``LLVG_BVI_impl.h``.

C Module MicroVG
""""""""""""""""

**Added**

* Add the API ``freeImageResources`` that allows to fix the release of the ``BufferedVectorImage`` resources.

**Fixed**

* Fix traces when debugging the SNI resources with external resource support.
* Remove an unused include.
* Do not define Freetype variables if ``VG_FEATURE_FONT`` is not defined.
* Do not call ``MICROVG_PATH_initialize()`` if ``VG_FEATURE_PATH`` is not defined.

C Module VGLite
"""""""""""""""

**Fixed**

* Fix the storing of color matrices in the ``BufferedVectorImage``.

[1.4.2] - 2023-11-13
====================

MicroVG
"""""""

**Added**

* Add some traces when debugging the SNI resources.

**Fixed**

* Fix dynamic paths larger than 64 KB.

Front Panel
"""""""""""

**Fixed**

* Fix dynamic paths larger than 64 KB.

C Module MicroVG
""""""""""""""""

**Added**

* Add some traces when debugging the SNI resources (external VectorFont).

**Fixed**

* Fix dynamic paths larger than 64 KB.
* Fix some comments.

C Module VGLite
"""""""""""""""

**Fixed**

* Fix some comments.
* Fix the dynamic path drawing on i.MX RT1170 Evaluation Kit (use the same quality of paths as vector images).
* Fix the path drawing on i.MX RT1170 Evaluation Kit (disable the color pre-multiplication).
* Fix the rendering of some blending modes on i.MX RT1170 Evaluation Kit by disabling the GPU pre-multiplication when required.

[1.4.1] - 2023-09-21
====================

MicroVG
"""""""

**Fixed**

* Fix the path command "move relative".

C Module VGLite
"""""""""""""""

**Added**

* Add the compatibility with VGLite ``3.0.15_rev7``.

**Fixed**

* Fix the use of the define ``VG_BLIT_WORKAROUND`` (useless).
* Fix the GPU deactivation when a drawing is not performed for any reason.

[1.4.0] - 2023-07-21
====================

**Fixed**

* Fix the UI Pack minimal compatible version (13.5.0).

MicroVG
"""""""

**Added**

* Add SystemView event logs (feature available with `C Module MicroVG 3.0.1`_).

.. _C Module MicroVG 3.0.1: https://repository.microej.com/modules/com/microej/clibrary/llimpl/microvg/3.0.1/

**Changed**

* Compatible with `MicroVG API 1.4`_.

.. _MicroVG API 1.4: https://repository.microej.com/modules/ej/api/microvg/1.4.0/

**Fixed**

* Fix path bounds computation.

C Module MicroVG
""""""""""""""""

**Fixed**

* Fix the SystemView log identifiers.
* Fix the documentation of ``MICROVG_HELPER_get_utf()``.
* Fix FreeType fonts closing twice.

C Module VGLite
"""""""""""""""

**Added**

* Add support for DST_OUT and PLUS blend modes (VG Pack 1.4.0).

**Fixed**

* Fix performing drawings when the clip is disabled.
* Fix the SystemView log identifiers.
* Remove the include of the unknown header file ``trace_vglite.h`` (require a re-build of FreeType library).

[1.3.0] - 2023-05-10
====================

UI Pack
"""""""

**Changed**

* Compatible with UI Pack 13.5.0 (``BufferedImage`` with custom format).

MicroVG
"""""""

**Changed**

* Compatible with `MicroVG API 1.3`_.

.. _MicroVG API 1.3: https://repository.microej.com/modules/ej/api/microvg/1.3.0/

Front Panel
"""""""""""

**Fixed**

* Simplify pixel data conversion after drawing.

C Module MicroVG
""""""""""""""""

**Added**

* Add the compatibility with multiple Graphics Context output formats (UI Pack 13.5.0).
* Add stub implementations for all MicroVG library algorithms.
* Add ``LLVG_PAINTER_impl.c`` to implement all MicroVG drawings and dispatch them to ``vg_drawing.h`` (like MicroUI and ``LLUI_PAINTER_impl.c`` / ``ui_drawing.h``).
* Add the MicroVG ``BufferedVectorImage`` definition (the functions to implement to draw into it).

**Changed**

* C Module MicroVG now depends on C Module MicroUI (to manage the support of multiple Graphics Context output formats).

**Fixed**

* Remove an extraneous file.
* Fix issue when measuring string width in complex layout mode.

**Removed**

* Remove the useless implementation of `LLVG_PATH_IMPL_mergePaths` (useless since VG Pack 1.2).
* Remove partial Freetype implementation that manipulates the font's glyphs as bitmaps (not compatible anymore with VG pack 1.3.0).

C Module VGLite
"""""""""""""""

**Added**

* Add the implementation of all MicroUI, Drawing and MicroVG drawings in MicroVG ``BufferedVectorImage``.
* Add incident reporting with drawing log flags (UI Pack 13.5.0).

**Changed**

* Merge ``BufferedVectorImage`` and RAW formats.
* Simplify the gradient modification according to the caller translation.

**Fixed**

* Fix the path to render during a *path data* animation.

**Removed**

* Remove ``LLVG_BVI_impl.c``: code is merged in ``LLVG_RAW_impl.c``.
* Remove (move) some utility functions to C Module MicroUI-VGLite.
* Remove *draw String* native functions implementation (implemented in C Module MicroVG).

[1.2.1] - 2023-02-06
====================

Front Panel
"""""""""""

**Fixed**

* Fix the cropped images when using GraphicsContext clip and translation.

C Module VGLite
"""""""""""""""

**Fixed**

* Fix the drawing of RAW images with multiple gradients in ``BufferedVectorImage``.
* Fix a deadlock when drawing an empty ``BufferedVectorImage``.
* Fix the interface between FreeType and MicroVG (remove useless parameter).
* Fix the synchronization with the Graphics Engine when a VG drawing is not performed (draw path, draw gradient, draw string).

[1.2.0] - 2022-12-30
====================

MicroVG
"""""""

**Changed**

* Compatible with `MicroVG API 1.2`_.
* Change the VectorImage internal format: *raw* format instead of *immutables* format.

.. _MicroVG API 1.2: https://repository.microej.com/modules/ej/api/microvg/1.2.0/

Front Panel
"""""""""""

**Fixed**

* Fix the redirection of fillEllipseArc to the right software algorithm.

Vector Image Converter
""""""""""""""""""""""

**Added**

* Add "fill alpha" animations to gradient elements.

C Module MicroVG
""""""""""""""""

**Added**

* Add ``LLVG_MATRIX_IMPL_multiply(c,a,b)`` (C = AxB): faster than ``setConcat`` when destination and source target the same matrix.
* Add an entry point to initialize the path engine on startup.

**Changed**

* Prevent a copy in a temp matrix when calling ``postXXX`` functions.

**Fixed**

* Fix ``A.setConcat(B,A)``.

C Module VGLite
"""""""""""""""

**Added**

* Add the compatibility with VGLite ``3.0.15_rev4`` (not backward compatible).
* Add the VectorImage in binary format management (RAW format).
* Add loading of VectorImage from external resource system.

**Changed**

* Reduce the gradient footprint in ``BufferedVectorImage``.
* Harmonize the use of ``vg_drawer.h`` functions (instead of ``VG_DRAWER_drawer_t`` functions) in ``BufferedVectorImage``.
* Use the global fields *VGLite paths* instead of functions fields (prevent dynamic allocation on task stack).

**Fixed**

* Fix the drawing of a text in a ``BufferedVectorImage``: do not wake-up the GPU.
* Fix the constants used in ``get_command_parameter_number()`` function (no side-effect).

[1.1.1] - 2022-09-05
====================

UI Pack
"""""""

**Changed**

* Compatible with UI Pack 13.3.0 (Internal feature).

MicroVG
"""""""

**Changed**

* Compatible with `MicroVG API 1.1`_.
* Change color animation interpolation (match Android formula).

**Fixed**

* Fix NullPointerException while sorting TranslateXY VectorDrawableObjectAnimator in vectorimage-converter.

.. _MicroVG API 1.1: https://repository.microej.com/modules/ej/api/microvg/1.1.1/

LLAPIs
""""""

**Added**

* Add LLAPI to close a font: ``LLVG_FONT_IMPL_dispose()``.

**Changed**

* Manage the font :ref:`complex layout <section_vg_font_complex>`.
* Returns an error code when drawing something.

C Module MicroVG
""""""""""""""""

**Added**

* Add ``microvg_configuration.h`` versioning.
* Add an option to load a VectorFont from the external resources.
* Add an option to select the text layouter between FreeType and Harfbuzz.
* Add a function to apply an opacity on a color.
* Add the text layout.

**Changed**

* Configure FreeType from ``microvg_configuration.h`` header file.

C Module VGLite
"""""""""""""""

**Added**

* Add the ``BufferedVectorImage`` feature (BVI).

**Changed**

* Manage the closed fonts.
* Move ``ftvglite.c`` and ``ftvglite.h`` to C Module FreeType.
* Extract text layout to C Module MicroVG.
* Get fill rule configuration from each glyph ``FT_Outline->flags`` instead of defaulting it to ``VG_LITE_FILL_EVEN_ODD``.
* Use the MicroUI over VGLite's Vectorial Drawer mechanism.
* Join character bboxes at baseline for ``drawStringOnCircle``.

[1.0.1] - 2022-05-16
====================

MicroVG
"""""""

**Fixed**

* Fix incorrect transformation of animated paths while creating a filtered image.

[1.0.0] - 2022-05-13
====================

* Initial release.

UI Pack
"""""""

* Compatible with UI Pack 13.2.0 or higher.

MicroVG
"""""""

* Compatible with MicroVG API 1.0.0.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.
