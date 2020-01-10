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
