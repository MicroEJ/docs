.. _pack_gnss:

====
GNSS
====


Principle
=========

The GNSS module defines a low-level GNSS framework for embedded
devices. It allows you to manage the underlying GNSS engine and retrieve data such as the longitude, latitude, velocity and time.


Functional Description
======================

The MicroEJ Application manages the GNSS engine using
GnssManager abstraction. The GNSS implementation made for each MicroEJ
VEE Port is responsible for surfacing the native GNSS specific
behavior.

GNSS Mock
=========

GNSS values on simulator can be controlled through an UI that can be activated and deactivated with the property : ``com.is2t.gnss.embedded.mock.ui``.

Dependencies
============

-  ``LLGNSS_impl.h`` implementations (see
   :ref:`LLGNSS-API-SECTION`).


Installation
============

GNSS is an additional module.
The GNSS :ref:`Pack <pack_overview>` module must be installed in your VEE Port:

.. code-block:: kotlin

   microejPack("com.microej.pack.gnss:gnss-pack:2.0.0")

Use
===

See :ref:`GNSS API <gnss_usage>` chapter in Application Developer Guide.

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
