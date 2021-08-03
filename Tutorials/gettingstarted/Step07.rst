Basic Drawing on Screen
=======================

- It is also possible to have access to a drawable interface that represents a pixelated version of the Display.

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

- The ``Painter`` class contains several primitives to draw geometric objects.
- The code below draws each component with the selected color (yellow, purple, green).
- The ``drawLine()`` method uses the starting and finishing point with x and y coordinates.
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

- The ``Painter`` class contains several primitives to draw images.

  .. code:: java

    Image image = Image.getImage("/images/microej_logo.png");
    // Draws the image at x,y coordinates (150, 50).
    Painter.drawImage(g, image, 150, 50);

  .. image:: images/imagedrawable.png
   :align: center

Drawing Thick Shapes
--------------------

- The ``ShapePainter`` class offers a set of primitives to render thick shapes with or without anti-aliasing.
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
