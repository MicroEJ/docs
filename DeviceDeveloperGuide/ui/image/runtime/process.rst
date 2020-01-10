Functional Description
======================

.. figure:: ui/image/runtime/images/image-decoders2.svg
   :alt: Image Decoder Principle
   :width: 80.0%

   Image Decoder Principle

Process overview (see too `??? <#section_image_core_process>`__)

1. The user specifies the images to embed as regular resources.

2. The original files are embedded as resources with the MicroEJ
   application. The original files' data are linked into the FLASH
   memory.

3. When the Image Engine Core calls the decoder to load an image, it
   transforms the image into a raw format that is compatible with the
   display format. It may need some additional RAM to store some working
   buffers. At the end of the decoding step, the working buffers are
   freed: Only the decoded image memory needs to be retained.

4. When the Image Engine Core calls the decoder to free the image
   resources, the decoder frees the decoded image buffer area.
