.. _pack_metrology:

=========
Metrology
=========

Principle
=========

The Metrology Foundation Library defines an interface to retrieve underlying metrology data.

Functional Description
======================

A typical Application using Metrology will register a data listener, receive new data notification, and finally perform data processing.

The Metrology integration in a VEE port relies on a native metrology data source to implement all of the above functionalities.

Dependencies
============

- ``LLMETROLOGY_impl.h`` implementation (see :ref:`LLMETROLOGY-API-SECTION`).

Installation
============

Metrology is an additional module. 
To enable it, the Metrology :ref:`Pack <pack_overview>` must be installed in your VEE Port:

.. code-block:: kotlin

   api("ej.api:metrology:3.2.0")

Use
===

See :ref:`Metrology API <metrology_api_usage>` chapter in Application Developer Guide.

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
