.. _ui_port_conf:

=====================
UI Port Configuration
=====================

Principle
=========

The first step is to update the :ref:`VEE Port Configuration project <platform_configuration_creation>` (often named ``xxx-configuration``): this project holds the :ref:`mmm_module_description` (``module.ivy``).
This update is done in several steps, described in the sections below. Some steps are optional, depending on the capabilities of the hardware.

.. warning:: This chapter assumes that a valid VEE Port has been created (as described in the chapter :ref:`new_platform_creation`).

UI Pack Selection
=================

The UI Pack bundles several modules, including the Graphics Engine.
The Graphics Engine is a library already compiled for an MCU and a C compiler.
The :ref:`MicroEJ Central Repository <central_repository>` provides UI Packs for a set of MCU/Compiler pairs (like for MicroEJ Architectures).

Refer to the chapter :ref:`pack_import` to add the required UI Pack. 
As an example, the module dependency to add for a Cortex-M4 and GCC toolchain would be:

.. code-block:: xml
   :emphasize-lines: 3

   <dependencies>
       <!-- MicroEJ Architecture Specific Pack -->
       <dependency org="com.microej.architecture.CM4.CM4hardfp_GCC48" name="flopi4G25-ui-pack" rev="13.4.1"/>
   </dependencies>

UI Pack Modules
===============

The following sections describe each module that comes with the UI Pack (purpose and configuration).

The modules provided by the UI Pack are **not installed** by default.
When a module is required, it has to be enabled and configured using the Platform Editor.

.. figure:: images/ui_modules.*
   :alt: UI Pack Modules

   UI Pack Modules

Refer to the chapter :ref:`platform_module_configuration` to add the UI Pack modules.

Module MicroUI
==============

MicroUI is a Foundation Library that defines a Low Level UI framework (refer to the chapter :ref:`section_microui` for more information).
The **mandatory** module MicroUI (it must be checked in the VEE Port configuration file) provides the MicroUI implementation library.
It requires a static initialization step to specify what MicroUI features are available for the application layer:

1. Create the file ``[VEE Port Configuration project]/microui/microui.xml`` 
2. Edit the file as described here: :ref:`section_static_init`.

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
Refer to the chapter :ref:`section_leds` to have more information.

This module is optional: when not selected, a stub implementation is used, and the UI Port does not need to provide one.

Modules Image Decoders
======================

.. note:: This chapter only applies when the device has a display. 

This module adds an internal image decoder: it allows the application to embed an encoded image (e.g., PNG or BMP Monochrom) and let the Graphics Engine decode it at runtime.
Both decoders (PNG and BMP Monochrom) are optional and can be selected (or not) independently.
Refer to the chapter :ref:`image_runtime_decoder` to have more information.

This module is optional: when no image decoder is embedded, the Graphics Engine relies on the UI Port (thanks to Abstraction Layer API) to decode the images.

Module Image Generator
======================

.. note:: This chapter only applies when the device has a display. 

This module allows decoding the application's images at compile-time.
The application's images are decoded and stored in a binary format compatible with the Graphics Engine.
The memory footprint of the application is higher, but the image loading time at runtime is very low.
Refer to the chapter :ref:`section_image_generator` to have more information.

This module is optional: when not selected, the application cannot embed generated images compatible with the Graphics Engine.

Module Font Generator
=====================

.. note:: This chapter only applies when the device has a display. 

This module allows for embedding the MicroEJ bitmap fonts of the application.
The application's fonts (EJF files) are decoded and stored in a binary format compatible with the Graphics Engine.
Refer to the chapter :ref:`section_fontgen` to have more information.

This module is optional: when not selected, the application cannot embed fonts compatible with the Graphics Engine.

Module Display
==============

.. note:: This chapter only applies when the device has a display. 

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

The color components organization defines how the color components (Red, Green, and Blue) are distributed in the pixel.
The greater the display pixel format (in bits), the better is the definition.
This format also indicates the number of bits-per-pixel.
For instance, the format RGB565 is a 16-BPP format, indicating that the five MSB bits are for the Red color component, the six next bits are for the Green component, and the five LSB bits are for the Blue component.
This pixel format can be symbolized by ``RRRRRGGGGGGBBBBB`` or ``RRRR RGGG GGGB BBBB``.

The display pixel format is often fixed by the display itself (its capabilities) and by the memory bus between the MCU and the LCD module. 
However, the display pixel format is often configurable by the LCD controller. 
Note that the number of bits-per-pixel and the display size fix the required memory to allocate: ``memory_size = width x height x bpp / 8``.
Consequently, the pixel format may be less precise than the display capabilities depending on the memory available on the device.
For instance, the RGB565 format may be used whereas the display is a 24-bit display (RGB888).

Constraints
-----------

The hardware constraints (display, bus, memory, etc.) may drive the configuration:

- The pixel format: Some hardware cannot use another pixel format other than the one of the display. This format may be standard or custom. See :ref:`display_pixel_structure`.
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
