Images
======

Adding Images
-------------

- Create two packages in the Resources folder, one named ``list`` and another named ``images``.

- Create an images list file, and add it to the ``list`` package (``myapp.images.list``).

- Save the following image to the ``images`` package:
  
  .. image:: images/microej_logo.png

- The structure looks like this:

  .. image:: images/resources.png

- Then go to the ``myapp.images.list`` and add the image file:

  .. code::

    /images/microej_logo.png:ARGB4444

- The image declaration in the .list file follows this pattern:

  .. code::

    path:format

-  ``path`` is the path to the image file, relative to the ``resources`` folder.
-  ``format`` specifies how the image will be embedded in the application.

.. note:: The ARGB4444 mode is used here because the image has transparency, more info in the  :ref:`section.ui.Images` section.

Displaying an Image
-------------------

- To display this image, first create an instance of the widget ``ImageWidget``, specifying the path to the image in the constructor:

  .. code:: java

    ImageWidget image = new ImageWidget("/images/microej_logo.png");

- Add the widget to the canvas container by adding this line:

  .. code:: java

    canvas.addChild(image, 0, 30, Widget.NO_CONSTRAINT, Widget.NO_CONSTRAINT);

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

       ImageWidget image = new ImageWidget("/images/microej_logo.png");
       canvas.addChild(image, 0, 30, Widget.NO_CONSTRAINT, Widget.NO_CONSTRAINT);

       CascadingStylesheet css = new CascadingStylesheet();
       EditableStyle style = css.getSelectorStyle(new TypeSelector(Label.class));
       style.setColor(Colors.RED);
       style.setBorder(new RectangularBorder(Colors.BLACK, 1));

       desktop.setStylesheet(css);
       desktop.setWidget(canvas);
       desktop.requestShow();
    }

  .. image:: images/imagessimulator.png
    :align: center 

..
   | Copyright 2021-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

    