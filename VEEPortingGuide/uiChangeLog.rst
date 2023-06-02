.. _section_ui_changelog:

=========
Changelog
=========

[13.5.0] (2023-05-03)
=====================

* Compatible with Architecture 7.13.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

- Implement MicroUI 3.2 (multi mutable image formats, drawing log flags, etc.).

**Fixed**

- Fix ellipse fading.

Drawing Implementation
""""""""""""""""""""""

**Fixed**

- Fix the position of arc caps.

LLAPIs
""""""
	
**Added**

* Add some functions in `LLUI_DISPLAY.h` to manage the MicroUI Drawing Log flags.
* Add some functions in `LLUI_DISPLAY.h` to change the MicroUI clip and colors.
* Add the notion of "drawer" to identify the available drawer for a given MicroUI Image format.

**Changed**

* Change the MicroUI image format `MICROUI_IMAGE_FORMAT_LCD` by `MICROUI_IMAGE_FORMAT_DISPLAY`.
* Change the signature of `xx_drawing_soft.h`: all functions return a drawing status. 

**Removed**

* Remove `ui_drawing.h` and `dw_drawing.h` (move them in MicroUI CCO).

FrontPanel
""""""""""
	
**Added**

* Add a service to decode immutable images with a custom format. 
* Add a service to create mutable images with a custom format. 
* Add a service to draw into mutable images with a format different than the display format. 
* Add some methods to manage the MicroUI Drawing Log flags.
* Add some methods to change the MicroUI clip and colors.

**Changed**

* Merge `DWDrawing` in `UIDrawing`.
* Turn `UIDrawing` as a service to handle drawings for a specific format.
* Change the mechanism to get the software drawer.
* Change the MicroUI image format `MICROUI_IMAGE_FORMAT_LCD` by `MICROUI_IMAGE_FORMAT_DISPLAY`.

**Removed**

* Remove the interfaces `UIDrawingDefault` and `DWDrawingDefault` (implement the interface `UIDrawing` instead).

ImageGenerator
""""""""""""""

**Added**

* Add the compatibility with the Architecture 8.

[13.4.1] (2023-02-06)
=====================
	
Drawing Implementation
""""""""""""""""""""""

**Fixed**

* Fix thick lines drawing (when thickness is larger than length).
* Fix circle and ellipse drawing (when the diameter/axis has an even length).

FrontPanel
""""""""""

**Changed**

* Increase the speed of RAW image decoding step.

ImageGenerator
""""""""""""""

**Fixed**

* Fix the VEE Port's memory alignment constraint.

[13.4.0] - 2022-12-13
=====================

* Compatible with Architecture 7.13.0 or higher.

MicroUI Implementation
""""""""""""""""""""""
	
**Fixed**

* Fix the unexpected resuming of the pump Java thread when a new event is added to the queue if it is an other component than the MicroUI queue that has suspended the pump Java thread.
* Fix the flush bounds of drawCircleArc and drawEllipseArc.   

FrontPanel
""""""""""

**Added**

* Add some checks to not perform a drawing when it is unnecessary. 

**Fixed**

* Fix the Front Panel representation of a BufferedImage: it is always opaque. 

ImageGenerator
""""""""""""""

**Added**

* Add the image format A8_RLE.

**Changed**

* Rename RLE1 format in ARGB1565_RLE (keep RLE1 for backward compatibility).

**Fixed**

* Fix the non-generation of external images for the features.

FontGenerator
"""""""""""""

**Fixed**

* Fix the external fonts output folder for the features.

[13.3.1] - 2022-09-09
=====================

* Compatible with Architecture 7.13.0 or higher.
 
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

[13.3.0] - 2022-09-02
=====================

* Compatible with Architecture 7.13.0 or higher.

MicroUI Implementation
""""""""""""""""""""""
	
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

[13.2.0] - 2022-05-05
=====================

* Compatible with Architecture 7.16.0 or higher.

Integration
"""""""""""
	
**Changed**	

* Update to the latest SDK license notice.
	
MicroUI Implementation
""""""""""""""""""""""
	
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

Front Panel
"""""""""""

**Added**

* Add the property ``-Dej.fp.hil=true`` in the application launcher to force to run the FrontPanel with the Graphics Engine as a standard HIL mock (requires MicroEJ Architecture 7.17.0 or higher).
* Add ``LLUIDisplayImpl.decode()``: the Front Panel project is able to read encoded image like the embedded side.
* Include automatically the AWT ImageIO services.
* Add ``MicroUIImage.readPixel()`` to read an image's pixel color.
 
**Fixed**

* Fix the "display context switch" and the loading of feature's font. 
* Fix OOM (Java heap space) when opening/closing several hundreds of big RAW Images. 
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

BSP
"""
	
**Fixed**

* Fix the IAR Embedded Workbench warnings during debug session.

[13.1.0] - 2021-08-03
=====================

* Compatible with Architecture 7.16.0 or higher.

MicroUI API
"""""""""""

**Removed**

* Remove MicroUI and Drawing API from UI pack.
	
MicroUI Implementation
""""""""""""""""""""""

**Changed**

* Compatible with `MicroUI API 3.1.0`_.
* Check Immortals heap minimal size required by MicroUI implementation.
* Change the EventGenerator Pointer event format.
* Do no systematically use the GPU to draw intermediate steps of a shape.  
	
**Fixed**

* EventGenerator's event has not to be sent to the Display's handler when EventGenerator's handler is null.
* Fill rounded rectangle: fix rendering when corner radius is higher than rectangle height.
* An external image is closed twice when the application only checks if the image is available.
* RLE1 image rendering when platform requires image pixels address alignment. 
* Manage the system fonts when the font generator is not embedded in the platform.
* Have to wait the end of current drawing before closing an image.

.. _MicroUI API 3.1.0: https://repository.microej.com/modules/ej/api/microui/3.1.0/

Drawing Implementation
""""""""""""""""""""""

**Changed**

* Compatible with `Drawing API 1.0.3`_.

.. _Drawing API 1.0.3: https://repository.microej.com/modules/ej/api/drawing/1.0.3/

LLAPIs
""""""
	
**Added**

* Add ``LLUI_DISPLAY_convertDisplayColorToARGBColor()``.
* Add LLAPI to manage the :ref:`MicroUI Image heap<section_image_loader_memory>`.
* Add LLAPI to dump the :ref:`MicroUI Image queue<section_inputs_eventbuffer>`.

**Changed**	

* Change signature of ``LLUI_DISPLAY_setDrawingLimits()``: remove ``MICROUI_GraphicsContext*`` to be able to call this function from GPU callback method. 

Simulator
"""""""""

**Added**

* Add ``MicroUIImage.getImage(int)``: apply a rendering color on Ax images.  
* Add ``LLUIDisplay.convertRegion()``: convert a region according image format restrictions.   

**Changed**	

* Compatible with new EventGenerator Pointer event format.
	
**Fixed**

* Fix OutputFormat A8 when loading an image (path or stream) or converting a RAW image.
* Fix OOM (Java heap space) when opening/closing several hundreds of MicroUI Images. 
* Simulates the image data alignment.

[13.0.7] - 2021-07-30
=====================

* Compatible with Architecture 7.16.0 or higher.

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

[13.0.6] - 2021-03-29
=====================

* Compatible with Architecture 7.16.0 or higher.

LLAPIs
""""""

**Fixed**

* Size of the typedef ``MICROUI_Image``: do not depend on the size of the enumeration ``MICROUI_ImageFormat`` (``LLUI_PAINTER_impl.h``).

[13.0.5] - 2021-03-08
=====================

* Compatible with Architecture 7.16.0 or higher.

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

Simulator
"""""""""

**Fixed**

* Front panel memory management: reduce simulation time.

[13.0.4] - 2021-01-15
=====================

* Compatible with Architecture 7.16.0 or higher.

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

ImageGenerator
""""""""""""""

**Changed**

* Compatible with `com.microej.pack.ui#ui-pack(imageGenerator)#13.0.4`_.
	
**Fixed**

* `NullPointerException`_ when trying to convert an unknown image.
* Restore external resources option in MicroEJ launcher.

.. _com.microej.pack.ui#ui-pack(imageGenerator)#13.0.4: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/13.0.4/

[13.0.3] - 2020-12-03
=====================

* Compatible with Architecture 7.16.0 or higher.
 
MicroUI API
"""""""""""

**Changed**

* [Changed] Include MicroUI API 3.0.2.
* [Changed] Include MicroUI Drawing API 1.0.1.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Reduce Java heap usage.
* Fix empty images heap.
* Draw image algorithm does not respect image stride in certain circumstances.
* Fix flush limits of `drawThickFadedLine`_, `drawThickEllipse`_ and `drawThickFadedEllipse`_.

.. _drawThickFadedLine: https://repository.microej.com/javadoc/microej_5.x/apis/ej/drawing/ShapePainter.html#drawThickFadedLine-ej.microui.display.GraphicsContext-int-int-int-int-int-int-ej.drawing.ShapePainter.Cap-ej.drawing.ShapePainter.Cap-
.. _drawThickEllipse: https://repository.microej.com/javadoc/microej_5.x/apis/ej/drawing/ShapePainter.html#drawThickEllipse-ej.microui.display.GraphicsContext-int-int-int-int-int-
.. _drawThickFadedEllipse: https://repository.microej.com/javadoc/microej_5.x/apis/ej/drawing/ShapePainter.html#drawThickFadedEllipse-ej.microui.display.GraphicsContext-int-int-int-int-int-int-
 
[13.0.2] - 2020-10-02
=====================

* Compatible with Architecture 7.16.0 or higher.
* Use new naming convention: ``com.microej.architecture.[toolchain].[architecture]-ui-pack``.

**Fixed**

* [ESP32] - Potential ``PSRAM`` access faults by rebuilding using esp-idf v3.3.0 toolchain - ``simikou2``.

[13.0.1] - 2020-09-22
=====================

* Compatible with Architecture 7.16.0 or higher.

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

LLAPIs
""""""

**Fixed**

* Missing a LLAPI to check the overlapping between source and destination areas.

Simulator
"""""""""

**Fixed**

* Cannot use an external image decoder on front panel.
* Missing an API to check the overlapping between source and destination areas.

ImageGenerator
""""""""""""""

**Fixed**

* Cannot build a platform with image generator and without front panel.

[13.0.0] - 2020-07-30
=====================

* Compatible with Architecture 7.16.0 or higher.
* Integrate SDK 3.0-B license.

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

Simulator
"""""""""

**Added**

* Able to override MicroUI drawings algorithms like embedded platform.
	
**Changed**

* Compatible with `com.microej.pack.ui#ui-pack(frontpanel)#13.0.0`_.
* See :ref:`Migration notes<section_ui_migration_frontpanelapi_13x>` that describe the available changes in Front Panel API.
	
**Removed**

* ``ej.tool.frontpanel#widget-microui`` has been replaced by ``com.microej.pack.ui#ui-pack(frontpanel)``.

.. _com.microej.pack.ui#ui-pack(frontpanel)#13.0.0: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/13.0.0/
 
ImageGenerator
""""""""""""""

**Added**

* Redirects source image reading to the image generator extension project in order to increase the number of supported image formats in input.
* Redirects destination image generation to the image generator extension project in order to be able to encode an image in a custom RAW format.
* Generates a linker file in order to always link the resources in same order between two launches.
	
**Changed**

* Compatible with `com.microej.pack.ui#ui-pack(imageGenerator)#13.0.0`_.
* See :ref:`Migration notes<section_ui_migration_imagegeneratorapi_13x>` that describe the available changes in Image Generator API.
* Uses a service loader to loads the image generator extension classes.
* Manages image data (pixels) address alignment.
	
**Removed**

* Classpath variable ``IMAGE-GENERATOR-x.x``: Image generator extension project has to use ivy dependency ``com.microej.pack.ui#ui-pack(imageGenerator)`` instead.

.. _com.microej.pack.ui#ui-pack(imageGenerator)#13.0.0: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/13.0.0/

FontGenerator
"""""""""""""

**Changed**

* Used a dedicated ``bss`` section to load characters from an external font instead of using the java heap.

[12.1.5] - 2020-10-02
=====================

* Compatible with Architecture 7.11.0 or higher.
* Use new naming convention: ``com.microej.architecture.[toolchain].[architecture]-ui-pack``.

**Fixed**

* [ESP32] - Potential ``PSRAM`` access faults by rebuilding using esp-idf v3.3.0 toolchain - ``simikou2``.

[12.1.4] - 2020-03-10
=====================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Obsolete references on Java heap are used (since MicroEJ UI Pack 12.0.0).

[12.1.3] - 2020-02-24
=====================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Caps are not used when drawing an anti-aliased line.

[12.1.2] - 2019-12-09
=====================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Fix Graphics Engine empty clip (empty clip had got a size of 1 pixel).
* Clip not respected when clip is set "just after or before" graphics context drawable area: first (or last) line (or column) of graphics context was rendered.

[12.1.1] - 2019-10-29
=====================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Fix Graphics Engine clip (cannot be outside graphics context).

[(maint) 8.0.0] - 2019-10-18
============================

* Compatible with Architecture 7.0.0 or higher.
* Based on 7.4.7.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Pending flush cannot be added after an ``OutOfEventException``.

[12.1.0] - 2019-10-16
=====================

* Compatible with Architecture 7.11.0 or higher.

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

[12.0.2] - 2019-09-23
=====================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* Change ``CM4hardfp_IAR83`` compiler flags.
*  Remove RAW images from cache as soon as possible to reduce java heap usage.
* Do not cache RAW images with their paths to reduce java heap usage.
	
**Fixed**

* Remove useless exception in SystemInputPump.

[12.0.1] - 2019-07-25
=====================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Physical size is not taken in consideration.

Simulator
"""""""""

**Fixed**

* Increase native implementation execution time.
  
[12.0.0] - 2019-06-24
=====================

* Compatible with Architecture 7.11.0 or higher.

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

Simulator
"""""""""

**Added**

* Simulate flush time (add JRE property ``-Dfrontpanel.flush.time=8``).
	
**Fixed**

* A pixel read on an image is always truncated.

FrontPanel Plugin
"""""""""""""""""

**Removed**

* FrontPanel version 5: Move front panel from MicroEJ UI Pack to Architecture *(not backward compatible)*; Architecture contains now Front Panel version 6.

[11.2.0] - 2019-02-01
=====================

* Compatible with Architecture 7.0.0 or higher.

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

[11.1.2] - 2018-08-10
=====================

* Compatible with Architecture 7.0.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Fix drawing bug in thick circle arcs.

[11.1.1] - 2018-08-02
=====================

* Compatible with Architecture 7.0.0 or higher.
* Internal release.

[11.1.0] - 2018-07-27
=====================

* Compatible with Architecture 7.0.0 or higher.
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

[11.0.1] - 2018-06-05
=====================

* Compatible with Architecture 7.0.0 or higher.
* Based on 11.0.0.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Image rendering may be invalid on custom display.
* Render a dynamic image on custom display is too slow.
* LRGB888 image format is always fully opaque.
* Number of colors returned when it is a custom display may be wrong.

[10.0.2] - 2018-02-15
=====================

* Compatible with Architecture 6.13.0 or higher.
* Based on 10.0.1.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Number of colors returned when it is a custom display may be wrong.
* LRGB888 image format is always fully opaque.
* Render a dynamic image on custom display is too slow.
* Image rendering may be invalid on custom display.

[11.0.0] - 2018-02-02
=====================

* Compatible with Architecture 7.0.0 or higher.
* Based on 10.0.1.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* SNI Callback feature in the VM to remove the SNI retry pattern *(not backward compatible)*.

[10.0.1] - 2018-01-03
=====================

* Compatible with Architecture 6.13.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Hard fault when using custom display stack.

[10.0.0] - 2017-12-22
=====================

* Compatible with Architecture 6.13.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* Improve ``TOP-LEFT`` anchor checks.
	
**Fixed**

* Subsequent renderings may not be correctly flushed.
* Rendering of display on display was not optimized.

Simulator
"""""""""

**Changed**

* Check the allocated memory when creating a dynamic image *(not backward compatible)*.

Misc
""""

**Added**

* Option in platform builder to images heap size.

[9.4.1] - 2017-11-24
====================

* Compatible with Architecture 6.12.0 or higher.

ImageGenerator
""""""""""""""

**Fixed**

* Missing some files in image generator module.

[9.4.0] - 2017-11-23
====================

* Compatible with Architecture 6.12.0 or higher.
* Deprecated: use 9.4.1 instead.

MicroUI Implementation
""""""""""""""""""""""
	
**Added**

* LUT image management.

**Changed**

* Optimize character encoding removing first vertical line when possible.
	
**Fixed**

* Memory leak when an ``OutOfEventException`` is thrown.
* A null Java object is not checked when using a font.
  
[9.3.1] - 2017-09-28
====================

* Compatible with Architecture 6.12.0 or higher.
  
MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Returned X coordinates when drawing a string was considered as an error code.
* Exception when loading a font from an application.
* ``LLEXT`` link error with Architecture 6.13+ and UI 9+.
  
[9.3.0] - 2017-08-24
====================

* Compatible with Architecture 6.12.0 or higher.
  
MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Ellipsis must not drawn when text anchor is a "manual" ``TOP-RIGHT``.

Simulator
"""""""""

**Fixed**

* Do not create an AWT window for each image.
* Error when trying to play with an unknown led.
  
[9.2.1] - 2017-08-14
====================

* Compatible with Architecture 6.12.0 or higher.

Simulator
"""""""""

**Added**

* Provide function to send a Long Button event.
* "flush" debug option.
	
**Fixed**

* Mock startup is too long.

[9.2.0] - 2017-07-21
====================

* Compatible with Architecture 6.12.0 or higher.
* Merge 9.1.2 and 9.0.2.

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

ImageGenerator
""""""""""""""

**Fixed**

* Generic displays must be able to generate standard images.

Misc
""""

**Changed**

* SOAR can exclude some resources (update llext output folder).

**Fixed**

* RI build: reduce frontpanel dependency.

[9.0.2] - 2017-04-21
====================

* Compatible with Architecture 6.4.0 or higher.
* Based on 9.0.1.
  
MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Rendering of a RAW image on grayscale display is wrong.

ImageGenerator
""""""""""""""

**Fixed**

* An Ax image may be fully opaque.

[9.1.2] - 2017-03-16
====================

* Compatible with Architecture 6.8.0 or higher.
* Based on 9.1.1.
  
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

ImageGenerator
""""""""""""""

**Fixed**

* Use the application classpath.
* An Ax image may be fully opaque.
    
[9.0.1] - 2017-03-13
====================

* Compatible with Architecture 6.4.0 or higher.
* Based on 9.0.0.
  
MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Hardfault when filling a rectangle on an odd image.
* Pixel rendering on non-standard LCD is wrong.
* RZ hardware accelerator: RAW images have to respect an aligned size.
* Use the classpath when invoking the fonts and images generators.

Simulator
"""""""""

**Fixed**

* Wrong rendering of A8 images.

FrontPanel Plugin
"""""""""""""""""

**Fixed**

* Manage display mask on preview.
* Respect initial background color set by user on preview.
* Preview does not respect the real size of display.

[9.1.1] - 2017-02-14
====================

* Compatible with Architecture 6.8.0 or higher.
* Based on 9.1.0.

Misc
""""

**Fixed**

* RI build: Several custom event generators in same ``microui.xml`` file are not embedded.
  
[9.1.0] - 2017-02-13
====================

* Compatible with Architecture 6.8.0 or higher.
* Based on 9.0.0.

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

Simulator
"""""""""

**Fixed**

* Wrong rendering of A8 images.

FrontPanel Plugin
"""""""""""""""""

**Fixed**

* Manage display mask on preview.
* Respect initial background color set by user on preview.
* Preview does not respect the real size of display.

[9.0.0] - 2017-02-02
====================

* Compatible with Architecture 6.4.0 or higher.

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

Simulator
"""""""""
	
**Added**

* Optional mask on display.

**Changed**

* Display Device UID if available in the window title.

Tools
"""""

**Changed**

* FrontPanel plugin: Update icons.
* FontDesigner plugin: Update icons.
* Font Designer and Generator: use Unicode 9.0.0 specification.

Misc
""""

**Fixed**

* Remove obsolete documentations from FrontPanel And FontDesigner plugins.

[8.1.0] - 2016-12-24
====================

* Compatible with Architecture 6.4.0 or higher.

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

Simulator
"""""""""

**Added**

* Can add an additional screen on simulator.

[8.0.0] - 2016-11-17
====================

* Compatible with Architecture 6.4.0 or higher.

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

Simulator
"""""""""

**Added**

* Can decode additional image formats.
	
**Fixed**

* Cannot set initial value of StateEventGenerator.

[7.4.7] - 2016-06-14
====================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Do not create all fonts derivations of built-in styles.
* A bold font is not flagged as bold font.
* Wrong A4 image rendering.

Simulator
"""""""""

**Fixed**

* Cannot convert an image.

[7.4.2] - 2016-05-25
====================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* invalid image drawing for *column* display.
  
[7.4.1] - 2016-05-10
====================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* Restore stack 1, 2 and 4 BPP.
  
[7.4.0] - 2016-04-29
====================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* image A1's width is sometimes invalid.

Simulator
"""""""""

**Added**

* Restore stack 1, 2 and 4 BPP.
  
[7.3.0] - 2016-04-25
====================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Added**

* Stack 8BPP with LUT support.
 
[7.2.1] - 2016-04-18
====================

* Compatible with Architecture 6.1.0 or higher.

Misc
""""

**Fixed**

* Remove ``java`` keyword in workbench extension.
  
[7.2.0] - 2016-04-05
====================

* Compatible with Architecture 6.1.0 or higher.

Tools
"""""

**Added**

* Preprocess ``*.xxx.list`` files.
  
[7.1.0] - 2016-03-02
====================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Added**

* Manage several images RAW formats.
  
[7.0.0] - 2016-01-20
====================

* Compatible with Architecture 6.1.0 or higher.

Misc
""""

**Changed**

* Remove ``@jpf.property.header@`` prefix to Application options *(not backward compatible)*.
  
[6.0.1] - 2015-12-17
====================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

* A negative clip throws an exception on simulator.

[6.0.0] - 2015-11-12
====================

MicroUI Implementation
""""""""""""""""""""""

**Changed**

* LLDisplay for UIv2 *(not backward compatible)*.

..
   | Copyright 2021-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
