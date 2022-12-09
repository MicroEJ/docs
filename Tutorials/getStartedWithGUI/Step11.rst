.. _ui-scroll-list:

Scroll List
===========

List
----

- A list is a container that lays out its children one after the other in a single column or row depending on its orientation.
- The size of each widget is set proportionally to its optimal size and the available size.
- Naturally, it shows some issues if the list contains too many components.
- Adding 45 items to a list shows the following result:

  .. code:: java

     public static void main(String[] args) {
        MicroUI.start();
        Desktop desktop = new Desktop();

        List list = new List(LayoutOrientation.VERTICAL);
        for (int i = 0; i < 45; i++) {
           Label label = new Label("Label" + i);
           list.addChild(label);
        }

        desktop.setWidget(list);
        desktop.requestShow();
     }

  .. image:: images/listsample.png
   :align: center

- To be able to see all the items, the list must be bigger than the display. So it needs to be included in another container that is able to scroll it.

Scrollable List
---------------

- A simple way to see all the items correctly and scroll the list is to include it in a ``Scroll`` container:

  .. code:: java 

     public static void main(String[] args) {
        MicroUI.start();
        Desktop desktop = new Desktop();
        List list = new List(LayoutOrientation.VERTICAL);
        for (int i = 0; i < 45; i++) {
           Label item = new Label("Label" + i);
           list.addChild(item);
        }
        CascadingStylesheet css = new CascadingStylesheet();
        Scroll scroll = new Scroll(LayoutOrientation.VERTICAL);
        scroll.setChild(list);
        desktop.setStylesheet(css);
        desktop.setWidget(scroll);
        desktop.requestShow();
     }

  .. image:: images/scrollbar.png
   :align: center

- The list can be optimized for the scroll (to exclude the items that are outside the visible area).
  A scrollable list is available at `Widget Demo <https://github.com/MicroEJ/Demo-Widget/tree/master/com.microej.demo.widget/src/main/java/com/microej/demo/widget/scrollablelist/widget>`__.
- It can be copied in the project and replace the list:

  .. code:: java 

     public static void main(String[] args) {
        MicroUI.start();
        Desktop desktop = new Desktop();
        ScrollableList list = new ScrollableList(LayoutOrientation.VERTICAL);
        for (int i = 0; i < 45; i++) {
           Label label = new Label("Label" + i);
           list.addChild(label);
        }
        CascadingStylesheet css = new CascadingStylesheet();
        Scroll scroll = new Scroll(LayoutOrientation.VERTICAL);
        scroll.setChild(list);
        desktop.setStylesheet(css);
        desktop.setWidget(scroll);
        desktop.requestShow();
     }

**Next step:** :ref:`ui-contact-list`

..
   | Copyright 2021-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

     