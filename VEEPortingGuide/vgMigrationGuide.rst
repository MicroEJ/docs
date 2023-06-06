
.. _section_vg_migrationguide:

===============
Migration Guide
===============

From 1.2.x to 1.3.x
=====================

BSP with VG-Lite
""""""""""""""""

* Follow the migration steps of :ref:`CCO MicroUI-VGLite 6.0.1 <section_ui_migrationguide_13.5_vglite>`.
* *[VEE Port configuration project]*

	* Fetch VG Pack 1.3.0, CCO MicroVG 3.0.0 and CCO MicroVG-VGLite 5.0.1.
	* Delete the content of ``dropins/include`` folder.

* *[BSP project]*

	* Delete the properties files ``cco_microvg.properties`` and ``cco_microvg-vglite.properties``.
	* Delete the C files ``freetype_bitmap_helper.h``, ``freetype_bitmap_helper.c``, ``LLVG_BVI_impl.c``, ``LLVG_FONT_PAINTER_freetype_bitmap.c`` and ``LLVG_PATH_PAINTER_vglite.c`` and remove them from the C project configuration.
	* In the C project configuration, include the new C files ``ui_drawing_bvi.c``, ``LLVG_BVI_stub.c``, ``LLVG_PAINTER_impl.c``, ``vg_drawing_bvi.c``, ``vg_drawing_stub.c``, ``vg_drawing_vglite.c`` and ``vg_drawing.c``.
	* In the C project configuration, set the define ``LLUI_GC_SUPPORTED_FORMATS=2`` to enable the BufferedVectorImage support.
	* Verify the options in ``microvg_configuration.h``. 
  
* Build the VEE Port, the Freetype library (in case of a dedicated project), and the BSP.

..
   | Copyright 2021-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
