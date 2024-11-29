.. _widget_library_debug_utilities:

Debug Utilities
===============

A few utilities useful for debugging are available in the package ``ej.widget.util.debug`` of the widget library.

.. _widget_library_debug_utilities_hierarchy:

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

The method `HierarchyInspector.hierarchyStyleToString(Widget)`_ returns the same information plus the list of the attributes of the style of each widget in the hierarchy.
It only adds the attributes that differ from the `default style`_.

For example:

.. code-block::

    Scroll (background=RectangularBackground, horizontalAlignment=hcenter)
    +--ScrollableList (background=RectangularBackground)
    |  +--Label (color=white, font=RasterFont[SourceSansPro_19px-300], horizontalAlignment=hcenter, verticalAlignment=vcenter)
    |  +--Dock (background=NoBackground)
    |  |  +--ImageWidget (horizontalAlignment=hcenter, verticalAlignment=vcenter)
    |  |  +--Label (color=0xf8a331, font=RasterFont[SourceSansPro_19px-300], horizontalAlignment=hcenter, verticalAlignment=vcenter)
    |  +--Label (color=white, font=RasterFont[SourceSansPro_19px-300], horizontalAlignment=hcenter, verticalAlignment=vcenter)

If the constant ``ej.mwt.debug.cascadingstyle.enabled`` is set (see :ref:`this section <mwt_how_to_debug_source_rule>`), it will also print the selector that originated each style's attribute.

For example:

.. code-block::

    Scroll (background=RectangularBackground from default, horizontalAlignment=hcenter from .class 896560)
    +--ScrollableList (background=RectangularBackground from default)
    |  +--Label (color=white from .class 896572, background=NoBackground from .class 896572, font=RasterFont[SourceSansPro_19px-300] from .class 896572, horizontalAlignment=hcenter from .class 896572, verticalAlignment=vcenter from .class 896572)
    |  +--Dock (background=NoBackground from default)
    |  |  +--ImageWidget (horizontalAlignment=hcenter from .class 896571, verticalAlignment=vcenter from .class 896571)
    |  |  +--Label (color=0xf8a331 from .class 896572 and :nth-child(odd), font=RasterFont[SourceSansPro_19px-300] from .class 896572, horizontalAlignment=hcenter from .class 896572, verticalAlignment=vcenter from .class 896572)
    |  +--Label (color=white from .class 896572, font=RasterFont[SourceSansPro_19px-300] from .class 896572, horizontalAlignment=hcenter from .class 896572, verticalAlignment=vcenter from .class 896572)

.. _HierarchyInspector.hierarchyToString(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/HierarchyInspector.html#hierarchyToString-ej.mwt.Widget-
.. _HierarchyInspector.hierarchyStyleToString(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/HierarchyInspector.html#hierarchyStyleToString-ej.mwt.Widget-
.. _default style: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/DefaultStyle.html
  
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
