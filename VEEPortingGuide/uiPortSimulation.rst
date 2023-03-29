.. _ui_port_sim:

==========
Simulation
==========

Principle
=========

The simulation part of the UI port requires the creation (or extension) of a Front Panel project which is compatible with the UI Pack.

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

The label must have an integer value from 0 to ``NUMBER_OF_LEDS - 1``.
The ``ej.microui.led.Leds`` class uses this value as the LED identifier in ``setLedOff(int ledId)``, ``setLedOn(int ledId)``, and other methods of the class.

Buttons
=======

The widget ``Button`` can simulate any hardware button.

1. With an image editor, create an image for the button released and an image for the button pressed. Both images must have the same size. 
2. Create a couple of images for each button.
3. In the Front Panel description file, add this line for each button:

.. code-block:: xml

   <ej.fp.widget.Button label="0" x="316" y="769" skin="W-U-0.png" pushedSkin="W-U-1.png"/>

The label must have an integer value from 0 to ``NUMBER_OF_BUTTONS - 1``.
The label is used by the application to listen to the button. 

By default, the widget sends a MicroUI Button event to the Buttons Event Generator whose name is ``BUTTONS`` and whose identifier is the button's label.
To target another Buttons Event Generator, refer to the chapter :ref:`section_ui_simulation_input`.

Widget Button Code
------------------

.. code-block:: java

      public static class ButtonListenerToButtonEvents implements ButtonListener {

      @Override
      public void press(Button widget) {
         EventButton.sendPressedEvent(getMicroUIGeneratorTag(), widget.getID());
      }

      @Override
      public void release(Button widget) {
         EventButton.sendReleasedEvent(getMicroUIGeneratorTag(), widget.getID());
      }

      /**
       * Gets the MicroUI Buttons events generator tag. This generator has to match the generator set during the
       * MicroEJ platform build in <code>microui/microui.xml</code>
       *
       * @return a MicroUI Buttons events generator tag
       */
      protected String getMicroUIGeneratorTag() {
         return EventButton.COMMON_MICROUI_GENERATOR_TAG;
      }

Application Code
----------------

To listen to the button, two ways are possible:

   - By default, the current ``Displayable`` receives all events. The subclass has to implement the method ``boolean handleEvent(int event);``.
   - A class must extend the interface ``EventHandler``, and this class must be set as the handler of the event generators Buttons: 

.. code-block:: java

   Buttons[] buttonsHandlers = (Buttons[]) EventGenerator.get(Buttons.class);
   for (EventGenerator buttonsHandler : generators) {
      buttonsHandler.setEventHandler(this);
   }

Here is an example of a handler:

.. code-block:: java

   @Override
   public boolean handleEvent(int event) {

      // get the event's data
      int data = Event.getData(event);

      String state = null;

      // print its state(s)
      if (Buttons.isPressed(data)) {
         state = "pressed ";
      }
      if (Buttons.isReleased(data)) {
         state = "released ";
      }
      if (Buttons.isRepeated(data)) {
         state = "repeated ";
      }
      if (Buttons.isLong(data)) {
         state = "long ";
      }
      if (Buttons.isClicked(data)) {
         state = "clicked ";
      }
      if (Buttons.isDoubleClicked(data)) {
         state = "double-clicked ";
      }

      if (state != null) {
         System.out.print("button\t\t");

         // get the button's id
         int id = Buttons.getButtonId(data);
         System.out.print(id+" ");
         System.out.println(state);
      }

      return true;
   }

Button to Command Event
-----------------------

A recommended approach is to favor Command events over Buttons events. 
MicroUI Command events are more generic because not they are not tied to a hardware component like a physical button. 
Command events make the application code more flexible to hardware changes.
For instance, instead of reacting to Button event 0, the application will respond to Command event ``Enter`` or ``Up``. 
The application does not care about the source of the Command event: it may be the button 0, 1, 10, or any other input device.

To map a MicroUI Command on the widget Button:

1. Update the widget description by adding a ``listenerClass``.

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

The application code becomes:

.. code-block:: java

   // [...]

      Command[] commandHandlers = (Command[]) EventGenerator.get(Command.class);
      for (EventGenerator commandHandler : generators) {
         commandHandler.setEventHandler(this);
      }

   // [...]

   @Override
   public boolean handleEvent(int event) {

      // get the event's data
      int data = Event.getData(event);

      switch (data) {
      case Command.ESC:
         System.out.println("ESC");
         break;
      case Command.BACK:
         System.out.println("BACK");
         break;

      // [...]
   }

Touch Panel
===========

Contrary to the other input devices, no image is required because a touch panel covers the display area.

1. Retrieve the display size in pixels.
2. In the Front Panel description file, add this line:

.. code-block:: xml 

   <ej.fp.widget.Pointer x="185" y="395" width="480" height="272" touch="true"/>

By default, the widget sends a MicroUI Pointer event to the Pointer Event Generator, whose name is ``TOUCH`` (a touch panel is considered a Pointer with only dragged events).
To target another Pointer Event Generator, refer to the chapter :ref:`section_ui_simulation_input`.

A snippet of application code that handles Pointer events:


.. code-block:: java

   // [...]

      Pointer[] pointerHandlers = (Pointer[]) EventGenerator.get(Pointer.class);
      for (EventGenerator pointerHandler : generators) {
         pointerHandler.setEventHandler(this);
      }

   // [...]

   @Override
   public boolean handleEvent(int event) {
      Pointer pointer = (Pointer) Event.getGenerator(event);
      int x = pointer.getX();
      int y = pointer.getY();
      System.out.println("(" + x + "," + y + ")");
   }

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

Once the Front Panel project is created or modified, the VEE Port must be built again (the front panel is built simultaneously with the VEE Port; see :ref:`platform_build`).

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
