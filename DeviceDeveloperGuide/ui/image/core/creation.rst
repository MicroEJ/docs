Image Identifier
================

Before loading an image calling the right sub module, the Image Engine
Core module tries first to attribute a unique identifier to the future
decoded image. This identifier will be used to retrieve the image after
the decoding step, in order to draw it and free it.

This identifier also targets some metadata for the image (same size for
all images, specific to the Display module). An identifier is reserved
for an image as long as the image is used by the MicroEJ application.
When the MicroUI Image is no longer needed, it is garbage collected by
the platform. The identifier (and its meta data memory space) is freed.
Thus, a new image can use this identifier.

To prevent some C allocation at runtime, the number of identifiers and
the memory space useful to store the image metadata are allocated at
compile time. By consequence the available number of identifiers is
limited. The MicroEJ launcher of the MicroEJ application has to specify
the number of identifiers.

When the limit of identifiers is reached, the MicroUI library throws an
``OutOfMemoryError``, error code ``-5``. In this case try to augment the
number of concurrent images in the MicroEJ launcher or try to remove the
links on useless MicroUI Image objects.
