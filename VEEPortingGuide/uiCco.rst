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

This C module is divided in several parts and each part provides an implementation of some :ref:`MicroUI Abstraction Layer APIs <section_display_llapi>`.
This C module is **mandatory** (the C files must be compiled in the BSP) but some C files are optional.

This C module is available on the :ref:`central_repository`: `com.microej.clibrary.llimpl#microui`_.

Drawings
--------

Overview
""""""""

The aim of this part is to facilitate the MicroUI Painter classes implementation:

1. It manages the synchronization with the Graphics Engine (see ``LLUI_DISPLAY_requestDrawing()``).
2. It checks the drawing parameters: clip, opacity, thickness, fade, image status, etc.
3. It logs the drawing	(see :ref:`microui_traces`).
4. It deports the rendering to ``ui_drawing.h``.

The implementation of ``ui_drawing.h`` depends on several options:

* If the BSP provides or not a :ref:`renderer <section_drawings_cco>` (software and / or hardware as a GPU),
* If the BSP is configured to manage :ref:`several destination formats <section_bufferedimage_cco>`,
* If the BSP is configured to manage :ref:`custom image formats <section_renderer_cco>`.

Files
"""""

* Implements: ``LLUI_PAINTER_impl.h`` and ``LLDW_PAINTER_impl.h``.
* C files: ``LLUI_PAINTER_impl.c``, ``LLDW_PAINTER_impl.c``, ``ui_drawing_stub.c``, ``ui_drawing.c`` and ``ui_image_drawing.c``.
* Status: mandatory.

Usage
"""""

1. Add all C files in the BSP project.

Images Heap
-----------

Overview
""""""""

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

Files
"""""

* Implements the functions of	``LLUI_DISPLAY_impl.h`` whose prefix is ``LLUI_DISPLAY_IMPL_image_heap_``.
* C file: ``LLUI_DISPLAY_HEAP_impl.c``.
* Status: optional.

Usage
"""""

1. To use the Graphics Engine's allocator, do not add the file ``LLUI_DISPLAY_HEAP_impl.c`` in the BSP project.
2. To use the C module's allocator, add the file ``LLUI_DISPLAY_HEAP_impl.c`` in the BSP project.
3. To use a third-party allocator, do not add the file ``LLUI_DISPLAY_HEAP_impl.c`` in the BSP project and implements the ``LLUI_DISPLAY_IMPL_image_heap_xxx`` functions.

Events Logger
-------------

Overview
""""""""

This part is only mandatory when the BSP is calling ``LLUI_INPUT_dump()``, see :ref:`section_inputs_eventbuffer`.
If not included, the call to ``LLUI_INPUT_dump()`` performs nothing. 
Its aim is to log the MicroUI events and to provide an events dumper. 

The logger adds some metadata to each MicroUI event in a dedicated array. 
When the BSP is calling ``LLUI_INPUT_dump()``, the logger is using its data to decode the events. 
Then it uses an implementation of ``microui_event_decoder.h`` to describe the events.

Files
"""""

* Implements the functions of ``LLUI_INPUT_impl.h`` whose prefix is ``LLUI_INPUT_IMPL_log_``.
* C files: ``LLUI_INPUT_LOG_impl.c`` and ``microui_event_decoder.c``.
* Status: optional.

Usage (to enable the events logger)
"""""""""""""""""""""""""""""""""""

1. Add all C files in the BSP project.
2. Configure the options in ``microui_event_decoder_conf.h`` (by default the logger is disabled).

Buffer Refresh Strategy
-----------------------

Overview
""""""""

This part provides three Buffer Refresh Strategies (BRS): ``predraw``, ``single`` and ``legacy``.
Refer to the chapter BRS XXX_TODO add link to have more information on these strategies.
These strategies are optional; when no strategy is selected, the BSP must provide its own strategy.

Some strategies require an implementation of ``UI_DISPLAY_BRS_restore()`` (see ``ui_display_brs.h``).
A weak implementation is available; this implementation uses the function ``memcpy()``.

Files
"""""

* Implements the functions of ``LLUI_DISPLAY_impl.h`` related to the BRS XXX_TODO add link: ``LLUI_DISPLAY_IMPL_refresh()``, ``LLUI_DISPLAY_IMPL_notify_drawing_region()`` and ``LLUI_DISPLAY_IMPL_notify_dirty_region()``.
* C files: ``ui_display_brs_legacy.c``, ``ui_display_brs_predraw.c``, ``ui_display_brs_single.c``, ``ui_display_brs.c`` and ``ui_rect_util.c``.
* Status: optional.

Usage
"""""

1. Add all C files in the BSP project (whatever the strategy).
2. Configure the options in ``ui_display_brs_configuration.h``.
3. Comment the line ``#error [...]"``.
4. (optional) Implement ``UI_DISPLAY_BRS_restore()`` (using a GPU for instance).  

.. _com.microej.clibrary.llimpl#microui: https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui/

.. _section_ui_c_module_microui_dma2d:

C Module: MicroUI Over DMA2D
============================

Overview
--------

This C module is a specific implementation of the C module MicroUI over STM32 DMA2D (Chrom-ART Graphics Accelerator):

* It implements a set of drawings over the official Chrom-ART Graphics Accelerator API.
* It is compatible with several STM32 MCU: ``STM32F4XX```, ``STM32F7XX``` and ``STM32H7XX```.
* It manages several configurations of memory cache.
* It is compatible with the :ref:`multiple destination formats <section_bufferedimage_cco>` (but it manages only one destination format).
* It is compatible with the Buffer Refresh Strategies (BRS) XXX_TODO link ``predraw``, ``single`` and ``legacy`` (switch).

This C module is available on the :ref:`central_repository`: `com.microej.clibrary.llimpl#display-dma2d`_.

Files
-----

* Implements some functions of ``ui_drawing.h`` (see above).
* C file: ``ui_drawing_dma2d.c``.
* Status: optional.

Usage
-----

1. Add the C file in the BSP project.
2. Add the BSP global define ``DRAWING_DMA2D_BPP`` to specify the destination format: 16, 24 or 32 respectively ``DMA2D_RGB565``, ``DMA2D_RGB888`` and ``DMA2D_ARGB8888``.
3. Call ``UI_DRAWING_DMA2D_initialize()`` from ``LLUI_DISPLAY_IMPL_initialize()``.

Drawings
--------

The following table describes the accelerated drawings:

+----------------+-----------------------------------------------------------+
| Feature        | Comment                                                   |
+================+===========================================================+
| Fill rectangle |                                                           |
+----------------+-----------------------------------------------------------+
| Draw image     | ARGB8888, RGB888, RGB565, ARGB1555, ARGB4444, A8, A4 [1]_ |
+----------------+-----------------------------------------------------------+

.. [1] The first and last odd columns are drawn in software (GPU memory alignment constraints). 

Cache
-----

Some STM32 MCU use a memory cache. 

This cache must be cleared before using the DMA2D: 

* before the call to ``HAL_DMA2D_Start_IT()``.
* before the call to ``HAL_DMA2D_BlendingStart_IT()``.

Usage
"""""

1. Check the configuration of the define ``DRAWING_DMA2D_CACHE_MANAGEMENT`` in ``ui_drawing_dma2d_configuration.h``.

Buffer Refresh Strategy "PreDraw"
---------------------------------

This strategy requires to copy some regions from the LCD frame buffer to the back buffer on demand (function ``UI_DISPLAY_BRS_restore()``, see above).
To perform these copies, this CCO uses the ``UI_DRAWING_DMA2D_xxx_memcpy()`` functions.

Usage
"""""

1. The function ``UI_DRAWING_DMA2D_IRQHandler()`` must be call from the DMA2D IRQ routine.
2. The function ``UI_DRAWING_DMA2D_memcpy_callback()`` should not be implemented (useless).

Example of Implementation
"""""""""""""""""""""""""

.. code-block:: c

   void LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t flush_identifier, const ui_rect_t regions[], size_t length) {
      
      // store the flush identifier
      g_current_flush_identifier = flush_identifier;
      
      // change the LCD buffer address
      HAL_LTDC_SetAddress(&hLtdcHandler, (uint32_t)LLUI_DISPLAY_getBufferAddress(&gc->image), LTDC_ACTIVE_LAYER);
      
      // ask an interrupt for next LCD tick
      lcd_enable_interrupt();
   }

   void LTDC_IRQHandler(LTDC_HandleTypeDef *hltdc) {
      // LTDC register reload
      __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_RR);
      
      // notify the MicroUI Graphics Engine 
      uint8_t* buffer = (uint8_t*)(BACK_BUFFER == LTDC_Layer->CFBAR ? FRAME_BUFFER : BACK_BUFFER);
      LLUI_DISPLAY_setDrawingBuffer(g_current_flush_identifier, buffer, from_isr);
   }

   void DMA2D_IRQHandler(void) {
      // call CCO DMA2D function
      UI_DRAWING_DMA2D_IRQHandler();
   }

Buffer Refresh Strategy "Single"
--------------------------------

Usually, this strategy is used when the LCD frame buffer cannot be mapped dynamically: the same buffer is always used as back buffer.
However, the LCD frame buffer can be mapped on a memory buffer that is in the CPU addresses range.
In that case, the ``UI_DRAWING_DMA2D_xxx_memcpy()`` functions can be used to copy the content of the back buffer to the LCD frame buffer.

Usage
"""""

1. The function ``UI_DRAWING_DMA2D_configure_memcpy()`` must be called from the implementation of ``LLUI_DISPLAY_IMPL_flush()``.
2. The function ``UI_DRAWING_DMA2D_start_memcpy()`` must be call from the LCD controller IRQ routine.
3. The function ``UI_DRAWING_DMA2D_IRQHandler()`` must be call from the DMA2D IRQ routine.
4. The function ``UI_DRAWING_DMA2D_memcpy_callback()`` must be implemented to unlock the MicroUI Graphics Engine.

Example of Implementation
"""""""""""""""""""""""""
.. code-block:: c

   void LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t flush_identifier, const ui_rect_t regions[], size_t length) {
      
      // store the flush identifier
      g_current_flush_identifier = flush_identifier;
      
      // configure the copy to launch at next LCD tick
      UI_DRAWING_DMA2D_configure_memcpy(LLUI_DISPLAY_getBufferAddress(&gc->image), (uint8_t*)LTDC_Layer->CFBAR, regions[0].x1, regions[0].y1, regions[0].x2, regions[0].y2, RK043FN48H_WIDTH, &dma2d_memcpy);
      
      // ask an interrupt for next LCD tick
      lcd_enable_interrupt();
   }

   void LTDC_IRQHandler(LTDC_HandleTypeDef *hltdc) {
      // clear interrupt flag
      LTDC->ICR = LTDC_IER_FLAG;

      // launch the copy from back buffer to frame buffer
      UI_DRAWING_DMA2D_start_memcpy(&dma2d_memcpy);
   }

   void DMA2D_IRQHandler(void) {
      // call CCO DMA2D function
      UI_DRAWING_DMA2D_IRQHandler();
   }

   void UI_DRAWING_DMA2D_memcpy_callback(bool from_isr) {
      // notify the MicroUI Graphics Engine 
      LLUI_DISPLAY_setDrawingBuffer(g_current_flush_identifier, (uint8_t*)BACK_BUFFER, from_isr);
   }

Buffer Refresh Strategy "Legacy"
---------------------------------

This strategy requires to copy the past (the previous drawings) from the LCD frame buffer to the back buffer before unlocking the MicroUI Graphics Engine.
To perform this copy, this CCO uses the ``UI_DRAWING_DMA2D_xxx_memcpy()`` functions.
At the end of the copy, the MicroUI Graphics Engine is unlocked: a new drawing can be performed in the new back buffer.

Usage
"""""

1. The function ``UI_DRAWING_DMA2D_configure_memcpy()`` must be called from the implementation of ``LLUI_DISPLAY_IMPL_flush()``.
2. The function ``UI_DRAWING_DMA2D_start_memcpy()`` must be call from the LCD controller IRQ routine.
3. The function ``UI_DRAWING_DMA2D_IRQHandler()`` must be call from the DMA2D IRQ routine.
4. The function ``UI_DRAWING_DMA2D_memcpy_callback()`` must be implemented to unlock the MicroUI Graphics Engine.

Example of Implementation
"""""""""""""""""""""""""
.. code-block:: c

   void LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t flush_identifier, const ui_rect_t regions[], size_t length) {
      
      // store the flush identifier
      g_current_flush_identifier = flush_identifier;
      
      // configure the copy to launch at next LCD tick
      UI_DRAWING_DMA2D_configure_memcpy(LLUI_DISPLAY_getBufferAddress(&gc->image), (uint8_t*)LTDC_Layer->CFBAR, regions[0].x1, regions[0].y1, regions[0].x2, regions[0].y2, RK043FN48H_WIDTH, &dma2d_memcpy);
      
      // change the LCD buffer address
      HAL_LTDC_SetAddress(&hLtdcHandler, (uint32_t)LLUI_DISPLAY_getBufferAddress(&gc->image), LTDC_ACTIVE_LAYER);
      
      // ask an interrupt for next LCD tick
      lcd_enable_interrupt();
   }

   void HAL_LTDC_ReloadEventCallback(LTDC_HandleTypeDef *hltdc) {
      // LTDC register reload
      __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_RR);

      // launch the copy from new frame buffer to new back buffer
      UI_DRAWING_DMA2D_start_memcpy(&dma2d_memcpy);
   }

   void DMA2D_IRQHandler(void) {
      // call CCO DMA2D function
      UI_DRAWING_DMA2D_IRQHandler();
   }

   void UI_DRAWING_DMA2D_memcpy_callback(bool from_isr) {
      // notify the MicroUI Graphics Engine 
      uint8_t* buffer = (uint8_t*)(BACK_BUFFER == LTDC_Layer->CFBAR ? FRAME_BUFFER : BACK_BUFFER);
      LLUI_DISPLAY_setDrawingBuffer(g_current_flush_identifier, buffer, from_isr);
   }

.. _com.microej.clibrary.llimpl#display-dma2d: https://repository.microej.com/modules/com/microej/clibrary/llimpl/display-dma2d/

.. _section_ui_c_module_microui_vglite:

C Module: MicroUI Over VGLite
=============================

Overview
--------

This C module is a specific implementation of the C module MicroUI over the VG-Lite library 3.0.15_rev7:

* It implements a set of drawings over the official VG-Lite library 3.0.15_rev7.
* It is compatible with the :ref:`multiple destination formats <section_bufferedimage_cco>`.

This C module also provides a set of header files (and their implementations) to manipulate some MicroUI concepts over the VGLite library: image management, path format, etc.: ``ui_vglite.h`` and ``ui_drawing_vglite_path.h``.

This C module is available on the :ref:`developer_repository`: `com.microej.clibrary.llimpl#microui-vglite`_.

Files
"""""

* Implements some functions of ``ui_drawing.h`` (see above).
* C files: ``ui_drawing_vglite_path.c``, ``ui_drawing_vglite_process.c``, ``ui_drawing_vglite.c`` and ``ui_vglite.c``.
* Status: optional.

Usage
"""""

1. Add the C files in the BSP project.
2. Call ``UI_VGLITE_init()`` from ``LLUI_DISPLAY_IMPL_initialize()``.
3. Configure the options in ``ui_vglite_configuration.h``.
4. Comment the line ``#error [...]"``.
5. Call ``UI_VGLITE_IRQHandler()`` during the GPU interrupt routine.
6. Set the VG-Lite library's preprocessor define ``VG_DRIVER_SINGLE_THREAD``.
7. VG-Lite library must be patched to be CCO compliant:

   .. code-block:: bash

         cd [...]/sdk/middleware/vglite
         patch -p1 < [...]/3.0.15_rev7.patch

8. In the file ``vglite_window.c``, add the function ``VGLITE_CancelSwapBuffers()`` and its prototype in ``vglite_window.h``:

   .. code-block:: c
      
         void VGLITE_CancelSwapBuffers(void) {   
            fb_idx = fb_idx == 0 ? (APP_BUFFER_COUNT - 1) : (fb_idx ) - 1;
         }

Options
-------

This C module provides some drawing algorithms that are disabled by default. 

* The rendering time of a simple shape with the GPU (time in the VG-Lite library + GPU setup time + rendering time) is longer than with software rendering. To enable the hardware rendering for simple shapes, uncomment the definition of ``VGLITE_USE_GPU_FOR_SIMPLE_DRAWINGS``  in ``ui_vglite_configuration.h``.
* The rendering time of an RGB565 image into an RGB565 buffer without applying an opacity (alpha == 0xff) is longer than with software rendering (as this kind of drawing consists in performing a mere memory copy). To enable the hardware rendering for RGB565 images, uncomment the definition of ``VGLITE_USE_GPU_FOR_RGB565_IMAGES``  in ``ui_vglite_configuration.h``.
* ARGB8888, ARGB1555, and ARGB4444 transparent images may not be compatible with some revisions of the VG-Lite GPU. Older GPU revisions do not render transparent images correctly because the pre-multiplication of the pixel opacity is not propagated to the pixel color components. To force the hardware rendering for non-premultiplied transparent images when the VG-Lite GPU is not compatible, uncomment the definition of ``VGLITE_USE_GPU_FOR_TRANSPARENT_IMAGES``  in ``ui_vglite_configuration.h``. Note that this limitation does not concern the VG-Lite GPU compatible with non-premultiplied transparent images and the A8/A4 formats.

Drawings
--------

The following table describes the accelerated drawings:

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

Compatibility With MCU i.MX RT595
---------------------------------

UI Pack 13
""""""""""

The versions of the C Module Over VGLite (before ``7.0.0``) included an implementation of the Low-Level API ``LLUI_DISPLAY_impl.h``.
This support has been extracted into a dedicated C Module since the version ``7.0.0``.
The dedicated C Module is available on the :ref:`developer_repository`: `com.microej.clibrary.llimpl#microui-mimxrt595-evk`_.

Only the C Module `com.microej.clibrary.llimpl#microui-vglite`_ is useful to target the Vivante VG-Lite GPU to perform the MicroUI and MicroVG drawings.
The C Module `com.microej.clibrary.llimpl#microui-mimxrt595-evk`_ only gives an example of an implementation compatible with the MCU i.MX RT595 MCU.

.. note:: For more information, see the :ref:`migration notes<section_ui_migrationguide_13.6_mimxrt595evk>`.

UI Pack 14
""""""""""

Since UI Pack 14, this C module is not compatible anymore and not maintained.

.. _com.microej.clibrary.llimpl#microui-vglite: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/llimpl/microui-vglite/
.. _com.microej.clibrary.llimpl#microui-mimxrt595-evk: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/llimpl/microui-mimxrt595-evk/

.. _section_ui_c_module_microui_nemagfx:

C Module: MicroUI Over NemaGFX
==============================

Overview
--------

This C module is a specific implementation of the C module MicroUI over the Think Silicon NemaGFX:

* It implements a set of drawings over the official Think Silicon NemaGFX.
* It is compatible with the :ref:`multiple destination formats <section_bufferedimage_cco>` (but it manages only one destination format).

This C module is available on the :ref:`developer_repository`: `com.microej.clibrary.llimpl#microui-nemagfx`_.

.. _com.microej.clibrary.llimpl#microui-nemagfx: https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/llimpl/microui-nemagfx/

Files
-----

* Implements some functions of ``ui_drawing.h`` (see above).
* C file: ``ui_drawing_nema.c``.
* Status: optional.

Usage
-----
1. Add the C file in the BSP project.
2. Call ``UI_DRAWING_NEMA_initialize()`` from ``LLUI_DISPLAY_IMPL_initialize()``.
3. Configure the options in ``ui_drawing_nema_configuration.h``.
4. Comment the line ``#error [...]"``.
5. Choose between *interrupt mode* and *task mode* (see Implementation).

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

Drawings
--------

The following table describes the accelerated drawings:

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

Compatibility
=============

The compatibility between the components (Packs, C modules, and Libraries) is described in the :ref:`section_ui_releasenotes_cmodule`.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
