.. _section_vg_gradient:

========
Gradient
========

Principle
=========

The Gradient module contains the C part of the MicroVG implementation, which manages linear gradients.
This module is composed of only one element: an implementation of the Abstraction Layer APIs to create gradient elements compatible with the hardware.

.. _section_vg_gradient_implementation:

Functional Description
======================

The Gradient module implements the framework of the MicroVG `LinearGradient`_. 
It provides Abstraction Layer APIs that consist in creating a linear gradient in a VEE Port-specific format. 
After the gradient creation and encoding, the gradient data should not change when the application draws it: the encoded format should be used by the VEE Port-specific implementation (generally GPU).

A linear gradient is a succession of colors at different positions.
The colors from the MicroVG library implementation are encoded in the 32-bit format: ARGB8888.
The color encoding in the gradient is a VEE Port-specific implementation.

The buffer where the gradient is encoded is stored in the Java heap.
The MicroVG implementation on demand automatically increases the buffer size.

.. _LinearGradient: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/LinearGradient.html

.. _section_vg_gradient_llapi:

Abstraction Layer API
=====================

There are two separate Abstraction Layer API header files (see :ref:`LLVG-GRADIENT-API-SECTION`):

* ``LLVG_GRADIENT_impl.h`` specifies the Abstraction Layer APIs used to create and encode the gradient.
* ``LLVG_PAINTER_impl.h`` lists the Abstraction Layer APIs called by  `VectorGraphicsPainter`_ to draw the path.

.. figure:: images/vg_llapi_gradient.*
   :alt: MicroVG Gradient Abstraction Layer
   :width: 400px
   :align: center

   Gradient Abstraction Layer API

* MicroVG library calls the BSP functions through the header files ``LLVG_GRADIENT_impl.h`` and ``LLVG_PAINTER_impl.h``.
* The :ref:`C module MicroVG <section_vg_c_module_microvg>` provides a default implementation of ``LLVG_GRADIENT_impl.h``: it manages the gradient buffer creation and filling, then redirect the gradient encoding to ``microvg_gradient.h``.
* This C module also provides an implementation of ``LLVG_PAINTER_impl.c`` that synchronizes the drawing with the MicroUI Graphics Engine and redirects the drawing itself to a third-party drawer.
* A C module dedicated to a GPU provides an implementation of ``LLVG_PAINTER_impl.h`` and ``microvg_gradient.h``: it encodes the gradient and implements the drawings over the GPU library.
* These files are automatically copied in the BSP project when fetching the C modules during the VEE Port build.

.. _VectorGraphicsPainter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorGraphicsPainter.html

Use
===

The MicroVG Gradient APIs are available in the class ``ej.microvg.`` `LinearGradient`_.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
