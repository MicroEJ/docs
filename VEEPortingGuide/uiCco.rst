.. _section_ui_cco:

=========
C Modules
=========

Principle
=========

Several C modules implement the UI Pack's Abstraction Layer APIs.
Some are generic, and some are VEE Port dependent (more precisely: GPU-dependent).
The generic modules provide header files to be extended by the specific modules. 
The generic C modules are available on the :ref:`central_repository` and the specific C modules on the :ref:`developer_repository`.

The following picture illustrates the available C modules, and the following chapters explain the aim and relations of each C module.

.. note:: It is a simplified view: all sources and headers files of each C module are not visible.

.. figure:: images/ui_cco.*
   :alt: MicroVG C Modules
   :width: 100%
   :align: center

   MicroUI C Modules

UI Pack
=======

The UI Pack provides a header file to implement the MicroUI drawings: ``LLUI_PAINTER_impl.h``.
See :ref:`UI Pack <section_display_llapi>` chapter to have more information.

The UI Pack and its header files are available on the Central Repository: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/. 

C Module: MicroUI
=================

This C module is divided in several parts and each part provides an implementation of some MicroUI Abstraction Layer APIs.
This C module is **mandatory** (the C files must be compiled in the BSP) but some C files are optional.

See :ref:`UI Pack <section_display_llapi>` chapter to have more information on the MicroUI Abstraction Layer APIs.
This C module is available on the :ref:`central_repository`: `com.microej.clibrary.llimpl#microui`_.

Drawings
--------

* Implements: ``LLUI_PAINTER_impl.h`` and ``LLDW_PAINTER_impl.h``.
* C files: ``LLUI_PAINTER_impl.c``, ``LLDW_PAINTER_impl.c``, ``ui_drawing_stub.c``, ``ui_drawing.c`` and ``ui_image_drawing.c``.
* Status: mandatory.

The aim of this part is to facilitate the MicroUI Painter classes implementation:

	1. It manages the synchronization with the Graphics Engine (see ``LLUI_DISPLAY_requestDrawing()``).
	2. It checks the drawing parameters: clip, opacity, thickness, fade, image status, etc.
	3. It logs the drawing	(see :ref:`microui_traces`).
	4. It deports the rendering to ``ui_drawing.h``.

The implementation of ``ui_drawing.h`` depends on several options:

	* If the BSP provides or not a :ref:`renderer <section_drawings_cco>` (software and / or hardware as a GPU),
	* If the BSP is configured to manage :ref:`several destination formats <section_bufferedimage_cco>`,
	* If the BSP is configured to manage :ref:`custom image formats <section_renderer_cco>`.

Usage:

	* Add all C files in the BSP project.

Images Heap
-----------

* Implements the functions of	``LLUI_DISPLAY_impl.h`` whose prefix is ``LLUI_DISPLAY_IMPL_image_heap_``.
* C file: ``LLUI_DISPLAY_HEAP_impl.c``.
* Status: optional.

This part is optional: the MicroUI Graphics Engine already includes an :ref:`section_image_loader_memory` allocator. 
Like MicroUI Graphics Engine's images heap allocator, the C module's images allocator is a best fit allocator. 
This kind of allocator has the following constraints: 

	* It requires a header at the beginning of heap section.
	* It adds a header and a footer for each allocated block.
	* It produces memory fragmentation: it may not not allow to allocate a block whose size is equal to the free memory size.

Contrary to the Graphics Engine's allocator, the C module's allocator adds some utility functions to get information about the heap: 
	 
	 * total size
	 * free size
	 * number of allocated blocks.

This allocator and the one in the Graphics Engine can be replaced by a third-party one.

Usage:

	 * To use the Graphics Engine's allocator, do not add the file ``LLUI_DISPLAY_HEAP_impl.c`` in the BSP project.
	 * To use the C module's allocator, add the file ``LLUI_DISPLAY_HEAP_impl.c`` in the BSP project.
	 * To use a third-party allocator, do not add the file ``LLUI_DISPLAY_HEAP_impl.c`` in the BSP project and implements the ``LLUI_DISPLAY_IMPL_image_heap_xxx`` functions.

Events Logger
-------------

* Implements the functions of ``LLUI_INPUT_impl.h`` whose prefix is ``LLUI_INPUT_IMPL_log_``.
* C files: ``LLUI_INPUT_LOG_impl.c`` and ``microui_event_decoder.c``.
* Status: optional.

This part is only mandatory when the BSP is calling ``LLUI_INPUT_dump()``, see :ref:`section_inputs_eventbuffer`.
If not included, the call to ``LLUI_INPUT_dump()`` performs nothing. 
Its aim is to log the MicroUI events and to provide an events dumper. 

The logger adds some metadata to each MicroUI event in a dedicated array. 
When the BSP is calling ``LLUI_INPUT_dump()``, the logger is using its data to decode the events. 
Then it uses an implementation of ``microui_event_decoder.h`` to describe the events.

Usage (to enable the events logger):

	* Add all C files in the BSP project.
	* Configures the options in ``microui_event_decoder_conf.h`` (by default the logger is disabled).

Buffer Refresh Strategy
-----------------------

* Implements the functions of ``LLUI_DISPLAY_impl.h`` related to the BRS XXX_TODO add link: ``LLUI_DISPLAY_IMPL_refresh()``, ``LLUI_DISPLAY_IMPL_notify_drawing_region()`` and ``LLUI_DISPLAY_IMPL_notify_dirty_region()``.
* C files: ``ui_display_brs_legacy.c``, ``ui_display_brs_predraw.c``, ``ui_display_brs_single.c``, ``ui_display_brs.c`` and ``ui_rect_util.c``.
* Status: optional.

This part provides three Buffer Refresh Strategies (BRS): ``predraw``, ``single`` and ``legacy``.
Refer to the chapter BRS XXX_TODO add link to have more information on these strategies.
These strategies are optional; when no strategy is selected, the BSP must provide its own strategy.

Usage:

	* Add all C files in the BSP project (whatever the strategy).
	* Configures the options in ``ui_display_brs_configuration.h``.

.. _com.microej.clibrary.llimpl#microui: https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui/

.. _section_ui_c_module_microui_dma2d:

C Module: MicroUI Over DMA2D
============================

This C module is a specific implementation of the C module MicroUI over STM32 DMA2D (Chrom-ART Graphics Accelerator).
It implements a set of drawings over the official Chrom-ART Graphics Accelerator API: ``ui_drawing_dma2d.c``.

Accelerated Drawings
--------------------

The following table describes the accelerated features:

+----------------+------------------------------------------------------+
| Feature        | Comment                                              |
+================+======================================================+
| Fill rectangle |                                                      |
+----------------+------------------------------------------------------+
| Draw image     | ARGB8888, RGB888, RGB565, ARGB1555, ARGB4444, A8, A4 |
+----------------+------------------------------------------------------+
| Flush (copy)   | Copy of data from back buffer to frame buffer        |
+----------------+------------------------------------------------------+

This C module is available on the :ref:`central_repository`: `com.microej.clibrary.llimpl#display-dma2d`_.

.. _com.microej.clibrary.llimpl#display-dma2d: https://repository.microej.com/modules/com/microej/clibrary/llimpl/display-dma2d/

.. _section_ui_c_module_microui_vglite:

C Module: MicroUI Over VGLite
=============================

This C module is a specific implementation of the C module MicroUI over Vivante VGLite.
It implements a set of drawings over the official Vivante VGLite library (that targets some GPU with vector graphics acceleration): ``ui_drawing_vglite.c``.

This C module also provides a set of header files (and their implementations) to manipulate some MicroUI concepts over the VGLite library: image management, path format, etc.: ``ui_vglite.h`` and ``ui_drawing_vglite_path.h``.

Options
-------

This C module provides some drawing algorithms that are disabled by default. 

* The rendering time of a simple shape with the GPU (time in the VG-Lite library + GPU setup time + rendering time) is longer than with software rendering. To enable the hardware rendering for simple shapes, uncomment the definition of ``VGLITE_USE_GPU_FOR_SIMPLE_DRAWINGS``  in ``ui_vglite_configuration.h``.
* The rendering time of an RGB565 image into an RGB565 buffer without applying an opacity (alpha == 0xff) is longer than with software rendering (as this kind of drawing consists in performing a mere memory copy). To enable the hardware rendering for RGB565 images, uncomment the definition of ``VGLITE_USE_GPU_FOR_RGB565_IMAGES``  in ``ui_vglite_configuration.h``.
* ARGB8888, ARGB1555, and ARGB4444 transparent images may not be compatible with some revisions of the VG-Lite GPU. Older GPU revisions do not render transparent images correctly because the pre-multiplication of the pixel opacity is not propagated to the pixel color components. To force the hardware rendering for non-premultiplied transparent images when the VG-Lite GPU is not compatible, uncomment the definition of ``VGLITE_USE_GPU_FOR_TRANSPARENT_IMAGES``  in ``ui_vglite_configuration.h``. Note that this limitation does not concern the VG-Lite GPU compatible with non-premultiplied transparent images and the A8/A4 formats.

Accelerated Drawings
--------------------

The following table describes the accelerated features:

+-----------------------------+-----------------------------------------------------------+
| Feature                     | Comment                                                   |
+=============================+===========================================================+
| Draw line                   | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill rectangle              | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Draw rounded rectangle      | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill rounded rectangle      |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw circle arc             | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill circle arc             |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw ellipse arc            | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill ellipse arc            |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw ellipse arc            | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill ellipse arc            |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw circle                 | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill circle                 |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw image                  | ARGB8888_PRE, ARGB1555_PRE, ARGB4444_PRE, RGB565, A8, A4  |
|                             | ARGB8888, ARGB1555, ARGB4444 (see above)                  |
+-----------------------------+-----------------------------------------------------------+
| Draw thick faded point      | Only with fade <= 1                                       |
+-----------------------------+-----------------------------------------------------------+
| Draw thick faded line       | Only with fade <= 1                                       |
+-----------------------------+-----------------------------------------------------------+
| Draw thick faded circle     | Only with fade <= 1                                       |
+-----------------------------+-----------------------------------------------------------+
| Draw thick faded circle arc | Only with fade <= 1                                       |
+-----------------------------+-----------------------------------------------------------+
| Draw thick faded ellipse    | Only with fade <= 1                                       |
+-----------------------------+-----------------------------------------------------------+
| Draw thick line             |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw thick circle           |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw thick circle arc       |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw thick ellipse          |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw flipped image          | See draw image                                            |
+-----------------------------+-----------------------------------------------------------+
| Draw rotated image          | See draw image                                            |
+-----------------------------+-----------------------------------------------------------+
| Draw scaled image           | See draw image                                            |
+-----------------------------+-----------------------------------------------------------+

This C module is available on the :ref:`developer_repository`: `com.microej.clibrary.llimpl#microui-vglite`_.

Compatibility With MCU i.MX RT595
---------------------------------

The previous versions of the C Module Over VGLite included an implementation of the Low-Level API ``LLUI_DISPLAY_impl.h``.
This support has been extracted into a dedicated C Module since the version ``7.0.0``.
The dedicated C Module is available on the :ref:`developer_repository`: `com.microej.clibrary.llimpl#microui-mimxrt595-evk`_.

Only the C Module `com.microej.clibrary.llimpl#microui-vglite`_ is useful to target the Vivante VG-Lite GPU to perform the MicroUI and MicroVG drawings.
The C Module `com.microej.clibrary.llimpl#microui-mimxrt595-evk`_ only gives an example of an implementation compatible with the MCU i.MX RT595 MCU.

.. note:: For more information, see the :ref:`migration notes<section_ui_migrationguide_13.6_mimxrt595evk>`.

.. _com.microej.clibrary.llimpl#microui-vglite: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/llimpl/microui-vglite/
.. _com.microej.clibrary.llimpl#microui-mimxrt595-evk: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/llimpl/microui-mimxrt595-evk/

.. _section_ui_c_module_microui_nemagfx:

C Module: MicroUI Over NemaGFX
==============================

This C module is a specific implementation of the C module MicroUI over Think Silicon NemaGFX.
It implements a set of drawings over the official NemaGFX library (that targets some GPU with vector graphics acceleration): ``ui_drawing_nema.c``.

Implementation
--------------

The MicroUI Graphics Engine waits the end of the asynchronous drawings (performed by the GPU).
The VEE Port must unlock this waiting by using one of these two solutions:

* Mode `interrupt`: the GPU interrupt routine has to call the function ``UI_DRAWING_NEMA_post_operation()`` (the GPU interrupt routine is often written in the same file than the implementation of ``nema_sys_init()``).
* Mode `task`: the VEE Port has to add a dedicated task that will wait the end of the drawings.

The mode `interrupt` is enabled by default. 
To use the mode `task`, comment the define ``NEMA_INTERRUPT_MODE`` in ``ui_drawing_nema_configuration.h``

.. note:: Retrieve more details in the ``#define NEMA_INTERRUPT_MODE`` documentation.

Options
-------

This C module provides some drawing algorithms that are disabled by default. 

* The rendering time of a simple shape with the GPU (time in the NemaGFX library + GPU setup time + rendering time) is longer than with software rendering. To enable the hardware rendering for simple shapes, uncomment the definition of ``ENABLE_SIMPLE_LINES``  in ``ui_drawing_nema_configuration.h``.
* To draw a shape, the GPU uses the commands list. For rectangular shapes (draw/fill rectangles and images), the maximum list size is fixed (around 300 bytes). For the other shapes (circle, etc.) the list increases according the shape size (dynamic shape): several blocks of 1024 bytes and 40 bytes are allocated and never freed. By default, the dynamic shapes are disabled and the software algorithms are used instead. To enable the hardware rendering for dynamic shapes, uncomment the definition of ``ENABLE_DYNAMIC_SHAPES``  in ``ui_drawing_nema_configuration.h``.
* Some GPU might not be able to render the images in specific memories. Comment the define ``ENABLE_IMAGE_ROTATION`` in ``ui_drawing_nema_configuration.h`` to not use the GPU to render the rotated images.

Accelerated Drawings
--------------------

The following table describes the accelerated features:

+-------------------------+-----------------------------------------------------------------------------+
| Feature                 | Comment                                                                     |
+=========================+=============================================================================+
| Draw line               |                                                                             |
+-------------------------+-----------------------------------------------------------------------------+
| Draw horizontal line    | Disabled by default (see above: ENABLE_SIMPLE_LINES)                        |
+-------------------------+-----------------------------------------------------------------------------+
| Draw vertical line      | Disabled by default (see above: ENABLE_SIMPLE_LINES)                        |
+-------------------------+-----------------------------------------------------------------------------+
| Draw rectangle          | Disabled by default (see above: ENABLE_SIMPLE_LINES)                        |
+-------------------------+-----------------------------------------------------------------------------+
| Fill rectangle          |                                                                             |
+-------------------------+-----------------------------------------------------------------------------+
| Draw rounded rectangle  | Disabled by default (see above: ENABLE_DYNAMIC_SHAPES)                      |
+-------------------------+-----------------------------------------------------------------------------+
| Fill rounded rectangle  | Disabled by default (see above: ENABLE_DYNAMIC_SHAPES)                      |
+-------------------------+-----------------------------------------------------------------------------+
| Draw circle             | Disabled by default (see above: ENABLE_DYNAMIC_SHAPES)                      |
+-------------------------+-----------------------------------------------------------------------------+
| Fill circle             | Disabled by default (see above: ENABLE_DYNAMIC_SHAPES)                      |
+-------------------------+-----------------------------------------------------------------------------+
| Draw image              | ARGB8888, RGB565, A8                                                        |
+-------------------------+-----------------------------------------------------------------------------+
| Draw thick faded line   | Only with fade <= 1                                                         |
+-------------------------+-----------------------------------------------------------------------------+
| Draw thick faded circle | Only with fade <= 1, disabled by default (see above: ENABLE_DYNAMIC_SHAPES) |
+-------------------------+-----------------------------------------------------------------------------+
| Draw thick line         |                                                                             |
+-------------------------+-----------------------------------------------------------------------------+
| Draw thick circle       | Disabled by default (see above: ENABLE_DYNAMIC_SHAPES)                      |
+-------------------------+-----------------------------------------------------------------------------+
| Draw rotated image      | See draw image                                                              |
+-------------------------+-----------------------------------------------------------------------------+
| Draw scaled image       | See draw image                                                              |
+-------------------------+-----------------------------------------------------------------------------+

This C module is available on the :ref:`developer_repository`: `com.microej.clibrary.llimpl#microui-nemagfx`_.

.. _com.microej.clibrary.llimpl#microui-nemagfx: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/llimpl/microui-nemagfx/

Compatibility
=============

The compatibility between the components (Packs, C modules, and Libraries) is described in the :ref:`section_ui_releasenotes_cmodule`.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
