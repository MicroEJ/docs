.. _section_font_renderer:

=============
Font Renderer
=============


Principle
=========

The Font Renderer is included in the MicroUI module (see :ref:`section_microui`) for the application side; and is included in the Display module (see :ref:`section_display`) for the C side.

Functional Description
======================

The Graphics Engine redirects all MicroUI font drawings to the internal software algorithms. There is no indirection to a set of Abstraction Layer API. 

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

Installation
============

The Font Renderer is part of the MicroUI module and Display module. You must install them in order to be able to use some fonts.


Use
===

The MicroUI font APIs are available in the class
`ej.microui.display.Font`_.

.. _ej.microui.display.Font: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html#

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
