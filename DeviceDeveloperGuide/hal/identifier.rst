Identifier
==========

Basic Rule
----------

MicroEJ application manipulates anonymous identifiers used to identify a
specific GPIO (port and pin). The identifiers are fixed by the HAL
implementation made for each MicroEJ Platform, and so this
implementation is able to make the link between the MicroEJ application
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
abstraction between the MicroEJ application and the HAL implementation.
For exmaple, on a board A, the pin ``D5`` of ``ARDUINO_DIGITAL`` port
will be connected to the MCU ``portA``, ``pin12`` (GPIO ID = ``1``,
``12``). And on board B, it will be connected to the MCU ``port5``,
``pin0`` (GPIO ID = ``5``, ``0``). From the MicroEJ application point of
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
