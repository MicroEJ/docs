.. _ui-creating-widgets:

Creating Widgets
================

- To create a widget, we need to create a class that extends the `Widget`_ superclass.
- In this example, we are going to create a simple progress bar.
- So create a MyProgressBarWidget class extending Widget.

.. note::
    
   The `computeContentOptimalSize()`_ and `renderContent()`_ methods must be overridden:

   .. code:: java

    public class MyProgressBarWidget extends Widget {
       @Override
       protected void computeContentOptimalSize(Size size) {
          // TODO Auto-generated method stub
       }

       @Override
       protected void renderContent(GraphicsContext g, int contentWidth, int contentHeight) {
          // TODO Auto-generated method stub
       }
    }

Setting Up
----------

- Let's use a progress bar with a fixed size:

  .. code:: java

    protected void computeContentOptimalSize(Size size) {
       size.setSize(200,50);
    }

- Then, let's create the progress bar, first, it is important to add a progress value:

  .. code:: java

    private float progressValue;

- Now, let's render the progress bar:

  .. code:: java

    protected void renderContent(GraphicsContext g, int contentWidth, int contentHeight) {
       // Draws the remaining bar: a 1 px thick grey line, with 1px of fading.
       g.setColor(Colors.SILVER);
       int halfHeight = contentHeight / 2;
       ShapePainter.drawThickFadedLine(g, 0, halfHeight, contentWidth, halfHeight, 1, 1, Cap.ROUNDED, Cap.ROUNDED);

       // Draws the progress bar: a 3 px thick blue line, with 1px of fading.
       g.setColor(Colors.NAVY);
       int barWidth = (int) (contentWidth * this.progressValue);
       ShapePainter.drawThickFadedLine(g, 0, halfHeight, barWidth, halfHeight, 3, 1, Cap.ROUNDED, Cap.ROUNDED);
    }

- Finally, let's create a method to set the progress on the progress bar:

  .. code:: java

    public void setProgress(float progress) {
       this.progressValue = progress;
    }

Using with Animator
-------------------

- Using the code made in the previous Animation tutorial, doing the modifications below, it is now possible to see the progress bar animated:

  .. code:: java

    public static void main(String[] args) {
       MicroUI.start();
       Desktop desktop = new Desktop();
       final MyProgressBarWidget progressBar = new MyProgressBarWidget();
       Flow flow = new Flow(LayoutOrientation.VERTICAL);
       flow.addChild(progressBar);

       Animation progressBarAnimation = new Animation() {

          float progress;

          @Override
          public boolean tick(long currentTimeMillis) {
             this.progress += 0.001f;
             progressBar.setProgress(this.progress);
             progressBar.requestRender();
             return true;
          }
       };
       Animator animator = desktop.getAnimator();
       animator.startAnimation(progressBarAnimation);
       desktop.setWidget(flow);
       desktop.requestShow();
    }

  .. image:: images/progressbar.png
   :align: center

.. _Widget: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html
.. _computeContentOptimalSize(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#computeContentOptimalSize-ej.mwt.util.Size-
.. _renderContent(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#renderContent-ej.microui.display.GraphicsContext-int-int-

**Next step:** :ref:`ui-using-layouts`

..
   | Copyright 2021-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

