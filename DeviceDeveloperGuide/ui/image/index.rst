Images
======

The Image Engine is composed of:

-  The "Image Engine Core" module which is able to load and drawing
   simultaneously some pre-generated images and some dynamic images.

-  An "Image Generator" module, for converting standard image formats
   into the display image format before runtime (pre-generated images).

-  A set of "Image Decoder" modules, for converting standard image
   formats into the display image format at runtime. Each Image Decoder
   is an additional module of the main module "Image Engine".

.. toctree::
    :maxdepth: 2

    core/core
    generator/generator
    runtime/runtime
