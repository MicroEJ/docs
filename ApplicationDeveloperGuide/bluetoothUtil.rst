.. _bluetooth_util:

Bluetooth Utility Library
=========================

Introduction
------------

The Bluetooth Utility Library provides utility methods which can be useful when developing a Bluetooth Application. It depends on the :ref:`bluetooth_api`.

Usage
-----

The Bluetooth Utility Library is provided as an Add-On Library.

To use the `Bluetooth Utility Library <https://repository.microej.com/modules/ej/library/iot/bluetooth-util/>`_, add the following to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.library.iot:bluetooth-util:1.1.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.library.iot" name="bluetooth-util" rev="1.1.0"/>

Since this library is built on top of the :ref:`bluetooth_api`, it inherits its requirements.

Classes Summary
---------------

.. _AdvertisementData: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/util/AdvertisementData.html
.. _AdvertisementFlags: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/util/AdvertisementFlags.html
.. _AttributeNotFoundException: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/util/AttributeNotFoundException.html
.. _DescriptorHelper: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/util/DescriptorHelper.html
.. _ServiceHelper: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/util/ServiceHelper.html

Main classes:

- `AdvertisementData`_: Parses or builds an advertisement payload
- `DescriptorHelper`_: Constants and utility methods related to GATT descriptors
- `ServiceHelper`_: Utility methods related to GATT services

Stateless and immutable classes:

- `AdvertisementFlags`_: Flags enumeration used in advertisement payloads
- `AttributeNotFoundException`_: Exception thrown by `ServiceHelper`_ when a GATT attribute is not found

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
