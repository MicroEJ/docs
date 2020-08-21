.. _section.ui.Images:

Images
======

Overview
--------

Images are graphical resources that can be accessed with a call to
``ej.microui.display.Image.getImage()`` or ``ej.microui.display.ResourceImage.loadImage()``. To be displayed, these
images have to be converted from their source format to the display raw
format. The conversion can either be done at:

-  build-time (using the image generator tool),

-  run-time (using the relevant decoder library).

Images that must be processed by the image generator tool are declared
in MicroEJ Classpath ``*.images.list`` files. The file format is a
standard Java properties file, each line representing a ``/`` separated
resource path relative to the MicroEJ classpath root referring to a
standard image file (e.g. ``.png``, ``.jpg``). The resource may be
followed by an optional parameter (separated by a ``:``) which defines
and/or describes the image output file format (raw format). When no
option is specified, the image is embedded as-is and will be decoded at
run-time (although listing files without format specifier has no impact
on the image generator processing, it is advised to specify them in the
``*.images.list`` files anyway, as it makes the run-time processing
behavior explicit). Example:

::

   # The following image is embedded 
   # as a PNG resource (decoded at run-time)
   com/mycompany/MyImage1.png

   # The following image is embedded 
   # as a 16 bits format without transparency (decoded at build-time)
   com/mycompany/MyImage2.png:RGB565

   # The following image is embedded 
   # as a 16 bits format with transparency (decoded at build-time)
   com/mycompany/MyImage3.png:ARGB1555

.. _image_gen_tool:

Configuration File
------------------

Here is the format of the ``*.images.list`` files.

::

   ConfigFile          ::= Line [ 'EOL' Line ]*
   Line                ::= ImagePath [ ':' ImageOption ]*
   ImagePath           ::= Identifier [ '/' Identifier ]*
   ImageOption         ::= [^:]*
   Identifier          ::= Letter [ LetterOrDigit ]*
   Letter              ::= 'a-zA-Z_$'
   LetterOrDigit       ::= 'a-zA-Z_$0-9'

Output Formats
--------------

No Compression
~~~~~~~~~~~~~~

When no output format is set in the images list file, the image is
embedded without any conversion / compression. This allows you to embed
the resource as well, in order to keep the source image characteristics
(compression, bpp etc.). This option produces the same result as
specifiying an image as a resource in the MicroEJ launcher.

Advantages:

-  Preserves the image characteristics.

Disadvantages:

-  Requires an image runtime decoder;

-  Requires some RAM in which to store the decoded image.

::

   image1

Display Output Format
~~~~~~~~~~~~~~~~~~~~~

This format encodes the image into the exact display memory
representation. If the image to encode contains some transparent pixels,
the output file will embed the transparency according to the display's
implementation capacity. When all pixels are fully opaque, no extra
information will be stored in the output file in order to free up some
memory space.

Advantages:

-  Drawing an image is very fast;

-  Supports alpha encoding.

Disadvantages:

-  No compression: the image size in bytes is proportional to the number
   of pixels.

::

   image1:display

Generic Output Formats
~~~~~~~~~~~~~~~~~~~~~~

Depending on the target hardware, several generic output formats are
available. Some formats may be directly managed by the BSP display
driver. Refer to the platform specification to retrieve the list of
natively supported formats.

Advantages:

-  The pixels layout and bits format are standard, so it is easy to
   manipulate these images on the C-side;

-  Drawing an image is very fast when the display driver recognizes the
   format (with or without transparency);

-  Supports or not the alpha encoding: select the most suitable format
   for the image to encode.

Disadvantages:

-  No compression: the image size in bytes is proportional to the number
   of pixels, the transparency, and the bits-per-pixel.

Select one the following format to use a generic format:

-  ARGB8888: 32 bits format, 8 bits for transparency, 8 per color.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return c;
      }

-  RGB888: 24 bits format, 8 per color. Image is always fully opaque.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return c & 0xffffff;
      }

-  ARGB4444: 16 bits format, 4 bits for transparency, 4 per color.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0
                  | ((c & 0xf0000000) >> 16)
                  | ((c & 0x00f00000) >> 12)
                  | ((c & 0x0000f000) >> 8)
                  | ((c & 0x000000f0) >> 4)
                  ;
      }

-  ARGB1555: 16 bits format, 1 bit for transparency, 5 per color.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0
                  | (((c & 0xff000000) == 0xff000000) ? 0x8000 : 0)
                  | ((c & 0xf80000) >> 9)
                  | ((c & 0x00f800) >> 6)
                  | ((c & 0x0000f8) >> 3)
                  ;
      }

-  RGB565: 16 bits format, 5 or 6 per color. Image is always fully
   opaque.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0
                  | ((c & 0xf80000) >> 8)
                  | ((c & 0x00fc00) >> 5)
                  | ((c & 0x0000f8) >> 3)
                  ;
      }

-  A8: 8 bits format, only transparency is encoded. The color to apply
   when drawing the image, is the current GraphicsContext color.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0xff - (toGrayscale(c) & 0xff);
      }

-  A4: 4 bits format, only transparency is encoded. The color to apply
   when drawing the image, is the current GraphicsContext color.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (0xff - (toGrayscale(c) & 0xff)) / 0x11;
      }

-  A2: 2 bits format, only transparency is encoded. The color to apply
   when drawing the image, is the current GraphicsContext color.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (0xff - (toGrayscale(c) & 0xff)) / 0x55;
      }

-  A1: 1 bit format, only transparency is encoded. The color to apply
   when drawing the image, is the current GraphicsContext color.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (0xff - (toGrayscale(c) & 0xff)) / 0xff;
      }

-  C4: 4 bits format with grayscale conversion. Image is always fully
   opaque.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (toGrayscale(c) & 0xff) / 0x11;
      }

-  C2: 2 bits format with grayscale conversion. Image is always fully
   opaque.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (toGrayscale(c) & 0xff) / 0x55;
      }

-  C1: 1 bit format with grayscale conversion. Image is always fully
   opaque.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (toGrayscale(c) & 0xff) / 0xff;
      }

-  AC44: 4 bits for transparency, 4 bits with grayscale conversion.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0
              | ((color >> 24) & 0xf0)
              | ((toGrayscale(color) & 0xff) / 0x11)
              ;
      }

-  AC22: 2 bits for transparency, 2 bits with grayscale conversion.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0
              | ((color >> 28) & 0xc0)
              | ((toGrayscale(color) & 0xff) / 0x55)
              ;
      }

-  AC11: 1 bit for transparency, 1 bit with grayscale conversion.

   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0
              | ((c & 0xff000000) == 0xff000000 ? 0x2 : 0x0)
              | ((toGrayscale(color) & 0xff) / 0xff)
              ;
      }

::

   image1:ARGB8888
   image2:RGB565
   image3:A4

RLE1 Output Format
~~~~~~~~~~~~~~~~~~

The image engine can display embedded images that are encoded into a
compressed format which encodes several consecutive pixels into one or
more 16-bits words. This encoding manages a maximum alpha level of 2
(alpha level is always assumed to be 2, even if the image is not
transparent).

-  Several consecutive pixels have the same color (2 words):

   -  First 16-bit word specifies how many consecutive pixels have the
      same color;

   -  Second 16-bit word is the pixels' color.

-  Several consecutive pixels have their own color (1 + n words):

   -  First 16-bit word specifies how many consecutive pixels have their
      own color;

   -  Next 16-bit word is the next pixel color.

-  Several consecutive pixels are transparent (1 word):

   -  16-bit word specifies how many consecutive pixels are transparent.

Advantages:

-  Supports 0 & 2 alpha encoding.

-  Good compression when several consecutive pixels respect one of the
   three previous rules.

Disadvantages:

-  Drawing an image is slightly slower than when using Display format.

::

   image1:RLE1

Error Messages
--------------

These errors can occur while preprocessing images.

.. tabularcolumns:: |L|p{1.5cm}|L|

.. table:: Static Image Generator Error Messages

   +--------+---------+-----------------------------------------------------+
   | ID     | Type    | Description                                         |
   +========+=========+=====================================================+
   | 0      | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error.                          |
   +--------+---------+-----------------------------------------------------+
   | 1      | Error   | The images list file has not been specified.        |
   +--------+---------+-----------------------------------------------------+
   | 2      | Error   | The image generator cannot create the final,        |
   |        |         | raw file.                                           |
   +--------+---------+-----------------------------------------------------+
   | 3      | Error   | The image generator cannot read the images          |
   |        |         | list file. Make sure the system allows reading of   |
   |        |         | this file.                                          |
   +--------+---------+-----------------------------------------------------+
   | 4      | Warning | The image generator has found no image to           |
   |        |         | generate.                                           |
   +--------+---------+-----------------------------------------------------+
   | 5      | Error   | The image generator cannot load the images          |
   |        |         | list file.                                          |
   +--------+---------+-----------------------------------------------------+
   | 6      | Warning | The specified image path is invalid: The image will |
   |        |         | be not converted.                                   |
   +--------+---------+-----------------------------------------------------+
   | 7      | Warning | There are too many or too few options for the       |
   |        |         | desired format.                                     |
   +--------+---------+-----------------------------------------------------+
   | 8      | Error   | The display format is not generic; a                |
   |        |         | MicroUIRawImageGeneratorExtension implementation is |
   |        |         | required to generate the MicroUI raw image.         |
   +--------+---------+-----------------------------------------------------+
   | 9      | Error   | The image cannot be read.                           |
   +--------+---------+-----------------------------------------------------+
   | 10     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid endianness).     |
   +--------+---------+-----------------------------------------------------+
   | 11     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid bpp).            |
   +--------+---------+-----------------------------------------------------+
   | 12     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid display format). |
   +--------+---------+-----------------------------------------------------+
   | 13     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid pixel layout).   |
   +--------+---------+-----------------------------------------------------+
   | 14     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid output folder).  |
   +--------+---------+-----------------------------------------------------+
   | 15     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid memory           |
   |        |         | alignment).                                         |
   +--------+---------+-----------------------------------------------------+
   | 16     | Warning | The specified format is not managed by the          |
   |        |         | image generator: The image will be not converted.   |
   +--------+---------+-----------------------------------------------------+
   | 17     | Warning | The image has been already loaded with another      |
   |        |         | output format. The image will be not converted.     |
   +--------+---------+-----------------------------------------------------+

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
