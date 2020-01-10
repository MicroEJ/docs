.. _LLHAL-API-SECTION:

LLHAL: Hardware Abstraction Layer
=================================

Naming Convention
-----------------

The Low Level API, the ``LLHAL`` API, relies on functions that need to
be implemented. The naming convention for such functions is that their
names match the ``LLHAL_IMPL_*`` pattern.

Header Files
------------

One header file is provided:

-  LLHAL_impl.h

   Defines the set of functions that the BSP must implement to configure
   and drive some MCU GPIO.
