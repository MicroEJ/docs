.. _section_font_core:

=============
Font Renderer
=============


Principle
=========

The Font Renderer module is a built-in module of the MicroUI module (see :ref:`section_microui`) for the application side; and is a
built-in module of the Display module (see :ref:`section_display`) for the C side.

Functional Description
======================

The engine redirects all MicroUI font drawings to the internal software algorithms. There is no inrection to a set of low-level API. 

.. graphviz::

   digraph {
      
      graph [
         overlap=false
         splines=true
         nodesep=0.5
         ranksep=0.5
         bgcolor="transparent"
         center=1
      ];
         
      node [
         fixedsize=true,
         fontname="Ubuntu"
         fontsize=14
         fontcolor=dimgray
         height=0.5
         width=2.5
         shape=box
         fillcolor=aliceblue
         color="lightblue"
         style="filled,setlinewidth(3)",
      ];
            
      edge [
         arrowsize=0.8
      ];
      
      app [label="Painter API"]
      stack [label="Graphical Engine"]
      algo [label="Software Algorithms"]
      hard  [label="hardware"]
      
      app -> stack -> algo -> hard
   }

.. _section_font_loader_memory:

External Resources
==================

The Font Rendere is able to load some fonts located outside the CPU addresses' space range. It uses the External Resource Loader.

When a font is located in such memory, the Font Renderer copies a very short part of the resource (the font file) into a RAM memory (into CPU addresses space range): the font header. This header stays located in RAM until MicroEJ Application is using the font. As soon as the MicroEJ Application uses another external font, new font replaces the old one. Then, on MicroEJ Application demand, the Font Renderer loads some extra information from the font into the RAM memory (the font meta data, the font pixels, etc.). This extra information is automatically unloaded from RAM when the Font Renderer no longer needs them. 

This extra information is stored into a RAM section called ``.bss.microui.display.externalFontsHeap``. Its size is automatically calculated according the external fonts used by the firmware. However it is possible to change this value setting the MicroEJ application property ``ej.microui.memory.externalfontsheap.size``. This option is very useful when building a kernel: the kernel may anticipate the section size required by the features.

.. warning:: When this size is smaller than required size by a given external font, some characters may be not drawn. 

Dependencies
============

-  MicroUI module (see :ref:`section_microui`)

-  Display module (see :ref:`section_display`)


Installation
============

The Font Renderer modules are part of the MicroUI module and Display module. You must install them in order to be able to use some fonts.


Use
===

The MicroUI font APIs are available in the class
``ej.microui.display.Font``.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
