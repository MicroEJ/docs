External Resources
==================

The Image Engine Core is able to load some images located outside the
CPU addresses' space range. It uses the External Resource Loader.

When an image is located in such memory, the Image Engine Core copies it
into RAM (into the CPU address space range). Then it calls the right sub
Image Engine module (see `??? <#section_image_generator>`__ and
`??? <#section_image_runtime>`__) to decode the specified image.

The RAM section used to load the external image is automatically freed
when the Image Engine Core and its modules do not need it again.
