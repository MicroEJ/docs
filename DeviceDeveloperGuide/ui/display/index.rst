.. _section_display:

Display
=======

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

.. figure:: ui/display/images/display_modes_nocustom.svg
   :alt: Buffer Modes
   :width: 70.0%

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
`table_title <#switchModeSyncSteps>`__.

.. table:: Switch Mode Synchronization Steps

   +-----------------------------+----------------------------------------+
   | *Step 1:* Drawing           |                                        |
   |                             |                                        |
   | MicroUI is drawing in       |                                        |
   | buffer 0 (back buffer) and  |                                        |
   | the display is reading its  |                                        |
   | contents from buffer 1      |                                        |
   | (display buffer).           |                                        |
   +-----------------------------+----------------------------------------+
   | *Step 2:* Switch            |                                        |
   |                             |                                        |
   | The drawing is done. Set    |                                        |
   | that the next read will be  |                                        |
   | done from buffer 0.         |                                        |
   |                             |                                        |
   | Note that the display       |                                        |
   | "hardware component"        |                                        |
   | asynchronously continues to |                                        |
   | read data from buffer 1.    |                                        |
   +-----------------------------+----------------------------------------+
   | *Step 3:* Copy              |                                        |
   |                             |                                        |
   | A copy from the buffer 0    |                                        |
   | (new display buffer) to the |                                        |
   | buffer 1 (new back buffer)  |                                        |
   | must be done to keep the    |                                        |
   | contents of the current     |                                        |
   | drawing. The copy routine   |                                        |
   | must wait until the display |                                        |
   | has finished the switch,    |                                        |
   | and start asynchronously by |                                        |
   | comparison with the MicroUI |                                        |
   | drawing routine (see next   |                                        |
   | step).                      |                                        |
   |                             |                                        |
   | This copy routine can be    |                                        |
   | done in a dedicated RTOS    |                                        |
   | task or in an interrupt     |                                        |
   | routine. The copy should    |                                        |
   | start after the display     |                                        |
   | "hardware component" has    |                                        |
   | finished a full buffer read |                                        |
   | to avoid flickering.        |                                        |
   | Usually a tearing signal    |                                        |
   | from the LCD at the end of  |                                        |
   | the read of the previous    |                                        |
   | buffer (buffer 1) or at the |                                        |
   | beginning of the read of    |                                        |
   | the new buffer (buffer 0)   |                                        |
   | throws an interrupt. The    |                                        |
   | interrupt routine starts    |                                        |
   | the copy using a DMA.       |                                        |
   |                             |                                        |
   | If it is not possible to    |                                        |
   | start an asynchronous copy, |                                        |
   | the copy must be performed  |                                        |
   | in the MicroUI drawing      |                                        |
   | routine, at the beginning   |                                        |
   | of the next step.           |                                        |
   |                             |                                        |
   | Note that the copy is       |                                        |
   | partial: only the parts     |                                        |
   | that have changed need to   |                                        |
   | be copied, lowering the CPU |                                        |
   | load.                       |                                        |
   +-----------------------------+----------------------------------------+
   | *Step 4:* Synchronization   |                                        |
   |                             |                                        |
   | Waits until the copy        |                                        |
   | routine has finished the    |                                        |
   | full copy.                  |                                        |
   |                             |                                        |
   | If the copy has not been    |                                        |
   | done asynchronously, the    |                                        |
   | copy must start after the   |                                        |
   | display has finished the    |                                        |
   | switch. It is a blocking    |                                        |
   | copy because the next       |                                        |
   | drawing operation has to    |                                        |
   | wait until this copy is     |                                        |
   | done.                       |                                        |
   +-----------------------------+----------------------------------------+
   | *Step 4:* Next draw         |                                        |
   | operation                   |                                        |
   |                             |                                        |
   | Same behavior as step 1     |                                        |
   | with buffers reversed.      |                                        |
   +-----------------------------+----------------------------------------+

.. _copyBufferMode:

Copy
~~~~

The copy mode is a double-buffered mode where the back buffer is in RAM
and has a fixed address. To update the display, data is sent to the
display buffer. This can be done either by a memory copy or by sending
bytes using a bus, such as SPI or I2C.

Synchronization steps are described in
`table_title <#copyModeSyncSteps>`__.

.. table:: Display Copy Mode

   +---------------------------+------------------------------------------+
   | *Step 1:* Drawing         |                                          |
   |                           |                                          |
   | MicroUI is drawing in the |                                          |
   | back buffer and the       |                                          |
   | display is reading its    |                                          |
   | content from the display  |                                          |
   | buffer.                   |                                          |
   +---------------------------+------------------------------------------+
   | *Step 2:* Copy            |                                          |
   |                           |                                          |
   | The drawing is done. A    |                                          |
   | copy from the back buffer |                                          |
   | to the display buffer is  |                                          |
   | triggered.                |                                          |
   |                           |                                          |
   | Note that the             |                                          |
   | implementation of the     |                                          |
   | copy operation may be     |                                          |
   | done asynchronously – it  |                                          |
   | is recommended to wait    |                                          |
   | until the display         |                                          |
   | "hardware component" has  |                                          |
   | finished a full buffer    |                                          |
   | read to avoid flickering. |                                          |
   | At the implementation     |                                          |
   | level, the copy may be    |                                          |
   | done by a DMA, a          |                                          |
   | dedicated RTOS task,      |                                          |
   | interrupt, etc.           |                                          |
   +---------------------------+------------------------------------------+
   | *Step 3:* Synchronization |                                          |
   |                           |                                          |
   | The next drawing          |                                          |
   | operation waits until the |                                          |
   | copy is complete.         |                                          |
   +---------------------------+------------------------------------------+

.. _directBufferMode:

Direct
~~~~~~

The direct mode is a single-buffered mode where the same memory area is
used for the back buffer and the display buffer
(`figure_title <#directMode>`__). Use of the direct mode is likely to
result in "noisy" rendering and flickering, but saves one buffer in
runtime memory.

.. figure:: ui/display/images/direct.svg
   :alt: Display Direct Mode
   :width: 30.0%

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
`??? <#section_display_installation>`__).

.. table:: Byte Layout: line

   +-------+-------+-------+-------+-------+-------+-------+-------+-------+
   | BPP   | MSB   |       |       |       |       |       |       | LSB   |
   +=======+=======+=======+=======+=======+=======+=======+=======+=======+
   | 4     | pixel | pixel |       |       |       |       |       |       |
   |       | 1     | 0     |       |       |       |       |       |       |
   +-------+-------+-------+-------+-------+-------+-------+-------+-------+
   | 2     | pixel | pixel | pixel | pixel |       |       |       |       |
   |       | 3     | 2     | 1     | 0     |       |       |       |       |
   +-------+-------+-------+-------+-------+-------+-------+-------+-------+
   | 1     | pixel | pixel | pixel | pixel | pixel | pixel | pixel | pixel |
   |       | 7     | 6     | 5     | 4     | 3     | 2     | 1     | 0     |
   +-------+-------+-------+-------+-------+-------+-------+-------+-------+

.. table:: Byte Layout: column

   +---------+-------------------+-------------------+-------------------+
   | BPP     | 4                 | 2                 | 1                 |
   +=========+===================+===================+===================+
   | MSB     | pixel 1           | pixel 3           | pixel 7           |
   +---------+-------------------+-------------------+-------------------+
   |         | pixel 6           |                   |                   |
   +---------+-------------------+-------------------+-------------------+
   |         | pixel 2           | pixel 5           |                   |
   +---------+-------------------+-------------------+-------------------+
   |         | pixel 4           |                   |                   |
   +---------+-------------------+-------------------+-------------------+
   |         | pixel 0           | pixel 1           | pixel 3           |
   +---------+-------------------+-------------------+-------------------+
   |         | pixel 2           |                   |                   |
   +---------+-------------------+-------------------+-------------------+
   |         | pixel 0           | pixel 1           |                   |
   +---------+-------------------+-------------------+-------------------+
   | LSB     | pixel 0           |                   |                   |
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
concern until 8 consecutive pixels (see `Byte
Layout <#section_display_layout_byte>`__). When installing the display
module, a property ``memoryLayout`` is required to specify the kind of
pixels representation (see `??? <#section_display_installation>`__).

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
`??? <#section_display_installation>`__).

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
representation (see `??? <#LLDISPLAY-API-SECTION>`__). This mode is
often used when the pixel representation is not ``ARGB`` or ``RGB`` but
``BGRA`` or ``BGR`` instead. This mode can also be used when the number
of bits for a color component (alpha, red, green or blue) is not
standard or when the value does not represent a color but an index in an
LUT.
