.. _section_microui:

=======
MicroUI
=======


Principle
=========

The MicroUI module defines a low-level UI framework for embedded
devices. This module allows the creation of basic
Human-Machine-Interfaces (HMI), with output on a pixelated screen. For
more information, please consult the MUI Specification [MUI].


.. _section_architecture:

Architecture
============

MicroUI is not a standalone library. It requires a configuration step
and several extensions to drive I/O devices (display, inputs, LEDs,
etc.).

.. figure:: images/microui-fragment-dependencies.*
   :alt: MicroUI Elements
   :width: 70.0%
   :align: center

   MicroUI Elements

At MicroEJ Application startup all MicroUI objects relative to the I/O
devices are created and accessible. The following MicroUI methods allow
you to access these internal objects:

-  ``Display.getDefaultDisplay()``: returns the instance of the default
   display which drives the main LCD screen.

-  ``Leds.getNumberOfLeds()``: returns the numbers of available LEDs.

First, MicroUI requires a configuration step in order to create these
internal objects before the call to the ``main()`` method. The chapter
:ref:`section_static_init` explains how to perform the configuration
step.

.. note::

   This configuration step is the same for both embedded and simulation
   platforms.

The embedded platform requires some additional C libraries to drive the
I/O devices. Each C library is dedicated to a specific kind of I/O
device. A specific chapter is available to explain each kind of I/O
device.

.. table:: MicroUI C libraries

   +-----------------------------------------+-----------------+----------------------------+
   | I/O devices                             | Extension Name  | Chapter                    |
   +=========================================+=================+============================+
   | Graphical / pixelated display (LCD      | Display         | :ref:`section_display`     |
   | screen)                                 |                 |                            |
   +-----------------------------------------+-----------------+----------------------------+
   | Inputs (buttons, joystick, touch,       | Input           | :ref:`section_input`       |
   | pointers etc.)                          |                 |                            |
   +-----------------------------------------+-----------------+----------------------------+
   | LEDs                                    | LEDs            | :ref:`section_leds`        |
   +-----------------------------------------+-----------------+----------------------------+

The simulation platform uses a mock which simulates all I/O devices.
Refer to the chapter :ref:`section_simulation`


Threads
=======

Principle
---------

The MicroUI implementation for MicroEJ uses internal threads. These
threads are created during the MicroUI initialization step, and are
started by a call to ``MicroUI.start()``. Refer the the MicroUI
specification [MUI] for more information about internal threads.

List
----

-  DisplayPump: This thread manages all display events (``repaint``,
   ``show()``, etc. There is one thread per display.

-  InputPump: This thread reads the I/O devices inputs and dispatches
   them into the display pump(s).

Memory
------

The threads are always running. The user has to count them to determine
the number of concurrent threads the MicroEJ core engine can run (see
Memory options in :ref:`workbenchLaunchOptions`).

Exceptions
----------

The threads cannot be stopped with a Java exception: The exceptions are
always checked by the framework.

When an exception occurs in a user method called by an internal thread
(for instance ``paint()``), the current ``UncaughtExceptionHandler``
receives the exception. The behavior of the default handler is to print
the stack trace.


Transparency
============

MicroUI provides several policies to use the transparency. These
policies depend on several factors, including the kind of drawing and
the LCD pixel rendering format. The main concept is that MicroUI does
not allow you to draw something with a transparency level different from
255 (fully opaque). There are two exceptions: the images and the fonts.

Images
------

Drawing an image (a pre-generated image or an image decoded at runtime)
which contains some transparency levels does not depend on the LCD pixel
rendering format. During the image drawing, each pixel is converted into
32 bits by pixel format.

This pixel format contains 8 bits to store the transparency level
(alpha). This byte is used to merge the foreground pixel (image
transparent pixel) with the background pixel (LCD buffer opaque pixel).
The formula to obtain the pixel is:

.. math::

   {\alpha}Mult = {\alpha}FG * {\alpha}BG) / 255

.. math::

   {\alpha}Out = {\alpha}FG + {\alpha}BG - {\alpha}Mult

.. math::

   COut = (CFG * {\alpha}FG + CBG * {\alpha}BG - CBG * {\alpha}Mult) / {\alpha}Out 

where:

-  :math:`{\alpha}`\ *FG* is the alpha level of the foreground pixel (layer pixel)

-  :math:`{\alpha}`\ *BG* is the alpha level of the background pixel (working buffer
   pixel)

-  :math:`{\alpha}`\ *xx* is a color component of a pixel (Red, Green or Blue).

-  :math:`{\alpha}`\ *Out* is the alpha level of the final pixel

Fonts
-----

A font holds only a transparency level (alpha). This fixed alpha level
is defined during the pre-generation of a font (see
:ref:`section_fonts`).

-  ``1`` means 2 levels are managed: fully opaque and fully transparent.

-  ``2`` means 4 levels are managed: fully opaque, fully transparent and
   2 intermediate levels.

-  ``4`` means 16 levels are managed: fully opaque, fully transparent
   and 14 intermediate levels.

-  ``8`` means 256 levels are managed: fully opaque, fully transparent
   and 254 intermediate levels.


Dependencies
============

-  MicroUI initialization step (see `section_static_init`).

-  MicroUI C libraries (see :ref:`section_architecture`).


.. _section_microui_installation:

Installation
============

The MicroUI library is an additional module. In the platform
configuration file, check :guilabel:`UI` > :guilabel:`MicroUI` to install the library.
When checked, the XML file :guilabel:`microui` > :guilabel:`microui.xml` is required
during platform creation in order to configure the module. This
configuration step is used to extend the MicroUI library. Refer to the
chapter :ref:`section_static_init` for more information about the
MicroUI Initialization step.


Use
===

The classpath variable named ``MICROUI-2.0`` is available.

This library provides a set of options. Refer to the chapter
:ref:`workbenchLaunchOptions` which lists all available options.


..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
