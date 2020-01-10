.. _LLCOMM-API-SECTION:

LLCOMM: Serial Communications
=============================

Naming Convention
-----------------

The Low Level Comm API (LLCOMM), relies on functions that need to be
implemented by engineers in a driver. The names of these functions match
the ``LLCOM_BUFFERED_CONNECTION_IMPL_*`` or the
``LLCOM_CUSTOM_CONNECTION_IMPL_*``\ pattern.

Header Files
------------

Four C header files are provided:

-  LLCOMM_BUFFERED_CONNECTION_impl.h

   Defines the set of functions that the driver must implement to
   provide a Buffered connection

-  LLCOMM_BUFFERED_CONNECTION.h

   Defines the set of functions provided by ECOM Comm that can be called
   by the driver (or other C code) when using a Buffered connection

-  LLCOMM_CUSTOM_CONNECTION_impl.h

   Defines the set of functions that the driver must implement to
   provide a Custom connection

-  LLCOMM_CUSTOM_CONNECTION.h

   Defines the set of functions provided by ECOM Comm that can be called
   by the driver (or other C code) when using a Custom connection
