.. _section_font_custom:

===========
Custom Font
===========

Principle
=========

A custom font is a class that extends the class MicroUI `Font`_.
It is associated to a native implementation that manages, at least, the drawings of strings.

.. warning:: Calling the Graphics Engine's software algorithms to draw a string with a custom font corrupts the MicroUI execution (flickering, memory corruption, unknown behavior, etc.).

Note that a MicroUI Font has got a fixed height and baseline (in pixels).
In case of the custom font is dynamic (dynamic height) XXX_TODO @seon

XXX_TODO show hierarchy ?

Requirements
============

This class and its native implementation are responsible:

* to provide one or several entry points to load a font (typically MyFont.getFont(*path_to_font*)),
* of the format of the input data (a file, a stream, a byte array, etc.),
* of the loading (if required) of the font on the native side,
* of the memory management (the custom font may require to allocate some memory on the native side),
* of the closure (mainly if some native data is associated to this font).

.. note:: In case of the input data is a file, the file can be listed in the :ref:`resources.list <section.classpath.elements.raw_resources>` file.

MicroUI Drawings
================

MicroUI provides several APIs to draw a string.
The native implementation of the custom font should implement the associated :ref:`Abstract Layer API <section_drawings>`.
This is not mandatory but advised: the main objective is to anonymize the use of the custom font in the application.
The application should be able to manipulate any fonts (internal fonts or custom fonts) without using specific font's API.

Renderable String
=================

This class should manage the MicroUI `RenderableString`_.
A renderable string is an immutable string associated to a font.
The objective of a renderable string is to be drawn faster than a simple string, because the data of the font for the renderable string never change.
No need to retrieve some information at drawing time.

By consequence, the custom font should keep some data that allows to quickly retrieve the data to draw.
The data format is custom font dependent. 
In the MicroUI library, the renderable string data is represented by a byte array (see `RenderableString.getSNIContext()`_ XXX_TODO link).
On native side, this data should be cast in a structure readable by the font drawer.

.. note:: If there is no support for the renderable strings in the custom font, the drawings are automatically redirected to the simple drawString algorithms. By consequence, there is no advantage for the application to use the RenderableString API.


Additional APIs
===============

The class can provide some additional methods:

* to get information on the font: ascent, descent, name, etc.
* to draw a string with additional parameters: opacity, matrix deformation, gradients, etc.

Rendering
=========

The native implementation of the renderings (the implementation of the MicroUI Abstract Layer API to draw a string with the font) is described in the chapter :ref:`section_font_renderer`.

.. _Font: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html#
.. _RenderableString: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/RenderableString.html#
.. _RenderableString.getSNIContext(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/RenderableString.html#

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
