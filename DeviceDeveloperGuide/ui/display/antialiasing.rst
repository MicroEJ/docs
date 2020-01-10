Antialiasing
============

Fonts
-----

The antialiasing mode for the fonts concerns only the fonts with more
than 1 bit per pixel (see `??? <#section_fontgen>`__).

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
