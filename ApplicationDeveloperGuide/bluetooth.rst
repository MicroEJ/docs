.. _bluetooth_api:

Bluetooth API Library
=====================

Introduction
------------

The Bluetooth API Library provides APIs to use BLE (Bluetooth Low Energy) in an Application.

Usage
-----

The Bluetooth API Library is provided as a Foundation Library.

To use the `Bluetooth API Library <https://repository.microej.com/modules/ej/api/bluetooth/>`_, add the following to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.api:bluetooth:2.2.1")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.api" name="bluetooth" rev="2.2.1"/>

Building or running an Application which uses the Bluetooth API Library requires the VEE Port to provide the :ref:`Bluetooth Pack <pack_bluetooth>`.

Basic Knowledge and APIs
------------------------

.. _BluetoothAdapter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAdapter.html
.. _BluetoothAddress: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAddress.html
.. _BluetoothAttribute: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAttribute.html
.. _BluetoothCharacteristic: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothCharacteristic.html
.. _BluetoothConnection: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothConnection.html
.. _BluetoothDataTypes: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothDataTypes.html
.. _BluetoothDescriptor: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothDescriptor.html
.. _BluetoothPermissions: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothPermissions.html
.. _BluetoothProperties: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothProperties.html
.. _BluetoothService: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothService.html
.. _BluetoothServiceDefinition: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothServiceDefinition.html
.. _BluetoothScanFilter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothScanFilter.html
.. _BluetoothStatus: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothStatus.html
.. _BluetoothUuid: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothUuid.html
.. _ConnectionListener: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html
.. _LocalServiceListener: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/LocalServiceListener.html
.. _RemoteServiceListener: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/RemoteServiceListener.html
.. _DefaultConnectionListener: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/impl/DefaultConnectionListener.html
.. _DefaultLocalServiceListener: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/impl/DefaultLocalServiceListener.html
.. _DefaultRemoteServiceListener: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/impl/DefaultRemoteServiceListener.html

.. _BluetoothAdapter.addService(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAdapter.html#addService-ej.bluetooth.BluetoothServiceDefinition-
.. _BluetoothAdapter.connect(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAdapter.html#connect-ej.bluetooth.BluetoothAddress-
.. _BluetoothAdapter.enable(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAdapter.html#enable--
.. _BluetoothAdapter.setConnectionListener(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAdapter.html#setConnectionListener-ej.bluetooth.listeners.ConnectionListener-
.. _BluetoothAdapter.startAdvertising(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAdapter.html#startAdvertising-byte:A-
.. _BluetoothAdapter.startScanning(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAdapter.html#startScanning-ej.bluetooth.BluetoothScanFilter-
.. _BluetoothAdapter.stopAdvertising(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAdapter.html#stopAdvertising--
.. _BluetoothAdapter.stopScanning(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothAdapter.html#startScanning-ej.bluetooth.BluetoothScanFilter-
.. _BluetoothConnection.discoverServices(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothConnection.html#discoverServices--
.. _BluetoothConnection.sendNotification(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothConnection.html#sendNotification-ej.bluetooth.BluetoothCharacteristic-byte:A-boolean-
.. _BluetoothConnection.sendPairRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothConnection.html#sendPairRequest--
.. _BluetoothConnection.sendPairResponse(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothConnection.html#sendPairResponse-boolean-
.. _BluetoothConnection.sendPasskeyResponse(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothConnection.html#sendPasskeyResponse-boolean-int-
.. _BluetoothConnection.sendReadRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothConnection.html#sendReadRequest-ej.bluetooth.BluetoothAttribute-
.. _BluetoothConnection.sendReadResponse(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothConnection.html#sendReadResponse-ej.bluetooth.BluetoothAttribute-byte-byte:A-
.. _BluetoothConnection.sendWriteRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothConnection.html#sendWriteRequest-ej.bluetooth.BluetoothAttribute-byte:A-
.. _ConnectionListener.onConnected(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onConnected-ej.bluetooth.BluetoothConnection-
.. _ConnectionListener.onDiscoveryResult(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onDiscoveryResult-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothService-
.. _ConnectionListener.onPairRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onPairRequest-ej.bluetooth.BluetoothConnection-
.. _ConnectionListener.onPasskeyGenerated(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onPasskeyGenerated-ej.bluetooth.BluetoothConnection-int-
.. _ConnectionListener.onPasskeyRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onPasskeyRequest-ej.bluetooth.BluetoothConnection-
.. _ConnectionListener.onScanResult(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onScanResult-ej.bluetooth.BluetoothAddress-byte:A-int-
.. _LocalServiceListener.onReadRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/LocalServiceListener.html#onReadRequest-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothAttribute-
.. _LocalServiceListener.onWriteRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/LocalServiceListener.html#onWriteRequest-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothAttribute-byte:A-
.. _RemoteServiceListener.onNotificationReceived(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/RemoteServiceListener.html#onNotificationReceived-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothCharacteristic-byte:A-
.. _RemoteServiceListener.onReadCompleted(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/RemoteServiceListener.html#onReadCompleted-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothAttribute-byte-byte:A-

BLE is very different from TCP/IP networking.
Like Wi-Fi, Bluetooth uses UHF radio waves to communicate over a short range, but it introduces an entirely unique protocol stack.
It is important to understand how BLE works to develop an efficient and reliable Bluetooth application.
This section explains the basics of BLE and how they are reified in the Bluetooth API.

Connection APIs
~~~~~~~~~~~~~~~

BLE introduces two roles of devices: the Central and Peripheral roles.
A Central device scans nearby Peripheral devices and initiates the connection, while a Peripheral device advertises (broadcasts) and listens for connection requests.
In this regard, a Peripheral device can be thought of as a Wi-Fi Access Point while a Peripheral device can be thought of as a Wi-Fi Station.

The following sequence explains the typical connection flow between two devices:

- The Peripheral device starts advertising
- The Central device starts scanning
- The Central device initiates a connection with the Peripheral device

A device must always enable its Bluetooth adapter using the `BluetoothAdapter.enable()`_ API before calling any other Bluetooth API.
A Peripheral device can call the `BluetoothAdapter.startAdvertising()`_ API to start advertising.
A Central device can call the `BluetoothAdapter.startScanning()`_ API to start scanning and the `BluetoothAdapter.connect()`_ API to initiate a connection.
The `BluetoothAdapter.stopAdvertising()`_ and `BluetoothAdapter.stopScanning()`_ APIs can be called to stop advertising or scanning,
however note that these operations are stopped automatically when a connection is established.
A device must set the connection listener of the adapter in order to be notified of asynchronous connection events, by calling the `BluetoothAdapter.setConnectionListener()`_ API.
The `ConnectionListener.onScanResult()`_ hook is called on every scan result and the `ConnectionListener.onConnected()`_ hook is called when a connection is established.

Pairing APIs
~~~~~~~~~~~~

Pairing is an optional procedure which allows to authenticate the connection by requesting a proof of possession (via a PIN code for example).
The pairing procedure can be started at any time during a connection. It is often performed upon connecting or when first accessing a secure GATT service.

Here are the steps of the pairing procedure:

- Either device sends a pairing request or security request to the other device
- Both devices share their I/O capabilities
- If the I/O capabilities of the devices allow to create a connection with MITM , the Passkey Entry method is used:

  - The device with display capability displays a generated passkey on its user interface
  - The device with input capability reads the passkey from the user input and sends it to the device with display capability
  - The device with display capability checks that the passkey match
- Otherwise, the Just Works method is used and the pairing is complete. This method does not prevent MITM attacks.

A device can call the `BluetoothConnection.sendPairRequest()`_ API to initiate pairing.
The `ConnectionListener.onPairRequest()`_ hook is called when the device receives a pairing request.
It can call the `BluetoothConnection.sendPairResponse()`_ API to accept or deny the pairing.
The `ConnectionListener.onPasskeyGenerated()`_ hook is called when the device with display capability has generated a passkey to display.
The `ConnectionListener.onPasskeyRequest()`_ hook is called when the device with input capability should provide the passkey.
It can call the `BluetoothConnection.sendPasskeyResponse()`_ API to provide it.

GATT Services APIs
~~~~~~~~~~~~~~~~~~

With BLE, devices exchange data through GATT services.
BLE specifies standard services (such as the Current Time Service or the Battery Service) which allow devices to be interoperable, but BLE also allows to define custom services.
Either device (Central or Peripheral or both) can provide services to the other.
A device must discover the services provided by the other device before it can use them.

A device can define and provide services using the `BluetoothServiceDefinition`_ builder class and the `BluetoothAdapter.addService()`_ API.
Once a connection is established, either device can discover the services of the other device by calling the `BluetoothConnection.discoverServices()`_ API.
The `ConnectionListener.onDiscoveryResult()`_ hook is called for each service provided by the other device.

A service provides characteristics, which can be thought of as data channels.
A characteristic has property flags, which indicate to the other devices how the characteristic can be used (whether it can be written, whether it provides notifications, etc.).
A characteristic may have descriptors, which allow to describe or configure the characteristic in a specific way.
Every attribute (characteristic or descriptor) has permission flags, which control its access (read-only, read/write, requires authentication, etc.).
Services and attributes are all identified by 16-bit UUID. If a service or attribute is standard, the relevant specification indicates its UUID.

A device can call the getter APIs of `BluetoothService`_, `BluetoothCharacteristic`_, `BluetoothDescriptor`_ and `BluetoothAttribute`_ to browse the content of a service.

BLE devices use characteristics to transfer data. There are 3 main procedures:

- A **read request** on a characteristic of a **discovered service** allows to **request data** from the device it belongs to.
  The device which discovered the service sends a read request and the device which owns the service sends back a read response with the data.
- A **write request** on a characteristic of a **discovered service** allows to **send data** to the device it belongs to.
  The device which discovered the service sends a write request with the data and the device which owns the service sends back a read response.
- A **notification** on a characteristic of a **provided service** allows to **send data** to any connected device.
  The device which owns the service sends a notification with the data to the desired device.
  BLE provides a built-in way to subcribe to the notifications of a characteristic of a discovered service, by sending a write request on its CCC descriptor.

For the read request procedure, a device can call the send `BluetoothConnection.sendReadRequest()`_ API to send a read request.
The `LocalServiceListener.onReadRequest()`_ hook is called when a device receives a read request.
It can call the `BluetoothConnection.sendReadResponse()`_ API send a read response with the data.
The `RemoteServiceListener.onReadCompleted()`_ hook is called with the data when a device receives a read response.

For the write request procedure, a device can call the send `BluetoothConnection.sendWriteRequest()`_ API to send a write request with the data.
The `LocalServiceListener.onWriteRequest()`_ hook is called with the data when a device receives a write request.

For the notification procedure, a device can call the send `BluetoothConnection.sendNotification()`_ API to send a notification with the data.
The `RemoteServiceListener.onNotificationReceived()`_ hook is called with the data when a device receives a notification.

Classes Summary
~~~~~~~~~~~~~~~

Main classes:

- `BluetoothAdapter`_ (singleton): Performs operations not related to a specific device connection (scan, advertise, connect, manage local GATT services)
- `BluetoothConnection`_: Performs operations related to a specific device connection (disconnect, pair, discover remote GATT services, send GATT requests)
- `BluetoothService`_: Represents a local or remote GATT service
- `ConnectionListener`_ and `DefaultConnectionListener`_: Callbacks for all events not related to a specific GATT service
- `LocalServiceListener`_ and `DefaultLocalServiceListener`_: Callbacks for events related to a specific local GATT service
- `RemoteServiceListener`_ and `DefaultRemoteServiceListener`_: Callbacks for events related to a specific remote GATT service

Stateless and immutable classes:

- `BluetoothAddress`_: Address (BD_ADDR) of a device
- `BluetoothScanFilter`_: Scan result filter used when starting a scan
- `BluetoothDataTypes`_: Data types enumeration used in advertisement payloads
- `BluetoothCharacteristic`_: Represents a local or remote GATT characteristic
- `BluetoothDescriptor`_: Represents a local or remote GATT descriptor
- `BluetoothAttribute`_: Abstract base class of BluetoothCharacteristic and BluetoothDescriptor
- `BluetoothUuid`_: UUID of a GATT service or GATT attribute
- `BluetoothProperties`_: Properties enumeration used in GATT characteristics
- `BluetoothPermissions`_: Permissions enumeration used when adding a local GATT attribute
- `BluetoothServiceDefinition`_: GATT service model used when adding a local GATT service
- `BluetoothStatus`_: Status code enumeration used when reading/writing a GATT attribute

Bluetooth Utility Library
-------------------------

The Bluetooth Utility Library provides utility methods which can be useful when developing a Bluetooth Application.

Usage
~~~~~

The Bluetooth Utility Library is provided as an Add-On Library.

To use the `Bluetooth Utility Library <https://repository.microej.com/modules/ej/library/iot/bluetooth-util/>`_, add the following to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.library.iot:bluetooth-util:1.1.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.library.iot" name="bluetooth-util" rev="1.1.0"/>

Since this library is built on top of the Bluetooth API Library, it inherits its requirements.

Classes Summary
~~~~~~~~~~~~~~~

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
