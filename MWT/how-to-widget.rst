How-To Create a Widget
======================

To create a custom widget, a new class should be created, extending the ``Widget`` class.
Widget subclasses have to implement two methods and may override optional methods, as explained in the following sections.

Implementing the mandatory methods
----------------------------------

Computing the optimal size of the widget
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``computeContentOptimalSize()`` method is called by the MWT framework in order to know the optimal size of the widget.
The optimal size of the widget should be big enough to contain all the drawings of the widget.

The ``Size`` parameter of the ``computeContentOptimalSize()`` method initially contains the size available for the widget.
An available width or height equal to ``Widget.NO_CONSTRAINT`` means that the optimal size should be computed without considering any restriction on the respective axis.
Before the method returns, the size object should be set to the optimal size of the widget.

When implementing this method, the ``getStyle()`` method may be called in order to retrieve the style of the widget.

For example, the following snippet computes the optimal size of a label:

.. code-block:: Java

	@Override
	protected void computeContentOptimalSize(Size size) {
		Font font = getStyle().getFont();
		int width = font.stringWidth(this.text);
		int height = font.getHeight();
		size.setSize(width, height);
	}

Rendering the content of the widget
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``renderContent()`` method is called by the MWT framework in order to render the content of the widget.

When implementing this method, the ``getStyle()`` method may be called in order to retrieve the style of the widget.

For example, the following snippet renders the content of a label:

.. code-block:: Java

	@Override
	protected void renderContent(GraphicsContext g, int contentWidth, int contentHeight) {
		Style style = getStyle();
		g.setColor(style.getColor());
		Painter.drawString(g, style.getFont(), this.text, 0, 0);
	}

Handling events
---------------

When a widget is created, it is disabled and it will not receive any event.
A widget may be enabled or disabled by calling ``setEnabled()``. A common practice is to enable the widget is its constructor.
 
Enabled widgets can handle events by overriding ``handleEvent()``. MicroUI event APIs may be used in order to know more information on the event, such as its type.
 
For example, the following snippet prints a message when the widget receives an event:

.. code-block:: Java

	@Override
	public boolean handleEvent(int event) {
		System.out.println("Event type: " + Event.getType(event));
	}

Listening to the life-cycle hooks
---------------------------------

``Widget`` subclasses may override the following methods in order to allocate and free the necessary resources:

- ``onAttached()``
- ``onDetached()``
- ``onLaidOut()``
- ``onShown()``
- ``onHidden()``

For example, the ``onAttached()`` may be overridden to load an image:

.. code-block:: Java

	@Override
	protected void onAttached() {
		this.image = ResourceImage.loadImage(this.imagePath);
	}

Likewise, the ``onDetached()`` method may be overridden to close the image:

.. code-block:: Java

	@Override
	protected void onDetached() {
		this.image.close();
	}

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
