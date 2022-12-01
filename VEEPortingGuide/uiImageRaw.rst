.. _section_image_raw:

============
Image Format
============

The Image Engine makes the distinction between:

* the `input format`: how the original image is encoded, 
* the `output format`: how the image is used by the platform and/or the Image Renderer,
* the `embedded format`: how the image is embedded by the application. 

The Image Engine manages several standard formats in input: PNG, JPEG, BMP, etc. In addition, an input format may be custom (platform-dependent).
It manages two formats in output: the MicroEJ format and the binary format.
The Image Renderer manages only the MicroEJ format (:ref:`section_image_standard_raw`, :ref:`section_image_display_raw` and :ref:`section_image_gpu_raw`).
The binary output format (:ref:`section_image_binary_raw`) is fully platform-dependent and can be used to encode some images which are not usable by MicroUI standard API.

The output format is generated from the input format:

* by using the off-board tool :ref:`section_image_generator` at application compile-time 
* or by using a :ref:`runtime decoder <image_runtime_decoder>` of the :ref:`section_image_loader` at application run-time.

The embedded format may be the one of the output formats or the :ref:`original input format <section_image_asis>`.

.. _section_image_display_raw:

MicroEJ Format: Display
=======================

See :ref:`section_image_display_output`.

The display can hold a pixel encoding which is not standard (see :ref:`display_pixel_structure`).
The MicroEJ format can be customized to encode the pixel in the same encoding as the display.
The number of bits per pixels and the pixel bit organization is asked during the MicroEJ format generation and when the ``drawImage`` algorithms are running.
If the image to encode contains some transparent pixels, the output file will embed the transparency according to the display’s implementation capacity.
When all pixels are fully opaque, no extra information will be stored in the output file in order to free up some memory space.

.. note:: From the Image Engine point of view, the format stays a MicroEJ format, readable by the Image Renderer.

The required memory is similar to :ref:`section_image_standard_raw`.

.. _section_image_standard_raw:

MicroEJ Format: Standard
========================

See :ref:`section_image_standard_output`.

This format requires a small header (around 20 bytes) to store the image size (width, height), format, flags (is_transparent etc.), row stride, etc.
The required memory also depends on the number of bits per pixels of the MicroEJ format:
::

      required_memory = header + (image_width * image_height) * bpp / 8;

The pixels array is stored after the MicroEJ image file header. A padding between the header and the pixels array is added to force to start the pixels array at a memory address aligned on number of bits-per-pixels.

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

MicroEJ Format: Grayscale
=========================

See :ref:`section_image_grayscale_output`.

This format requires a small header (around 20 bytes) to store the image size (width, height), format, flags (is_transparent etc.), row stride, etc.
The required memory also depends on the number of bits per pixels of the MicroEJ format:
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

.. _section_image_gpu_raw:

MicroEJ Format: GPU
===================

The MicroEJ format may be customized to be compatible with the platform's GPU. It can be extended by one or several restrictions on the pixels array: 

* Its start address has to be aligned on a higher value than the number of bits-per-pixels. 
* A padding has to be added after each line (row stride).
* The MicroEJ format can hold a platform-dependent header, located between the MicroEJ format header (start of file) and the pixel array.
  The MicroEJ format is designed to let the platform encode and decode this additional header.
  For Image Engine software algorithms, this header is not needed and never used.

.. note:: From Image Engine point of view, the format stays a MicroEJ format, readable by the Image Engine Renderer.

Advantages:

* Encoding is recognized by the GPU.
* Drawing an image is often very fast.
* Supports opacity encoding.

Disadvantages:

* No compression: the image size in bytes is proportional to the number of pixels.
  The required memory is similar to :ref:`section_image_standard_raw` when there is no custom header. 

When the MicroEJ format holds another header (called ``custom_header``), the required memory is:
::

      required_memory = header + custom_header + (image_width * image_height) * bpp / 8;

The row stride allows to add some padding at the end of each line in order to start the next line at an address with a specific memory alignment; it is often required by hardware accelerators (GPU).
The row stride is by default a value in relation with the image width: ``row_stride_in_bytes = image_width * bpp / 8``.
It can be customized at image buffer creation thanks to the Low Level API ``LLUI_DISPLAY_IMPL_getNewImageStrideInBytes``.
The required memory becomes:
::

      required_memory = header + custom_header + row_stride * image_height;

.. figure:: images/uiFormat02.*
   :width: 50.0%

.. _section_image_binary_raw:

Binary Format
=============

This format is not compatible with the Image Renderer and MicroUI.
It can be used by MicroUI addon libraries which provide their own image management procedures.

Advantages:

* Encoding is known by platform.
* Compression is inherent to the format itself.

Disadvantages:

* This format cannot be used to target a MicroUI Image (unsupported format).

.. _section_image_asis:

Original Input Format
=====================

See :ref:`section_image_unspecified_output`.

An image can be embedded without any conversion / compression.
This allows to embed the resource as it is, in order to keep the source image characteristics (compression, bpp, etc.).
This option produces the same result as specifying an image as a resource in the MicroEJ launcher.

The following table lists the original formats that can be decoded at run-time and / or compile-time:

* Image Generator: the off-board tool that converts an image in an output format. All AWT `ImageIO`_ default formats are supported and always enabled.
* Front Panel: the decoders embedded by the simulator part. All AWT `ImageIO`_ default formats are supported but disabled by default.
* Runtime Decoders: the decoders embedded by the embedded part. 

.. table:: Original Image Formats

   +-----------------------------------------+-----------------+-------------+------------------+
   | Type                                    | Image Generator | Front Panel | Runtime Decoders |
   +=========================================+=================+=============+==================+
   | Graphics Interchange Format (GIF)       | yes             | yes (1)     | no (6)           |
   +-----------------------------------------+-----------------+-------------+------------------+
   | Joint Photographic Experts Group (JPEG) | yes             | yes (1)     | no (6)           |
   +-----------------------------------------+-----------------+-------------+------------------+
   | Portable Network Graphics (PNG)         | yes             | yes (2)     | yes (2)          |
   +-----------------------------------------+-----------------+-------------+------------------+
   | Windows bitmap (BMP)                    | yes             | yes (3)     | yes/no (3)       |
   +-----------------------------------------+-----------------+-------------+------------------+
   | Web Picture (WebP)                      | yes (4)         | yes (4)     | yes (5)          |
   +-----------------------------------------+-----------------+-------------+------------------+

* (1): The formats are disabled by default, see :ref:`fp_ui_decoder`.
* (2): The PNG format is supported when the module ``PNG`` is selected in the platform configuration file (see :ref:`image_runtime_decoder`).
* (3): The Monochrome BMP is supported when the module ``BMPM`` is selected in the platform configuration file (see :ref:`image_runtime_decoder`); the `colored` BMP format is only supported by the Front Panel (disabled by default, see :ref:`fp_ui_decoder`).
* (4): Install the tool ``com.microej.tool.imageio-webp`` from the :ref:`developer_repository` in the platform to support the WEBP format (see :ref:`section_image_generator_imageio` and :ref:`fp_ui_decoder`).

   .. code:: xml

      <dependency org="com.microej.tool" name="imageio-webp" rev="1.0.1"/>

* (5): Install the C component ``com.microej.clibrary.thirdparty.libwebp`` in the BSP to support the WEBP format at runtime.

   .. code:: xml

      <dependency org="com.microej.clibrary.thirdparty" name="libwebp" rev="1.0.1"/>

* (6): The UI-pack does not provide some runtime decoders for these formats but a BSP can add its own decoders (see :ref:`image_runtime_decoder`).

.. _ImageIO: https://docs.oracle.com/javase/7/docs/api/javax/imageio/ImageIO.html


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.