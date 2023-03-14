.. _ui_port_sim:

==========
Simulation
==========

Principle
=========

The simulation involves creating or extending a Front Panel project to be UI Pack compatible.

First, if no Front Panel project exists, follow the steps described here: :ref:`section_frontpanel`.
Then, follow the next chapters to extend the Front Panel project with UI Pack notions.

Project Extension
=================

The Front Panel project must depend on the UI Pack.
Add the following dependency to the Front Panel ivy file:

.. code-block:: xml

   <dependency org="com.microej.pack.ui" name="ui-pack" rev="[UI Pack version]">
      <artifact name="frontpanel" type="jar"/>
   </dependency>

See :ref:`section_ui_simulation` for more information about the Front Panel project dependencies.

LEDs
====

When the VEE Port Configuration project LEDs module is checked, the Front Panel project should add a widget ``LED`` for each led.

1. With an image editor, create an image for the LED off and an image for the LED on. Both images must have the same size. 
2. Create a couple of images for each LED.
3. In the Front Panel description file, add this line for each LED:

.. code-block:: xml 

   <ej.fp.widget.LED label="0" x="170" y="753" ledOff="Led-0.png" ledOn="Led-GREEN.png" overlay="false"/>

The label is used by the application to turn on/off the LED. 
LED 0 has the label 0, and so on.

Buttons
=======

The widget ``Button`` should be used to simulate each hardware button (if any).

1. With an image editor, create an image for the button released and an image for the button pressed. Both images must have the same size. 
2. Create a couple of images for each button.
3. In the Front Panel description file, add this line for each button:

.. code-block:: xml

   <ej.fp.widget.Button label="0" x="316" y="769" skin="W-U-0.png" pushedSkin="W-U-1.png"/>

The label is used by the application to listen to the button. 
The button 0 has the label 0, and so on.

By default, the widget sends a MicroUI Button event to the Buttons Event Generator whose name is ``BUTTONS`` and whose identifier is the button's label.
To target another Buttons Event Generator, refer to the chapter :ref:`section_ui_simulation_input`.

To be more independent, the widget should send a MicroUI Command event, which is more generic, and the application code is better.
For instance, instead of reacting on Button event 0, the application will respond on Command ``Enter`` or ``Up``. 
The application does not care about the source of the Command event: maybe it is the button 0, 1, 10, or any other input device.

To map a MicroUI Command on the widget Button:

1. Update the widget description by adding a ``listenerClass``

.. code-block:: xml 

   <ej.fp.widget.Button label="0" x="316" y="769" skin="W-U-0.png" pushedSkin="W-U-1.png" listenerClass="com.is2t.microej.fp.Button2Command"/>

2. In the Front Panel project, create the class ``com.is2t.microej.fp.Button2Command``, for instance:

.. code-block:: java

   public class Button2Command implements ej.fp.widget.Button.ButtonListener {

      public int getCommand(int buttonId) {
         // same command as EmbJPF (see buttons_listener.c)
         switch (buttonId) {
         default:
         case 0:
            return EventCommand.ESC;
         case 1:
            return EventCommand.MENU;
         }
      }

      @Override
      public void press(Button widget) {
         EventCommand.sendEvent(getCommand(widget.getID()));
      }

      @Override
      public void release(Button widget) {
         // nothing to send
      }
   }

Touch Panel
===========

Contrary to the other input devices, no image is required: a touch panel is over the display.

1. Retrieve the display size in pixels.
2. In the Front Panel description file, add this line:

.. code-block:: xml 

   <ej.fp.widget.Pointer x="185" y="395" width="480" height="272" touch="true"/>

By default, the widget sends a MicroUI Pointer event to the Pointer Event Generator, whose name is ``TOUCH``.
To target another Pointer Event Generator, refer to the chapter :ref:`section_ui_simulation_input`.

Display
=======

The widget Display features a lot of options to simulate the hardware specificities.

1. Retrieve the display size in pixels.
2. In the Front Panel description file, add this line:

.. code-block:: xml 

   <ej.fp.widget.Display x="185" y="395" width="480" height="272"/>

For more information, refer to the java-doc of the widget Display and the chapter :ref:`section_ui_simulation_display`.

Build
=====

Once the Front Panel project is created or modified, it must be built again to be included in the VEE Port.
The Front Panel project is built simultaneously with the VEE Port; see :ref:`platform_build`.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
