.. _section_leds:

===
LED
===


Principle
=========

The LED module contains the C part of the MicroUI implementation which manages LED devices.
This module is composed of only one element: an implementation of the Abstraction Layer APIs for the LEDs which must be provided by the BSP (see :ref:`LLLEDS-API-SECTION`).

.. _section_leds_implementation:

Functional Description
======================

The LED module implements the MicroUI `Leds`_ framework.
``LLUI_LED`` specifies the Abstraction Layer APIs that receive orders from the Java world.

The Abstraction Layer APIs are the same for the LED which is connected to a ``GPIO`` (``0`` or ``1``), to a ``PWM``, to a bus (``I2C``, ``SPI``), etc.
The BSP has the responsibility of interpreting the application parameter ``intensity``.

Typically, when the LED is connected to a ``GPIO``, the ``intensity`` "0" means "OFF", and all other values "ON".
When the LED is connected via a ``PWM``, the ``intensity`` "0" means "OFF", and all other values must configure the ``PWM`` duty cycle signal.

The BSP should be able to return the state of an LED.
If it is not able to do so (for example ``GPIO`` is not accessible in read mode), the BSP has to save the LED state in a global variable.
If not, the returned value may be wrong and the application may not be able to know the LEDs states.

.. _Leds: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/led/Leds.html

.. _section_leds_llapi:

Abstraction Layer API
=====================

The LED module provides Abstraction Layer APIs that allow the BSP to manage the LEDs.
The BSP has to implement these Abstraction Layer APIs, making the link between the MicroUI library and the BSP LEDs drivers.

The Abstraction Layer APIs to implement are listed in the header file ``LLUI_LEDS_impl.h``.
First, in the initialization function, the BSP must return the available number of LEDs the board provides.
The other functions are used to turn the LEDs on and off.

.. figure:: images/ui_llapi_led.*
   :alt: MicroUI LED Abstraction Layer
   :width: 200px
   :align: center

   Led Abstraction Layer API

When there is no LED on the board, a *stub* implementation of C library is available.
This C library must be linked by the third-party C IDE when the MicroUI module is installed in the VEE Port.
This stub library does not provide any Abstraction Layer API files.

Typical Implementation
======================

This chapter helps to write a basic ``LLUI_LEDS_impl.h`` implementation.
This implementation manages some two-state LEDs: on or off.

The pseudo-code calls external functions such as ``LEDS_DRIVER_xxx`` to symbolize the use of external drivers.

.. code:: c

   static void get_led_port_and_pin(int32_t ledID, int32_t* port, int32_t* pin)
   {
      switch(ledID)
      {
         /* TODO */
         *port = ...;
         *pin = ...;
      }
   }	

   jint LLUI_LED_IMPL_getIntensity(jint ledID)
   {
      int32_t port;
      int32_t pin;
      get_led_port_and_pin(ledID, &port, &pin);

      return GPIO_ReadPin(port, pin) == GPIO_PIN_RESET ? LLUI_LED_MAX_INTENSITY : LLUI_LED_MIN_INTENSITY;
   }

   jint LLUI_LED_IMPL_initialize(void)
   {
      return DRIVER_LEDS_Init();  // return the available number of leds
   }

   void LLUI_LED_IMPL_setIntensity(jint ledID, jint intensity)
   {
      int32_t port;
      int32_t pin;
      get_led_port_and_pin(ledID, &port, &pin);

      GPIO_WritePin(port, pin, 0 == intensity ? GPIO_PIN_RESET : GPIO_PIN_SET);
   }

Dependencies
============

-  MicroUI module (see :ref:`section_microui`).

-  ``LLUI_LED_impl.h`` implementation if standard implementation is chosen (see :ref:`section_leds_implementation` and :ref:`LLLEDS-API-SECTION`).


.. _section_leds_installation:

Installation
============

LEDs is a sub-part of MicroUI library.
When the MicroUI module is installed, the LED module must be installed in order to be able to connect physical LEDs with VEE Port.
If not installed, the *stub* module will be used.

In the VEE Port configuration file, check :guilabel:`UI` > :guilabel:`LEDs` to install LEDs.

Use
===

The MicroUI LEDs APIs are available in the class ``ej.microui.led.`` `Leds`_.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
