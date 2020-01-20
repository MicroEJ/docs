.. _LLMJVM-API-SECTION:

LLMJVM: MicroEJ core engine
===========================

Naming Convention
-----------------

The Low Level MicroEJ core engine API, the ``LLMJVM`` API, relies on
functions that need to be implemented. The naming convention for such
functions is that their names match the ``LLMJVM_IMPL_*`` pattern.

Header Files
------------

Three C header files are provided:

-  LLMJVM_impl.h

   Defines the set of functions that the BSP must implement to launch
   and schedule the virtual machine

-  LLMJVM.h

   Defines the set of functions provided by virtual machine that can be
   called by the BSP when using the virtual machine

-  LLBSP_impl.h

   Defines the set of extra functions that the BSP must implement.
