.. _front_panel_file:

Front Panel
===========

FP File
-------

XML Schema
~~~~~~~~~~

::

   <?xml version="1.0"?>
   <frontpanel 
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns="http://xml.is2t.com/ns/1.0/frontpanel" 
       xsi:schemaLocation="http://xml.is2t.com/ns/1.0/frontpanel .fp1.0.xsd">
               
           
       <description file="widgets.desc"/>
           
       <device name="example" skin="example-device.png">
           <body>
               <init class="[fully-qualified-class-name]"/> (optional)
               <[widget-type] id="0" x="54" y="117" [widget-attributes] />
               <[widget-type] id="1" x="266" y="115" [widget-attributes] />
               ...
           </body>
       </device>
   </frontpanel>

File Specification
~~~~~~~~~~~~~~~~~~

.. table:: FP File Specification

   +-----------------+-----------------+-----------------------------------+
   | Tag             | Attributes      | Description                       |
   +=================+=================+===================================+
   | ``fp``          |                 | The root element.                 |
   +-----------------+-----------------+-----------------------------------+
   | ``xmlns:xsi``   | Invariant       |                                   |
   |                 | tag [1]_        |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``xmlns``       | Invariant       |                                   |
   |                 | tag. [2]_       |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``xsi:s         | Invariant       |                                   |
   | chemaLocation`` | tag. [3]_       |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``description`` |                 | Defines the widgets descriptions  |
   |                 |                 | file (which is automatically      |
   |                 |                 | generated).                       |
   +-----------------+-----------------+-----------------------------------+
   | ``file``        | The widgets     |                                   |
   |                 | descriptions    |                                   |
   |                 | file. [4]_      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``device``      |                 | The device's root element.        |
   +-----------------+-----------------+-----------------------------------+
   | ``name``        | The device's    |                                   |
   |                 | logical name.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``skin``        | Refers to a PNG |                                   |
   |                 | file which      |                                   |
   |                 | defines the     |                                   |
   |                 | device          |                                   |
   |                 | background.     |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``body``        |                 | Defines the device's body. It     |
   |                 |                 | contains the elements that define |
   |                 |                 | the widgets that make up the      |
   |                 |                 | front panel.                      |
   +-----------------+-----------------+-----------------------------------+
   | ``init``        | ``class``       | Optional tag that defines a class |
   |                 |                 | to be loaded at startup. The      |
   |                 |                 | class can contain a static        |
   |                 |                 | initializer to initiate required  |
   |                 |                 | behavior. The ``body`` tag can    |
   |                 |                 | contain several ``init`` tags;    |
   |                 |                 | the classes will be loaded in the |
   |                 |                 | order of the ``init`` tags.       |
   +-----------------+-----------------+-----------------------------------+
   | ``pix           |                 | Defines the widget "display with  |
   | elatedDisplay`` |                 | pixels".                          |
   +-----------------+-----------------+-----------------------------------+
   | ``id``          | The unique      |                                   |
   |                 | widget ID.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``x``           | The widget      |                                   |
   |                 | x-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``y``           | The widget      |                                   |
   |                 | y-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``width``       | The display's   |                                   |
   |                 | width in        |                                   |
   |                 | pixels.         |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``height``      | The display's   |                                   |
   |                 | height in       |                                   |
   |                 | pixels.         |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``realWidth``   | The logical     |                                   |
   |                 | display's width |                                   |
   |                 | (the width      |                                   |
   |                 | returned to the |                                   |
   |                 | MicroUI         |                                   |
   |                 | application).   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``realHeight``  | The logical     |                                   |
   |                 | display's       |                                   |
   |                 | height (the     |                                   |
   |                 | height returned |                                   |
   |                 | to the MicroUI  |                                   |
   |                 | application).   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | `               | The default     |                                   |
   | `initialColor`` | display         |                                   |
   |                 | background      |                                   |
   |                 | color.          |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``mask``        | The image which |                                   |
   |                 | defines the     |                                   |
   |                 | visible display |                                   |
   |                 | area.           |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``e             | The extension   |                                   |
   | xtensionClass`` | class which     |                                   |
   |                 | defines the     |                                   |
   |                 | display's       |                                   |
   |                 | characteristics |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``push``        |                 | Defines the widget "basic push    |
   |                 |                 | button".                          |
   +-----------------+-----------------+-----------------------------------+
   | ``id``          | The unique      |                                   |
   |                 | widget ID.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``x``           | The widget      |                                   |
   |                 | x-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``y``           | The widget      |                                   |
   |                 | y-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``skin``        | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | button is       |                                   |
   |                 | released.       |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``pushedSkin``  | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | button is       |                                   |
   |                 | pressed.        |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``filter``      | The image which |                                   |
   |                 | defines the     |                                   |
   |                 | button's active |                                   |
   |                 | area.           |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``              | The class which |                                   |
   | listenerClass`` | implements the  |                                   |
   |                 | button's        |                                   |
   |                 | listener        |                                   |
   |                 | interface.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``repeatPush``  |                 | Defines the widget "repeat push   |
   |                 |                 | button".                          |
   +-----------------+-----------------+-----------------------------------+
   | ``id``          | The unique      |                                   |
   |                 | widget ID.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``x``           | The widget      |                                   |
   |                 | x-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``y``           | The widget      |                                   |
   |                 | y-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``skin``        | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | button is       |                                   |
   |                 | released.       |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``pushedSkin``  | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | button is       |                                   |
   |                 | pressed.        |                                   |
   +-----------------+-----------------+-----------------------------------+
   | `               | The time in     |                                   |
   | `repeatPeriod`` | milliseconds    |                                   |
   |                 | which defines   |                                   |
   |                 | the period of   |                                   |
   |                 | the repeat      |                                   |
   |                 | action.         |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``filter``      | The image which |                                   |
   |                 | defines the     |                                   |
   |                 | button's active |                                   |
   |                 | area.           |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``              | The class which |                                   |
   | listenerClass`` | implements the  |                                   |
   |                 | repeat button's |                                   |
   |                 | listener        |                                   |
   |                 | interface.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``joystick``    |                 | Defines the widget "joystick".    |
   +-----------------+-----------------+-----------------------------------+
   | ``id``          | The unique      |                                   |
   |                 | widget ID.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``x``           | The widget      |                                   |
   |                 | x-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``y``           | The widget      |                                   |
   |                 | y-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``skin``        | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | joystick is     |                                   |
   |                 | released.       |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``mask``        | The image which |                                   |
   |                 | defines the     |                                   |
   |                 | joystick's      |                                   |
   |                 | active area.    |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``upSkin``      | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | button UP is    |                                   |
   |                 | pressed.        |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``downSkin``    | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | button DOWN is  |                                   |
   |                 | pressed.        |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``leftSkin``    | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | button LEFT is  |                                   |
   |                 | pressed.        |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``rightSkin``   | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | button RIGHT is |                                   |
   |                 | pressed.        |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``enterSkin``   | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | button ENTER is |                                   |
   |                 | pressed (the    |                                   |
   |                 | central         |                                   |
   |                 | button).        |                                   |
   +-----------------+-----------------+-----------------------------------+
   | `               | true to disable |                                   |
   | `disableEnter`` | the ENTER       |                                   |
   |                 | button.         |                                   |
   +-----------------+-----------------+-----------------------------------+
   | `               | The time in     |                                   |
   | `repeatPeriod`` | milliseconds    |                                   |
   |                 | which defines   |                                   |
   |                 | the period of   |                                   |
   |                 | the repeat      |                                   |
   |                 | action.         |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``              | The class which |                                   |
   | listenerClass`` | implements the  |                                   |
   |                 | joystick's      |                                   |
   |                 | listener        |                                   |
   |                 | interface.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``pointer``     |                 | Defines the widget "pointer".     |
   +-----------------+-----------------+-----------------------------------+
   | ``id``          | The unique      |                                   |
   |                 | widget ID.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``x``           | The widget      |                                   |
   |                 | x-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``y``           | The widget      |                                   |
   |                 | y-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``width``       | The pointer     |                                   |
   |                 | area's width.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``height``      | The pointer     |                                   |
   |                 | area's height.  |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``touch``       | true means the  |                                   |
   |                 | pointer         |                                   |
   |                 | simulates a     |                                   |
   |                 | touch.          |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``              | The class which |                                   |
   | listenerClass`` | implements the  |                                   |
   |                 | pointer's       |                                   |
   |                 | listener        |                                   |
   |                 | interface.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``led2states``  |                 | Defines the widget "2-states LED  |
   |                 |                 | " (light on or light off).        |
   +-----------------+-----------------+-----------------------------------+
   | ``id``          | The unique      |                                   |
   |                 | widget ID.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``x``           | The widget      |                                   |
   |                 | x-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``y``           | The widget      |                                   |
   |                 | y-coordinate.   |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``ledOff``      | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | LED is off.     |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``ledOn``       | The image to    |                                   |
   |                 | show when the   |                                   |
   |                 | LED is on.      |                                   |
   +-----------------+-----------------+-----------------------------------+
   | ``overlay``     | true means the  |                                   |
   |                 | LED can be      |                                   |
   |                 | overlaid by     |                                   |
   |                 | another LED     |                                   |
   |                 | (transparency   |                                   |
   |                 | management).    |                                   |
   +-----------------+-----------------+-----------------------------------+

.. [1]
   Must be  "``http://www.w3.org/2001/XMLSchema-instance``"

.. [2]
   Must be  "``http://xml.is2t.com/ns/1.0/frontpanel``"

.. [3]
   Must be  "``http://xml.is2t.com/ns/1.0/frontpanel .fp1.0.xsd``"

.. [4]
   Must be "``widgets.desc``"
