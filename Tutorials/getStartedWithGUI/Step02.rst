Using Layouts
=============

The lay out process determines the position and size of the widgets.
It depends on:

-  The layout of the containers: how the children are arranged within the containers.
-  The widgets content size: the size needed by the widgets for optimal display.

This process is started automatically when the desktop is shown.
It can also be triggered programmatically.

Using a Flow Layout
-------------------

The flow layout lays out any number of children horizontally or vertically, using multiple rows if necessary depending on the size of each child widget.

.. image:: images/flowexample.png
   :align: center

Creating a flow layout:

- First, instantiate a `Flow`_ container, then add two `Label`_ objets to this container. 
- Finally, add the `Flow`_ container to the `Desktop`_.

.. code:: java

   public static void main(String[] args) {
      MicroUI.start();
      Desktop desktop = new Desktop();
      Label label = new Label("Hello World");
      Label secondLabel = new Label("Hello World 2");

      Flow flowContainer = new Flow(LayoutOrientation.HORIZONTAL);
      flowContainer.addChild(label);
      flowContainer.addChild(secondLabel);

      desktop.setWidget(flowContainer);
      desktop.requestShow();
   }

Both of the labels will share the screen:

.. image:: images/flowusage.png
   :align: center

   
Using a Canvas
--------------

A canvas lays out any number of children freely.

To add a widget to a `Canvas`_, specify its position and size.

.. note::
   Using `Widget.NO_CONSTRAINT`_ sets the width and height to the optimal size of the widget.

.. code:: java

   public static void main(String[] args) {
      MicroUI.start();
      Desktop desktop = new Desktop();
      Label label = new Label("Hello World");
      Label label2 = new Label("Hello World 2");

      Canvas canvas = new Canvas();
      canvas.addChild(label, 0, 0, Widget.NO_CONSTRAINT, Widget.NO_CONSTRAINT);
      canvas.addChild(label2, 15, 15, Widget.NO_CONSTRAINT, Widget.NO_CONSTRAINT);

      desktop.setWidget(canvas);
      desktop.requestShow();
   }

.. image:: images/canvassample.png
 :align: center 

.. _Flow: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/container/Flow.html
.. _Label: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/basic/Label.html
.. _Desktop: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html
.. _Canvas: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/container/Canvas.html
.. _Widget.NO_CONSTRAINT: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#NO_CONSTRAINT

..
   | Copyright 2021-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
