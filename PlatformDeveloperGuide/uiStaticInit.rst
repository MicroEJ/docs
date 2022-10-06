.. _section_static_init:

=====================
Static Initialization
=====================

Principle
=========

The MicroUI implementation for MicroEJ requires a configuration step (also called extension step) to customize itself before application startup (see :ref:`section_architecture`). This configuration step uses an XML file. In order to save both runtime execution time and flash memory, the file is processed by the Static MicroUI Initializer tool, avoiding the need to process the XML configuration file at runtime. The tool generates appropriate initialized objects directly within the MicroUI library, as well as Java and C constants files for sharing MicroUI event generator IDs.

This XML file (also called the initialization file) defines:

-  The MicroUI event generators that will exist in the application in relation to Low Level drivers that provide data to these event generators (see :ref:`section_input`).
-  Whether the application has a display; and if so, it provides its logical name.
-  Which fonts will be provided to the application.

The next chapters describe succinctly the XML file. For more information about grammar, please consult appendix :ref:`muiStaticInit`.

Functional Description
======================

The Static MicroUI Initializer tool takes as entry point the initialization file which describes the MicroUI library extension. This tool is automatically launched during the MicroEJ Platform build (see :ref:`section_microui_installation` ). 

The Static MicroUI Initializer tool is able to generate two files:

-  A Java library which extends MicroUI library. This library is automatically added to the :ref:`MicroEJ Application classpath<chapter.microej.classpath>` when MicroUI API library is fetched. This library is used at MicroUI startup to create all instances of I/O devices (`Display`_, `EventGenerator`_, etc.) and contains the fonts described into the configuration file (these fonts are also called "system fonts").

.. warning:: This MicroUI extension library is always generated and MicroUI library cannot run without this extension.

-  A C header file (``*.h``). This header file contains some IDs which are
   used to make a link between an input device (buttons, touch) and its
   MicroUI event generator (see :ref:`section_input`).

.. note:: The Front Panel project does not need a configuration file (like C header file for embedded platform).

.. figure:: images/static_init_process.*
   :alt: Static MicroUI Initializer Process
   :width: 750px
   :align: center

   Static MicroUI Initializer Process

.. _Display: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.htmls
.. _EventGenerator: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/EventGenerator.html

XML File
========

The XML file must be created in platform configuration project, in folder ``microui`` and called ``microui.xml``.

.. figure:: images/static_xml.*
   :alt: Static MicroUI Initializer XML File

   Static MicroUI Initializer XML File

The XML file grammar is detailed :ref:`here<muiStaticInit>`. The following list gives a short description of each element:

* Root element: The initialization file root element is ``<microui>`` and contains component-specific elements.

    ::

        <microui>
            [ component specific elements ]
        </microui>


* Display element: The ``display`` element augments the initialization file with the configuration of the display. The following snippet is an example of ``display`` element:

    ::

        <display name="DISPLAY"/>

* Fonts element: The ``fonts`` element augments the initialization file with the fonts that are implicitly embedded within the application (also called system fonts). Applications can also embed their own fonts. 
   
    .. note:: The system fonts are optional, in which case application has to provide some fonts to be able to draw characters.

    The following snippet is an example of ``fonts`` element:

    ::

        <fonts>
            <font file="resources\fonts\myfont.ejf">
                <range name="LATIN" sections="0-2"/>
                <customrange start="0x21" end="0x3f"/>
            </font>
            <font file="C:\data\myfont.ejf"/>
        </fonts>


* Event generators element: The ``eventgenerators`` element augments the initialization file with:

    -  the configuration of the predefined MicroUI `EventGenerator`_: `Command`_, `Buttons`_, `States`_, `Pointer`_ and Touch.

    -  the configuration of the generic MicroUI `EventGenerator`_.

    The following snippet is an example of ``eventgenerators`` element:

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


.. _Command: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Command.html
.. _Buttons: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Buttons.html
.. _States: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/States.html
.. _Pointer: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/generator/Pointer.html

XML File Example
================

This common MicroUI initialization file initializes MicroUI with:

-  a `Display`_,

-  a `Command`_ event generator,

-  a `Buttons`_ event generator which targets *n* buttons (3 first buttons having extended features),

-  a `Buttons`_ event generator which targets the buttons of a joystick,

-  a `Pointer`_ event generator which targets a touch panel,

-  a `Font`_ whose path is relative to this file.

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

.. _Font: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html

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
MicroEJ Platform build.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
