.. _ui_port_conf:

=====================
UI Port Configuration
=====================

Principle
=========

The first step consists of updating the VEE Port Configuration project (often called ``xxx-configuration``): the project that holds the :ref:`mmm_module_description` ``module.ivy``.
This update consists of several steps described in the chapters below. All steps are not mandatory according to the board capabilities.

.. warning:: This chapter considers the VEE Port is performed and functional (see :ref:`new_platform_creation`).

UI Pack Selection
=================

The UI Pack holds several modules, including the Graphics Engine.
The Graphics Engine is a library already compiled for an MCU and a C compiler.
Consequently, the MicroEJ Central Repository offers several UI Packs according to the couple MCU/Compiler (as the MicroEJ Architecture).

Refer to the chapter :ref:`pack_import` to add the expected UI Pack:

.. code-block:: xml
   :emphasize-lines: 3

   <dependencies>
       <!-- MicroEJ Architecture Specific Pack -->
       <dependency org="com.microej.architecture.CM4.CM4hardfp_GCC48" name="flopi4G25-ui-pack" rev="13.4.1"/>
   </dependencies>

UI Pack Modules
===============

The UI Pack holds several modules. 
Following chapters describe each module (aim and configuration).

The modules provided by the UI Pack are **not installed** by default.
They must be enabled and configured using the Platform Editor.

.. figure:: images/ui_modules.*
   :alt: UI Pack Modules

   UI Pack Modules

Refers to the chapter :ref:`platform_module_configuration` to add the UI Pack modules.

Module MicroUI
==============

This module holds the MicroUI implementation library. 
Refers to the chapter :ref:`section_microui` to have more information.

This module is **not optional** and must be checked.

This module requires a static initialization to specify the MicroUI features the application can use.

1. Create the file ``[VEE Port Configuration project]/microui/microui.xml`` 
2. Fill the file as described here: :ref:`section_static_init`.

.. code-block:: xml

   <microui>

       <display name="DISPLAY"/>
       
       <eventgenerators>
           <command name="COMMANDS"/>
           <buttons name="BUTTONS" extended="3"/>
           <buttons name="JOYSTICK" extended="5"/>
           <touch name="TOUCH" display="DISPLAY"/>
       </eventgenerators>
       
       <fonts>
           <font file="resources\fonts\myfont.ejf"/>
       </fonts>

   </microui>

Module LEDs
===========

MicroUI provides some API to manipulate the LEDs.
This module allows the UI Port to drive the LEDs.
Refers to the chapter :ref:`section_leds` to have more information.

This module is optional: when not selected, a stub implementation is used, and the UI Port does not need to provide a stub implementation.

Modules Image Decoders
======================

.. note:: This chapter only applies when the board holds a display. 

This module adds an internal image decoder that allows the application to embed an encoded image (PNG or BMP Monochrom) and to let the Graphics Engine decodes it at runtime.
Both decoders (PNG and BMP Monochrom) are optional and can be selected (or not) independently.
Refers to the chapter :ref:`image_runtime_decoder` to have more information.

This module is optional: when no image decoder is embedded, the Graphics Engine asks the UI Port (thanks to Low-level API) to decode the encoded images.

Module Image Generator
======================

.. note:: This chapter only applies when the board holds a display. 

This module allows decoding the application's images at compile-time.
The application's images are decoded and stored in a binary format compatible with the Graphics Engine.
The footprint is bigger, but the image loading at runtime is null.
Refers to the chapter :ref:`section_image_generator` to have more information.

This module is optional: when not selected, the application cannot embed generated images compatible with the Graphics Engine.

Module Font Generator
======================

.. note:: This chapter only applies when the board holds a display. 

This module allows embedding the application's fonts.
The application's fonts (EJF files) are decoded and stored in a binary format compatible with the Graphics Engine.
Refers to the chapter :ref:`section_fontgen` to have more information.

This module is optional: when not selected, the application cannot embed fonts compatible with the Graphics Engine.

Module Display
==============

.. note:: This chapter only applies when the board holds a display. 

This chapter takes the concepts described in chapter :ref:`section_display`. 
The first step is determining the kind of display: size, pixel format, and constraints.
This information will be used later by the UI Port configuration project, the Simulator extension project, and the BSP.

Size
----

The size is expressed in *pixels*, often 320x240 or 480x272. 
This size defines the area the application can target; it can retrieve this size by calling ``Display.getWidth()`` and ``Display.getHeight()``.
It is always a rectangular area, even for the rounded displays (a square area frames a rounded display).

The display size is fixed for a display: retrieve this size in the board's datasheet.

Pixel Format
------------

The display pixel format (or pixel structure) gives two notions: the number of bits-per-pixel and the organization of color components in these bits. 

The number of bits-per-pixel (bpp) is an integer value among this list: 1, 2, 4, 8, 16, 24, or 32.

The color components organization explains how the color components (Red, Green, and Blue) are distributed in the pixel.
A more oversized display pixel format is (in bits) better in the definition.
This format also indicates the number of bits-per-pixel.
For instance, the format RGB565 is a 16-BPP format, indicating that the five MSB bits are for the Red color component, the six next bits are for the Green component, and the five LSB bits are for the Blue component.
This pixel format can be symbolized by ``RRRRRGGGGGGBBBBB`` or ``RRRR RGGG GGGB BBBB``.

The display pixel format is often fixed by the display itself (its capabilities) and by the memory bus between the MCU and the LCD module. 
However, the display pixel format is often configurable by the LCD controller. 
Note that the number of bits-per-pixel and the display size fix the required memory to allocate: ``memory_size = width x height x bpp / 8``.
Consequently, the pixel format may be less precise than the display capabilities to preserve memory.
For instance, RGB565, whereas the display is a 24-bit display (RGB888).

Constraints
-----------

The hardware (display, bus, memory, etc.) may require some constraints:

- The pixel format: Some hardware cannot use another pixel format other than the display. This format may be standard or custom. See :ref:`display_pixel_structure`.
- The size of the buffers: The available memory may be limited. This limitation can drive the chosen pixel format.
- Memory alignment: Some LCD controllers require a memory alignment on the display buffer (alignment on 64 bits, for instance).
- Buffer width alignment: Some LCD controllers also require an alignment for each line. The line size (in pixels) in memory may be larger than the display line size (width): this is the stride. The alignment constraint may be expressed in pixels or bytes. The required memory to allocate becomes: ``memory_size = stride (in pixels) x height x bpp / 8``.

Configuration
-------------

In the VEE Port Configuration project, create and fill the file ``display.properties``:

1. Create the file ``[VEE Port Configuration project]/display/display.properties`` 
2. Fill the file as described here: :ref:`section_display_installation`, according to the pixel format and the display constraints.

.. code-block:: java

   bpp=rgb565
   imageBuffer.memoryAlignment=32
   memoryLayout=line
   byteLayout=line

VEE Port Build
==============

Once modules are selected and configured, the VEE Port can be built again; see :ref:`platform_build`.

.. note: When a module is removed, added, or re-configured, the VEE Port must be built again.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
