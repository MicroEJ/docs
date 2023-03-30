.. _pack_wifi:

=====
Wi-Fi
=====

Overview
========

The Wi-Fi Foundation Library provides a way to manage and configure Wi-Fi access points.

Dependencies
============

- Network core module (see :ref:`network_core`).

- ``LLECOM_WIFI_impl.h`` implementation (see :ref:`LLECOM_WIFI-API-SECTION`).

Installation
============

The Wi-Fi :ref:`Pack <pack_overview>` module must be installed in your VEE Port.

In the Platform configuration project, (``-configuration`` suffix), add
the following dependency to the :ref:`module.ivy <mmm_module_description>` file:

::

	<dependency org="com.microej.pack.ecom-wifi" name="ecom-wifi-pack" rev="1.0.0" />

The Platform project must be rebuilt (:ref:`platform_build`).

Use
===

The `Wi-Fi API Module`_ must be added to the :ref:`module.ivy <mmm_module_description>` file of the 
Application project: 

::

	<dependency org="ej.api" name="ecom-wifi" rev="2.2.2"/>

.. _Wi-Fi API Module: https://repository.microej.com/modules/ej/api/ecom-wifi/

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
