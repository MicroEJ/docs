How to Define an Outline or Border
==================================

To create a custom outline or border, a new class should be created, extending the `Outline`_ class.
Outline subclasses have to implement two methods, as explained in the following sections.

.. _Outline: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/outline/Outline.html

Applying the outline on an outlineable object
---------------------------------------------

The `apply(Outlineable)`_ method is called by the MWT framework in order to subtract the outline from a `Size`_ or `Rectangle`_ object.

The `Outlineable`_ parameter of the method initially contains the size or bounds of the box, including the outline.
Before the method returns, the outlineable object should be modified by subtracting the outline.
In order to remove the outline from the object, the `removeOutline()`_ method of ``Outlineable`` should be used, passing as argument the thickness on each side.

For example, the following snippet applies an outline of 1 pixel on every side:

.. code-block:: Java

	@Override
	public void apply(Outlineable outlineable) {
		outlineable.removeOutline(1, 1, 1, 1);
	}

.. _apply(Outlineable): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/outline/Outline.html#apply-ej.mwt.util.Outlineable-
.. _Size: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/util/Size.html
.. _Rectangle: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/util/Rectangle.html
.. _Outlineable: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/util/Outlineable.html
.. _removeOutline(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/util/Outlineable.html#removeOutline-int-int-int-int-

Applying the outline on a graphics context
------------------------------------------

The `apply(GraphicsContext, Size)`_ method is called by the MWT framework in order to render the outline (only relevant if it is a border) and to update the translation and clip of a graphics context.

The ``Size`` parameter of the method initially contains the size of the box, including the outline.
Before the method returns, the size object should be modified by subtracting the outline.
In order to remove the outline from the object, the `removeOutline()`_ method of ``Outlineable`` should be used, passing as argument the thickness on each side.

For example, the following snippet applies an outline of 1 pixel on every side:

.. code-block:: Java

	@Override
	public void apply(GraphicsContext g, Size size) {
		size.removeOutline(1, 1, 1, 1);
		g.translate(1, 1);
		g.setClip(0, 0, size.getWidth(), size.getHeight());
	}

.. _apply(GraphicsContext, Size): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/outline/Outline.html#apply-ej.microui.display.GraphicsContext-ej.mwt.util.Size-

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
