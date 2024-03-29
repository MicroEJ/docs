.. _bluetooth_api:

Bluetooth API Library
=====================

Introduction
------------

The Bluetooth API Library provides APIs to use BLE (Bluetooth Low Energy) in an Application.

.. _bluetooth_api_usage:

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

BLE is very different from TCP/IP networking.
Like Wi-Fi, Bluetooth uses UHF radio waves to communicate over a short range, but it introduces an entirely unique protocol stack.
It is important to understand how BLE works to develop an efficient and reliable Bluetooth application.
This section explains the basics of BLE and how they are reified in the Bluetooth API.

Connection APIs
~~~~~~~~~~~~~~~

BLE introduces two roles of devices: the Central and Peripheral roles.
A Central device scans nearby Peripheral devices and initiates the connection, while a Peripheral device advertises (broadcasts) and listens for connection requests.
In this regard, a Central device can be thought of as a Wi-Fi Station while a Peripheral device can be thought of as a Wi-Fi Access Point.

The following sequence explains the typical connection flow between two devices:

- The Peripheral device starts advertising
- The Central device starts scanning
- The Central device initiates a connection with the Peripheral device

.. figure:: images/bluetooth_connection_procedure.png
   :alt: Connection Procedure
   :align: center
   :scale: 50%

   Connection Procedure

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
- If the I/O capabilities of the devices allow to create a connection with protection against MITM attacks, the Passkey Entry method is used:

  - The device with display capability displays a generated passkey on its user interface
  - The device with input capability reads the passkey from the user input and sends it to the device with display capability
  - The device with display capability checks that the passkey match
- Otherwise, the "Just Works" method is used and the pairing is complete. This method does not prevent from MITM attacks.

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
Services and attributes are all identified by a 16-bit UUID. If a service or attribute is standard, the relevant specification indicates its UUID.

.. figure:: images/bluetooth_service_structure.png
   :alt: Service Structure
   :align: center
   :scale: 50%

   Service Structure

A device can call the getter APIs of `BluetoothService`_, `BluetoothCharacteristic`_, `BluetoothDescriptor`_ and `BluetoothAttribute`_ to browse the content of a service.

BLE devices use characteristics to transfer data. There are 4 main procedures:

- The **Read** procedure allows the device which **discovered** the service to **request data**.
  The device sends a read request and the device which provides the service sends back a read response with the data.
- The **Write** procedure allows the device which **discovered** the service to **send data** and to require an acknowledgment.
  The device sends a write request with the data and the device which provides the service sends back a write response.
- The **Write Without Response** procedure allows the device which **discovered** the service to **send data** without expecting an acknowledgment.
  The device just sends a write request with the data.
- The **Notify** procedure allows the device which **provides** the service to **send data**.
  The device sends a notification with the data, and if it requires an acknowledgment, the device which discovered the service sends back an acknowledgment.
  It is a common practice to send notifications only to devices which have subscribed to the characteristic (a device can subscribe to a characteristic by sending a write request on its CCC descriptor).

.. figure:: images/bluetooth_data_transfer_procedures.png
   :alt: Data Transfer Procedures
   :align: center
   :scale: 50%

For the Read procedure, a device can call the `BluetoothConnection.sendReadRequest()`_ API to send a read request.
The `LocalServiceListener.onReadRequest()`_ hook is called when a device receives a read request.
It can call the `BluetoothConnection.sendReadResponse()`_ API to send a read response with the data.
The `RemoteServiceListener.onReadCompleted()`_ hook is called with the data when a device receives a read response.

For the Write Without Response and the Write procedures, a device can call the send `BluetoothConnection.sendWriteRequest()`_ API to send a write request with the data.
The `LocalServiceListener.onWriteRequest()`_ hook is called with the data when a device receives a write request.
It can call the `BluetoothConnection.sendWriteResponse()`_ API to send a write response (in case of the write procedure).
The `RemoteServiceListener.onWriteCompleted()`_ hook is called when a write request is sent (or when it receives a write response, in case of the write procedure).

For the Notify procedure, a device can call the send `BluetoothConnection.sendNotification()`_ API to send a notification with the data.
The `RemoteServiceListener.onNotificationReceived()`_ hook is called with the data when a device receives a notification.
The `LocalServiceListener.onNotificationSent()`_ hook is called when a notification is sent (or when it receives the acknowledgment, if one is required).

Classes Summary
~~~~~~~~~~~~~~~

Main classes:

- `BluetoothAdapter`_ (singleton): Performs operations not related to a specific device connection (scan, advertise, connect, provide GATT service)
- `BluetoothConnection`_: Performs operations related to a specific device connection (disconnect, pair, discover GATT services, send GATT requests)
- `BluetoothService`_: Represents a GATT service
- `ConnectionListener`_ and `DefaultConnectionListener`_: Callbacks for all events not related to a specific GATT service
- `LocalServiceListener`_ and `DefaultLocalServiceListener`_: Callbacks for events related to a specific provided GATT service
- `RemoteServiceListener`_ and `DefaultRemoteServiceListener`_: Callbacks for events related to a specific discovered GATT service

Stateless and immutable classes:

- `BluetoothAddress`_: Address (BD_ADDR) of a device
- `BluetoothScanFilter`_: Scan result filter used when starting a scan
- `BluetoothDataTypes`_: Data types enumeration used in advertisement payloads
- `BluetoothCharacteristic`_: Represents a GATT characteristic
- `BluetoothDescriptor`_: Represents a GATT descriptor
- `BluetoothAttribute`_: Abstract base class of BluetoothCharacteristic and BluetoothDescriptor
- `BluetoothUuid`_: UUID of a GATT service or GATT attribute
- `BluetoothProperties`_: Properties enumeration used in GATT characteristics
- `BluetoothPermissions`_: Permissions enumeration used when defining a GATT attribute
- `BluetoothServiceDefinition`_: Builder class used when adding a GATT service
- `BluetoothStatus`_: Status code enumeration used when reading/writing a GATT attribute

Use-Cases
---------

Achieving Maximum Throughput
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In some use-cases, such as when sending a large file to another device, the throughput must be as high as possible to decrease the transfer time.

Here are some guidelines to achieve the maximum throughput:

- Change the MTU to the maximum value (512 bytes) instead of the default value (23 bytes)

  - Once devices are connected, either device should send a MTU request with the maximum value
  - When the other device receives the MTU request, it should send a MTU response with the maximum value
  - Since there is no API for MTU exchange in the Bluetooth API Library, this step has to be performed in the native code
- Use a data transfer procedure which does not require an acknowledgment

  - If the service is provided by the device sending the data: use the Notify procedure without requesting an acknowledgment
  - If the service is discovered by the device sending the data: use the Write Without Response procedure
- Send the data chunks as fast as possible

  - Do not wait for the previous chunk to be delivered before sending the next chunk
  - If a chunk can not be delivered because the connection is congested, wait a bit and retry sending the chunk

Examples
--------

MicroEJ provides two examples which show how to use the Bluetooth API. There is one example of Central device and one example of Peripheral device.

These examples can be found on `GitHub <https://github.com/MicroEJ/Example-Foundation-Libraries>`_.
Please refer to their own README for more information on these examples.

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
.. _BluetoothConnection.sendWriteResponse(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/BluetoothConnection.html#sendWriteResponse-ej.bluetooth.BluetoothAttribute-byte-
.. _ConnectionListener.onConnected(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onConnected-ej.bluetooth.BluetoothConnection-
.. _ConnectionListener.onDiscoveryResult(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onDiscoveryResult-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothService-
.. _ConnectionListener.onPairRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onPairRequest-ej.bluetooth.BluetoothConnection-
.. _ConnectionListener.onPasskeyGenerated(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onPasskeyGenerated-ej.bluetooth.BluetoothConnection-int-
.. _ConnectionListener.onPasskeyRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onPasskeyRequest-ej.bluetooth.BluetoothConnection-
.. _ConnectionListener.onScanResult(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/ConnectionListener.html#onScanResult-ej.bluetooth.BluetoothAddress-byte:A-int-
.. _LocalServiceListener.onNotificationSent(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/LocalServiceListener.html#onNotificationSent-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothCharacteristic-boolean-
.. _LocalServiceListener.onReadRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/LocalServiceListener.html#onReadRequest-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothAttribute-
.. _LocalServiceListener.onWriteRequest(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/LocalServiceListener.html#onWriteRequest-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothAttribute-byte:A-
.. _RemoteServiceListener.onNotificationReceived(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/RemoteServiceListener.html#onNotificationReceived-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothCharacteristic-byte:A-
.. _RemoteServiceListener.onReadCompleted(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/RemoteServiceListener.html#onReadCompleted-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothAttribute-byte-byte:A-
.. _RemoteServiceListener.onWriteCompleted(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bluetooth/listeners/RemoteServiceListener.html#onWriteCompleted-ej.bluetooth.BluetoothConnection-ej.bluetooth.BluetoothAttribute-byte-

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
