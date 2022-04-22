.. _section.ui.Images:

Images
======

Immutable Images
----------------

Overview
~~~~~~~~

Immutable images are graphical resources that can be accessed with a call to `ej.microui.display.Image.getImage() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#getImage-java.lang.String->`_ or `ej.microui.display.ResourceImage.loadImage() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html#loadImage-java.lang.String->`_. As their name suggests, immutable images can not be modified. Therefore, there is no way to get a Graphics Context to draw into these images. To be displayed, these
images have to be converted from their source format to a RAW
format. The conversion can either be done at:

-  build-time (using the image generator tool),

-  run-time (using the relevant decoder library).

Immutable images that must be processed by the Image Generator tool are declared in :ref:`MicroEJ Classpath<chapter.microej.classpath>` ``*.images.list`` files (or ``*.imagesext.list`` for an external resource, see :ref:`section.applicationResources.internal_and_external_resources`).
The file format is a standard Java properties file, each line representing a ``/`` separated resource path relative to the MicroEJ classpath root referring to a standard image file (e.g. ``.png``, ``.jpg``).
The resource may be followed by an optional parameter (separated by a ``:``) which defines and/or describes the image output file format (RAW format).
When no option is specified, the image is embedded as-is and will be decoded at run-time (although listing files without format specifier has no impact on the image generator processing, it is advised to specify them in the ``*.images.list`` files anyway, as it makes the run-time processing behavior explicit).
Example:

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
~~~~~~~~~~~~~~~~~~

Here is the format of the ``*.images.list`` files.

::

   ConfigFile          ::= Line [ 'EOL' Line ]*
   Line                ::= ImagePath [ ':' ImageOption ]*
   ImagePath           ::= Identifier [ '/' Identifier ]*
   ImageOption         ::= [^:]*
   Identifier          ::= Letter [ LetterOrDigit ]*
   Letter              ::= 'a-zA-Z_$'
   LetterOrDigit       ::= 'a-zA-Z_$0-9'

Unspecified Output Format
~~~~~~~~~~~~~~~~~~~~~~~~~

When no output format is set in the images list file, the image is
embedded without any conversion / compression. This allows you to embed
the resource as-is, in order to keep the source image characteristics
(compression, bpp, etc.). This option produces the same result as
specifying an image as a resource in the MicroEJ launcher (i.e. in a ``.resources.list`` file).

**Advantages**

- Preserves the image characteristics;
- Preserves the original image compression.

**Disadvantages**

- Requires an image runtime decoder;
- Requires some RAM in which to store the decoded image;
- Requires execution time to decode the image.

::

   image1
   
Standard Output Formats
~~~~~~~~~~~~~~~~~~~~~~~

Depending on the target hardware, several generic output formats are
available. Some formats may be directly managed by the BSP display
driver. Refer to the platform specification to retrieve the list of
natively supported formats.

**Advantages**

-  The pixels layout and bits format are standard, so it is easy to
   manipulate these images on the C-side;

-  Drawing an image is very fast when the display driver recognizes the
   format (with or without transparency);

-  Supports or not the alpha encoding: select the most suitable format
   for the image to encode.

**Disadvantages**

- No compression: the image size in bytes is proportional to the number   of pixels, the transparency, and the bits-per-pixel;
- Slower than ``display`` format when the display driver does not recognize the  format: a pixel conversion is required at runtime.

Select one the following format to use a generic format among this list: ``ARGB8888``, ``RGB888``, ``ARGB4444``, ``ARGB1555``, ``RGB565``, ``A8``, ``A4``, ``A2``, ``A1``, ``C4``, ``C2``, ``C1``, ``AC44``, ``AC22`` and ``AC11``. The following snippets describe the color conversion for each format:

-  ARGB8888: 32 bits format, 8 bits for transparency, 8 per color.

   ::

      int convertARGB8888toRAWFormat(int c){
          return c;
      }

-  RGB888: 24 bits format, 8 per color. Image is always fully opaque.

   ::

      int convertARGB8888toRAWFormat(int c){
          return c & 0xffffff;
      }

-  ARGB4444: 16 bits format, 4 bits for transparency, 4 per color.

   ::

      int convertARGB8888toRAWFormat(int c){
          return 0
                  | ((c & 0xf0000000) >> 16)
                  | ((c & 0x00f00000) >> 12)
                  | ((c & 0x0000f000) >> 8)
                  | ((c & 0x000000f0) >> 4)
                  ;
      }

-  ARGB1555: 16 bits format, 1 bit for transparency, 5 per color.

   ::

      int convertARGB8888toRAWFormat(int c){
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

      int convertARGB8888toRAWFormat(int c){
          return 0
                  | ((c & 0xf80000) >> 8)
                  | ((c & 0x00fc00) >> 5)
                  | ((c & 0x0000f8) >> 3)
                  ;
      }

-  A8: 8 bits format, only transparency is encoded. The color to apply
   when drawing the image, is the current GraphicsContext color.

   ::

      int convertARGB8888toRAWFormat(int c){
          return 0xff - (toGrayscale(c) & 0xff);
      }

-  A4: 4 bits format, only transparency is encoded. The color to apply
   when drawing the image, is the current GraphicsContext color.

   ::

      int convertARGB8888toRAWFormat(int c){
          return (0xff - (toGrayscale(c) & 0xff)) / 0x11;
      }

-  A2: 2 bits format, only transparency is encoded. The color to apply
   when drawing the image, is the current GraphicsContext color.

   ::

      int convertARGB8888toRAWFormat(int c){
          return (0xff - (toGrayscale(c) & 0xff)) / 0x55;
      }

-  A1: 1 bit format, only transparency is encoded. The color to apply
   when drawing the image, is the current GraphicsContext color.

   ::

      int convertARGB8888toRAWFormat(int c){
          return (0xff - (toGrayscale(c) & 0xff)) / 0xff;
      }

-  C4: 4 bits format with grayscale conversion. Image is always fully
   opaque.

   ::

      int convertARGB8888toRAWFormat(int c){
          return (toGrayscale(c) & 0xff) / 0x11;
      }

-  C2: 2 bits format with grayscale conversion. Image is always fully
   opaque.

   ::

      int convertARGB8888toRAWFormat(int c){
          return (toGrayscale(c) & 0xff) / 0x55;
      }

-  C1: 1 bit format with grayscale conversion. Image is always fully
   opaque.

   ::

      int convertARGB8888toRAWFormat(int c){
          return (toGrayscale(c) & 0xff) / 0xff;
      }

-  AC44: 4 bits for transparency, 4 bits with grayscale conversion.

   ::

      int convertARGB8888toRAWFormat(int c){
          return 0
              | ((color >> 24) & 0xf0)
              | ((toGrayscale(color) & 0xff) / 0x11)
              ;
      }

-  AC22: 2 bits for transparency, 2 bits with grayscale conversion.

   ::

      int convertARGB8888toRAWFormat(int c){
          return 0
              | ((color >> 28) & 0xc0)
              | ((toGrayscale(color) & 0xff) / 0x55)
              ;
      }

-  AC11: 1 bit for transparency, 1 bit with grayscale conversion.

   ::

      int convertARGB8888toRAWFormat(int c){
          return 0
              | ((c & 0xff000000) == 0xff000000 ? 0x2 : 0x0)
              | ((toGrayscale(color) & 0xff) / 0xff)
              ;
      }

Examples:

::

   image1:ARGB8888
   image2:RGB565
   image3:A4

Display Output Format
~~~~~~~~~~~~~~~~~~~~~

This format encodes the image into the exact display memory
representation. If the image to encode contains some transparent pixels,
the output file will embed the transparency according to the display's
implementation capacity. When all pixels are fully opaque, no extra
information will be stored in the output file in order to free up some
memory space.

.. note:: When the display memory representation is standard, the display output format is automatically replaced by a standard format.

**Advantages**

-  Drawing an image is very fast because no pixel conversion is required at runtime;

-  Supports alpha encoding when display pixel format allow it.

**Disadvantages**

-  No compression: the image size in bytes is proportional to the number
   of pixels.

::

   image1:display


RLE1 Output Format
~~~~~~~~~~~~~~~~~~

The image engine can display embedded images that are encoded into a compressed format which encodes several consecutive pixels into one or
more 16-bit words. This encoding manages a maximum alpha level of 2
(alpha level is always assumed to be 2, even if the image is not
transparent).

-  Several consecutive pixels have the same color (2 words):

   -  First 16-bit word specifies how many consecutive pixels have the
      same color (pixels colors converted in RGB565 format, without opacity data).

   -  Second 16-bit word is the pixels' color in RGB565 format.

-  Several consecutive pixels have their own color (1 + n words):

   -  First 16-bit word specifies how many consecutive pixels have their
      own color;

   -  Next 16-bit word is the next pixel color.

-  Several consecutive pixels are transparent (1 word):

   -  16-bit word specifies how many consecutive pixels are transparent.

**Advantages**

-  Supports fully opaque and fully transparent encoding.

-  Good compression when several consecutive pixels respect one of the
   three previous rules.

**Disadvantages**

-  Drawing an image is slightly slower than when using Display format.
- Not designed for images with many different pixel colors: in such case, the output file size may be larger than the original image file.

::

   image1:RLE1

Image Generator Error Messages
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
   | 16     | Error   | The input image format and / or the ouput format are| 
   |        |         | not managed by the image generator.                 |
   +--------+---------+-----------------------------------------------------+
   | 17     | Error   | The image has been already loaded with another      |
   |        |         | output format.                                      |
   +--------+---------+-----------------------------------------------------+


Mutable Images
--------------

Overview
~~~~~~~~

Unlike immutable images, mutable images are graphical resources that can be created and modified at runtime. The application can draw into such images using the Painter classes with the image's `Graphics Context <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html#getGraphicsContext-->`_ as the destination.
Mutable images can be created with a call to constructor `ej.microui.display.BufferedImage() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html#BufferedImage-int-int->`_. 

.. code:: java

   BufferedImage image = new BufferedImage(320,  240);
   GraphicsContext g = image.getGraphicsContext();
   g.setColor(Colors.BLACK);
   Painter.fillRectangle(g, 0, 0, 320, 240);
   g.setColor(Colors.RED);
   Painter.drawHorizontalLine(g, 50, 50, 100);
   image.close();


Transparency
~~~~~~~~~~~~

The output format of `BufferedImage <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html>`_ matches the pixel organization (layout, depth, etc.) of the display.
The algorithms used to draw in such an image are the same as those used to draw on the display (for footprint purposes). 
Since the display buffer is opaque, the algorithms cannot draw transparent pixels.

In addition, `GraphicsContext.setColor() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html#setColor-int->`_ does not take the alpha channel into account and only accepts RGB values. 
The given color value is interpreted as a 24-bit RGB color, where the high-order byte is ignored, and the remaining bytes contain the red, green, and blue channels, respectively.

.. _images_heap:

Images Heap
-----------

The images heap is used to allocate the pixel data of:

- mutable images (i.e. `BufferedImage <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html>`_  instances)
- immutable images decoded at runtime, typically a PNG: the heap is used to store the decoded image **and** the runtime decoder's temporary buffers, required during the decoding step. After the decoding step, all the temporary buffers are freed. Note that the size of the temporary buffers depend on the decoder **and** on the original image itself (compression level, pixel encoding, etc.)
- immutable images which are not byte-addressable, such as images opened with an input stream (i.e. `ResourceImage <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html>`_  instances)
- immutable images which are byte-addressable but converted to a different output format (i.e. `ResourceImage <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html>`_  instances)

In other words, every image which can not be retrieved using `Image.getImage() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#getImage-java.lang.String->`_  is saved on the images heap.

The size of the images heap can be configured with the ``ej.microui.memory.imagesheap.size`` property.

.. warning:: A `ResourceImage <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html>`_  allocated on the images heap must be closed manually by the application (`ResourceImage.close() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html#close-->`_); otherwise, a memory leak will occur on the images heap.


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
