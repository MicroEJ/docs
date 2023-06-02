.. _section_vg_image:

=====
Image
=====

Principle
=========

The Image module contains the part of the MicroVG implementation, which manages vectorial images.
This module is composed of several elements: 

* an :ref:`offline tool <section_vg_image_generator>` that converts standard vector images in a binary format compatible with the :ref:`section_vg_image_engine`,
* an implementation of Abstraction Layer APIs to manipulate image files,
* an implementation of Abstraction Layer APIs for MicroVG drawings.

Compile-time Image
==================

The Image module implements the MicroVG `VectorImage`_ framework. 
It provides an offline tool that consist of opening and decoding an image file and some Abstraction Layer APIs that consist of manipulating the image at runtime. 

A compile-time image file:

* is either an AVD (Android Vector Drawable) or a Scalable Vector Graphics (SVG), 
* is identified by the resource name,
* is encoded in a binary format compatible with the :ref:`image renderer <section_vg_image_engine>`,
* can be stored as internal resource or external (see :ref:`chapter.microej.applicationResources`, but only in a byte-addressable memory),
* is an immutable image: the application cannot draw into.

.. _section_vg_image_generator:

Image Generator
---------------

The offline tool is an extension of the MicroUI :ref:`section_image_generator`.
This tool is automatically installed during the VEE Port build.

The tool converts :

* The Android Vector Drawable (AVD): this kind of images can hold linear gradients, animations on colors, opacity, path transformations, etc. 
* The Scalable Vector Graphics (SVG): this kind of images is partially supported: linear gradients but no animations. It is very advised to convert the SVG files in AVD files before using the Image Converter tool.

The tool generates a binary file (a RAW file) compatible with the :ref:`section_vg_image_engine`.
The RAW file consists of a series of vector paths and animations.

To list the images to convert, the tool uses the application list files whose extension is ``.vectorimage.list``. 
The generator provides an option to encode the path data (the path's points): it can be stored on signed 8, 16, 32 bit words or in ``float`` format.
Respectively, the options are ``VG8``, ``VG16``, ``VG32`` and ``VGF``.

This is an example of ``.vectorimage.list`` files:

.. code-block::

   # convert an AVDin float format
   /avd_image_1.xml:VGF
   # convert an AVD in signed 16-bit format
   /path/to/avd_image_2.xml:VG16
   # convert a SVG in signed 8-bit format
   /svg_image.svg:VG8

MicroVG Library
---------------

To load this kind of images, the application has to call `VectorImage.getImage()`_.
This API takes the image relative path: ``/avd_image_1.xml`` or ``/path/to/avd_image_2.xml`` or ``/svg_image.svg``.

The implementation uses the Abstraction Layer API to retrieve the image. 
No data is stored in the Java heap (expect the VectorImage object itself).

Abstraction Layer API
---------------------

The implementation of the MicroVG library is specific to the target (the GPU): the format of the RAW paths, gradients and animations are GPU compliant.

Refer to :ref:`section_vg_cco` for more information.

Simulation
----------

The implementation of the MicroVG library is included in the VG Pack.
No specific support is required to retrieve and use the image.

Resource Vector Image
=====================

The Image module implements the MicroVG `ResourceVectorImage`_ framework. 

External Memory
---------------

MicroVG provides the API `ResourceVectorImage.loadImage()`_.
This is an extension of the compile-time images (the concepts are exactly the same) but it allows to load a RAW image stored in an external memory which is not byte-addressable.

However, the RAW image data must be copied into a byte-addressable memory to use it. 
No data is stored in the Java heap: the image data should be copied into the MicroUI image heap.
The implementation is responsible for the image's cycle life: allocation and release (already implemented in the :ref:`section_vg_cco`).

Filtered Image
--------------

MicroVG provides the API `VectorImage.filterImage()`_ to decline an image in another image using a 4x5 color matrix.
The resulted image is a copy of the original image (plus color transformation) stored in the MicroUI images heap.
The implementation is responsible for the image's cycle life: allocation and release (already implemented in the :ref:`section_vg_cco`).

Buffered Vector Image
=====================

This kind of image is a `ResourceVectorImage`_ where the application can draw into.
More specifically, the drawings are not *performed* but *stored*.

The concept consists to store the compatible MicroUI drawings [#note_uibvi]_ and all MicroVG drawings into a commands list.
The application can play this list of commands applying (or not) a global transformation.

.. note:: The implementation uses the concept of MicroUI :ref:`custom <section_image_custom_raw>` format (the custom ``Format.CUSTOM_7``).

The way to register the drawing commands is hardly linked to the targeted GPU:

* the paths and gradients are stored to be used directly by the GPU when rendering the image (prevent runtime modifications before the image rendering)
* according to the GPU capabilities (a GPU may be able to draw a MicroUI anti-aliased line but not an aliased line), some MicroUI drawing API may be implemented or not (see :ref:`section_buffered_image`).

By consequence, the implementation is dedicated to the GPU.
The :ref:`section_vg_cco` provide some implementations and the Front Panel (for the Simulation) features the same limitations than the embedded side (it is not possible to store a MicroUI drawing in the simulator if the embedded side is not able to perform it).

.. [#note_uibvi] The compatible MicroUI drawings depends on the GPU Port, see :ref:`section_vg_cco`.

Runtime Image
=============

The third-party library `VectorImageLoader`_ features an API to load an Android Vector Drawable (AVD) at runtime.
This API creates a `ResourceVectorImage`_ 

This library uses a simple XML parser (for performance and footprint convenience) that limits the compatibility with the AVD specification.
For instance, this loader does not manage the animations.

The :ref:`Vector Image Generator <section_vg_image_generator>` can generate a compatible AVD file, in the ``.vectorimage.list``, use ``AVD`` as output format.

.. code-block::

   # convert an AVD in compatible AVD format
   /avd_image.xml:AVD
   # convert a SVG in compatible AVD format
   /svg_image.svg:AVD

.. _section_vg_image_engine:

Rendering Engine
================

The Vector Image Rendering Engine has the responsibility to draw the vector images.
The destination is the display buffer, a MicroUI BufferedImage or a MicroVG BufferedVectorImage.

Three transformations can be applied when drawing a vector image:

* a global path transformation (3x3 matrix)
* a color transformation (4x5 color matrix)
* an opacity (value between 0 and 255)

The :ref:`section_vg_cco` and the Front Panel already implement this engine.

Use
===

The MicroVG Font APIs are available in the class ``ej.microvg.`` `VectorImage`_.


.. _VectorImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorImage.html
.. _VectorImage.getImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorImage.html#getImage-java.lang.String-
.. _VectorImage.filterImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorImage.html#filterImage-float:A-
.. _ResourceVectorImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/ResourceVectorImage.html
.. _ResourceVectorImage.loadImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/ResourceVectorImage.html#loadImage-java.lang.String-
.. _VectorGraphicsPainter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorGraphicsPainter.html
.. _VectorImageLoader: https://forge.microej.com/artifactory/microej-developer-repository-release/ej/library/ui/vectorimage-loader

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
