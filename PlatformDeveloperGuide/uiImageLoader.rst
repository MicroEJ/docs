.. _section_image_loader:

============
Image Loader
============

Principle
=========

The Image Loader module is an on-board engine that 

* retrieves image data that is ready to be displayed without needing additional runtime memory, 
* retrieves image data that is required to be converted into the format known by the Image Renderer (MicroEJ format),
* retrieves image in external memories (external memory loader),
* converts images in MicroEJ format, 
* creates a runtime buffer to manage MicroUI BufferedImage,
* manages dynamic images cycle life.

.. note:: The Image Loader is managing images to be compatible with Image Renderer. It does manage image in custom format (see :ref:`section_image_binary_raw`)

Functional Description
======================

1. The application is using one of three ways to create a MicroUI Image object.
2. The Image Loader creates the image according the MicroUI API, image location, image input format and image output format to be compatible with Image Renderer.
3. When the application closes the image, the Image Loader frees the RAM memory.

.. _section_image_loader_memory:

Memory
======

There are several ways to create a MicroUI Image. Except few specific cases, the Image Loader requires some RAM memory to store the image content in MicroEJ format. This format requires a small header as explained here: :ref:`section_image_standard_raw`.  It can be GPU compatible as explained here: :ref:`section_image_gpu_raw`. 

The heap size is application dependant. In MicroEJ application launcher, set its size in ``Libraries > MicroUI > Images heap size (in bytes)``. It will declare a section whose name is ``.bss.microui.display.imagesHeap``.

BufferedImage
=============

MicroUI application is able to create an image where it is allowed to draw into: the MicroUI ``BufferedImage``. The image format is the same than the display format; in other words, its number of bits-per-pixel and its pixel bits organization are the same. The display pixel format can standard or custom (see :ref:`display_pixel_structure`). To create this kind of image, the Image Loader has just to create a buffer in RAM whose size depends on the image size (see :ref:`section_image_display_raw`).

External Resource
=================

An image is retrieved by its path (except for ``BufferedImage``). The path describes a location in application classpath. The resource may be generated at same time than application (internal resource) or be external (external resource). The Image Loader is able to load some images located outside the CPU addresses' space range. It uses the External Resource Loader.

When an image is located in such memory, the Image Loader copies it into RAM (into the CPU addresses' space range). Then it considers the image as an internal resource: it can continue to load the image (see next chapters). The RAM section used to load the external image is automatically freed when the Image Loader do not need it again.

The image may be located in external memory but be available in CPU addresses' space ranges (byte-adressable). In this case the Image Loader considers the image as `internal` and does not need to copy its content in RAM memory. 

Image in MicroEJ Format
=======================

An image may be pre-processed (:ref:`section_image_generator`) and so already in the format compatible with Image Renderer: MicroEJ format. 

* When application is loading an image which is in such format and without specifiying another output format, the Image Loader has just to make a link between the MicroUI Image object and the resource location. No more runtime decoder or converter is required, and so no more RAM memory.
* When application specifies another output format than MicroEJ format encoded in the image, Image Loader has to allocate a buffer in RAM. It will convert the image in the expected MicroEJ format.
* When application is loading an image in MicroEJ format located in external memory, the Image Loader has to copy the image into RAM memory to be usable by Image Renderer.

.. _image_runtime_decoder:

Encoded Image
=============

An image can be encoded (PNG, JPEG etc.). In this case Image Loader asks to its Image Decoders module if a decoder is able to decode the image. The source image is not copied in RAM (expect for images located in an external memory). Image Decoder allocates the decoded image buffer in RAM first and then inflates the image. The image is encoded in MicroEJ format specified by the application, when specified. When not specified, the image in encoded in the default MicroEJ format specified by the Image Decoder itself.

.. _image_internal_decoder:

The UI extension provides two internal Image Decoders modules:

* PNG Decoder: a full PNG decoder that implements the PNG format (``https://www.w3.org/Graphics/PNG`` ). Regular, interlaced, indexed (palette) compressions are handled. 
* BMP Monochrome Decoder: .bmp format files that embed only 1 bit per pixel can be decoded by this decoder.

.. _image_external_decoder:

Some additional decoders can be added. Implement the function ``LLUI_DISPLAY_IMPL_decodeImage`` to add a new decoder. The implementation must respect the following rules:

-  Fills the ``MICROUI_Image`` structure with the image
   characteristics: width, height and format.

   .. note::

      The output image format might be different than the expected
      format (given as argument). In this way, the display module will
      perform a conversion after the decoding step. During this
      conversion, an out of memory error can occur because the final RAW
      image cannot be allocated.

-  Allocates the RAW image data calling the function
   ``LLUI_DISPLAY_allocateImageBuffer``. This function will allocates
   the RAW image data space in the display working buffer according the
   RAW image format and size.

-  Decodes the image in the allocated buffer.

-  Waiting the end of decoding step before returning.


Dependencies
============

-  Image Renderer module (see :ref:`section_image_core`)


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
