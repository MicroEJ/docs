How to detect text overflow
===========================


Widgets that display some text may experience text overflow when the strings are too long to fit into the available area. It can be the case, for example, in applications that support multiple languages because widgets have to deal with texts of different lengths.


Instrumenting the widget
------------------------

The goal is to check whether the text to be displayed is within the content bounds of the widget. A way to test this is to extend or modify the widget.
In this article, the widget ``MyLabel`` will extend the type ``Label`` from the Widget library, which displays a text:

.. code-block:: java

    public class MyLabel extends Label {

        public MyLabel(String text) {
            super(text);
        }
    }


Overriding the onLaidOut() method
---------------------------------
 
Once the position and size of a wigdet are set during the lay out process, the ``onLaidOut()`` method is called to notify the widget.
Overriding this method is a good place to check whether the text overflows or not.

For example, the following snippet compares the text width with the available width: it will print a message if an overflow is detected.

.. code-block:: java

    @Override
    protected void onLaidOut() {
        super.onLaidOut();
        final Font font = getStyle().getFont();
        final String text = getText();
        // compute the width of the text with the specified font
        final int textWidth = font.stringWidth(text);
        // get the available width for the content of the widget (excluding outlines)
        final int contentWidth = getContentBounds().getWidth();
        if (textWidth > contentWidth) {
            System.err.println("The text size is greater than the widget content width!");
        }
    }


Testing
-------

Here is a case where the widget size is set manually to be a little shorter than the text width:
  
.. code-block:: java

    public static void main(String[] args) {
        MicroUI.start();
        Desktop desktop = new Desktop();
        Canvas canvas = new Canvas();
        canvas.addChild(new MyLabel("Test"), 15, 0, 15, 10);
        desktop.setWidget(canvas);
        desktop.requestShow();
    }

.. image:: images/tuto_microej_bounds_check.png
    :alt: Text overflow example
    :align: center

The console should now log that a text overflow has been detected:

.. code-block:: console

    The text size is greater than the widget content width!


Improving the detection
-----------------------

To ease the correction process, it is best to add some additional debug information to locate the issue.

The following snippet adds:
* the text that overflows and where it truncates.
* the path to the widget in the widget hierachy to help the tester locate the affected widget in the GUI.

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
                    System.out.printErr(text + "\" truncates after \"" + text.substring(0, i) + "\""); //$NON-NLS-1$ //$NON-NLS-2$
                    break;
                }

            }
        }
    }


This code may also be extracted to a helper class in order to be used in other widgets:

.. code-block:: java

    public class MyTextHelper {

        public static void checkTextOverflow(final Font font, final String text, final int contentWidth) {
            if (Constants.getBoolean("com.mycompany.check.text.overflow")) {
                int stringWidth = font.stringWidth(text);
                if (stringWidth > contentWidth) {
                    for (int i = text.length() - 1; i >= 0; i--) {
                        if (font.substringWidth(text, 0, i) <= contentWidth) {
                            System.out.printErr(text + "\" truncates after \"" + text.substring(0, i) + "\""); //$NON-NLS-1$ //$NON-NLS-2$
                            break;
                        }
                    }
                }
            }
        }
    
    }

.. note::

    Note the usage of :ref:`BON constants <section.classpath.elements.constants>` ``com.mycompany.check.text.overflow``. The debug code will not be embedded in the production firmware when the constant is set to ``false``.
    It also disables the extra verbosity.


