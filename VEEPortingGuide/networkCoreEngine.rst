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

It is called from a static code block in the Net library so it will run before the application starts, see the following implementation example `available here <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/blob/main/bsp/vee/port/net/src/LLNET_CHANNEL_bsd.c>`_:

.. rli:: https://raw.githubusercontent.com/MicroEJ/nxp-vee-imxrt1170-evk/refs/heads/main/bsp/vee/port/net/src/LLNET_CHANNEL_bsd.c
   :language: c
   :lines: 63-76
   :linenos:
   :lineno-start: 63

This example is used on VEE Port with BSD-like sockets APIs, on all VEE Ports a macro is provided to call custom initialization code (also see `here <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/blob/main/bsp/vee/port/net/inc/LLNET_configuration.h>`_):

.. rli:: https://raw.githubusercontent.com/MicroEJ/nxp-vee-imxrt1170-evk/refs/heads/main/bsp/vee/port/net/inc/LLNET_configuration.h
   :language: c
   :lines: 92-108
   :linenos:
   :lineno-start: 92

In the previous declaration we call a custom LwIP compatible initialization that does the following:

- Initializes the hardware.
- Initializes the LwIP stack.
- Configure the network interface.
- Sends a DHCP request and assigns the address to the interface once the DHCP request is done.

This is suitable for most of the networks with a DHCP server.

In environments where DHCP is not available, the network stack must be configured to use a static IP address instead.
This involves manually assigning an IP address, subnet mask, gateway, and optionally DNS settings during the initialization phase.
Refer to the documentation of your IP stack for target specific static IP configuration steps.

.. Also provide example here?

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
