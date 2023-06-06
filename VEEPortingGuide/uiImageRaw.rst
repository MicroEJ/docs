.. _section_image_raw:

============
Image Format
============

The Image Engine makes the distinction between:

* The `input format`: the format of the original image.
* The `output format`: the image format used by the Image Renderer.

Several formats are managed in input: PNG, JPEG, BMP, etc.
A specific VEE Port can support additional input formats.

Several formats are managed in output: the MicroEJ formats and the binary format.
The output format can be:

* Generated from the input format using the off-board tool :ref:`section_image_generator` at application compile-time.
* Generated from the input format by using a :ref:`runtime decoder <image_runtime_decoder>` of the :ref:`section_image_loader` at application run-time.
* Dynamically created when using a `BufferedImage`_.

The Image Renderer manages only the MicroEJ formats (:ref:`section_image_standard_raw`, :ref:`section_image_display_raw`, and :ref:`section_image_custom_raw`).

The following table list all the formats and their usage.

+-----------+---------+---------+----------------------------+
| Format    | Input   | Output  | BufferedImage              |
+===========+=========+=========+============================+
| Display   | no      | yes     | yes                        |
+-----------+---------+---------+----------------------------+
| Standard  | no      | yes     | yes [#note_bufferedimage]_ |
+-----------+---------+---------+----------------------------+
| Grayscale | no      | yes     | yes [#note_bufferedimage]_ |
+-----------+---------+---------+----------------------------+
| RLE       | no      | yes     | no                         |
+-----------+---------+---------+----------------------------+
| Custom    | no      | not yet | yes [#note_bufferedimage]_ |
+-----------+---------+---------+----------------------------+
| Binary    | no      | yes     | no                         |
+-----------+---------+---------+----------------------------+
| Original  | yes     | no      | no                         |
+-----------+---------+---------+----------------------------+

.. [#note_bufferedimage] Need some support in the VEE Port to support formats different than the display one (see :ref:`section_buffered_image`).

The following sections list all the formats and their usage.

.. _section_image_display_raw:

MicroEJ Format: Display
=======================

The display buffer holds a pixel encoding which is:

* standard: see :ref:`section_image_standard_output`,
* grayscale: see :ref:`section_image_grayscale_output`,
* non-standard: see :ref:`section_image_display_output` and :ref:`display_pixel_structure`.

The non-standard display format can be customized to encode the pixel in the same encoding as the display.
The number of bits per pixel and the pixel bit organization is asked during the MicroEJ format generation and when the ``drawImage`` algorithms are running.
If the image to encode contains some transparent pixels, the output file will embed the transparency according to the display's implementation capacity.
When all pixels are fully opaque, no extra information will be stored in the output file to free up some memory space.

Notes:

* From the Image Engine point of view, the non-standard display format stays a MicroEJ format, readable by the Image Renderer.
* The required memory to encode an image with a non-standard display format is similar to :ref:`section_image_standard_raw`.
* When the display format is standard or grayscale, the encoded image format is replaced by the related standard format.
* The :ref:`Graphics Engine's drawing software algorithms <section_drawings_soft>` only target (are only compatible with) the buffered images whose format is the same as the display format (standard or non-standard).

.. _section_image_standard_raw:

MicroEJ Format: Standard
========================

See :ref:`section_image_standard_output`.

This format requires a small header (around 20 bytes) to store the image size (width, height), format, flags (is_transparent, etc.), row stride, etc.
The required memory also depends on the number of bits per pixel of the MicroEJ format:
::

      required_memory = header + (image_width * image_height) * bpp / 8;

The pixels array is stored after the MicroEJ image file header. A padding between the header and the pixels array is added to force to start the pixels array at a memory address aligned on the number of bits-per-pixels.

.. figure:: images/uiFormat01.*
   :width: 50.0%

Here are the conversions of 32-bit to each format:

-  ARGB8888: 32-bit format, 8 bits for transparency, 8 per color.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return c;
      }

-  ARGB4444: 16-bit format, 4 bits for transparency, 4 per color.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0
                  | ((c & 0xf0000000) >> 16)
                  | ((c & 0x00f00000) >> 12)
                  | ((c & 0x0000f000) >> 8)
                  | ((c & 0x000000f0) >> 4)
                  ;
      }

-  ARGB1555: 16-bit format, 1 bit for transparency, 5 per color.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0
                  | (((c & 0xff000000) == 0xff000000) ? 0x8000 : 0)
                  | ((c & 0xf80000) >> 9)
                  | ((c & 0x00f800) >> 6)
                  | ((c & 0x0000f8) >> 3)
                  ;
      }

-  RGB888: 24-bit format, 8 per color.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return c & 0xffffff;
      }

-  RGB565: 16-bit format, 5 for red, 6 for green, 5 for blue.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0
                  | ((c & 0xf80000) >> 8)
                  | ((c & 0x00fc00) >> 5)
                  | ((c & 0x0000f8) >> 3)
                  ;
      }

-  A8: 8-bit format, only transparency is encoded.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return 0xff - (toGrayscale(c) & 0xff);
      }

-  A4: 4-bit format, only transparency is encoded.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (0xff - (toGrayscale(c) & 0xff)) / 0x11;
      }

-  A2: 2-bit format, only transparency is encoded.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (0xff - (toGrayscale(c) & 0xff)) / 0x55;
      }

-  A1: 1-bit format, only transparency is encoded.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (0xff - (toGrayscale(c) & 0xff)) / 0xff;
      }

The pixel order follows this rule:
   ::

         pixel_offset = (pixel_Y * image_width + pixel_X) * bpp / 8;

.. _section_image_grayscale_raw:

MicroEJ Format: Grayscale
=========================

See :ref:`section_image_grayscale_output`.

This format requires a small header (around 20 bytes) to store the image size (width, height), format, flags (is_transparent, etc.), row stride, etc.
The required memory also depends on the number of bits per pixel of the MicroEJ format:
::

      required_memory = header + (image_width * image_height) * bpp / 8;

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

-  C4: 4 bits with grayscale conversion.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (toGrayscale(c) & 0xff) / 0x11;
      }

-  C2: 2 bits with grayscale conversion.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (toGrayscale(c) & 0xff) / 0x55;
      }

-  C1: 1 bit with grayscale conversion.
   ::

      u32 convertARGB8888toRAWFormat(u32 c){
          return (toGrayscale(c) & 0xff) / 0xff;
      }

The pixel order follows this rule:
   ::

         pixel_offset = (pixel_Y * image_width + pixel_X) * bpp / 8;

MicroEJ Format: RLE Compressed
==============================

See :ref:`section_image_rle_output`.

.. _section_image_custom_raw:

MicroEJ Format: Custom
======================

A custom format embeds a buffer whose data are VEE Port specific. 
This data may be:

* a pixel buffer whose encoding is different than the formats proposed before,
* a buffer that is not a pixel buffer.

This format is identified by a specific format value between 0 and 7: see `custom formats`_.

Images with a custom format can be used as any other image.
For that, it requires some support at different levels depending on their usage:

* To convert an image to this format at compile-time and embed it, an extension of the image generator is necessary; see:ref:`section_imagegenerator_custom_format`.
* To create a new one at runtime, some native extension is necessary; see:ref:`section_buffered_image`.
* To use it as a source (to draw the image in another buffer), some native extension is necessary; see:ref:`section_buffered_image_drawer_custom`.
* To use it as a destination (to draw into the image), some native extension is necessary; see:ref:`section_buffered_image`.

.. _section_image_binary_raw:

Binary Format
=============

This format is not compatible with the Image Renderer and MicroUI.
It can be used by MicroUI addon libraries which provide their image management procedures.

Advantages:

* Encoding is known by platform.
* Compression is inherent to the format itself.

Disadvantages:

* This format cannot target a MicroUI Image (unsupported format).

.. _section_image_asis:

Original Input Format
=====================

See :ref:`section_image_unspecified_output`.

An image can be embedded without any conversion/compression.
This allows embedding the resource as it is to keep the source image characteristics (compression, bpp, etc.).
This option produces the same result as specifying an image as a resource in the MicroEJ launcher.

The following table lists the original formats that can be decoded at run-time and/or compile-time:

* Image Generator: the off-board tool that converts an image into an output format. All AWT `ImageIO`_ default formats are supported and always enabled.
* Front Panel: the decoders embedded by the simulator part. All AWT `ImageIO`_ default formats are supported but disabled by default.
* Runtime Decoders: the decoders embedded by the embedded part. 

.. table:: Original Image Formats

   +-----------------------------------------+-------------------+-----------------------------+----------------------------+
   | Type                                    | Image Generator   | Front Panel                 | Runtime Decoders           |
   +=========================================+===================+=============================+============================+
   | Graphics Interchange Format (GIF)       | yes               | yes [#note_disabledformat]_ | no [#note_runtimedecoder]_ |
   +-----------------------------------------+-------------------+-----------------------------+----------------------------+
   | Joint Photographic Experts Group (JPEG) | yes               | yes [#note_disabledformat]_ | no [#note_runtimedecoder]_ |
   +-----------------------------------------+-------------------+-----------------------------+----------------------------+
   | Portable Network Graphics (PNG)         | yes               | yes [#note_png]_            | yes [#note_png]_           |
   +-----------------------------------------+-------------------+-----------------------------+----------------------------+
   | Windows bitmap (BMP)                    | yes               | yes [#note_bmp]_            | yes/no [#note_bmp]_        |
   +-----------------------------------------+-------------------+-----------------------------+----------------------------+
   | Web Picture (WebP)                      | yes [#note_webp]_ | yes [#note_webp]_           | yes [#note_webpruntime]_   |
   +-----------------------------------------+-------------------+-----------------------------+----------------------------+

.. [#note_disabledformat] The formats are disabled by default; see:ref:`fp_ui_decoder`.
.. [#note_png] The PNG format is supported when the module ``PNG`` is selected in the platform configuration file (see :ref:`image_runtime_decoder`).
.. [#note_bmp] The Monochrome BMP is supported when the module ``BMPM`` is selected in the platform configuration file (see :ref:`image_runtime_decoder`); the `colored` BMP format is only supported by the Front Panel (disabled by default, see :ref:`fp_ui_decoder`).
.. [#note_webp] Install the tool ``com.microej.tool#imageio-webp-1.0.1`` from the :ref:`developer_repository` in the platform to support the WEBP format (see :ref:`section_image_generator_imageio` and :ref:`fp_ui_decoder`).
.. [#note_webpruntime] Install the C component ``com.microej.clibrary.thirdparty#libwebp-1.0.1`` in the BSP to support the WEBP format at runtime.
.. [#note_runtimedecoder] The UI-pack does not provide some runtime decoders for these formats, but a BSP can add its decoders (see :ref:`image_runtime_decoder`).

.. _section_image_gpu_raw:

GPU Format Support
==================

The MicroEJ formats :ref:`display <section_image_display_raw>`, :ref:`standard <section_image_standard_raw>` and :ref:`grayscale <section_image_grayscale_raw>` may be customized to be compatible with the hardware (usually GPU). 
It can be extended by one or several restrictions on the pixels array: 

* Its start address has to be aligned on a higher value than the number of bits-per-pixels. 
* A padding has to be added after each line (row stride).
* The MicroEJ format can hold a platform-dependent header between the MicroEJ format header (start of file) and the pixel array.
  The MicroEJ format is designed to let the platform encode and decode this additional header.
  This header is unnecessary and never used for Image Engine software algorithms.

.. note:: From the Image Engine point of view, the format stays a MicroEJ format, readable by the Image Engine Renderer.

Advantages:

* The GPU recognizes encoding.
* Drawing an image is often very fast.
* Supports opacity encoding.

Disadvantages:

* No compression: the image size in bytes is proportional to the number of pixels.
  The required memory is similar to :ref:`section_image_standard_raw` when no custom header exists. 

When the MicroEJ format holds another header (called ``custom_header``), the required memory is:
::

      required_memory = header + custom_header + (image_width * image_height) * bpp / 8;

The row stride allows adding some padding at the end of each line to start the next line at an address with a specific memory alignment; it is often required by hardware accelerators (GPU).
The row stride is, by default, a value in relation to the image width: ``row_stride_in_bytes = image_width * bpp / 8``.
Thanks to the Abstraction Layer API ``LLUI_DISPLAY_IMPL_getNewImageStrideInBytes``, it can be customized at image buffer creation.
The required memory becomes:
::

      required_memory = header + custom_header + row_stride * image_height;

.. figure:: images/uiFormat02.*
   :width: 50.0%

.. _BufferedImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html#
.. _ImageIO: https://docs.oracle.com/javase/7/docs/api/javax/imageio/ImageIO.html

.. XXX TODO XXX to replace by https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Format.html#CUSTOM_0
.. _custom formats: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.