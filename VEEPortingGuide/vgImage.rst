.. _section_vg_image:

=====
Image
=====

Principle
=========

XXX TODO XXX

.. _section_vg_image_implementation:

Functional Description
======================

XXX TODO XXX

image (avd/svg or avd runtime or bvi) -> raw image -> renderer

.. _VectorImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorImage.html

Compile-time Image
==================

XXX TODO XXX

* avd / svg
* image generator extension
* vectorimages.list
* output format VGF, AVD etc.

Runtime Image
=============

XXX TODO XXX

* AVD simplified (see upper)
* addon lib
* external resource

BufferedVectorImage
===================

XXX TODO XXX

* microui custom format 4
* store GPU commands
* microui drawing with GPU -> available in bvi

.. _section_vg_image_llapi:

Abstraction Layer API
=====================

XXX TODO XXX

.. _VectorGraphicsPainter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorGraphicsPainter.html

Use
===

The MicroVG Font APIs are available in the class ``ej.microvg.`` `VectorImage`_.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
