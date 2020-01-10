.. _LLNET-API-SECTION:

LLNET: Network
==============

Naming Convention
-----------------

The Low Level API, the ``LLNET`` API, relies on functions that need to
be implemented. The naming convention for such functions is that their
names match the ``LLNET_IMPL_*`` pattern.

Header Files
------------

Several header files are provided:

-  LLNET_CHANNEL_impl.h

   Defines a set of functions that the BSP must implement to initialize
   the Net native component. It also defines some configuration
   operations to setup a network connection.

-  LLNET_SOCKETCHANNEL_impl.h

   Defines a set of functions that the BSP must implement to create,
   connect and retrieve information on a network connection.

-  LLNET_STREAMSOCKETCHANNEL_impl.h

   Defines a set of functions that the BSP must implement to do some I/O
   operations on connection oriented socket (TCP). It also defines
   function to put a server connection in accepting mode (waiting for a
   new client connection).

-  LLNET_DATAGRAMSOCKETCHANNEL_impl.h

   Defines a set of functions that the BSP must implement to do some I/O
   operations on connectionless oriented socket (UDP).

-  LLNET_DNS_impl.h

   Defines a set of functions that the BSP must implement to request
   host IP address associated to a host name or to request Domain Name
   Service (DNS) host IP addresses setup in the underlying system.

-  LLNET_NETWORKADDRESS_impl.h

   Defines a set of functions that the BSP must implement to convert
   string IP address or retrieve specific IP addresses (lookup,
   localhost or loopback IP address).

-  LLNET_NETWORKINTERFACE_impl.h

   Defines a set of functions that the BSP must implement to retrieve
   information on a network interface (MAC address, interface link
   status, etc.).
