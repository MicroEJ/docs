.. _image_external_decoder:

External Decoders
=================

Some additional decoders can be added. Implement the function
``LLDISPLAY_EXTRA_IMPL_decodeImage`` to add a new decoder (see
`??? <#LLDISPLAY-EXTRA-API-SECTION>`__).

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
