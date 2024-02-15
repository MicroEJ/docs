.. _section_vg_changelog:

=========
Changelog
=========

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
* Fix the release of the BVI resources.

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

* Add the API ``freeImageResources`` that allows to fix the release of the BVI resources.

**Fixed**

* Fix traces when debugging the SNI resources with external resource support.
* Remove an unused include.
* Do not define Freetype variables if ``VG_FEATURE_FONT`` is not defined.
* Do not call ``MICROVG_PATH_initialize()`` if ``VG_FEATURE_PATH`` is not defined.

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

[1.4.1] - 2023-09-21
====================

**Fixed**

* Fix the path command "move relative". 

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
* Add the MicroVG BufferedVectorImage definition (the functions to implement to draw into it).

**Changed**

* C Module MicroVG now depends on C Module MicroUI (to manage the support of multiple Graphics Context output formats).

**Fixed**

* Remove an extraneous file.
* Fix issue when measuring string width in complex layout mode.

**Removed**

* Remove the useless implementation of `LLVG_PATH_IMPL_mergePaths` (useless since VG Pack 1.2).
* Remove partial Freetype implementation that manipulates the font's glyphs as bitmaps (not compatible anymore with VG pack 1.3.0).  

[1.2.1] - 2023-02-06
====================

Front Panel
"""""""""""

**Fixed**

* Fix the cropped images when using GraphicsContext clip and translation.

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

* Add ``microvg_configuration.h`` versionning.
* Add an option to load a VectorFont from the external resources. 
* Add an option to select the text layouter between FreeType and Harfbuzz.
* Add a function to apply an opacity on a color.

**Changed**

* Configure FreeType from ``microvg_configuration.h`` header file.
  
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
