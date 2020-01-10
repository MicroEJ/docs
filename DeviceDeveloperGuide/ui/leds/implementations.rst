.. _section_leds_implementation:

Implementations
===============

The LEDs module provides only one implementation which exposes some low
level API (LLLEDS) that allow the BSP to manage the LEDs. This
implementation of the MicroUI ``Leds`` API provides some low level API.
The BSP has to implement these LLAPI, making the link between the
MicroUI C library ``leds`` and the BSP LEDs drivers.

The LLAPI to implement are listed in the header file ``LLLEDS_impl.h``.
First, in the initialization function, the BSP must return the available
number of LEDs the board provides. The others functions are used to turn
the LEDs on and off.

The LLAPI are the same for the LED which is connected to a ``GPIO``
(``0`` or ``1``) or via a ``PWM``. The BSP has the responsibility of
interpreting the MicroEJ application parameter ``intensity``.

Typically, when the LED is connected to a ``GPIO``, the ``intensity``
"0" means "OFF," and all others values "ON." When the LED is connected
via a ``PWM``, the ``intensity`` "0" means "OFF," and all others values
must configure the ``PWM`` signal.

The BSP should be able to return the state of an LED. If it is not able
to do so (for example ``GPIO`` is not accessible in read mode), the
returned value may be wrong. The MicroEJ application may not be able to
know the LEDs states.

When there is no LED on the board, a *stub* implementation of C library
is available. This C library must be linked by the third-party C IDE
when the MicroUI module is installed in the MicroEJ platform.
