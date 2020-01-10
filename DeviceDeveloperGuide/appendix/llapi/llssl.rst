.. _LLNET_SSL-API-SECTION:

LLNET_SSL: SSL
==============

Naming Convention
-----------------

The Low Level API, the ``LLNET_SSL`` API, relies on functions that need
to be implemented. The naming convention for such functions is that
their names match the ``LLNET_SSL_*`` pattern.

Header Files
------------

Three header files are provided:

-  LLNET_SSL_CONTEXT_impl.h

   Defines a set of functions that the BSP must implement to create a
   SSL Context and to load CA (Certificate Authority) certificates as
   trusted certificates.

-  LLNET_SSL_SOCKET_impl.h

   Defines a set of functions that the BSP must implement to initialize
   the SSL native components, to create an underlying SSL Socket and to
   initiate a SSL session handshake. It also defines some I/O operations
   such as ``LLNET_SSL_SOCKET_IMPL_write`` or
   ``LLNET_SSL_SOCKET_IMPL_read`` used for encrypted data exchange
   between the client and the server.

-  LLNET_SSL_X509_CERT_impl.h

   Defines a function named ``LLNET_SSL_X509_CERT_IMPL_parse`` for
   certificate parsing. This function checks if a given certificate is
   an X.509 digital certificate and returns its encoded format type :
   Distinguished Encoding Rules (DER) or Privacy-Enchanced Mail (PEM).
