.. _pack_bluetooth:

=========
Bluetooth
=========

Principle
=========

The Bluetooth Foundation Library defines a low-level Bluetooth framework for embedded
devices. It allows you to manage abstract Bluetooth connections without
worrying about the native underlying Bluetooth kind.

Functional Description
======================

The MicroEJ Application manages Bluetooth elements using
Adapter/Connection/Service/Characteristic/Descriptor/etc abstraction. 
The Bluetooth implementation made for each MicroEJ
Platform is responsible for surfacing the native Bluetooth specific
behavior.

Dependencies
============

.. _Espressif ESP32-S3 VEE Port: https://github.com/MicroEJ/VEEPort-Espressif-ESP32-S3-DevKitC-1/blob/master/ESP32-S3-DevKitC1-Xtensa-FreeRTOS-bsp/projects/microej/bluetooth/src/LLBLUETOOTH_impl.c

- ``LLBLUETOOTH_impl.h`` implementation (see :ref:`LLBLUETOOTH-API-SECTION`).

  - A sample implementation based on the Bluedroid stack can be found in the `Espressif ESP32-S3 VEE Port`_.

Installation
============

Bluetooth is an additional module. 
To enable it, the Bluetooth :ref:`Pack <pack_overview>` module must be installed in your VEE Port:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         microejPack("com.microej.pack.bluetooth:bluetooth-pack:2.4.1")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.pack.bluetooth" name="bluetooth-pack" rev="2.4.1" />

Use
===

See :ref:`Bluetooth API <bluetooth_api_usage>` chapter in Application Developer Guide.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.