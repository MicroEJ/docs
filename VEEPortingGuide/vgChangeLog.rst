.. _section_vg_changelog:

=========
Changelog
=========

[1.3.0] - 2023-05-10
====================

* Compatible with UI Pack 13.5.0 or higher.

MicroVG Implementation
""""""""""""""""""""""

**Changed**

* Compatible with MicroVG API 1.3. 

Front Panel
"""""""""""

**Fixed**

* Simplify pixels data conversion after drawing.

[1.2.1] - 2023-02-06
====================

Front Panel
"""""""""""

**Fixed**

* Fix the cropped images when using GraphicsContext clip and translation.

[1.2.0] - 2022-12-30
====================

* Compatible with UI Pack 13.3.0 or higher.

MicroVG Implementation
""""""""""""""""""""""

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

[1.1.0] - 2022-09-05
====================

* Compatible with UI Pack 13.3.0 or higher.

MicroVG Implementation
""""""""""""""""""""""

**Changed**

* Compatible with `MicroVG API 1.1`_.
* Allow loading a VectorFont from external resources. 
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

[1.0.1] - 2022-05-16
====================

* Compatible with UI Pack 13.2.0 or higher.

MicroVG Implementation
""""""""""""""""""""""

**Fixed**

* Fix incorrect transformation of animated paths while creating a filtered image.

[1.0.0] - 2022-05-13
====================

* Initial release.
* Compatible with UI Pack 13.2.0 or higher.
* Compatible with MicroVG API 1.0.0.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
