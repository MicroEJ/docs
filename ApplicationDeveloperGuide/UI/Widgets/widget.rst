.. _widget_library:

Widget Library
==============

The `Widget library`_ provides very common widgets with basic implementations.
These simple widgets may not provide every desired feature, but they can easily be forked since their implementation is very simple.

The widget library does not provide any example. However, the widget demo provides examples for these widgets.

.. _Widget library: https://repository.microej.com/modules/ej/library/ui/widget/4.1.0/

Source
------

To use the widgets provided by the widget library, add the following line to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: java

         implementation("ej.library.ui:widget:4.1.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.library.ui" name="widget" rev="4.1.0"/>

To fork one of the provided widgets, duplicate the associated Java class from the widget library JAR into the source code of your application.
It is recommended to move the duplicated class to an other package and to rename the class in order to avoid confusion between your forked class and the original class.

Provided Widgets
----------------

Widgets:

- `Label`_: displays a text.
- `ImageWidget`_: displays an image which is loaded from a resource.
- `Button`_: displays a text and reacts to click events.
- `ImageButton`_: displays an image which is loaded from a resource and reacts to click events.

Containers:

- `List`_: lays out any number of children horizontally or vertically.
- `Flow`_: lays out any number of children horizontally or vertically, using multiple rows if necessary.
- `Grid`_: lays out any number of children in a grid.
- `Dock`_: lays out any number of children by docking each child one by one on a side.
- `SimpleDock`_: lays out three children horizontally or vertically.
- `OverlapContainer`_: lays out any number of children by stacking them.
- `Canvas`_: lays out any number of children freely.

.. _Label: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/basic/Label.html
.. _ImageWidget: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/basic/ImageWidget.html
.. _Button: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/basic/Button.html
.. _ImageButton: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/basic/ImageButton.html
.. _List: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/container/List.html
.. _Flow: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/container/Flow.html
.. _Grid: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/container/Grid.html
.. _Dock: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/container/Dock.html
.. _SimpleDock: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/container/SimpleDock.html
.. _OverlapContainer: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/container/OverlapContainer.html
.. _Canvas: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/container/Canvas.html

Color Utilities
---------------

The widget library offers some color utilities.

The `ColorHelper`_ is helpful for decomposing colors into components (alpha, red, blue, green) and building back a color from components.

The `GradientHelper`_ can blend two colors and create a gradient from two colors.

The resulting gradient is a list of distinct colors from the start color to the end color.
The colors are truncated to the display color depth.
As a consequence, for the same start and end colors, a gradient created for a 32-bit display will contain more colors than on a 16-bit display.

The `LightHelper`_ proposes several primitives concerning the luminance of the colors.
The luminance of a color is computed from the luminance and the quantity of each of its components.
The green being the brighter, then the red and finally the blue.

.. _ColorHelper: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/color/ColorHelper.html
.. _GradientHelper: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/color/GradientHelper.html
.. _LightHelper: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/color/LightHelper.html

.. _widget_library_debug_utilities:

Debug Utilities
---------------

A few utilities useful for debugging are available in the package ``ej.widget.util.debug`` of the widget library.

Print the Hierarchy of Widgets
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

.. _HierarchyInspector.hierarchyToString(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/debug/HierarchyInspector.html#hierarchyToString-ej.mwt.Widget-
  
Print the Path to a Widget
~~~~~~~~~~~~~~~~~~~~~~~~~~

The method `HierarchyInspector.pathToWidgetToString(Widget)`_ returns a String representing the list of ancestors of the widget.
For example: ``Desktop > Scroll > ScrollableList > Label``.

It may be used to identify a widget in a trace.

It is also possible to choose the separator by using `HierarchyInspector.pathToWidgetToString(Widget, char)`_ method.
For example: ``Desktop ; Scroll ; ScrollableList ; Label``.

.. _HierarchyInspector.pathToWidgetToString(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/debug/HierarchyInspector.html#pathToWidgetToString-ej.mwt.Widget-
.. _HierarchyInspector.pathToWidgetToString(Widget, char): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/debug/HierarchyInspector.html#pathToWidgetToString-ej.mwt.Widget-char-

Count the Number of Widgets or Containers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The methods `HierarchyInspector.countNumberOfWidgets(Widget)`_ and `HierarchyInspector.countNumberOfContainers(Widget)`_ respectively count the number of widgets and containers in a hierarchy.

It may be used to evaluate the complexity of a hierarchy of widgets.

.. _HierarchyInspector.countNumberOfWidgets(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/debug/HierarchyInspector.html#countNumberOfWidgets-ej.mwt.Widget-
.. _HierarchyInspector.countNumberOfContainers(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/debug/HierarchyInspector.html#countNumberOfContainers-ej.mwt.Widget-

Count the Maximum Depth of a Hierarchy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The method `HierarchyInspector.countMaxDepth(Widget)`_ counts the maximum depth of a hierarchy.
In other words, the depth of the widget with the biggest number of parents recursively.

It may be used to evaluate the complexity of a hierarchy of widgets.

.. _HierarchyInspector.countMaxDepth(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/debug/HierarchyInspector.html#countMaxDepth-ej.mwt.Widget-

Print the Bounds of a Widget
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The method `BoundsInspector.boundsToString(Widget)`_ returns a String with the widget type and its bounds.
The returned String contains:

- the simple name of the class of the widget,
- its position relative to its parent,
- its size,
- its absolute position.

For example: ``Label: 0,0 7x25 (absolute: 75,75)``

.. _BoundsInspector.boundsToString(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/debug/BoundsInspector.html#boundsToString-ej.mwt.Widget-

Print the bounds of all the widgets in a hierarchy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
  

.. _BoundsInspector.boundsRecursiveToString(Widget): https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/util/debug/BoundsInspector.html#boundsRecursiveToString-ej.mwt.Widget-

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
