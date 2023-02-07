.. _ui-basic-drawing-on-screen:

Basic Drawing on Screen
=======================

- We have seen a basic use of the MWT and widgets libraries. Before going further let's see how to write directly on a display using both Displayable and GraphicsContext classes.
- A Displayable represents what can be shown on a screen, a GraphicsContext provides access to a modifiable (readable and writable) pixel buffer to be associated with an Image or a Displayable.
- It is then possible to have access to a drawable interface that represents a pixelated version of the Display.

  .. code:: java
    
    public static void main(String[] args){
       MicroUI.start();
       Displayable myDisplayable = new Displayable() {

          @Override
          protected void render(GraphicsContext g) {
             // Draws a yellow line.
             g.setColor(Colors.YELLOW);
             Painter.drawLine(g, 0, 0, 100, 50);
          }

          @Override
          public boolean handleEvent(int event) {
             return false;
          }
       };

       Display.getDisplay().requestShow(myDisplayable);
    }
   
- This draws a line from the coordinates of the display ``(0,0)`` to ``(100,50)``.
   
  .. image:: images/drawline.png
   :align: center
 
Drawing Basic Shapes
--------------------

- The `Painter`_ class contains several primitives to draw geometric objects.
- The code below draws each component with the selected color (yellow, purple, green).
- The `drawLine()`_ method uses the starting and finishing point with x and y coordinates.
- Fill rectangle and ellipse methods use x and y coordinates and also width and height.
- Draw circle uses x and y and a diameter.

  .. code:: java

    g.setColor(Colors.YELLOW);
    Painter.drawLine(g, 0, 0, 100, 50);

    g.setColor(Colors.PURPLE);
    Painter.fillRectangle(g, 10, 20, 100, 20);
    Painter.fillEllipse(g, 120, 50, 20, 100);

    g.setColor(Colors.GREEN);
    Painter.drawCircle(g, 50, 50, 100);

  .. image:: images/geometry.png
   :align: center
       
Drawing Images
--------------

- The `Painter`_ class contains several primitives to draw images.

  .. code:: java

    Image image = Image.getImage("/images/microej_logo.png");
    // Draws the image at x,y coordinates (150, 50).
    Painter.drawImage(g, image, 150, 50);

  .. image:: images/imagedrawable.png
   :align: center

Drawing Thick Shapes
--------------------

- The `ShapePainter`_ class offers a set of primitives to render thick shapes with or without anti-aliasing.
- The code below shows how to draw a thick faded line.

  .. code:: java

    // Draws a thick yellow line. 
    g.setColor(Colors.YELLOW);
    ShapePainter.drawThickFadedLine(g, 20, 20, 100, 80, 10, 6, Cap.ROUNDED, Cap.PERPENDICULAR);

    // Draws a thick green circle.
    g.setColor(Colors.GREEN);
    ShapePainter.drawThickFadedCircle(g, 130, 20, 100, 20, 2);

  .. image:: images/thickshapes.png
   :align: center

.. _Painter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Painter.html
.. _drawLine(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Painter.html#drawLine-ej.microui.display.GraphicsContext-int-int-int-int- 
.. _ShapePainter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/drawing/ShapePainter.html

**Next step:** :ref:`ui-animation`

..
   | Copyright 2021-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

   