.. _security:

========
Security
========

Principle
=========

The Security Foundation Library provides standard Java API (part of the Java Cryptography Architecture) for cryptographic operations:
cipher, digest, MAC, signature, secure random & key/certificate management.
It relies on a native crypto engine (such as Mbed TLS, OpenSSL or wolfSSL).

Dependencies
============

- The ``LLSEC_*.h`` implementations (see :ref:`LLSECURITY-API-SECTION`).

.. _security_installation:

Installation
============

The Net Pack bundles several libraries: Net, SSL & Security.

Refer to the chapter :ref:`pack_import` to integrate a specific version of the Net Pack:

.. code-block:: xml
   :emphasize-lines: 2

   <dependencies>
       <dependency org="com.microej.pack.net" name="net-pack" rev="11.0.2"/>
   </dependencies>

Then, using the VEE Port Editor (see :ref:`platform_module_configuration`), enable the Security library (API, Impl & Mock):

.. figure:: images/net-ssl_modules.*
   :alt: Net Pack Modules

   Net Pack Modules

Use
===

The `Security API`_ module must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ
Application project to use the Security library.

::

  <dependency org="ej.api" name="security" rev="1.6.0"/>

.. _Security API: https://repository.microej.com/modules/ej/api/security/

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
