.. _section.ui.Images:

Images
======

Immutable Images
----------------

Overview
~~~~~~~~

Immutable images are graphical resources that can be accessed with a call to `ej.microui.display.Image.getImage()`_ or `ej.microui.display.ResourceImage.loadImage()`_.
As their name suggests, immutable images can not be modified.
Therefore, there is no way to get a Graphics Context to draw into these images.
To be displayed, these images have to be converted from their source format to a RAW format.
The conversion can either be done:

- At build-time, using the image generator tool.
- At run-time, using the relevant decoder library.

Immutable images are declared in :ref:`Classpath<chapter.microej.classpath>` ``*.images.list`` files (**or** in ``*.imagesext.list`` for an external resource, see :ref:`chapter.microej.applicationResources`).

.. graphviz::

  digraph D {
  
      internalImage [shape=diamond, label="internal?"]
      imagesList [shape=box, label="*.images.list"]
      imagesExt [shape=box, label="*.imagesext.list"]
      subgraph cluster_image {
          label ="Image"
          internalImage -> imagesList [label="yes"]
          internalImage -> imagesExt [label="no=external"]
      }
  }

The file format is a standard Java properties file.
Each line contains a ``/``-separated resource path relative to the Classpath root referring to a standard image file (e.g. ``.png``, ``.jpg``).
The resource may be followed by an optional parameter (separated by a ``:``) which defines and/or describes the image output file format (RAW format).
When no option is specified, the image is embedded as-is and will be decoded at run-time.
Example:

::

   # The following image is embedded as
   # a PNG resource (decoded at run-time)
   com/mycompany/MyImage1.png

   # The following image is embedded as
   # a 16-bit encoding without transparency (decoded at build-time)
   com/mycompany/MyImage2.png:RGB565

   # The following image is embedded as
   # a 16-bit encoding with transparency (decoded at build-time)
   com/mycompany/MyImage3.png:ARGB1555


.. _ej.microui.display.Image.getImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#getImage-java.lang.String-
.. _ej.microui.display.ResourceImage.loadImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html#loadImage-java.lang.String-

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

.. _section_image_unspecified_output:

Unspecified Output Format
~~~~~~~~~~~~~~~~~~~~~~~~~

When no output format is set in the image list file, the image is embedded without any conversion / compression.
This allows you to embed the resource as-is, in order to keep the source image characteristics (compression, bpp, size, etc.).
This option produces the same result as specifying an image as a resource in the MicroEJ launcher (i.e. in a ``.resources.list`` file).

Refer to the platform specification to retrieve the list of runtime decoders.

**Advantages**

- Preserves the image characteristics.
- Preserves the original image compression.

**Disadvantages**

- Requires an image runtime decoder.
- Requires some RAM in which to store the decoded image.
- Requires execution time to decode the image.

::

   image1
   
.. _section_image_display_output:

Display Output Format
~~~~~~~~~~~~~~~~~~~~~

It encodes the image into the exact display memory representation.
If the image to encode contains some transparent pixels, the output file will embed the transparency according to the display's implementation capacity.
When all pixels are fully opaque, no extra information will be stored in the output file in order to free up some memory space.

.. note:: When the display memory representation is standard, the display output format is automatically replaced by a standard format.

**Advantages**

- Drawing an image is very fast because no pixel conversion is required at runtime.
- Supports alpha encoding when the display pixel format allows it.

**Disadvantages**

- No compression: the image size in bytes is proportional to the number of pixels.

::

   image1:display

.. _section_image_standard_output:

Standard Output Formats
~~~~~~~~~~~~~~~~~~~~~~~

Some image formats are well known and commonly implemented by GPUs.

Refer to the platform specification to retrieve the list of natively supported formats.

**Advantages**

- The pixel layout and bit format are standard, so it is easy to manipulate these images on the C-side.
- Drawing an image is very fast when the display driver recognizes the format (with or without transparency).

**Disadvantages**

- No compression: the image size in bytes is proportional to the number of pixels.
- Slower than ``display`` format when the display driver does not recognize the format: a pixel conversion is required at runtime.

Here is the list of the standard formats:

- Transparent images:
   - ARGB8888: 32-bit format, 8 bits for transparency, 8 per color.
   - ARGB4444: 16-bit format, 4 bits for transparency, 4 per color.
   - ARGB1555: 16-bit format, 1 bit for transparency, 5 per color.
- Opaque images:
   - RGB888: 24-bit format, 8 per color,
   - RGB565: 16-bit format, 5 for red, 6 for green, 5 for blue.
- Alpha images, only transparency is encoded (the color applied when drawing the image is the current GraphicsContext color):
   - A8: 8-bit format,
   - A4: 4-bit format,
   - A2: 2-bit format,
   - A1: 1-bit format.

Examples:

::

   image1:ARGB8888
   image2:RGB565
   image3:A4

.. _section_image_grayscale_output:

Grayscale Output Formats
~~~~~~~~~~~~~~~~~~~~~~~~

Some grayscale formats may be useful on grayscale or black and white displays.

**Advantages**

- Reduced footprint with less bits per pixels.

**Disadvantages**

- No compression: the image size in bytes is proportional to the number of pixels.
- Slower: a pixel conversion is required at runtime.

Here is the list of the grayscale formats:

- With transparency:
   - AC44: 4 bits for transparency, 4 bits with grayscale conversion.
   - AC22: 2 bits for transparency, 2 bits with grayscale conversion.
   - AC11: 1 bit for transparency, 1 bit with grayscale conversion.
- Without transparency:
   - C4: 4 bits with grayscale conversion.
   - C2: 2 bits with grayscale conversion.
   - C1: 1 bit with grayscale conversion.

Examples:

::

   image1:AC44
   image2:C2

.. _section_image_rle_output:

Compressed Output Formats
~~~~~~~~~~~~~~~~~~~~~~~~~

Some image formats are compressed using run-length encoding.
This compression is lossless.
The principle is that identical consecutive pixels are stored as one entry (value and count).
The more the consecutive pixels are identical, the more the compression is efficient.

**Advantages**

- Good compression when there are a lot of identical consecutive pixels.

**Disadvantages**

- Drawing an image may be slightly slower than using an uncompressed format supported by the GPU.
- Not designed for images with many different pixel colors: in such case, the output file size may be larger than the original image file.

Here is the list of the compressed formats:

- ARGB1565_RLE: 16-bit format, 1 bit for transparency, 5 for red, 6 for green, 5 for blue. (Formerly named RLE1 up to UI Pack 13.3.X.)
- A8_RLE: similar to A8.

::

   image1:ARGB1565_RLE
   image2:RLE1 # Deprecated
   image3:A8_RLE

Expected Result
~~~~~~~~~~~~~~~

The following table summarizes the usage of the different formats and the actual result on a white background.

.. table:: Image Output Formats Usage

   +--------------+------------------------------------+-------------------------------------+
   | Format       | Source                             | Result                              |
   +==============+====================================+=====================================+
   | ARGB8888     | .. image:: images/transparent.png  | .. image:: images/argb8888.png      |
   +--------------+------------------------------------+-------------------------------------+
   | ARGB4444     | .. image:: images/transparent.png  | .. image:: images/argb4444.png      |
   +--------------+------------------------------------+-------------------------------------+
   | ARGB1555     | .. image:: images/transparent.png  | .. image:: images/argb1555.png      |
   +--------------+------------------------------------+-------------------------------------+
   | RGB888       | .. image:: images/opaque.png       | .. image:: images/rgb888_o.png      |
   |              +------------------------------------+-------------------------------------+
   |              | .. image:: images/transparent.png  | .. image:: images/rgb888_t.png      |
   +--------------+------------------------------------+-------------------------------------+
   | RGB565       | .. image:: images/opaque.png       | .. image:: images/rgb565_o.png      |
   |              +------------------------------------+-------------------------------------+
   |              | .. image:: images/transparent.png  | .. image:: images/rgb565_t.png      |
   +--------------+------------------------------------+-------------------------------------+
   | A8           | .. image:: images/picto.png        | .. image:: images/a8.png            |
   |              +------------------------------------+-------------------------------------+
   |              | With 0x0000ff as color             | .. image:: images/a8_c.png          |
   +--------------+------------------------------------+-------------------------------------+
   | A4           | .. image:: images/picto.png        | .. image:: images/a4.png            |
   |              +------------------------------------+-------------------------------------+
   |              | With 0x0000ff as color             | .. image:: images/a4_c.png          |
   +--------------+------------------------------------+-------------------------------------+
   | A2           | .. image:: images/picto.png        | .. image:: images/a2.png            |
   |              +------------------------------------+-------------------------------------+
   |              | With 0x0000ff as color             | .. image:: images/a2_c.png          |
   +--------------+------------------------------------+-------------------------------------+
   | A1           | .. image:: images/picto.png        | .. image:: images/a1.png            |
   |              +------------------------------------+-------------------------------------+
   |              | With 0x0000ff as color             | .. image:: images/a1_c.png          |
   +--------------+------------------------------------+-------------------------------------+
   | C4           | .. image:: images/grayscale.png    | .. image:: images/c4.png            |
   +--------------+------------------------------------+-------------------------------------+
   | C2           | .. image:: images/grayscale.png    | .. image:: images/c2.png            |
   +--------------+------------------------------------+-------------------------------------+
   | C1           | .. image:: images/grayscale.png    | .. image:: images/c1.png            |
   +--------------+------------------------------------+-------------------------------------+
   | AC44         | .. image:: images/grayscale_t.png  | .. image:: images/ac44.png          |
   +--------------+------------------------------------+-------------------------------------+
   | AC22         | .. image:: images/grayscale_t.png  | .. image:: images/ac22.png          |
   +--------------+------------------------------------+-------------------------------------+
   | AC11         | .. image:: images/grayscale_t.png  | .. image:: images/ac11.png          |
   +--------------+------------------------------------+-------------------------------------+
   | ARGB1565_RLE | .. image:: images/transparent.png  | .. image:: images/argb1555.png      |
   +--------------+------------------------------------+-------------------------------------+
   | A8_RLE       | .. image:: images/picto.png        | .. image:: images/a8.png            |
   +--------------+------------------------------------+-------------------------------------+



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

Unlike immutable images, mutable images are graphical resources that can be created and modified at runtime. The application can draw into such images using the Painter classes with the image's `Graphics Context`_ as the destination.
Mutable images can be created with a call to constructor `ej.microui.display.BufferedImage()`_. 

.. code:: java

   BufferedImage image = new BufferedImage(320,  240);
   GraphicsContext g = image.getGraphicsContext();
   g.setColor(Colors.BLACK);
   Painter.fillRectangle(g, 0, 0, 320, 240);
   g.setColor(Colors.RED);
   Painter.drawHorizontalLine(g, 50, 50, 100);
   image.close();


.. _Graphics Context: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html#getGraphicsContext--
.. _ej.microui.display.BufferedImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html#BufferedImage-int-int-

Transparency
~~~~~~~~~~~~

The output format of `BufferedImage`_ matches the pixel organization (layout, depth, etc.) of the display.
The algorithms used to draw in such an image are the same as those used to draw on the display (for footprint purposes). 
Since the display buffer is opaque, the algorithms cannot draw transparent pixels.

In addition, `GraphicsContext.setColor()`_ does not take the alpha channel into account and only accepts RGB values. 
The given color value is interpreted as a 24-bit RGB color, where the high-order byte is ignored, and the remaining bytes contain the red, green, and blue channels, respectively.

.. _BufferedImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html
.. _GraphicsContext.setColor(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html#setColor-int-

.. _images_heap:

Images Heap
-----------

The image heap is used to allocate the pixel data of:

- Mutable images (i.e. `BufferedImage`_  instances).
- Immutable images decoded at runtime, typically a PNG: the heap is used to store the decoded image **and** the runtime decoder's temporary buffers, required during the decoding step.
  After the decoding step, all the temporary buffers are freed.
  Note that the size of the temporary buffers depends on the decoder **and** on the original image itself (compression level, pixel encoding, etc.).
- Immutable images which are not byte-addressable, such as images opened with an input stream (i.e. `ResourceImage`_  instances).
- Immutable images which are byte-addressable but converted to a different output format (i.e. `ResourceImage`_  instances).

In other words, every image which cannot be retrieved using `ej.microui.display.Image.getImage()`_  is saved on the image heap.

The size of the images heap can be configured with the ``ej.microui.memory.imagesheap.size`` property.

.. warning:: A `ResourceImage`_  allocated on the images heap must be closed manually by the application (`ResourceImage.close()`_); otherwise, a memory leak will occur on the images heap.

.. _ResourceImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html
.. _ResourceImage.close(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html#close--

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
