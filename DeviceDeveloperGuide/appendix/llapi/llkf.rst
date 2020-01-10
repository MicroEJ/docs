.. _LLKF-API-SECTION:

LLKERNEL: Multi Applications
============================

Naming Convention
-----------------

The Low Level Kernel API, the ``LLKERNEL`` API, relies on functions that
need to be implemented. The naming convention for such functions is that
their names match the ``LLKERNEL_IMPL_*`` pattern.

Header Files
------------

One C header file is provided:

-  LLKERNEL_impl.h

   Defines the set of functions that the BSP must implement to manage
   memory allocation of dynamically installed applications.
