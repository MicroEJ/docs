.. _section_vg_gradient:

========
Gradient
========

Principle
=========

The Gradient module contains the C part of the MicroVG implementation which manages linear gradients.
This module is composed of only one element: an implementation of the Low Level APIs to create gradient elements compatible with the hardware.

.. _section_vg_gradient_implementation:

Functional Description
======================

The Gradient module implements the MicroVG `LinearGradient <zzz_javadocurl_zzz/ej/microvg/LinearGradient.html>`_ framework. 
It provides Low Level APIs that consist in creating a linear gradient in platform specific format. 
After the gradient creation and encoding, the gradient data should not change when the application draws it: the encoded format should be the one used by the platform specific implementation (generally GPU).

A linear gradient is a succession of colors at different positions.
The colors from the MicroVG library implementation are encoded in 32-bit format: ARGB8888.
The color encoding in the gradient is platform specific implementation.

The buffer where the gradient is encoded is stored in the Java heap.
The buffer size is automatically increased by the MicroVG implementation on demand.

.. _section_vg_gradient_llapi:

Low Level API
=============

The Low Level APIs to implement are listed in the header file ``LLVG_GRADIENT_impl.h`` (see :ref:`LLVG-GRADIENT-API-SECTION`):

.. figure:: images/vg_llapi_gradient.*
   :alt: MicroVG Gradient Low Level
   :width: 200px
   :align: center

   Gradient Low Level API

Use
===

The MicroVG Gradient APIs are available in the class `ej.microvg.LinearGradient <zzz_javadocurl_zzz/ej/microvg/LinearGradient.html>`_.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
