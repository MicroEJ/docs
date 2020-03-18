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


Installation
============

Network is an additional module. In the platform configuration file,
check :guilabel:`NET` to install this module. When checked, the properties file
``net`` > ``net.properties`` is required during platform creation to
configure the module. This configuration step is used to customize the
kind of TCP/IP native stack used and the Domain Name System (DNS)
implementation.

The properties file must / can contain the following properties:

-  ``stack`` [optional, default value is "custom"]: Defines the kind of
   TCP/IP interface used in the C project.

   -  ``custom``: Select this configuration to make a "from scratch"
      implementation glue between the C Network Core Engine and the C
      project TCP/IP interface.

   -  ``bsd``: Select this configuration to use a BSD-like library
      helper to implement the glue between the C Network Core Engine and
      the C project TCP/IP interface. This property requires that the C
      project provides a TCP/IP native stack with a Berkeley Sockets API
      and a ``select`` mechanism.

-  ``dns`` [optional, default value is "native"]: Defines the kind of
   Domain Name System implementation used.

   -  ``native``: Select this configuration to implement the glue
      between the C Network Core Engine DNS part and the C project
      TCP/IP interface.

   -  ``soft``: Select this configuration if you want a software
      implementation of the DNS part. Only the IPs list of the DNS
      server must be provided by the C Network Core Engine glue.


Use
===

A classpath variable named ``NET-1.1`` is available.

This library provides a set of options. Refer to the chapter
:ref:`workbenchLaunchOptions` which lists all available options.


..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
