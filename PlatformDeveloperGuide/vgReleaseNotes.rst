.. _section_vg_releasenotes:

=============
Release Notes
=============

MicroEJ Architecture Compatibility Version
==========================================

The current VG Pack version is 1.1.0.
The following table describes the compatibility ranges between MicroEJ VG Packs and MicroEJ UI Packs.

+---------------+-----------------+------------------+
| VG Pack Range | UI Pack Range   | Comment          |
+===============+=================+==================+
| 1.1.0         | [13.3.0-14.0.0[ | Internal feature |
+---------------+-----------------+------------------+
| [1.0.0-1.0.1] | [13.2.0-14.0.0[ |                  |
+---------------+-----------------+------------------+

.. _section_vg_api:

Foundation Libraries
====================

The following table describes Foundation Libraries API versions implemented in MicroEJ VG Packs.

.. list-table:: MicroVG API Implementation
   :widths: 20 10
   :header-rows: 1

   * - VG Pack Range
     - MicroVG
   * - 1.1.0
     - 1.1.0
   * - [1.0.0-1.0.1]
     - 1.0.0

.. _section_vg_releasenotes_cmodule:

C modules
=========

Several C modules are available on `MicroEJ Central Repository <zzz_centralrepourl_zzz/modules>`_  and `Developer Repository <zzz_devrepourl_zzz/microej-developer-repository-release>`_

.. _section_vg_c_module_microvg:

MicroVG
-------

The C module `<zzz_centralrepourl_zzz/modules/com/microej/clibrary/llimpl/microvg>`_ provides default implementations for:

* ``LLVG_MATRIX_impl.h`` (see Matrix module's :ref:`section_vg_matrix_llapi`): a basic software implementation,
* ``LLVG_PATH_impl.h`` (see Path module's :ref:`section_vg_path_llapi`): a generic implementation that manages the command buffer's life cycle and dispatches the command encoding to a 3rd-party header file ``microvg_path.h``,
* ``LLVG_GRADIENT_impl.h`` (see Gradient module's :ref:`section_vg_gradient_llapi`): a generic implementation that manages the gradient buffer's life cycle and dispatches the gradient encoding to a 3rd-party header file ``microvg_gradient.h``,
* ``LLVG_FONT_impl.h`` (see Font module's :ref:`section_vg_font_llapi`): an implementation of vector font over Freetype: open font file and retrieve font's characteristics.

Freetype
--------

The C module `<zzz_centralrepourl_zzz/modules/com/microej/clibrary/thirdparty/freetype>`_ provides a fork of Freetype 2.11.0 and compatible with the C module `MicroVG`.

Harfbuzz
--------

The C module `<zzz_centralrepourl_zzz/modules/com/microej/clibrary/thirdparty/harfbuzz>`_ provides a fork of Harfbuzz 4.2.1 and compatible with the C module `MicroVG`.

MicroVG-VGLite
--------------

The C module `<zzz_devrepourl_zzz/com/microej/clibrary/llimpl/microvg-vglite>`_ provides default implementations for:

* ``LLVG_PATH_PAINTER_impl.h`` (see Path module's :ref:`section_vg_path_llapi`) and ``microvg_path.h`` (see :ref:`section_vg_c_module_microvg`): the painter implementation for NXP i.MX RT500 (that provides Vivante VGLITE GPU),
* ``LLVG_FONT_PAINTER_impl.h`` (see Font module's :ref:`section_vg_font_llapi`): the font painter implementation for NXP i.MX RT500 (that provides Vivante VGLITE GPU).

This module requires the C module `MicroUI over VGLite`: `<zzz_devrepourl_zzz/com/microej/clibrary/llimpl/microui-vglite>`_

Compatibility
-------------

The C module `MicroVG-VGLite` fetches automatically by transitivity the other C modules.
No need to fetch explicitly the other modules.
An update of this C module updates (if necessary) the other C modules.
The following table describes the compatibility versions between this C module and the MicroEJ VG Packs:

+-----------------------------+---------------+
| MicroVG-VGLite Module Range | VG Pack Range |
+=============================+===============+
| 3.0.0                       | 1.1.0         |
+-----------------------------+---------------+
| [1.0.0-2.0.0] *deprecated*  | n/a           |
+-----------------------------+---------------+

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
