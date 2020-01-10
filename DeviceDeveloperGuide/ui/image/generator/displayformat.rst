.. _imagen_lcd_format:

Display Output Format
=====================

The default embedded image data format provided by the Image Generator
tool when using a generic extension is to encode the image into the
exact display memory representation. If the image to encode contains
some transparent pixels, the output file will embed the transparency
according to the display's implementation capacity. When all pixels are
fully opaque, no extra information will be stored in the output file in
order to free up some memory space.

Advantages:

-  Drawing an image is very fast.

-  Supports alpha encoding.

Disadvantages:

-  No compression: the image size in bytes is proportional to the number
   of pixels.

::

   image1:display
