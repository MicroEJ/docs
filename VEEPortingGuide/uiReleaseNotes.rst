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
| [13.5.0-14.0.0] | [7.13.0-9.0.0[     | Compatibility with Architecture 8                       |
+-----------------+--------------------+---------------------------------------------------------+
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
   * - 14.0.0
     - `3.5.0 <https://repository.microej.com/modules/ej/api/microui/3.4.0/>`_ XXX_TODO wrong link
     - `1.0.4 <https://repository.microej.com/modules/ej/api/drawing/1.0.4/>`_
   * - [13.7.0-13.7.2]
     - `3.4.0 <https://repository.microej.com/modules/ej/api/microui/3.4.0/>`_
     - `1.0.4 <https://repository.microej.com/modules/ej/api/drawing/1.0.4/>`_
   * - [13.6.0-13.6.2]
     - `3.3.0 <https://repository.microej.com/modules/ej/api/microui/3.3.0/>`_
     - `1.0.4 <https://repository.microej.com/modules/ej/api/drawing/1.0.4/>`_
   * - [13.5.0-13.5.1]
     - `3.2.0 <https://repository.microej.com/modules/ej/api/microui/3.2.0/>`_
     - `1.0.4 <https://repository.microej.com/modules/ej/api/drawing/1.0.4/>`_
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
| 14.0.0          | XXX_TODO                                                         |
|                 |                                                                  |
|                 | * ``void LLUI_DISPLAY_IMPL_initialize([...]);``                  |
|                 | * ``void LLUI_DISPLAY_IMPL_binarySemaphoreTake([...]);``         |
|                 | * ``void LLUI_DISPLAY_IMPL_binarySemaphoreGive([...]);``         |
|                 | * ``uint8_t* LLUI_DISPLAY_IMPL_flush([...]);``                   |
+-----------------+------------------------------------------------------------------+
| [13.0.0-13.7.2] | *UI3* format: implement ``LLUI_DISPLAY_impl.h``:                 |
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
| [13.0.0-14.0.0] | *UI3* format: implement ``LLUI_INPUT_impl.h``:                   |
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
| [13.0.0-13.7.2] | *UI3* format: implement ``LLUI_LED_impl.h``:                     |
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

.. _section_ui_releasenotes_frontpanel:

Front Panel API
===============

The Front Panel project must fetch the widgets compatible with the MicroEJ UI Pack fetched in the VEE Port configuration project:

* Before MicroEJ UI Pack ``12.0.0``, the Front Panel project must depend on the classpath variable ``FRONTPANEL_WIDGETS_HOME``.
* For the UI Packs ``12.x.x``, the Front Panel project must fetch the module `ej.tool.frontpanel.widget-microui`_.
* Since MicroEJ UI Pack ``13.0.0``, the Front Panel project must depend on the module `com.microej.pack.ui.ui-pack(frontpanel)`_ (the module version is the MicroEJ Generic UI Pack version, that is always aligned with the MicroEJ UI Packs specific for MCUs).

+-----------------+--------------------------------------------+-----------------+
| UI Pack Range   | Module                                     | Version         |
+=================+============================================+=================+
| [13.0.0-14.0.0] | `com.microej.pack.ui.ui-pack(frontpanel)`_ | [13.0.0-14.0.0] |
+-----------------+--------------------------------------------+-----------------+
| [12.0.0-12.1.5] | `ej.tool.frontpanel.widget-microui`_       | 1.0.0           |
+-----------------+--------------------------------------------+-----------------+
| [6.0.0-11.2.0]  | n/a                                        | n/a             |
+-----------------+--------------------------------------------+-----------------+

The widget module `ej.tool.frontpanel#widget`_ provides some widgets compatible with the Graphics Engine.
This module fetches by transitivity the module `com.microej.pack.ui.ui-pack(frontpanel)`_. 
When the Front Panel project does not require/use the latest Front Panel UI API, it can only fetch the widget module.

.. note:: This module has been moved from the MicroEJ `Central`_ Repository to the MicroEJ `Developer`_ Repository.   

+---------------------+-----------------------------+--------------+
| Widget Module Range | UI Pack Compatibility Range | Repository   |
+=====================+=============================+==============+
| 4.0.0               | 14.0.0                      | `Developer`_ |
+---------------------+-----------------------------+--------------+
| 3.0.0               | [13.5.1-10-13.7.2]          | `Developer`_ |
+---------------------+-----------------------------+--------------+
| 2.2.0               | [13.1.0-13.7.2]             | `Developer`_ |
+---------------------+-----------------------------+--------------+
| [2.1.0-2.1.1]       | [13.1.0-13.7.2]             | `Central`_   |
+---------------------+-----------------------------+--------------+
| 2.0.0               | [13.0.0-13.7.2]             | `Central`_   |
+---------------------+-----------------------------+--------------+
| 1.0.1               | [12.0.0-12.1.5]             | `Developer`_ |
+---------------------+-----------------------------+--------------+

To use the latest functionalities provided by the UI Pack ``13.0.0`` and higher, the Front Panel project must depend on the same version of the UI Pack as the VEE Port configuration project.
However, if the Front Panel project does not require/use the latest Front Panel UI API, it can fetch a version of the UI Pack older than the version fetched in the VEE Port configuration project.

.. _com.microej.pack.ui.ui-pack(frontpanel): https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/
.. _ej.tool.frontpanel.widget-microui: https://forge.microej.com/ui/native/microej-developer-repository-release/ej/tool/frontpanel/widget-microui/
.. _ej.tool.frontpanel#widget: https://forge.microej.com/ui/native/microej-developer-repository-release/ej/tool/frontpanel/widget/
.. _Central: https://repository.microej.com/modules/ej/tool/frontpanel/widget/
.. _Developer: https://forge.microej.com/ui/native/microej-developer-repository-release/ej/tool/frontpanel/widget/

Image Generator API
===================

Since MicroEJ UI Pack ``13.0.0``, the Image Generator extension project must depend on module `com.microej.pack.ui.ui-pack(imagegenerator)`_.
The module version is the MicroEJ Generic UI Pack version, that is always aligned with the MicroEJ UI Packs specific for MCUs.

+-----------------+-------------------------------------------------+-------------------+
| UI Pack Range   | Module                                          | Version           |
+=================+=================================================+===================+
| [13.0.0-14.0.0] | `com.microej.pack.ui.ui-pack(imagegenerator)`_  | [13.0.0-14.0.0]   |
+-----------------+-------------------------------------------------+-------------------+

.. note:: Before MicroEJ UI Pack ``13.0.0``, the Image Generator extension project must depend on classpath variable ``IMAGE-GENERATOR-x.x``.

.. _com.microej.pack.ui.ui-pack(imagegenerator): https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/
 
.. _section_ui_releasenotes_cmodule:

C Modules
=========

MicroUI C Module
""""""""""""""""

The MicroUI C module `com.microej.clibrary.llimpl(microui)`_ is available on MicroEJ Central Repository, see :ref:`section_ui_cco`.
The following table describes the compatibility versions between the MicroEJ UI Packs and the C modules:

+-----------------+----------------+------------------------------------------+
| UI Pack Range   | C Module Range | Comment                                  |
+=================+================+==========================================+
| 14.0.0          | 4.0.0          | buffer refresh strategies                |
+-----------------+----------------+------------------------------------------+
| [13.7.0-13.7.2] | 3.1.0          | free image resources                     |
+-----------------+----------------+------------------------------------------+
| [13.5.0-13.6.2] | 3.0.0          | multiple Graphics Context output formats |
+-----------------+----------------+------------------------------------------+
| [13.3.0-13.4.1] | [2.0.0-2.0.1]  | copy and draw image                      |
+-----------------+----------------+------------------------------------------+
| [13.1.0-13.2.0] | [1.1.0-1.1.1]  | image heap, events queue, drawing limits |
+-----------------+----------------+------------------------------------------+
| [13.0.0-13.1.0] | [1.0.0-1.0.3]  |                                          |
+-----------------+----------------+------------------------------------------+

.. _com.microej.clibrary.llimpl(microui): https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui/

Extended C Modules
""""""""""""""""""

Some C modules extend the main MicroUI C module.
They override the default implementation to use a GPU to perform some drawings.
Contrary to the main MicroUI C module, they are optional: when they are not available, the default implementation of drawings is used.
The default implementations use the Graphics Engine software algorithms.

**STM32 Chrom-ART**

The :ref:`DMA2D C module <section_ui_c_module_microui_dma2d>` targets the STM32 CPU that provides the Chrom-ART accelerator. 

The following table describes the version compatibility between the MicroEJ UI Packs and the C modules:

+-----------------+----------------+------------------------------------------+
| UI Pack Range   | C Module Range | Comment                                  |
+=================+================+==========================================+
| 14.0.0          | 5.0.0          | buffer refresh strategies                |
+-----------------+----------------+------------------------------------------+
| [13.7.0-13.7.2] | 4.1.0          | free image resources                     |
+-----------------+----------------+------------------------------------------+
| [13.5.0-13.6.2] | 4.0.0          | multiple Graphics Context output formats |
+-----------------+----------------+------------------------------------------+
| [13.3.0-13.4.1] | [3.0.0-3.0.2]  | copy and draw image                      |
+-----------------+----------------+------------------------------------------+
| [13.1.0-13.2.0] | [2.0.0-2.1.0]  | drawing limits                           |
+-----------------+----------------+------------------------------------------+
| [13.0.0-13.0.7] | [1.0.6-1.0.8]  |                                          |
+-----------------+----------------+------------------------------------------+

**Vivante VG-Lite**

The :ref:`VG-Lite C module <section_ui_c_module_microui_vglite>` targets the NXP CPU that provides the Vivante VG-Lite accelerator. 

The following table describes the version compatibility between the MicroEJ UI Packs and the C modules:

+-----------------+----------------+------------------------------------------+
| UI Pack Range   | C module Range | Comment                                  |
+=================+================+==========================================+
| 14.0.0          | 8.0.0          | buffer refresh strategies                |
+-----------------+----------------+------------------------------------------+
| [13.7.0-13.7.2] | 7.2.0          | free image resources                     |
+-----------------+----------------+------------------------------------------+
| [13.5.0-13.6.2] | [6.0.0-7.1.0]  | multiple Graphics Context output formats |
+-----------------+----------------+------------------------------------------+
| [13.3.0-13.4.1] | [3.0.0-5.0.1]  | copy and draw image                      |
+-----------------+----------------+------------------------------------------+
| [13.1.0-13.2.0] | [1.0.0-2.0.0]  |                                          |
+-----------------+----------------+------------------------------------------+

The following table describes the version compatibility between the C module and the VG-Lite libraries (officially supported):

+----------------+-----------------------------+
| C Module Range | VG-Lite Libraries Range     |
+================+=============================+
| [7.1.0-7.2.0]  | 3.0.15_rev4 and 3.0.15_rev7 |
+----------------+-----------------------------+
| [4.0.0-7.0.0]  | 3.0.15_rev4                 |
+----------------+-----------------------------+
| [2.0.0-3.0.0]  | 3.0.11_rev3                 |
+----------------+-----------------------------+
| 1.0.0          | 3.0.4_rev2 and 3.0.4_rev4   |
+----------------+-----------------------------+

**Think Silicon NemaGFX**

The :ref:`NemaGFX C module <section_ui_c_module_microui_nemagfx>` targets the CPU that provides the NemaGFX accelerator. 

The following table describes the version compatibility between the MicroEJ UI Packs and the C modules:

+-----------------+----------------+---------------------------+
| UI Pack Range   | C module Range | Comment                   |
+=================+================+===========================+
| 14.0.0          | 2.0.0          | buffer refresh strategies |
+-----------------+----------------+---------------------------+
| [13.7.0-13.7.2] | [1.1.0-1.2.0]  | free image resources      |
+-----------------+----------------+---------------------------+
| [13.5.0-13.6.2] | 1.0.0          |                           |
+-----------------+----------------+---------------------------+

..
   | Copyright 2021-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
