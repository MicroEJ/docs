.. _section_animate_widget:

How to Animate a Widget
=======================

Starting and stopping the animation
-----------------------------------

To animate a widget, an `Animator`_ instance is required. This instance can be retrieved from the desktop of the widget by calling `Desktop.getAnimator()`_.
Make sure that your widget subclass implements the `Animation`_ interface so that it can be used with an `Animator`_.

An animation can be started at any moment, provided that the widget is shown. For example, the animation can start on a click event.
Likewise, an animation can be stopped at any moment, for example a few seconds after the animation has started. Once the widget is hidden, its animation should always be stopped to avoid memory leaks and unnecessary operations.

To start the animation of the widget, call the `startAnimation()`_ method of the `Animator`_ instance. To stop it, call the `stopAnimation()`_ method of the same `Animator`_ instance.

For example, the following snippet starts the animation as soon as the widget is shown and stops it once the widget is hidden:

.. code-block:: Java

	public class MyAnimatedWidget extends Widget implements Animation {

		private long startTime;
		private long elapsedTime;

		@Override
		protected void onShown() {
			// start animation
			getDesktop().getAnimator().startAnimation(this);
			// save start time
			this.startTime = Util.platformTimeMillis();
			// set widget initial state
			this.elapsedTime = 0;
		}

		@Override
		protected void onHidden() {
			// stop animation
			getDesktop().getAnimator().stopAnimation(this);
		}                                                                                                                                                                                                                                                                                                                                                      
	}

.. _Animator: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/animation/Animator.html
.. _Desktop.getAnimator(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html#getAnimator--
.. _Animation: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/animation/Animation.html
.. _startAnimation(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/animation/Animator.html#startAnimation-ej.mwt.animation.Animation-
.. _stopAnimation(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/animation/Animator.html#stopAnimation-ej.mwt.animation.Animation-

Performing an animation step
----------------------------

The `tick()`_ method is called by the animator in order to update the widget. It is called in the UI thread once the display has been flushed.
This method should not render the widget but should update its state and request a new render if necessary.
The `tick()`_ method should return whether or not the animation should continue after this increment.

For example, the following snippet updates the state of the widget when it is ticked, requests a new render and keeps the animation going until 5 seconds have passed:

.. code-block:: Java

	@Override
	public boolean tick(long platformTimeMillis) {
		// update widget state
		this.elapsedTime = platformTimeMillis - this.startTime;
		// request new render
		requestRender();
		// return whether to continue or to stop the animation
		return (this.elapsedTime < 5_000);
	}

The `renderContent()`_ method should render the widget by using its current state (saved in the fields of the widget).
This method should not call methods such as `Util.platformTimeMillis()`_ because the widget could be rendered in multiple passes, for example if a :ref:`partial buffer <section_display_partial_buffer>` is used.

For example, the following snippet renders the current state of the widget by displaying the time elapsed since the start of the animation:

.. code-block:: Java

	@Override
	protected void renderContent(GraphicsContext g, int contentWidth, int contentHeight) {
		Style style = getStyle();
		g.setColor(style.getColor());
		Painter.drawString(g, Long.toString(this.elapsedTime), style.getFont(), 0, 0);
	}

.. _tick(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/animation/Animation.html#tick-long-
.. _renderContent(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#renderContent-ej.microui.display.GraphicsContext-int-int-
.. _Util.platformTimeMillis(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/Util.html#platformTimeMillis--

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
