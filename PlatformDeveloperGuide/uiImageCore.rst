.. _section_image_core:

==============
Image Renderer
==============

Principle
=========

The Image Renderer module is an on-board engine that reads and draws the image encoded in MicroEJ format (see :ref:`section_image_raw`) . It calls low-level APIs to draw and transform the images (rotation, scaling, deformation etc.). It also includes software algorithms to perform the rendering.

Functional Description
======================

The engine redirects all MicroUI images drawings to a set of low-level API. All low-level API are implemented by weak functions which call software algorithms. The BSP has the possibility to override this default behavior for each low-level API independently. Furthermore, the BSP can override a low-level API for a specific MicroEJ format (for instance ``ARGB8888``) and call the software algorithms for all others formats.

.. graphviz::

   digraph {
      
      { 
         node [shape=rect color="lightgray" style="filled" ffixedsize=true width=3]
         app bsp gpu algo llapi llimpl drawApi weak hard
      }
      
      {
         app [label="Painter API"]
         bsp [label="BSP"]
         gpu [label="GPU"]
         algo [label="Software Algorithms"]
         llapi  [label="LLUI_PAINTER_impl.h"]
         llimpl  [label="LLUI_PAINTER_impl.c"]         
         drawApi  [label="ui_drawing.h"]
         weak  [label="weak_ui_drawing.c"]
         hard  [label="hardware"]
      }  

      app -> llapi -> llimpl -> drawApi -> {weak bsp} -> algo -> hard
      bsp -> gpu -> hard
   }


Dependencies
============

-  MicroUI module (see :ref:`section_microui`)

-  Display module (see :ref:`section_display`)


Installation
============

Image Renderer module is part of the MicroUI module and Display module. Install them in order to be able to use some images.


Use
===

The MicroUI image APIs are available in the class
``ej.microui.display.Image``.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
