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

Wi-Fi is an additional module. 
To enable it, the Wi-Fi :ref:`Pack <pack_overview>` module must be installed in your VEE Port:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         microejPack("com.microej.pack.ecom-wifi:ecom-wifi-pack:1.0.0")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.pack.ecom-wifi" name="ecom-wifi-pack" rev="1.0.0" />

      Then the VEE Port project must be rebuilt (:ref:`platform_build`).

Use
===

The `Wi-Fi API Module`_ must be added to the Application project build file to use the NET library:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.api:ecom-wifi:2.2.2")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="ej.api" name="ecom-wifi" rev="2.2.2"/>


.. _Wi-Fi API Module: https://repository.microej.com/modules/ej/api/ecom-wifi/

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
