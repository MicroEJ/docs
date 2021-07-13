Hiding a Widget
====================
- To hide a widget, it's possible to use desktops to show and hide then at will 
- in the sample below, The desktop will be exchanged with the one with the container/widget

Using Desktop To hide a widget
---------------------------------

In the code Sample below, a button is created to change the Desktop when clicked, a new desktop with a widget is created, hiding the ones behind it

.. code-block:: java

    MicroUI.start();
    Desktop desktop = new Desktop();
    Canvas c;
    MyFlow list = new MyFlow();
    list.addChild(new Label("Label 1"));
    list.addChild(new Label("Label 2"));
    Button b = new Button("Click to change the Widget");
    Desktop desktop2 = new Desktop();
    b.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick() {
            desktop2.setWidget(new Label("new Widget"));
            desktop2.requestShow();
        }
    });
    list.addChild(b);
    desktop.setWidget(list);
    desktop.requestShow();

it's possible to go back with the old desktop by just requesting show on the old desktop 

.. image:: images/hidewidgetshow.png

.. image:: images/hidewidgethidden.png

