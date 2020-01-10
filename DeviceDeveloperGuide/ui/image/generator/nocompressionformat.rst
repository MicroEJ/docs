No compression
==============

When no output format is set in the images list file, the image is
embedded without any conversion / compression. This allows you to embed
the resource as well, in order to keep the source image characteristics
(compression, bpp etc.). This option produces the same result as
specifying an image as a resource in the MicroEJ launcher.

Advantages:

-  Conserves the image characteristics.

Disadvantages:

-  Requires an image runtime decoder.

-  Requires some RAM in which to store the decoded image

::

   image1
