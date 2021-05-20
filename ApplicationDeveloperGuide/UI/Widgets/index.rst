.. _Widgets and Examples:

Widgets and Examples
====================

Widget library
--------------

The widget library provides very common widgets with basic implementations.
These simple widgets may not provide every desired feature, but they can easily be forked since their implementation is very simple.

The widget library does not provide any example. However, the widget demo provides examples for these widgets.

Source
~~~~~~

To use the widgets provided by the widget library, add the following line to a :ref:`module description file <mmm_module_description>`:

.. code-block:: XML

	<dependency org="ej.library.ui" name="widget" rev="4.0.0"/>

To fork one of the provided widgets, duplicate the associated Java class from the widget library JAR into the source code of your application.
It is recommended to move the duplicated class to an other package and to rename the class in order to avoid confusion between your forked class and the original class.

Provided widgets
~~~~~~~~~~~~~~~~

Widgets:

- ``Label``: displays a text.
- ``ImageWidget``: displays an image which is loaded from a resource.
- ``Button``: displays a text and reacts to click events.
- ``ImageButton``: displays an image which is loaded from a resource and reacts to click events.

Containers:

- ``List``: lays out any number of children horizontally or vertically.
- ``Flow``: lays out any number of children horizontally or vertically, using multiple rows if necessary.
- ``Grid``: lays out any number of children in a grid.
- ``Dock``: lays out any number of children by docking each child one by one on a side.
- ``SimpleDock``: lays out three children horizontally or vertically.
- ``OverlapContainer``: lays out any number of children by stacking them.
- ``Canvas``: lays out any number of children freely.

Widget demo
-----------

The widget demo provides some widget implementations as well as usage examples for these widgets and for the widgets of the Widget library.
The widgets and usage examples are intended to be duplicated by the developers in order to be adapted to their use-case.

Source
~~~~~~

To use the widgets provided by the widget demo, clone the following GitHub repository: `<https://github.com/MicroEJ/Demo-Widget>`_.
You can then import the ``com.microej.demo.widget`` project into your workspace to see the source of the widgets and their associated examples.

Each subpackage contains the source code for a specific widget and for a page which showcases the widget.
For example, the ``com.microej.demo.widget.checkbox`` package contains the ``Checkbox`` widget and the ``CheckboxPage``.

Provided widgets
~~~~~~~~~~~~~~~~

Widgets:

- ``Checkbox``: displays a text and a square which can be checked or unchecked.
- ``RadioButton``: displays a text and a circle which can be checked or unchecked.
- ``ProgressBar``: displays an animated bar indicating that the user should wait for an estimated amount of time.
- ``IndeterminateProgressBar``: displays an animated bar indicating that the user should wait for an indeterminate amount of time.
- ``Toggle``: displays a text and a switch that can be checked or unchecked.

Containers:

- ``Split``: lays out two children horizontally or vertically, by giving each child a portion of the available space.
- ``ScrollableList``: lays out its widgets the same way as a regular list, but provides an optimization when added to a scroll.

MWT examples
------------

The MWT Examples repository provides various examples which extend or customize the MWT framework.

Source
~~~~~~

To run the examples and read the source code of these examples, clone the following GitHub repository: `<https://github.com/MicroEJ/ExampleJava-MWT>`_.
You can then import the multiple project into your workspace to see the source of each example and to run it on Simulator or on your board.

Provided examples
~~~~~~~~~~~~~~~~~

- ``com.microej.example.mwt.attribute``: shows how to customize the style of widgets using attributes selectors, similar to CSS.
- ``com.microej.example.mwt.focus``: shows how to introduce focus management in your project.
- ``com.microej.example.mwt.lazystylesheet``: shows how to use a lazy stylesheet rather than the default stylesheet implementation.
- ``com.microej.example.mwt.mvc``: shows how to develop responsive widgets using a MVC design pattern and how to display a cursor image representing the pointer.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
