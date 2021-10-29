Widget Library
==============

The widget library provides very common widgets with basic implementations.
These simple widgets may not provide every desired feature, but they can easily be forked since their implementation is very simple.

The widget library does not provide any example. However, the widget demo provides examples for these widgets.

Source
------

To use the widgets provided by the widget library, add the following line to a :ref:`module description file <mmm_module_description>`:

.. code-block:: XML

	<dependency org="ej.library.ui" name="widget" rev="4.1.0"/>

To fork one of the provided widgets, duplicate the associated Java class from the widget library JAR into the source code of your application.
It is recommended to move the duplicated class to an other package and to rename the class in order to avoid confusion between your forked class and the original class.

Provided Widgets
----------------

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
---------------

A few utilities useful for debugging are available in the package ``ej.widget.util.debug`` of the widget library.

Print the Hierarchy of Widgets
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
  
Print the Path to a Widget
~~~~~~~~~~~~~~~~~~~~~~~~~~

The method ``HierarchyInspector. pathToWidgetToString(Widget)`` returns a String representing the list of ancestors of the widget.
For example: ``Desktop > Scroll > ScrollableList > Label``.

It may be used to identify a widget in a trace.

It is also possible to choose the separator by using ``HierarchyInspector.pathToWidgetToString(Widget, char)`` method.
For example: ``Desktop ; Scroll ; ScrollableList ; Label``.

Count the Number of Widgets or Containers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The methods ``HierarchyInspector.countNumberOfWidgets(Widget)`` and ``HierarchyInspector.countNumberOfContainers(Widget)`` respectively count the number of widgets and containers in a hierarchy.

It may be used to evaluate the complexity of a hierarchy of widgets.

Count the Maximum Depth of a Hierarchy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The method ``HierarchyInspector.countMaxDepth(Widget)`` counts the maximum depth of a hierarchy.
In other words, the depth of the widget with the biggest number of parents recursively.

It may be used to evaluate the complexity of a hierarchy of widgets.

Print the Bounds of a Widget
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The method ``BoundsInspector.boundsToString(Widget)`` returns a String with the widget type and its bounds.
The returned String contains:

- the simple name of the class of the widget,
- its position relative to its parent,
- its size,
- its absolute position.

For example: ``Label: 0,0 7x25 (absolute: 75,75)``

Print the bounds of all the widgets in a hierarchy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
  

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
