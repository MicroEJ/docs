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

Formats
=======

Standard
--------

The Image Renderer is by default able to draw all :ref:`standard formats <section_image_standard_raw>`.
* no extra support, similar to drawing: simple flow & custom flow (gpu)

Custom
------

The VEE Port can extend the Image Renderer to support the drawing of custom images.
* requires extra support to read / decode / draw 
* vee allows custom format.
* to draw it, can use shapes drawings
* examples of use cases ? command vs pixels

MicroUI C Module
================

Principle
---------

The BSP can implement the functions that draw images (draw, copy, region flip, rotate and scale).

* The custom image manager can call again the ui_drawing.h API to draw its elements in the destination.
* More complex and more footprint (#define xxxx)
* xxx copier hackmd graph
both implems: footprint & cie

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


Custom Format Support 
---------------------

define à mettre LLUI xxx

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

Simulation
==========

Principle
---------

both implems: footprint & cie

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
