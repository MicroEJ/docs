.. _section_vg_image:

=====
Image
=====

Principle
=========

The Image module contains the part of the MicroVG implementation which manages vectorial images.
This module is composed of several elements: 

* an :ref:`offline tool <section_vg_image_generator>` that converts standard vector images in a binary format compatible with the :ref:`section_vg_image_engine`,
* an implementation of Abstraction Layer APIs to manipulate image files,
* an implementation of Abstraction Layer APIs for MicroVG drawings.

Compile-time Image
==================

The Image module implements the MicroVG `VectorImage`_ framework.
It provides an offline tool that consists in opening and decoding an image file and some Abstraction Layer APIs that manipulate the image at runtime.

A compile-time image file:

* is either an AVD (Android Vector Drawable) or a Scalable Vector Graphics (SVG), 
* is identified by the resource name,
* is encoded in a binary format compatible with the :ref:`image renderer <section_vg_image_engine>`,
* can be stored as an internal resource or an external one (see :ref:`section_vg_image_external`),
* is an immutable image: the application cannot draw into it.

.. _section_vg_image_generator:

Image Generator
---------------

The offline tool is an extension of the MicroUI :ref:`section_image_generator`.
This tool is automatically installed during the VEE Port build.

The tool converts :

* The Android Vector Drawable (AVD): this kind of image can hold linear gradients, animations on colors, opacity, path transformations, etc. 
* The Scalable Vector Graphics (SVG): this kind of image is partially supported: linear gradients but no animations. It is advised to convert the SVG files into AVD files before using the Image Converter tool.

The tool generates a binary (RAW) file compatible with the :ref:`section_vg_image_engine`.
The RAW file consists in a series of vector paths and animations.

To list the images to convert, the tool uses the application list files whose extension is ``.vectorimage.list``. 
The generator provides an option to encode the path data (the path's points): it can be stored on signed 8, 16, 32-bit words or in ``float`` format.
Respectively, the options are ``VG8``, ``VG16``, ``VG32`` and ``VGF``.

This is an example of a ``vectorimage.list`` file:

.. code-block::

   # Convert an AVD in float format
   /avd_image_1.xml:VGF
   # Convert an AVD in signed 16-bit format
   /path/to/avd_image_2.xml:VG16
   # Convert an SVG in signed 8-bit format
   /svg_image.svg:VG8

MicroVG Library
---------------

To load this kind of image, the application has to call `VectorImage.getImage()`_.
This API takes the image relative path: ``/avd_image_1.xml`` or ``/path/to/avd_image_2.xml`` or ``/svg_image.svg``.

The implementation uses the Abstraction Layer API to retrieve the image. 
No data is stored in the Java heap (except the `VectorImage`_ object's instance).

Resource Vector Image
=====================

The Image module implements the MicroVG `ResourceVectorImage`_ framework. 

Filtered Image
--------------

MicroVG `VectorImage.filterImage()`_ API allows to transform an image using a 4x5 color matrix.
The result of the image transformation is stored in the MicroUI :ref:`images_heap`.
MicroVG ports for dedicated GPU (Low Level implementation) are responsible of the deallocation of this generated image.
An implementation is available for :ref:`MicroVG Over VGLite<section_vg_c_module_microvg_vglite>`.

.. _section_vg_image_external:

External Memory
---------------

Principle
~~~~~~~~~

MicroVG provides the API `ResourceVectorImage.loadImage()`_.
This is an extension of the compile-time images (the concepts are exactly the same), but it allows a load of a RAW image stored in an external memory that is not byte-addressable.

An external image loaded from byte-addressable memory is processed the same way than any compile-time image.
For an image loaded from an external memory which is not byte-addressable, its data must be copied into byte-addressable memory before the image can be used for drawings.
By default (see :ref:`section_vg_cco`), the image data is copied into MicroUI :ref:`images_heap`.
The implementation is responsible for the image's lifecycle: allocation and release (already implemented in the :ref:`section_vg_cco`).

Configuration File
~~~~~~~~~~~~~~~~~~

Like compile-time images, the :ref:`section_vg_image_generator` uses a list file whose extension is ``.externvectorimages.list``. 
The rules are exactly the sames than the compile-time images.

Process
~~~~~~~

The process to open a Vector Image from an external memory is exactly the same than the loading of :ref:`an external MicroUI Image<section_image_external_memory>` . 

The following steps describe how to setup the loading of an external resource from the application:

1. Add the image to the application project resources (typically in the source folder ``src/main/resources`` and in the package ``images``).
2. Create / open the configuration file (e.g. ``application.externvectorimages.list``).
3. Add the relative path of the image and its output format (e.g. ``/images/myImage.avd:VGF`` see :ref:`section_vg_image_generator`).
4. Build the application: the Image Generator converts the image in RAW format in the external resources folder (``[application_output_folder]/externalResources``).
5. Deploy the external resources to the external memory (SDCard, flash, etc.) of the device.
6. (optional) Configure the :ref:`section_externalresourceloader` to load from this source.
7. Build the application and run it on the device.
8. The application loads the external resource using `ResourceVectorImage.loadImage()`_.
9. The image loader looks for the image and copies it in the :ref:`images heap<section_image_loader_memory>` (no copy if the external memory is byte-addressable).
10. The external resource is immediately closed: the image's bytes have been copied in the images heap, or the image's bytes are always available (byte-addressable memory).
11. The application can use the image.
12. The application closes the image: the image is removed from the image heap.

Simulation
~~~~~~~~~~

The Simulator automatically manages the external resources like internal resources.
All images listed in ``*.externvectorimages.list`` files are copied in the external resources folder, and this folder is added to the Simulator's classpath.

Buffered Vector Image
=====================

This image is a `ResourceVectorImage`_ that the application can draw into.
More specifically, the drawings are not *performed* but *stored*.

The concept consists in storing the compatible MicroUI drawings [#note_uibvi]_ and all MicroVG drawings into a command list.
The application can then play this list of commands applying (or not) a global transformation.

.. note:: The implementation uses the concept of MicroUI :ref:`custom <section_image_custom_raw>` format (the custom ``Format.CUSTOM_7``).

The way to register the drawing commands is strongly linked to the targeted GPU:

* The paths and gradients are stored to be used directly by the GPU to render the image (prevent runtime modifications before the image rendering).
* Depending on the GPU capabilities (a GPU may be able to draw a MicroUI anti-aliased line but not an aliased line), some MicroUI drawing API may be implemented (see :ref:`section_buffered_image`).

As a consequence, the implementation is dedicated to the GPU.
The :ref:`section_vg_cco` provide some implementations, and the Front Panel (for the Simulation) features the same limitations as the embedded side (it is not possible to store a MicroUI drawing in the simulator if the embedded side is not able to perform it).

.. [#note_uibvi] The compatible MicroUI drawings depend on the GPU Port; see:ref:`section_vg_cco`.

Runtime Image
=============

The third-party library `VectorImageLoader`_ features an API to load an Android Vector Drawable (AVD) at runtime.
This API creates a `ResourceVectorImage`_ 

This library uses a simple XML parser (for performance and footprint convenience) that limits compatibility with the AVD specification.
For instance, this loader does not manage the animations.

The :ref:`Vector Image Generator <section_vg_image_generator>` can generate a compatible AVD file in the ``.vectorimage.list``, using ``AVD`` as output format.

.. code-block::

   # Convert an AVD into a compatible AVD format
   /avd_image.xml:AVD
   # Convert an SVG into a compatible AVD format
   /svg_image.svg:AVD

.. _section_vg_image_engine:

Rendering Engine
================

The Vector Image Rendering Engine has the responsibility of drawing the vector images.
The destination is the display buffer, a MicroUI :ref:`BufferedImage<section_buffered_image>` or a MicroVG BufferedVectorImage.

Three transformations can be applied when drawing a vector image:

* a global path transformation (3x3 matrix)
* a color transformation (4x5 color matrix)
* an opacity (value between 0 and 255)

The :ref:`section_vg_cco` and the Front Panel already implement this engine.

.. _section_vg_image_llapi:

Abstraction Layer API
=====================

There are two separate Abstraction Layer API header files:

* ``LLVG_BVI_impl.h`` specifies the Abstraction Layer APIs used to open and manage the BufferedVectorImage cycle-life.
* ``LLVG_PAINTER_impl.h`` lists the Abstraction Layer APIs called by  `VectorGraphicsPainter`_ to draw an image (compile-time, runtime, or buffered vector image).

.. figure:: images/vg_llapi_bvi.*
   :alt: MicroVG BufferedVectorImage Abstraction Layer
   :width: 400px
   :align: center

   Image Abstraction Layer API

* MicroVG library calls the BSP functions through the header files ``LLVG_BVI_impl.h`` and ``LLVG_PAINTER_impl.h``.
* A C module dedicated to a GPU provides an implementation of ``LLVG_BVI_impl.h`` and ``LLVG_PATH_PAINTER_impl.h``: the implementation is specific to the target (the GPU): the format of the RAW paths, gradients, and animations are GPU compliant.
* These files are automatically copied in the BSP project when fetching the C modules during the VEE Port build.

Simulation
==========

The implementation of the MicroVG library is included in the VG Pack.
No specific support is required to retrieve and use the images.

Use
===

The MicroVG Font APIs are available in the class ``ej.microvg.`` `VectorImage`_.


.. _VectorImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorImage.html
.. _VectorImage.getImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorImage.html#getImage-java.lang.String-
.. _VectorImage.filterImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorImage.html#filterImage-float:A-
.. _ResourceVectorImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/ResourceVectorImage.html
.. _ResourceVectorImage.loadImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/ResourceVectorImage.html#loadImage-java.lang.String-
.. _VectorGraphicsPainter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorGraphicsPainter.html
.. _VectorImageLoader: 

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
