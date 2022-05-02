Vector Graphics Images
======================

Overview
--------

Vector Graphics Images are graphical resources that can be accessed with a call to `ej.microvg.VectorImage.getImage` <FIXME link to api page>.
The images are converted at build-time (using the image generator tool) to immutable resources.

Images that must be processed by the image generator tool are declared
in ``*.vectorimages.list`` files. 
The file format is a standard Java properties file, each line representing a ``/`` separated
resource path relative to the MicroEJ classpath root referring to a
vector image file (e.g. ``.svg``, ``.xml``). The resource must be
followed by a parameter (separated by a ``:``) which defines
and/or describes the image output file format (raw format).
Currently accepted format are : 

- ":VGF" : vglite compatible format with coordinates encoded as floating points.

Example:

::

   # The following image is embedded 
   # as a PNG resource (decoded at run-time)
   /com/mycompany/MyImage1.svg:VGF
   /com/mycompany/androidVectorDrawable.xml:VGF

Supported input files
---------------------

The image generator tool supports the following input file formats:

-  SVG 
-  Android VectorDrawable

The vector graphics image objects are extracted and converted to paths made of Move, Line and Curves commands. 

Each path is associated with either a fill color or a linear gradient. All object strokes are converted to fill paths
at build-time.

Objects group transformations are also extracted from the input file and applied at run-time.


Drawing Images
---------------

Drawing and positioning images
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once an image has been loaded it can be drawn in the graphic context with a call to 
`ej.microvg.VectorGraphicsPainter.drawImage()` <FIXME link to api page>.

The image is associated with a transformation Matrix (see: <FIXME link Matrix section>) that
will be applied to translate, scale and/or rotate the image. 

The application can get the width and the height of the image with `ej.microvg.VectorImage.getWidth()` <FIXME link to api page> 
and `ej.microvg.VectorImage.getHeight()` <FIXME link to api page> to correctly scale and position the image in the application 
window.

.. code-block:: java

   public static void main(String[] args) {
      MicroUI.start();

	   Display display = Display.getDisplay();
	   GraphicsContext g = display.getGraphicsContext();

	   VectorImage image = VectorImage.getImage("/images/myImage.xml"); //$NON-NLS-1$

	   Matrix matrix = new Matrix();
	   matrix.setTranslate(80, 80);
	   matrix.preScale(250 / image.getWidth(), 250 / image.getHeight());

	   VectorGraphicsPainter.drawImage(g, image, matrix);

	   display.flush();
   }

Drawing with opacity
~~~~~~~~~~~~~~~~~~~~

The vector graphics image can be drawn with a global opacity level. 

.. code-block:: java

   VectorImage image = VectorImage.getImage("/images/myImage.xml"); //$NON-NLS-1$

   // the global opacity rendering value, between 0 (transparent) and 255 (opaque)
   int opacity = 0.5f;

   VectorGraphicsPainter.drawImage(g, image, matrix, opacity);

.. warning:: As paths are drawn one after the other, images that contain overlapping paths are not correctly 
   colored when a global opacity is applied. The rendering of these images will throw an exception. The images must
   be reworked to suppress overlapping, if the image needs to be drawn with a global opacity.

Color filtering
~~~~~~~~~~~~~~~



Animated Vector Graphics Image
------------------------------

The MicroVG VectorImage



Limitations
-----------


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.