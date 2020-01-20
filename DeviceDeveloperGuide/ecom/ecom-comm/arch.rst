Component architecture
======================

The ECOM Comm C module relies on a native driver to perform actual
communication on the serial ports. Each port can be bound to a different
driver implementation, but most of the time, it is possible to use the
same implementation (i.e. same code) for multiple ports. Exceptions are
the use of different hardware UART types, or the need for different
behaviors.

Five C header files are provided:

-  ``LLCOMM_impl.h``

   Defines the set of functions that the driver must implement for the
   global ECOM comm stack, such as synchronization of accesses to the
   connections pool.

-  ``LLCOMM_BUFFERED_CONNECTION_impl.h``

   Defines the set of functions that the driver must implement to
   provide a Buffered connection

-  ``LLCOMM_BUFFERED_CONNECTION.h``

   Defines the set of functions provided by ECOM Comm that can be called
   by the driver (or other C code) when using a Buffered connection

-  ``LLCOMM_CUSTOM_CONNECTION_impl.h``

   Defines the set of functions that the driver must implement to
   provide a Custom connection

-  ``LLCOMM_CUSTOM_CONNECTION.h``

   Defines the set of functions provided by ECOM Comm that can be called
   by the driver (or other C code) when using a Custom connection

The ECOM Comm drivers are implemented using standard LLAPI features. The
diagram below shows an example of the objects (both Java and C) that
exist to support a Buffered connection.

.. figure:: ecom-comm/images/architecture.svg
   :alt: ECOM Comm components
   :width: 80.0%

   ECOM Comm components

The connection is implemented with three objects  [1]_ :

-  The Java object used by the application; an instance of
   ``ej.ecom.io.CommConnection``

-  The connection object within the ECOM Comm C module

-  The connection object within the driver

Each driver implementation provides one or more connections. Each
connection typically corresponds to a physical UART.

.. [1]
   This is a conceptual description to aid understanding - the reality
   is somewhat different, although that is largely invisible to the
   implementor of the driver.
