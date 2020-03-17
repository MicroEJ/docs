.. _section_static_init:

=====================
Static Initialization
=====================


Principle
=========

MicroUI requires a configuration step (also called extension step) to
customize itself before MicroEJ Application startup (see
:ref:`section_architecture`). This configuration step uses an XML
file. In order to save both runtime execution time and flash memory, the
file is processed by the Static MicroUI Initializer tool, avoiding the
need to process the XML configuration file at runtime. The tool
generates appropriate initialized objects directly within the MicroUI
library, as well as Java and C constants files for sharing MicroUI event
generator IDs.

This XML file (also called the initialization file) defines:

-  The MicroUI event generators that will exist in the application in
   relation to low level drivers that provide data to these event
   generators (see :ref:`section_input`).

-  Whether the application has a display; and if so, it provides its
   logical name.

-  Which fonts will be provided to the application.


Functional Description
======================

The Static MicroUI Initializer tool takes as entry point the
initialization file which describes the MicroUI library extension. This
tool is automatically launched during the MicroUI module installation
(see :ref:`section_microui_installation` ).

The Static MicroUI Initializer tool is able to out until three files:

-  A Java library which extends MicroUI library. This library is
   automatically added to the MicroEJ Application classpath when MicroUI
   library is set as a classpath variable. This library is used at
   MicroUI startup to create all instances of I/O devices (``Display``,
   ``EventGenerator`` etc.) and contains the fonts described into the
   configuration file (these fonts are also called "system fonts").

   This MicroUI extension library is always generated and MicroUI
   library cannot run without this extension.

-  A C header file (\*.h) file. This H file contains some IDs which are
   used to make a link between an input device (buttons, touch) and its
   MicroUI event generator (see :ref:`section_input`).

   This file is useless if the BSP does not provide any input device and
   the Static MicroUI Initializer tool is able to not generate this
   file. Otherwise the MicroUI configuration file has to specify where
   put this file, typically in a BSP ``include`` directory.

-  A Java interface file. This Java file contains the same IDs which are
   used to make a link between an input device (buttons, touch) and its
   MicroUI event generator (see :ref:`section_input`).

   This Java file is used to configure the Simulator with the same
   characteristics as the BSP.

   This file is useless if the BSP does not provide any input device and
   the Static MicroUI Initializer tool is able to not generate this
   file. Otherwise the MicroUI configuration file has to specify where
   put this file, typically in the Simulator project (also called front
   panel project, see :ref:`section_simulation`).

.. figure:: images/static_init_process.*
   :alt: MicroUI Process
   :width: 70.0%
   :align: center

   MicroUI Process


Root Element
============

The initialization file root element is ``<microui>`` and contains
component-specific elements.

::

   <microui>
       [ component specific elements ]
   </microui>


Display Element
===============

The display component augments the initialization file with:

-  The configuration of the display.

-  Fonts that are implicitly embedded within the application (also
   called system fonts). Applications can also embed their own fonts.

::

   <display name="DISPLAY"/>

   <fonts>
       <font file="resources\fonts\myfont.ejf">
           <range name="LATIN" sections="0-2"/>
           <customrange start="0x21" end="0x3f"/>
       </font>
       <font file="C:\data\myfont.ejf"/>
   </fonts>


Event Generators Element
========================

The event generators component augments the initialization file with:

-  the configuration of the predefined MicroUI ``Event Generator``:
   ``Command``, ``Buttons``, ``States``, ``Pointer``, ``Touch``

-  the configuration of the generic MicroUI ``Event Generator``

::

   <eventgenerators>
       <!-- Generic Event Generators -->
       <eventgenerator name="GENERIC" class="foo.bar.Zork">
           <property name="PROP1" value="3"/>
           <property name="PROP2" value="aaa"/>
       </eventgenerator>

       <!-- Predefined Event Generators -->
       <command name="COMMANDS"/>
       <buttons name="BUTTONS" extended="3"/>
       <buttons name="JOYSTICK" extended="5"/>
       <pointer name="POINTER" width="1200" height="1200"/>
       <touch name="TOUCH" display="DISPLAY"/>
       <states name="STATES" numbers="NUMBERS" values="VALUES"/>

   </eventgenerators>

   <array name="NUMBERS">
       <elem value="3"/>
       <elem value="2"/>
       <elem value="5"/>
   </array>

   <array name="VALUES">
       <elem value="2"/>
       <elem value="0"/>
       <elem value="1"/>
   </array>


Example
=======

This common MicroUI initialization file initializes MicroUI with:

-  a display

-  a ``Command`` event generator

-  a ``Buttons`` event generator which targets *n* buttons (3 first
   buttons having extended features)

-  a ``Buttons`` event generator which targets the buttons of a joystick

-  a ``Pointer`` event generator which targets a touch panel

-  a ``DisplayFont`` whose path is relative to this file

::

   <microui>

       <display name="DISPLAY"/>
       
       <eventgenerators>
           <command name="COMMANDS"/>
           <buttons name="BUTTONS" extended="3"/>
           <buttons name="JOYSTICK" extended="5"/>
           <touch name="TOUCH" display="DISPLAY"/>
       </eventgenerators>
       
       <fonts>
           <font file="resources\fonts\myfont.ejf"/>
       </fonts>

   </microui>


Dependencies
============

No dependency.


Installation
============

The Static Initialization tool is part of the MicroUI module (see
:ref:`section_microui`). Install the MicroUI module to install the
Static Initialization tool and fill all properties in MicroUI module
configuration file (which must specify the name of the initialization
file).


Use
===

The Static MicroUI Initializer tool is automatically launched during the
MicroUI module installation.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
