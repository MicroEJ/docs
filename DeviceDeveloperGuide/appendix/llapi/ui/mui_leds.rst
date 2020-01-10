.. _LLLEDS-API-SECTION:

LLLEDS: LEDs
============

Principle
---------

The LEDs stack provides a Low Level API for connecting LED drivers. The
file ``LLLEDS_impl.h``, which comes with the LEDs stack, defines the API
headers to be implemented.

Naming convention
-----------------

The Low Level API relies on functions that must be implemented. The
naming convention for such functions is that their names match the
``*_IMPL_*`` pattern.

Initialization
--------------

The first function called is ``LLLEDS_IMPL_initialize``, which allows
the driver to initialize all LED devices. This method must return the
number of LEDs available.

Each LED has a unique identifier. The first LED has the ID 0, and the
last has the ID NbLEDs – 1.

This UI extension provides support to efficiently implement the set of
methods that interact with the LEDs provided by a device. Below are the
relevant C functions:

-  ``LLLEDS_IMPL_getIntensity``: Get the intensity of a specific LED
   using its ID.

-  ``LLLEDS_IMPL_setIntensity``: Set the intensity of an LED using its
   ID.
