.. _section_ui_simulation:

==========
Simulation
==========


Principle
=========

The graphical user interface uses the Front Panel mock (see :ref:`section_frontpanel`) and some extensions (widgets) to simulate the user interactions. It is the equivalent of the three embedded modules (Display, Inputs and LED) of the MicroEJ Platform (see :ref:`section_microui`).

The Front Panel enhances the development environment by allowing User Interface  applications to be designed and tested on the computer rather than on the target device (which may not yet be built). The mock interacts with the user's computer in two ways: 

-  output: LEDs, graphical displays
-  input: buttons, joystick, touch, haptic sensors

.. note:: This chapter completes the notions described in :ref:`section_frontpanel` chapter. 

Module Dependencies
===================

The Front Panel project requires the dependency ``ej.tool.frontpanel#widget``. This library provides some widgets which have been designed to be compatible with the graphical engine: the MicroUI natives are implemented in these widgets and the widgets behavior matches with MicroUI implementation.

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

Widget Display
==============

By default, a display area is rectangular. Some displays can have
another appearance (for instance: circular). The front panel is able to
simulate that using a filter (see :ref:`section_frontpanel_widget`) . This filter defines the pixels inside and
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

Installation
============

Front Panel is an additional module for MicroUI library. When the
MicroUI module is installed, install this module in order to be able to
simulate UI drawings on the Simulator. See :ref:`fp_installation` to install the module.

The properties file can additional properties:
   
-  ``hardwareImageDecoders.list`` [optional, default value is ""
   (*empty*)]: Defines the available list of additional image decoders
   provided by the hardware. Use comma (',') to specify several decoders
   among this list: bmp, jpg, jpeg, gif, png. If empty or unspecified,
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
