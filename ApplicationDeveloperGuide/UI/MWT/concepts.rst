.. _mwt_concepts:

Concepts
========

Graphical Elements
------------------

.. figure:: images/hierarchy.png
   :alt: MWT Hierarchy
   :align: center

Widget
~~~~~~

A widget is an object that is intended to be displayed on a screen. A widget occupies a specific region of the display and holds a state. A user may interact with a widget (using a touch screen or a button for example).

Widgets are arranged on a desktop. A widget can be part of only one desktop hierarchy, and can appear only once on that desktop.

Container
~~~~~~~~~

A container follows the composite pattern: it is a widget composed of other widgets. It also defines the layout policy of its children (defining their bounds). The children's positions are relative to the position of their parent.
Containers can be nested to design elaborate user interfaces.

By default, the children are rendered in the order in which they have been added in the container. And thus if the container allows overlapping, the widgets added last will be on top of the widgets added first. A container can also modify how its children are rendered.

Desktop
~~~~~~~

A desktop is a displayable intended to be shown on a display (cf. MicroUI). At any time, only one desktop can be displayed per display.

A desktop contains a widget (or a container). When the desktop is shown, its widget (and all its hierarchy for a container) is drawn on the display.

Rendering
---------

A new rendering of a widget on the display can be requested by calling its `requestRender()`_ method. The rendering is done asynchronously in the MicroUI thread.

When a container is rendered, all its children are also rendered.

A widget can be transparent, meaning that it does not draw every pixel within its bounds. In this case, when this widget is asked to be rendered, its parent is asked to be rendered in the area of the widget (recursively if the parent is also transparent). Usually a widget is transparent when its background (from the style) is transparent.

A widget can also be rendered directly in a specific graphics context by calling its `render(GraphicsContext)`_ method. It can be useful to render a widget (and its children) in an image for example.

.. _requestRender(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#requestRender--
.. _render(GraphicsContext): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#render-ej.microui.display.GraphicsContext-

.. _section_render_policy:

Render Policy
~~~~~~~~~~~~~

A render policy is a strategy that MWT uses in order to repaint the entire desktop or to repaint a specific widget.

The most naive render policy would be to render the whole hierarchy of the desktop whenever a widget has changed. However `DefaultRenderPolicy`_ is smarter than that: it only repaints the widget, and its ancestors if the widget is transparent. The result is correct only if there is no overlapping widget, in which case  `OverlapRenderPolicy`_ should be used instead. This policy repaints the widget (or its non-transparent ancestor), then it repaints all the widgets that overlap it.

When using a :ref:`partial buffer <section_display_partial_buffer>`, these render policies can not be used because they render the entire screen in a single pass. Instead, a custom render policy which renders the screen in multiple passes has to be used. Refer to the `partial buffer demo`_ for more information on how to implement this render policy and how to use it.

The render policy can be changed by overridding `Desktop.createRenderPolicy()`_.

.. _DefaultRenderPolicy: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/render/DefaultRenderPolicy.html
.. _OverlapRenderPolicy: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/render/OverlapRenderPolicy.html
.. _partial buffer demo: https://github.com/MicroEJ/Demo-PartialBuffer
.. _Desktop.createRenderPolicy(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html#createRenderPolicy--

.. _section_layout_process:

Lay Out
-------

All widgets are laid out at once during the lay out process. This process can be started by `Desktop.requestLayOut()`_, `Widget.requestLayOut()`_. The layout is also automatically done when the desktop is shown (`Desktop.onShown()`_). This process is composed of two steps, each step browses the hierarchy of widgets following a depth-first algorithm:

- compute the optimal size for each widget and container (considering the constraints of the lay out),
- set position and size for each widget.

Once the position and size of a widget is set, the widget is notified by a call to `onLaidOut()`_.

.. _Desktop.requestLayOut(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html#requestLayOut--
.. _Widget.requestLayOut(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#requestLayOut--
.. _Desktop.onShown(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html#onShown--
.. _onLaidOut(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#onLaidOut--

Event Dispatch
--------------

Events generated in the hardware (touch, buttons, etc.) are sent to the event dispatcher of the desktop. It is then responsible of sending the event to one or several widgets of the hierarchy. A widget receives the event through its `handleEvent(int)`_ method. This method returns a boolean that indicates whether or not the event has been consumed by the widget.

Widgets are disabled by default and don't receive the events.

.. _handleEvent(int): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#handleEvent-int-

Pointer Event Dispatcher
~~~~~~~~~~~~~~~~~~~~~~~~

By default, the desktop proposes an event dispatcher that handles only pointer events.

Pointer events are grouped in sessions. A session starts when the pointer is pressed, and ends when the pointer is released or when it exits the pressed widget.

While no widget consumes the events, they are sent to the widget that is under the pointer (see `Desktop.getWidgetAt(int, int)`_), then sent to all its parent hierarchy recursively.

.. figure:: images/eventDispatchUML.png
   :alt: Pointer Event Dispatcher Flow
   :align: center

Once a widget has consumed an event, it will be the only one to receive the next events during the session.

.. figure:: images/pointerEventDispatcherFlow.png
   :alt: Pointer Event Dispatcher Flow
   :align: center

A widget can redefine its reactive area by subclassing the `contains(int x, int y)`_ method. It is useful when a widget does not fill fully its bounds.

.. Add an example such as a circular slider or an analog watchface.

.. _Desktop.getWidgetAt(int, int): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html#getWidgetAt-int-int-
.. _contains(int x, int y): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#contains-int-int-

Style
-----

A style describes how widgets must be rendered on screen. The attributes of the style are strongly inspired from CSS.

Dimension
~~~~~~~~~

The dimension is used to constrain the size of the widget.

MWT provides multiple implementations of dimensions:

- `NoDimension`_ does not constrain the dimension of the widget, so the widget will take all the space granted by its parent container.
- `OptimalDimension`_ constrains the dimension of the widget to its optimal size, which is given by the `computeContentOptimalSize()`_ method of the widget.
- `FixedDimension`_ constrains the dimension of the widget to a fixed absolute size.
- `RelativeDimension`_ constrains the dimension of the widget to a percentage of the size of its parent container.

.. _NoDimension: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/dimension/NoDimension.html
.. _OptimalDimension: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/dimension/OptimalDimension.html
.. _computeContentOptimalSize(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#computeContentOptimalSize-ej.mwt.util.Size-
.. _FixedDimension: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/dimension/FixedDimension.html
.. _RelativeDimension: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/dimension/RelativeDimension.html

Alignment
~~~~~~~~~

The horizontal and vertical alignments are used to position the content of the widget within its bounds.

The alignment is used by the framework to position the widget within its available space if the size of the widget has been constrained with a `Dimension`_.

The alignment can also be used in the `renderContent()`_ method in order to position the drawings of the widget (such as a text or an image) within its content bounds.

.. _Dimension: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/dimension/Dimension.html
.. _renderContent(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#requestRender-int-int-int-int-

Outlines
~~~~~~~~

The margin, border and padding are the 3 outlines which wrap the content of the widget. The widget is wrapped in the following sequence: first the padding, then the border, and finally the margin.

.. figure:: images/boxmodel.png
   :alt: Box model
   :align: center

MWT provides multiple implementations of invisible outlines which are usually used for margin and padding:

- `NoOutline`_ does not wrap the widget in an outline.
- `UniformOutline`_ wraps the widget in an outline which thickness is equal on all sides.
- `FlexibleOutline`_ wraps the widget in an outline which thickness can be configured for each side.

MWT also provides multiple implementations of visible outlines which are usually used for border:

- `RectangularBorder`_ draws a plain rectangle around the widget.
- `RoundedBorder`_ draws a plain rounded rectangle around the widget.

.. _NoOutline: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/outline/NoOutline.html
.. _UniformOutline: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/outline/UniformOutline.html
.. _FlexibleOutline: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/outline/FlexibleOutline.html
.. _RectangularBorder: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/outline/border/RectangularBorder.html
.. _RoundedBorder: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/outline/border/RoundedBorder.html

Background
~~~~~~~~~~

The background is used to render the background of the widget.
The background covers the border, the padding and the content of the widget, but not its margin.

MWT provides multiple implementations of backgrounds:

- `NoBackground`_ leaves a transparent background behind the widget.
- `RectangularBackground`_ draws a plain rectangle behind the widget.
- `RoundedBackground`_ draws a plain rounded rectangle behind the widget.
- `ImageBackground`_ draws an image behinds the widget.

.. _NoBackground: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/background/NoBackground.html
.. _RectangularBackground: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/background/RectangularBackground.html
.. _RoundedBackground: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/background/RoundedBackground.html
.. _ImageBackground: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/background/ImageBackground.html

Color
~~~~~

The color is not used by the framework itself, but it may be used in the ``renderContent()`` to select the color of the drawings.

Font
~~~~

The font is not used by framework itself, but it may be used in the ``renderContent()`` to select the font to use when drawing strings.

Extra fields
~~~~~~~~~~~~

Extra fields are not used by framework itself, but they may be used in the ``renderContent()`` to customize the behavior and the appearance of the widget.

See chapter :ref:`section_define_extra_style_field` for more information on extra fields.

Stylesheet
----------

A stylesheet allows to customize the appearance of all the widgets of a desktop without changing the code of the widget subclasses.

MWT provides multiple implementations of stylesheets:

- `VoidStylesheet`_ assigns the same default style for every widget.
- `CascadingStylesheet`_ assigns styles to widgets using selectors, similarly to CSS.

For example, the following code customizes the style of every `Label`_ widget of the desktop:

.. code-block:: Java

	CascadingStylesheet stylesheet = new CascadingStylesheet();

	EditableStyle labelStyle = stylesheet.getSelectorStyle(new TypeSelector(Label.class));
	labelStyle.setColor(Colors.RED);
	labelStyle.setBackground(new RectangularBackground(Colors.WHITE));

	desktop.setStylesheet(stylesheet);

.. _VoidStylesheet: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/stylesheet/VoidStylesheet.html
.. _CascadingStylesheet: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/stylesheet/cascading/CascadingStylesheet.html
.. _Label: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/basic/Label.html

.. _section_animations:

Animations
----------

MWT provides a utility class in order to animate widgets: `Animator`_.
When a widget is being animated by an animator, the widget is notified each time that the display is flushed. The widget can use this interrupt in order to update its state and request a new rendering.

See chapter :ref:`section_animate_widget` for more information on animating a widget.

.. _Animator: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/animation/Animator.html

Partial buffer considerations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Rendering a widget in :ref:`partial buffer mode <section_display_partial_buffer>` may require multiple cycles if the buffer is not big enough to hold all the pixels to update in a single shot.
This means that rendering is slower in partial buffer mode, and this may cause performance being significantly affected during animations.

Besides, the whole screen is flushed in multiple times instead of a single one, which means that the user may see the display at a time where every part of the display has not been flushed yet.

Due to these limitations, it is not recommended to repaint big parts of the screen at the same time.
For example, a transition on a small part of the screen will look better than a transition affecting the whole screen.
A transition will look perfect if the partial buffer can hold all the lines to repaint.
Since the buffer holds a group of lines, a horizontal transition may not look the same as a vertical transition.

Desktop and widget states
-------------------------

Desktop and widgets pass through different states. Once created, they can be attached, then they can be shown.

A desktop is attached automatically as soon as it is shown on the display.
It can also be attached manually by calling `Desktop.setAttached()`_. It could be used to render the desktop (and its widgets) on an image for example.

A widget is considered as attached when it is contained by a desktop that is attached.

In the same way, by default, a widget is shown when its desktop is shown. But for optimization purpose, a container can control when its children are shown or hidden. A typical use case is when the widgets are moved outside the display.

Once a widget is attached, it means that it is ready to be shown (for instance, the necessary resources are allocated). In other words, once attached a widget is ready to be rendered (on an image or on the display).

Once a widget is shown, it means that it is intended to be rendered on the display. While shown, it may start a periodic refresh or an animation.

.. figure:: images/showSequence.png
   :alt: Show Sequence
   :align: center

The following sections will present several ways to customize and extend the framework to better fit your needs.

.. _Desktop.setAttached(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html#setAttached--

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
