.. _section_vg_matrix:

======
Matrix
======

Principle
=========

The Matrix module contains the C part of the MicroVG implementation, which manages arithmetics matrices.
This module is composed of only one element: an implementation of Abstraction Layer APIs to create and manipulate the matrices.

.. _section_vg_matrix_implementation:

Functional Description
======================

The Matrix module implements the framework of the MicroVG `Matrix`_. 
It provides Abstraction Layer APIs that manipulate the matrices: fill an identity matrix, do a translation, a rotation, or a scaling and concatenate two matrices.

A matrix is a 3x3 matrix, and its elements are encoded in ``float`` (32-bit values):

* matrix_memory[0] = matrix[0][0];
* matrix_memory[1] = matrix[0][1];
* matrix_memory[2] = matrix[0][2];
* matrix_memory[3] = matrix[1][0];
* matrix_memory[4] = matrix[1][1];
* matrix_memory[5] = matrix[1][2];
* matrix_memory[6] = matrix[2][0];
* matrix_memory[7] = matrix[2][1];
* matrix_memory[8] = matrix[2][2];

The buffer where the matrix is encoded is stored in the Managed heap. 

.. _Matrix: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/Matrix.html

.. _section_vg_matrix_llapi:

Abstraction Layer API
=====================

The Abstraction Layer APIs that have to be implemented are listed in the header file ``LLVG_MATRIX_impl.h`` (see :ref:`LLVG-MATRIX-API-SECTION`):

.. figure:: images/vg_llapi_matrix.*
   :alt: MicroVG Matrix Abstraction Layer
   :width: 200px
   :align: center

   Matrix Abstraction Layer API

* MicroVG library calls the BSP functions through the header file ``LLVG_MATRIX_impl.h``.
* The :ref:`C module MicroVG <section_vg_c_module_microvg>` provides a default implementation of this header file: ``LLVG_MATRIX_impl.c``. 
* This file is automatically copied in the BSP project when fetching the C module during the VEE Port build.

Use
===

The MicroVG Matrix APIs are available in the class ``ej.microvg.`` `Matrix`_.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
