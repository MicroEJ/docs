RLE1 Output Format
==================

The image engine can display embedded images that are encoded into a
compressed format which encodes several consecutive pixels into one or
more 16-bits words. This encoding manages a maximum alpha level of 2
(alpha level is always assumed to be 2, even if the image is not
transparent).

-  Several consecutive pixels have the same color (2 words).

   -  First 16-bit word specifies how many consecutive pixels have the
      same color.

   -  Second 16-bit word is the pixels' color.

-  Several consecutive pixels have their own color  (1 + n words).

   -  First 16-bit word specifies how many consecutive pixels have their
      own color.

   -  Next 16-bit word is the next pixel color.

-  Several consecutive pixels are transparent (1 word).

   -  16-bit word specifies how many consecutive pixels are transparent.

Advantages:

-  Supports 0 & 2 alpha encoding.

-  Good compression when several consecutive pixels respect one of the
   three previous rules.

Disadvantages:

-  Drawing an image is slightly slower than when using Display format.

::

   image1:RLE1
