.. _section_vg_gradient:

========
Gradient
========

Principle
=========

The Gradient module contains the C part of the MicroVG implementation, which manages linear gradients.
This module is composed of only one element: an implementation of the Low-Level APIs to create gradient elements compatible with the hardware.

.. _section_vg_gradient_implementation:

Functional Description
======================

The Gradient module implements the framework of the MicroVG `LinearGradient <zzz_javadocurl_zzz/ej/microvg/LinearGradient.html>`_. 
It provides Low-Level APIs that consist in creating a linear gradient in a platform-specific format. 
After the gradient creation and encoding, the gradient data should not change when the application draws it: the encoded format should be used by the platform-specific implementation (generally GPU).

A linear gradient is a succession of colors at different positions.
The colors from the MicroVG library implementation are encoded in the 32-bit format: ARGB8888.
The color encoding in the gradient is a platform-specific implementation.

The buffer where the gradient is encoded is stored in the Java heap.
The MicroVG implementation on demand automatically increases the buffer size.

.. _section_vg_gradient_llapi:

Low-Level API
=============

The low-level APIs that have to be implemented are listed in the header file ``LLVG_GRADIENT_impl.h`` (see :ref:`LLVG-GRADIENT-API-SECTION`):

.. figure:: images/vg_llapi_gradient.*
   :alt: MicroVG Gradient Low Level
   :width: 400px
   :align: center

   Gradient Low-Level API

* MicroVG library calls the BSP functions through the header files ``LLVG_GRADIENT_impl.h``, ``LLVG_PATH_PAINTER_impl.h`` and  ``LLVG_FONT_PAINTER_impl.h``.
* The :ref:`C module MicroVG <section_vg_c_module_microvg>` provides a default implementation of ``LLVG_GRADIENT_impl.h``: it manages the gradient buffer creation and filling, then redirect the gradient encoding to ``microvg_gradient.h``.
* The :ref:`C module MicroVG-VGLte <section_vg_c_module_microvg>` provides an implementation of ``LLVG_PATH_PAINTER_impl.h``, ``LLVG_FONT_PAINTER_impl.h`` and ``microvg_gradient.h``: it encodes the gradient and implements the drawings over the Vivante VGLite library and Freetype.
* These files are automatically copied in the BSP project when fetching the C modules during the platform build.


Use
===

The MicroVG Gradient APIs are available in the class `ej.microvg.LinearGradient <zzz_javadocurl_zzz/ej/microvg/LinearGradient.html>`_.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
