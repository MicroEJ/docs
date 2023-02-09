.. include:: uiReplaces.rst

.. _section_ui_releasenotes:

=============
Release Notes
=============

MicroEJ Architecture Compatibility Version
==========================================

The current UI Pack version is |UIPACKVERSION|.
The following tables describe the compatibility ranges between MicroEJ UI Packs and MicroEJ Architectures.

Standard Versions
"""""""""""""""""

+-----------------+--------------------+---------------------------------------------------------+
| UI Pack Range   | Architecture Range | Comment                                                 |
+=================+====================+=========================================================+
| [13.0.0-13.4.1] | [7.13.0-8.0.0[     | SNI 1.3                                                 |
+-----------------+--------------------+---------------------------------------------------------+
| [12.0.0-12.1.5] | [7.11.0-8.0.0[     | Move Front Panel in MicroEJ Architecture                |
+-----------------+--------------------+---------------------------------------------------------+
| [11.0.0-11.2.0] | [7.0.0-8.0.0[      | SNI Callback feature                                    |
+-----------------+--------------------+---------------------------------------------------------+
| [9.3.1-10.0.2]  | [6.13.0-7.0.0[     | ``LLEXT`` link error with Architecture 6.13+ and UI 9+  |
+-----------------+--------------------+---------------------------------------------------------+
| [9.2.0-9.3.0]   | [6.12.0-6.13.0[    | SOAR can exclude some resources                         |
+-----------------+--------------------+---------------------------------------------------------+
| [9.1.0-9.1.2]   | [6.8.0-6.12.0[     | Internal scripts                                        |
+-----------------+--------------------+---------------------------------------------------------+
| [8.0.0-9.0.2]   | [6.4.0-6.12.0[     | Manage external memories like byte addressable memories |
+-----------------+--------------------+---------------------------------------------------------+
| [6.0.0-7.4.7]   | [6.1.0-6.12.0[     |                                                         |
+-----------------+--------------------+---------------------------------------------------------+

Maintenance Versions
""""""""""""""""""""

+-----------------+----------------------+--------------------+----------------------+
| UI Pack Version | UI Pack Base Version | Architecture Range | Comment              |
+=================+======================+====================+======================+
| (maint) 8.0.0   | 7.4.7                | [7.0.0-8.0.0[      | SNI Callback feature |
+-----------------+----------------------+--------------------+----------------------+

.. _section_ui_api:

Foundation Libraries
====================

The following table describes Foundation Libraries API versions implemented in MicroEJ UI Packs.

.. list-table:: MicroUI API Implementation
   :widths: 20 10 10
   :header-rows: 1

   * - UI Pack Range
     - MicroUI
     - Drawing
   * - [13.2.0-13.4.1]
     - `3.1.1 <https://repository.microej.com/modules/ej/api/microui/3.1.1/>`_
     - `1.0.4 <https://repository.microej.com/modules/ej/api/drawing/1.0.4/>`_
   * - 13.1.0
     - `3.1.0 <https://repository.microej.com/modules/ej/api/microui/3.1.0/>`_
     - `1.0.3 <https://repository.microej.com/modules/ej/api/drawing/1.0.3/>`_
   * - [13.0.4-13.0.7]
     - `3.0.3 <https://repository.microej.com/modules/ej/api/microui/3.0.3/>`_
     - `1.0.2 <https://repository.microej.com/modules/ej/api/drawing/1.0.2/>`_
   * - 13.0.3
     - 3.0.2
     - 1.0.1
   * - [13.0.1-13.0.2]
     - `3.0.1 <https://repository.microej.com/modules/ej/api/microui/3.0.1/>`_
     - `1.0.0 <https://repository.microej.com/modules/ej/api/drawing/1.0.0/>`_
   * - 13.0.0
     - `3.0.0 <https://repository.microej.com/modules/ej/api/microui/3.0.0/>`_
     - `1.0.0 <https://repository.microej.com/modules/ej/api/drawing/1.0.0/>`_
   * - [12.1.0-12.1.5]
     - `2.4.0 <https://repository.microej.com/modules/ej/api/microui/2.4.0/>`_
     - 
   * - [11.1.0-11.2.0]
     - `2.3.0 <https://repository.microej.com/modules/ej/api/microui/2.3.0/>`_
     - 
   * - [9.2.0-11.0.1]
     - `2.2.0 <https://repository.microej.com/modules/ej/api/microui/2.2.0/>`_
     - 
   * - [9.1.1-9.1.2]
     - 2.1.3
     - 
   * - 9.1.0 
     - 2.1.2
     - 
   * - [9.0.0-9.0.2]
     - `2.0.6 <https://repository.microej.com/modules/ej/api/microui/2.0.6/>`_
     - 
   * - [6.0.0-8.1.0]
     - 2.0.0
     - 

Abstraction Layer Interface
===========================

The following sections briefly describes Abstraction Layer interface changes.
For more details, refer to the :ref:`section_ui_migrationguide`.

Display
"""""""

+-----------------+------------------------------------------------------------------+
| UI Pack Range   | Changes                                                          |
+=================+==================================================================+
| [13.0.0-13.4.1] | *UI3* format: implement ``LLUI_DISPLAY_impl.h``:                 |
|                 |                                                                  |
|                 | * ``void LLUI_DISPLAY_IMPL_initialize([...]);``                  |
|                 | * ``void LLUI_DISPLAY_IMPL_binarySemaphoreTake([...]);``         |
|                 | * ``void LLUI_DISPLAY_IMPL_binarySemaphoreGive([...]);``         |
|                 | * ``uint8_t* LLUI_DISPLAY_IMPL_flush([...]);``                   |
+-----------------+------------------------------------------------------------------+
| [10.0.0-12.1.5] | Remove:                                                          | 
|                 |                                                                  |
|                 | * ``int32_t LLDISPLAY_IMPL_getWorkingBufferStartAddress([...]);``|
|                 | * ``int32_t LLDISPLAY_IMPL_getWorkingBufferEndAddress([...]);``  |
+-----------------+------------------------------------------------------------------+
| [8.0.0-9.4.1]   | Merge in ``LLDISPLAY_impl.h``:                                   |
|                 |                                                                  |
|                 | * ``LLDISPLAY_SWITCH_impl.h``                                    |
|                 | * ``LLDISPLAY_COPY_impl.h``                                      |
|                 | * ``LLDISPLAY_DIRECT_impl.h``                                    | 
+-----------------+------------------------------------------------------------------+
| [6.0.0-7.4.7]   | *UI2* format: implement one of header file:                      |
|                 |                                                                  |
|                 | * ``LLDISPLAY_SWITCH_impl.h``                                    |
|                 | * ``LLDISPLAY_COPY_impl.h``                                      |
|                 | * ``LLDISPLAY_DIRECT_impl.h``                                    |
+-----------------+------------------------------------------------------------------+

Input
"""""

+-----------------+------------------------------------------------------------------+
| UI Pack Range   | Changes                                                          |
+=================+==================================================================+
| [13.0.0-13.4.1] | *UI3* format: implement ``LLUI_INPUT_impl.h``:                   |
|                 |                                                                  |
|                 | * ``void LLUI_INPUT_IMPL_initialize([...]);``                    |
|                 | * ``jint LLUI_INPUT_IMPL_getInitialStateValue([...]);``          |
|                 | * ``void LLUI_INPUT_IMPL_enterCriticalSection([...]);``          |
|                 | * ``void LLUI_INPUT_IMPL_leaveCriticalSection([...]);``          |
+-----------------+------------------------------------------------------------------+
| [6.0.0-12.1.5]  | *UI2* format: implement ``LLINPUT_impl.h``                       |
|                 |                                                                  |
|                 | * ``void LLINPUT_IMPL_initialize([...]);``                       |
|                 | * ``int32_t LLINPUT_IMPL_getInitialStateValue([...]);``          |
|                 | * ``void LLINPUT_IMPL_enterCriticalSection([...]);``             |
|                 | * ``void LLINPUT_IMPL_leaveCriticalSection([...]);``             |
+-----------------+------------------------------------------------------------------+

LED
"""

+-----------------+------------------------------------------------------------------+
| UI Pack Range   | Changes                                                          |
+=================+==================================================================+
| [13.0.0-13.4.1] | *UI3* format: implement ``LLUI_LED_impl.h``:                     |
|                 |                                                                  |
|                 | * ``jint LLUI_LED_IMPL_initialize([...]);``                      |
|                 | * ``jint LLUI_LED_IMPL_getIntensity([...]);``                    |
|                 | * ``void LLUI_LED_IMPL_setIntensity([...]);``                    |
+-----------------+------------------------------------------------------------------+
| [6.0.0-12.1.5]  | *UI2* format: implement ``LLLEDS_impl.h``                        |
|                 |                                                                  |
|                 | * ``int32_t LLLEDS_IMPL_initialize([...]);``                     |
|                 | * ``int32_t LLLEDS_IMPL_getIntensity([...]);``                   |
|                 | * ``void LLLEDS_IMPL_setIntensity([...]);``                      |
+-----------------+------------------------------------------------------------------+

Front Panel API
===============

Since MicroEJ UI Pack ``13.0.0``, the Front Panel project must depend on module `com.microej.pack.ui.ui-pack(frontpanel)`_. 
The module version is the MicroEJ Generic UI Pack version, that is always aligned with the MicroEJ UI Packs specific for MCUs.

+-----------------+---------------------------------------------+-------------------+
| UI Pack Range   | Module                                      | Version           |
+=================+=============================================+===================+
| [13.0.0-13.4.1] | `com.microej.pack.ui.ui-pack(frontpanel)`_  | |UIPACKVERSION|   |
+-----------------+---------------------------------------------+-------------------+
| [12.0.0-12.1.5] | ``ej.tool.frontpanel.widget-microui``       | 1.0.0             |
+-----------------+---------------------------------------------+-------------------+

.. note:: Before MicroEJ UI Pack ``12.0.0``, the Front Panel project must depend on classpath variable ``FRONTPANEL_WIDGETS_HOME``.

.. _com.microej.pack.ui.ui-pack(frontpanel): https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/

Image Generator API
===================

Since MicroEJ UI Pack ``13.0.0``, the Image Generator extension project must depend on module `com.microej.pack.ui.ui-pack(imagegenerator)`_.
The module version is the MicroEJ Generic UI Pack version, that is always aligned with the MicroEJ UI Packs specific for MCUs.

+-----------------+-------------------------------------------------+-------------------+
| UI Pack Range   | Module                                          | Version           |
+=================+=================================================+===================+
| [13.0.0-13.4.1] | `com.microej.pack.ui.ui-pack(imagegenerator)`_  | |UIPACKVERSION|   |
+-----------------+-------------------------------------------------+-------------------+

.. note:: Before MicroEJ UI Pack ``13.0.0``, the Image Generator extension project must depend on classpath variable ``IMAGE-GENERATOR-x.x``.

.. _com.microej.pack.ui.ui-pack(imagegenerator): https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/
 
.. _section_ui_releasenotes_cmodule:

C Modules
=========

MicroUI C Module
""""""""""""""""

The MicroUI C module `com.microej.clibrary.llimpl(microui)`_ is available on MicroEJ Central Repository. 
This C module is **mandatory** and provides default implementations for:

* ``LLUI_PAINTER_impl.h`` and ``LLDW_PAINTER_impl.h``: see :ref:`section_display_llapi`,
* Images heap allocator: see :ref:`section_image_loader_memory`,
* ``LLUI_INPUT_IMPL_log_queue_xxx()``: see :ref:`section_inputs_eventbuffer`.

The following table describes the compatibility versions between the C modules and the MicroEJ UI Packs:

+----------------+-----------------+
| C Module Range | UI Pack Range   |
+================+=================+
| [2.0.0-2.0.1]  | [13.3.0-13.4.1] |
+----------------+-----------------+
| [1.1.0-1.1.1]  | [13.1.0-13.2.0] |
+----------------+-----------------+
| [1.0.0-1.0.3]  | [13.0.0-13.1.0] |
+----------------+-----------------+

.. _com.microej.clibrary.llimpl(microui): https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui/

Extended C Modules
""""""""""""""""""

Some C modules extend the main MicroUI C module.
They override the default implementation to use a GPU to perform some drawings.
Contrary to the main MicroUI C module, they are optional: when they are not available, the default implementation of drawings is used.
The default implementations use the Graphics Engine software algorithms.

**STM32 Chrom-ART**

The DMA2D C module `com.microej.clibrary.llimpl(display-dma2d)`_ targets the STM32 CPU that provides the Chrom-ART accelerator. 

The following table describes the accelerated features:

+----------------+------------------------------------------------------+
| Feature        | Comment                                              |
+================+======================================================+
| Fill rectangle |                                                      |
+----------------+------------------------------------------------------+
| Draw image     | ARGB8888, RGB888, RGB565, ARGB1555, ARGB4444, A8, A4 |
+----------------+------------------------------------------------------+
| Flush (copy)   | Copy of data from back buffer to frame buffer        |
+----------------+------------------------------------------------------+

The following table describes the version compatibility between the C module and the MicroEJ UI Packs:

+----------------+-----------------+
| C Module Range | UI Pack Range   |
+================+=================+
| [3.0.0-3.0.2]  | [13.3.0-13.4.1] |
+----------------+-----------------+
| [2.0.0-2.1.0]  | [13.1.0-13.2.0] |
+----------------+-----------------+
| [1.0.6-1.0.8]  | [13.0.0-13.0.7] |
+----------------+-----------------+

.. _com.microej.clibrary.llimpl(display-dma2d): https://repository.microej.com/modules/com/microej/clibrary/llimpl/display-dma2d/

**Vivante VG-Lite**

The VG-Lite C module `com.microej.clibrary.llimpl(microui-vglite)`_ targets the NXP CPU that provides the Vivante VG-Lite accelerator. 

This C module provides some drawing algorithms that are disabled by default. 

* The rendering time of a simple shape with the GPU (time in the VG-Lite library + GPU setup time + rendering time) is longer than with software rendering. To enable the hardware rendering for simple shapes, uncomment the definition of ``VGLITE_USE_GPU_FOR_SIMPLE_DRAWINGS``  in ``display_configuration.h``.
* The rendering time of an RGB565 image into an RGB565 buffer without applying an opacity (alpha == 0xff) is longer than than with software rendering (as this kind of drawing consists in performing a mere memory copy). To enable the hardware rendering for RGB565 images, uncomment the definition of ``VGLITE_USE_GPU_FOR_RGB565_IMAGES``  in ``display_configuration.h``.
* ARGB8888, ARGB1555 and ARGB4444 transparent images are not compatible with some revisions of the VG-Lite GPU. Older GPU revisions do not render correctly transparent images because the pre-multiplication of the pixel opacity is not propagated to the pixel color components. To enable the hardware rendering for transparent images, uncomment the definition of ``VGLITE_USE_GPU_FOR_TRANSPARENT_IMAGES``  in ``display_configuration.h``. Note that this limitation does not concern the A8 and A4 formats.

The following table describes the accelerated features:

+-----------------------------+-----------------------------------------------------------+
| Feature                     | Comment                                                   |
+=============================+===========================================================+
| Draw line                   | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill rectangle              | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Draw rounded rectangle      | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill rounded rectangle      |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw circle arc             | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill circle arc             |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw ellipse arc            | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill ellipse arc            |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw ellipse arc            | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill ellipse arc            |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw circle                 | Disabled by default (see above)                           |
+-----------------------------+-----------------------------------------------------------+
| Fill circle                 |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw image                  | RGB565, A8, A4 + ARGB8888, ARGB1555, ARGB4444 (see above) |
+-----------------------------+-----------------------------------------------------------+
| Draw thick faded point      | Only with fade <= 1                                       |
+-----------------------------+-----------------------------------------------------------+
| Draw thick faded line       | Only with fade <= 1                                       |
+-----------------------------+-----------------------------------------------------------+
| Draw thick faded circle     | Only with fade <= 1                                       |
+-----------------------------+-----------------------------------------------------------+
| Draw thick faded circle arc | Only with fade <= 1                                       |
+-----------------------------+-----------------------------------------------------------+
| Draw thick faded ellipse    | Only with fade <= 1                                       |
+-----------------------------+-----------------------------------------------------------+
| Draw thick line             |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw thick circle           |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw thick circle arc       |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw thick ellipse          |                                                           |
+-----------------------------+-----------------------------------------------------------+
| Draw flipped image          | See draw image                                            |
+-----------------------------+-----------------------------------------------------------+
| Draw rotated image          | See draw image                                            |
+-----------------------------+-----------------------------------------------------------+
| Draw scaled image           | See draw image                                            |
+-----------------------------+-----------------------------------------------------------+

The following table describes the version compatibility between the C module and the MicroEJ UI Packs:

+----------------+-----------------+
| C Module Range | UI Pack Range   |
+================+=================+
| [3.0.0-5.0.1]  | [13.3.0-13.4.1] |
+----------------+-----------------+
| [1.0.0-2.0.0]  | [13.1.0-13.2.0] |
+----------------+-----------------+


The following table describes the version compatibility between the C module and the VG-Lite libraries (officially supported):

+----------------+---------------------------+
| C Module Range | VG-Lite Libraries Range   |
+================+===========================+
| [4.0.0-5.0.1]  | 3.0.15_rev4               |
+----------------+---------------------------+
| [2.0.0-3.0.0]  | 3.0.11_rev3               |
+----------------+---------------------------+
| 1.0.0          | 3.0.4_rev2 and 3.0.4_rev4 |
+----------------+---------------------------+

.. _com.microej.clibrary.llimpl(microui-vglite): https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/clibrary/llimpl/microui-vglite/

..
   | Copyright 2021-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
