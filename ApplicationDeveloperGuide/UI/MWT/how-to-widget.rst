How to Create a Widget
======================

A widget is the main way to render information on the display. A set of pre-defined widgets is described in the :ref:`Widgets and Examples` section.

If the needed widget does not already exist, it is possible to create it from scratch (or by derivating another one).

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
A widget may be enabled or disabled by calling ``setEnabled()``. A common practice is to enable the widget in its constructor.
 
Enabled widgets can handle events by overriding ``handleEvent()``. MicroUI event APIs may be used in order to know more information on the event, such as its type.
The ``handleEvent()`` method should return whether or not the event was consumed by the widget.
 
For example, the following snippet prints a message when the widget receives an event:

.. code-block:: Java

	@Override
	public boolean handleEvent(int event) {
		System.out.println("Event type: " + Event.getType(event));
		return false;
	}

Consuming events
~~~~~~~~~~~~~~~~

To indicate that an event was consumed by a widget, ``handleEvent()`` should return ``true``.
Usually, once an event is consumed, it is not dispatched to other widgets (this behavior is controlled by the event dispatcher).
The widget that consumed the event is the last one to receive it.

The following guidelines are recommended to decide when to consume an event and when not to consume an event:

- If the widget triggers an action when receiving the event, it consumes the event.
- If the widget does not trigger an action when receiving the event, it does not consume the event.

.. note::

   If the event is ``Pointer.PRESSED``, do not consume the event unless it is required that the subsequent widgets in the hierarchy do not receive it.
   The ``Pointer.PRESSED`` event is special because pressing a widget is usually not the deciding factor to trigger an action.
   The user has to release it or drag it.
   If the user presses a widget and then drags their finger or the pointer out of the widget before releasing it, the action is not triggered.

Listening to the life-cycle hooks
---------------------------------

``Widget`` subclasses may override the following methods in order to allocate and free the necessary resources:

- ``onAttached()``
- ``onDetached()``
- ``onLaidOut()``
- ``onShown()``
- ``onHidden()``

For example, the ``onAttached()`` method may be overridden to load an image:

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

For example, the ``onShown()`` method may be overridden to start an animation:

.. code-block:: Java

	@Override
	protected void onShown() {
		Animator animator = getDesktop().getAnimator();
		animator.startAnimation(this);
	}

Likewise, the ``onHidden()`` method may be overridden to stop an animation:

.. code-block:: Java

	@Override
	protected void onHidden() {
		Animator animator = getDesktop().getAnimator();
		animator.stopAnimation(this);
	}

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
