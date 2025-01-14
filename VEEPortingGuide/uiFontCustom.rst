.. _section_font_custom:

===========
Custom Font
===========

Principle
=========

A custom font is a class that extends the class MicroUI `Font`_.
It is associated to a native implementation that handles, at least, the drawing of strings specified by `Painter.drawString()`_.

.. warning:: Calling the Graphics Engine's software algorithms to draw a string with a custom font corrupts the MicroUI execution (flickering, memory corruption, unknown behavior, etc.).

Note that a MicroUI Font has a fixed height and a fixed baseline (in pixels).
Yet, it can be based on a font that manage several heights.
In this case, the MicroUI Font is configured with a specific height.

Requirements
============

The custom font class and its native implementation are responsible for:

* Providing one or several entry points to load a font (typically MyFont.getFont(*path_to_font*)).
* Defining the format of the input data (a file, a stream, a byte array, etc.).
* Loading (if required) the font on the native side.
* Managing memory (the custom font may require to allocate some memory on the native side).
* Closing the font (mainly if some native data is associated to this font).

.. note:: In case the input data is a file, the file can be listed in the :ref:`resources.list <section.classpath.elements.raw_resources>` file.

MicroUI Drawings
================

MicroUI provides several APIs to draw a string.
The native implementation of the custom font should implement the associated :ref:`Abstract Layer API <section_drawings>`.
This is not mandatory but strongly recommended: the main goal is to abstract away the use of custom fonts for the application.
The application should be able to manipulate any font (internal fonts or custom fonts) without using a different API for each font type.

Renderable String
=================

The custom font class should manage the MicroUI `RenderableString`_.
A renderable string is an immutable string associated with a font.
The objective of a renderable string is to be drawn faster than a standard string.
Because the font data for the renderable string never changes, some information can be cached, avoiding retrieving it at drawing time.

As a consequence, the custom font should keep some data that allows one to quickly retrieve the data to draw.
The data format is custom-font-dependent.
In the MicroUI library, the renderable string data is represented by a byte array (see `RenderableString.getSNIContext()`_).
On the native side, this data should be cast to a structure readable by the font drawer.

.. note:: If there is no support for the renderable strings in the custom font, the drawings are automatically redirected to the simple drawString algorithms.
   Consequently, there is no advantage for the application to use the RenderableString API.

Additional APIs
===============

The class can provide some additional methods:

* To get information on the font: ascent, descent, name, etc.
* To draw a string with additional parameters: opacity, matrix deformation, gradients, etc.

Rendering
=========

The native implementation of the renderings (the implementation of the MicroUI Abstract Layer API to draw a string with the font) is described in the chapter :ref:`section_font_renderer`.

.. _Font: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html#
.. _Painter.drawString(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Painter.html#drawString-ej.microui.display.GraphicsContext-java.lang.String-ej.microui.display.Font-int-int-
.. _RenderableString: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/RenderableString.html#
.. _RenderableString.getSNIContext(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/RenderableString.html#getSNIContext--

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
