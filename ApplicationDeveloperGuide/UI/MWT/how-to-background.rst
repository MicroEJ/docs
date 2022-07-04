How to Define a Background
==========================

To create a custom background, a new class should be created, extending the `Background <https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/background/Background.html>`_ class.
Background subclasses have to implement two methods, as explained in the following sections.

Informing whether the background is transparent
-----------------------------------------------

The `isTransparent() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/background/Background.html#isTransparent-int-int->`_ method is called by the MWT framework in order to know whether or not the background is transparent.
A background is considered as transparent if it does not draw every pixel with maximal opacity when it is applied.

For example, the following snippet informs that the background is completely opaque regardless of its size:

.. code-block:: Java

	@Override
	public boolean isTransparent(int width, int height) {
		return false;
	}

Applying the background on a graphics context
---------------------------------------------

The ``apply(GraphicsContext g, Size size)`` method is called by the MWT framework in order to render the background and to set or remove the background color of subsequent drawings.

For example, the following snippet applies a white background:

.. code-block:: Java

	@Override
	public void apply(GraphicsContext g, Size size) {
		g.setColor(Colors.WHITE);
		Painter.fillRectangle(g, 0, 0, size.getWidth(), size.getHeight());
		g.setBackgroundColor(Colors.WHITE);
	}

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
