.. _section_image_core_process:

Functional Description
======================

.. figure:: ui/image/core/images/process.svg
   :alt: Image Engine Core Principle
   :width: 80.0%

   Image Engine Core Principle

Process overview:

1. The user specifies the pre-generated images to embed (see
   `??? <#section_image_generator>`__) and / or the images to embed as
   regular resources (see `??? <#section_image_runtime>`__)

2. The files are embedded as resources with the MicroEJ application. The
   files' data are linked into the FLASH memory.

3. When the MicroEJ application creates a MicroUI Image object, the
   Image Engine Core loads the image, calling the right sub Image Engine
   module (see `??? <#section_image_generator>`__ and
   `??? <#section_image_runtime>`__) to decode the specified image.

4. When the MicroEJ application draws this MicroUI Image on the display
   (or on another image), the decoded image data is used, and no more
   decoding is required, so the decoding is done only once.

5. When the MicroUI Image is no longer needed, it is garbage-collected
   by the platform; and the Image Engine Core asks the right sub Image
   Engine module (see `??? <#section_image_generator>`__ and
   `??? <#section_image_runtime>`__) to free the image working area.
