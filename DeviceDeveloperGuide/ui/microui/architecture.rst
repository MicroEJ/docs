.. _section_architecture:

Architecture
============

MicroUI is not a standalone library. It requires a configuration step
and several extensions to drive I/O devices (display, inputs, LEDs,
etc.).

.. figure:: ui/microui/images/microui-fragment-dependencies.svg
   :alt: MicroUI Elements
   :width: 80.0%

   MicroUI Elements

At MicroEJ application startup all MicroUI objects relative to the I/O
devices are created and accessible. The following MicroUI methods allow
you to access these internal objects:

-  ``Display.getDefaultDisplay()``: returns the instance of the default
   display which drives the main LCD screen.

-  ``Leds.getNumberOfLeds()``: returns the numbers of available LEDs.

First, MicroUI requires a configuration step in order to create these
internal objects before the call to the ``main()`` method. The chapter
`??? <#section_static_init>`__ explains how to perform the configuration
step.

.. note::

   This configuration step is the same for both embedded and simulation
   platforms.

The embedded platform requires some additional C libraries to drive the
I/O devices. Each C library is dedicated to a specific kind of I/O
device. A specific chapter is available to explain each kind of I/O
device.

.. table:: MicroUI C libraries

   +-----------------------------------------+-----------------+-----------+
   | I/O devices                             | Extension Name  | Chapter   |
   +=========================================+=================+===========+
   | Graphical / pixelated display (LCD      | Display         | `??? <#s  |
   | screen)                                 |                 | ection_di |
   |                                         |                 | splay>`__ |
   +-----------------------------------------+-----------------+-----------+
   | Inputs (buttons, joystick, touch,       | Input           | `??? <    |
   | pointers etc.)                          |                 | #section_ |
   |                                         |                 | input>`__ |
   +-----------------------------------------+-----------------+-----------+
   | LEDs                                    | LEDs            | `???      |
   |                                         |                 | <#section |
   |                                         |                 | _leds>`__ |
   +-----------------------------------------+-----------------+-----------+

The simulation platform uses a mock which simulates all I/O devices.
Refer to the chapter `??? <#section_simulation>`__
