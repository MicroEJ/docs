.. _section_vg_changelog:

=========
Changelog
=========

[1.1.0] - 2022-09-05
====================

* Compatible with UI Pack 13.3.0 or higher.

MicroVG Implementation
""""""""""""""""""""""

**Changed**

* Compatible with `MicroVG API 1.1 <https://repository.microej.com/modules/ej/api/microvg/1.1.0/>`_.
* Allow loading a VectorFont from external resources. 
* Change color animation interpolation (match Android formula).
   
**Fixed**

* Fix NullPointerException while sorting TranslateXY VectorDrawableObjectAnimator in vectorimage-converter.

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
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
