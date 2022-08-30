.. _section_vg_path:

====
Path
====

Principle
=========

The Path module contains the C part of the MicroVG implementation, which manages vector paths.
This module is composed of two elements: 

* an implementation of Low-Level APIs to create path elements compatible with the hardware,
* an implementation of Low-Level APIs for MicroVG drawings.

.. _section_vg_path_implementation:

Functional Description
======================

The Path module implements the framework of the MicroVG `Path <zzz_javadocurl_zzz/ej/microvg/Path.html>`_. 
It provides Low-Level APIs that create and merge some paths in a platform-specific format. 
After the path creation and encoding, the path data should not change when the application draws it: the encoded format should be used by the platform-specific implementation (generally GPU).

A path is a succession of commands.
The command encoding is implementation specific; however, the ``float`` format is recommended.

List of commands:

* ``LLVG_PATH_CMD_CLOSE``: MicroVG "CLOSE" command.
* ``LLVG_PATH_CMD_MOVE``: MicroVG "MOVE ABS" command.
* ``LLVG_PATH_CMD_MOVE_REL``: MicroVG "MOVE REL" command.
* ``LLVG_PATH_CMD_LINE``: MicroVG "LINE ABS" command.
* ``LLVG_PATH_CMD_LINE_REL``: MicroVG "LINE REL" command.
* ``LLVG_PATH_CMD_QUAD``: MicroVG "QUAD ABS" command.
* ``LLVG_PATH_CMD_QUAD_REL``: MicroVG "QUAD REL" command.
* ``LLVG_PATH_CMD_CUBIC``: MicroVG "CUBIC ABS" command.
* ``LLVG_PATH_CMD_CUBIC_REL``: MicroVG "CUBIC REL" command.

The buffer where the commands are encoded is stored in the Java heap.
The buffer size is automatically increased by the MicroVG implementation when no more commands can be added.

A path is drawn with a color or with a :ref:`linear gradient<section_vg_gradient>`.

.. _section_vg_path_llapi:

Low-Level API
=============

There are two separate Low Level API header files (see :ref:`LLVG-PATH-API-SECTION`):

* ``LLVG_PATH_impl.h`` specifies the Low-Level APIs used to create and encode the path.
* ``LLVG_PATH_PAINTER_impl.h`` lists the Low-Level APIs called by  `VectorGraphicsPainter <zzz_javadocurl_zzz/ej/microvg/VectorGraphicsPainter.html>`_ to draw the path.

.. figure:: images/vg_llapi_path.*
   :alt: MicroVG Path Low Level
   :width: 400px
   :align: center

   Path Low-Level API

* MicroVG library calls the BSP functions through the header files ``LLVG_PATH_impl.h`` and ``LLVG_PATH_PAINTER_impl.h``.
* The :ref:`C module MicroVG <section_vg_c_module_microvg>` provides a default implementation of ``LLVG_PATH_impl.h``: it manages the path buffer creation and filling, then redirect the command encoding to ``microvg_path.h``.
* The :ref:`C module MicroVG-VGLite <section_vg_c_module_microvg>` provides an implementation of ``LLVG_PATH_PAINTER_impl.h`` and ``microvg_path.h``: it encodes the path commands and implements the drawings over the Vivante VGLite library.
* The drawer also manages the :ref:`section_vg_gradient`.
* These files are automatically copied in the BSP project when fetching the C modules during the platform build.

Use
===

The MicroVG Path APIs are available in the class `ej.microvg.Path <zzz_javadocurl_zzz/ej/microvg/Path.html>`_.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
