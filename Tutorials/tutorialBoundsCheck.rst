String bounds check on a Widget
===============================
The issue
-------------
- When creating an application, it may support multiple languages, some of those languages have words and phrases that may be bigger than first planned when creating an application

Extending a Widget
-------------------
- Firstly, to add a check for label size, the Widget needs to be extendend,on this example, the Label class will be used for this purpose

.. code-block:: java

    public class MyLabel extends Label {

        public MyLabel(String txt) {
            super(txt);
        }

        @Override
        protected void onLaidOut() {

        }
    }

Overriding onLaidOut
--------------------
- After a widget is laidOut, the onLaidOut method is called, so, overriding this method is possible to check whether or not the text fits 
- Inside of the method ,get the Font from the Style that the widget is using, and then, get the Font 

.. code-block:: java

    @Override
    protected void onLaidOut() {
        final Font font = getStyle().getFont();
        final String text = getText();
        final int stringWidth = font.stringWidth(text);
        final int labelWidth = this.getContentBounds().getWidth();
        if (stringWidth > labelWidth) {
            System.err.println("The text size is greater than the Widget content Width!");
        }
    }

Testing with canvas
--------------------
- Using canvas, it's possible to set constraints to each added widget
  
.. code-block:: java

    public static void main(String[] args) {
        MicroUI.start();
        Desktop desktop = new Desktop();
        Canvas canvas = new Canvas();
        canvas.addChild(new MyLabel("Teste"), 15, 0, 15, 10);
        desktop.setWidget(canvas);
        desktop.requestShow();
    }

.. image:: images/tuto_microej_bounds_check.png

- and the console should show this

.. code-block:: console

The text size is greater than the Widget content Width!

Improving the Bounds Check
----------------------------
- To make the debugging process easier, it's possible to show on which section of the text is truncated 

.. code-block:: java

    @Override
    protected void onLaidOut() {
        final Font font = getStyle().getFont();
        final String text = getText();
        final int stringWidth = font.stringWidth(text);
        final int labelWidth = this.getContentBounds().getWidth();
        if (stringWidth > labelWidth) {
            for (int i = text.length() - 1; i >= 0; i--) {
                if (font.substringWidth(text, 0, i) <= labelWidth) {
                    System.out.println(text + "\" trucantes after \"" + text.substring(0, i) + "\""); //$NON-NLS-1$ //$NON-NLS-2$
                    break;
                }

            }
        }
    }

- This block of code can be also extracted to a helper class,to be used also in other Widgets, not only the one extending Label

.. code-block:: java
    public class LabelBoundsCheck {

    static void fits(final Font font, final String text, final int contentWidth) {
        if (Constants.getBoolean("myapp.debugtextsize")) {
            int stringWidth = font.stringWidth(text);
            if (stringWidth > contentWidth) {
                for (int i = text.length() - 1; i >= 0; i--) {
                    if (font.substringWidth(text, 0, i) <= contentWidth) {
                        System.out.println(text + "\" trucantes after \"" + text.substring(0, i) + "\""); //$NON-NLS-1$ //$NON-NLS-2$
                        break;
                    }

                }
            }
        }
    }
    }



