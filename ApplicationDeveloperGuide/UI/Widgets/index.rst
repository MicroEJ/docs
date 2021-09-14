.. _Widgets and Examples:

Widgets and Examples
====================

Widget Library
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

Provided Widgets
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

Debug Utilities
~~~~~~~~~~~~~~~

A few utilities useful for debugging are available in the package ``ej.widget.util.debug`` of the widget library.

- Print the hierarchy of widgets.

  The method ``HierarchyInspector.hierarchyToString(Widget)`` returns a String representing the hierarchy of a widget.
  In other words, it prints the widget and its children recursively in a tree format.

  It may be used to analyse the content of a page and have a quick estimation of the number of widgets and the depth of the hierarchy.

  For example:

  .. code-block::

     Scroll
     +--ScrollableList
     |  +--Label
     |  +--Dock
     |  |  +--ImageWidget
     |  |  +--Label
     |  +--Label
  
- Print the path to a widget.

  The method ``HierarchyInspector. pathToWidgetToString(Widget)`` returns a String representing the list of ancestors of the widget.
  For example: ``Desktop > Scroll > ScrollableList > Label``.

  It may be used to identify a widget in a trace.

  It is also possible to choose the separator by using ``HierarchyInspector.pathToWidgetToString(Widget, char)`` method.
  For example: ``Desktop ; Scroll ; ScrollableList ; Label``.

- Count the number of widgets or containers.

  The methods ``HierarchyInspector.countNumberOfWidgets(Widget)`` and ``HierarchyInspector.countNumberOfContainers(Widget)`` respectively count the number of widgets and containers in a hierarchy.

  It may be used to evaluate the complexity of a hierarchy of widgets.

- Count the maximum depth of a hierarchy.

  The method ``HierarchyInspector.countMaxDepth(Widget)`` counts the maximum depth of a hierarchy.
  In other words, the depth of the widget with the biggest number of parents recursively.

  It may be used to evaluate the complexity of a hierarchy of widgets.

- Print the bounds of a widget.

  The method ``BoundsInspector.boundsToString(Widget)`` returns a String with the widget type and its bounds.
  The returned String contains:

  - the simple name of the class of the widget,
  - its position relative to its parent,
  - its size,
  - its absolute position.

  For example: ``Label: 0,0 7x25 (absolute: 75,75)``

- Print the bounds of all the widgets in a hierarchy.

  The method ``BoundsInspector.boundsRecursiveToString(Widget)`` returns a String representing the type and bounds of each widget in the hierarchy of a widget.

  For example:

  .. code-block::

     Scroll: 0,0 480x272 (absolute: 0,0)
     +--ScrollableList: 0,0 480x272 (absolute: 0,0)
     |  +--Label: 0,0 480x50 (absolute: 0,0)
     |  +--Dock: 0,50 480x50 (absolute: 0,50)
     |  |  +--ImageWidget: 0,0 70x50 (absolute: 0,50)
     |  |  +--Label: 70,0 202x50 (absolute: 70,50)
     |  +--Label: 0,100 480x50 (absolute: 0,100)
  
Widget Demo
-----------

The widget demo provides some widget implementations as well as usage examples for these widgets and for the widgets of the Widget library.
The widgets and usage examples are intended to be duplicated by the developers in order to be adapted to their use-case.

Source
~~~~~~

To use the widgets provided by the widget demo, clone the following GitHub repository: `<https://github.com/MicroEJ/Demo-Widget>`_.
You can then import the ``com.microej.demo.widget`` project into your workspace to see the source of the widgets and their associated examples.

Each subpackage contains the source code for a specific widget and for a page which showcases the widget.
For example, the ``com.microej.demo.widget.checkbox`` package contains the ``Checkbox`` widget and the ``CheckboxPage``.

Provided Widgets
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

MWT Examples
------------

The MWT Examples repository provides various examples which extend or customize the MWT framework.

Source
~~~~~~

To run the examples and read the source code of these examples, clone the following GitHub repository: `<https://github.com/MicroEJ/ExampleJava-MWT>`_.
You can then import the multiple project into your workspace to see the source of each example and to run it on Simulator or on your board.

Provided Examples
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
