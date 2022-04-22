.. _section_microui:

=======
MicroUI
=======


Principle
=========

MicroUI library defines a Low Level UI framework for embedded devices. This module allows the creation of basic Human-Machine-Interfaces (HMI), with output on a pixel-based screen. 

.. _section_architecture:

Architecture
============

MicroUI library is the entry point to perform some drawings on a display and to interact with user input events. This library contains only a minimal set of basic APIs. High-level libraries can be used to have more expressive power, such as :ref:`mwt`. In addition to this restricted set of APIs, the MicroUI implementation has been designed so that the EDC and BON footprint is minimal. 

At MicroEJ application startup all MicroUI objects relative to the I/O devices are created and accessible. The following MicroUI methods allow you to access these objects:

-  `Display.getDisplay() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#getDisplay-->`_ : returns the instance of the display which drives the main display screen.

-  `Leds.getNumberOfLeds() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/led/Leds.html#getNumberOfLeds-->`_: returns the numbers of available LEDs.

MicroUI is not a standalone library. It requires a configuration step and several extensions to drive I/O devices (display, inputs, LEDs).

First, MicroUI requires a configuration step in order to create these internal objects before the call to the ``main()`` method. The chapter :ref:`section_static_init` explains how to perform the configuration step.

.. note::

   This configuration step is the same for both embedded and simulated Platforms.

The embedded platform requires some additional C libraries to drive the I/O devices. Each C library is dedicated to a specific kind of I/O device. A specific chapter is available to explain each kind of I/O device.

.. table:: MicroUI C libraries

   +-------------------------------------------+-----------------+----------------------------+
   | I/O devices                               | Extension Name  | Chapter                    |
   +===========================================+=================+============================+
   | Graphical / pixel-based display           | Display         | :ref:`section_display`     |
   +-------------------------------------------+-----------------+----------------------------+
   | Inputs (buttons, joystick, touch,         | Input           | :ref:`section_input`       |
   | pointers, etc.)                           |                 |                            |
   +-------------------------------------------+-----------------+----------------------------+
   | LEDs                                      | LED             | :ref:`section_leds`        |
   +-------------------------------------------+-----------------+----------------------------+

The simulation platform uses a mock which simulates all I/O devices.
Refer to the chapter :ref:`section_ui_simulation`.


Thread
=======

Principle
---------

The MicroUI implementation for MicroEJ uses one internal thread. This thread is created during the MicroUI initialization step, and is started by a call to `MicroUI.start() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/MicroUI.html#start-->`_. 

Role
----

This thread has several roles:

- It manages all display events (`requestRender() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#requestRender-->`_, `requestShow() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#requestShow-ej.microui.display.Displayable->`_, etc.).
- It reads the I/O devices inputs and dispatches them into the event generators' listeners. See input section: :ref:`section_input`. 
- It allows to run some piece of code using the `callSerially() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/MicroUI.html#callSerially-java.lang.Runnable->`_ method.

Memory
------

The thread is always running. The user has to count it to determine the number of concurrent threads the MicroEJ Core Engine can run (see *Memory* options in :ref:`application_options`).

Exceptions
----------

The thread cannot be stopped with a Java exception: the exceptions are always checked by the framework.

When an exception occurs in a user method called by the internal thread (for instance `render() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Displayable.html#render-ej.microui.display.GraphicsContext->`_), the current ``UncaughtExceptionHandler`` receives the exception. When no exception handler is set, a default handler prints the stack trace.

Native Calls
============

The MicroUI implementation for MicroEJ uses native methods to perform some actions (read input devices events, perform drawings, turn on LEDs, etc.). The library implementation has been designed to not use blocking native methods (wait input devices, wait end of drawing, etc.) which can lock the full MicroEJ Core Engine execution. 

The specification of the native methods is to perform the action as fast as possible. The action execution may be sequential or parallel because an action is able to use a third-party device (software or hardware). In this case, some callbacks are available to notify the end of this kind of parallel actions. 

However some actions have to wait the end of a previous parallel action. By consequence the caller thread is blocked until the previous action is done; in other words, until the previous parallel action has called its callback. In this case, only the current Java thread is locked (because it cannot continue its execution until both actions are performed). All other Java threads can run, even a thread with a lower priority than current thread. If no thread has to be run, MicroEJ Core Engine goes in sleep mode until the native callback is called.

Transparency
============

MicroUI provides several policies to use the transparency. These policies depend on several factors, including the kind of drawing and the display pixel rendering format. The main concept is that MicroUI does not allow you to draw something with a transparency level different from 255 (fully opaque). There are two exceptions: the images and the fonts.

Images
------

Drawing an image (a pre-generated image or an image decoded at runtime)
which contains some transparency levels does not depend on the display pixel
rendering format. During the image drawing, each pixel is converted into
32 bits by pixel format.

This pixel format contains 8 bits to store the transparency level
(alpha). This byte is used to merge the foreground pixel (image
transparent pixel) with the background pixel (buffer opaque pixel).
The formula to obtain the pixel is:

.. math::

   {\alpha}Mult = ({\alpha}FG * {\alpha}BG) / 255

.. math::

   {\alpha}Out = {\alpha}FG + {\alpha}BG - {\alpha}Mult

.. math::

   COut = (CFG * {\alpha}FG + CBG * {\alpha}BG - CBG * {\alpha}Mult) / {\alpha}Out 

The destination buffer is always opaque, so:

.. math::

   COut = (CFG * {\alpha}FG + CBG * (255 - {\alpha}Mult)) / 255

where:

-  :math:`{\alpha}`\ *FG* is the alpha level of the foreground pixel (layer pixel),
-  :math:`{\alpha}`\ *BG* is the alpha level of the background pixel (working buffer pixel),
-  *Cxx* is a color component of a pixel (Red, Green or Blue),
-  :math:`{\alpha}`\ *Out* is the alpha level of the final pixel.

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

.. _section_microui_installation:

Installation
============

The MicroUI library is an additional module. In the platform
configuration file, check :guilabel:`UI` > :guilabel:`MicroUI` to install the library.
When checked, the XML file ``microui/microui.xml`` is required
during platform creation in order to configure the module. This
configuration step is used to extend the MicroUI library. Refer to the
chapter :ref:`section_static_init` for more information about the
MicroUI Initialization step.


Use
===

See :ref:`MicroUI <section_app_microui>` chapter in Application Developer Guide.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
