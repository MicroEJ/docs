.. _section_leds:

===
LED
===


Principle
=========

The LED engine contains the C part of the MicroUI implementation which manages LED devices. This module is composed of only one element: an implementation of the low level API for the LEDs which must be provided by the BSP (see :ref:`LLLEDS-API-SECTION`).

.. _section_leds_implementation:

Functional Description
======================

The LED engine implements the MicroUI `Leds <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/led/Leds.html>`_ framework. ``LLUI_LED`` specifies the low level API that receive orders from the Java world.

The low level API are the same for the LED which is connected to a ``GPIO`` (``0`` or ``1``), to a ``PWM``, to a bus (``I2C``, ``SPI``) etc. The BSP has the responsibility of interpreting the MicroEJ Application parameter ``intensity``.

Typically, when the LED is connected to a ``GPIO``, the ``intensity`` "0" means "OFF," and all others values "ON." When the LED is connected via a ``PWM``, the ``intensity`` "0" means "OFF," and all others values must configure the ``PWM`` signal.

The BSP should be able to return the state of an LED. If it is not able to do so (for example ``GPIO`` is not accessible in read mode), the returned value may be wrong. The MicroEJ Application may not be able to know the LEDs states.

Low-Level API
=============

The LED engine provides low level APIs that allow the BSP to manage the LEDs. The BSP has to implement these LLAPI, making the link between the MicroUI library and the BSP LEDs drivers.

The LLAPI to implement are listed in the header file ``LLUI_LEDS_impl.h``. First, in the initialization function, the BSP must return the available number of LEDs the board provides. The others functions are used to turn the LEDs on and off.

.. figure:: images/ui_llapi_led.*
   :alt: MicroUI LED Low-Level
   :width: 200px

When there is no LED on the board, a *stub* implementation of C library is available. This C library must be linked by the third-party C IDE when the MicroUI module is installed in the MicroEJ Platform. This stub library does not provide any low-level API files.

Dependencies
============

-  MicroUI module (see :ref:`section_microui`)

-  ``LLUI_LED_impl.h`` implementation if standard implementation is chosen
   (see :ref:`section_leds_implementation` and
   :ref:`LLLEDS-API-SECTION`).


.. _section_leds_installation:

Installation
============

LEDs is a sub-part of MicroUI library. When the MicroUI module is installed, the LEDs module must be installed in order to be able to connect physical LEDs with MicroEJ Platform. If not installed, the
*stub* module will be used.

In the platform configuration file, check :guilabel:`UI` > :guilabel:`LEDs` to install LEDs.

Use
===

The MicroUI LEDs APIs are available in the class `ej.microui.led.Leds <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/led/Leds.html>`_.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
