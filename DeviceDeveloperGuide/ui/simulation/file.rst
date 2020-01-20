FP File
=======

File Contents
-------------

The mock engine takes an XML file (the fp file) as input. It describes
the panel using mock-widgets: They simulate the drivers, sensors and
actuators of the real device. The mock engine generates the graphical
representation of the real device, and is displayed in a window on the
user's development machine when the application is executed in the
simulator.

The following example file describes a typical board with one LCD, a
touch panel, three buttons, a joystick and four LEDs:

::

   <?xml version="1.0"?>
   <frontpanel 
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns="http://xml.is2t.com/ns/1.0/frontpanel" 
       xsi:schemaLocation="http://xml.is2t.com/ns/1.0/frontpanel .fp1.0.xsd">
       
       <description file="widgets.desc"/>
       
       <device name="MyBoard" skin="myboard.png">
           <body>
               <pixelatedDisplay id="0" x="162" y="114" width="320" height="240" initialColor="0x000000"/>
               <pointer id="0" x="162" y="114" width="320" height="240" touch="true" listenerClass="com.is2t.microej.fp.PointerListenerImpl"/>
       
               <led2states id="0" x="277" y="374" ledOff="led0_0.png" ledOn="led0_1.png" overlay="false"/>
               <led2states id="1" x="265" y="374" ledOff="led1_0.png" ledOn="led1_1.png" overlay="false"/>
               <led2states id="2" x="254" y="374" ledOff="led2_0.png" ledOn="led2_1.png" overlay="false"/>
               <led2states id="3" x="242" y="372" ledOff="led3_0.png" ledOn="led3_1.png" overlay="false"/>
               
               <repeatPush id="0" x="250" y="395" skin="Button1_0.png" pushedSkin="Button1_1.png" repeatPeriod="250" listenerClass="com.is2t.microej.fp.ButtonListener"/>
               <repeatPush id="1" x="322" y="395" skin="Button1_0.png" pushedSkin="Button1_1.png" repeatPeriod="250" listenerClass="com.is2t.microej.fp.ButtonListener"/>
               <repeatPush id="2" x="456" y="395" skin="Button1_0.png" pushedSkin="Button1_1.png" repeatPeriod="250" listenerClass="com.is2t.microej.fp.ButtonListener"/>
               <joystick id="0" x="368" y="375" skin="Joy0.png" mask="JoyMask.png" enterSkin="Joy1.png" upSkin="Joy_UP.png" downSkin="Joy_DOWN.png" leftSkin="Joy_LEFT.png" rightSkin="Joy_RIGHT.png" listenerClass="com.is2t.microej.fp.JoystickListenerImpl"/>
           </body>
       </device>
   </frontpanel>

The ``description`` element must appear exactly as shown. It refers to
the ``widgets.desc`` file mentioned above.

The ``device`` ``skin`` must refer to a ``png`` file in the
``resources`` folder. This image is used to render the background of the
front panel. The widgets are drawn on top of this background.

The ``body`` element contains the elements that define the widgets that
make up the front panel. The name of the widget element defines the type
of widget. The set of valid types is determined by the Front Panel
Designer. Every widget element defines an ``id``, which must be unique
for widgets of this type, and the ``x`` and ``y`` coordinates of the
position of the widget within the front panel (0,0 is top left). There
may be other attributes depending on the type of the widget.

The file and tags specifications are available in chapter
`??? <#front_panel_file>`__.

Working with fp Files
---------------------

To edit an fp file, open it using the Eclipse XML editor (right-click on
the fp file, select ``Open With > XML Editor``). This editor features
syntax highlighting and checking, and content-assist based on the schema
(XSD file) referenced in the fp file. This schema is a hidden file
within the project's definitions folder. An incremental builder checks
the contents of the fp file each time it is saved and highlights
problems in the Eclipse Problems view, and with markers on the fp file
itself.

A preview of the front panel can be obtained by opening the Front Panel
Preview
(``Window > Show View > Other... > MicroEJ > Front Panel Preview``).

The preview updates each time the fp file is saved.

A typical working layout is shown below.

.. figure:: simulation/images/working-layout.png
   :alt: Working Layout Example

   Working Layout Example

Within the XML editor, content-assist is obtained by pressing
ctrl+space.  The editor will list all the elements valid at the cursor
position, and insert a template for the selected element.

Skins and Filters
-----------------

The widgets which simulate the input devices use images (or "skins") to
show their current states (pressed and released). The user can change
the state of the widget by clicking anywhere on the skin: it is the
active area. This active area is, by default, rectangular.

These skins can be associated with an additional image called a
``filter`` or ``mask``. This image defines the widget's active area. It
is useful when the widget is not rectangular.

.. figure:: simulation/images/fp-widget-active-area.svg
   :alt: Active Area
   :width: 40.0%

   Active Area

The filter image must have the same size as the skin image. The active
area is delimited by the color 0xFF00FF (pink). Every pixel in the
filter image which is not this color is considered not part of the
active area.

Display Mask
------------

By default, a display area is rectangular. Some displays can have
another appearance (for instance: circular). The front panel is able to
simulate that using a mask. This mask defines the pixels inside and
outside the real display area. The mask image must have the same size
than display rectangular area. A display pixel at a given position will
be not rendered if the pixel at the same position in mask is fully
transparent.
