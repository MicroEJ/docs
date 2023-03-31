.. _pack_bluetooth:

=========
Bluetooth
=========


Principle
=========

The Bluetooth module defines a low-level Bluetooth framework for embedded
devices. It allows you to manage abstract Bluetooth connections without
worrying about the native underlying Bluetooth kind.


Functional Description
======================

The MicroEJ Application manages Bluetooth elements using
Adapter/Connection/Service/Characteristic/Descriptor/etc abstraction. 
The Bluetooth implementation made for each MicroEJ
Platform is responsible for surfacing the native Bluetooth specific
behavior.


Overview
========

The Bluetooth Foundation Library provides a way to manage and configure Bluetooth module.

Dependencies
============

- ``LLBLUETOOTH_impl.h`` implementation (see :ref:`LLBLUETOOTH-API-SECTION`).

Installation
============

The Bluetooth :ref:`Pack <pack_overview>` module must be installed in your VEE Port.

In the Platform configuration project, (``-configuration`` suffix), add
the following dependency to the :ref:`module.ivy <mmm_module_description>` file:

::

	<dependency org="com.microej.pack.bluetooth" name="bluetooth-pack" rev="2.2.1" />

The Platform project must be rebuilt (:ref:`platform_build`).

Use
===

The `Bluetooth API Module`_ must be added to the :ref:`module.ivy <mmm_module_description>` file of the 
Application project: 

::

	<dependency org="ej.api" name="bluetooth" rev="2.1.1"/>

.. _Bluetooth API Module: https://repository.microej.com/modules/ej/api/bluetooth/

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.