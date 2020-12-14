.. _section_animate_widget:

How to Animate a Widget
=======================

Starting and stopping the animation
-----------------------------------

To animate a widget, an ``Animator`` instance is required. This instance can be passed in the constructor of the widget or be fetched from a service provider.
Make sure that your widget subclass implements the ``Animation`` interface so that it can be used with an ``Animator``.

An animation can be started at any moment, provided that the widget is shown. For example, the animation can start on a click event.
Likewise, an animation can be stopped at any moment, for example a few seconds after the animation has started. Once the widget is hidden, its animation should always be stopped to avoid memory leaks and unnecessary operations.

To start the animation of the widget, call the ``startAnimation()`` method of the ``Animator`` instance. To stop it, call the ``stopAnimation()`` method of the same ``Animator`` instance.

For example, the following snippet starts the animation as soon as the widget is shown and stops it once the widget is hidden:

.. code-block:: Java

	public class MyAnimatedWidget extends Widget implements Animation {

		private final Animator animator;

		private long startTime;
		private long elapsedTime;

		public MyAnimatedWidget(Animator animator) {
			this.animator = animator;
		}

		@Override
		protected void onShown() {
			this.startTime = System.currentTimeMillis();
			this.animator.startAnimation(this);
		}

		@Override
		protected void onHidden() {
			this.animator.stopAnimation(this);
		}
	}


Performing an animation step
----------------------------

The ``tick()`` method is called by the animator in order to update the widget. It is called in the UI thread once the display has been flushed.
This method should not render the widget but should update its state and request a new render if necessary.
The ``tick()`` method should return whether or not the animation should continue after this increment.

For example, the following snippet updates the state of the widget when it is ticked, requests a new render and keeps the animation going until 5 seconds have passed:

.. code-block:: Java

	@Override
	public boolean tick(long currentTimeMillis) {
		// update widget state
		this.elapsedTime = currentTimeMillis - this.startTime;
		// request new render
		requestRender();
		// return whether to continue or to stop the animation
		return (this.elapsedTime < 5_000);
	}

The ``renderContent()`` method should render the widget by using its current state (saved in the fields of the widget).
This method should not call methods such as ``System.currentTimeMillis()`` because the widget could be rendered in multiple passes, for example if a :ref:`partial buffer <section_display_partial_buffer>` is used.

For example, the following snippet renders the current state of the widget by displaying the time elapsed since the start of the animation:

.. code-block:: Java

	@Override
	protected void renderContent(GraphicsContext g, int contentWidth, int contentHeight) {
		Style style = getStyle();
		g.setColor(style.getColor());
		Painter.drawString(g, Long.toString(this.elapsedTime), style.getFont(), 0, 0);
	}

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
