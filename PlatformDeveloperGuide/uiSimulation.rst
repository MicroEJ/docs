.. _section_simulation:

==========
Simulation
==========


Principle
=========

A major strength of the MicroEJ environment is that it allows
applications to be developed and tested in a Simulator rather than on
the target device, which might not yet be built. To make this possible
for devices that have a display or controls operated by the user (such
as a touch screen or buttons), the Simulator must connect to a "mock" of
the control panel (the "Front Panel") of the device. The Front Panel generates a graphical representation of the
device, and is displayed in a window on the user's
development machine when the application is executed in the Simulator.
The Front Panel is the equivalent of the three embedded modules (Display,
Inputs and LED) of the MicroEJ Platform (see
:ref:`section_microui`).

The Front Panel enhances the development environment by allowing
User Interface  applications to be designed and tested on the computer
rather than on the target device (which may not yet be built). The mock
interacts with the user's computer in two ways:

-  output: LEDs, graphical displays

-  input: buttons, joystick, touch, haptic sensors


Functional Description
======================

1. Creates a new Front Panel project.

2. Creates an image of the required front panel. This could be a
   photograph or a drawing.

3. Defines the contents and layout of the front panel by editing an XML
   file (called an fp file). Full details about the structure and
   contents of fp files can be found in chapter
   :ref:`front_panel_file`.

4. Creates images to animate the operation of the controls (for example
   button down image).

5. Creates *Listeners* that generate the same MicroUI input events as
   the hardware.

6. Previews the front panel to check the layout of controls and the
   events they create, etc.

7. Exports the Front Panel project into a MicroEJ Platform project.


The Front Panel Project
=======================

Creating a Front Panel Project
------------------------------

A Front Panel project is created using the New Front Panel Project
wizard. Select:

``New > Project... > MicroEJ > Front Panel Project``

The wizard will appear:

.. figure:: images/newfp.png
   :alt: New Front Panel Project Wizard
   :align: center
   :width: 700px
   :height: 500px

   New Front Panel Project Wizard

Enter the name for the new project.

Project Contents
----------------

.. figure:: images/project-content.png
   :alt: Project Contents
   :align: center

   Project Contents

A Front Panel project has the following structure and contents:

* The ``src/main/java`` folder is provided for the definition of ``Listeners`` (and ``DisplayExtensions``). It is initially empty. The creation of these classes will be explained later.
* The ``src/main/resources`` folder holds the file or files that define the contents and layout of the front panel, with a ``.fp`` extension (the fp file or files), plus images used to create the front panel. A newly created project will have a single fp file with the same name as the project, as shown above. The contents of fp files are detailed later in this  document.
* The ``JRE System Library`` is referenced, because a Front Panel  project needs to support the writing of Java for the ``Listeners`` (and ``DisplayExtensions``).
* The ``Modules Dependencies`` contains the libraries for the front panel simulation, the widgets it supports and the types needed to implement ``Listeners`` (and ``DisplayExtensions``).
* The ``lib`` contains a local copy of ``Modules Dependencies``. 

Module Dependencies
===================

The Front Panel project is a standard IVY project. Its ``module.ivy`` file should look like this example:

::

   <ivy-module version="2.0" xmlns:ea="http://www.easyant.org" xmlns:ej="https://developer.microej.com" ej:version="2.0.0"> 
   <info organisation="com.mycompany" module="examplePanel" status="integration" revision="1.0.0"/>      

      <configurations defaultconfmapping="default->default;provided->provided">
         <conf name="default" visibility="public" description="Runtime dependencies to other artifacts"/>
         <conf name="provided" visibility="public" description="Compile-time dependencies to APIs provided by the platform"/>
      </configurations>

      <dependencies>
         <dependency org="ej.tool.frontpanel" name="widget" rev="1.0.0"/>
      </dependencies>
   </ivy-module>


It depends at least on the Front Panel framework. This framework contains the front panel core classes. The dependencies can be reduced to:

::

   <dependencies>
      <dependency org="ej.tool.frontpanel" name="framework" rev="1.0.0"/>
   </dependencies>

FP File
=======

File Contents
-------------

The Front Panel engine takes an XML file (the fp file) as input. It describes
the panel using widgets: They simulate the drivers, sensors and
actuators of the real device. The front panel engine generates the graphical
representation of the real device, and is displayed in a window on the
user's development machine when the application is executed in the
Simulator.

The following example file describes a typical board with one LCD, a
touch panel, three buttons, a joystick and four LEDs:

::

   <?xml version="1.0"?>
   <frontpanel 
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xmlns="https://developer.microej.com" 
      xsi:schemaLocation="https://developer.microej.com .widget.xsd">
      
      <device name="MyBoard" skin="myboard.png">
         <ej.fp.widget.Display x="22" y="51" width="480" height="272"/>
         <ej.fp.widget.Pointer x="22" y="51" width="480" height="272" touch="true"/>
         
         <ej.fp.widget.LED label="0" x="30" y="352" ledOff="led0_0.png" ledOn="led0_1.png"/>		
         <ej.fp.widget.LED label="1" x="50" y="352" ledOff="led1_0.png" ledOn="led1_1.png"/>		
         <ej.fp.widget.LED label="2" x="70" y="352" ledOff="led2_0.png" ledOn="led2_1.png"/>		
         <ej.fp.widget.LED label="3" x="90" y="352" ledOff="led3_0.png" ledOn="led3_1.png"/>
         
         <ej.fp.widget.RepeatButton label="0" x="125" y="345" skin="button0.png" pushedSkin="button1.png"/>
         <ej.fp.widget.RepeatButton label="1" x="169" y="345" skin="button0.png" pushedSkin="button1.png"/>
         <ej.fp.widget.RepeatButton label="2" x="213" y="345" skin="button0.png" pushedSkin="button1.png"/>
         
         <ej.fp.widget.Joystick x="300" y="341" upSkin="joystick-UP.png" downSkin="joystick-DOWN.png" rightSkin="joystick-RIGHT.png" leftSkin="joystick-LEFT.png" skin="joystick-0.png"/>		
      </device>
   </frontpanel>

The ``device`` ``skin`` must refer to a ``png`` file in the
``src/main/resources`` folder. This image is used to render the background of the
front panel. The widgets are drawn on top of this background.

The ``device`` contains the elements that define the widgets that
make up the front panel. The name of the widget element defines the type
of widget. The set of valid types is determined by the Front Panel
Designer. Every widget element defines a ``label``, which must be unique
for widgets of this type (optional or not), and the ``x`` and ``y`` coordinates of the
position of the widget within the front panel (0,0 is top left). There
may be other attributes depending on the type of the widget.

The file and tags specifications are available in chapter
:ref:`front_panel_file`.

.. note:: The ``fp`` file grammar has changed since the UI pack version 12.x (Front Panel core has been moved in MicroEJ Architecture 7.11). A quick migration guide is available here: open platform configuration file ``.platform``, go to ``Content`` tab, click on module ``Front Panel``. The migration guide is available in ``Details`` box.

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

.. figure:: images/working-layout.png
   :alt: Working Layout Example
   :align: center

   Working Layout Example

Within the XML editor, content-assist is obtained by pressing
ctrl+space.  The editor will list all the elements valid at the cursor
position, and insert a template for the selected element.

Several fp Files
----------------

A front panel project can contain several ``fp`` files. All ``fp`` files are compiled when exporting the front panel project in a platform (or during platform build). It is useful to have two or more representation of a board (size, devices layout, display size etc.). By default the MicroEJ Application chooses a random ``fp`` file. To force to use a specific fp, add the option ``-Dfrontpanel.file=xxx.fp`` in the MicroEJ Application launcher (JRE tab) where ``xxx`` is the ``fp`` file name.

Widget
======

Description
-----------

A widget is a subclass of front panel framework class ``ej.fp.Widget``. The library ``ej.tool.frontpanel#widget`` provides a set of widgets which are graphical engine compatible. To create a new widget (or a subclass of an existing widget), have a look on available widgets in this library.

A widget is recognized by the ``fp`` file as soon as its class contains a ``@WidgetDescription`` annotation. The annotation contains several ``@WidgetAttribute``. An attribute has got a name and tells if it is an optional attribute of widget (by default an attribute is mandatory).

This is the description of the widget ``LED``:

::

   @WidgetDescription(attributes = { @WidgetAttribute(name = "label"), @WidgetAttribute(name = "x"),
         @WidgetAttribute(name = "y"), @WidgetAttribute(name = "ledOff"), @WidgetAttribute(name = "ledOn"),
         @WidgetAttribute(name = "overlay", isOptional = true) })

As soon as a widget is created (with its description) in front panel project, the ``fp`` file can use it. Close and reopen ``fp`` file after creating a new widget. In ``device`` group, press ``CTRL + SPACE`` to visualize the available widgets: the new widget can be added.

::

   <ej.fp.widget.LED label="0" x="170" y="753" ledOff="Led-0.png" ledOn="Led-GREEN.png" overlay="false"/>

Each attribute requires the ``set`` methods in the widget source code. For instance, the widget LED (or its hierarchy) contains the following methods for sure:

* ``setLabel(String)``,
* ``setX(int)``,
* ``setY(int)``,
* ``setLedOff(Image)``,
* ``setLedOn(Image)``,
* ``setOverlay(boolean)``.

The ``set`` method parameter's type fixes the expected value in ``fp`` file. If the attribute cannot match the expected type, an error is throw when editing ``fp`` file. Widget master class already provides a set of standard attributes:

* ``setFilter(Image)``: apply a filtering image which allows to crop input area (:ref:`section_filter_input`)  or area to render (:ref:`section_filter_display`).
* ``setWidth(int)`` and ``setHeight(int)``: limits the widget size.
* ``setLabel(String)``: specifies an identifier to the widget.
* ``setOverlay(boolean)``: draws widget skin with transparency or not.
* ``setSkin(Image)``: specifies the widget skin.
* ``setX(int)`` and ``setY(int)``: specifies widget position.

Notes:

* Widget class does not specify if an attribute is optional or not. It it the responsability to the subclass. 
* The label is often used as identifier. It also allows to retrieve a widget calling ``Device.getDevice().getWidget(Class<T>, String)``. Some widgets are using this identifier as an integer label (for example widget ``LED``). It is the responsability to the widget to fix the signification of the label.
* The widget size is often fixed by the its skin (which is an image). See ``Widget.finalizeConfiguration()``: it sets the widget size according the skin if the skin has been set; even if methods ``setWidth()`` and ``setHeight()`` have been called before.

Runtime
-------

The front panel engine parsing the ``fp`` file at application runtime. The widget methods are called in two times. First, engine creates widget by widget:

#. widget's constructor: Widget should initialize its own fields which not depend on widget attributes (not valorized yet).
#. ``setXXX()``: Widget should check if given attribute value matches the expected behavior (the type has been already checked by caller). For instance if a width is not negative. On error, implementation can throw an ``IllegalArgumentException``. These checks must not depend on other attributes because they may have not already valorized.
#. ``finalizeConfiguration()``: Widget should check the coherence between all attributes: they are now valorized.

During these three calls, all widgets are not created yet. And so, by definition, the main device (which is a widget) not more. By consequence, the implementation must not try to get the instance of device by calling ``Device.getDevice()``. Furthermore, a widget cannot try to get another widget by calling ``Device.getDevice().getWidget(s)``. If a widget depend on another widget for any reason, the last checks can be performed in ``start()`` method. This method is called when all widgets and main device are created. Call to ``Device.getDevice()`` is allowed.

The method ``showYourself()`` is only useful when visualizing the ``fp`` file during its editing (use Eclipse view ``Front Panel Preview``). This method is called when clicking on button ``Outputs``.

Empty Widget
------------

By definition a widget may not contain an attribute. This kind of widget is useful to perform something at front panel startup, for instance to start a thread to pick up data somewhere. 

The widget description is ``@WidgetDescription(attributes = { })``. In ``start()`` method, a custom behavior can be performed. In ``fp`` file, the widget declaration is ``<com.mycompany.Init/>`` (where ``Init`` is an example of widget name).


.. _section_filter_input:

Input Device Filters
--------------------

The widgets which simulate the input devices use images (or "skins") to
show their current states (pressed and released). The user can change
the state of the widget by clicking anywhere on the skin: it is the
active area. This active area is, by default, rectangular.

These skins can be associated with an additional image called a
``filter``. This image defines the widget's active area. It
is useful when the widget is not rectangular.

.. figure:: images/fp-widget-active-area.*
   :alt: Active Area
   :width: 25.0%
   :align: center

   Active Area

The filter image must have the same size as the skin image. The active
area is delimited by the fully opaque pixels. Every pixel in the
filter image which is not fully opaque is considered not part of the
active area.

.. _section_filter_display:

Display Filter
--------------

By default, a display area is rectangular. Some displays can have
another appearance (for instance: circular). The front panel is able to
simulate that using a filter. This filter defines the pixels inside and
outside the real display area. The filter image must have the same size
than display rectangular area. A display pixel at a given position will
be not rendered if the pixel at the same position in mask is fully
transparent.


Inputs Extensions
=================

The input device widgets (button, joystick, touch etc.) require a listener to know how to react on input events (press, release, move etc.). The aim of this listener is to generate an event compatible with MicroUI ``EventGenerator``. Thereby, a button press action can become a MicroUI ``Buttons`` press event or a ``Command`` event or anything else. 

A MicroUI ``EventGenerator`` is known by its name. This name is fixed during the MicroUI static initialization (see :ref:`section_static_init`). To generate an event to a specific event generator, the widget has to use the event generator name as identifier. 

A front panel widget can:

* Force the behavior of an input action: the associated MicroUI ``EventGenerator`` type is hardcoded (``Buttons``, ``Pointer`` etc.), the event is hardcoded (for instance: widget button press action may be hardcoded on event generator ``Buttons`` and on the event `pressed`). Only the event generator name (identifier) should be editable by the front panel extension project.
* Propose a default behavior of an input action: contrary to first point, the front panel extension project is able to change the default behavior. For instance a joystick can simulate a MicroUI ``Pointer``.
* Do nothing: the widget requires the front panel extension project to give a listener. This listener will receive all widgets action (press, release, etc.) and will have to react on it. The action should be converted on a MicroUI ``EventGenerator`` event or might be dropped.

This choice of behavior is widget dependant. Please refer to the widget documentation to have more information about the chosen behavior.

Heap Simulation
===============

Graphical engine is using two dedicated heaps: for the images and the external fonts. Front panel simulates partly simulates the heaps usage.

* Images heap: Front Panel simulates the heap usage when the application is creating a ``BufferedImage``, when it loads and decodes an image (PNG, BMP etc.), when it converts an image in MicroEJ format in another MicroEJ format. However it does not simulate the external image copy in heap.
* External fonts heap: Front Panel does not simulate this heap. 

Image Decoders
==============

Front Panel uses its own internal image decoders when the internal image
decoders related modules have been selected (see
:ref:`image_internal_decoder`).

Front Panel can add some additional decoders like the C-side for the
embedded platform (see :ref:`image_external_decoder`). However, the
exhaustive list of additional decoders is limited (Front Panel is using
the Java AWT ``ImageIO`` API). To add an additional decoder, specify the
property ``hardwareImageDecoders.list`` in front panel configuration
properties file (see :ref:`fp_installation`) with one or several
property values:

.. table:: Front Panel Additional Image Decoders

   +-----------------------------------------------------+-----------------+
   | Type                                                | Property value  |
   +=====================================================+=================+
   | Graphics Interchange Format (GIF)                   | gif             |
   +-----------------------------------------------------+-----------------+
   | Joint Photographic Experts Group (JPEG)             | jpeg \| jpg     |
   +-----------------------------------------------------+-----------------+
   | Portable Network Graphics (PNG)                     | png             |
   +-----------------------------------------------------+-----------------+
   | Windows bitmap (BMP)                                | bmp             |
   +-----------------------------------------------------+-----------------+

The decoders list is comma (*,*) separated. Example:

::

   hardwareImageDecoders.list=jpg,bmp


Dependencies
============

-  MicroUI module (see :ref:`section_microui`).

-  Display module (see :ref:`section_display`): This module gives
   the characteristics of the graphical display that are useful for
   configuring the Front Panel.


.. _fp_installation:

Installation
============

Front Panel is an additional module for MicroUI library. When the
MicroUI module is installed, install this module in order to be able to
simulate UI drawings on the Simulator.

In the platform configuration file, check :guilabel:`Front Panel` to
install the Front Panel module. When checked, the properties file
``frontpanel`` > ``frontpanel.properties`` is required during platform creation to
configure the module. This configuration step is used to identify and
configure the front panel.

The properties file must / can contain the following properties:

-  ``project.name`` [mandatory]: Defines the name of the front panel
   project (same workspace as the platform configuration project). If
   the project name does not exist, a new project will be created.

-  ``fpFile.name`` [optional, default value is "" (*empty*)]: Defines
   the front panel file (\*.fp) the application has to use by default when several ``fp`` files are available in project.
   
-  ``hardwareImageDecoders.list`` [optional, default value is ""
   (*empty*)]: Defines the available list of additional image decoders
   provided by the hardware. Use comma (',') to specify several decoders
   among this list: bmp, jpg, jpeg, gif, png. If empty or unspecified,
   no image decoder is added.

To test a front panel project without rebuilding the platform or without exporting manually the project, add the property ``-Dej.fp.project=[full project path]`` in the MicroEJ Application launcher (JRE tab). The application will use the front panel project even if the platform the application already contain a built-in front panel. 

.. note:: This feature works only if the platform already contains a built-in front panel; more specifically the scripts which allows to start the front panel.

.. warning:: This feature is useful to test locally some changes in Front Panel project. The platform does not contain the changes until a new platform build.


Use
===

Launch a MicroUI application on the Simulator to run the Front Panel.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
