.. _ui-style:

Style
=====

Instances of `Desktop`_, `Widget`_, and `Container`_ classes are semantic elements of the GUI, describing the structure and meaning of the content.

The Style API (`ej.mwt.style`_) defines style options for widgets, allowing for a clear separation of the core structure (content) and the design aspects (colors, fonts, spacing, background, etc.).
   
.. note::
   Some of the attributes are inspired by CSS, like Background, Border, Color, Dimension, Font, Alignment, Margin/Padding.
   And the `CascadingStylesheet`_ manages the order of the selectors (with their specificity), the cascading, etc.


.. _Desktop: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html
.. _Widget: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html
.. _Container: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html
.. _ej.mwt.style: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/package-summary.html
.. _CascadingStylesheet: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/stylesheet/cascading/CascadingStylesheet.html

Selectors
---------

Selectors determine the widget(s) to which a style applies. There are three main types of selectors:

-  Simple selectors (based on type or class),
-  State Selectors (based on state or position),
-  Combinators (based on relationships or conditions).

.. note::
    More of this will be presented in the :ref:`ui-advanced-styling` step.

Usage
`````

- With a `CascadingStylesheet`_, we can define a style for all labels using a TypeSelector:

  .. code:: java

   CascadingStylesheet stylesheet = new CascadingStylesheet();
   EditableStyle style = stylesheet.getSelectorStyle(new TypeSelector(Label.class));

- We can now change the style object options. In this sample, we change the base color to red and adding a black rectangular border of 1px thickness.

  .. code:: java

   style.setColor(Colors.RED);
   style.setBorder(new RectangularBorder(Colors.BLACK, 1));

- For these options to take effect, bind the stylesheet to the desktop.

  .. code:: java

   desktop.setStylesheet(stylesheet);

- The final code looks like this:

  .. code:: java

   public static void main(String[] args) {
      MicroUI.start();
      Desktop desktop = new Desktop();
      Label label = new Label("Hello World");
      Label label2 = new Label("Hello World 2");

      Canvas canvas = new Canvas();
      canvas.addChild(label, 0, 0, Widget.NO_CONSTRAINT, Widget.NO_CONSTRAINT);
      canvas.addChild(label2, 0, 15, Widget.NO_CONSTRAINT, Widget.NO_CONSTRAINT);

      CascadingStylesheet stylesheet = new CascadingStylesheet();
      EditableStyle style = stylesheet.getSelectorStyle(new TypeSelector(Label.class));
      style.setColor(Colors.RED);
      style.setBorder(new RectangularBorder(Colors.BLACK, 1));

      desktop.setStylesheet(stylesheet);
      desktop.setWidget(canvas);
      desktop.requestShow();
   }

  .. image:: images/styleborder.png
   :align: center 

Padding and Margin
~~~~~~~~~~~~~~~~~~

- Using margin and padding is pretty simple. Adding margin is as follows:

  .. code:: java

   style.setMargin(new UniformOutline(4));

  .. image:: images/margin.png
   :align: center

- Setting an oversized margin looks like this:

  .. code:: java
   
   style.setMargin(new UniformOutline(10));
   
  .. image:: images/tuto_microej_gettingstarted_oversizedmargin.png
   :align: center

- Adding padding:

  .. code:: java

   style.setPadding(new UniformOutline(2));


  .. image:: images/marginandpadding.png
   :align: center

- Oversizing the padding (the widgets ovelap each other because we use a canvas with fixed positions):

  .. code:: java
 
   style.setPadding(new UniformOutline(15));


  .. image:: images/tuto_microej_gettingstarted_oversizedmarginandpadding.png  
   :align: center

**Next step:** :ref:`ui-images`

..
   | Copyright 2021-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
  