==========================
Hardware Abstraction Layer
==========================


Principle
=========

The Hardware Abstraction Layer (HAL) library features API that target IO
devices, such as GPIOs, analog to/from digital converters (ADC / DAC),
etc. The API are very basic in order to be as similar as possible to the
BSP drivers.


Functional Description
======================

The MicroEJ Application configures and uses some physical GPIOs, using
one unique identifier per GPIO. The HAL implementation made for each
MicroEJ Platform has the responsibility of verifying the veracity of the
GPIO identifier and the valid GPIO configuration.

Theoretically, a GPIO can be reconfigured at any time. For example a
GPIO is configured in OUTPUT first, and later in ADC entry. However the
HAL implementation can forbid the MicroEJ Application from performing
this kind of operation.


Identifier
==========

Basic Rule
----------

MicroEJ Application manipulates anonymous identifiers used to identify a
specific GPIO (port and pin). The identifiers are fixed by the HAL
implementation made for each MicroEJ Platform, and so this
implementation is able to make the link between the MicroEJ Application
identifiers and the physical GPIOs.

-  A ``port`` is a value between ``0`` and ``n - 1``, where ``n`` is the
   available number of ports.

-  A ``pin`` is a value between ``0`` and ``m - 1``, where ``m`` is the
   maximum number of pins per port.

Generic Rules
-------------

Most of time the basic implementation makes the link between the port /
pin and the physical GPIO following these rules:

-  The port ``0`` targets all MCU pins. The first pin of the first MCU
   port has the ID ``0``, the second pin has ``1``; the first pin of the
   next MCU port has the ID ``m`` (where ``m`` is the maximum number of
   pins per port), etc. Examples:

   ::

      /* m = 16 (16 pins max per MCU port) */
      mcu_pin = application_pin & 0xf;
      mcu_port = (application_pin >> 4) + 1;

   ::

      /* m = 32 (32 pins max per MCU port) */
      mcu_pin = application_pin & 0x1f;
      mcu_port = (application_pin >> 5) + 1;

-  The port from ``1`` to ``n`` (where ``n`` is the available number of
   MCU ports) targets the MCU ports. The first MCU port has the ID
   ``1``, the second has the ID ``2``, and the last port has the ID
   ``n``.

-  The pin from ``0`` to ``m - 1`` (where ``m`` is the maximum number of
   pins per port) targets the port pins. The first port pin has the ID
   ``0``, the second has the ID ``1``, and the last pin has the ID
   ``m - 1``.

The implementation can also normalize virtual and physical board
connectors. A physical connector is a connector available on the board,
and which groups several GPIOs. The physical connector is usually called
``JPn`` or ``CNn``, where ``n`` is the connector ID. A virtual connector
represents one or several physical connectors, and has a *name*; for
example ``ARDUINO_DIGITAL``.

Using a unique ID to target a virtual connector allows you to make an
abstraction between the MicroEJ Application and the HAL implementation.
For exmaple, on a board A, the pin ``D5`` of ``ARDUINO_DIGITAL`` port
will be connected to the MCU ``portA``, ``pin12`` (GPIO ID = ``1``,
``12``). And on board B, it will be connected to the MCU ``port5``,
``pin0`` (GPIO ID = ``5``, ``0``). From the MicroEJ Application point of
view, this GPIO has the ID ``30``, ``5``.

Standard virtual connector IDs are:

::

   ARDUINO_DIGITAL = 30;
   ARDUINO_ANALOG = 31;

Finally, the available physical connectors can have a number from ``64``
to ``64 + i - 1``, where ``i`` is the available number of connectors on
the board. This allows the application to easily target a GPIO that is
available on a physical connector, without knowing the corresponding MCU
port and pin.

::

   JP3 = 64;
   JP6 = 65;
   JP11 = 66;


Configuration
=============

A GPIO can be configured in any of five modes:

-  Digital input: The MicroEJ Application can read the GPIO state (for
   example a button state).

-  Digital input pull-up: The MicroEJ Application can read the GPIO
   state (for example a button state); the default GPIO state is driven
   by a pull-up resistor.

-  Digital output: The MicroEJ Application can set the GPIO state (for
   example to drive an LED).

-  Analog input: The MicroEJ Application can convert some incoming
   analog data into digital data (ADC). The returned values are values
   between ``0`` and ``n - 1``, where ``n`` is the ADC precision.

-  Analog output: The MicroEJ Application can convert some outgoing
   digital data into analog data (DAC). The digital value is a
   percentage (0 to 100%) of the duty cycle generated on selected GPIO.


Dependencies
============

-  ``LLHAL_impl.h`` implementation (see :ref:`LLHAL-API-SECTION`).


Installation
============

HAL is an additional module. In the platform configuration file, check
:guilabel:`HAL` to install the module.


Use
===

The `HAL API Module`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project to use the HAL library.

::

   <dependency org="ej.api" name="hal" rev="1.0.4"/>

.. _HAL API Module: https://forge.microej.com/artifactory/microej-developer-repository-release/ej/api/hal/

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
