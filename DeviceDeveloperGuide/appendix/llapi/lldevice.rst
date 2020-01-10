.. _LLDEVICE-API-SECTION:

LLDEVICE: Device Information
============================

Naming Convention
-----------------

The Low Level Device API (LLDEVICE), relies on functions that need to be
implemented by engineers in a driver. The names of these functions match
the ``LLDEVICE_IMPL_*`` pattern.

Header Files
------------

One C header file is provided:

-  LLDEVICE_impl.h

   Defines a set of functions that the BSP must implement to get the
   platform architecture name and unique device identifier.
