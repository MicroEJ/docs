===
SSL
===


Principle
=========

SSL (Secure Sockets Layer) library provides APIs to create and establish
an encrypted connection between a server and a client. It implements the
standard SSL/TLS (Transport Layer Security) protocol that manages client
or server authentication and encrypted communication. Mutual authentication
is supported since `SSL API` 2.1.0`_.


Functional Description
======================

The SSL/TLS process includes two sub-protocols :

-  Handshake protocol: consists that a server presents its digital
   certificate to the client to authenticate the server's identity. The
   authentication process uses public-key encryption to validate the
   digital certificate and confirm that a server is in fact the server
   it claims to be.

-  Record protocol: after the server authentication, the client and the
   server establish cipher settings to encrypt the information they
   exchange. This provides data confidentiality and integrity.


Dependencies
============

-  Network core module (see :ref:`network_core`).

-  ``LLNET_SSL_CONTEXT_impl.h`` and ``LLNET_SSL_SOCKET_impl.h``
   implementations (see :ref:`LLNET_SSL-API-SECTION`).


Installation
============

The Net Pack bundles several libraries: Net, SSL & Security.

Refer to the chapter :ref:`pack_import` to integrate a specific version of the Net Pack:

.. code-block:: xml
   :emphasize-lines: 2

   <dependencies>
       <dependency org="com.microej.pack.net" name="net-pack" rev="11.0.2"/>
   </dependencies>

Then, using the VEE Port Editor (see :ref:`platform_module_configuration`), enable the SSL library (API, Impl & Mock):

.. figure:: images/net-ssl_modules.*
   :alt: Net Pack Modules

   Net Pack Modules

Use
===

The `SSL API`_ module must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ
Application project to use the SSL library.

::

  <dependency org="ej.api" name="ssl" rev="2.2.3"/>

.. _SSL API: https://repository.microej.com/modules/ej/api/ssl/

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
