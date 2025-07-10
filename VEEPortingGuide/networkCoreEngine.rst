.. _network_core:

===================
Network Core Engine
===================


Principle
=========

The Net module defines a low-level network framework for embedded
devices. This module allows you to manage connection (TCP)- or
connectionless (UDP)-oriented protocols for client/server networking
applications.


Functional Description
======================

The Net library includes two sub-protocols:

-  UDP: a connectionless-oriented protocol that allows communication
   with the server or client side in a non-reliable way. No handshake
   mechanisms, no guarantee on delivery, and no order in packet sending.

-  TCP: a connection-oriented protocol that allows communication with
   the server or client side in a reliable way. Handshakes mechanism
   used, bytes ordered, and error checking performed upon delivery.


Dependencies
============

-  ``LLNET_CHANNEL_impl.h``, ``LLNET_SOCKETCHANNEL_impl.h``,
   ``LLNET_STREAMSOCKETCHANNEL_impl.h``,
   ``LLNET_DATAGRAMSOCKETCHANNEL_impl.h``, ``LLNET_DNS_impl.h``,
   ``LLNET_NETWORKADDRESS_impl.h``, ``LLNET_NETWORKINTERFACE_impl.h``
   (see :ref:`LLNET-API-SECTION`).


.. _network_core_installation:

Installation
============

NET is an additional module. 
To enable it, the Net :ref:`Pack <pack_overview>` (which bundles several libraries: Net, SSL & Security) must be installed in your VEE Port:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         microejPack("com.microej.pack.net:net-pack:11.0.2")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.pack.net" name="net-pack" rev="11.0.2"/>


      Then, using the VEE Port Editor (see :ref:`platform_module_configuration`), enable the Net library (API, Impl & Mock):

      .. figure:: images/net-ssl_modules.*
         :alt: Net Pack Modules

         Net Pack Modules

Initialization
==============

When porting the Net library it is necessary to initialize and configure the lower layers of the network before the application can access it.
This includes configuring the hardware network interfaces, initializing the IP stack, and ensuring connectivity is available.
The Net library assumes that these are correctly set up and ready for use when the initialization is done.

The entry point for this initialization is the following native function: ``LLNET_CHANNEL_impl_initialize``:

.. code-block::

   /**
    * @brief Initializes the TCP/IP stack components.
    *
    * @note Throws NativeIOException on error.
    *
    * @see LLNET_ERRORS.h header file for error codes.
    */
   void LLNET_CHANNEL_IMPL_initialize(void);

It is called from a static code block in the Net library so it will run before the application starts, see `this implementation example <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/blob/main/bsp/vee/port/net/src/LLNET_CHANNEL_bsd.c#L63>`_.

.. code-block::

   void LLNET_CHANNEL_IMPL_initialize(void)
   {
      LLNET_DEBUG_TRACE("%s\n", __func__);
      int32_t res;
   #ifdef LLNET_IGNORE_SIGPIPE
      // Ignore SIGPIPE signal that is sent when a connection is closed by the remote host.
      signal(SIGPIPE, SIG_IGN);
   #endif
      llnet_init();
      res = async_select_init();
      if(res != 0){
         SNI_throwNativeIOException(J_EUNKNOWN, "init error");
      }
   }

This example is used on VEE Port with BSD-like sockets APIs, on all VEE Ports a macro is provided to call custom initialization code (also see header `here <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/blob/main/bsp/vee/port/net/inc/LLNET_configuration.h#L108>`_):

.. code-block::

   /**
    * Use this macro to define the initialization function of the network stack.
    * Called from LLNET_CHANNEL_IMPL_initialize().
    *
    * For example, It can be used to initialize ecom-network & ecom-wifi:
    * 	#include "LLECOM_NETWORK.h"
    *	#include "LLECOM_WIFI.h"
    *	static inline int32_t llnet_init() {
    *		LLECOM_NETWORK_initialize();
    *		LLECOM_WIFI_initialize();
    *		return 0;
    *	}
    *
    * By default this macro does nothing.
    */
   #include "lwip_util.h"
   #define llnet_init		llnet_lwip_init

Use
===

The `Net API Module`_ must be added to the Application project build file to use the NET library:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.api:net:1.1.4")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="ej.api" name="net" rev="1.1.4"/>

This library provides a set of options. Refer to the chapter
:ref:`application_options` which lists all available options.

.. _Net API Module: https://repository.microej.com/modules/ej/api/net/

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
