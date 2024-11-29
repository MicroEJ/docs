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

Enabling Traces for System View
-------------------------------

MWT logs some keypoints when traces are enabled (see :ref:`event-tracing`).

Here is the list of the logs:

* The creation of a widget. A unique ID is associated to the widget at this moment that will be used in the other traces all along its lifetime.
* The creation of a desktop. A unique ID is associated to the desktop at this moment that will be used in the other traces all along its lifetime.
* The request to show a desktop.
* The request to layout a widget.
* The request to layout a desktop.
* The request to render a widget. The region of the rendering request is available in the trace.
* The request to render a desktop.
* The update of the style of a widget. There is another trace for the end of the cascading update of containers.
* The compute of the optimal size of a widget. There is another trace for the end of the cascading compute of containers.
* The lay out of a widget. There is another trace for the end of the cascading lay out of containers.
* The rendering of a widget. There is another trace for the end of the cascading rendering of containers.
* When a widget is shown.
* When a widget is hidden.
* When a desktop is shown.
* When a desktop is hidden.
* When a widget is attached.
* When a widget is detached.

It is possible to print more information about the created widgets and desktops (to associate the ID with an actual object).
It can be activated by setting the :ref:`Application Option <application_options>` named ``ej.mwt.debug.log.trace.enabled`` to ``true``.

The traces can be seen in SystemView.
For the traces to be more human-readable, the file ``SYSVIEW_MWT.txt``` must be put in SystemView installation folder (e.g. ``SEGGER/SystemView_V252a/Description/``).
This file can be found in the ``resources`` folder of the jar of MWT.
Otherwise, it can be created manually with the following content:

.. code-block::

   0   MWT_CreateWidget            (MWT) Create a widget (ID = %u, type = %x)
   1   MWT_CreateDesktop           (MWT) Create a desktop (ID = %u, type = %x)
   2   MWT_RequestShowDesktop      (MWT) Request to show a desktop (ID = %u)
   3   MWT_RequestLayout           (MWT) Request to layout a widget (ID = %u)
   4   MWT_RequestLayoutDesktop    (MWT) Request to layout a desktop (ID = %u)
   5   MWT_RequestRender           (MWT) Request to render a widget (ID = %u, x = %d, y = %d, width = %d, height = %d)
   6   MWT_RequestRenderDesktop    (MWT) Request to render a desktop (ID = %u)
   7   MWT_UpdateStyle             (MWT) Update the style of a widget (ID = %u)            | (MWT) Container style updated (ID = %u)
   8   MWT_ComputeOptimalSize      (MWT) Compute the optimal size of a widget (ID = %u)    | (MWT) Container size computed (ID = %u)
   9   MWT_Layout                  (MWT) Lay out a widget (ID = %u)                        | (MWT) Container layout done (ID = %u)
   10  MWT_Render                  (MWT) Render a widget (ID = %u)                         | (MWT) Container render done (ID = %u)
   11  MWT_OnShown                 (MWT) A widget is shown (ID = %u)
   12  MWT_OnHidden                (MWT) A widget is hidden (ID = %u)
   13  MWT_OnShownDesktop          (MWT) A desktop is shown (ID = %u)
   14  MWT_OnHiddenDesktop         (MWT) A desktop is hidden (ID = %u)
   15  MWT_OnAttached              (MWT) A widget is attached (ID = %u)
   16  MWT_OnDetached              (MWT) A widget is detached (ID = %u)

.. note:: Available since MWT 3.6.0.

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

.. _mwt_how_to_debug_source_rule:

Finding which Rule Originates the Attributes of a Widget's Style
----------------------------------------------------------------

The method `CascadingStylesheet.getStyleSources()`_ is able to retrieve the selectors used to create a Style (that has been originated from a CascadingStylesheet).
It requires to set the constant ``ej.mwt.debug.cascadingstyle.enabled`` to ``true``.

The result of this method is an array containing 16 selectors: one for each parameter of the style.
The indices for each style entry are available as constants in the ``CascadingStylesheet`` class.
For each entry, the selector belongs to the rule selected to fill the matching parameter (thus set by `getSelectorStyle()`_).
A ``null`` entry means that the parameter is from the default style (thus set by `getDefaultStyle()`_).

This feature is used in the :ref:`HierarchyInspector <widget_library_debug_utilities_hierarchy>` of the Widget library.

.. warning:: Beware that enabling that feature may downgrade the performances (more time to compute a style and more Java heap used).

.. note:: Available since MWT 3.6.0.

.. _CascadingStylesheet.getStyleSources(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/stylesheet/cascading/CascadingStylesheet.html#getStyleSources-ej.mwt.style.Style-
.. _getDefaultStyle(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/stylesheet/cascading/CascadingStylesheet.html#getDefaultStyle--
.. _getSelectorStyle(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/stylesheet/cascading/CascadingStylesheet.html#getSelectorStyle-ej.mwt.stylesheet.selector.Selector-

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
