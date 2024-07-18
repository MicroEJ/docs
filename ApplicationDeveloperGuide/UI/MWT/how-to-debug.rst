.. _mwt_how_to_debug:

How to Debug
============

Highlighting the Bounds of the Widgets
--------------------------------------

When designing a UI, it can be pretty convenient to highlight the bounds of each widget.
Here are some cases where it helps:

- Verify if the layout fits the expected design.
- Set the outlines (margin, padding, border).
- Check the alignment of the widget content inside its bounds.

Setting the ``ej.mwt.debug.bounds.enabled`` constant to ``true`` will add a rectangle overlay over each widget and container.
For more information about constants, see the :ref:`section.classpath.elements.constants` section.

By default, the rectangles around the widgets are magenta.
But their color can be adjusted by modifying the ``ej.mwt.debug.bounds.color`` constant.

Here is an example of a ``xxx.constants.list`` file with the result in an application:

.. code-block::

	ej.mwt.debug.bounds.enabled=true
	ej.mwt.debug.bounds.color=0x00ff00

.. figure:: images/highlightWidgetList.png
	:alt: Highlight widgets in a list
	:align: center
 
.. figure:: images/highlightWidgetWheel.png
	:alt: Highlight widgets in a wheel
	:align: center

.. note:: Available since MWT 3.3.0.

Monitoring the Render Operations
--------------------------------

When developing a GUI application, it may not be obvious what/how exactly the UI is rendered.
Especially, when a widget can be re-rendered from a distant part of the application code.
Or simply because of the ``RenderPolicy`` used.

MWT provides a way to inject a monitor for the following render operations:

* Render requests done by the Application.
* Successive render executions triggered by the ``RenderPolicy``.

Setting the ``ej.mwt.debug.render.enabled`` constant to ``true`` will enable the monitoring of above render operations.
For more information about the monitoring mechanism, see `RenderPolicy Javadoc <https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/render/RenderPolicy.html>`_.
For more information about constants, see the :ref:`section.classpath.elements.constants` section.

The Widget library provides a default monitor implementation that prints the operations on the standard output.
The logs produced also contain information about what is rendered (widget and area) and what code requested the rendering.
For more information about this monitor implementation, see `RenderMonitor Javadoc <https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/debug/RenderMonitor.html>`_.

To use a different implementation (and if Widget is not in the classpath), set the ``ej.mwt.debug.render.monitor`` constant
to the FQN of the monitor implementation class.

Here is an example of a ``xxx.constants.list`` file with the result in an application:

.. code-block::

	ej.mwt.debug.render.enabled=true
	ej.mwt.debug.render.monitor=ej.widget.debug.RenderMonitor

.. figure:: images/renderWidgetBefore.png
	:alt: Radio Button page in Widget examples with "Money" selected
	:align: center

	Screenshot before click

.. code-block::
	:caption: Application logs after click

	rendermonitor@ INFO: Render requested on com.microej.demo.widget.common.PageHelper$2 > SimpleDock > OverlapContainer > SimpleDock > List > RadioButton at {0,0 87x25} of {221,116 87x25} by com.microej.demo.widget.radiobutton.widget.RadioButtonGroup.setChecked(RadioButtonGroup.java:47)
	rendermonitor@ INFO: Render requested on com.microej.demo.widget.common.PageHelper$2 > SimpleDock > OverlapContainer > SimpleDock > List > RadioButton at {0,0 87x25} of {221,166 87x25} by com.microej.demo.widget.radiobutton.widget.RadioButtonGroup.setChecked(RadioButtonGroup.java:50)
	rendermonitor@ INFO: Render executed on  com.microej.demo.widget.common.PageHelper$2 > SimpleDock > OverlapContainer > SimpleDock > List > RadioButton at {-221,-116 87x25} of {221,116 87x25}
	rendermonitor@ INFO: Render executed on  com.microej.demo.widget.common.PageHelper$2 > SimpleDock > OverlapContainer > SimpleDock > List > RadioButton at {-221,-141 87x25} of {221,141 87x25}
	rendermonitor@ INFO: Render executed on  com.microej.demo.widget.common.PageHelper$2 > SimpleDock > OverlapContainer > SimpleDock > List > RadioButton at {-221,-166 87x25} of {221,166 87x25}
	rendermonitor@ INFO: Render executed on  com.microej.demo.widget.common.PageHelper$2 > SimpleDock > OverlapContainer > ImageWidget at {133,116 87x25} of {44,0 20x16}
	rendermonitor@ INFO: Render executed on  com.microej.demo.widget.common.PageHelper$2 > SimpleDock > OverlapContainer > ImageWidget at {133,-140 87x25} of {44,256 20x16}
	rendermonitor@ INFO: Render executed on  com.microej.demo.widget.common.PageHelper$2 > SimpleDock > OverlapContainer > SimpleDock > List > RadioButton at {-221,-116 87x25} of {221,166 87x25}
	rendermonitor@ INFO: Render executed on  com.microej.demo.widget.common.PageHelper$2 > SimpleDock > OverlapContainer > ImageWidget at {133,166 87x25} of {44,0 20x16}
	rendermonitor@ INFO: Render executed on  com.microej.demo.widget.common.PageHelper$2 > SimpleDock > OverlapContainer > ImageWidget at {133,-90 87x25} of {44,256 20x16}

.. figure:: images/renderWidgetAfter.png
	:alt: Radio Button page in Widget examples with "Energy" selected
	:align: center

	Screenshot after click

.. note:: Available since MWT 3.5.0 & Widget 5.0.0.

.. _section_monitoring_animators:

Monitoring the Animators
------------------------

Since an animator ticks its animations as often as possible, the animator may take 100% CPU usage if none of its animations requests a render.

MWT provides a way to inject a monitor to be notified when none of the animations has requested a render during an animator tick.

Setting the ``ej.mwt.debug.animator.enabled`` constant to ``true`` will enable animator monitoring.
For more information about constants, see the :ref:`section.classpath.elements.constants` section.

The Widget library provides a default monitor implementation which logs warning messages.
The logs produced also contain information about the animations running on the animator.
The Animation instances are logged using their ``toString()`` method, so it can be a good idea to override this method
in the Animation subclasses to be able to identify them.

To use a different implementation (and if Widget is not in the classpath), set the ``ej.mwt.debug.animator.monitor`` constant
to the FQN of the monitor implementation class.

Here is an example of a ``xxx.constants.list`` file with the result in an application:

.. code-block::

	ej.mwt.debug.animator.enabled=true

.. code-block::
	:caption: Application logs when the watchface update animation is started but it doesn't request a render

	animatormonitor WARNING: No render requested during animator tick. Animations list: [Watchface update animation]

.. note:: Available since MWT 3.5.0 & Widget 5.0.0.

Detecting Text Overflow
-----------------------


Widgets that display a text may experience text overflow when the strings are too long to fit into the available area.
It can be the case, for example, in applications that support multiple languages because widgets have to deal with texts of different lengths.

This document presents a solution to detect such text overflows.


Instrumenting the Widget
~~~~~~~~~~~~~~~~~~~~~~~~

The goal is to check whether the text to be displayed is within the content bounds of the widget. A way to test this is to extend or modify the widget.
In this article, the widget ``MyLabel`` will extend the type `Label`_ from the Widget library, which displays a text:

.. code-block:: java
    :emphasize-lines: 3

    import ej.widget.basic.Label;

    public class MyLabel extends Label {

        public MyLabel(String text) {
            super(text);
        }
    }


.. _Label: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/basic/Label.html

Overriding the onLaidOut() Method
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
Once the position and size of a wigdet are set during the lay out process, the `onLaidOut()`_ method is called to notify the widget.
Overriding `onLaidOut()`_ of class ``MyLabel`` is a good place to check whether the text overflows or not.

For example, the following snippet compares the text width with the available width: it will print a message if an overflow is detected.

.. code-block:: java
    :emphasize-lines: 12,13,14

    @Override
    protected void onLaidOut() {
        super.onLaidOut();
        
        // compute the width of the text with the specified font
        final Font font = getStyle().getFont();
        final String text = getText();
        final int textWidth = font.stringWidth(text);
        
        // compare to the width available for the content of the widget
        final int contentWidth = getContentBounds().getWidth();
        if (textWidth > contentWidth) {
            System.out.println("Overflow detected:\n > Text: \"" + text + "\"\n > Width = " + textWidth + " px (available: " + contentWidth + " px)");
        }
    }

.. _onLaidOut(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#onLaidOut--

Testing
~~~~~~~

Here is a case where the widget size is set manually to be a little shorter than the text width:
  
.. code-block:: java
    :emphasize-lines: 6

    public static void main(String[] args) {
        MicroUI.start();
        Desktop desktop = new Desktop();
        Canvas canvas = new Canvas();
        // add a label with an arbitrary fixed width of 25 pixels (which is too short)
        canvas.addChild(new MyLabel("Some text"), 20, 20, 25, 10);
        desktop.setWidget(canvas);
        desktop.requestShow();
    }

.. image:: images/tuto_microej_bounds_check.png
    :alt: Text overflow example
    :align: center

The text is cropped and the console logs that a text overflow has been detected:

.. code-block:: console

    =============== [ Initialization Stage ] ===============
    =============== [ Converting fonts ] ===============
    =============== [ Converting images ] ===============
    =============== [ Launching on Simulator ] ===============
    Overflow detected:
     > Text: "Some text"
     > Width = 47 px (available: 25 px)


Improving the Detection
~~~~~~~~~~~~~~~~~~~~~~~

To ease the correction process, it is best to add some additional debug information to locate the issue. 
Let's extract the text overflow detection into a helper class, so that it is available for all classes across the application.

The following snippet:
 
* extracts the text overflow detection into the class ``MyTextHelper``.
* prints the part of the text that is displayed.
* prints the path to the widget in the widget tree to help the tester locate the affected widget in the GUI.

.. code-block:: java
    :emphasize-lines: 13,30

    public class MyLabel extends Label {

        public MyLabel(String text) {
            super(text);
        }

        @Override
        protected void onLaidOut() {
            super.onLaidOut();

            final Font font = getStyle().getFont();
            final String text = getText();
            MyTextHelper.checkTextOverflow(this, text, font);
        }
    }

    public class MyTextHelper {

        /**
        * Checks whether the given text overflows for the specified widget and font. In the case where an overflow is
        * detected, the method prints a message that details the error.
        *
        * @param widget
        *            the widget that displays the text.
        * @param text
        *            the text to display.
        * @param font
        *            the font used for drawing the text.
        */
        public static void checkTextOverflow(final Widget widget, final String text, final Font font) {
            final int textWidth = font.stringWidth(text);
            final int contentWidth = widget.getContentBounds().getWidth();

            if (textWidth > contentWidth) {
                String displayedText = buildDisplayedText(text, font, contentWidth);
                String widgetPath = buildWidgetPath(widget);
                System.out.println(
                        "Overflow detected:\n > Text: \"" + text + "\"\n > Width = " + textWidth + " px (available: "
                                + contentWidth + " px) \n > Displayed: \"" + displayedText + "\"\n > Path : " + widgetPath);
            }
        }

        private static String buildDisplayedText(String text, Font font, int width) {
            for (int i = text.length() - 1; i > 0; i--) {
                if (font.substringWidth(text, 0, i) <= width) {
                    return text.substring(0, i);
                }
            }

            return "";
        }

        private static String buildWidgetPath(Widget widget) {
            StringBuilder builder = new StringBuilder();

            Widget ancestor = widget;
            do {
                builder.insert(0, " > " + ancestor.getClass().getSimpleName());
                ancestor = ancestor.getParent();
            } while (ancestor != null);
            builder.insert(0, widget.getDesktop().getClass().getSimpleName());

            return builder.toString();
        }
    }

When the application is launched again, the console shows more information about the text overflow:

.. code-block:: console

    =============== [ Initialization Stage ] ===============
    =============== [ Converting fonts ] ===============
    =============== [ Converting images ] ===============
    =============== [ Launching on Simulator ] ===============
    Overflow detected:
     > Text: "Some text"
     > Width = 47 px (available: 25 px) 
     > Displayed: "Some"
     > Path : Desktop > Canvas > MyLabel


To keep control over the extra verbosity and code size, one option is to use :ref:`BON constants <section.classpath.elements.constants>` to enable/disable this debug code at will.
In the following snippet, when the constant ``com.mycompany.check.text.overflow`` is set to ``false``, the debug code will not be embedded in the application.

.. code-block:: java
    :emphasize-lines: 2

    public static void checkTextOverflow(final Widget widget, final String text, final Font font) {
        if (Constants.getBoolean("com.mycompany.check.text.overflow")) {
            final int textWidth = font.stringWidth(text);
            final int contentWidth = widget.getContentBounds().getWidth();

            if (textWidth > contentWidth) {
                String displayedText = buildDisplayedText(text, font, contentWidth);
                String widgetPath = buildWidgetPath(widget);
                System.out.println(
                        "Overflow detected:\n > Text: \"" + text + "\"\n > Width = " + textWidth + " px (available: "
                                + contentWidth + " px) \n > Displayed: \"" + displayedText + "\"\n > Path : " + widgetPath);
            }
        }
    }


..
   | Copyright 2021-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
