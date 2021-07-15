.. _section_font_core:

=============
Font Renderer
=============


Principle
=========

The Font Renderer is included in the MicroUI module (see :ref:`section_microui`) for the application side; and is included in the Display module (see :ref:`section_display`) for the C side.

Functional Description
======================

The Graphics Engine redirects all MicroUI font drawings to the internal software algorithms. There is no indirection to a set of Low Level API. 

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
      stack [label="Graphics Engine"]
      algo [label="Software Algorithms"]
      hard  [label="hardware"]
      
      app -> stack -> algo -> hard
   }

.. _section_font_loader_memory:

External Resources
==================

Memory Management
-----------------

The Font Renderer is able to load some fonts located outside the CPU addresses' space range. It uses the External Resource Loader.

When a font is located in such memory, the Font Renderer copies a very short part of the resource (the font file) into a RAM memory (into CPU addresses space range): the font header. This header stays located in RAM until MicroEJ Application is using the font. As soon as the MicroEJ Application uses another external font, new font replaces the old one. Then, on MicroEJ Application demand, the Font Renderer loads some extra information from the font into the RAM memory (the font meta data, the font pixels, etc.). This extra information is automatically unloaded from RAM when the Font Renderer no longer needs them. 

This extra information is stored into a RAM section called ``.bss.microui.display.externalFontsHeap``. Its size is automatically calculated according to the external fonts used by the firmware. However it is possible to change this value by setting the MicroEJ application property ``ej.microui.memory.externalfontsheap.size``. This option is very useful when building a kernel: the kernel may anticipate the section size required by the features.

.. warning:: When this size is smaller than the size required by an external font, some characters may be not drawn. 

Backward Compatibility
----------------------

As explained :ref:`here<section.tool.fontdesigner.styles>`, the notion of `dynamic` styles and the style `underline` are not supported anymore by MicroUI 3. However, an external font may have been generated with an older version of the Font Generator; and by consequence, the generated file can hold the dynamic style. The Font Renderer is able to load these old versions of fonts. However, there are some runtime limitations:

* The `dynamic` styles are ignored. The font is drawn without any dynamic algorithm.
* The font style (the style returned by ``Font.isBold()`` and ``Font.isItalic()``) is the `dynamic` style. For instance when a font holds the style `bold` as dynamic style and the style `italic` as built-in style, the font is considered as `bold` + `italic`; even if the style `bold` is not rendered.

Dependencies
============

-  MicroUI module (see :ref:`section_microui`),

-  Display module (see :ref:`section_display`).


Installation
============

The Font Renderer is part of the MicroUI module and Display module. You must install them in order to be able to use some fonts.


Use
===

The MicroUI font APIs are available in the class
`ej.microui.display.Font <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html#>`_.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
