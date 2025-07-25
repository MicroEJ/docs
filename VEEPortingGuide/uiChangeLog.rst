.. include:: uiReplaces.rst

.. _section_ui_changelog:

=========
Changelog
=========

.. _section_ui_changelog_14_4_2:

[14.4.2] - 2025-05-20
=====================

Known Issues
""""""""""""

- Some SystemView logs are not identified, example: ``Function #586 Returns 0x0 after 169.844 us``.

  - Reason: The new C header file  ``ui_log.h`` (in the C Module MicroUI) defines some invalid log identifiers:
  
	.. code-block:: c

		#define UI_LOG_drawThickFadedPoint 70
		[...]
		#define UI_LOG_drawRotatedCharacter 95
	
  - Workaround: Change manually the log identifiers:
  
	.. code-block:: c

		#define UI_LOG_drawThickFadedPoint 110
		#define UI_LOG_drawThickFadedLine 111
		#define UI_LOG_drawThickFadedCircle 112
		#define UI_LOG_drawThickFadedCircleArc 113
		#define UI_LOG_drawThickFadedEllipse 114
		#define UI_LOG_drawThickLine 115
		#define UI_LOG_drawThickCircle 116
		#define UI_LOG_drawThickEllipse 117
		#define UI_LOG_drawThickCircleArc 118
		#define UI_LOG_drawFlippedImage 130
		#define UI_LOG_drawRotatedImage 131
		#define UI_LOG_drawScaledImage 132
		#define UI_LOG_drawScaledString 133
		#define UI_LOG_drawScaledRenderableString 134
		#define UI_LOG_drawRotatedCharacter 135

VG Pack
"""""""

**Fixed**

- Fix the VEE Port build with the UI Pack 14.4 and the VG Pack 1.7 (since UI Pack 14.4.1).

FrontPanel
""""""""""

**Fixed**

- Fix the use of the SDK5 option "Resolve in workspace" (since UI Pack 14.4.1).

C Module MicroUI
""""""""""""""""

**Known Issues**

- see above.

C Module DMA2D
""""""""""""""

**Fixed**

- Fix the implementation of ``UI_DRAWING_DMA2D_copyImage()`` to use the right software algorithm.

C Module VGLite
"""""""""""""""

**Fixed**

- Fix the implementation of ``UI_DRAWING_VGLITE_copyImage()`` to use the right software algorithm.
- Fix the premultiplication of the format ARGB1555: it is useless.

C Module NemaGFX
""""""""""""""""

**Fixed**

- Fix the rendering of a RGB565 image with a transparent opacity.
- Fix the implementation of ``UI_DRAWING_NEMA_copyImage()`` to use the right software algorithm.

.. _section_ui_changelog_14_4_1:

[14.4.1] - 2025-03-13
=====================

Known Issues
""""""""""""

- This version is not compatible with the VG Pack (any versions): 

  - Reason: A VEE Port with this UI Pack and a VG Pack cannot be built:

	.. code-block:: bash

		[java] microvg/ui-pack:
		[java] C:\[...]-configuration\target~\scripts\rip\build\autoConfiguration-microvg.xml:43: VG Pack requires the UI Pack 14.1.0 or higher and the platform fetches the UI Pack ${ui.packVersion}.

  - Workaround: None, use the UI Pack 14.3.3 instead.

- Some SystemView logs are not identified, example: ``Function #586 Returns 0x0 after 169.844 us``.

  - Reason: The new C header file  ``ui_log.h`` (in the C Module MicroUI) defines some invalid log identifiers:
  
	.. code-block:: c

		#define UI_LOG_drawThickFadedPoint 70
		[...]
		#define UI_LOG_drawRotatedCharacter 95
	
  - Workaround: Change manually the log identifiers:
  
	.. code-block:: c

		#define UI_LOG_drawThickFadedPoint 110
		#define UI_LOG_drawThickFadedLine 111
		#define UI_LOG_drawThickFadedCircle 112
		#define UI_LOG_drawThickFadedCircleArc 113
		#define UI_LOG_drawThickFadedEllipse 114
		#define UI_LOG_drawThickLine 115
		#define UI_LOG_drawThickCircle 116
		#define UI_LOG_drawThickEllipse 117
		#define UI_LOG_drawThickCircleArc 118
		#define UI_LOG_drawFlippedImage 130
		#define UI_LOG_drawRotatedImage 131
		#define UI_LOG_drawScaledImage 132
		#define UI_LOG_drawScaledString 133
		#define UI_LOG_drawScaledRenderableString 134
		#define UI_LOG_drawRotatedCharacter 135

MicroUI
"""""""

**Changed**

- Improve the trace events (SystemView description file `SYSVIEW_MicroUI.txt` is updated).
- Change some log identifiers to be backward compatible with the UI Pack since version 12.1.5.

FrontPanel
""""""""""

**Added**

- Add a button to start/stop the recording of the drawings in the Flush Visualizer.
- Add the class ``Log`` that provides utility methods to log the drawings.
- Add ``MicroUIImage.getIdentifier()`` that identifies an image (useful for the logs).
- Add the same logs as embedded side (all drawings, out of clip, drawn regions, etc.).

**Changed**

- Improve the content of the tree of the drawing operations in the Flush Visualizer.
- Show the time between two frames in the Flush Visualizer.
- Use the core property ``core.trace.enabled`` to enable the Flush Visualizer.
- Do not draw if the clip is empty (align behavior between the simulator and the embedded side). 

**Fixed**

- Fix the execution of the Front Panel in the HIL classpath (VEE Port with UI and application without UI; since UI Pack 14.3.0).
- Fix the use of the logs in the mode ``s3.board.compliant`` (Use target characteristics).

**Removed**

- Remove the use of the property ``ej.fp.display.flushVisualizer`` (replaced by ``core.trace.enabled``). 

C Module MicroUI
""""""""""""""""

**Added**

- Add some logs: out of clip, drawn region, etc.
 
**Changed**

- Gather all logs identifiers and functions in ``ui_log.c``.
- Log all drawing parameters. 

**Removed**

- Remove some logs of the BRS management.

**Known Issues**

- see above.

.. _section_ui_changelog_14_3_3:

[14.3.3] - 2025-02-18
=====================

FrontPanel
""""""""""

**Fixed**

- Fix the five issues of the UI Pack 14.3.2 (see below).

.. _section_ui_changelog_14_3_2:

[14.3.2] - 2025-02-10
=====================

FrontPanel
""""""""""

**Fixed**

- Fix the performance issue of ``LLUIDisplay.convertRegion()`` when using the Front Panel Framework 1.3.0.

**Known Issues**

.. warning:: The following issues concern the UI Packs **14.3.0** and **14.3.2**.

*Front Panel*

- On non-rectangular displays (see :ref:`section_ui_simulation_display`), the Front Panel widget display's filter sometimes disappears partially, causing some visual glitches around the display.
- The rendering of Front Panel widgets other than the display is truncated: the right and bottom lines (1 pixel thick) are missing.
  This is caused by the widget rendering clip being too small.
  As a workaround, you can increase the size of each widget image with empty lines on the right and bottom sides.
- With a zoom other than 1:1, some Front Panel widgets other than the display may not be rendered, or may be truncated.

*Flush Visualizer*

- A native Concurrent Exception may be thrown during application animations.
  This is due to the drawing storage not being synchronized with the Flush Visualizer text file dump.
- On non-rectangular displays (see :ref:`section_ui_simulation_display`), the Front Panel widget display's filter sometimes disappears partially, causing some visual glitches around the display in the screenshot.

.. _section_ui_changelog_14_3_0:

[14.3.0] - 2025-01-24
=====================

FrontPanel
""""""""""

**Added**

- Add the class ``ej.fp.widget.display.Rectangle`` (extracted from ``ej.tool.frontpanel#widget#4.0.2``).
- Add all MicroUI and Drawing algorithms in the Flush Visualizer traces.
- Add a toolbar with various options (zoom, etc.).
- Add a statusbar with various information (current zoom, coordinates, etc.).
- Add the ability to resize and/or scroll the Front Panel.

**Changed**

- Speed up the drawing of images whose format is identical to the display, without transparency or transformation.
- Display a tree of regions and drawings in the Flush Visualizer traces.
- Use the Front Panel Framework 1.3.0 to implement ``LLUIDisplay.convertRegion()``.

ImageGenerator
""""""""""""""

**Fixed**

- Fix the usage of an incompatible or corrupted cache (drop it).

FontGenerator
"""""""""""""

**Fixed**

- Fix the usage of an incompatible or corrupted cache (drop it).

.. _section_ui_changelog_14_2_0:

[14.2.0] - 2024-11-18
=====================

ImageGenerator
""""""""""""""

**Added**

- Add the options ``grayscale`` and ``alpha`` for the output formats ``A8``, ``A4``, ``A2``, ``A1`` and ``A8_RLE``.

  - ``grayscale`` means black pixels are encoded as fully opaque pixels and white pixels as fully transparent pixels.
  - ``alpha`` only encodes the opacity element like the MicroUI ``OutputFormat#A8``.
  - No option defaults to ``grayscale`` for backward compatibility.
  - An invalid option prevents the encoding of the image.

**Changed**

- Make the cache faster.

FontGenerator
"""""""""""""

**Added**

- Add the support of ``.fnt`` files.

**Changed**

- Make the cache faster.

**Fixed**

- Fix the computing of fonts heap usage when using cache.

.. _section_ui_changelog_13_7_3:

[13.7.3] - 2024-10-18
=====================

FontGenerator
"""""""""""""

**Fixed**

- Fix the management of the kernel's fonts on the simulator (mode Multi-Sandbox).

.. _section_ui_changelog_14_1_1:

[14.1.1] - 2024-10-17
=====================

MicroUI
"""""""

* Implement `MicroUI API 3.6.0`_ (new ``Font`` management).

**Added**

- Add some SystemView logs to trace the new MicroUI 3.6 APIs.

Drawing
"""""""

**Fixed**

- Fix the invalid ``StringIndexOutOfBoundsException`` when drawing the last character of a string using ``TransformPainter.drawScaledSubstringBilinear()``.

FrontPanel
""""""""""

**Added**

- Add the classes, interfaces, enumeration, registration and utility methods to implement the drawing of strings and the handling of custom fonts.
- Add ``LLUIDisplay.getByteOrder()`` to retrieve the embedded VEE Port's memory endianness.
- Add the API ``LLUIDisplay.isImageClosed()`` to replace the deprecated API ``LLUIDisplay.isClosed()``.

**Changed**

- Deprecate the API ``LLUIDisplay.isClosed()``: use ``LLUIDisplay.isImageClosed()`` instead.

ImageGenerator
""""""""""""""

**Changed**

- Speed-up the generation when the cache is used.

FontGenerator
"""""""""""""

**Changed**

- Speed-up the generation when the cache is used.

**Fixed**

- Fix the management of the kernel's fonts on the simulator (mode Multi-Sandbox).

LLAPIs
""""""

**Added**

- Add the LLAPI (implemented by the MicroUI C Module):

	- ``LLUI_PAINTER_IMPL_drawString()``
	- ``LLUI_PAINTER_IMPL_stringWidth()``
	- ``LLUI_PAINTER_IMPL_initializeRenderableStringSNIContext()``
	- ``LLUI_PAINTER_IMPL_drawRenderableString()``
	- ``LLDW_PAINTER_IMPL_drawScaledStringBilinear()``
	- ``LLDW_PAINTER_IMPL_drawScaledRenderableStringBilinear()``
	- ``LLDW_PAINTER_IMPL_drawCharWithRotationBilinear()``
	- ``LLDW_PAINTER_IMPL_drawCharWithRotationNearestNeighbor()``

- Add the software drawing APIs (implemented by the Graphics Engine):

	- ``UI_DRAWING_SOFT_drawString()``
	- ``UI_DRAWING_SOFT_drawRenderableString()``
	- ``UI_DRAWING_SOFT_stringWidth()``
	- ``UI_DRAWING_SOFT_initializeRenderableStringSNIContext()``
	- ``UI_DRAWING_SOFT_drawChar()``
	- ``DW_DRAWING_SOFT_drawScaledStringBilinear()``
	- ``DW_DRAWING_SOFT_drawScaledRenderableStringBilinear()``
	- ``DW_DRAWING_SOFT_drawCharWithRotationBilinear()``
	- ``DW_DRAWING_SOFT_drawCharWithRotationNearestNeighbor()``

- Add the enumeration ``MICROUI_FontFormat`` that lists the MicroUI custom font formats.
- Add the structure ``MICROUI_Font`` that represents a MicroUI Font (``Font.getSNIContext()``).
- Add the structure ``MICROUI_RenderableString`` that represents a MicroUI RenderableString (``RenderableString.getSNIContext()``).
- Add the API ``LLUI_DISPLAY_isImageClosed()`` to replace the deprecated API ``LLUI_DISPLAY_isClosed()``.

**Changed**

- Deprecate the API ``LLUI_DISPLAY_isClosed()``: use ``LLUI_DISPLAY_isImageClosed()`` instead.

C Module MicroUI
""""""""""""""""

**Added**

- Add ``ui_configuration.h`` that provides macros to configure some low level APIs.
- Add ``ui_font_drawing.h`` that provides functions to handle custom fonts.
- Add the option ``UI_FEATURE_FONT_CUSTOM_FORMATS`` to enable the management of custom fonts.
- Add the option ``UI_FEATURE_ALLOCATOR`` to replace the Graphics Engine's image heap allocator by a bestfit allocator.
- Add the implementation of the following LLAPI (plus their redirections, default implementations and logs):

	- ``LLUI_PAINTER_IMPL_drawString()``
	- ``LLUI_PAINTER_IMPL_stringWidth()``
	- ``LLUI_PAINTER_IMPL_initializeRenderableStringSNIContext()``
	- ``LLUI_PAINTER_IMPL_drawRenderableString()``
	- ``LLDW_PAINTER_IMPL_drawScaledStringBilinear()``
	- ``LLDW_PAINTER_IMPL_drawScaledRenderableStringBilinear()``
	- ``LLDW_PAINTER_IMPL_drawCharWithRotationBilinear()``
	- ``LLDW_PAINTER_IMPL_drawCharWithRotationNearestNeighbor()``

- Add the handling of custom fonts (``ui_font_drawing.c``).

**Changed**

- Gather all C Module configurations in one file: ``ui_configuration.h``.
- Harmonize the naming convention of all existing options: prefix ``UI_``.
- Replace the UI event decoder options:

	- ``LLUI_DEBUG_TRACE`` by ``UI_DEBUG_PRINT``
	- ``MICROUIEVENTDECODER_ENABLED`` by ``UI_FEATURE_EVENT_DECODER``
	- ``MICROUIEVENTDECODER_EVENTGEN_COMMAND`` by ``UI_EVENTDECODER_EVENTGEN_COMMAND``
	- ``MICROUIEVENTDECODER_EVENTGEN_BUTTONS`` by ``UI_EVENTDECODER_EVENTGEN_BUTTONS``
	- ``MICROUIEVENTDECODER_EVENTGEN_TOUCH`` by ``UI_EVENTDECODER_EVENTGEN_TOUCH``

- Replace the UI display BRS options:

	- ``UI_DISPLAY_BRS`` by ``UI_FEATURE_BRS``
	- ``UI_DISPLAY_BRS_LEGACY`` by ``UI_FEATURE_BRS_LEGACY``
	- ``UI_DISPLAY_BRS_SINGLE`` by ``UI_FEATURE_BRS_SINGLE``
	- ``UI_DISPLAY_BRS_PREDRAW`` by ``UI_FEATURE_BRS_PREDRAW``
	- ``UI_DISPLAY_BRS_DRAWING_BUFFER_COUNT`` by ``UI_FEATURE_BRS_DRAWING_BUFFER_COUNT``
	- ``UI_DISPLAY_BRS_FLUSH_SINGLE_RECTANGLE`` by ``UI_FEATURE_BRS_FLUSH_SINGLE_RECTANGLE``

- Move the option ``UI_RECT_COLLECTION_MAX_LENGTH`` to ``ui_configuration.h``.
- Replace the option ``LLUI_GC_SUPPORTED_FORMATS`` by ``UI_GC_SUPPORTED_FORMATS``.
- Replace the option ``LLUI_IMAGE_CUSTOM_FORMATS`` by ``UI_FEATURE_IMAGE_CUSTOM_FORMATS``.

**Removed**

- Remove ``microui_event_decoder_conf.h``: import ``ui_configuration.h`` instead.
- Remove ``ui_display_brs_configuration.h``: import ``ui_configuration.h`` instead.

C Module DMA2D
""""""""""""""

**Changed**

- Make this C Module compatible with the MicroUI C Module 14.1.1.

C Module VGLite
""""""""""""""""

**Changed**

- Make this C Module compatible with the MicroUI C Module 14.1.1.

C Module NemaGFX
""""""""""""""""

**Changed**

- Make this C Module compatible with the MicroUI C Module 14.1.1.

.. _section_ui_changelog_14_0_3:

[14.0.3] - 2024-10-01
=====================

MicroUI
"""""""

**Fixed**

* Fix the ``IllegalArgumentException`` being caught and not logged in ``Displayable.handleEvent()``.
* Fix unexpected exception when killing a feature while MicroUI is not yet started.
* Fix the permissions: ``getName()`` and ``getActions()`` returned ``null``.
* Fix the log when calling ``Image.getImage()``.

FrontPanel
""""""""""

**Fixed**

* A VEE port's buffered image provider can be ignored (which prevents opening buffered images in a format other than the display format).

LLAPIs
""""""

**Changed**

* Check the ``LLUI_DISPLAY_SInitData`` values set by the BSP (``LLUI_DISPLAY_IMPL_initialize()``) before initializing the Graphics Engine.

.. _section_ui_changelog_14_0_2:

[14.0.2] - 2024-07-26
=====================

MicroUI
"""""""

**Fixed**

* Fix the rendering of anti-aliased arcs for some compilers (rounding issue).
* Fix a synchronization issue that may cause invalid parameters to be sent in the flush request.

Front Panel
"""""""""""

**Fixed**

* Fix the infinite waiting on a display event when killing a feature.

.. _section_ui_changelog_14_0_1:

[14.0.1] - 2024-04-09
=====================

MicroUI
"""""""

* Implement `MicroUI API 3.5.0`_.

**Fixed**

* Fix the infinite waiting on a display event when killing a feature.
* Fix the dump of the events queue when it is full.

Front Panel
"""""""""""

**Added**

* Add ``LLUIDisplayImpl.getCurrentBackBuffer()`` (replace ``LLUIDisplayImpl.getCurrentDrawingBuffer()``).

**Changed**

* Homogenize the notions of back and front buffers.
* Set ``LLUIDisplayImpl.getCurrentDrawingBuffer()`` as deprecated: implement ``LLUIDisplayImpl.getCurrentBackBuffer()`` instead.

LLAPIs
""""""

**Changed**

* Homogenize the notions of back and front buffers: ``LLUI_DISPLAY_setBackBuffer()`` replaces ``LLUI_DISPLAY_setDrawingBuffer()``.

C Module MicroUI
""""""""""""""""

* New version: `C Module MicroUI 4.0.1`_.

**Changed**

* Homogenize the notions of back and front buffers.

**Fixed**

* Disable the clip before calling ``UI_DISPLAY_BRS_restore()``.

C Module DMA2D
""""""""""""""

* New version: `C Module DMA2D 5.0.1`_.

**Changed**

* Homogenize the notions of back and front buffers.

C Module VGLite
"""""""""""""""

* New version: `C Module VGLite 8.0.1`_.

**Changed**

* Homogenize the notions of back and front buffers.

C Module NemaGFX
""""""""""""""""

* New version: `C Module NemaGFX 2.0.1`_.

**Changed**

* Homogenize the notions of back and front buffers.

.. _section_ui_changelog_14_0_0:

[14.0.0] - 2024-02-14
=====================

MicroUI
"""""""

* Implement `MicroUI API 3.5.0`_.

**Added**

* Add ``GraphicsContext.notifyDrawingRegion()`` that allows the notification of a future altered region.
* Add ``Format.getSNIContext()``  and ``OutputFormat.getSNIContext()`` to identify the format in the native world.

**Changed**

* Change the semantic of the content of the back buffer after a flush: the *past* is not systematically restored.
* Clarify the message when a generic event generator specified in the VEE Port is not available in the application classpath.

**Fixed**

* Fix the drawing of thick faded circle arcs.
* Fix some linker issues on some Architectures:

  * Fix invalid linker issues (when MicroUI is not used or if another allocator is used).
  * Fix custom LCD format on VEE Port with ASLR mode (example: X86 with -pie option).
  * Remove some absolute symbols.
  * Replace sections ``.text`` by ``.rodata``.

Front Panel
"""""""""""

**Added**

* Add new APIs to manage several display buffer policies and refresh strategies (BRS):

  * Add ``LLUIDisplay.getSource()``.
  * Add ``LLUIDisplayImpl.newDrawingRegion()``.
  * Add ``LLUIDisplayImpl.getCurrentDrawingBuffer()``.
  * Add ``MicroUIImage.requestReading()``

**Changed**

* Remove ``force`` parameter in ``LLUIDisplay.requestFlush()``
* Remove all parameters in ``LLUIDisplayImpl.flush()`` and ``LLUIDisplayImpl.waitFlush()``
* Extract ``MicroUIImageFormat`` and ``MicroUIImage`` and ``MicroUIGraphicsContext`` from ``LLUIPainter``.

**Fixed**

* Fix clip and drawn area computing in flush visualizer.

**Removed**

* Remove ``MicroUIGraphicsContext.setDrawingLimits()``.

LLAPIs
""""""

**Added**

* Add the possibility to log external events in the MicroUI event group.
* Add some functions in ``LLUI_DISPLAY.h`` and ``LLUI_DISPLAY_impl.h`` to manage the display buffer refresh strategy (BRS):

  * ``LLUI_DISPLAY_getSourceImage()``.
  * ``LLUI_DISPLAY_getImageBPP()`` and ``LLUI_DISPLAY_getFormatBPP()``.
  * ``LLUI_DISPLAY_IMPL_refresh()``.
  * ``LLUI_DISPLAY_IMPL_newDrawingRegion()``.
  * ``LLUI_DISPLAY_setDrawingBuffer()``: it replaces ``LLUI_DISPLAY_flushDone()``.

**Changed**

* Change the signature of the function ``LLUI_DISPLAY_requestFlush()``: remove the boolean ``force`` (not backward compatible).
* Change the signature of the function ``LLUI_DISPLAY_IMPL_flush()``: give a list of rectangles and a flush identifier.

**Removed**

* Remove the function ``LLUI_DISPLAY_flushDone()``: replaced by ``LLUI_DISPLAY_setDrawingBuffer()``.
* Remove the function  ``LLUI_DISPLAY_setDrawingLimits()``.
* Remove the functions ``LLUI_DISPLAY_logDrawingStart()`` and ``LLUI_DISPLAY_logDrawingEnd()``: use standard logger instead.

C Module MicroUI
""""""""""""""""

* New version: `C Module MicroUI 4.0.0`_.

**Added**

* Add the possibility to log external events in the MicroUI event group.
* Add the buffer refresh strategies (BRS) Legacy, Single and Predraw.
* Add some utility functions to manipulate rectangles and collections of rectangles.

C Module DMA2D
""""""""""""""

* New version: `C Module DMA2D 5.0.0`_.

**Added**

* Add the compatibility with UI Pack 14.0.
* Add the function ``UI_DRAWING_DMA2D_memcpy_callback()`` to be notified about the end of the memory copy.
* Add the support of the display Buffer Refresh Strategies (BRS) ``PREDRAW`` and ``SINGLE``.
* Add a configuration version in ``ui_drawing_dma2d_configuration`` (``1``).

C Module VGLite
"""""""""""""""

* New version: `C Module VGLite 8.0.0`_.
* Compatible with VGLite library ``3.0.15_rev7``.

**Added**

* Add the compatibility with UI Pack 14.0.

**Removed**

* Remove the compatibility with the VGLite library ``3.0.15_rev4``.

C Module NemaGFX
""""""""""""""""

* New version: `C Module NemaGFX 2.0.0`_.

**Added**

* Add the compatibility with UI Pack 14.0.

**Fixed**

* Fix ``nema_draw_line()`` ``y1`` argument.

.. _section_ui_changelog_13_7_2:

[13.7.2] - 2023-12-21
=====================

MicroUI
"""""""

**Fixed**

* Fix the drawing of thick faded circle arcs.

FontGenerator
"""""""""""""

**Fixed**

- Fix the management of the feature's fonts on the simulator (mode Multi-Sandbox).

C Module NemaGFX
""""""""""""""""

* New version: `C Module NemaGFX 1.2.0`_.

**Changed**

* Disable the rendering of thick faded line with the GPU by default (see option ``ENABLE_FADED_LINES``).
* Increase the version of the configuration file (2).

**Fixed**

* Fix the drawing status when a thick line is out-of-clip (results in an infinite loop).

.. _section_ui_changelog_13_7_0:

[13.7.0] - 2023-10-23
=====================

MicroUI
"""""""

* Implement `MicroUI API 3.4.0`_.

**Added**

* Add the pre-multiplied image formats ``ARGB8888_PRE``, ``ARGB1555_PRE`` and ``ARGB4444_PRE``.
* Add the possibility to free third-party resources associated with images.
* Add some traces when debugging the SNI resources.

.. _MicroUI API 3.4.0: https://repository.microej.com/modules/ej/api/microui/3.4.0/

Front Panel
"""""""""""

**Added**

* Add the pre-multiplied image formats ``ARGB8888_PRE``, ``ARGB1555_PRE`` and ``ARGB4444_PRE``.

Image Generator
"""""""""""""""

**Changed**

* Do not enable the cache when generating external resources.

**Fixed**

* Do not use cached images when there is no ``.images.list`` file.
* Do not use cached images when a VEE Port property has changed.
* Fix the handling of backslashes in list files.
* Remove debug log in script.

Font Generator
""""""""""""""

**Changed**

* Do not enable the cache when generating external resources.

**Fixed**

* Do not use cached fonts when a VEE Port property has changed.
* Fix the handling of backslashes in list files.

C Module MicroUI
""""""""""""""""

* New version: `C Module MicroUI 3.1.1`_.

**Added**

* Add the compatibility with UI Pack 13.7.

C Module DMA2D
""""""""""""""

* New version: `C Module DMA2D 4.1.0`_.

**Added**

* Add the compatibility with UI Pack 13.7.

C Module VGLite
"""""""""""""""

* New version: `C Module VGLite 7.2.0`_.
* Compatible with VGLite libraries ``3.0.15_rev4`` and ``3.0.15_rev7``.

**Added**

* Add the pre-mulitplied image formats: ``ARGB8888_PRE``, ``ARGB4444_PRE`` and ``ARGB1555_PRE``.
* Add ``UI_VGLITE_need_to_premultiply()`` to find out whether a color must be pre-multiplied according to the GPU's capabilities.

**Fixed**

* Fix the use of power quad when not available.

C Module NemaGFX
""""""""""""""""

* New version: `C Module NemaGFX 1.1.0`_.

**Added**

* Add the compatibility with UI Pack 13.7.

.. _section_ui_changelog_13_6_2:

[13.6.2] - 2023-09-20
=====================

Image Generator
"""""""""""""""

**Fixed**

* Fix handling zip/jar file entries in the cache.

Font Generator
""""""""""""""

**Fixed**

* Fix handling zip/jar file entries in the cache.

C Module VGLite
"""""""""""""""

* New version: `C Module VGLite 7.1.0`_.
* Compatible with VGLite libraries ``3.0.15_rev4`` and ``3.0.15_rev7``.

**Added**

* Add the compatibility with VGLite ``3.0.15_rev7`` (add a .patch file).

**Fixed**

* Fix the use of the define ``VG_BLIT_WORKAROUND`` (useless).
* Fix the GPU deactivation when a drawing is not performed for any reason.
* VGLite ``3.0.15_rev4``: Fix the bounding box of the ``vg_lite_blit()`` given to the MicroEJ Graphics Engine when the define ``VG_BLIT_WORKAROUND`` is set (the function ``vg_lite_blit()`` is not used by default).

.. _section_ui_changelog_13_6_1:

[13.6.1] - 2023-07-26
=====================

MicroUI
"""""""

**Fixed**

* Fix creating a BufferedImage when traces are enabled.

.. _section_ui_changelog_13_6_0:

[13.6.0] - 2023-07-17
=====================

MicroUI
"""""""

* Implement `MicroUI API 3.3.0`_.

**Added**

* Add a flag stating that an undefined character was drawn.

**Fixed**

* Fix the Java compiler version used to build the MicroUI extension class to be compatible with the JDK 11.
* Fix the drawing of faded arcs and ellipses.

.. _MicroUI API 3.3.0: https://repository.microej.com/modules/ej/api/microui/3.3.0/

Front Panel
"""""""""""

**Added**

* Add the drawing log flag ``DRAWING_LOG_MISSING_CHARACTER``, stating that an undefined character was drawn.

Image Generator
"""""""""""""""

**Changed**

* Use a cache to avoid generating images for each launch.

Font Generator
""""""""""""""

**Changed**

* Use a cache to avoid generating fonts for each launch.

C Module VGLite
"""""""""""""""

* New version: `C Module VGLite 7.0.0`_.
* Compatible with VGLite library ``3.0.15_rev4``.
* Several additions, changes and fixes are available. Refer to the `C Module VGLite 7.0.0`_ changelog for more information.
* The C Module has been divided in two parts to extract the `NXP i.MX RT500`_ specific support from the generic C Module for VGLite:

  * `NXP i.MX RT500`_ Display management: `C Module RT500 7.0.0`_
  * Drawing over VGLite: `C Module VGLite 7.0.0`_

C Module NemaGFX
""""""""""""""""

* New C Module: `C Module NemaGFX 1.0.0`_.
* Compatible with UI Pack 13.5.x and 13.6.0.

.. _section_ui_changelog_13_5_1:

[13.5.1] - 2023-06-08
=====================

MicroUI
"""""""

**Fixed**

* Fix the compatibility with MicroEJ Architecture 8 (SOAR error with internal MicroUI system properties file).

Front Panel
"""""""""""

**Fixed**

* Fix consecutive calls to ``LLUIDisplay.newMicroUIImage()`` throwing an exception.
* Allow overriding the display drawer with a service or in a Front Panel widget.

C Module VGLite
"""""""""""""""

* New version: `C Module VGLite 6.0.1`_.
* Compatible with VGLite library ``3.0.15_rev4``.

**Fixed**

* Fix performing drawings when the clip is disabled.

.. _section_ui_changelog_13_5_0:

[13.5.0] - 2023-05-03
=====================

MicroUI
"""""""

* Implement `MicroUI API 3.2.0`_.

**Added**

* Add multi BufferedImage image formats management.
* Add custom RAM Image image formats management.
* Add drawing logs flags management.

**Fixed**

* Fix ellipse fading.

.. _MicroUI API 3.2.0: https://repository.microej.com/modules/ej/api/microui/3.2.0/

Drawing
"""""""

**Fixed**

* Fix the position of arc caps.

Front Panel
"""""""""""

**Added**

* Add a service to decode immutable images with a custom format.
* Add a service to create mutable images with a custom format.
* Add a service to draw into mutable images with a format different than the display format.
* Add some methods to manage the MicroUI Drawing Log flags.
* Add some methods to change the MicroUI clip and colors.

**Changed**

* Merge ``DWDrawing`` in ``UIDrawing``.
* Turn ``UIDrawing`` as a service to handle drawings for a specific format.
* Change the mechanism to get the software drawer.
* Change the MicroUI image format ``MICROUI_IMAGE_FORMAT_LCD`` by ``MICROUI_IMAGE_FORMAT_DISPLAY``.

**Removed**

* Remove the interfaces ``UIDrawingDefault`` and ``DWDrawingDefault`` (implement the interface ``UIDrawing`` instead).

Image Generator
"""""""""""""""

**Added**

* Add compatibility with Architecture 8.

LLAPIs
""""""

**Added**

* Add some functions in ``LLUI_DISPLAY.h`` to manage the MicroUI Drawing Log flags.
* Add some functions in ``LLUI_DISPLAY.h`` to change the MicroUI clip and colors.
* Add the notion of "drawer" to identify the available drawer for a given MicroUI Image format.

**Changed**

* Change the MicroUI image format ``MICROUI_IMAGE_FORMAT_LCD`` by ``MICROUI_IMAGE_FORMAT_DISPLAY``.
* Change the signature of ``xx_drawing_soft.h``: all functions return a drawing status.

**Removed**

* Remove ``ui_drawing.h`` and ``dw_drawing.h`` (move them in MicroUI C Module).

C Module MicroUI
""""""""""""""""

* New version: `C Module MicroUI 3.0.0`_.

**Added**

* Add support for multiple Graphics Context output formats.
* Add support for multiple Image input formats.
* Add stub implementations for all MicroUI and Drawing libraries algorithms.

C Module DMA2D
""""""""""""""

* New version: `C Module DMA2D 4.0.0`_.

**Added**

* Add the configuration file ``drawing_dma2d_configuration.h`` to enable or not the cache management (cache invalidate and clean).
* Add the compatibility with multiple Graphics Context output formats.

**Fixed**

* Fix the problems with reading memory back after a DMA2D transfer on cache-enabled CPUs.
* Fix an include directive for case-sensitive filesystems.

C Module VGLite
"""""""""""""""

* New version: `C Module VGLite 6.0.0`_.
* Compatible with VGLite library ``3.0.15_rev4``.

**Added**

* Add the compatibility with multiple Graphics Context output formats.
* Add (or move) some utility functions in ``display_vglite``.
* Add incident reporting with drawing log flags.

**Fixed**

* Set the appropriate format for the destination buffer.
* Fix the drawing of horizontal lines.

**Removed**

* Remove the notion of ``vg_drawer`` and the define ``VGLITE_USE_MULTIPLE_DRAWERS`` (replaced by multiple Graphics Context output formats).

.. _section_ui_changelog_13_4_1:

[13.4.1] - 2023-02-06
=====================

Drawing
"""""""

**Fixed**

* Fix thick lines drawing (when thickness is larger than length).
* Fix circle and ellipse drawing (when the diameter/axis has an even length).

Front Panel
"""""""""""

**Changed**

* Increase the speed of RAW image decoding step.

Image Generator
"""""""""""""""

**Fixed**

* Fix the VEE Port's memory alignment constraint.

C Module VGLite
"""""""""""""""

* New version: `C Module VGLite 5.0.1`_.
* Compatible with VGLite library ``3.0.15_rev4``.
* Several additions, changes and fixes are available. Refer to the `C Module VGLite 5.0.1`_ changelog for more information.

.. _section_ui_changelog_13_4_0:

[13.4.0] - 2022-12-13
=====================

MicroUI
"""""""

**Fixed**

* Fix the unexpected resuming of the pump thread when a new event is added to the queue if it is an other component than the MicroUI queue that has suspended the pump thread.
* Fix the flush bounds of drawCircleArc and drawEllipseArc.

Front Panel
"""""""""""

**Added**

* Add some checks to not perform a drawing when it is unnecessary.

**Fixed**

* Fix the Front Panel representation of a BufferedImage: it is always opaque.

Image Generator
"""""""""""""""

**Added**

* Add the image format A8_RLE.

**Changed**

* Rename RLE1 format in ARGB1565_RLE (keep RLE1 for backward compatibility).

**Fixed**

* Fix the non-generation of external images for the features.

Font Generator
""""""""""""""

**Fixed**

* Fix the external fonts output folder for the features.

C Module MicroUI
""""""""""""""""

* New version: `C Module MicroUI 2.0.1`_.

**Changed**

* Do not draw thick shapes when thickness and fade are equal to zero.

C Module DMA2D
""""""""""""""

* New version: `C Module DMA2D 3.0.2`_.

**Fixed**

* Fix the flush bounds when drawing an image (must be set before calling ``LLUI_DISPLAY_notifyAsynchronousDrawingEnd()``).

C Module VGLite
"""""""""""""""

* New version: `C Module VGLite 4.0.0`_.
* Compatible with VGLite library ``3.0.15_rev4``.
* Several additions, changes and fixes are available. Refer to the `C Module VGLite 4.0.0`_ changelog for more information.

.. _section_ui_changelog_13_3_1:

[13.3.1] - 2022-09-09
=====================

Image Generator
"""""""""""""""

**Added**

* Add an :ref:`Application Option <application_options>` to quickly test an Image Generator Extension project.

**Changed**

* Increase logs when application verbosity is enabled.
* Check the stride defined by the Image Generator Extension project (throw an error if the value is incompatible with the memory alignment).

**Fixed**

* Fix the external resource generation: they were no longer generated (UI pack 13.3.0 regression).
* Fix the duplicate generation (as internal and external resources) of the custom ``.list`` file images (consider only custom ``.list`` file images as external resources when the prefix of the list file extension starts with ``extern``).
* Fix the internal limit error when converting images with BPP lower than 8 bits (for platforms that define a rule for the image stride through an Image Generator Extension project).

.. _section_ui_changelog_13_3_0:

[13.3.0] - 2022-09-02
=====================

MicroUI
"""""""

**Fixed**

* Fix the Cx (x == 1 | 2 | 4) Graphics Engine's when memory layout is "column".
* Fix the consistency between `Image.getImage()`_ and `Font.getFont()`_ about starting MicroUI.

.. _Image.getImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#getImage-java.lang.String-
.. _Font.getFont(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html#getFont-java.lang.String-

Front Panel
"""""""""""

**Added**

* Add custom image formats and a service to prepare for future MicroUI functionality.

Image Generator
"""""""""""""""

**Fixed**

* Fix the stride stored in the image when the Graphics Engine's memory layout is "column".

LLAPIs
""""""

**Added**

* Add custom image formats to prepare for future MicroUI functionality.
* Add LLAPI to adjust new image characteristics (size and alignment).
* Add API: ``UI_DRAWING_copyImage`` and ``UI_DRAWING_drawRegion``.
* Add the LLUI version (== UI Pack version) in header files.

**Changed**

* Use type ``jbyte`` to identify an image format instead of ``MICROUI_ImageFormat`` (prevent C compiler optimization).

**Removed**

* Remove the MicroUI's native functions declaration with macros *(not backward compatible)*.

C Module MicroUI
""""""""""""""""

* New version: `C Module MicroUI 2.0.0`_.

**Changed**

* Improve ``drawImage``: identify faster use cases (copy an image and draw a region with overlap).
* Use new UI Pack LLAPI: ``UI_DRAWING_copyImage`` and ``UI_DRAWING_drawRegion``.
* Use new MicroUI's native functions declaration (not backward compatible).

C Module DMA2D for UI Pack 13.2.0 (maintenance)
"""""""""""""""""""""""""""""""""""""""""""""""

* New version: `C Module DMA2D 2.1.0`_.

**Added**

* Add the compatibility with the STM32H7 series.

**Changed**

* Manage the overlapping (draw an image on the same image).

**Fixed**

* Fix the limitation of UI Pack 13.x in checking the MicroUI GraphicsContext clip before filling a rectangle.

C Module DMA2D for UI Pack 13.3.0
"""""""""""""""""""""""""""""""""

* New version: `C Module DMA2D 3.0.0`_.

**Added**

* Add the implementation of ``UI_DRAWING_drawRegion``.

**Removed**

* Remove the software implementation of "image overlap" (already available in UI Pack 13.3.0).

C Module VGLite
"""""""""""""""

* New version: `C Module VGLite 3.0.0`_.
* Compatible with VGLite library ``3.0.11_rev3``.
* Several additions, changes and fixes are available. Refer to the `C Module VGLite 3.0.0`_ changelog for more information.

.. _section_ui_changelog_13_2_0:

[13.2.0] - 2022-05-05
=====================

Integration
"""""""""""

**Changed**

* Update to the latest SDK license notice.

MicroUI
"""""""

* Implement `MicroUI API 3.1.1`_.

**Changed**

* Use ``.rodata`` sections instead of ``.text`` sections.

**Fixed**

* Clean KF stale references when killing a feature without display context switch.
* Make sure to wait the end of an asynchronous drawing before killing a KF feature.
* Redirect the events sent to the pump to the pump's handler instead of to the event generator's handler.
* Fix the drawing of antialiased arc: caps are drawn over the arc itself (rendering issue when the GraphicsContext's background color is set).
* Fix the drawing of antialiased arc: arc is not fully drawn when (int)startAngle == (int)((startAngle + arcAngle) % 360)).
* Fix the input queue size when not already set by the application launcher.
* Fix the use of a negative ``scanLength`` in `GraphicsContext.readPixels()`_ and `Image.readPixels()`_.

.. _GraphicsContext.readPixels(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html#readPixel-int-int-
.. _Image.readPixels(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#readPixel-int-int-
.. _MicroUI API 3.1.1: https://repository.microej.com/modules/ej/api/microui/3.1.1/

Drawing
"""""""

* Compatible with `Drawing API 1.0.4`_.

.. _Drawing API 1.0.4: https://repository.microej.com/modules/ej/api/drawing/1.0.4/

Front Panel
"""""""""""

**Added**

* Add the property ``-Dej.fp.hil=true`` in the application launcher to force to run the Front Panel with the Graphics Engine as a standard HIL mock (requires MicroEJ Architecture 7.17.0 or higher).
* Add ``LLUIDisplayImpl.decode()``: the Front Panel project is able to read encoded image like the embedded side.
* Include automatically the AWT ImageIO services.
* Add ``MicroUIImage.readPixel()`` to read an image's pixel color.

**Fixed**

* Fix the "display context switch" and the loading of feature's font.
* Fix OOM (Managed heap space) when opening/closing several hundreds of big RAW Images.
* Fix the synchronization with the Graphics Engine when calling `GraphicsContext.setColor()`_ or `GraphicsContext.enableEllipsis()`_.

.. _GraphicsContext.setColor(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html#setColor-int-
.. _GraphicsContext.enableEllipsis(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html#enableEllipsis-int-

Image Generator
"""""""""""""""

**Added**

* Include automatically the AWT ImageIO services.
* Allow to a custom image converter to generate a file other than a binary resource.
* Allow to a custom image converter to specify the supported ``.list`` files.

LLAPIs
""""""

**Added**

* Add ``LLUI_DISPLAY_readPixel`` to read an image's pixel color.

C Module DMA2D
""""""""""""""

* New version: `C Module DMA2D 1.0.8`_ for UI Pack 13.0.x (maintenance).
* New version: `C Module DMA2D 2.0.0`_ for UI Pack 13.1.0 and UI Pack 13.2.0.

**Fixed**

* Fix the use of returned code when drawing images with the DMA2D.
* Clean cache before each DMA2D transfer (no-op on STM32 CPU without cache).

C Module VGLite
"""""""""""""""

* New C Module: C Module VGLite 2.0.0.
* Compatible with VGLite library ``3.0.11_rev3``.

**Added**

* Provides the :ref:`VGLite C module <section_ui_cco>` 2.0.0 to target the NXP CPU that provides the Vivante VGLite accelerator.

BSP
"""

**Fixed**

* Fix the IAR Embedded Workbench warnings during debug session.

.. _section_ui_changelog_13_1_0:

[13.1.0] - 2021-08-03
=====================

MicroUI API
"""""""""""

**Removed**

* Remove MicroUI and Drawing API from UI pack.

MicroUI Implementation
""""""""""""""""""""""

* Implement `MicroUI API 3.1.0`_.

**Changed**

* Check Immortals heap minimal size required by MicroUI implementation.
* Change the EventGenerator Pointer event format.
* Do no systematically use the GPU to draw intermediate steps of a shape.

**Fixed**

* EventGenerator's event has not to be sent to the Display's handler when EventGenerator's handler is null.
* Fill rounded rectangle: fix rendering when corner radius is higher than rectangle height.
* An external image is closed twice when the application only checks if the image is available.
* RLE1 image rendering when platform requires image pixels address alignment.
* Manage the system fonts when the Font Generator is not embedded in the platform.
* Have to wait the end of current drawing before closing an image.

.. _MicroUI API 3.1.0: https://repository.microej.com/modules/ej/api/microui/3.1.0/

Drawing Implementation
""""""""""""""""""""""

* Compatible with `Drawing API 1.0.3`_.

.. _Drawing API 1.0.3: https://repository.microej.com/modules/ej/api/drawing/1.0.3/

Front Panel
"""""""""""

**Added**

* Add ``MicroUIImage.getImage(int)``: apply a rendering color on Ax images.
* Add ``LLUIDisplay.convertRegion()``: convert a region according image format restrictions.
* Add ``LLUIDisplayImpl.waitFlush()``: can manage an asynchronous flush.

**Changed**

* Compatible with new EventGenerator Pointer event format.

**Fixed**

* Fix OutputFormat A8 when loading an image (path or stream) or converting a RAW image.
* Fix OOM (Managed heap space) when opening/closing several hundreds of MicroUI Images.
* Simulates the image data alignment.

LLAPIs
""""""

**Added**

* Add ``LLUI_DISPLAY_convertDisplayColorToARGBColor()``.
* Add LLAPI to manage the :ref:`MicroUI Image heap<section_image_loader_memory>`.
* Add LLAPI to dump the :ref:`MicroUI Events queue<section_inputs_eventbuffer>`.

**Changed**

* Change signature of ``LLUI_DISPLAY_setDrawingLimits()``: remove ``MICROUI_GraphicsContext*`` to be able to call this function from GPU callback method.

C Module MicroUI
""""""""""""""""

* New version: `C Module MicroUI 1.1.0`_.

**Added**

* Add a MicroUI events logger (optional).
* Add a MicroUI images heap allocator (optional).

**Fixed**

* Fix comments in ``LLUI_PAINTER_impl.c`` and ``LLDW_PAINTER_impl.c``.
* Ignore a drawing when at least one scaling factor is equal to zero.

.. _section_ui_changelog_13_0_7:

[13.0.7] - 2021-07-30
=====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Allow to open a font in format made with UI Pack 12.x (but cannot manage ``Dynamic`` styles).
* `Display.flush()`_ method is called once when MicroUI pump thread has a higher priority than the caller of `Display.requestFlush()`_.
* `Display.requestFlush()`_ is only executed once from a feature (UI deadlock).

.. _Display.flush(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush--
.. _Display.requestFlush(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#requestFlush--

Misc
""""

**Fixed**

* Fix MMM dependencies: do not fetch the MicroEJ Architecture.

.. _section_ui_changelog_13_0_6:

[13.0.6] - 2021-03-29
=====================

LLAPIs
""""""

**Fixed**

* Size of the typedef ``MICROUI_Image``: do not depend on the size of the enumeration ``MICROUI_ImageFormat`` (``LLUI_PAINTER_impl.h``).

.. _section_ui_changelog_13_0_5:

[13.0.5] - 2021-03-08
=====================

MicroUI Implementation
""""""""""""""""""""""

**Removed**

* Remove ResourceManager dependency.

**Fixed**

* A feature was not able to call `Display.callOnFlushCompleted()`_.
* Stop feature: prevent `NullPointerException`_ when a kernel's EventGenerator is removed from event generators pool.
* Filter `DeadFeatureException`_ in MicroUI pump.
* Drawing of thick arcs which represent an almost full circle.
* Drawing of thick faded arcs which pass by 0° angle.

.. _Display.callOnFlushCompleted(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#callOnFlushCompleted-java.lang.Runnable-
.. _NullPointerException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/NullPointerException.html
.. _DeadFeatureException: https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/DeadFeatureException.html

Front Panel
"""""""""""

**Fixed**

* Front Panel memory management: reduce simulation time.

.. _section_ui_changelog_13_0_4:

[13.0.4] - 2021-01-15
=====================

MicroUI API
"""""""""""

**Changed**

* [Changed] Include `MicroUI API 3.0.3`_.
* [Changed] Include `MicroUI Drawing API 1.0.2`_.

.. _MicroUI API 3.0.3: https://repository.microej.com/modules/ej/api/microui/3.0.3/
.. _MicroUI Drawing API 1.0.2: https://repository.microej.com/modules/ej/api/drawing/1.0.2/

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Fix each circle arc cap being drawn on both sides of an angle.
* Fix drawing of rounded caps of circle arcs when fade is 0.
* Cap thickness and fade in thick drawing algorithms.
* Clip is not checked when filling arcs, circles and ellipsis.
* Image path when loading an external image (``LLEXT``).
* ``InternalLimitsError`` when calling `MicroUI.callSerially()`_ from a feature.

.. _MicroUI.callSerially(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/MicroUI.html#callSerially-java.lang.Runnable-

Drawing Implementation
""""""""""""""""""""""

**Fixed**

* Draw deformed image is not rendered.

Image Generator
"""""""""""""""

**Changed**

* Compatible with `com.microej.pack.ui#ui-pack(imageGenerator)#13.0.4`_.

**Fixed**

* `NullPointerException`_ when trying to convert an unknown image.
* Restore external resources option in MicroEJ launcher.

.. _com.microej.pack.ui#ui-pack(imageGenerator)#13.0.4: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/13.0.4/

.. _section_ui_changelog_13_0_3:

[13.0.3] - 2020-12-03
=====================

MicroUI API
"""""""""""

**Changed**

* [Changed] Include MicroUI API 3.0.2.
* [Changed] Include MicroUI Drawing API 1.0.1.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Reduce Managed heap usage.
* Fix empty images heap.
* Draw image algorithm does not respect image stride in certain circumstances.
* Fix flush limits of `drawThickFadedLine`_, `drawThickEllipse`_ and `drawThickFadedEllipse`_.

.. _drawThickFadedLine: https://repository.microej.com/javadoc/microej_5.x/apis/ej/drawing/ShapePainter.html#drawThickFadedLine-ej.microui.display.GraphicsContext-int-int-int-int-int-int-ej.drawing.ShapePainter.Cap-ej.drawing.ShapePainter.Cap-
.. _drawThickEllipse: https://repository.microej.com/javadoc/microej_5.x/apis/ej/drawing/ShapePainter.html#drawThickEllipse-ej.microui.display.GraphicsContext-int-int-int-int-int-
.. _drawThickFadedEllipse: https://repository.microej.com/javadoc/microej_5.x/apis/ej/drawing/ShapePainter.html#drawThickFadedEllipse-ej.microui.display.GraphicsContext-int-int-int-int-int-int-

C Module MicroUI
""""""""""""""""

* New version: `C Module MicroUI 1.0.3`_.

C Module DMA2D
""""""""""""""

* New version: `C Module DMA2D 1.0.6`_.

.. _section_ui_changelog_13_0_2:

[13.0.2] - 2020-10-02
=====================

* Use new naming convention: ``com.microej.architecture.[toolchain].[architecture]-ui-pack``.

**Fixed**

* [ESP32] - Potential ``PSRAM`` access faults by rebuilding using esp-idf v3.3.0 toolchain - ``simikou2``.

C Module DMA2D
""""""""""""""

* New version: C Module DMA2D 1.0.5.

**Changed**

* De-init the DMA2D before re-initializing it, to reset the context at HAL level.
* Manipulate the drawing limits after being sure the DMA2D job is finished.

.. _section_ui_changelog_13_0_1:

[13.0.1] - 2020-09-22
=====================

MicroUI API
"""""""""""

**Changed**

* Include `MicroUI API 3.0.1`_.

.. _MicroUI API 3.0.1: https://repository.microej.com/modules/ej/api/microui/3.0.1/

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Throw an exception when there is no display.
* Antialiased circle may be cropped.
* `FillRoundedRectangle`_ can give invalid arguments to `FillRectangle`_.
* Flush bounds may be invalid.
* Reduce memory footprint (java heap and immortal heap).
* No font is loaded when an external font is not available.
* A8 color is cropped to display limitation too earlier on simulator.

.. _FillRoundedRectangle: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Painter.html#fillRoundedRectangle-ej.microui.display.GraphicsContext-int-int-int-int-int-int-
.. _FillRectangle: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Painter.html#fillRectangle-ej.microui.display.GraphicsContext-int-int-int-int-

Front Panel
"""""""""""

**Fixed**

* Cannot use an external image decoder on Front Panel.
* Missing an API to check the overlapping between source and destination areas.

Image Generator
"""""""""""""""

**Fixed**

* Cannot build a platform with Image Generator and without Front Panel.

LLAPIs
""""""

**Fixed**

* Missing a LLAPI to check the overlapping between source and destination areas.

C Module MicroUI
""""""""""""""""

* New version: C Module MicroUI 1.0.2.

**Changed**

* Change module organization.

C Module DMA2D
""""""""""""""

* New version: C Module DMA2D 1.0.3.

**Changed**

* Remove/replace notion of ``LLDISPLAY``.
* Change module organization.

**Fixed**

* Fix file names.

.. _section_ui_changelog_13_0_0:

[13.0.0] - 2020-07-30
=====================

* Integrate SDK 3.0-B license.

Architecture
""""""""""""

**Changed**

* Compatible with Architecture 7.16.0 or higher (SNI 1.3).

MicroUI API
"""""""""""

**Changed**

* [Changed] Include `MicroUI API 3.0.0`_.
* [Changed] Include `MicroUI Drawing API 1.0.0`_.

.. _MicroUI API 3.0.0: https://repository.microej.com/modules/ej/api/microui/3.0.0/
.. _MicroUI Drawing API 1.0.0: https://repository.microej.com/modules/ej/api/drawing/1.0.0/

MicroUI Implementation
""""""""""""""""""""""

**Added**

* Manage image data (pixels) address alignment (not more fixed to 32-bits word alignment).

**Changed**

* Reduce EDC dependency.
* Merge ``DisplayPump`` and ``InputPump``: only one thread is required by MicroUI.
* Use a ``bss`` section to load characters from an external font instead of using java heap.

**Removed**

* Dynamic fonts (dynamic bold, italic, underline and ratios).

**Fixed**

* Lock only current thread when waiting end of flush or end of drawing (and not all threads).
* Draw anti-aliased ellipse issue (vertical line is sometimes drawn).
* Screenshot on platform whose *physical* size is higher than *virtual* size.

**Known issue**

* Render of draw/fill arc/circle/ellipse with an even diameter/edge is one pixel too high (center is 1/2 pixel too high).

Front Panel
"""""""""""

**Added**

* Able to override MicroUI drawings algorithms like embedded platform.

**Changed**

* Compatible with `com.microej.pack.ui#ui-pack(frontpanel)#13.0.0`_.
* See :ref:`Migration notes<section_ui_migration_frontpanelapi_13x>` that describe the available changes in Front Panel API.

**Removed**

* ``ej.tool.frontpanel#widget-microui`` has been replaced by ``com.microej.pack.ui#ui-pack(frontpanel)``.

.. _com.microej.pack.ui#ui-pack(frontpanel)#13.0.0: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/13.0.0/

Image Generator
"""""""""""""""

**Added**

* Redirects source image reading to the Image Generator extension project in order to increase the number of supported image formats in input.
* Redirects destination image generation to the Image Generator extension project in order to be able to encode an image in a custom RAW format.
* Generates a linker file in order to always link the resources in same order between two launches.

**Changed**

* Compatible with `com.microej.pack.ui#ui-pack(imageGenerator)#13.0.0`_.
* See :ref:`Migration notes<section_ui_migration_imagegeneratorapi_13x>` that describe the available changes in Image Generator API.
* Uses a service loader to loads the Image Generator extension classes.
* Manages image data (pixels) address alignment.

**Removed**

* Classpath variable ``IMAGE-GENERATOR-x.x``: Image generator extension project has to use ivy dependency ``com.microej.pack.ui#ui-pack(imageGenerator)`` instead.

.. _com.microej.pack.ui#ui-pack(imageGenerator)#13.0.0: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/13.0.0/

Font Generator
""""""""""""""

**Changed**

* Used a dedicated ``bss`` section to load characters from an external font instead of using the java heap.

LLAPIs
""""""

**Added**

* Some new functions are mandatory: see header files list, tag *mandatory*.
* Some new functions are optional: see header files list, tag *optional*.
* Some header files list the libraries ``ej.api.microui`` and ``ej.api.drawing`` natives. Provided by Abstraction Layer implementation module `com.microej.clibrary.llimpl#microui`_.
* Some header files list the drawing algorithms the platform can implement; all algorithms are optional.
* Some header files list the internal Graphics Engine software algorithms the platform can call.

**Changed**

* All old header files and functions have been renamed or shared.
* See :ref:`Migration notes<section_ui_migration_llapi_13x>` that describe the available changes in LLAPI.

.. _com.microej.clibrary.llimpl#microui: https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui

C Modules
"""""""""

**Added**

* Provides the C Module MicroUI 1.0.1 that extends the `UI Pack 13.0.0`_.
* Provides the C Module DMA2D 1.0.2 that targets the STM32 CPU that provides the Chrom-ART accelerator.
* See :ref:`MicroUI C module <section_ui_cco>`.

.. _UI Pack 13.0.0: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/13.0.0/

.. _section_ui_changelog_12_1_5:

[12.1.5] - 2020-10-02
=====================

* Use new naming convention: ``com.microej.architecture.[toolchain].[architecture]-ui-pack``.

**Fixed**

* [ESP32] - Potential ``PSRAM`` access faults by rebuilding using esp-idf v3.3.0 toolchain - ``simikou2``.

.. _section_ui_changelog_12_1_4:

[12.1.4] - 2020-03-10
=====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Obsolete references on Managed heap are used (since MicroEJ UI Pack 12.0.0).

.. _section_ui_changelog_12_1_3:

[12.1.3] - 2020-02-24
=====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Caps are not used when drawing an anti-aliased line.

.. _section_ui_changelog_12_1_2:

[12.1.2] - 2019-12-09
=====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Fix Graphics Engine empty clip (empty clip had got a size of 1 pixel).
* Clip not respected when clip is set "just after or before" graphics context drawable area: first (or last) line (or column) of graphics context was rendered.

.. _section_ui_changelog_12_1_1:

[12.1.1] - 2019-10-29
=====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Fix Graphics Engine clip (cannot be outside graphics context).

.. _section_ui_changelog_(maint)_8_0_0:

[(maint) 8.0.0] - 2019-10-18
============================

* Based on UI Pack 7.4.7.

Architecture
""""""""""""

**Changed**

* Compatible with Architecture 7.0.0 or higher (Use SNI callback feature).

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Pending flush cannot be added after an ``OutOfEventException``.

.. _section_ui_changelog_12_1_0:

[12.1.0] - 2019-10-16
=====================
MicroUI API
"""""""""""

**Changed**

* Include `MicroUI API 2.4.0`_.

.. _MicroUI API 2.4.0: https://repository.microej.com/modules/ej/api/microui/2.4.0/

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* Prepare inlining of get X/Y/W/H methods.
* Reduce number of strings embedded by MicroUI library.

**Fixed**

* Pending flush cannot be added after an ``OutOfEventException``.
* `Display.isColor()`_ returns an invalid value.
* Draw/fill circle/ellipse arc is not drawn when angle is negative.

.. _Display.isColor(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#isColor--

.. _section_ui_changelog_12_0_2:

[12.0.2] - 2019-09-23
=====================

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* Change ``CM4hardfp_IAR83`` compiler flags.
*  Remove RAW images from cache as soon as possible to reduce java heap usage.
* Do not cache RAW images with their paths to reduce java heap usage.

**Fixed**

* Remove useless exception in SystemInputPump.

.. _section_ui_changelog_12_0_1:

[12.0.1] - 2019-07-25
=====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Physical size is not taken in consideration.

Front Panel
"""""""""""

**Fixed**

* Increase native implementation execution time.

.. _section_ui_changelog_12_0_0:

[12.0.0] - 2019-06-24
=====================

Architecture
""""""""""""

**Changed**

* Compatible with Architecture 7.11.0 or higher (Move Front Panel in Architecture).

MicroUI Implementation
""""""""""""""""""""""

**Added**

* Trace MicroUI events and log them on SystemView.

**Changed**

* Manage the Graphics Context clip on native side.
* Use java heap to store images metadata instead of using icetea heap (remove option "max offscreen").
* Optimize retrieval of all fonts.
* Ensure user buffer size is larger than LCD size.
* Use java heap to store flying images metadata instead of using icetea heap (remove option "max flying images").
* Use java heap to store fill polygon algorithm's objects instead of using icetea heap (remove option "max edges").
* ``SecurityManager`` enabled as a boolean constant option (footprint removal by default).
* Remove ``FlyingImage`` feature using BON constants (option to enable it).

**Fixed**

* Wrong rendering of a fill polygon on emb.
* Wrong rendering of image overlaping on C1/2/4 platforms.
* Wrong rendering of a LUT image with more than 127 colors on emb.
* Wrong rendering of an antialiased arc with 360 angle.
* Debug option com.is2t.microui.log=true fails when there is a flying image.
* Gray scale between gray and white makes magenta.
* Minimal size of some buffers set by user is never checked.
* The format of a RAW image using "display" format is wrong.
* Dynamic image width for platform C1/2/4 may be wrong.
* Wrong pixel address when reading from a C2/4 display.
* `getDisplayColor()`_ can return a color with transparency (spec is ``0x00RRGGBB``).
* A fully opaque image is tagged as transparent (ARGB8888 platform).

.. _getDisplayColor(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#getDisplayColor-int-

Front Panel
"""""""""""

**Added**

* Simulate flush time (add JRE property ``-Dfrontpanel.flush.time=8``).

**Fixed**

* A pixel read on an image is always truncated.

Front Panel Plugin
""""""""""""""""""

**Removed**

* Front Panel version 5: Move Front Panel from MicroEJ UI Pack to Architecture *(not backward compatible)*; Architecture contains now Front Panel version 6.

.. _section_ui_changelog_11_2_0:

[11.2.0] - 2019-02-01
=====================

MicroUI Implementation
""""""""""""""""""""""

**Added**

* Manage extended UTF16 characters (> 0xffff).

**Fixed**

* IOException thrown instead of an OutOfMemory when using external resource loader.

Tools
"""""

**Removed**

* Remove Font Designer from pack (useless).

.. _section_ui_changelog_11_1_2:

[11.1.2] - 2018-08-10
=====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Fix drawing bug in thick circle arcs.

.. _section_ui_changelog_11_1_1:

[11.1.1] - 2018-08-02
=====================

* Internal release.

.. _section_ui_changelog_11_1_0:

[11.1.0] - 2018-07-27
=====================

* Merge 10.0.2 and 11.0.1.

MicroUI API
"""""""""""

**Changed**

* Include `MicroUI API 2.3.0`_.

.. _MicroUI API 2.3.0: https://repository.microej.com/modules/ej/api/microui/2.3.0/

MicroUI Implementation
""""""""""""""""""""""

**Added**

* ``LLDisplay``: prepare round LCD.

**Fixed**

* ``Fillrect`` throws a hardfault on 8bpp platform.
* Rendering of a LUT image is wrong when using software algorithm.

.. _section_ui_changelog_11_0_1:

[11.0.1] - 2018-06-05
=====================

* Based on UI Pack 11.0.0.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Image rendering may be invalid on custom display.
* Render a dynamic image on custom display is too slow.
* LRGB888 image format is always fully opaque.
* Number of colors returned when it is a custom display may be wrong.

.. _section_ui_changelog_10_0_2:

[10.0.2] - 2018-02-15
=====================

* Based on UI Pack 10.0.1.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Number of colors returned when it is a custom display may be wrong.
* LRGB888 image format is always fully opaque.
* Render a dynamic image on custom display is too slow.
* Image rendering may be invalid on custom display.

.. _section_ui_changelog_11_0_0:

[11.0.0] - 2018-02-02
=====================

* Based on UI Pack 10.0.1.

Architecture
""""""""""""

**Changed**

* Compatible with Architecture 7.0.0 or higher (Use SNI callback feature).

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* SNI Callback feature in the Core Engine to remove the SNI retry pattern *(not backward compatible)*.

.. _section_ui_changelog_10_0_1:

[10.0.1] - 2018-01-03
=====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Hard fault when using custom display stack.

.. _section_ui_changelog_10_0_0:

[10.0.0] - 2017-12-22
=====================

Architecture
""""""""""""

**Changed**

* Compatible with Architecture 6.13.0 or higher (``LLEXT`` link error with Architecture 6.13+ and UI Pack 9+).

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* Improve ``TOP-LEFT`` anchor checks.

**Fixed**

* Subsequent renderings may not be correctly flushed.
* Rendering of display on display was not optimized.

Front Panel
"""""""""""

**Changed**

* Check the allocated memory when creating a dynamic image *(not backward compatible)*.

Misc
""""

**Added**

* Option in platform builder to images heap size.

.. _section_ui_changelog_9_4_1:

[9.4.1] - 2017-11-24
====================

Image Generator
"""""""""""""""

**Fixed**

* Missing some files in Image Generator module.

.. _section_ui_changelog_9_4_0:

[9.4.0] - 2017-11-23
====================

* Deprecated: use UI Pack 9.4.1 instead.

MicroUI Implementation
""""""""""""""""""""""

**Added**

* LUT image management.

**Changed**

* Optimize character encoding removing first vertical line when possible.

**Fixed**

* Memory leak when an ``OutOfEventException`` is thrown.
* A null Java object is not checked when using a font.

.. _section_ui_changelog_9_3_1:

[9.3.1] - 2017-09-28
====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Returned X coordinates when drawing a string was considered as an error code.
* Exception when loading a font from an application.
* ``LLEXT`` link error with Architecture 6.13+ and UI 9+.

.. _section_ui_changelog_9_3_0:

[9.3.0] - 2017-08-24
====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Ellipsis must not drawn when text anchor is a "manual" ``TOP-RIGHT``.

Front Panel
"""""""""""

**Fixed**

* Do not create an AWT window for each image.
* Error when trying to play with an unknown led.

.. _section_ui_changelog_9_2_1:

[9.2.1] - 2017-08-14
====================

Front Panel
"""""""""""

**Added**

* Provide function to send a Long Button event.
* "flush" debug option.

**Fixed**

* Mock startup is too long.

.. _section_ui_changelog_9_2_0:

[9.2.0] - 2017-07-21
====================

* Merge UI Packs 9.1.2 and 9.0.2.

Architecture
""""""""""""

**Changed**

* Compatible with Architecture 6.12.0 or higher (SOAR can exclude some resources).

MicroUI API
"""""""""""

**Changed**

* Include `MicroUI API 2.2.0`_.

.. _MicroUI API 2.2.0: https://repository.microej.com/modules/ej/api/microui/2.2.0/

MicroUI Implementation
""""""""""""""""""""""

**Added**

* Provide function to send a Long Button event (emb only).

**Changed**

* Use font format v5.
* A signature on RAW files.
* Allow to open a raw image with ``Image.createImage(stream)``.
* Improve ``Image.createImage(stream)`` when stream is a memory input stream.

**Fixed**

* Draw region of the display on the display does not support overlap.
* Unspecified exception while loading an image with an empty name.
* `Display.flush()`_: ymax can be higher than display.height.

.. _Display.flush(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush--

Image Generator
"""""""""""""""

**Fixed**

* Generic displays must be able to generate standard images.

Misc
""""

**Changed**

* SOAR can exclude some resources (update llext output folder).

**Fixed**

* RI build: reduce Front Panel dependency.

.. _section_ui_changelog_9_0_2:

[9.0.2] - 2017-04-21
====================

*  Based on UI Pack 9.0.1.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Rendering of a RAW image on grayscale display is wrong.

Image Generator
"""""""""""""""

**Fixed**

* An Ax image may be fully opaque.

.. _section_ui_changelog_9_1_2:

[9.1.2] - 2017-03-16
====================

*  Based on UI Pack 9.1.1.

MicroUI API
"""""""""""

**Changed**

* Include MicroUI API 2.1.3.

MicroUI Implementation
""""""""""""""""""""""

**Added**

* Renderable strings.

**Changed**

* Draw string: improve time to perform it.
* Optimize antialiased circle arc drawing when fade=0.

**Fixed**

* ImageScale bugs.
* Draw string: some errors are not thrown.
* ``Font.getWidth()`` and `getHeight()`_ don't use ratio factor.
* Draw antialiased circle arc render issue.
* Draw antialiased circle arc render bug with 45° angles.
* MicroUI lib expects the dynamic image decoder default format.
* Wrong error code is returned when converting an image.

.. _getHeight(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html#getHeight--

Image Generator
"""""""""""""""

**Fixed**

* Use the application classpath.
* An Ax image may be fully opaque.

.. _section_ui_changelog_9_0_1:

[9.0.1] - 2017-03-13
====================

*  Based on UI Pack 9.0.0.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Hardfault when filling a rectangle on an odd image.
* Pixel rendering on non-standard LCD is wrong.
* RZ hardware accelerator: RAW images have to respect an aligned size.
* Use the classpath when invoking the fonts and images generators.

Front Panel
"""""""""""

**Fixed**

* Wrong rendering of A8 images.

Front Panel Plugin
""""""""""""""""""

**Fixed**

* Manage display mask on preview.
* Respect initial background color set by user on preview.
* Preview does not respect the real size of display.

.. _section_ui_changelog_9_1_1:

[9.1.1] - 2017-02-14
====================

*  Based on UI Pack 9.1.0.

Misc
""""

**Fixed**

* RI build: Several custom event generators in same ``microui.xml`` file are not embedded.

.. _section_ui_changelog_9_1_0:

[9.1.0] - 2017-02-13
====================

* Based on UI Pack 9.0.0.

Architecture
""""""""""""

**Changed**

* Compatible with Architecture 6.8.0 or higher (Internal scripts).

MicroUI API
"""""""""""

**Changed**

* Include MicroUI API 2.1.2.

MicroUI Implementation
""""""""""""""""""""""

**Added**

* G2D hardware accelerator.
* Hardware accelerator: add flip feature.

**Fixed**

* Hardfault when filling a rectangle on an odd image.
* Pixel rendering on non-standard LCD is wrong.
* RZ hardware accelerator: RAW images have to respect an aligned size.
* Use the classpath when invoking the fonts and images generators.
* Exception when flipping an image out of display bounds.
* Flipped image is translated when clip is modified.

Front Panel
"""""""""""

**Fixed**

* Wrong rendering of A8 images.

Front Panel Plugin
""""""""""""""""""

**Fixed**

* Manage display mask on preview.
* Respect initial background color set by user on preview.
* Preview does not respect the real size of display.

.. _section_ui_changelog_9_0_0:

[9.0.0] - 2017-02-02
====================

MicroUI API
"""""""""""

**Changed**

* Include `MicroUI API 2.0.6`_.

.. _MicroUI API 2.0.6: https://repository.microej.com/modules/ej/api/microui/2.0.6/

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* Update MicroUI to use watchdogs in KF implementation.

**Fixed**

* Display linker file is required even if there is no display on platform.
* MicroUI on KF: NPE when changing app quickly (in several threads).
* MicroUI on KF: NPE when stopping a Feature and there's no eventHandler in a generator.
* MicroUI on KF: Remaining K->F link when there is no default event handler registered by the Kernel.

MWT
"""

**Removed**

* Remove MWT from MicroEJ UI Pack *(not backward compatible)*.

Front Panel
"""""""""""

**Added**

* Optional mask on display.

**Changed**

* Display Device UID if available in the window title.

Tools
"""""

**Changed**

* Front Panel plugin: Update icons.
* Font Designer plugin: Update icons.
* Font Designer and Generator: use Unicode 9.0.0 specification.

Misc
""""

**Fixed**

* Remove obsolete documentations from Front Panel And Font Designer plugins.

.. _section_ui_changelog_8_1_0:

[8.1.0] - 2016-12-24
====================

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* Improve image drawing timings.
* Runtime decoders can force the output RAW image's fully opacity.

MWT
"""

**Fixed**

* With two panels, the paint is done but the screen is not refreshed.
* Widget show notify method is called before the panel is set.
* Widget still linked to panel when ``lostFocus()`` is called.

Front Panel
"""""""""""

**Added**

* Can add an additional screen on simulator.

.. _section_ui_changelog_8_0_0:

[8.0.0] - 2016-11-17
====================

Architecture
""""""""""""

**Changed**

* Compatible with Architecture 6.4.0 or higher (Manage external memories like byte addressable memories).

MicroUI Implementation
""""""""""""""""""""""

**Added**

* RZ UI acceleration.
* External image decoders.
* Manage external memories like internal memories.
* Custom display stacks (hardware acceleration).

**Changed**

* Merge stacks ``DIRECT/COPY/SWITCH`` *(not backward compatible)*.

**Fixed**

* add KF rule: a thread cannot enter in a feature code while it owns a kernel monitor.
* automatic flush is not waiting the end of previous flush.
* Invalid image rotation rendering.
* Do not embed Images & Fonts.list of kernel API classpath in app mode.
* Invalid icetea heap allocation.
* microui image: invalid "defaultformat" and "format" fields values.

MWT
"""

**Fixed**

* possible to create an inconsistent hierarchy.

Front Panel
"""""""""""

**Added**

* Can decode additional image formats.

**Fixed**

* Cannot set initial value of StateEventGenerator.

.. _section_ui_changelog_7_4_7:

[7.4.7] - 2016-06-14
====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Do not create all fonts derivations of built-in styles.
* A bold font is not flagged as bold font.
* Wrong A4 image rendering.

Front Panel
"""""""""""

**Fixed**

* Cannot convert an image.

.. _section_ui_changelog_7_4_2:

[7.4.2] - 2016-05-25
====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* invalid image drawing for *column* display.

.. _section_ui_changelog_7_4_1:

[7.4.1] - 2016-05-10
====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Restore stack 1, 2 and 4 BPP.

.. _section_ui_changelog_7_4_0:

[7.4.0] - 2016-04-29
====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* image A1's width is sometimes invalid.

Front Panel
"""""""""""

**Added**

* Restore stack 1, 2 and 4 BPP.

.. _section_ui_changelog_7_3_0:

[7.3.0] - 2016-04-25
====================

MicroUI Implementation
""""""""""""""""""""""

**Added**

* Stack 8BPP with LUT support.

.. _section_ui_changelog_7_2_1:

[7.2.1] - 2016-04-18
====================

Misc
""""

**Fixed**

* Remove ``java`` keyword in workbench extension.

.. _section_ui_changelog_7_2_0:

[7.2.0] - 2016-04-05
====================

Tools
"""""

**Added**

* Preprocess ``*.xxx.list`` files.

.. _section_ui_changelog_7_1_0:

[7.1.0] - 2016-03-02
====================

MicroUI Implementation
""""""""""""""""""""""

**Added**

* Manage several images RAW formats.

.. _section_ui_changelog_7_0_0:

[7.0.0] - 2016-01-20
====================

Misc
""""

**Changed**

* Remove ``@jpf.property.header@`` prefix to Application options *(not backward compatible)*.

.. _section_ui_changelog_6_0_1:

[6.0.1] - 2015-12-17
====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* A negative clip throws an exception on simulator.

.. _section_ui_changelog_6_0_0:

[6.0.0] - 2015-11-12
====================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* LLDisplay for UIv2 *(not backward compatible)*.

..
   | Copyright 2021-2025, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.
