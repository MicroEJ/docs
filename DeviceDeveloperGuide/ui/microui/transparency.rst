Transparency
============

MicroUI provides several policies to use the transparency. These
policies depend on several factors, including the kind of drawing and
the LCD pixel rendering format. The main concept is that MicroUI does
not allow you to draw something with a transparency level different from
255 (fully opaque). There are two exceptions: the images and the fonts.

Images
------

Drawing an image (a pre-generated image or an image decoded at runtime)
which contains some transparency levels does not depend on the LCD pixel
rendering format. During the image drawing, each pixel is converted into
32 bits by pixel format.

This pixel format contains 8 bits to store the transparency level
(alpha). This byte is used to merge the foreground pixel (image
transparent pixel) with the background pixel (LCD buffer opaque pixel).
The formula to obtain the pixel is:

::

   αMult = (αFG * αBG) / 255
   αOut = αFG + αBG - αMult
   COut = (CFG * αFG + CBG * αBG - CBG * αMult) / αOut 

where:

-  α\ *FG* is the alpha level of the foreground pixel (layer pixel)

-  α\ *BG* is the alpha level of the background pixel (working buffer
   pixel)

-  C\ *xx* is a color component of a pixel (Red, Green or Blue).

-  α\ *Out* is the alpha level of the final pixel

Fonts
-----

A font holds only a transparency level (alpha). This fixed alpha level
is defined during the pre-generation of a font (see
`??? <#section_fonts>`__).

-  ``1`` means 2 levels are managed: fully opaque and fully transparent.

-  ``2`` means 4 levels are managed: fully opaque, fully transparent and
   2 intermediate levels.

-  ``4`` means 16 levels are managed: fully opaque, fully transparent
   and 14 intermediate levels.

-  ``8`` means 256 levels are managed: fully opaque, fully transparent
   and 254 intermediate levels.
