.. include:: aliases.rst

VectorFont
============

Overview
--------

The MicroVG library enables the usage of Vector Fonts. 

Compared to MicroUI Fonts (:ref:`section.ui.Fonts`), Vector Fonts brings these features:

- the text strings are scalable and can be transformed using a `Matrix` object.
- the TTF/OTF font files don't need to be preprocessed.
- the text strings can be drawn with opacity, a color or a linear gradient.

The library also considers the `Kerning` space described in the font file kerning table, and allows a fine adjustement of the inter-letters spacing.

Its also provides metrics measurement methods to correctly place the text within the surrounding drawing elements (i.e. in a label).

Loading a Font File
-------------------

Font files must be declared as ressources in a `.list` file available in the classpath(:ref:`chapter.microej.applicationResources`).

Then the font has to be loaded in a `VectorFont` object with a call to `ej.microvg.VectorFont.loadFont` <FIXME link to API>. This `VectorFont` object can then be used to draw text strings.


Drawing a String
----------------

A string can be drawn in the graphic context with a call to `ej.microvg.VectorFontPainter.drawString` <FIXME link to API>.

The text string height is scalable, and multiple font files can be used in parrallel.

|startTable| 

.. code-block:: java

      VectorFont font0 = VectorFont.loadFont("/fonts/Arial.ttf");
		VectorFont font1 = VectorFont.loadFont("/fonts/RAVIE.ttf");

		int x = 20;
		int y = 30;
		int yOffset = 150;

		g.setColor(Colors.LIME);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font0, 20, x, y);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font1, 20, x, y + yOffset);

		g.setColor(Colors.RED);
		y += 20;
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font0, 30, x, y);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font1, 30, x, y + yOffset);

		g.setColor(Colors.WHITE);
		y += 30;
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font0, 40, x, y);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font1, 40, x, y + yOffset);

		g.setColor(Colors.YELLOW);
		y += 40;
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font0, 50, x, y);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font1, 50, x, y + yOffset);

		display.flush();

|midTable| 

.. figure:: images/drawString0.png
   :width: 300px
   :align: center

|endTable| 

The text string can be colored with the graphic context color or a with a linear gradient(:ref:`Linear Gradient`).

`FillType` and `Alpha Blending Mode` are also managed similarly to `Path` drawing (refer to :ref:`FillType` and `Alpha Blending Mode`).

|startTable|

.. code-block:: java

   	g.setColor(Colors.LIME);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font, 50, x, y);

		LinearGradient gradient = new LinearGradient(0, 0, 250, 50, 
                                                new int[] { 0xffff0000, 0xffffff00, 0xffffffff });

		Matrix matrix = new Matrix();
		matrix.setTranslate(x, y + 60);
		VectorGraphicsPainter.drawGradientString(g, "Hello MicroEJ", font, 50, matrix, gradient, 0xff,
				BlendMode.SRC_OVER, 0);

|midTable| 

.. figure:: images/drawString1.png
   :width: 300px
   :align: center

|endTable| 

The text string can also be transformed with a `Matrix` to translate, rotate, scale the drawing.

|startTable|

.. code-block:: java

      Matrix matrix0 = new Matrix();

		matrix0.setTranslate(20, 60);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font, 50, matrix0, 0xff, BlendMode.SRC_OVER, 0);

		matrix0.preRotate(180);
		matrix0.postTranslate(300, 120);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font, 50, matrix0, 0xff, BlendMode.SRC_OVER, 0);

		Matrix matrix1 = new Matrix();
		matrix1.setScale(0.5f, 1.2f);
		matrix1.postRotate(45);
		matrix1.postTranslate(80, 200);

		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font, 50, matrix1, 0xff, BlendMode.SRC_OVER, 0);

		matrix1.setScale(0.5f, 1.2f);
		matrix1.postRotate(-45);
		matrix1.postTranslate(200, 300);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font, 50, matrix1, 0xff, BlendMode.SRC_OVER, 0);

|midTable| 

.. figure:: images/drawString2.png
   :width: 300px
   :align: center

|endTable| 

The inter character distance can also be adjust for each string drawing. By default, the inter character distance is take from the font file `kerning table <https://en.wikipedia.org/wiki/Kerning>`_, if any. The letterSpacing drawString() parameter default value is 0 pixel, a positive/negative value will increase/reduce the inter space distance by the corresponding pixel value.

|startTable|

.. code-block:: java

      Matrix matrix = new Matrix();

		matrix.setTranslate(20, 60);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font, 50, matrix, 0xff, BlendMode.SRC_OVER, 0);

		matrix.postTranslate(0, 60);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font, 50, matrix, 0xff, BlendMode.SRC_OVER, 5f);

		matrix.postTranslate(0, 60);
		VectorGraphicsPainter.drawString(g, "Hello MicroEJ", font, 50, matrix, 0xff, BlendMode.SRC_OVER, -2);

|midTable| 

.. figure:: images/drawString3.png
   :width: 300px
   :align: center

|endTable| 

The library supports the drawing of colored multilayer glyphs.


Draw a String on Circular arc
-----------------------------



..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.