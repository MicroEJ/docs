.. _section_display:

=======
Display
=======


Principle
=========

The Display module contains the C part of the MicroUI implementation
which manages graphical displays. This module is composed of two
elements:

-  the C part of MicroUI Display API (a built-in C archive)

-  an implementation of a low level API for the displays (LLDISPLAY)
   that the BSP must provide (see :ref:`LLDISPLAY-API-SECTION`)


.. _section_display_modes:

Display Configurations
----------------------

The Display modules provides a number of different configurations. The
appropriate configuration should be selected depending on the
capabilities of the screen and other related hardware, such as LCD
controllers.

The modes can vary in three ways:

-  the buffer mode: double-buffer, simple buffer (also known as
   "direct")

-  the memory layout of the pixels

-  pixel format or depth

The supplied configurations offer a limited range of combinations of the
options.

Buffer Modes
------------

Overview
~~~~~~~~

When using the double buffering technique, the memory into which the
application draws (called graphics buffer or back buffer) is not the
memory used by the screen to refresh it (called frame buffer or display
buffer). When everything has been drawn consistently from the
application point of view, the back buffer contents are synchronized
with the display buffer. Double buffering avoids flickering and
inconsistent rendering: it is well suited to high quality animations.

For more static display-based applications, and/or to save memory, an
alternative configuration is to use only one buffer, shared by both the
application and the screen.

Displays addressed by one of the standard configurations are called
*generic displays*. For these generic displays, there are three buffer
modes: switch, copy and direct. The following flow chart provides a
handy guide to selecting the appropriate buffer mode according to the
hardware configuration.

.. figure:: images/display_modes_nocustom.*
   :alt: Buffer Modes
   :width: 60.0%
   :align: center

   Buffer Modes

Implementation
~~~~~~~~~~~~~~

The display module (or stack) does not depend on type of buffer mode. At
the end of a drawing, the display stack calls the LLAPI
``LLDISPLAY_IMPL_flush`` to let the implementation to update the LCD
data. This function should be atomic and the implementation has to
return the new graphics buffer address (back buffer address). In
``direct`` and ``copy`` modes, this address never changes and the
implementation has always to return the back buffer address. In
``switch`` mode, the implementation has to return the old LCD frame
buffer address.

The next sections describe the work to do for each mode.

.. _switchBufferMode:

Switch
~~~~~~

The switch mode is a double-buffered mode where two buffers in RAM
alternately play the role of the back buffer and the display buffer. The
display source is alternatively changed from one buffer to the other.

Switching the source address may be done asynchronously. The synchronize
function is called before starting the next set of draw operations, and
must wait until the driver has switched to the new buffer.

Synchronization steps are described in
:ref:`the table below <table_switchModeSyncSteps>`.

.. _table_switchModeSyncSteps :
.. list-table:: Switch Mode Synchronization Steps

   -
      - | *Step 1:* Drawing
        | MicroUI is drawing in buffer 0 (back buffer) and the display is reading its contents from buffer 1 (display buffer).
      - .. image:: images/switch-step1.*
           :width: 284px
           :height: 160px
   -
      - | *Step 2:* Switch
        | The drawing is done. Set that the next read will be done from buffer 0.
        | Note that the display \"hardware component\" asynchronously continues to read data from buffer 1.
      - .. image:: images/switch-step2.*
           :width: 284px
           :height: 160px
   -
      - | *Step 3:* Copy
        | A copy from the buffer 0 (new display buffer) to the buffer 1 (new back buffer) must be done to keep the contents of the current drawing. The copy routine must wait until the display has finished the switch, and start asynchronously by comparison with the MicroUI drawing routine (see next step).
        | This copy routine can be done in a dedicated RTOS task or in an interrupt routine. The copy should start after the display \"hardware component\" has finished a full buffer read to avoid flickering.
        | Usually a tearing signal from the LCD at the end of the  read of the previous buffer (buffer 1) or at the beginning of the read of the new  buffer (buffer 0) throws an interrupt. The interrupt routine starts the copy using a DMA.
        | If it is not possible to start an asynchronous copy, the copy must be performed in the MicroUI drawing routine, at the beginning of the next step.
        | Note that the copy is partial: only the parts that have changed need to be copied, lowering the CPU load.
      - .. image:: images/switch-step3.*
           :width: 284px
           :height: 160px
   -
      - | *Step 4:* Synchronisation
        | Waits until the copy routine has finished the full copy.
        | If the copy has not been done asynchronously, the copy must start after the display has finished the switch. It is a blocking copy because the next drawing operation has to wait until this copy is done.
      - 
   -
      - | *Step 5:* Next draw operation
        | Same behavior as step 1 with buffers reversed.
      - .. image:: images/switch-step4.*
           :width: 284px
           :height: 160px

.. _copyBufferMode:

Copy
~~~~

The copy mode is a double-buffered mode where the back buffer is in RAM
and has a fixed address. To update the display, data is sent to the
display buffer. This can be done either by a memory copy or by sending
bytes using a bus, such as SPI or I2C.

Synchronization steps are described in
:ref:`the table below <table_copyModeSyncSteps>`.

.. _table_copyModeSyncSteps:
.. list-table:: Display Copy Mode

   -
      - | *Step 1:* Drawing 
        | MicroUI is drawing in the back buffer and the display is reading its content from the display buffer.
      - .. image:: images/copy-step1.*
           :width: 284px
           :height: 160px
           :scale: 100
   -
      - | *Step 2:* Copy 
        | The drawing is done. A copy from the back buffer to the display buffer is triggered. 
        | Note that the implementation of the copy operation may be done asynchronously – it is recommended to wait until the display "hardware component" has finished a full buffer read to avoid flickering. At the implementation level, the copy may be done by a DMA, a dedicated RTOS task, interrupt, etc.
      - .. image:: images/copy-step2.*
           :width: 284px
           :height: 160px
           :scale: 100
   -
      - | *Step 3:*  Synchronization
        | The next drawing operation waits until the copy is complete.
      - .. image:: images/copy-step3.*
           :width: 284px
           :height: 160px
           :scale: 100

.. _directBufferMode:

Direct
~~~~~~

The direct mode is a single-buffered mode where the same memory area is
used for the back buffer and the display buffer
(:ref:`See illustration below <fig_directMode>`). Use of the direct mode is likely to
result in "noisy" rendering and flickering, but saves one buffer in
runtime memory.

.. _fig_directMode:
.. figure:: images/direct.*
   :alt: Display Direct Mode
   :width: 30.0%
   :align: center

   Display Direct Mode

.. _section_display_layout_byte:

Byte Layout
-----------

This chapter concerns only LCD with a number of bits-per-pixel (BPP)
smaller than 8. For this kind of LCD, a byte contains several pixels and
the display module allows to customize how to organize the pixels in a
byte.

Two layouts are available:

-  line: The byte contains several consecutive pixels on same line. When
   the end of line is reatched, a padding is added in order to start a
   new line with a new byte.

-  column: The byte contains several consecutive pixels on same column.
   When the end of column is reatched, a padding is added in order to
   start a new column with a new byte.

When installing the display module, a property ``byteLayout`` is
required to specify the kind of pixels representation (see
:ref:`section_display_installation`).

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
-------------

For the LCD with a number of bits-per-pixel (BPP) higher or equal to 8,
the display module supports the line-by-line memory organization: pixels
are laid out from left to right within a line, starting with the top
line. For a display with 16 bits-per-pixel, the pixel at (0,0) is stored
at memory address 0, the pixel at (1,0) is stored at address 2, the
pixel at (2,0) is stored at address 4, and so on.

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

For the LCD with a number of bits-per-pixel (BPP) lower than 8, the
display module supports the both memory organizations: line by line
(pixels are laid out from left to right within a line, starting with the
top line) and column by column (pixels are laid out from top to bottom
within a line, starting with the left line). These byte organizations
concern until 8 consecutive pixels (see :ref:`section_display_layout_byte`). When installing the display
module, a property ``memoryLayout`` is required to specify the kind of
pixels representation (see :ref:`section_display_installation`).

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
   |     | (0,7)     | (15,7)    | (23,7)    | (31,7)    | (39,7)    |
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
---------------

The Display module provides pre-built display configurations with
standard pixel memory layout. The layout of the bits within the pixel
may be standard (see MicroUI GraphicsContext pixel formats) or
driver-specific. When installing the display module, a property ``bpp``
is required to specify the kind of pixel representation (see
:ref:`section_display_installation`).

When the value is one among this list:
``ARGB8888 | RGB888 | RGB565 | ARGB1555 | ARGB4444 | C4 | C2 | C1``, the
display module considers the LCD pixels representation as standard.
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

When the value is one among this list: ``1 | 2 | 4 | 8 | 16 | 24 | 32``,
the display module considers the LCD pixel representation as generic but
not standard. In this case, the driver must implement functions that
convert MicroUI's standard 32 bits ARGB colors to LCD color
representation (see :ref:`LLDISPLAY-API-SECTION`). This mode is
often used when the pixel representation is not ``ARGB`` or ``RGB`` but
``BGRA`` or ``BGR`` instead. This mode can also be used when the number
of bits for a color component (alpha, red, green or blue) is not
standard or when the value does not represent a color but an index in an
LUT.


Antialiasing
============

Fonts
-----

The antialiasing mode for the fonts concerns only the fonts with more
than 1 bit per pixel (see :ref:`section_fontgen`).

Background Color
----------------

For each pixel to draw, the antialiasing process blends the foreground
color with a background color. This background color is static or
dynamic:

-  static: The background color is fixed by the MicroEJ application
   (``GraphicsContext.setBackgroundColor()``).

-  dynamic: The background color is the original color of the
   destination pixel (a "read pixel" operation is performed for each
   pixel).

Note that the dynamic mode is slower than the static mode.


.. _display_lut:

LUT
===

The display module allows to target LCD which uses a pixel indirection
table (LUT). This kind of LCD are considered as generic but not standard
(see :ref:`display_pixel_structure`). By consequence, the driver
must implement functions that convert MicroUI's standard 32 bits ARGB
colors (see :ref:`LLDISPLAY-API-SECTION`) to LCD color
representation. For each application ARGB8888 color, the display driver
has to find the corresponding color in the table. The display module
will store the index of the color in the table instead of using the
color itself.

When an application color is not available in the display driver table
(LUT), the display driver can try to find the nearest color or return a
default color. First solution is often quite difficult to write and can
cost a lot of time at runtime. That's why the second solution is
preferred. However, a consequence is that the application has only to
use a range of colors provided by the display driver.

MicroUI and the display module uses blending when drawing some texts or
anti-aliased shapes. For each pixel to draw, the display stack blends
the current application foreground color with the targeted pixel current
color or with the current application background color (when enabled).
This blending *creates* some intermediate colors which are managed by
the display driver. Most of time the default color will be returned and
so the rendering will be wrong. To prevent this use case, the display
module offers a specific LLAPI
``LLDISPLAY_EXTRA_IMPL_prepareBlendingOfIndexedColors(void* foreground, void* background)``.
This API is only used when a blending is required and when the
background color is enabled. Display module calls the API just before
the blending and gives as parameter the pointers on the both ARGB
colors. The display driver should replace the ARGB colors by the LUT
indexes. Then the display module will only use the indexes between the
both indexes. For instance, when the returned indexes are ``20`` and
``27``, the display stack will use the indexes ``20`` to ``27``, where
all indexes between ``20`` and ``27`` target some intermediate colors
between the both original ARGB colors.

This solution requires several conditions:

-  Background color is enabled and it is an available color in the LUT.

-  Application can only use foreground colors provided by the LUT. The
   platform designer should give to the application developer the
   available list of colors the LUT manages.

-  The LUT must provide a set blending ranges the application can use.
   Each range can have its own size (different number of colors between
   two colors). Each range is independent. For instance if the
   foreground color ``RED`` (``0xFFFF0000``) can be blended with two
   background colors ``WHITE`` (``0xFFFFFFFF``) and ``BLACK``
   (``0xFF000000``), two ranges must be provided. The both ranges have
   to contain the same index for the color ``RED``.

-  Application can only use blending ranges provided by the LUT.
   Otherwise the display driver is not able to find the range and the
   default color will be used to perform the blending.

-  Rendering of dynamic images (images decoded at runtime) may be wrong
   because the ARGB colors may be out of LUT range.


.. _display_hard_accelerator:

Hardware Accelerator
====================

Overview
--------

The display module allows to use an hardware accelerator to perform some
drawings: fill a rectangle, draw an image, rotate an image etc. Some
optional functions are available in ``LLDISPLAY_EXTRA.h`` file (see
:ref:`LLDISPLAY-EXTRA-API-SECTION`). These functions are not
automatically call by the display module. The display module must be
configured during the MicroEJ platform construction specifying which
hardware accelerator to use. It uses the property
``hardwareAccelerator`` in ``display/display.properties`` file to select
a hardware accelerator (see :ref:`section_display_installation`).

The following table lists the available hardware accelerators supported
by MicroEJ, their full names, short names (used in the next tables) and
the ``hardwareAccelerator`` property value (see
:ref:`section_display_installation`).

.. table:: Hardware Accelerators

   +------------------------------------------+-------------+-------------+
   |                                          | Short name  | Property    |
   +==========================================+=============+=============+
   | Renesas Graphics Library RGA  [1]_       | RGA         | rga         |
   +------------------------------------------+-------------+-------------+
   | Renesas TES Dave/2d                      | Dave2D      | dave2d      |
   +------------------------------------------+-------------+-------------+
   | STMicroelectronics Chrom-ART Graphics    | DMA2D       | dma2d       |
   | Accelerator                              |             |             |
   +------------------------------------------+-------------+-------------+
   | Custom Hardware Accelerator              | Custom      | custom [2]_ |
   +------------------------------------------+-------------+-------------+

.. note::

   It is possible to target an hardware accelerator which is not
   supported by MicroEJ yet. Set the property ``hardwareAccelerator`` to
   ``custom`` to force display module to call all drawing functions
   which can be accelerated. The LLDISPLAY implementation is able or not
   to implement a function. If not, the software algorithm will be used.

The available list of supported hardware accelerators is MicroEJ
architecture dependent. For instance, the STMicroelectronics Chrom-ART
Graphics Accelerator is only available for the MicroEJ architecture for
Cortex-M4 and Cortex-M7. The Renesas Graphics Library RGA is only
available for the MicroEJ architecture for Cortex-A9. The following
table shows in which MicroEJ architecture an hardware accelerator is
available.

.. table:: Hardware Accelerators according MicroEJ Architectures

    +---------------------+-----+--------+-------+--------+
    |                     | RGA | Dave2D | DMA2D | Custom |
    +=====================+=====+========+=======+========+
    | ARM Cortex-M0+ IAR  |     |        |       | •      |
    +---------------------+-----+--------+-------+--------+
    | ARM Cortex-M4 ARMCC |     |        | •     | •      |
    +---------------------+-----+--------+-------+--------+
    | ARM Cortex-M4 GCC   |     | •      | •     | •      |
    +---------------------+-----+--------+-------+--------+
    | ARM Cortex-M4 IAR   |     |        | •     | •      |
    +---------------------+-----+--------+-------+--------+
    | ARM Cortex-M7 ARMCC |     |        | •     | •      |
    +---------------------+-----+--------+-------+--------+

.. note::

   Some hardware accelerators may not be available in off-the-self
   architectures . However they are available on some specific
   architectures. Please consult the engineering services page on
   MicroEJ website.

All hardware accelerators are not available for each number of
bits-per-pixel configuration. The following table illustrates in which
display stack according ``bpp``, an hardware accelerator can be used.

.. table:: Hardware Accelerators according BPP

   +-----------------------------+---------+---------+---------+---------+
   |                             | RGA     | Dave2D  | DMA2D   | Custom  |
   +=============================+=========+=========+=========+=========+
   | 1 BPP                       |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | C1                          |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | 2 BPP                       |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | C2                          |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | 4 BPP                       |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | C4                          |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | 8 BPP                       |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | 16 BPP                      |         |         |         | •       |
   +-----------------------------+---------+---------+---------+---------+
   | RGB565                      | •       | •       | •       | •       |
   +-----------------------------+---------+---------+---------+---------+
   | ARGB1555                    | •       | •       | •       | •       |
   +-----------------------------+---------+---------+---------+---------+
   | ARGB4444                    | •       | •       | •       | •       |
   +-----------------------------+---------+---------+---------+---------+
   | 24 BPP                      |         |         |         | •       |
   +-----------------------------+---------+---------+---------+---------+
   | RGB888                      |         |         | •       | •       |
   +-----------------------------+---------+---------+---------+---------+
   | 32 BPP                      |         |         |         | •       |
   +-----------------------------+---------+---------+---------+---------+
   | ARGB8888                    | •       | •       | •       | •       |
   +-----------------------------+---------+---------+---------+---------+

.. [1]
   hardware or software implementation

.. [2]
   see next note

Features and Limits
-------------------

Each hardware accelerator has a list of features (list of drawings the
hardware accelerator can perform) and some constraints. When the display
module is configured to use an hardware accelerator, it takes in
consideration these features and limits. If a drawing is detected by the
display module as a drawing to be hardware accelerated, the LLDISPLAY
implementation *must* configure and use the hardware accelerator to
perform the full drawing (not just a part of drawing).

.. note::

   The *custom* hardware generator does not have any limit by default.
   This is the LLDISPLAY implementation which fixes the limits.

The following table lists the algorithms accelerated by each hardware
accelerator.

.. table:: Hardware Accelerators Algorithms

   +-----------------------------------+-----------+-----------+-----------+
   |                                   | RGA       | Dave2D    | DMA2D     |
   +===================================+===========+===========+===========+
   | Fill a rectangle                  | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | Draw an image                     | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | Scale an image                    | •         |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | Rotate an image                   | •         |           |           |
   +-----------------------------------+-----------+-----------+-----------+

Images
------

The available list of supported image formats is not the same for all
hardware accelerators. Furthermore some hardware accelerators require a
custom header before the RAW pixel data, require a padding between each
line etc.. MicroEJ manages these contraints for supported hardware
accelerators. For *custom* hardware accelerator, no image header can be
added and no padding can be set.

The following table illustratres the RAW image formats supported by each
hardware accelerator.

.. table:: Hardware Accelerators RAW Image Formats

   +-----------------------------------+-----------+-----------+-----------+
   |                                   | RGA       | Dave2D    | DMA2D     |
   +===================================+===========+===========+===========+
   | A1                                | •  [3]_   |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | A2                                |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | A4                                | •  [4]_   |           | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | A8                                | •  [5]_   |           | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | C1                                |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | C2                                |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | C4                                |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | AC11                              |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | AC22                              |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | AC44                              |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | RGB565                            | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | ARGB1555                          | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | ARGB4444                          | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | RGB888                            |           |           | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | ARGB8888                          | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+

The RAW image given as parameter (in input and/or in output) respects
the hardware accelerator specification. For instance a RAW image with
4BPP must be often aligned on 8 bits, even if its size is odd. The RAW
image size given as parameter is the *software* size. That means it is
the size of the original image.

Example for a A4 image with required alignment on 8 bits:

-  Original image width in pixels (== width in MicroEJ application): 47

-  Hardware image width in pixels (== line width in pixels in RAW image
   data): 48

-  Width in pixels available in ``LLDISPLAY``
   (``((LLDISPLAY_SImage*)src)->width``): 48

-  Hardware width in bytes (== line width in bytes in RAW image data):
   48 / 2 = 24

The hardware size may be higher than the software size (like in the
example). However the number of pixels to draw
(``((LLDISPLAY_SDrawImage*)drawing)->src_width``) is *always* smaller or
equal to the software area size. That means the display module never
asks to draw the pixels which are outside the software area. The
hardware size is only useful to be compatible with the hardware
accelerator restrictions about memory alignment.

.. [3]
   maximum size <= display width

.. [4]
   maximum size <= display width

.. [5]
   maximum size <= display width


.. _section_display_implementation:

Implementations
===============

The implementation of the MicroUI ``Display`` API targets a generic
display (see :ref:`section_display_modes`): Switch, Copy and Direct.
It provides some low level API. The BSP has to implement these LLAPI,
making the link between the MicroUI C library ``display`` and the BSP
display driver. The LLAPI to implement are listed in the header file
``LLDISPLAY_impl.h``.

When there is no display on the board, a *stub* implementation of C
library is available. This C library must be linked by the third-party C
IDE when MicroUI module is installed in the MicroEJ platform.


Dependencies
============

-  MicroUI module (see :ref:`section_microui`)

-  ``LLDISPLAY_impl.h`` implementation if standard or custom
   implementation is chosen (see
   :ref:`section_display_implementation` and
   :ref:`LLDISPLAY-API-SECTION`).


.. _section_display_installation:

Installation
============

Display is a sub-part of the MicroUI library. When the MicroUI module is
installed, the Display module must be installed in order to be able to
connect the physical display with the MicroEJ Platform. If not
installed, the *stub* module will be used.

In the platform configuration file, check :guilabel:`UI` > :guilabel:`Display` to
install the Display module. When checked, the properties file
:guilabel:`display` > :guilabel:`display.properties` is required during platform creation to
configure the module. This configuration step is used to choose the kind
of implementation (see :ref:`section_display_implementation`).

The properties file must / can contain the following properties:

-  ``bpp`` [mandatory]: Defines the number of bits per pixels the
   display device is using to render a pixel. Expected value is one
   among these both list:

   Standard formats:

   -  ``ARGB8888``: Alpha 8 bits; Red 8 bits; Green 8 bits; Blue 8 bits

   -  ``RGB888``: Alpha 0 bit; Red 8 bits; Green 8 bits; Blue 8 bits
      (fully opaque)

   -  ``RGB565``: Alpha 0 bit; Red 5 bits; Green 6 bits; Blue 5 bits
      (fully opaque)

   -  ``ARGB1555``: Alpha 1 bit; Red 5 bits; Green 5 bits; Blue 5 bits
      (fully opaque or fully transparent)

   -  ``ARGB4444``: Alpha 4 bits; Red 4 bits; Green 4 bits; Blue 4 bits

   -  ``C4``: 4 bits to encode linear grayscale colors between
      0xff000000 and 0xffffffff (fully opaque)

   -  ``C2``: 2 bits to encode linear grayscale colors between
      0xff000000 and 0xffffffff (fully opaque)

   -  ``C1``: 1 bit to encode grayscale colors 0xff000000 and 0xffffffff
      (fully opaque)

   Custom formats:

   -  ``32``: until 32 bits to encode Alpha, Red, Green and/or Blue

   -  ``24``: until 24 bits to encode Alpha, Red, Green and/or Blue

   -  ``16``: until 16 bits to encode Alpha, Red, Green and/or Blue

   -  ``8``: until 8 bits to encode Alpha, Red, Green and/or Blue

   -  ``4``: until 4 bits to encode Alpha, Red, Green and/or Blue

   -  ``2``: until 2 bits to encode Alpha, Red, Green and/or Blue

   -  ``1``: 1 bit to encode Alpha, Red, Green or Blue

   All others values are forbidden (throw a generation error).

-  ``byteLayout`` [optional, default value is "line"]: Defines the
   pixels data order in a byte the display device is using. A byte can
   contain several pixels when the number of bits-per-pixels (see 'bpp'
   property) is lower than 8. Otherwise this property is useless. Two
   modes are available: the next bit(s) on same byte can target the next
   pixel on same line or on same column. In first case, when the end of
   line is reatched, the next byte contains the first pixels of next
   line. In second case, when the end of column is reatched, the next
   byte contains the first pixels of next column. In both cases, a new
   line or a new column restarts with a new byte, even if it remains
   some free bits in previous byte.

   -  ``line``: the next bit(s) on current byte contains the next pixel
      on same line (x increment)

   -  ``column``: the next bit(s) on current byte contains the next
      pixel on same column (y increment)

   .. note::

      -  Default value is 'line'.

      -  All others modes are forbidden (throw a generation error).

      -  When the number of bits-per-pixels (see 'bpp' property) is
         higher or equal than 8, this property is useless and ignored.

-  ``memoryLayout`` [optional, default value is "line"]: Defines the
   pixels data order in memory the display device is using. This option
   concerns only the LCD with a bpp lower than 8 (see 'bpp' property).
   Two modes are available: when the byte memory address is incremented,
   the next targeted group of pixels is the next group on the same line
   or the next group on same column. In first case, when the end of line
   is reached, the next group of pixels is the first group of next line.
   In second case, when the end of column is reached, the next group of
   pixels is the first group of next column.

   -  ``line``: the next memory address targets the next group of pixels
      on same line (x increment)

   -  ``column``: the next memory address targets the next group of
      pixels on same column (y increment)

   .. note::

      -  Default value is 'line'.

      -  All others modes are forbidden (throw a generation error).

      -  When the number of bits-per-pixels (see 'bpp' property) is
         higher or equal than 8, this property is useless and ignored.


Use
===

The MicroUI Display APIs are available in the class
``ej.microui.display.Display``.

