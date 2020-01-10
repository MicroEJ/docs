.. _section_display_installation:

Installation
============

Display is a sub-part of the MicroUI library. When the MicroUI module is
installed, the Display module must be installed in order to be able to
connect the physical display with the PLATFORM. If not installed, the
*stub* module will be used.

In the platform configuration file, check ``GROUP.UI`` >
``MODULE.DISPLAY.PNAME`` to install the Display module. When checked,
the properties file ``MODULE.DISPLAY.NAME`` > ``MODULE.DISPLAY.NAME
            .properties`` is required during platform creation to
configure the module. This configuration step is used to choose the kind
of implementation (see `??? <#section_display_implementation>`__).

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
