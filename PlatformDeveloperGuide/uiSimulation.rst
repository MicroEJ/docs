.. _section_ui_simulation:

==========
Simulation
==========


Principle
=========

The graphical user interface uses the Front Panel mock (see :ref:`section_frontpanel`) and some extensions (widgets) to simulate the user interactions. It is the equivalent of the three embedded modules (Display, Input and LED) of the MicroEJ Platform (see :ref:`section_microui`).

The Front Panel enhances the development environment by allowing User Interface  applications to be designed and tested on the computer rather than on the target device (which may not yet be built). The mock interacts with the user's computer in two ways: 

-  output: LEDs, graphical displays
-  input: buttons, joystick, touch, haptic sensors

.. note:: This chapter completes the notions described in :ref:`section_frontpanel` chapter. 

Module Dependencies
===================

The Front Panel project is a regular MicroEJ Module project. Its module.ivy file should look like this example:

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


It depends at least on the Front Panel framework. This framework contains the Front Panel core classes. The dependencies can be reduced to:

::

   <dependencies>
      <dependency org="ej.tool.frontpanel" name="framework" rev="1.1.0"/>
   </dependencies>

To be compatible with Display module's Graphics Engine, the project must depend on an extension of Front Panel framework. This extension provides some interfaces and classes the Front Panel is using to target simulated display and input devices. The extension does not provide any widgets. It is the equivalent of the embedded Low Level API. It fetches by transitivity the Front Panel framework, so the Front Panel framework dependency does not need to be specified explicitly: 

::

   <dependencies>
      <dependency org="com.microej.pack.ui" name="ui-pack" rev="13.0.0">
         <artifact name="frontpanel" type="jar"/>
      </dependency>
   </dependencies>

.. warning:: This extension is built for each UI pack version. By consequence a Front Panel project is made for a platform built with the same UI pack. When the UI pack mismatch, some errors may occur during the Front Panel project export step, during the platform build and/or during the application runtime.

The Front Panel extension does not provide any widgets. Some compatible widgets are available in a third library. The life cycle of this library is different than the UI pack's one. New widgets can be added to simulate new kind of displays, input devices, etc. This extension fetches by transitivity the Front Panel extension, so this extension dependency does not need to be specified explicitly: 

::

   <dependencies>
      <dependency org="ej.tool.frontpanel" name="widget" rev="2.0.0"/>
   </dependencies>

.. warning:: The minimal version ``2.0.0`` is required to be compatible with UI pack 13.0.0 and higher. By default, when creating a new Front Panel project, the widget dependency version is ``1.0.0``.


Widget Display
==============

By default, a display area is rectangular. Some displays can have
another appearance (for instance: circular). The Front Panel is able to
simulate that using a filter (see :ref:`section_frontpanel_widget`) . This filter defines the pixels inside and
outside the real display area. The filter image must have the same size
than display rectangular area. A display pixel at a given position will
be not rendered if the pixel at the same position in mask is fully
transparent.


Inputs Extensions
=================

The input device widgets (button, joystick, touch, etc.) require a listener to know how to react on input events (press, release, move, etc.). The aim of this listener is to generate an event compatible with MicroUI `Event Generator <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/EventGenerator.html>`_. Thereby, a button press action can become a MicroUI `Buttons <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Buttons.html>`_ press event or a `Command <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Command.html>`_ event or anything else. 

A MicroUI `Event Generator <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/EventGenerator.html>`_ is known by its name. This name is fixed during the MicroUI static initialization (see :ref:`section_static_init`). To generate an event to a specific event generator, the widget has to use the event generator name as identifier. 

A Front Panel widget can:

* Force the behavior of an input action: the associated MicroUI `Event Generator <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/EventGenerator.html>`_ type is hardcoded (`Buttons <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Buttons.html>`_, `Pointer <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Pointer.html>`_, etc.), the event is hardcoded (for instance: widget button press action may be hardcoded on event generator `Buttons <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Buttons.html>`_ and on the event `pressed`). Only the event generator name (identifier) should be editable by the Front Panel extension project.
* Propose a default behavior of an input action: contrary to first point, the Front Panel extension project is able to change the default behavior. For instance a joystick can simulate a MicroUI `Pointer <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Pointer.html>`_.
* Do nothing: the widget requires the Front Panel extension project to give a listener. This listener will receive all widgets action (press, release, etc.) and will have to react on it. The action should be converted on a MicroUI `Event Generator <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/EventGenerator.html>`_ event or might be dropped.

This choice of behavior is widget dependant. Please refer to the widget documentation to have more information about the chosen behavior.

Heap Simulation
===============

Graphics Engine is using two dedicated heaps: for the images (see :ref:`section_image_loader_memory` ) and the external fonts (see :ref:`section_font_loader_memory`). Front Panel partly simulates the heaps usage.

* Images heap: Front Panel simulates the heap usage when the application is creating a `BufferedImage <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html#>`_, when it loads and decodes an image (PNG, BMP, etc.) which is not a raw resource and when it converts an image in MicroEJ format in another MicroEJ format. However it does not simulate the external image copy in heap (see :ref:`section_image_external_memory`).
* External fonts heap: Front Panel does not simulate this heap (see :ref:`section_font_loader_memory`). There is no rendering limitation when application is using a font which is located outside CPU addresses ranges.

.. _fp_ui_decoder:

Image Decoders
==============

Front Panel uses its own internal image decoders when the associated modules have been selected (see :ref:`internal image decoders<image_external_decoder>`). Front Panel can add some additional decoders like the C-side for the embedded platform (see :ref:`external image decoders<image_external_decoder>`). However, the exhaustive list of additional decoders is limited (Front Panel is using the Java AWT ``ImageIO`` API). To add an additional decoder, specify the property ``hardwareImageDecoders.list`` in Front Panel configuration properties file (see :ref:`fp_ui_installation`) with one or several property values:

.. table:: Front Panel Additional Image Decoders

   +-----------------------------------------------------+-----------------+
   | Type                                                | Property value  |
   +=====================================================+=================+
   | Graphics Interchange Format (GIF)                   | gif             |
   +-----------------------------------------------------+-----------------+
   | Joint Photographic Experts Group (JPEG)             | jpeg or jpg     |
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

-  MicroUI module (see :ref:`section_microui`),

-  Display module (see :ref:`section_display`): This module gives
   the characteristics of the graphical display that are useful for
   configuring the Front Panel.

.. _fp_ui_installation:

Installation
============

Front Panel is an additional module for MicroUI library. When the
MicroUI module is installed, install this module in order to be able to
simulate UI drawings on the Simulator. See :ref:`fp_installation` to install the module.

The properties file can additional properties:
   
-  ``hardwareImageDecoders.list`` [optional, default value is ""
   (*empty*)]: Defines the available list of additional image decoders
   provided by the hardware (see :ref:`fp_ui_decoder`). Use comma (',') to specify several decoders among this list: bmp, jpg, jpeg, gif, png. If empty or unspecified,
   no image decoder is added.

Use
===

Launch a MicroUI application on the Simulator to run the Front Panel.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
