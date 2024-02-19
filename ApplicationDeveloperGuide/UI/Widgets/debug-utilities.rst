.. _widget_library_debug_utilities:

Debug Utilities
===============

A few utilities useful for debugging are available in the package ``ej.widget.util.debug`` of the widget library.

Print the Hierarchy of Widgets
------------------------------

The method `HierarchyInspector.hierarchyToString(Widget)`_ returns a String representing the hierarchy of a widget.
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

.. _HierarchyInspector.hierarchyToString(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/HierarchyInspector.html#hierarchyToString-ej.mwt.Widget-
  
Print the Path to a Widget
--------------------------

The method `HierarchyInspector.pathToWidgetToString(Widget)`_ returns a String representing the list of ancestors of the widget.
For example: ``Desktop > Scroll > ScrollableList > Label``.

It may be used to identify a widget in a trace.

It is also possible to choose the separator by using `HierarchyInspector.pathToWidgetToString(Widget, char)`_ method.
For example: ``Desktop ; Scroll ; ScrollableList ; Label``.

.. _HierarchyInspector.pathToWidgetToString(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/HierarchyInspector.html#pathToWidgetToString-ej.mwt.Widget-
.. _HierarchyInspector.pathToWidgetToString(Widget, char): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/HierarchyInspector.html#pathToWidgetToString-ej.mwt.Widget-char-

Count the Number of Widgets or Containers
-----------------------------------------

The methods `HierarchyInspector.countNumberOfWidgets(Widget)`_ and `HierarchyInspector.countNumberOfContainers(Widget)`_ respectively count the number of widgets and containers in a hierarchy.

It may be used to evaluate the complexity of a hierarchy of widgets.

.. _HierarchyInspector.countNumberOfWidgets(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/HierarchyInspector.html#countNumberOfWidgets-ej.mwt.Widget-
.. _HierarchyInspector.countNumberOfContainers(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/HierarchyInspector.html#countNumberOfContainers-ej.mwt.Widget-

Count the Maximum Depth of a Hierarchy
--------------------------------------

The method `HierarchyInspector.countMaxDepth(Widget)`_ counts the maximum depth of a hierarchy.
In other words, the depth of the widget with the biggest number of parents recursively.

It may be used to evaluate the complexity of a hierarchy of widgets.

.. _HierarchyInspector.countMaxDepth(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/HierarchyInspector.html#countMaxDepth-ej.mwt.Widget-

Print the Bounds of a Widget
----------------------------

The method `BoundsInspector.boundsToString(Widget)`_ returns a String with the widget type and its bounds.
The returned String contains:

- the simple name of the class of the widget,
- its position relative to its parent,
- its size,
- its absolute position.

For example: ``Label: 0,0 7x25 (absolute: 75,75)``

.. _BoundsInspector.boundsToString(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/BoundsInspector.html#boundsToString-ej.mwt.Widget-

Print the bounds of all the widgets in a hierarchy
--------------------------------------------------

The method `BoundsInspector.boundsRecursiveToString(Widget)`_ returns a String representing the type and bounds of each widget in the hierarchy of a widget.

For example:

.. code-block::

    Scroll: 0,0 480x272 (absolute: 0,0)
    +--ScrollableList: 0,0 480x272 (absolute: 0,0)
    |  +--Label: 0,0 480x50 (absolute: 0,0)
    |  +--Dock: 0,50 480x50 (absolute: 0,50)
    |  |  +--ImageWidget: 0,0 70x50 (absolute: 0,50)
    |  |  +--Label: 70,0 202x50 (absolute: 70,50)
    |  +--Label: 0,100 480x50 (absolute: 0,100)
  

.. _BoundsInspector.boundsRecursiveToString(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/BoundsInspector.html#boundsRecursiveToString-ej.mwt.Widget-

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
