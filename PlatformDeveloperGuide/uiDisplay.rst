.. _section_display:

=======
Display
=======


Principle
=========

The Display module contains the C part of the MicroUI implementation which manages graphical displays. This module is composed of three elements:

- the C part of MicroUI Display API (a built-in C archive) called Graphics Engine,
- an implementation of a Low Level APIs for the displays (LLUI_DISPLAY) that the BSP must provide (see :ref:`LLDISPLAY-API-SECTION`),
- an implementation of a Low Level APIs for MicroUI drawings.


Functional Description
======================

The Display module implements the MicroUI graphics framework. This framework is constituted of several notions: the display characteristics (size, format, backlight, contrast, etc.), the drawing state machine (render, flush, wait flush completed), the images life cycle, the fonts and drawings. The main part of the Display module is provided by a built-in C archive called Graphics Engine. This library manages the drawing state machine mechanism, the images and fonts. The display characteristics and the drawings are managed by the ``LLUI_DISPLAY`` implementation.   

The Graphics Engine is designed to let the BSP use an optional graphics processor unit (GPU) or an optional third-party drawing library. Each drawing can be implemented independently. If no extra framework is available, the Graphics Engine performs all drawings in software. 
In this case, the BSP has to perform a very simple implementation (four functions) of the Graphics Engine low-level APIs.

MicroUI library also gives the possibility to perform some additional drawings which are not available as API in MicroUI library. The Graphics Engine gives a set of functions to synchronize the drawings between them, to get the destination (and sometimes source) characteristics, to call internal software drawings, etc. 

Front Panel (simulator Graphics Engine part) gives the same possibilities. Same constraints can be applied, same drawings can be overridden or added, same software drawing rendering is performed (down to the pixel).

.. _section_display_modes:

Display Configurations
======================

The Graphics Engine provides a number of different configurations. The appropriate configuration should be selected depending on the capabilities of the screen and other related hardware, such as display controllers.

The modes can vary in three ways:

-  the buffer mode: double-buffer, simple buffer (also known as *direct*),
-  the memory layout of the pixels,
-  pixel format or depth.

Buffer Modes
============

Overview
--------

When using the double buffering technique, the memory into which the application draws (called graphics buffer or back buffer) is not the memory used by the screen to refresh it (called frame buffer or display
buffer). When everything has been drawn consistently from the application point of view, the back buffer contents are synchronized with the display buffer. Double buffering avoids flickering and inconsistent rendering: it is well suited to high quality animations.

For more static display-based applications, and/or to save memory, an alternative configuration is to use only one buffer, shared by both the application and the screen.

Displays addressed by one of the standard configurations are called *generic displays*. For these generic displays, there are three buffer modes: switch, copy and direct. The following flow chart provides a
handy guide to selecting the appropriate buffer mode according to the hardware configuration.

.. figure:: images/display_modes_nocustom.*
   :alt: Buffer Modes
   :scale: 50%
   :align: center

   Buffer Modes

Implementation
--------------

The Graphics Engine does not depend on the type of buffer mode. The implementation of `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_  calls the Low Level API ``LLUI_DISPLAY_IMPL_flush`` to let the BSP to update the display data. This function should be atomic and the implementation has to return the new graphics buffer address (back buffer address). In
``direct`` and ``copy`` modes, this address never changes and the implementation has always to return the back buffer address. In ``switch`` mode, the implementation has to return the old display frame buffer address.

The next sections describe the work to do for each mode.

.. _switchBufferMode:

Switch
------

The switch mode is a double-buffered mode where two buffers in RAM alternately play the role of the back buffer and the display buffer. The display source is alternatively changed from one buffer to the other. Switching the source address may be done asynchronously. The synchronize function is called before starting the next set of draw operations, and must wait until the driver has switched to the new buffer.

Synchronization steps are described :ref:`below <switchModeSyncSteps>`.

.. _switchModeSyncSteps :

- | *Step 1:* Drawing
  | MicroUI is drawing in buffer 0 (back buffer) and the display is reading its contents from buffer 1 (display buffer).

.. figure:: images/switch-step1.*
   :alt: Step 1: Drawing
   :width: 400px
   :align: center

- | *Step 2:* Switch
  | The drawing is done. Set that the next read will be done from buffer 0.
  | Note that the display \"hardware component\" asynchronously continues to read data from buffer 1.

.. figure:: images/switch-step2.*
   :alt: Step 2: Switch
   :width: 400px
   :align: center

- | *Step 3:* Copy
  | A copy from the buffer 0 (new display buffer) to the buffer 1 (new back buffer) must be done to keep the contents of the current drawing. The copy routine must wait until the display has finished the switch, and start asynchronously by comparison with the MicroUI drawing routine (see next step). 
  | This copy routine can be done in a dedicated RTOS task or in an interrupt routine. The copy should start after the display \"hardware component\" has finished a full buffer read to avoid flickering.
  | Usually a tearing signal from the display at the end of the read of the previous buffer (buffer 1) or at the beginning of the read of the new buffer (buffer 0) throws an interrupt. The interrupt routine starts the copy using a DMA.
  | If it is not possible to start an asynchronous copy, the copy must be performed in the MicroUI drawing routine, at the beginning of the next step.
  | Note that the copy is partial: only the parts that have changed need to be copied, lowering the CPU load.

.. figure:: images/switch-step3.*
   :alt: Step 3: Copy
   :width: 400px
   :align: center

- | *Step 4:* Synchronisation
  | Waits until the copy routine has finished the full copy.
  | If the copy has not been done asynchronously, the copy must start after the display has finished the switch. It is a blocking copy because the next drawing operation has to wait until this copy is done.

- | *Step 5:* Next draw operation
  | Same behavior as step 1 with buffers reversed.

.. figure:: images/switch-step4.*
   :alt: Step 5: Next draw operation
   :width: 400px
   :align: center


.. _copyBufferMode:

Copy
----

The copy mode is a double-buffered mode where the back buffer is in RAM and has a fixed address. To update the display, data is sent to the display buffer. This can be done either by a memory copy or by sending
bytes using a bus, such as SPI or I2C.

Synchronization steps are described :ref:`below <table_copyModeSyncSteps>`.

.. _table_copyModeSyncSteps:

- | *Step 1:* Drawing 
  | MicroUI is drawing in the back buffer and the display is reading its content from the display buffer.

.. image:: images/copy-step1.*
   :width: 400px
   :align: center

- | *Step 2:* Copy 
  | The drawing is done. A copy from the back buffer to the display buffer is triggered. 
  | Note that the implementation of the copy operation may be done asynchronously – it is recommended to wait until the display "hardware component" has finished a full buffer read to avoid flickering. At the implementation level, the copy may be done by a DMA, a dedicated RTOS task, interrupt, etc.

.. image:: images/copy-step2.*
   :width: 400px
   :align: center

- | *Step 3:*  Synchronization
  | The next drawing operation waits until the copy is complete.

.. image:: images/copy-step3.*
   :width: 400px
   :align: center

.. _directBufferMode:

Direct
------

The direct mode is a single-buffered mode where the same memory area is used for the back buffer and the display buffer (:ref:`See illustration below <fig_directMode>`). Use of the direct mode is likely to
result in "noisy" rendering and flickering, but saves one buffer in runtime memory.

.. _fig_directMode:
.. figure:: images/direct.*
   :alt: Display Direct Mode
   :width: 270px
   :align: center

.. _section_display_partial_buffer:

Partial Buffer
==============

In the case where RAM usage is not a constraint, the graphics buffer is sized to store all the pixel data of the screen.
However, when the RAM available on the device is very limited, a partial buffer can be used instead.
In that case, the buffer is smaller and can only store a part of the screen (one third for example).

When this technique is used, the application draws in the partial buffer.
To flush the drawings, the content of the partial buffer is copied to the display (to its internal memory or to a complete buffer from which the display reads).

If the display does not have its own internal memory and if the device does not have enough RAM to allocate a complete buffer, then it is not possible to use a partial buffer. In that case, only the *Direct* buffer mode can be used.

Workflow
--------

A partial buffer of the desired size has to be allocated in RAM.
If the display does not have its own internal memory, a complete buffer also has to be allocated in RAM, and the display has to be configured to read from the complete buffer.

The implementation should follow these steps:

1. First, the application draws in the partial buffer.
2. Then, to flush the drawings on the screen, the data of the partial buffer is sent to the display (either copied to its internal memory or to the complete buffer in RAM).
3. Finally, a synchronization is required before starting the next drawing operation.

Dual Partial Buffer
-------------------

A second partial buffer can be used to avoid the synchronization delay before between two drawing cycles.
While one of the two partial buffers is being copied to the display, the application can start drawing in the second partial buffer.

This technique is interesting when the copy time is long. The downside is that it requires more RAM or to reduce the size of the partial buffers.

Using a dual partial buffer has no impact on the application code.

Application Limitations
-----------------------

Using a partial buffer rather than a complete buffer may require adapting the code of the application, since rendering a graphical element may require multiple passes. If the application uses MWT, a :ref:`custom render policy <section_render_policy>` has to be used.

Besides, the `GraphicsContext.readPixel() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html#readPixel-int-int->`_
and the `GraphicsContext.readPixels() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html#readPixels-int:A-int-int-int-int-int-int->`_ APIs
can not be used on the graphics context of the display in partial buffer mode.
Indeed, we cannot rely on the current content of the back buffer as it doesn't contain what is seen on the screen.

Likewise, the `Painter.drawDisplayRegion() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Painter.html>`_ API can not be used in partial buffer mode.
Indeed, this API reads the content of the back buffer in order to draw a region of the display.
Instead of relying on the drawings which were performed previously, this API should be avoided and the drawings should be performed again.

Using a partial buffer can have a significant impact on animation performance. Refer to :ref:`section_animations` for more information on the development of animations in an application.

Implementation Example
----------------------

The `partial buffer demo <https://github.com/MicroEJ/Demo-PartialBuffer>`__ provides an example of partial buffer implementation. This example explains how to implement partial buffer support in the BSP and how to use it in an application.

.. _section_display_layout_byte:

Byte Layout
===========

This chapter concerns only display with a number of bits-per-pixel (BPP) smaller than 8. For this kind of display, a byte contains several pixels and the Graphics Engine allows to customize how to organize the pixels in a
byte.

Two layouts are available:

-  line: The byte contains several consecutive pixels on same line. When the end of line is reached, a padding is added in order to start a new line with a new byte.
-  column: The byte contains several consecutive pixels on same column. When the end of column is reached, a padding is added in order to start a new column with a new byte.

When installing the Display module, a property ``byteLayout`` is required to specify the kind of pixels representation (see :ref:`section_display_installation`).

.. table:: Byte Layout: line

   +-------+-------+-------+-------+-------+-------+-------+-------+-------+
   | BPP   | MSB   |       |       |       |       |       |       | LSB   |
   +=======+=======+=======+=======+=======+=======+=======+=======+=======+
   | 4     | pixel                         | pixel                         |
   |       | 1                             | 0                             |
   +-------+---------------+---------------+---------------+---------------+
   | 2     | pixel         | pixel         | pixel         | pixel         |
   |       | 3             | 2             | 1             | 0             |
   +-------+-------+-------+-------+-------+-------+-------+-------+-------+
   | 1     | pixel | pixel | pixel | pixel | pixel | pixel | pixel | pixel |
   |       | 7     | 6     | 5     | 4     | 3     | 2     | 1     | 0     |
   +-------+-------+-------+-------+-------+-------+-------+-------+-------+

.. table:: Byte Layout: column

   +---------+-------------------+-------------------+-------------------+
   | BPP     | 4                 | 2                 | 1                 |
   +=========+===================+===================+===================+
   | MSB     | pixel 1           | pixel 3           | pixel 7           |
   +---------+                   |                   +-------------------+
   |         |                   |                   | pixel 6           |
   +---------+                   +-------------------+-------------------+
   |         |                   | pixel 2           | pixel 5           |
   +---------+                   |                   +-------------------+
   |         |                   |                   | pixel 4           |
   +---------+-------------------+-------------------+-------------------+
   |         | pixel 0           | pixel 1           | pixel 3           |
   +---------+                   |                   +-------------------+
   |         |                   |                   | pixel 2           |
   +---------+                   +-------------------+-------------------+
   |         |                   | pixel 0           | pixel 1           |
   +---------+                   |                   +-------------------+
   | LSB     |                   |                   | pixel 0           |
   +---------+-------------------+-------------------+-------------------+

.. _section_display_layout_memory:

Memory Layout
=============

For the display with a number of bits-per-pixel (BPP) higher or equal to 8, the Graphics Engine supports the line-by-line memory organization: pixels are laid out from left to right within a line, starting with the top
line. For a display with 16 bits-per-pixel, the pixel at (0,0) is stored at memory address 0, the pixel at (1,0) is stored at address 2, the pixel at (2,0) is stored at address 4, and so on.

.. table:: Memory Layout for BPP >= 8

   +-----+-----------+-----------+-----------+-----------+-----------+
   | BPP | @ + 0     | @ + 1     | @ + 2     | @ + 3     | @ + 4     |
   +=====+===========+===========+===========+===========+===========+
   | 32  | pixel 0   | pixel 0   | pixel 0   | pixel 0   | pixel 1   |
   |     | [7:0]     | [15:8]    | [23:16]   | [31:24]   | [7:0]     |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 24  | pixel 0   | pixel 0   | pixel 0   | pixel 1   | pixel 1   |
   |     | [7:0]     | [15:8]    | [23:16]   | [7:0]     | [15:8]    |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 16  | pixel 0   | pixel 0   | pixel 1   | pixel 1   | pixel 2   |
   |     | [7:0]     | [15:8]    | [7:0]     | [15:8]    | [7:0]     |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 8   | pixel 0   | pixel 1   | pixel 2   | pixel 3   | pixel 4   |
   |     | [7:0]     | [7:0]     | [7:0]     | [7:0]     | [7:0]     |
   +-----+-----------+-----------+-----------+-----------+-----------+

For the display with a number of bits-per-pixel (BPP) lower than 8, the Graphics Engine supports the both memory organizations: line by line (pixels are laid out from left to right within a line, starting with the top line) and column by column (pixels are laid out from top to bottom within a line, starting with the left line). These byte organizations concern until 8 consecutive pixels (see :ref:`section_display_layout_byte`). When installing the Display module, a property ``memoryLayout`` is required to specify the kind of pixels representation (see :ref:`section_display_installation`).

.. table:: Memory Layout 'line' for BPP < 8 and byte layout 'line'

   +-----+-----------+-----------+-----------+-----------+-----------+
   | BPP | @ + 0     | @ + 1     | @ + 2     | @ + 3     | @ + 4     |
   +=====+===========+===========+===========+===========+===========+
   | 4   | (0,0) to  | (2,0) to  | (4,0) to  | (6,0) to  | (8,0) to  |
   |     | (1,0)     | (3,0)     | (5,0)     | (7,0)     | (9,0)     |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 2   | (0,0) to  | (4,0) to  | (8,0) to  | (12,0) to | (16,0) to |
   |     | (3,0)     | (7,0)     | (11,0)    | (15,0)    | (19,0)    |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 1   | (0,0) to  | (8,0) to  | (16,0) to | (24,0) to | (32,0) to |
   |     | (7,0)     | (15,0)    | (23,0)    | (31,0)    | (39,0)    |
   +-----+-----------+-----------+-----------+-----------+-----------+

.. table:: Memory Layout 'line' for BPP < 8 and byte layout 'column'

   +-----+-----------+-----------+-----------+-----------+-----------+
   | BPP | @ + 0     | @ + 1     | @ + 2     | @ + 3     | @ + 4     |
   +=====+===========+===========+===========+===========+===========+
   | 4   | (0,0) to  | (1,0) to  | (2,0) to  | (3,0) to  | (4,0) to  |
   |     | (0,1)     | (1,1)     | (2,1)     | (3,1)     | (4,1)     |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 2   | (0,0) to  | (1,0) to  | (2,0) to  | (3,0) to  | (4,0) to  |
   |     | (0,3)     | (1,3)     | (2,3)     | (3,3)     | (4,3)     |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 1   | (0,0) to  | (1,0) to  | (2,0) to  | (3,0) to  | (4,0) to  |
   |     | (0,7)     | (1,7)     | (2,7)     | (3,7)     | (4,7)     |
   +-----+-----------+-----------+-----------+-----------+-----------+

.. table:: Memory Layout 'column' for BPP < 8 and byte layout 'line'

   +-----+-----------+-----------+-----------+-----------+-----------+
   | BPP | @ + 0     | @ + 1     | @ + 2     | @ + 3     | @ + 4     |
   +=====+===========+===========+===========+===========+===========+
   | 4   | (0,0) to  | (0,1) to  | (0,2) to  | (0,3) to  | (0,4) to  |
   |     | (1,0)     | (1,1)     | (1,2)     | (1,3)     | (1,4)     |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 2   | (0,0) to  | (0,1) to  | (0,2) to  | (0,3) to  | (0,4) to  |
   |     | (3,0)     | (3,1)     | (3,2)     | (3,3)     | (3,4)     |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 1   | (0,0) to  | (0,1) to  | (0,2) to  | (0,3) to  | (0,4) to  |
   |     | (7,0)     | (7,1)     | (7,2)     | (7,3)     | (7,4)     |
   +-----+-----------+-----------+-----------+-----------+-----------+

.. table:: Memory Layout 'column' for BPP < 8 and byte layout 'column'

   +-----+-----------+-----------+-----------+-----------+-----------+
   | BPP | @ + 0     | @ + 1     | @ + 2     | @ + 3     | @ + 4     |
   +=====+===========+===========+===========+===========+===========+
   | 4   | (0,0) to  | (0,2) to  | (0,4) to  | (0,6) to  | (0,8) to  |
   |     | (0,1)     | (0,3)     | (0,5)     | (0,7)     | (0,9)     |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 2   | (0,0) to  | (0,4) to  | (0,8) to  | (0,12) to | (0,16) to |
   |     | (0,3)     | (0,7)     | (0,11)    | (0,15)    | (0,19)    |
   +-----+-----------+-----------+-----------+-----------+-----------+
   | 1   | (0,0) to  | (0,8) to  | (0,16) to | (0,24) to | (0,32) to |
   |     | (0,7)     | (0,15)    | (0,23)    | (0,31)    | (0,39)    |
   +-----+-----------+-----------+-----------+-----------+-----------+

.. _display_pixel_structure:

Pixel Structure
===============

Principle
---------

The Display module provides pre-built display configurations with standard pixel memory layout. The layout of the bits within the pixel may be :ref:`standard<display_pixel_structure_standard>` or :ref:`driver-specific<display_pixel_structure_driver>`. When installing the Display module, a property ``bpp`` is required to specify the kind of pixel representation (see :ref:`section_display_installation`).

.. _display_pixel_structure_standard:

Standard
--------

When the value is one among this list: ``ARGB8888 | RGB888 | RGB565 | ARGB1555 | ARGB4444 | C4 | C2 | C1``, the Display module considers the pixels representation as **standard**. 
All standard representations are internally managed by the Display module, by the :ref:`Front Panel<section_ui_simulation>` and by the :ref:`Image Generator<section_image_generator>`. 
No specific support is required as soon as a MicroEJ Platform is using a standard representation. It can:

* generate at compile-time RAW images in the same format than display pixel format,
* convert at runtime MicroUI 32-bit colors in display pixel format,
* simulate at runtime the display pixel format.

.. note:: The custom implementations of the image generator, low-level APIs, and Front Panel APIs are ignored by the Display module when a standard pixel representation is selected.

According to the chosen format, some color data can be lost or cropped.

-  ARGB8888: the pixel uses 32 bits-per-pixel (alpha[8], red[8],
   green[8] and blue[8]).

   ::

      u32 convertARGB8888toLCDPixel(u32 c){
          return c;
      }

      u32 convertLCDPixeltoARGB8888(u32 c){
          return c;
      }

-  RGB888: the pixel uses 24 bits-per-pixel (alpha[0], red[8], green[8]
   and blue[8]).

   ::

      u32 convertARGB8888toLCDPixel(u32 c){
          return c & 0xffffff;
      }

      u32 convertLCDPixeltoARGB8888(u32 c){
          return 0
                  | 0xff000000
                  | c
                  ;
      }

-  RGB565: the pixel uses 16 bits-per-pixel (alpha[0], red[5], green[6]
   and blue[5]).

   ::

      u32 convertARGB8888toLCDPixel(u32 c){
          return 0
                  | ((c & 0xf80000) >> 8)
                  | ((c & 0x00fc00) >> 5)
                  | ((c & 0x0000f8) >> 3)
                  ;
      }

      u32 convertLCDPixeltoARGB8888(u32 c){
          return 0
                  | 0xff000000
                  | ((c & 0xf800) << 8)
                  | ((c & 0x07e0) << 5)
                  | ((c & 0x001f) << 3)
                  ;
      }

-  ARGB1555: the pixel uses 16 bits-per-pixel (alpha[1], red[5],
   green[5] and blue[5]).

   ::

      u32 convertARGB8888toLCDPixel(u32 c){
          return 0
                  | (((c & 0xff000000) == 0xff000000) ? 0x8000 : 0)
                  | ((c & 0xf80000) >> 9)
                  | ((c & 0x00f800) >> 6)
                  | ((c & 0x0000f8) >> 3)
                  ;
      }

      u32 convertLCDPixeltoARGB8888(u32 c){
          return 0
                  | ((c & 0x8000) == 0x8000 ? 0xff000000 : 0x00000000)
                  | ((c & 0x7c00) << 9)
                  | ((c & 0x03e0) << 6)
                  | ((c & 0x001f) << 3)
                  ;
      }

-  ARGB4444: the pixel uses 16 bits-per-pixel (alpha[4], red[4],
   green[4] and blue[4]).

   ::

      u32 convertARGB8888toLCDPixel(u32 c){
          return 0
                  | ((c & 0xf0000000) >> 16)
                  | ((c & 0x00f00000) >> 12)
                  | ((c & 0x0000f000) >> 8)
                  | ((c & 0x000000f0) >> 4)
                  ;
      }

      u32 convertLCDPixeltoARGB8888(u32 c){
          return 0
                  | ((c & 0xf000) << 16)
                  | ((c & 0xf000) << 12)
                  | ((c & 0x0f00) << 12)
                  | ((c & 0x0f00) << 8)
                  | ((c & 0x00f0) << 8)
                  | ((c & 0x00f0) << 4)
                  | ((c & 0x000f) << 4)
                  | ((c & 0x000f) << 0)
                  ;
      }

-  C4: the pixel uses 4 bits-per-pixel (grayscale[4]).

   ::

      u32 convertARGB8888toLCDPixel(u32 c){
          return (toGrayscale(c) & 0xff) / 0x11;
      }

      u32 convertLCDPixeltoARGB8888(u32 c){
          return 0xff000000 | (c * 0x111111);
      }

-  C2: the pixel uses 2 bits-per-pixel (grayscale[2]).

   ::

      u32 convertARGB8888toLCDPixel(u32 c){
          return (toGrayscale(c) & 0xff) / 0x55;
      }

      u32 convertLCDPixeltoARGB8888(u32 c){
          return 0xff000000 | (c * 0x555555);
      }

-  C1: the pixel uses 1 bit-per-pixel (grayscale[1]).

   ::

      u32 convertARGB8888toLCDPixel(u32 c){
          return (toGrayscale(c) & 0xff) / 0xff;
      }

      u32 convertLCDPixeltoARGB8888(u32 c){
          return 0xff000000 | (c * 0xffffff);
      }

.. _display_pixel_structure_driver:

Driver-Specific
---------------

The Display module considers the pixel representation as **driver-specific** when the value is one among this list: ``1 | 2 | 4 | 8 | 16 | 24 | 32``. 
This mode is often used when the pixel representation is not ``ARGB`` or ``RGB`` but ``BGRA`` or ``BGR`` instead. 
This mode can also be used when the number of bits for a color component (alpha, red, green, or blue) is not standard or when the value does not represent a color but an index in a :ref:`display_lut`.
This mode requires some specific support in the MicroEJ Platform:

* An extension of the image generator is mandatory: see :ref:`section_image_generator_extended` to convert MicroUI's standard 32-bit ARGB colors to display pixel format.
* The Front Panel widget ``Display`` requires an extension to convert the MicroUI 32-bit colors in display pixel format and vice-versa, see :ref:`section_ui_simulation_display`.  
* The driver must implement functions that convert MicroUI's standard 32-bit ARGB colors to display pixel format and vice-versa: see :ref:`colorConversions`.

The following example illustrates the use of specific format BGR565 (the pixel uses 16 bits-per-pixel (alpha[0], red[5], green[6]
and blue[5]):

1. Configure the MicroEJ Platform:

   * Create or open the Platform configuration project file ``display/display.properties``: 

   .. code-block:: java 

      bpp=16

2. Image Generator:
  
  *  Create a project as described :ref:`here<section_image_generator_extended>`.
  *  Create the class ``com.microej.graphicalengine.generator.MicroUIGeneratorExtension`` that extends the class ``com.microej.tool.ui.generator.BufferedImageLoader``.
  *  Fill the method ``convertARGBColorToDisplayColor()``:

  .. code-block:: java

      public class MicroUIGeneratorExtension extends BufferedImageLoader {
        @Override
        public int convertARGBColorToDisplayColor(int color) {
           return ((color & 0xf80000) >> 19) | ((color & 0x00fc00) >> 5) | ((color & 0x0000f8) << 8);
        }
     }
     
  * Configure the Image Generator' service loader: add the file ``/META-INF/services/com.microej.tool.ui.generator.MicroUIRawImageGeneratorExtension``:

  .. code-block:: java
   
      com.microej.graphicalengine.generator.MicroUIGeneratorExtension

  * Build the module (click on the blue button).
  * Copy the generated jar file (``imageGeneratorMyPlatform.jar``) in the MicroEJ Platform configuration project: ``/dropins/tools/``.

2. Simulator (Front Panel):

   *  Create the class ``com.microej.fp.MyDisplayExtension`` that implements the interface ``ej.fp.widget.Display.DisplayExtension``:

   .. code-block:: java

      public class MyDisplayExtension implements DisplayExtension {

         @Override
         public int convertARGBColorToDisplayColor(Display display, int color) {
            return ((color & 0xf80000) >> 19) | ((color & 0x00fc00) >> 5) | ((color & 0x0000f8) << 8);
         }

         @Override
         public int convertDisplayColorToARGBColor(Display display, int color) {
            return ((color & 0x001f) << 19) | ((color & 0x7e00) << 5) | ((color & 0xf800) >> 8) | 0xff000000;
         }

         @Override
         public boolean isColor(Display display) {
            return true;
         }

         @Override
         public int getNumberOfColors(Display display) {
            return 1 << 16;
         }
      }
   
   * Configure the widget ``Display`` in the ``.fp`` file by referencing the display extension:

   .. code-block:: xml

      <ej.fp.widget.Display x="41" y="33" width="320" height="240" extensionClass="com.microej.fp.MyDisplayExtension"/>

3. Build the MicroEJ Platform as usual

4. Update the ``LLUI_DISPLAY`` implementation by adding the following functions:

   .. code-block:: c

      uint32_t LLUI_DISPLAY_IMPL_convertARGBColorToDisplayColor(uint32_t color)
      {
         return ((color & 0xf80000) >> 19) | ((color & 0x00fc00) >> 5) | ((color & 0x0000f8) << 8);
      }
      
      uint32_t LLUI_DISPLAY_IMPL_convertDisplayColorToARGBColor(uint32_t color)
      {
        return ((color & 0x001f) << 19) | ((color & 0x7e00) << 5) | ((color & 0xf800) >> 8) | 0xff000000;
      }

.. _section_display_llapi:

Low Level API
=============

Overview
--------

.. figure:: images/ui_llapi_display.*
   :alt: MicroUI Display Low Level
   :width: 70%
   :align: center

   Display Low Level API

* MicroUI library calls the BSP functions through the Graphics Engine and header file ``LLUI_DISPLAY_impl.h``. 
* Implementation of ``LLUI_DISPLAY_impl.h`` can call Graphics Engine functions through ``LLUI_DISPLAY.h``.
* To perform some drawings, MicroUI uses ``LLUI_PAINTER_impl.h`` functions.
* The :ref:`C module<section_ui_releasenotes_cmodule>` provides a default implementation of the drawing native functions of ``LLUI_PAINTER_impl.h`` and ``LLDW_PAINTER_impl.h``:
  * It implements the synchronization layer, then redirects drawings implementations to ``ui_drawing.h`` and ``dw_drawing.h``
* ``ui_drawing.h`` and ``dw_drawing.h`` are already implemented by built-in software algorithms (library provided by the UI Pack).
* It is possible to implement some of the ``ui_drawing.h`` and ``dw_drawing.h`` functions in the BSP to provide a custom implementation (for instance, a GPU).
  * Custom implementation is still allowed to call software algorithms declared in ``ui_drawing_soft.h`` and ``dw_drawing_soft.h``.

Display Size
------------

The Low-Level APIs distinguish between the display *virtual* size and the display *physical* size (in pixels).

* The display *virtual* size is the size of the area where the drawings are visible. Virtual memory size is: ``lcd_width * lcd_height * bpp / 8``.
* The display *physical* size is the required memory size where the *virtual* area is located. On some devices, the memory width (in pixels) is higher than the virtual width. In this way, the graphics buffer memory size is: ``memory_width * memory_height * bpp / 8``.

.. note:: The *physical* size may not be configured; in that case, the Graphics Engine considers the *virtual* size os *physical* size.

Semaphores
----------

The Graphics Engine requires two binary semaphores to synchronize its internal states. 
These semaphores are reserved for the Graphics Engine. 
The ``LLUI_DISPLAY_impl.h`` implementation is not allowed to use these semaphores to synchronize the function ``LLUI_DISPLAY_IMPL_flush()`` with the display driver (or for any other synchronization actions). 
The implementation must create its semaphores in addition to these dedicated Graphics Engine's semaphores.

The binary semaphores must be configured in a state such that the semaphore must first be *given* before it can be *taken* (this initialization must be performed in ``LLUI_DISPLAY_IMPL_initialize`` function).

Required Low Level API
----------------------

Some four Low Level APIs are required to connect the Graphics Engine on the display driver. The functions are listed in ``LLUI_DISPLAY_impl.h``. 

* ``LLUI_DISPLAY_IMPL_initialize``: The initialization function is called when the application is calling ``MicroUI.start()``. Before this call, the display is useless and don't need to be initialized. This function consists in initializing the LCD driver and in filling the given structure ``LLUI_DISPLAY_SInitData``.  This structure has to contain pointers on the two binary semaphores, the back buffer address (see :ref:`section_display_modes`), the display *virtual* size in pixels (``lcd_width`` and ``lcd_height``) and optionally the display *physical* size in pixels (``memory_width`` and ``memory_height``). 

* ``LLUI_DISPLAY_IMPL_binarySemaphoreTake`` and ``LLUI_DISPLAY_IMPL_binarySemaphoreGive``: Two distinct functions have to be implemented to *take* and *give* a binary semaphore. 

* ``LLUI_DISPLAY_IMPL_flush``: According the display buffer mode (see :ref:`section_display_modes`), the ``flush`` function has to be implemented. This function must not be blocking and not performing the copy directly. Another OS task or a dedicated hardware must be configured to perform the buffer copy. 

Optional Low Level API
----------------------

Several optional Low Level API are available in ``LLUI_DISPLAY_impl.h``. They are already implemented as *weak* functions in the Graphics Engine and return no error. These optional features concern the display backlight and constrast, display characteristics (is colored display, double buffer), colors conversions (see :ref:`display_pixel_structure` and :ref:`display_lut`), etc. Refer to each function comment to have more information about the default behavior.

Painter Low Level API
---------------------

All MicroUI drawings (available in ``Painter`` class) are calling a native function. The MicroUI native drawing functions are listed in ``LLUI_PAINTER_impl.h``. The implementation must take care about a lot of constraints: synchronization between drawings, Graphics Engine notification, MicroUI ``GraphicsContext`` clip and colors, flush dirty area, etc. The principle of implementing a MicroUI drawing function is described in the chapter :ref:`display_drawing_native`. 

An implementation of ``LLUI_PAINTER_impl.h`` is already available on the :ref:`C module<section_ui_releasenotes_cmodule>`. This implementation respects the synchronization between drawings, the Graphics Engine notification, reduce (when possible) the MicroUI ``GraphicsContext`` clip constraints and update (when possible) the flush dirty area. This implementation does not perform the drawings. It only calls the equivalent of drawing available in ``ui_drawing.h``. This allows to simplify how to use a GPU (or a third-party library) to perform a drawing: the ``ui_drawing.h`` implementation has just to take in consideration the  MicroUI ``GraphicsContext`` clip and colors and flush dirty area. Synchronization with the Graphics Engine is already performed.

In addition to the implementation of ``LLUI_PAINTER_impl.h``, an implementation of ``ui_drawing.h`` is already available in Graphics Engine (in *weak* mode). This allows to implement only the functions the GPU is able to perform. For a given drawing, the weak function implementation is calling the equivalent of drawing available in ``ui_drawing_soft.h``. This file lists all drawing functions implemented by the Graphics Engine.

The Graphics Engine implementation of ``ui_drawing_soft.h`` is performing the drawings in software. However some drawings can call another ``ui_drawing.h`` function. For instance ``UI_DRAWING_SOFT_drawHorizontalLine`` is calling ``UI_DRAWING_fillRectangle`` in order to use a GPU if available. If not available, the weak implementation of ``UI_DRAWING_fillRectangle`` is calling ``UI_DRAWING_SOFT_fillRectangle`` and so on.

The BSP implementation is also allowed to call ``ui_drawing_soft.h`` algorithms, one or several times per function to implement. For instance, a GPU may be able to draw an image whose format is RGB565. But if the image format is ARGB1555, BSP implementation can call ``UI_DRAWING_SOFT_drawImage`` function.

Graphics Engine API
--------------------

The Graphics Engine provides a set of functions to interact with the C archive. The functions allow to retrieve some drawing characteristics, synchronize drawings between them, notify the end of flush and drawings, etc. 

The functions are available in ``LLUI_DISPLAY.h``. 

Typical Implementations
=======================

This chapter helps to write some basic ``LLUI_DISPLAY_impl.h`` implementations according the display buffer mode (see :ref:`section_display_modes`).
The pseudo-code calls external function such as ``LCD_DRIVER_xxx`` or ``DMA_DRIVER_xxx`` to symbolize the use of external drivers.

.. note:: The pseudo code don't use the dirty area bounds (xmin, ymax, etc.) to simplify the reading.

Common Functions
----------------

The three functions ``LLUI_DISPLAY_IMPL_initialize``, ``LLUI_DISPLAY_IMPL_binarySemaphoreTake`` and ``LLUI_DISPLAY_IMPL_binarySemaphoreGive`` are often the same.
The following example shows an implementation over FreeRTOS.

.. code:: c
 
   void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data)
   {
      // create the Graphics Engine's binary semaphores
      g_sem_copyLaunch = xSemaphoreCreateBinary();
      g_sem_taskTest = xSemaphoreCreateBinary();

      // fill the LLUI_DISPLAY_SInitData structure
      init_data->binary_semaphore_0 = (void*)xSemaphoreCreateBinary();
      init_data->binary_semaphore_1 = (void*)xSemaphoreCreateBinary();
      init_data->lcd_width = LCD_DRIVER_get_width();
      init_data->lcd_height = LCD_DRIVER_get_height();
   }

   void LLUI_DISPLAY_IMPL_binarySemaphoreTake(void* sem)
   {
      xSemaphoreTake((xSemaphoreHandle)sem, portMAX_DELAY);
   }

   void LLUI_DISPLAY_IMPL_binarySemaphoreGive(void* sem, bool under_isr)
   {
      if (under_isr)
      {
         portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
         xSemaphoreGiveFromISR((xSemaphoreHandle)sem, &xHigherPriorityTaskWoken);
         if(xHigherPriorityTaskWoken != pdFALSE )
         {
            // Force a context switch here.
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
         }
      }
      else
      {
         xSemaphoreGive((xSemaphoreHandle)sem);
      }
   }

Direct Mode
-----------

This mode considers the application and the LCD driver share the same buffer. 
In other words, all drawings made by the application are immediately shown on the display.
This particular case is the easiest to write because the ``flush()`` stays empty:

.. code:: c

   void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data)
   {
      // [...]

      // use same buffer between the LCD driver and the Graphics Engine
      LCD_DRIVER_initialize(lcd_buffer);
      init_data->back_buffer_address = lcd_buffer;
   }

   uint8_t* LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t* srcAddr, uint32_t xmin, uint32_t ymin, uint32_t xmax, uint32_t ymax)
   {
      // nothing to send to the LCD, just have to return the same buffer address
      return srcAddr;
   }

Serial Display
--------------

A display connected to the CPU through a serial bus (I2C, SPI, etc.) requires the :ref:`copy<copyBufferMode>` mode: the application uses a buffer to perform its drawings and the buffer's content has to be sent to the display when the Graphics Engine is calling the ``flush()`` function.

The specification of the ``flush()`` function is to be **not** blocker (atomic). 
Its aim is to prepare / configure the serial bus and data to send and then, to start the asynchronous copy (data sent).
The ``flush()`` function has to return as soon as possible.

Before executing the next application drawing after a flush, the Graphics Engine automatically waits the end of the serial data sent: the drawing buffer (currently used by the serial device) is not updated until the end of data sent.
The serial device driver has the responsibility to unlock the Graphics Engine by calling the function ``LLUI_DISPLAY_flushDone()`` at the end of the copy.

There are two use cases:

**Hardware**

The serial data sent is performed in hardware. 
In that case, the serial driver must configure an interrupt to be notified about the end of the copy.

.. code:: c

   void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data)
   {
      // [...]

      LCD_DRIVER_initialize();
      init_data->back_buffer_address = back_buffer;

      // initialize the serial driver & device: GPIO, etc.
      SERIAL_DRIVER_initialize();
   }

   uint8_t* LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t* srcAddr, uint32_t xmin, uint32_t ymin, uint32_t xmax, uint32_t ymax)
   {
      // configure the serial device to send n bytes
      // srcAddr == back_buffer
      SERIAL_DRIVER_prepare_sent(srcAddr, LCD_WIDTH * LCD_HEIGHT * LCD_BPP / 8);

      // configure the "end of copy" interrupt
      SERIAL_DRIVER_enable_interrupt(END_OF_COPY);

      // start the copy
      SERIAL_DRIVER_start();

      // return the same buffer address for next drawings
      return srcAddr;
   }

   void SERIAL_DEVICE_IRQHandler(void)
   {
      SERIAL_DRIVER_clear_interrupt();
      SERIAL_DRIVER_disable_interrupt(END_OF_COPY);

      // end of copy, unlock the Graphics Engine
      LLUI_DISPLAY_flushDone(true); // true: called under interrupt
   }

**Software**

The copy (serial data sent) cannot be performed in hardware or require a software loop to send all data.
This sent must not be performed in the ``flush()`` function. 
A dedicated OS task is required to perform this sent.

.. code:: c

   static void* _copy_task_semaphore;

   static void _task_flush(void *p_arg)
   {
      while(1)
      {
         // wait until the Graphics Engine gives the order to copy
         LLUI_DISPLAY_IMPL_binarySemaphoreTake(_copy_task_semaphore);

         // send data
         SERIAL_DRIVER_send_data(back_buffer, LCD_WIDTH * LCD_HEIGHT * LCD_BPP / 8);

         // end of copy, unlock the Graphics Engine
         LLUI_DISPLAY_flushDone(false); // true: called outside interrupt
      }
   }

   void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data)
   {
      // [...]

      LCD_DRIVER_initialize();
      init_data->back_buffer_address = back_buffer;

      // create a "flush" task and a dedicated semaphore
      _copy_task_semaphore = (void*)xSemaphoreCreateBinary();
      xTaskCreate(_task_flush, "FlushTask", 1024, NULL, 12, NULL);
   }

   uint8_t* LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t* srcAddr, uint32_t xmin, uint32_t ymin, uint32_t xmax, uint32_t ymax)
   {
      // unlock the copy task
      LLUI_DISPLAY_IMPL_binarySemaphoreGive(_copy_task_semaphore, false);

      // return the same buffer address for next drawings
      return srcAddr;
   }

Parallel Display: Copy Mode (Tearing Disabled)
----------------------------------------------

.. note:: This mode should synchronize the copy buffer process with the LCD tearing signal. However,  this notion is sometimes not available. This chapter describes the copy buffer process without using the tearing signal (see :ref:`next chapter<section_lluidisplay_parallel_tearing>`).

This kind of configuration requires two buffers in RAM. 
The first buffer is used by the application (back buffer) and the second buffer is used by the LCD controller to send data to the display (frame buffer).

The content of the frame buffer must be updated with the content of the back buffer when the Graphics Engine is calling the ``flush()`` function.

The specification of the ``flush()`` function is to be **not** blocker (atomic). 
Its aim is to prepare / configure the copy buffer process and then, to start the asynchronous copy.
The ``flush()`` function has to return as soon as possible.

Before executing the next application drawing after a flush, the Graphics Engine automatically waits the end of the copy buffer process: the back buffer (currently used by the copy buffer process) is not updated until the end of the copy.
The copy driver has the responsibility to unlock the Graphics Engine by calling the function ``LLUI_DISPLAY_flushDone()`` at the end of the copy.

There are two use cases:

**Hardware**

The copy buffer process is performed in hardware (DMA). 
In that case, the DMA driver must configure an interrupt to be notified about the end of the copy.

.. code:: c

   void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data)
   {
      // [...]

      // use two distinct buffers between the LCD driver and the Graphics Engine
      LCD_DRIVER_initialize(frame_buffer);
      init_data->back_buffer_address = back_buffer;

      // initialize the DMA driver: GPIO, etc.
      DMA_DRIVER_initialize();
   }

   uint8_t* LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t* srcAddr, uint32_t xmin, uint32_t ymin, uint32_t xmax, uint32_t ymax)
   {
      // configure the DMA to send n bytes
      // srcAddr == back_buffer
      DMA_DRIVER_prepare_sent(frame_buffer, srcAddr, LCD_WIDTH * LCD_HEIGHT * LCD_BPP / 8); // dest / src / size

      // configure the "end of copy" interrupt
      DMA_DRIVER_enable_interrupt(END_OF_COPY);

      // start the copy
      DMA_DRIVER_start();

      // return the same buffer address for next drawings
      return srcAddr;
   }

   void DMA_IRQHandler(void)
   {
      DMA_DRIVER_clear_interrupt();
      DMA_DRIVER_disable_interrupt(END_OF_COPY);

      // end of copy, unlock the Graphics Engine
      LLUI_DISPLAY_flushDone(true); // true: called under interrupt
   }

**Software**

The copy buffer process cannot be performed in hardware or require a software loop to send all data (DMA linked list).
This copy buffer process must not be performed in the ``flush()`` function. 
A dedicated OS task is required to perform this copy.

.. code:: c

   static void* _copy_task_semaphore;

   static void _task_flush(void *p_arg)
   {
      while(1)
      {
         int32_t size = LCD_WIDTH * LCD_HEIGHT * LCD_BPP / 8;
         uint8_t* dest = frame_buffer;
         uint8_t* src = back_buffer;

         // wait until the Graphics Engine gives the order to copy
         LLUI_DISPLAY_IMPL_binarySemaphoreTake(_copy_task_semaphore);

         // copy data
         while(size)
         {
            int32_t s = min(DMA_MAX_SIZE, size);
            DMA_DRIVER_send_data(dest, src, s); // dest / src / size
            dest += s;
            src += s;
            size -= s;
         }

         // end of copy, unlock the Graphics Engine
         LLUI_DISPLAY_flushDone(false); // true: called outside interrupt
      }
   }

   void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data)
   {
      // [...]

      // use two distinct buffers between the LCD driver and the Graphics Engine
      LCD_DRIVER_initialize(frame_buffer);
      init_data->back_buffer_address = back_buffer;

      // create a "flush" task and a dedicated semaphore
      _copy_task_semaphore = (void*)xSemaphoreCreateBinary();
      xTaskCreate(_task_flush, "FlushTask", 1024, NULL, 12, NULL);
   }

   uint8_t* LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t* srcAddr, uint32_t xmin, uint32_t ymin, uint32_t xmax, uint32_t ymax)
   {
      // unlock the copy task
      LLUI_DISPLAY_IMPL_binarySemaphoreGive(_copy_task_semaphore, false);

      // return the same buffer address for next drawings
      return srcAddr;
   }  


.. _section_lluidisplay_parallel_tearing:

Parallel Display: Copy Mode (Tearing Enabled)
----------------------------------------------

The configuration is the same than previous chapter but it uses the LCD tearing signal to synchronize the LCD refresh rate with the copy buffer process.

The copy buffer process should not start during the call of ``flush()`` but should wait the next tearing signal to start the copy.

There are two use cases:

**Hardware**

.. code:: c

   static uint8_t _start_DMA;

   void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data)
   {
      // [...]

      // use two distinct buffers between the LCD driver and the Graphics Engine
      LCD_DRIVER_initialize(frame_buffer);
      init_data->back_buffer_address = back_buffer;

      // enable the tearing interrupt
      _start_DMA = 0;
      TE_enable_interrupt();

      // initialize the DMA driver: GPIO, etc.
      DMA_DRIVER_initialize();
   }

   uint8_t* LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t* srcAddr, uint32_t xmin, uint32_t ymin, uint32_t xmax, uint32_t ymax)
   {
      // configure the DMA to send n bytes
      // srcAddr == back_buffer
      DMA_DRIVER_prepare_sent(frame_buffer, srcAddr, LCD_WIDTH * LCD_HEIGHT * LCD_BPP / 8); // dest / src / size

      // configure the "end of copy" interrupt
      DMA_DRIVER_enable_interrupt(END_OF_COPY);

      // unlock the job of the tearing interrupt
      _start_DMA = 1;

      // return the same buffer address for next drawings
      return srcAddr;
   }

   void TE_IRQHandler(void)
   {
      TE_clear_interrupt();

      if (_start_DMA)
      {
         _start_DMA = 0;

         // start the copy
         DMA_DRIVER_start();
      }
   }

   void DMA_IRQHandler(void)
   {
      DMA_DRIVER_clear_interrupt();
      DMA_DRIVER_disable_interrupt(END_OF_COPY);

      // end of copy, unlock the Graphics Engine
      LLUI_DISPLAY_flushDone(true); // true: called under interrupt
   }

**Software**

.. code:: c

   static void* _copy_task_semaphore;
   static uint8_t _start_copy;

   static void _task_flush(void *p_arg)
   {
      while(1)
      {
         // wait until the Graphics Engine gives the order to copy
         LLUI_DISPLAY_IMPL_binarySemaphoreTake(_copy_task_semaphore);

         int32_t size = LCD_WIDTH * LCD_HEIGHT * LCD_BPP / 8;
         uint8_t* dest = frame_buffer;
         uint8_t* src = back_buffer;

         // copy data
         while(size)
         {
            int32_t s = min(DMA_MAX_SIZE, size);
            DMA_DRIVER_send_data(dest, src, s); // dest / src / size
            dest += s;
            src += s;
            size -= s;
         }

         // end of copy, unlock the Graphics Engine
         LLUI_DISPLAY_flushDone(false); // true: called outside interrupt
      }
   }

   void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data)
   {
      // [...]

      // use two distinct buffers between the LCD driver and the Graphics Engine
      LCD_DRIVER_initialize(frame_buffer);
      init_data->back_buffer_address = back_buffer;

      // create a "flush" task and a dedicated semaphore
      _copy_task_semaphore = (void*)xSemaphoreCreateBinary();
      xTaskCreate(_task_flush, "FlushTask", 1024, NULL, 12, NULL);

      // enable the tearing interrupt
      _start_copy = 0;
      TE_enable_interrupt();
   }

   uint8_t* LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t* srcAddr, uint32_t xmin, uint32_t ymin, uint32_t xmax, uint32_t ymax)
   {
      // unlock the job of the tearing interrupt
      _start_copy = 1;

      // return the same buffer address for next drawings
      return srcAddr;
   }

   void TE_IRQHandler(void)
   {
      TE_clear_interrupt();

      if (_start_copy)
      {
         _start_copy = 0;

         // unlock the copy task
         LLUI_DISPLAY_IMPL_binarySemaphoreGive(_copy_task_semaphore, true);
      }
   }  

Parallel Display: Switch Mode
-----------------------------

This kind of configuration requires two buffers in RAM. 
The first buffer is used by the application (buffer A) and the second buffer is used by the LCD controller to send data to the display (buffer B).

The LCD controller is reconfigured to use the buffer A when the Graphics Engine is calling the ``flush()`` function.
A copy buffer process is required to restore the content of the application buffer (buffer B after the flush).

Before executing the next application drawing after a flush, the Graphics Engine automatically waits the end of the copy buffer process: the buffer B (currently used by the LDC controller or by the copy buffer process) is not updated until the end of the copy.
The copy driver has the responsibility to unlock the Graphics Engine by calling the function ``LLUI_DISPLAY_flushDone()`` at the end of the copy.

There are two use cases:

**Hardware**

The copy buffer process is performed in hardware (DMA). 
In that case, the DMA driver must configure an interrupt to be notified about the end of the copy.

.. code:: c

   static uint8_t* buffer_A;
   static uint8_t* buffer_B;

   void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data)
   {
      // [...]

      // use two distinct buffers between the LCD driver and the Graphics Engine
      LCD_DRIVER_initialize(buffer_B);
      init_data->back_buffer_address = buffer_A;

      // initialize the DMA driver: GPIO, etc.
      DMA_DRIVER_initialize();
   }

   uint8_t* LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t* srcAddr, uint32_t xmin, uint32_t ymin, uint32_t xmax, uint32_t ymax)
   {
      // the copy destination is the future back buffer (current frame buffer)
      uint8_t* dest = LCDC_get_address();

      // configure the DMA to send n bytes
      DMA_DRIVER_prepare_sent(dest, srcAddr, LCD_WIDTH * LCD_HEIGHT * LCD_BPP / 8); // dest / src / size

      // configure the "end of copy" interrupt
      DMA_DRIVER_enable_interrupt(END_OF_COPY);

      // change the LCDC address (executed at next LCD refresh loop)
      LCDC_set_address(srcAddr);

      // return the new buffer address for next drawings
      return dest;
   }

   // only called when reloading a new LCDC address
   void LCDC_RELOAD_IRQHandler(void)
   {
      LCDC_DRIVER_clear_interrupt();

      // start the copy
      DMA_DRIVER_start();
   }

   void DMA_IRQHandler(void)
   {
      DMA_DRIVER_clear_interrupt();
      DMA_DRIVER_disable_interrupt(END_OF_COPY);

      // end of copy, unlock the Graphics Engine
      LLUI_DISPLAY_flushDone(true); // true: called under interrupt
   }


**Software**

The copy buffer process cannot be performed in hardware or require a software loop to send all data (DMA linked list).
This copy buffer process must not be performed in the ``flush()`` function. 
A dedicated OS task is required to perform this copy.

.. code:: c

   static void* _copy_task_semaphore;
   static uint8_t* buffer_A;
   static uint8_t* buffer_B;

   static void _task_flush(void *p_arg)
   {
      while(1)
      {
         // wait until the Graphics Engine gives the order to copy
         LLUI_DISPLAY_IMPL_binarySemaphoreTake(_copy_task_semaphore);

         int32_t size = LCD_WIDTH * LCD_HEIGHT * LCD_BPP / 8;
         uint8_t* src = LCDC_get_address();
         uint8_t* dest = src == buffer_A ? buffer_B : buffer_A;

         // copy data
         while(size)
         {
            int32_t s = min(DMA_MAX_SIZE, size);
            DMA_DRIVER_send_data(dest, src, s);
            src += s;
            dest += s;
            size -= s;
         }

         // end of copy, unlock the Graphics Engine
         LLUI_DISPLAY_flushDone(false); // true: called outside interrupt
      }
   }

   void LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData* init_data)
   {
      // [...]

      // use two distinct buffers between the LCD driver and the Graphics Engine
      LCD_DRIVER_initialize(buffer_B);
      init_data->back_buffer_address = buffer_A;

      // initialize the DMA driver: GPIO, etc.
      DMA_DRIVER_initialize();

      // create a "flush" task and a dedicated semaphore
      _copy_task_semaphore = (void*)xSemaphoreCreateBinary();
      xTaskCreate(_task_flush, "FlushTask", 1024, NULL, 12, NULL);
   }

   uint8_t* LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext* gc, uint8_t* srcAddr, uint32_t xmin, uint32_t ymin, uint32_t xmax, uint32_t ymax)
   {
      // the copy destination is the future back buffer (current frame buffer)
      uint8_t* dest = LCDC_get_address();

      // change the LCDC address (executed at next LCD refresh loop)
      LCDC_set_address(srcAddr);

      // return the new buffer address for next drawings
      return dest;
   }

   // only called when reloading a new LCDC address
   void LCDC_RELOAD_IRQHandler(void)
   {
      LCDC_DRIVER_clear_interrupt();

      // unlock the copy task
      LLUI_DISPLAY_IMPL_binarySemaphoreGive(_copy_task_semaphore, true);
   }

.. _display_drawing_native:

Drawing Native
==============

As explained before, MicroUI implementation provides a dedicated header file which lists all MicroUI Painter drawings native function. The implementation of these functions has to respect several rules to not corrupt the MicroUI execution (flickering, memory corruption, unknown behavior, etc.). These rules are already respected in the default Abstraction Layer implementation modules available on the :ref:`C module<section_ui_releasenotes_cmodule>`. In addition, MicroUI allows to add some custom drawings. The implementation of MicroUI Painter native drawings should be used as model to implement the custom drawings.

All native functions must have a ``MICROUI_GraphicsContext*`` as parameter (often first parameter). This identifies the destination target: the MicroUI `GraphicsContext <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html>`_. This target is retrieved in application calling the method ``GraphicsContext.getSNIContext()``. This method returns a byte array which is directly mapped on the ``MICROUI_GraphicsContext`` structure in MicroUI native drawing function declaration.
 
A graphics context holds a clip and the drawer is not allowed to perform a drawing outside this clip (otherwise the behavior is unknown). Note the bottom-right coordinates might be smaller than top-left (in x and/or y) when the clip width and/or height is null. The clip may be disabled (when the current drawing fits the clip); this allows to reduce runtime. See ``LLUI_DISPLAY_isClipEnabled()``.

.. note::

   Several clip functions are available in ``LLUI_DISPLAY.h`` to check if a drawing fits the clip.

The Graphics Engine requires the synchronization between the drawings. To do that, it requires a call to ``LLUI_DISPLAY_requestDrawing`` at the beginning of native function implementation. This function takes as parameter the graphics context and the pointer on the native function itself. This pointer must be casted in a ``SNI_callback``. 

The drawing function must update the next `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ area (dirty area). If not performed, the next call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ will not call ``LLUI_DISPLAY_IMPL_flush()`` function.
 
The native function implementation pattern is:

.. code:: c

   void Java_com_mycompany_MyPainterClass_myDrawingNative(MICROUI_GraphicsContext* gc, ...)
   {
      // tell to the Graphics Engine if drawing can be performed
      if (LLUI_DISPLAY_requestDrawing(gc, (SNI_callback)&Java_com_mycompany_MyPainterClass_myDrawingNative))
      {
         DRAWING_Status status;

         // perform the drawings (respecting clip if not disabled)
         [...]

         // update new flush dirty area
         LLUI_DISPLAY_setDrawingLimits(gc, ...);

         // set drawing status
         LLUI_DISPLAY_setDrawingStatus(DRAWING_DONE); // or DRAWING_RUNNING;
      }
      // else: refused drawing
   }

Display Synchronization
=======================

.. note:: This chapter is mainly helpful when the :ref:`copy<copyBufferMode>` mode is used: the aim consists of synchronizing the update of the LCD frame buffer with the LCD refresh rate.

Overview
--------

The Graphics Engine is designed to be synchronized with the display refresh rate by defining some points in the rendering timeline. It is optional; however it is mainly recommanded.  This chapter explains why to use display tearing signal and its consequences. Some chronograms describe several use cases: with and without display tearing signal, long drawings, long flush time, etc. Times are in milliseconds. To simplify chronograms views, the display refresh rate is every 16ms (62.5Hz). 

Captions definition:

* UI: It is the UI task which performs the drawings in the back buffer. At the end of the drawings, the examples consider that the UI thread calls `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ 1 millisecond after the end of the drawings. At this moment, a flush can start (the call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ is symbolized by a simple `peak` in chronograms).
* Flush: In :ref:`copy<copyBufferMode>` mode, it is the time to transfer the content of back buffer to display buffer. In :ref:`switch<switchBufferMode>` mode, it is the time to swap back and display buffers (often instantaneous) and the time to recopy the content of new display buffer to new back buffer. During this time, the back buffer is `in use` and UI task has to wait the end of copy before starting a new drawing. 
* Tearing: The peaks show the tearing signals.
* Rendering frequency: the frequency between the start of a drawing to the end of flush.

Tearing Signal
--------------

In this example, the drawing time is 7ms, the time between the end of drawing and the call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ is 1ms and the flush time is 6ms. So the expected rendering frequency is 7 + 1 + 6 = 14ms (71.4Hz). Flush starts just after the call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ and the next drawing starts just after the end of flush. Tearing signal is not taken in consideration. By consequence the display content is refreshed during the display refresh time. The content can be corrupted: flickering, glitches, etc. The rendering frequency is faster than display refresh rate.

.. figure:: images/uiDisplaySync01.*
   :width: 100%

In this example, the times are identical to previous example. The tearing signal is used to start the flush in respecting the display refreshing time. The rendering frequency becomes smaller: it is cadenced on the tearing signal, every 16ms (62.5Hz). During 2ms, the CPU can schedule other tasks or goes in idle mode. The rendering frequency is equal to display refresh rate.

.. figure:: images/uiDisplaySync02.*
   :width: 100%

In this example, the drawing time is 14ms, the time between the end of drawing and the call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ is 1ms and the flush time is 6ms. So the expected rendering frequency is 14 + 1 + 6 = 21ms (47.6Hz). Flush starts just after the call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ and the next drawing starts just after the end of flush. Tearing signal is not taken in consideration. 

.. figure:: images/uiDisplaySync03.*
   :width: 100%
 
In this example, the times are identical to previous example. The tearing signal is used to start the flush in respecting the display refreshing time. The drawing time + flush time is higher than display tearing signal period. So the flush cannot start at every tearing peak: it is cadenced on two tearing signals, every 32ms (31.2Hz). During 11ms, the CPU can schedule other tasks or goes in idle mode. The rendering frequency is equal to display refresh rate divided by two.

.. figure:: images/uiDisplaySync04.*
   :width: 100%

Additional Buffer 
-----------------

Some devices take a lot of time to send back buffer content to display buffer. The following examples demonstrate the consequence on rendering frequency. The use of an additional buffer optimizes this frequency, however it uses a lot of RAM memory.

In this example, the drawing time is 7ms, the time between the end of drawing and the call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ is 1ms and the flush time is 12ms. So the expected rendering frequency is 7 + 1 + 12 = 20ms (50Hz). Flush starts just after the call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ and the next drawing starts just after the end of flush. Tearing signal is not taken in consideration. The rendering frequency is cadenced on drawing time + flush time.

.. figure:: images/uiDisplaySync05.*
   :width: 100%

As mentionned above, the idea is to use two back buffers. First, UI task is drawing in back buffer ``A``. Just after the call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_, the flush can start. At same moment, the content of back buffer ``A`` is copied in back buffer ``B`` (use a DMA, copy time is 1ms). During the flush time (copy of back buffer ``A`` to display buffer), the back buffer ``B`` can be used by UI task to continue the drawings. When the drawings in back buffer ``B`` are done (and after call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_), the DMA copy of back buffer ``B`` to back buffer ``A`` cannot start: the copy can only start when the flush is fully done because the flush is using the back buffer ``A``. As soon as the flush is done, a new flush (and DMA copy) can start. The rendering frequency is cadenced on flush time, ie 12ms (83.3Hz).

.. figure:: images/uiDisplaySync06.*
   :width: 100%

The previous example doesn't take in consideration the display tearing signal. With tearing signal and only one back buffer, the frequency is cadenced on two tearing signals (see previous chapter). With two back buffers, the frequency is now cadenced on only one tearing signal, despite the long flush time. 

.. figure:: images/uiDisplaySync07.*
   :width: 100%

Time Sum-up
-----------

The following table resumes the previous examples times:

* It consider the display frequency is 62.5Hz (16ms). 
* *Drawing time* is the time let to the application to perform its drawings and call `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_. In our examples, the time between the last drawing and the call to `Display.flush() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush-->`_ is 1ms.
* *FPS* and *CPU load* are calculated from examples times.
* *Max drawing time* is the maximum time let to the application to perform its drawings, without overlapping next display tearing signal (when tearing is enabled). 

+----------+-------------+--------------------+------------------+---------------------+-----------+---------------+------------------------+
|  Tearing |  Nb buffers |  Drawing time (ms) |  Flush time (ms) |  DMA copy time (ms) |  FPS (Hz) |  CPU load (%) |  Max drawing time (ms) |
+==========+=============+====================+==================+=====================+===========+===============+========================+
|     no   |       1     |         7+1        |         6        |                     |    71.4   |      57.1     |                        |
+----------+-------------+--------------------+------------------+---------------------+-----------+---------------+------------------------+
|    yes   |       1     |         7+1        |         6        |                     |    62.5   |       50      |            10          |
+----------+-------------+--------------------+------------------+---------------------+-----------+---------------+------------------------+
|     no   |       1     |         14+1       |         6        |                     |    47.6   |      71.4     |                        |
+----------+-------------+--------------------+------------------+---------------------+-----------+---------------+------------------------+
|    yes   |       1     |         14+1       |         6        |                     |    31.2   |      46.9     |            20          |
+----------+-------------+--------------------+------------------+---------------------+-----------+---------------+------------------------+
|     no   |       1     |         7+1        |         12       |                     |     50    |       40      |                        |
+----------+-------------+--------------------+------------------+---------------------+-----------+---------------+------------------------+
|    yes   |       1     |         7+1        |         12       |                     |    31.2   |       25      |            8           |
+----------+-------------+--------------------+------------------+---------------------+-----------+---------------+------------------------+
|     no   |       2     |         7+1        |         12       |           1         |    83.3   |      66.7     |                        |
+----------+-------------+--------------------+------------------+---------------------+-----------+---------------+------------------------+
|    yes   |       2     |         7+1        |         12       |           1         |    62.5   |       50      |            11          |
+----------+-------------+--------------------+------------------+---------------------+-----------+---------------+------------------------+

GPU Synchronization
===================

When a GPU is used to perform a drawing, the caller (MicroUI painter native method) returns immediately. This allows the application to perform other operations during the GPU rendering. However, as soon as the application is trying to perform another drawing, the previous drawing made by the GPU must be done. The Graphics Engine is designed to be synchronized with the GPU asynchronous drawings by defining some points in the rendering timeline. It is not optional: MicroUI considers a drawing is fully done when it starts a new one. The end of GPU drawing must notify the Graphics Engine calling ``LLUI_DISPLAY_drawingDone()``.

Antialiasing
============

Fonts
-----

The antialiasing mode for the fonts concerns only the fonts with more than 1 bit per pixel (see :ref:`section_fontgen`).

Background Color
----------------

For each pixel to draw, the antialiasing process blends the foreground color with a background color. This background color can be specified or not by the application:

- *specified*: The background color is fixed by the application  (`GraphicsContext.setBackgroundColor() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html#setBackgroundColor-int->`_).
-  *not specified*: The background color is the original color of the destination pixel (a "read pixel" operation is performed for each pixel).

.. _display_lut:

CLUT
====

The Display module allows to target display which uses a pixel indirection table (CLUT). This kind of display are considered as generic but not standard (see :ref:`display_pixel_structure`). It consists to store color indices in image memory buffer instead of colors themselves.

Color Conversion
----------------

The driver must implement functions that convert MicroUI's standard 32-bit ARGB colors (see :ref:`LLDISPLAY-API-SECTION`) to display color representation. For each application ARGB8888 color, the display driver has to find the corresponding color in the table. The Graphics Engine will store the index of the color in the table instead of using the color itself.

When an application color is not available in the display driver table (CLUT), the display driver can try to find the closest color or return a default color. First solution is often quite difficult to write and can cost a lot of time at runtime. That's why the second solution is preferred. However, a consequence is that the application has only to use a range of colors provided by the display driver.

Alpha Blending
--------------

MicroUI and the Graphics Engine use blending when drawing some texts or anti-aliased shapes. For each pixel to draw, the display stack blends the current application foreground color with the targeted pixel current color or with the current application background color (when enabled). This blending *creates* some  intermediate colors which are managed by the display driver. 

Most of time the intermediate colors do not match with the palette. The default color is so returned and the rendering becomes wrong. To prevent this use case, the Graphics Engine offers a specific Low Level API ``LLUI_DISPLAY_IMPL_prepareBlendingOfIndexedColors(void* foreground, void* background)``. 

This API is only used when a blending is required and when the background color is enabled. The Graphics Engine calls the API just before the blending and gives as parameter the pointers on the both ARGB colors. The display driver should replace the ARGB colors by the CLUT indices. Then the Graphics Engine will only use between both indices. 

For instance, when the returned indices are ``20`` and ``27``, the display stack will use the indices ``20`` to ``27``, where all indices between ``20`` and ``27`` target some intermediate colors between both the original ARGB colors. 

This solution requires several conditions:

-  Background color is enabled and it is an available color in the CLUT.
-  Application can only use foreground colors provided by the CLUT. The platform designer should give to the application developer the available list of colors the CLUT manages.
-  The CLUT must provide a set of blending ranges the application can use. Each range can have its own size (different number of colors between two colors). Each range is independent. For instance if the foreground color ``RED`` (``0xFFFF0000``) can be blended with two background colors ``WHITE`` (``0xFFFFFFFF``) and ``BLACK`` (``0xFF000000``), two ranges must be provided. Both the ranges have to contain the same index for the color ``RED``.
-  Application can only use blending ranges provided by the CLUT. Otherwise the display driver is not able to find the range and the default color will be used to perform the blending.
-  Rendering of dynamic images (images decoded at runtime) may be wrong because the ARGB colors may be out of CLUT range.

.. _display_pixel_conversion:

Image Pixel Conversion
======================

Overview
--------

The Graphics Engine is built for a dedicated display pixel format (see :ref:`display_pixel_structure`). For this pixel format, the Graphics Engine must be able to draw images with or without alpha blending and with or without transformation. In addition, it must be able to read all image formats.

The application may not use all MicroUI image drawings options and may not use all images formats. It is not possible to detect what the application needs, so no optimization can be performed at application compiletime. However, for a given application, the platform can be built with a reduced set of pixel support. 

All pixel format manipulations (read, write, copy) are using dedicated functions. It is possible to remove some functions or to use generic functions. The advantage is to reduce the memory footprint. The inconvenient is that some features are removed (the application should not use them) or some features are slower (generic functions are slower than the dedicated functions).

Functions
---------

There are five pixel *conversion* modes:

-  Draw an image without transformation and without global alpha blending: copy a pixel from a format to the destination format (display format).
-  Draw an image without transformation and with global alpha blending: copy a pixel with alpha blending from a format to the destination format (display format).
-  Draw an image with transformation and with or without alpha blending: draw an ARGB8888 pixel in destination format (display format).
-  Load a `ResourceImage <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html>`_ with an output format: convert an ARGB8888 pixel to the output format.
-  Read a pixel from an image (`Image.readPixel() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#readPixel-int-int->`_ or to draw an image with transformation or to convert an image): read any pixel formats and convert it in ARGB8888.

.. table:: Pixel Conversion

   +------------------------------------------+-------------+-------------+-------------+
   |                                          | Nb input    | Nb output   | Number of   |
   |                                          | formats     | formats     | combinations|
   +==========================================+=============+=============+=============+
   | Draw image without global alpha          |     22      |      1      |     22      |
   +------------------------------------------+-------------+-------------+-------------+
   | Draw image with global alpha             |     22      |      1      |     22      |
   +------------------------------------------+-------------+-------------+-------------+
   | Draw image with transformation           |      2      |      1      |      2      |
   +------------------------------------------+-------------+-------------+-------------+
   | Load a  ``ResourceImage``                |      1      |      6      |      6      |
   +------------------------------------------+-------------+-------------+-------------+
   | Read an image                            |     22      |      1      |     22      |
   +------------------------------------------+-------------+-------------+-------------+

There are ``22x1 + 22x1 + 2x1 + 1x6 + 22x1 = 74`` functions. Each function takes between 50 and 200 bytes depending on its complexity and the C compiler. 

Linker File
-----------

All pixel functions are listed in a platform linker file. It is possible to edit this file to remove some features or to share some functions (using generic function).

How to get the file:

#. Build platform as usual.
#. Copy platform file ``[platform]/source/link/display_image_x.lscf`` in platform configuration project: ``[platform configuration project]/dropins/link/``. ``x`` is a number which characterizes the display pixel format (see :ref:`display_pixel_structure`). See next warning.
#. Perform some changes into the copied file (see after).
#. Rebuild the platform: the `dropins` file is copied in the platform instead of the original one.

.. warning:: When the display format in ``[platform configuration project]/display/display.properties`` changes, the linker file suffix changes too. Perform again all operations in new file with new suffix.

The linker file holds five tables, one for each use case, respectively ``IMAGE_UTILS_TABLE_COPY``, ``IMAGE_UTILS_TABLE_COPY_WITH_ALPHA``, ``IMAGE_UTILS_TABLE_DRAW``, ``IMAGE_UTILS_TABLE_SET`` and ``IMAGE_UTILS_TABLE_READ``. For each table, a comment describes how to remove an option (when possible) or how to replace an option by a generic function (if available). 

Library ej.api.Drawing
======================

This Foundation Library provides additional drawing APIs. This library is fully integrated in Display module. It requires an implementation of its Low Level API: ``LLDW_PAINTER_impl.h``. These functions are implemented in the Abstraction Layer implementation module `com.microej.clibrary.llimpl#microui <https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui>`_. Like MicroUI painter's natives, the functions are redirected to ``dw_drawing.h``. A default implementation of these functions is available in Software Algorithms module (in weak). This allows the BSP to override one or several APIs.

.. _section_display_implementation:

Dependencies
============

-  MicroUI module (see :ref:`section_microui`)

-  ``LLUI_DISPLAY_impl.h`` implementation if standard or custom
   implementation is chosen (see
   :ref:`section_display_implementation` and
   :ref:`LLDISPLAY-API-SECTION`).


.. _section_display_installation:

Installation
============

The Display module is a sub-part of the MicroUI library. When the MicroUI module is
installed, the Display module must be installed in order to be able to
connect the physical display with the MicroEJ Platform. If not
installed, the *stub* module will be used.

In the platform configuration file, check :guilabel:`UI` > :guilabel:`Display` to
install the Display module. When checked, the properties file
``display/display.properties`` is required during platform creation to
configure the module. This configuration step is used to choose the kind
of implementation (see :ref:`section_display_implementation`).

The properties file must / can contain the following properties:

-  ``bpp`` [mandatory]: Defines the number of bits per pixels the
   display device is using to render a pixel. Expected value is one
   among these both list:

   Standard formats:

   -  ``ARGB8888``: Alpha 8 bits; Red 8 bits; Green 8 bits; Blue 8 bits,

   -  ``RGB888``: Alpha 0 bit; Red 8 bits; Green 8 bits; Blue 8 bits
      (fully opaque),

   -  ``RGB565``: Alpha 0 bit; Red 5 bits; Green 6 bits; Blue 5 bits
      (fully opaque),

   -  ``ARGB1555``: Alpha 1 bit; Red 5 bits; Green 5 bits; Blue 5 bits
      (fully opaque or fully transparent),

   -  ``ARGB4444``: Alpha 4 bits; Red 4 bits; Green 4 bits; Blue 4 bits,

   -  ``C4``: 4 bits to encode linear grayscale colors between
      0xff000000 and 0xffffffff (fully opaque),

   -  ``C2``: 2 bits to encode linear grayscale colors between
      0xff000000 and 0xffffffff (fully opaque),

   -  ``C1``: 1 bit to encode grayscale colors 0xff000000 and 0xffffffff
      (fully opaque).

   Custom formats:

   -  ``32``: up to 32 bits to encode Alpha, Red, Green and Blue (in any custom arrangement),

   -  ``24``: up to 24 bits to encode Alpha, Red, Green and Blue (in any custom arrangement),

   -  ``16``: up to 16 bits to encode Alpha, Red, Green and Blue (in any custom arrangement),

   -  ``8``: up to 8 bits to encode Alpha, Red, Green and Blue (in any custom arrangement),

   -  ``4``: up to 4 bits to encode Alpha, Red, Green and Blue (in any custom arrangement),

   -  ``2``: up to 2 bits to encode Alpha, Red, Green and Blue (in any custom arrangement),

   -  ``1``: 1 bit to encode Alpha, Red, Green or Blue.

   All other values are forbidden (throw a generation error).

-  ``byteLayout`` [optional, default value is "line"]: Defines the
   pixels data order in a byte the display device is using. A byte can
   contain several pixels when the number of bits-per-pixels (see 'bpp'
   property) is lower than 8. Otherwise this property is useless. Two
   modes are available: the next bit(s) on the same byte can target the next pixel on the same line or on the same column. In first case, when the end of
   line is reached, the next byte contains the first pixels of next
   line. In second case, when the end of column is reached, the next
   byte contains the first pixels of next column. In both cases, a new
   line or a new column restarts with a new byte, even if it remains
   some free bits in previous byte.

   -  ``line``: the next bit(s) on current byte contains the next pixel
      on same line (x increment),

   -  ``column``: the next bit(s) on current byte contains the next
      pixel on same column (y increment).

   .. note::

      -  Default value is 'line'.

      -  All other modes are forbidden (throw a generation error).

      -  When the number of bits-per-pixels (see 'bpp' property) is
         higher or equal than 8, this property is useless and ignored.

-  ``memoryLayout`` [optional, default value is "line"]: Defines the
   pixels data order in memory the display device is using. This option
   concerns only the display with a bpp lower than 8 (see 'bpp' property).
   Two modes are available: when the byte memory address is incremented,
   the next targeted group of pixels is the next group on the same line
   or the next group on same column. In first case, when the end of line
   is reached, the next group of pixels is the first group of next line.
   In second case, when the end of column is reached, the next group of
   pixels is the first group of next column.

   -  ``line``: the next memory address targets the next group of pixels
      on same line (x increment),

   -  ``column``: the next memory address targets the next group of
      pixels on same column (y increment).

   .. note::

      -  Default value is 'line'.

      -  All other modes are forbidden (throw a generation error).

      -  When the number of bits-per-pixels (see 'bpp' property) is
         higher or equal than 8, this property is useless and ignored.

-  ``imageBuffer.memoryAlignment`` [optional, default value is "4"]: Defines the image memory alignment to respect when creating an image. This notion is useful when images drawings are performed by a third party hardware accelerator (GPU): it can require some constraints on the image to draw. This value is used by the Graphics Engine when creating a dynamic image and by the image generator to encode a RAW image. See :ref:`section_image_gpu_raw` and :ref:`section_image_custom_format`. Allowed values are 1, 2, 4, 8, 16, 32, 64, 128 and 256.

-  ``imageHeap.size`` [optional, default value is "not set"]: Defines the images heap size. Useful to fix a platform heap size when building a firmware in command line. When using a MicroEJ launcher, the size set in this launcher is priority to the platform value.


Use
===

The MicroUI Display APIs are available in the class `ej.microui.display.Display <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html>`_.


..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
