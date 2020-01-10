Functional Description
======================

.. figure:: ui/image/generator/images/static-image-gen2.svg
   :alt: Image Generator Principle
   :width: 80.0%

   Image Generator Principle

Process overview (see too `??? <#section_image_core_process>`__)

1. The user defines, in a text file, the images to load.

2. The Image Generator outputs a raw file for each image to convert (the
   raw format is display device-dependent).

3. The raw files are embedded as (hidden) resources within the MicroEJ
   application. The raw files' data are linked into the FLASH memory.

4. When the MicroEJ application creates a MicroUI Image object which
   targets a pre-generated image, the Image Engine Core has only to
   create a link from the MicroUI image object to the data in the FLASH
   memory. Therefore, the loading is very fast; only the image data from
   the FLASH memory is used: no copy of the image data is sent to the
   RAM first.

5. When the MicroUI Image is no longer needed, it is garbage-collected
   by the platform, which just deletes the useless link to the FLASH
   memory.
