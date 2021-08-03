Creating a Contact List using Scroll List
=========================================

Creating the Contact Widget
---------------------------

- As explained in Creating Widget, it is possible to create our own widget by
  just extending the Widget class.
- First, let's create a constructor with all the things that we are
  going to need for this.

  .. code:: java

    public ContactWidget(String contactName, Image image) {
       this.contactName = contactName;
       this.image = image;
    }

- Then, overriding the two abstract methods of Widget

  .. code:: java

    @Override
    protected void computeContentOptimalSize(Size size) {
       Font f = getStyle().getFont();
       int height = Math.max(f.getHeight(), this.image.getHeight());
       int stringWidth = f.stringWidth(this.contactName);
       int width = stringWidth + this.image.getWidth();
       size.setSize(width, height);
    }

  .. code:: java

    @Override
    protected void renderContent(GraphicsContext g, int contentWidth, int contentHeight) {
       g.setColor(Colors.BLACK);
       Painter.drawImage(g, this.image, 0, 0);
       int cornerEllipseSize = contentHeight / 2;
       int imageWidth = this.image.getWidth();
       int imageHeight = this.image.getHeight();
       Painter.drawRoundedRectangle(g, 0, 0, imageWidth, imageHeight, cornerEllipseSize, cornerEllipseSize);
       Painter.drawString(g, this.contactName, getStyle().getFont(), imageWidth + 2, contentHeight / 3);
    }

- Then, simply replace the children in the List used in the last step:

  .. code:: java

    for (int i = 0; i < 45; i++) {
       list.addChild(new ContactWidget("Label" + i, Image.getImage("/images/microej_logo.png")));
    }

- The class is as follows:

  .. code:: java

    public class ContactWidget extends Widget {

       private String contactName;
       private Image image;

       public ContactWidget(String contactName, Image image) {
          this.contactName = contactName;
          this.image = image;
       }

       @Override
       protected void computeContentOptimalSize(Size size) {
          Font f = getStyle().getFont();
          int height = Math.max(f.getHeight(), this.image.getHeight());
          int stringWidth = f.stringWidth(this.contactName);
          int width = stringWidth + this.image.getWidth();
          size.setSize(width, height);
       }

       @Override
       protected void renderContent(GraphicsContext g, int contentWidth, int contentHeight) {
          g.setColor(Colors.BLACK);
          Painter.drawImage(g, this.image, 0, 0);
          int cornerEllipseSize = contentHeight / 2;
          int imageWidth = this.image.getWidth();
          int imageHeight = this.image.getHeight();
          Painter.drawRoundedRectangle(g, 0, 0, imageWidth, imageHeight, cornerEllipseSize, cornerEllipseSize);
          Painter.drawString(g, this.contactName, getStyle().getFont(), imageWidth + 2, contentHeight / 3);
       }
    }

  .. image:: images/listcontact.png
   :align: center

