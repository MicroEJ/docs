.. _section_image_core:

==============
Image Renderer
==============

Principle
=========

The Image Renderer is an on-board engine that reads and draws the images (see :ref:`section_image_raw`).
It calls Abstraction Layer APIs to draw and transform the images (rotation, scaling, deformation, etc.).
It also includes software algorithms to perform the rendering.

Functional Description
======================

All MicroUI image drawings are redirected to a set of Abstraction Layer APIs.
All Abstraction Layer APIs are implemented by weak functions which call software algorithms.
The BSP has the possibility to override this default behavior for each Abstraction Layer API independently.
Furthermore, the BSP can override an Abstraction Layer API for a specific MicroEJ format (for instance ``ARGB8888``) and call the software algorithms for all other formats.

Destination Format
==================

Since MicroUI 3.2, the destination buffer of the drawings can be different than the display buffer format (see :ref:`section_image_display_raw`).
This destination buffer format can be a :ref:`standard format <section_image_standard_raw>` (ARGB8888, A8, etc.) or a :ref:`custom format <section_image_custom_raw>`. 

See :ref:`section_buffered_image` to have more information about how to create buffered images with another format than the display format and how to draw into.

Input Formats
=============

Standard
--------

The Image Renderer is by default able to draw all :ref:`standard formats <section_image_standard_raw>`.
No extra support in the VEE Port is required to draw this kind of images.

The image drawing is similar to a :ref:`shape drawing <section_drawings>`. 
The drawing is performed by default by the :ref:`section_drawings_soft` and can be overridden to use a third-party library or a GPU.

Custom
------

A :ref:`section_image_custom_raw` image can be:

* an image with a pixel buffer but whose pixel organization is not standard,
* an image with a data buffer: an image encoded with a third-party encoder (proprietary format or not),
* an image with a command buffer: instead of performing the drawings, the image *stores* the drawing actions,
* etc.

The VEE Port must extend the Image Renderer to support the drawing of these images.
This extension can consist to:

* decode the image at runtime to draw it,
* use a compatible GPU to draw it,
* use a command interpreter to perform some :ref:`shape drawings <section_drawings>`,
* etc.

To draw the custom images, the Image Renderer introduces the notion of *custom image drawer*.
This drawer is an engine which has the responsibility to draw the image.
Each custom image format (``0`` to ``7``) has its own drawer.

Contrary to the standard images or the shapes where the drawing is stubbed when is not performed (by a soft algo or by a GPU), the custom image drawing is redirected to the associated image drawer.

.. note:: A custom image drawer can call again the UI Shapes Drawing API to draw its elements in the destination.

The implementation is not the same between the Embedded side and the Simulation.
However the concepts are the same and are described in dedicated chapters.

MicroUI C Module
================

Principle
---------

As described above, the Image Renderer must be extended to feature the support of the custom images.
The :ref:`MicroUI C module<section_ui_releasenotes_cmodule>` is designed to manage this extension: it does not *support* the custom formats, but it allows to add some extensions.

This support uses several weak functions and tables to redirect the image drawings.
When this support is useless (when the VEE Port does not need to support *custom* images), this support can be removed to reduce the footprint (by removing tables indirections) and increase the performances (by reducing the number of runtime functions calls).

Standard Formats Only (Default Implementation)
----------------------------------------------

This implementation can only draw images whose format is a :ref:`standard format <section_image_standard_raw>`. 
In other words, the application is not able to draw a custom image. 
This is the most frequently used case, which was the only available use-case with MicroUI before version 3.2. 

.. hint:: To select this implementation (to disable the custom format support), the define ``LLUI_IMAGE_CUSTOM_FORMATS`` must be unset.

This is the default implementation. 

The following graph illustrates the drawing of an image:

.. graphviz::

   digraph {
      ratio="auto"
      splines="true";
      node [style=filled fillcolor=white shape=rectangle fontname=monospace fontcolor=black width=3];
         
      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]
      Painter.drawXXX();" shape=ellipse] 
      LLUI_h [label="[LLUI_PAINTER_impl.h]
      LLUI_PAINTER_IMPL_drawXXX();" fillcolor=gray]
      LLUI_c [label="[LLUI_PAINTER_impl.c]
      LLUI_PAINTER_IMPL_drawXXX();"]
      UID_h [label="[ui_drawing.h]
      UI_DRAWING_drawXXX();" fillcolor=gray]
      UID_weak_c [label="[ui_drawing.c]
      weak UI_DRAWING_drawXXX();" style=dotted]
      UID_soft_h [label="[ui_drawing_soft.h]
      UI_DRAWING_SOFT_drawXXX();" fillcolor=gray]
      UID_soft_c [label="[Graphics Engine]" shape=ellipse]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="algo implemented ?" shape=diamond]
      UID_gpu_c [label="[ui_drawing_gpu.c]
      UI_DRAWING_drawXXX();"]
      UID_gpu_cond [label="GPU compatible ?" shape=diamond]
      UID_gpu_driver [label="[GPU driver]"]
      UID_gpu_hard [label="[GPU]" shape=ellipse]

      UID_stub_h [label="[ui_drawing_stub.h]
      UI_DRAWING_STUB_drawXXX();" fillcolor=gray]
      UID_stub_c [label="[ui_drawing_stub.c]
      UI_DRAWING_STUB_drawXXX();"]
      stub [label="-" shape=ellipse]

      // --- MULTIPLE IMAGES FLOW ELEMENTS -- //

      UII_h [label="[ui_image.h]
      UI_IMAGE_drawXXX();" fillcolor=gray]
      UII_c [label="[ui_image.c]
      UI_IMAGE_drawXXX();"]
      UII_cond [label="standard image ?" shape=diamond]


      // --- FLOW -- //

      mui->LLUI_h->LLUI_c->UID_h->UID_cond
      UID_cond->UID_weak_c [label="no"]
      UID_weak_c->UII_h->UII_c->UII_cond
      UID_cond->UID_gpu_c [label="yes"]
      UID_gpu_c->UID_gpu_cond
      UID_gpu_cond->UII_h [label="no"]
      UID_gpu_cond->UID_gpu_driver [label="yes"]
      UID_gpu_driver->UID_gpu_hard
      UII_cond->UID_soft_h [label="yes"]
      UII_cond->UID_stub_h [label="no"]
      UID_soft_h->UID_soft_c
      UID_stub_h->UID_stub_c->stub
   }

XXX graph to describe

Custom Format Support 
---------------------

In addition with the :ref:`standard formats <section_image_standard_raw>`, this implementation allows to draw images whose format is a :ref:`custom format <section_image_custom_raw>`. 
This is an advanced use-case, only available with MicroUI 3.2 or higher. 

.. hint:: To select this implementation, the define ``LLUI_IMAGE_CUSTOM_FORMATS`` must be set (no specific value).

The MicroUI C module uses some tables to redirect the image management to the expected extension.
There is one table per Imagz Abstraction Layer API (draw, copy, region, rotate, scale, flip) in order to not embed all algorithms (a table and its functions are only embedded in the final binary file if and only if the MicroUI drawing method is called).

Each table contains ten elements:

.. code:: c

   static const UI_IMAGE_DRAWING_draw_t UI_IMAGE_DRAWING_draw_custom[] = {
         &UI_DRAWING_STUB_drawImage,
         &UI_DRAWING_SOFT_drawImage,
         &UI_IMAGE_DRAWING_draw_custom0,
         &UI_IMAGE_DRAWING_draw_custom1,
         &UI_IMAGE_DRAWING_draw_custom2,
         &UI_IMAGE_DRAWING_draw_custom3,
         &UI_IMAGE_DRAWING_draw_custom4,
         &UI_IMAGE_DRAWING_draw_custom5,
         &UI_IMAGE_DRAWING_draw_custom6,
         &UI_IMAGE_DRAWING_draw_custom7,
   };

* ``UI_DRAWING_STUB_drawImage`` is the drawing function called when the drawing function is not implemented,
* ``UI_DRAWING_SOFT_drawImage`` is the drawing function that redirects the drawing to the :ref:`section_drawings_soft`,
* ``UI_IMAGE_DRAWING_draw_customX`` (``0`` to ``7``) are the drawing functions for each custom format.

The table index is retrieved by the MicroUI C Module according to the image format.

The following graph illustrates the drawing of an image:


.. graphviz::

   digraph {
      ratio="auto"
      splines="true";
      node [style=filled fillcolor=white shape=rectangle fontname=monospace fontcolor=black width=3];
         
      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]
      Painter.drawXXX();" shape=ellipse] 
      LLUI_h [label="[LLUI_PAINTER_impl.h]
      LLUI_PAINTER_IMPL_drawXXX();" fillcolor=gray]
      LLUI_c [label="[LLUI_PAINTER_impl.c]
      LLUI_PAINTER_IMPL_drawXXX();"]
      UID_h [label="[ui_drawing.h]
      UI_DRAWING_drawXXX();" fillcolor=gray]
      UID_weak_c [label="[ui_drawing.c]
      weak UI_DRAWING_drawXXX();" style=dotted]
      UID_soft_h [label="[ui_drawing_soft.h]
      UI_DRAWING_SOFT_drawXXX();" fillcolor=gray]
      UID_soft_c [label="[Graphics Engine]" shape=ellipse]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="algo implemented ?" shape=diamond]
      UID_gpu_c [label="[ui_drawing_gpu.c]
      UI_DRAWING_drawXXX();"]
      UID_gpu_cond [label="GPU compatible ?" shape=diamond]
      UID_gpu_driver [label="[GPU driver]"]
      UID_gpu_hard [label="[GPU]" shape=ellipse]

      UID_stub_h [label="[ui_drawing_stub.h]
      UI_DRAWING_STUB_drawXXX();" fillcolor=gray]
      UID_stub_c [label="[ui_drawing_stub.c]
      UI_DRAWING_STUB_drawXXX();"]
      stub [label="-" shape=ellipse]

      // --- MULTIPLE IMAGES FLOW ELEMENTS -- //

      UII_h [label="[ui_image.h]
      UI_IMAGE_drawXXX();" fillcolor=gray]
      UII_c [label="[ui_image.c]
      UI_IMAGE_drawXXX();"]
      UII_cond [label="standard image ?" shape=diamond]
      UIIx_c [label="[ui_image.c]
      table[x] = UI_IMAGE_drawCustom_x()"]
      UIIx_weak_c [label="[ui_image.c]
      weak UI_IMAGE_drawCustom_x();" style=dotted]
      UIIx_cond [label="implemented ?" shape=diamond]
      UIIx_impl_c [label="[ui_image_x.c]
      UI_IMAGE_drawCustom_x()"]
      UIIx_impl_d [label="[custom drawing]" shape=ellipse]

      UID_h2 [label="[ui_drawing.h]
      @see Simple Flow With GPU;"  fillcolor=gray]

      // --- FLOW -- //

      mui->LLUI_h->LLUI_c->UID_h->UID_cond
      UID_cond->UID_weak_c [label="no"]
      UID_weak_c->UII_h->UII_c->UII_cond
      UID_cond->UID_gpu_c [label="yes"]
      UID_gpu_c->UID_gpu_cond
      UID_gpu_cond->UII_h [label="no"]
      UID_gpu_cond->UID_gpu_driver [label="yes"]
      UID_gpu_driver->UID_gpu_hard
      UII_cond->UID_soft_h [label="yes"]
      UII_cond->UIIx_c [label="no"]
      UID_soft_h->UID_soft_c
      UIIx_c->UIIx_cond
      UIIx_cond->UIIx_weak_c [label="no"]
      UIIx_weak_c->UID_stub_h->UID_stub_c->stub
      UIIx_cond->UIIx_impl_c [label="yes"]
      UIIx_impl_c->UIIx_impl_d
      UIIx_impl_d->UID_h2 [style=dotted label="optional
      (drawShapes)"]
   }

XXX graph to describe

Simulation
==========

* service xxx UIImageDrawing
* xxx notion decode (cf UIImageDrawing.decode())


Standard Formats Only (Default Implementation)
----------------------------------------------

.. graphviz::

   digraph {
      ratio="auto"
      splines="true";
      node [style=filled fillcolor=white shape=rectangle fontname=monospace fontcolor=black width=3];
         
      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]
      Painter.drawXXX();" shape=ellipse] 
      LLUI_c [label="[FrontPanel]
      LLUIPainter.drawXXX();"]
      UID_h [label="[FrontPanel]
      getUIDrawer().drawXXX();" fillcolor=gray]
      UID_weak_c [label="[FrontPanel]
      DisplayDrawer.drawXXX();"]
      UID_soft_h [label="[FrontPanel]
      getUIDrawerSoftware()
      .drawXXX();" fillcolor=gray]
      UID_soft_c [label="[Graphics Engine]" shape=ellipse]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="method overridden ?" shape=diamond]
      UID_gpu_c [label="[VEE Port FP]
      DisplayDrawerExtension
      .drawXXX();"]
      UID_gpu_cond [label="can draw algo ?" shape=diamond]
      UID_gpu_hard [label="[Third-party lib]" shape=ellipse]

      UID_stub_c [label="[FrontPanel]
      no op"]
      stub [label="-" shape=ellipse]

      // --- MULTIPLE IMAGES FLOW ELEMENTS -- //

      UII_h [label="[FrontPanel]
      getUIImageDrawer()
      .drawXXX();" fillcolor=gray]
      UII_cond [label="standard image ?" shape=diamond]

      // --- FLOW -- //

      mui->LLUI_c->UID_h->UID_weak_c->UID_cond
      UID_cond->UII_h [label="no"]
      UII_h->UII_cond
      UID_cond->UID_gpu_c [label="yes"]
      UID_gpu_c->UID_gpu_cond
      UID_gpu_cond->UII_h [label="no"]
      UID_gpu_cond->UID_gpu_hard [label="yes"]
      UII_cond->UID_soft_h [label="yes"]
      UII_cond->UID_stub_c [label="no"]
      UID_soft_h->UID_soft_c
      UID_stub_c->stub
   }

Custom Format Support 
---------------------

* service xxx UIImageDrawing
* xxx notion decode (cf UIImageDrawing.decode())

.. graphviz::

   digraph {
      ratio="auto"
      splines="true";
      node [style=filled fillcolor=white shape=rectangle fontname=monospace fontcolor=black width=3];
         
      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]
      Painter.drawXXX();" shape=ellipse] 
      LLUI_c [label="[FrontPanel]
      LLUIPainter.drawXXX();"]
      UID_h [label="[FrontPanel]
      getUIDrawer().drawXXX();" fillcolor=gray]
      UID_weak_c [label="[FrontPanel]
      DisplayDrawer.drawXXX();"]
      UID_soft_h [label="[FrontPanel]
      getUIDrawerSoftware()
      .drawXXX();" fillcolor=gray]
      UID_soft_c [label="[Graphics Engine]" shape=ellipse]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="method overridden ?" shape=diamond]
      UID_gpu_c [label="[VEE Port FP]
      DisplayDrawerExtension
      .drawXXX();"]
      UID_gpu_cond [label="can draw algo ?" shape=diamond]
      UID_gpu_hard [label="[Third-party lib]" shape=ellipse]

      UID_stub_c [label="[FrontPanel]
      no op"]
      stub [label="-" shape=ellipse]

      // --- MULTIPLE IMAGES FLOW ELEMENTS -- //

      UII_h [label="[FrontPanel]
      getUIImageDrawer()
      .drawXXX();" fillcolor=gray]
      UII_cond [label="standard image ?" shape=diamond]
      UIIx_cond [label="available image drawer
      and method implemented ?" shape=diamond]
      UIIx_impl_c [label="[VEE Port Fp]
      CustomImageDrawing.draw()"]
      UIIx_impl_d [label="[custom drawing]" shape=ellipse]

      UID_h2 [label="[FrontPanel]
      getUIDrawer().drawXXX();
      @see Simple Flow With GPU;"  fillcolor=gray]

      // --- FLOW -- //

      mui->LLUI_c->UID_h->UID_weak_c->UID_cond
      UID_cond->UII_h [label="no"]
      UII_h->UII_cond
      UID_cond->UID_gpu_c [label="yes"]
      UID_gpu_c->UID_gpu_cond
      UID_gpu_cond->UII_h [label="no"]
      UID_gpu_cond->UID_gpu_hard [label="yes"]
      UII_cond->UID_soft_h [label="yes"]
      UII_cond->UIIx_cond [label="no"]
      UID_soft_h->UID_soft_c
      UIIx_cond->UID_stub_c [label="no"]
      UID_stub_c->stub
      UIIx_cond->UIIx_impl_c [label="yes"]
      UIIx_impl_c->UIIx_impl_d
      UIIx_impl_d->UID_h2 [style=dotted label="optional
      (drawShapes)"]
   }


Dependencies
============

-  MicroUI module (see :ref:`section_microui`),
-  Display module (see :ref:`section_display`).

Installation
============

Image Renderer module is part of the MicroUI module and Display module. Install them in order to be able to use some images.

Use
===

The MicroUI image APIs are available in the class `ej.microui.display.Image`_.

.. _ej.microui.display.Image: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
