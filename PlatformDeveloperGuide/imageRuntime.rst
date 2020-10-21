.. _section_image_runtime:

=============
Image Decoder
=============


Principle
=========

The Image Engine provides runtime decoders which allow the dynamic
loading of images without using the Image Generator (see
:ref:`section_image_generator`). The two main advantages are:

-  The original image is embedded as a resource with the MicroEJ
   Application.

-  The original image size in bytes is often smaller than a
   pre-generated image (especially in PNG mode).


Functional Description
======================

.. figure:: images/image-decoders2.*
   :alt: Image Decoder Principle
   :width: 750px
   :align: center

   Image Decoder Principle

Process overview (see too :ref:`section_image_core_process`)

1. The user specifies the images to embed as regular resources.

2. The original files are embedded as resources with the MicroEJ
   Application. The original files' data are linked into the FLASH
   memory.

3. When the Image Engine Core calls the decoder to load an image, it
   transforms the image into a raw format that is compatible with the
   display format. It may need some additional RAM to store some working
   buffers. At the end of the decoding step, the working buffers are
   freed: Only the decoded image memory needs to be retained.

4. When the Image Engine Core calls the decoder to free the image
   resources, the decoder frees the decoded image buffer area.


.. _image_internal_decoder:

Internal Decoders
=================

The UI extension provides two internal Image Decoders modules:

-  PNG Decoder: a full PNG decoder that implements the PNG format (
   ``https://www.w3.org/Graphics/PNG`` ). Regular, interlaced, indexed
   (palette) compressions are handled. The RAM used by the decoder is
   allocated outside the Java heap.

-  BMP Monochrome Decoder: .bmp format files that embed only 1 bit per
   pixel can be decoded by this decoder. The RAM used by the decoder to
   store the decoded image is outside the Java heap.


.. _image_external_decoder:

External Decoders
=================

Some additional decoders can be added. Implement the function
``LLDISPLAY_EXTRA_IMPL_decodeImage`` to add a new decoder (see
:ref:`LLDISPLAY-EXTRA-API-SECTION`).

The implementation must respect the following rules:

-  Fills the ``LLDISPLAY_SImage`` structure with the image
   characteristics: width, height and format.

   .. note::

      The output image format might be different than the expected
      format (given as argument). In this way, the display module will
      perform a conversion after the decoding step. During this
      conversion, an out of memory error can occur because the final RAW
      image cannot be allocated.

-  Allocates the RAW image data calling the function
   ``LLDISPLAY_UTILS_allocateRawImage``. This function will allocates
   the RAW image data space in the display working buffer according the
   RAW image format and size.

-  Decodes the image in the allocated buffer.

-  Waiting the end of decoding step before returning.


Dependencies
============

-  Image Engine Core module (see :ref:`section_image_core`)


.. _section_decoder_installation:

Installation
============

The Image Decoders modules are some additional modules to the Display
module. The decoders belong to distinct modules, and either or several
may be installed.

In the platform configuration file, check :guilabel:`UI` > :guilabel:`Image PNG Decoder`
to install the runtime PNG decoder. Check :guilabel:`UI` >
:guilabel:`Image BMP Monochrome Decoder` to install the runtime BMP monochrom
decoder.


Use
===

The MicroUI Image APIs are available in the class
``ej.microui.display.Image``. There is no specific API that uses a
runtime image. When an image has not been pre-processed (see
:ref:`section_image_generator`), the MicroUI Image APIs
``createImage*`` will load this image.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
