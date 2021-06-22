.. _networking:

Networking
==========

This section presents network's libraries.

The following schema shows the overall architecture and modules:

.. figure:: images/networking_overview.png
   :alt: Network Libraries Overview
   :width: 600px
   :align: center

   Network Libraries Overview

Foundation Libraries
---------------------

.. list-table::
   :header-rows: 1
   :widths: 10 200 10 70

   *  -  Name
      -  Description
      -  Module Link
      -  Use
   
   *  -  ``Bluetooth``
      -  Provides interfaces and classes stubs of the Bluetooth API.
      -  `bluetooth <https://repository.microej.com/modules/ej/api/bluetooth/>`_
      -  `utility library <https://repository.microej.com/modules/ej/library/iot/bluetooth-util/>`_

   *  -  ``ECOM-Network``
      -  Provides classes to manage the network interfaces and their IP configurations.
      -  `ecom-network <https://repository.microej.com/modules/ej/api/ecom-network/>`_
      - 

   *  -  ``ECOM-WIFI``
      -  Provides classes to manage Wi-Fi.
      -  `ecom-wifi <https://repository.microej.com/modules/ej/api/ecom-wifi/>`_
      -  -  `wifi-util <https://repository.microej.com/modules/ej/library/iot/wifi-util/>`_
         -  `Example Wi-fi setup <https://github.com/MicroEJ/Example-Wi-Fi-Setup>`_

   *  -  ``NET``
      -  Contains classes and interfaces stubs of NET API (ESR024).
      -  `net <https://repository.microej.com/modules/ej/api/net/>`_
      -  -  `MicroEJ/Foundation/Net <https://github.com/MicroEJ/Example-Standalone-Foundation-Libraries/tree/master/com.microej.example.foundation.net.helloworld>`_
         -  `net-util <https://repository.microej.com/modules/ej/library/iot/net-util/>`_

   *  -  ``Security``
      -  MicroEJ Java library API: security.
      -  `security <https://repository.microej.com/modules/ej/api/security/>`_
      - 

   *  -  ``SSL``
      -  Contains classes and interfaces stubs of SSL API (ESR029).
      -  `ssl <https://repository.microej.com/modules/ej/api/ssl/>`_
      -  -  `ssl-util <https://repository.microej.com/modules/ej/library/iot/ssl-util/>`_
         -  `SSL Mutual <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/com.microej.example.iot.ssl.mutual>`_
         -  `SSL Mutual Server <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/com.microej.example.iot.ssl.mutual.server>`_

IoT Libraries
--------------

.. list-table::
   :header-rows: 1
   :widths: 10 200 10 100

   *  -  Name
      -  Description
      -  Module Link
      -  Use

   *  -  ``Android Connectivity`` 
      -  Contains android connectivity utilities.
      -  `android-connectivity <https://repository.microej.com/modules/ej/library/iot/android-connectivity/>`_
      -  `Example-Sandboxed-IOT/android-connectivity <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/com.microej.example.iot.androidconnectivity>`_

   *  -  ``HTTP Client``
      -  Contains the implementation of an HTTP client.
      -  `httpclient <https://repository.microej.com/modules/ej/library/eclasspath/httpclient/>`_, `httpsclient <https://repository.microej.com/modules/ej/library/eclasspath/httpsclient/>`_
      -  See REST Client
   
   *  -  ``HTTP Server (Hoka)``
      -  Provides a tiny footprint yet extensible web server. Check the documentation of this library by following this link:
         `Hoka/user-manual.rst <https://github.com/MicroEJ/LibraryJava-hoka/blob/master/hoka/user-manual.rst>`_
      -  `hoka <https://repository.microej.com/modules/ej/library/iot/hoka/>`_
      -  `Example-Hoka <https://github.com/MicroEJ/Example-Hoka>`_   

   *  -  ``MQTT Client``
      -  - This is a fork of Paho: `eclispe/paho/clients/java <https://eclipse.org/paho/clients/java/>`_ from commit 496f94a58a41557ba2401d4ba94bc099a75ba8ef (just after version 1.0.2).
         - Implements MQTT 3.1.1
      -  `mqtt <https://repository.microej.com/modules/org/eclipse/paho/mqttv3-microej/>`_, `mqtt-ssl <https://repository.microej.com/modules/org/eclipse/paho/mqttv3-ssl-microej/>`_
      -  -  `Example-Sandboxed-IOT/mqtt.publisher <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/com.microej.example.iot.mqtt.publisher>`_  
         -  `Example-Sandboxed-IOT/mqtt.subscriber <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/com.microej.example.iot.ssl.mqtt.subscriber>`_


   *  -  ``REST Client``
      -  It is a tiny RESTful services client. Check out README.md
         to learn more: `RestClient/README.md <https://repository.microej.com/modules/ej/library/iot/restclient/1.1.0/README-1.1.0.md>`_
      -  `restclient <https://repository.microej.com/modules/ej/library/iot/restclient/>`_
      -  `Example-Sandboxed-IOT/rest <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/com.microej.example.iot.ssl.rest>`_

   *  -  ``REST Server``
      -  A simple REST server implementation over Hoka library.
      -  `restserver <https://repository.microej.com/modules/ej/library/iot/restserver/>`_
      -  `Example-Sandboxed-IOT/dynamic-restserver <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/com.microej.example.iot.dynamic-restserver>`_

   *  -  ``SNTP Client``
      -  Implements an SNTP client. It can be used to retrieve the current time from an NTP server. Check out README.md
         to learn more: `SNTPClient/README.md <https://repository.microej.com/modules/ej/library/iot/sntpclient/1.3.0/README-1.3.0.md>`_
      -  `sntpclient <https://repository.microej.com/modules/ej/library/iot/sntpclient/>`_
      -

   *  -  ``WebSocket Client``
      -  Implementation for the client side of the WebSocket protocol as described in RFC 6455. Check out README.md
         to learn more: `WebSocket/README.md <https://repository.microej.com/modules/ej/library/iot/websocket/2.0.0/README-2.0.0.md>`_
      -  `websocket <https://repository.microej.com/modules/ej/library/iot/websocket/>`_, `websocket-secure <https://repository.microej.com/modules/ej/library/iot/websocket-secure/>`_
      -  `Example-Sandboxed-IOT/websocket <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/com.microej.example.iot.ssl.websocket>`_  


Data Serialization Libraries
-----------------------------

.. list-table::
   :header-rows: 1
   :widths: 10 200 10 70

   *  -  Name
      -  Description
      -  Module Link
      -  Use

   *  -  ``CBOR``
      -  Library for encoding/decoding CBOR format.
      -  `cbor <https://repository.microej.com/modules/ej/library/iot/cbor/>`_
      -  `Tutorials/CBOR <https://docs.microej.com/en/latest/Tutorials/tutorialExploreDataSerializationFormats.html#cbor>`_

   *  -  ``JSON``
      -  Provides APIs for writing to and reading from JSON streams. Check out README.md
         to learn more: `JSON/README.md <https://repository.microej.com/modules/ej/library/iot/json/1.0.0/README-1.0.0.md>`_
      -  `json <https://repository.microej.com/modules/ej/library/iot/json/>`_
      -  `Tutorials/JSON <https://docs.microej.com/en/latest/Tutorials/tutorialExploreDataSerializationFormats.html#json>`_

   *  -  ``Protocol Buffer``
      -  Contains the lite part of Google Protocol Buffer library for java.
         It supports java files compiled by protoc with lite plugin.
      -  `protobuf3 <https://repository.microej.com/modules/com/google/protobuf3/>`_
      -  `Demo-Protobuf3 <https://github.com/MicroEJ/Demo-Protobuf3>`_


Cloud Agent Libraries
----------------------

.. list-table::
   :header-rows: 1
   :widths: 5 200 10 70

   *  -  Name
      -  Description
      -  Module Link
      -  Use

   *  -  ``AWS``
      -  Enables MicroEJ developers to access the AWS IoT platform, providing publish/subscribe functionalities. Check out README.md
         to learn more: `AWS/README.md <https://repository.microej.com/modules/ej/library/iot/aws/aws-iot/1.2.0/README-1.2.0.md>`_
      -  `aws <https://repository.microej.com/modules/ej/library/iot/aws/aws-iot/>`_
      -  `AWS <https://github.com/MicroEJ/AWS>`_

   *  -  ``Google Cloud Platform Iot Core``
      -  Allows to connect to Google Cloud Platform Iot Core services.
      -  `gcp-iotcore <https://repository.microej.com/modules/googlecloud/iotcore/>`_
      - 

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.
