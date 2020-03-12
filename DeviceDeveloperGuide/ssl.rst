===
SSL
===


Principle
=========

SSL (Secure Sockets Layer) library provides APIs to create and establish
an encrypted connection between a server and a client. It implements the
standard SSL/TLS (Transport Layer Security) protocol that manages client
or server authentication and encrypted communication.


Functional Description
======================

The SSL/TLS process includes two sub-protocols :

-  Handshake protocol : consists that a server presents its digital
   certificate to the client to authenticate the server's identity. The
   authentication process uses public-key encryption to validate the
   digital certificate and confirm that a server is in fact the server
   it claims to be.

-  Record protocol : after the server authentication, the client and the
   server establish cipher settings to encrypt the information they
   exchange. This provides data confidentiality and integrity.


Dependencies
============

-  Network core module (see :ref:`network_core`).

-  ``LLNET_SSL_CONTEXT_impl.h``, ``LLNET_SSL_SOCKET_impl.h`` and
   ``LLNET_SSL_X509_CERT_impl.h`` implementations (see
   :ref:`LLNET_SSL-API-SECTION`).


Installation
============

SSL is an additional module. In the platform configuration file, check
``SSL`` to install the module.


Use
===

A classpath variable named ``SSL-2.0`` is available.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
