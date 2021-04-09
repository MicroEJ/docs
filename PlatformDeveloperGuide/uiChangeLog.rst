.. _section_ui_changelog:

=========
Changelog
=========

13.0.6 (2021-03-29)
===================

* Compatible with Architecture 7.13.0 or higher.

LLAPIs
""""""

**Fixed**

	* Size of the typedef ``MICROUI_Image``: do not depend on the size of the enumeration ``MICROUI_ImageFormat`` (``LLUI_PAINTER_impl.h``).

13.0.5 (2021-03-08)
===================

* Compatible with Architecture 7.13.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Removed**

	* Remove ResourceManager dependency.

**Fixed**

	* A feature was not able to call Display.callOnFlushCompleted().
	* Stop feature: prevent NullPointerException when a kernel's EventGenerator is removed from event generators pool.
	* Filter DeadFeatureException in MicroUI pump. .
	* Drawing of thick arcs which represent an almost full circle.
	* Drawing of thick faded arcs which pass by 0° angle.

Simulator
"""""""""

**Fixed**

	* Front panel memory management: reduce simulation time.

13.0.4 (2021-01-15)
===================

* Compatible with Architecture 7.13.0 or higher.

MicroUI API
"""""""""""

**Changed**

	* [Changed] Include `MicroUI API 3.0.3 <https://repository.microej.com/artifacts/ej/api/microui/3.0.3/>`_.
	* [Changed] Include `MicroUI Drawing API 1.0.2 <https://repository.microej.com/artifacts/ej/api/drawing/1.0.2/>`_.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Fix each circle arc cap being drawn on both sides of an angle.
	* Fix drawing of rounded caps of circle arcs when fade is 0.
	* Cap thickness and fade in thick drawing algorithms.
	* Clip is not checked when filling arcs, circles and ellipsis.
	* Image path when loading an external image (``LLEXT``).
	* ``InternalLimitsError`` when calling ``MicroUI.callSerially()`` from a feature.

Drawing Implementation
""""""""""""""""""""""

**Fixed**

	* Draw deformed image is not rendered.

ImageGenerator
""""""""""""""

**Changed**

	* Compatible with `com.microej.pack.ui#ui-pack(imageGenerator)#13.0.4 <https://repository.microej.com/artifacts/com/microej/pack/ui/ui-pack/13.0.4/>`_.
	
**Fixed**

	* ``NullPointerException`` when trying to convert an unknown image.
	* Restore external resources option in MicroEJ launcher.

13.0.3 (2020-12-03)
===================

* Compatible with Architecture 7.13.0 or higher.
 
MicroUI API
"""""""""""

**Changed**

	* [Changed] Include MicroUI API 3.0.2.
	* [Changed] Include MicroUI Drawing API 1.0.1.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Reduce Java heap usage. .
	* Fix empty images heap.
	* Draw image algorithm does not respect image stride in certain circumstances.
	* Fix flush limits of ``drawThickFadedLine``, ``drawThickEllipse`` and ``drawThickFadedEllipse``.
 
13.0.2 (2020-10-02)
===================

* Compatible with Architecture 7.13.0 or higher.
* Use new naming convention: ``com.microej.architecture.[toolchain].[architecture]-ui-pack``.

**Fixed**

	* [ESP32] - Potential ``PSRAM`` access faults by rebuilding using esp-idf v3.3.0 toolchain - ``simikou2``.

13.0.1 (2020-09-22)
===================

* Compatible with Architecture 7.13.0 or higher.

MicroUI API
"""""""""""

**Changed**

	* Include `MicroUI API 3.0.1 <https://repository.microej.com/artifacts/ej/api/microui/3.0.1/>`_.
 
MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Throw an exception when there is no display.
	* Antialiased circle may be cropped.
	* ``FillRoundRectangle`` can give invalid arguments to ``FillRectangle``.
	* Flush bounds may be invalid.
	* Reduce memory footprint (java heap and immortal heap).
	* No font is loaded when an external font is not available.
	* A8 color is cropped to display limitation too earlier on simulator.

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

13.0.0 (2020-07-30)
===================

* Compatible with Architecture 7.13.0 or higher.
* Integrate SDK 3.0-B license.

MicroUI API
"""""""""""

**Changed**

	* [Changed] Include `MicroUI API 3.0.0 <https://repository.microej.com/artifacts/ej/api/microui/3.0.0/>`_.
	* [Changed] Include `MicroUI Drawing API 1.0.0 <https://repository.microej.com/artifacts/ej/api/drawing/1.0.0/>`_.

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
	* Some header files list the libraries ``ej.api.microui`` and ``ej.api.drawing`` natives. Provided by Abstraction Layer implementation module `com.microej.clibrary.llimpl#microui <https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui>`_.
	* Some header files list the drawing algorithms the platform can implement; all algorithms are optional.
	* Some header files list the internal graphical engine software algorithms the platform can call.
	
**Changed**

	* All old header files and functions have been renamed or shared.
	* See :ref:`Migration notes<section_ui_migration_llapi_13x>` that describe the available changes in LLAPI.

Simulator
"""""""""

**Added**

	* Able to override MicroUI drawings algorithms like embedded platform.
	
**Changed**

	* Compatible with `com.microej.pack.ui#ui-pack(frontpanel)#13.0.0 <https://repository.microej.com/artifacts/com/microej/pack/ui/ui-pack/13.0.0/>`_.
	* See :ref:`Migration notes<section_ui_migration_frontpanelapi_13x>` that describe the available changes in Front Panel API.
	
**Removed**

	* ``ej.tool.frontpanel#widget-microui`` has been replaced by ``com.microej.pack.ui#ui-pack(frontpanel)``. .
 
ImageGenerator
""""""""""""""

**Added**

	* Redirects source image reading to the image generator extension project in order to increase the number of supported image formats in input.
	* Redirects destination image generation to the image generator extension project in order to be able to encode an image in a custom RAW format.
	* Generates a linker file in order to always link the resources in same order between two launches.
	
**Changed**

	* Compatible with `com.microej.pack.ui#ui-pack(imageGenerator)#13.0.0 <https://repository.microej.com/artifacts/com/microej/pack/ui/ui-pack/13.0.0/>`_.
	* See :ref:`Migration notes<section_ui_migration_imagegeneratorapi_13x>` that describe the available changes in Image Generator API.
	* Uses a service loader to loads the image generator extension classes.
	* Manages image data (pixels) address alignment.
	
**Removed**

	* Classpath variable ``IMAGE-GENERATOR-x.x``: Image generator extension project has to use ivy dependency ``com.microej.pack.ui#ui-pack(imageGenerator)`` instead.

FontGenerator
"""""""""""""

**Changed**

	* Used a dedicated ``bss`` section to load characters from an external font instead of using the java heap.

12.1.5 (2020-10-02)
===================

* Compatible with Architecture 7.11.0 or higher.
* Use new naming convention: ``com.microej.architecture.[toolchain].[architecture]-ui-pack``.

**Fixed**

	* [ESP32] - Potential ``PSRAM`` access faults by rebuilding using esp-idf v3.3.0 toolchain - ``simikou2``.

12.1.4 (2020-03-10)
===================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Obsolete references on Java heap are used (since MicroEJ UI Pack 12.0.0).

12.1.3 (2020-02-24)
===================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Caps are not used when drawing an anti-aliased line.

12.1.2 (2019-12-09)
===================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Fix graphical engine empty clip (empty clip had got a size of 1 pixel).
	* Clip not respected when clip is set "just after or before" graphics context drawable area: first (or last) line (or column) of graphics context was rendered.

12.1.1 (2019-10-29)
===================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Fix graphical engine clip (cannot be outside graphics context).

(maint) 8.0.0 (2019-10-18)
==========================

* Compatible with Architecture 7.0.0 or higher.
* Based on 7.4.7.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Pending flush cannot be added after an OutOfEventException.

12.1.0 (2019-10-16)
===================

* Compatible with Architecture 7.11.0 or higher.

MicroUI API
"""""""""""

**Changed**

	* Include `MicroUI API 2.4.0 <https://repository.microej.com/artifacts/ej/api/microui/2.4.0/>`_.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

	* Prepare inlining of get X/Y/W/H methods.
	* Reduce number of strings embedded by MicroUI library.
	
**Fixed**

	* Pending flush cannot be added after an ``OutOfEventException``.
	* ``Display.isColor()`` returns an invalid value.
	* Draw/fill circle/ellipse arc is not drawn when angle is negative.

12.0.2 (2019-09-23)
===================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

	* Change ``CM4hardfp_IAR83`` compiler flags.
	*  Remove RAW images from cache as soon as possible to reduce java heap usage.
	* Do not cache RAW images with their paths to reduce java heap usage.
	
**Fixed**

	* Remove useless exception in SystemInputPump.

12.0.1 (2019-07-25)
===================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Physical size is not taken in consideration.

Simulator
"""""""""

**Fixed**

	* Increase native implementation execution time.
  
12.0.0 (2019-06-24)
===================

* Compatible with Architecture 7.11.0 or higher.

MicroUI Implementation
""""""""""""""""""""""
	
**Added**

	* Trace MicroUI events and log them on SystemView.

**Changed**

	* Manage the Graphics Context clip on native side.
	* Use java heap to store images metadata instead of using icetea heap (remove option "max offscreen").
	* Optimize retrieval of all fonts .
	* Ensure user buffer size is larger than LCD size .
	* Use java heap to store flying images metadata instead of using icetea heap (remove option "max flying images") .
	* Use java heap to store fill polygon algorithm's objects instead of using icetea heap (remove option "max edges") .
	* ``SecurityManager`` enabled as a boolean constant option (footprint removal by default).
	* Remove ``FlyingImage`` feature using BON constants (option to enable it) .
	
**Fixed**

	* Wrong rendering of a fill polygon on emb.
	* Wrong rendering of image overlaping on C1/2/4 platforms.
	* Wrong rendering of a LUT image with more than 127 colors on emb.
	* Wrong rendering of an antialiased arc with 360 angle.
	* Debug option com.is2t.microui.log=true fails when there is a flying image.
	* Gray scale between gray and white makes magenta.
	* Minimal size of some buffers set by user is never checked .
	* The format of a RAW image using "display" format is wrong.
	* Dynamic image width for platform C1/2/4 may be wrong.
	* Wrong pixel address when reading from a C2/4 display.
	* ``getDisplayColor()`` can return a color with transparency (spec is ``0x00RRGGBB``).
	* A fully opaque image is tagged as transparent (ARGB8888 platform).

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

11.2.0 (2019-02-01)
===================

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

11.1.2 (2018-08-10)
===================

* Compatible with Architecture 7.0.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Fix drawing bug in thick circle arcs.

11.1.1 (2018-08-02)
===================

* Compatible with Architecture 7.0.0 or higher.
* Internal release.

11.1.0 (2018-07-27)
===================

* Compatible with Architecture 7.0.0 or higher.
* Merge 10.0.2 and 11.0.1.

MicroUI API
"""""""""""

**Changed**

	* Include `MicroUI API 2.3.0 <https://repository.microej.com/artifacts/ej/api/microui/2.3.0/>`_.

MicroUI Implementation
""""""""""""""""""""""

**Added**

	* ``LLDisplay``: prepare round LCD.
	
**Fixed**

	* ``Fillrect`` throws a hardfault on 8bpp platform.
	* Rendering of a LUT image is wrong when using software algorithm.

11.0.1 (2018-06-05)
===================

* Compatible with Architecture 7.0.0 or higher.
* Based on 11.0.0.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Image rendering may be invalid on custom display.
	* Render a dynamic image on custom display is too slow.
	* LRGB888 image format is always fully opaque.
	* Number of colors returned when it is a custom display may be wrong.

10.0.2 (2018-02-15)
===================

* Compatible with Architecture 6.13.0 or higher.
* Based on 10.0.1.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Number of colors returned when it is a custom display may be wrong.
	* LRGB888 image format is always fully opaque.
	* Render a dynamic image on custom display is too slow.
	* Image rendering may be invalid on custom display.

11.0.0 (2018-02-02)
===================

* Compatible with Architecture 7.0.0 or higher.
* Based on 10.0.1.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

	* SNI Callback feature in the VM to remove the SNI retry pattern *(not backward compatible)*.

10.0.1 (2018-01-03)
===================

* Compatible with Architecture 6.13.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Hard fault when using custom display stack.

10.0.0 (2017-12-22)
===================

* Compatible with Architecture 6.13.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

	* Improve ``TOP-LEFT`` anchor checks .
	
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

9.4.1 (2017-11-24)
==================

* Compatible with Architecture 6.12.0 or higher.

ImageGenerator
""""""""""""""

**Fixed**

	* Missing some files in image generator module.

9.4.0 (2017-11-23)
==================

* Compatible with Architecture 6.12.0 or higher.
* Deprecated: use 9.4.1 instead.

MicroUI Implementation
""""""""""""""""""""""
	
**Added**

	* LUT image management.

**Changed**

	* Optimize character encoding removing first vertical line when possible.
	
**Fixed**

	* Memory leak when an ``OutOfEvent`` exception is thrown.
	* A null Java object is not checked when using a font.
  
9.3.1 (2017-09-28)
==================

* Compatible with Architecture 6.12.0 or higher.
  
MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Returned X coordinates when drawing a string was considered as an error code .
	* Exception when loading a font from an application .
	* ``LLEXT`` link error with Architecture 6.13+ and UI 9+.
  
9.3.0 (2017-08-24)
==================

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
  
9.2.1 (2017-08-14)
==================

* Compatible with Architecture 6.12.0 or higher.

Simulator
"""""""""

**Added**

	* Provide function to send a Long Button event.
	* "flush" debug option.
	
**Fixed**

	* Mock startup is too long.

9.2.0 (2017-07-21)
==================

* Compatible with Architecture 6.12.0 or higher.
* Merge 9.1.2 and 9.0.2.

MicroUI API
"""""""""""

**Changed**

	* Include `MicroUI API 2.2.0 <https://repository.microej.com/artifacts/ej/api/microui/2.2.0/>`_.
  
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
	* ``Display.flush()``: ymax can be higher than display.height.

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

9.0.2 (2017-04-21)
==================

* Compatible with Architecture 6.4.0 or higher.
* Based on 9.0.1.
  
MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Rendering of a RAW image on grayscale display is wrong .

ImageGenerator
""""""""""""""

**Fixed**

	* An Ax image may be fully opaque.

9.1.2 (2017-03-16)
==================

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
	* ``Font.getWidth()`` and ``getHeight()`` don't use ratio factor.
	* Draw antialiased circle arc render issue.
	* Draw antialiased circle arc render bug with 45° angles.
	* MicroUI lib expects the dynamic image decoder default format.
	* Wrong error code is returned when converting an image.

ImageGenerator
""""""""""""""

**Fixed**

	* Use the application classpath.
	* An Ax image may be fully opaque.
    
9.0.1 (2017-03-13)
==================

* Compatible with Architecture 6.4.0 or higher.
* Based on 9.0.0.
  
MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Hardfault when filling a rectangle on an odd image .
	* Pixel rendering on non-standard LCD is wrong.
	* RZ hardware accelerator: RAW images have to respect an aligned size .
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

9.1.1 (2017-02-14)
==================

* Compatible with Architecture 6.8.0 or higher.
* Based on 9.1.0.

Misc
""""

**Fixed**

	* RI build: Several custom event generators in same ``microui.xml`` file are not embedded.
  
9.1.0 (2017-02-13)
==================

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

	* Hardfault when filling a rectangle on an odd image .
	* Pixel rendering on non-standard LCD is wrong.
	* RZ hardware accelerator: RAW images have to respect an aligned size .
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

9.0.0 (2017-02-02)
==================

* Compatible with Architecture 6.4.0 or higher.

MicroUI API
"""""""""""

**Changed**

	* Include `MicroUI API 2.0.6 <https://repository.microej.com/artifacts/ej/api/microui/2.0.6/>`_.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

	* Update MicroUI to use watchdogs in KF implementation.
	
**Fixed**

	* Display linker file is required even if there is no display on platform .
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

8.1.0 (2016-12-24)
==================

* Compatible with Architecture 6.4.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Changed**

	* Improve image drawing timings .
	* Runtime decoders can force the output RAW image's fully opacity.

MWT
"""

**Fixed**

	* With two panels, the paint is done but the screen is not refreshed.
	* Widget show notify method is called before the panel is set.
	* Widget still linked to panel when ``lostFocus()`` is called. .

Simulator
"""""""""

**Added**

	* Can add an additional screen on simulator.

8.0.0 (2016-11-17)
==================

* Compatible with Architecture 6.4.0 or higher.

MicroUI Implementation
""""""""""""""""""""""
	
**Added**

	* RZ UI acceleration.
	* External image decoders .
	* Manage external memories like internal memories. .
	* Custom display stacks (hardware acceleration).

**Changed**

	* Merge stacks ``DIRECT/COPY/SWITCH`` *(not backward compatible)*.
	
**Fixed**

	* add KF rule: a thread cannot enter in a feature code while it owns a kernel monitor .
	* automatic flush is not waiting the end of previous flush.
	* Invalid image rotation rendering.
	* Do not embed Images & Fonts.list of kernel API classpath in app mode .
	* Invalid icetea heap allocation .
	* microui image: invalid "defaultformat" and "format" fields values.

MWT
"""

**Fixed**

	* possible to create an inconsistent hierarchy.

Simulator
"""""""""

**Added**

	* Can decode additional image formats .
	
**Fixed**

	* Cannot set initial value of StateEventGenerator.

7.4.7 (2016-06-14)
==================

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

7.4.2 (2016-05-25)
==================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* invalid image drawing for *column* display.
  
7.4.1 (2016-05-10)
==================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* Restore stack 1, 2 and 4 BPP.
  
7.4.0 (2016-04-29)
==================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* image A1's width is sometimes invalid.

Simulator
"""""""""

**Added**

	* Restore stack 1, 2 and 4 BPP.
  
7.3.0 (2016-04-25)
==================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Added**

	* Stack 8BPP with LUT support.
 
7.2.1 (2016-04-18)
==================

* Compatible with Architecture 6.1.0 or higher.

Misc
""""

**Fixed**

	* Remove ``java`` keyword in workbench extension.
  
7.2.0 (2016-04-05)
==================

* Compatible with Architecture 6.1.0 or higher.

Tools
"""""

**Added**

	* Preprocess ``*.xxx.list`` files.
  
7.1.0 (2016-03-02)
==================

* Compatible with Architecture 6.1.0 or higher.

MicroUI Implementation
""""""""""""""""""""""

**Added**

	* Manage several images RAW formats.
  
7.0.0 (2016-01-20)
==================

* Compatible with Architecture 6.1.0 or higher.

Misc
""""

**Changed**

	* Remove jpf property header *(not backward compatible)*.
  
6.0.1 (2015-12-17)
==================

MicroUI Implementation
""""""""""""""""""""""

**Fixed**

	* A negative clip throws an exception on simulator.

6.0.0 (2015-11-12)
==================

MicroUI Implementation
""""""""""""""""""""""

**Changed**

	* LLDisplay for UIv2 *(not backward compatible)*.

..
   | Copyright 2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
