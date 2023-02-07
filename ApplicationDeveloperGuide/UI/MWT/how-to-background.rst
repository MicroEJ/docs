How to Define a Background
==========================

To create a custom background, a new class should be created, extending the `Background`_ class.
Background subclasses have to implement two methods, as explained in the following sections.

.. _Background: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/background/Background.html

Informing whether the background is transparent
-----------------------------------------------

The `isTransparent()`_ method is called by the MWT framework in order to know whether or not the background is transparent.
A background is considered as transparent if it does not draw every pixel with maximal opacity when it is applied.

For example, the following snippet informs that the background is completely opaque regardless of its size:

.. code-block:: Java

	@Override
	public boolean isTransparent(int width, int height) {
		return false;
	}

.. _isTransparent(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/background/Background.html#isTransparent-int-int-

Applying the background on a graphics context
---------------------------------------------

The `apply(GraphicsContext g, int width, int height)`_ method is called by the MWT framework in order to render the background and to set or remove the background color of subsequent drawings.

For example, the following snippet applies a white background:

.. code-block:: Java

	@Override
	public void apply(GraphicsContext g, int width, int height) {
		g.setColor(Colors.WHITE);
		Painter.fillRectangle(g, 0, 0, width, height);
		g.setBackgroundColor(Colors.WHITE);
	}

.. _apply(GraphicsContext g, int width, int height): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/background/Background.html#apply-ej.microui.display.GraphicsContext-int-int-

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
