.. _networkingAddonLibraries:

Add-On Libraries
================

IoT Libraries
~~~~~~~~~~~~~

.. list-table::
   :header-rows: 1
   :widths: 10 30 10 20 20

   *  -  Name
      -  Description
      -  Module Link
      -  API Link
      -  Use

   *  -  ``Android Connectivity`` 
      -  Network connection state and notifications.
      -  `android-connectivity <https://repository.microej.com/modules/ej/library/iot/android-connectivity/>`_
      -  `ConnectivityManager class <https://repository.microej.com/javadoc/microej_5.x/apis/android/net/ConnectivityManager.html>`_
      -  - `Connectivity Example <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/androidconnectivity>`_

   *  -  ``HTTP Client``
      -  OpenJDK HTTP client.
      -  `httpclient <https://repository.microej.com/modules/ej/library/eclasspath/httpclient/>`_, `httpsclient <https://repository.microej.com/modules/ej/library/eclasspath/httpsclient/>`_
      -  `HttpURLConnection class <https://repository.microej.com/javadoc/microej_5.x/apis/java/net/HttpURLConnection.html>`_
      -  - `HTTP client README <https://repository.microej.com/modules/ej/library/eclasspath/httpclient/1.3.0/README-1.3.0.md>`_
   
   *  -  ``Web Server (HOKA)``
      -  Tiny footprint yet extensible web server. 
      -  `HOKA <https://repository.microej.com/modules/ej/library/iot/hoka/>`_
      -  `HttpServer class <https://repository.microej.com/javadoc/microej_5.x/apis/ej/hoka/http/HttpServer.html>`_
      -  - :ref:`HOKA User Manual<hokaWebserverUserGuide>`
         - `HOKA Examples <https://github.com/MicroEJ/Example-Hoka>`_   

   *  -  ``MQTT Client (MicroPaho)``
      -  Tiny footprint MQTT 3.1.1 client based on Eclipse Paho Java APIs.
      -  `micropaho <https://repository.microej.com/modules/ej/library/iot/micropaho/1.0.0/>`_
      -  `MqttClient class <https://repository.microej.com/javadoc/microej_5.x/apis/org/eclipse/paho/client/mqttv3/MqttClient.html>`_
      -  - `MicroPaho README <https://repository.microej.com/modules/ej/library/iot/micropaho/1.0.0/README-1.0.0.md>`_
         - `MQTT publish Example <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/mqtt.publisher>`_  
         - `MQTT subscribe Example <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/ssl.mqtt.subscriber>`_

   *  -  ``REST Client``
      -  REpresentational State Tranfer (REST) client.
      -  `restclient <https://repository.microej.com/modules/ej/library/iot/restclient/>`_
      -  `Resty class <https://repository.microej.com/javadoc/microej_5.x/apis/ej/rest/web/Resty.html>`_
      -  - `REST client README <https://repository.microej.com/modules/ej/library/iot/restclient/1.1.0/README-1.1.0.md>`_

   *  -  ``SNTP Client``
      -  Simple Network Time Protocol (SNTP) client, used to retrieve the current time from an NTP server.
      -  `sntpclient <https://repository.microej.com/modules/ej/library/iot/sntpclient/>`_
      -  `SntpClient class <https://repository.microej.com/javadoc/microej_5.x/apis/android/net/SntpClient.html>`_
      -  - `SNTP client README <https://repository.microej.com/modules/ej/library/iot/sntpclient/1.3.0/README-1.3.0.md>`_

   *  -  ``WebSocket Client``
      -  WebSocket client (RFC 6455).
      -  `websocket <https://repository.microej.com/modules/ej/library/iot/websocket/>`_, `websocket-secure <https://repository.microej.com/modules/ej/library/iot/websocket-secure/>`_
      -  `WebSocket class <https://repository.microej.com/javadoc/microej_5.x/apis/index.html?ej/websocket/WebSocket.html>`_
      -  - `WebSocket client README <https://repository.microej.com/modules/ej/library/iot/websocket/2.0.0/README-2.0.0.md>`_
         - `WebSocket client Example <https://github.com/MicroEJ/Example-Sandboxed-IOT/tree/master/ssl.websocket>`_  


Data Serialization Libraries
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. list-table::
   :header-rows: 1
   :widths: 10 30 10 20 20

   *  -  Name
      -  Description
      -  Module Link
      -  API Link
      -  Use

   *  -  ``CBOR``
      -  Concise Binary Object Representation (CBOR) encoder and decoder (RFC 7049).
      -  `cbor <https://repository.microej.com/modules/ej/library/iot/cbor/>`_
      -  - `CborEncoder class <https://repository.microej.com/javadoc/microej_5.x/apis/ej/cbor/CborEncoder.html>`_
         - `CborDecoder class <https://repository.microej.com/javadoc/microej_5.x/apis/ej/cbor/CborDecoder.html>`_
      -  - :ref:`CBOR Tutorial <tutorial_cbor>`

   *  -  ``JSON``
      -  JavaScript Object Notation (JSON) encoder and decoder.
      -  `json <https://repository.microej.com/modules/ej/library/iot/json/>`_
      -  - `JSONObject class <https://repository.microej.com/javadoc/microej_5.x/apis/org/json/me/JSONObject.html>`_ (decoder)
         - `JSONWriter class <https://repository.microej.com/javadoc/microej_5.x/apis/org/json/me/JSONWriter.html>`_ (encoder)
      -  - `README <https://repository.microej.com/modules/ej/library/iot/json/1.0.0/README-1.0.0.md>`_
         - :ref:`JSON Tutorial <tutorial_json>`

   *  -  ``Protocol Buffers``
      -  Google Protocol Buffers 3 encoder and decoder, supporting files compiled by ``protoc`` with lite plugin.
      -  `protobuf3 <https://repository.microej.com/modules/com/google/protobuf3/>`_
      -  - `CodedInputStream class <https://repository.microej.com/javadoc/microej_5.x/apis/com/google/protobuf/CodedInputStream.html>`_ (decoder)
         - `CodedOutputStream class <https://repository.microej.com/javadoc/microej_5.x/apis/com/google/protobuf/CodedOutputStream.html>`_ (encoder)
      -  - `Protobuf3 Example <https://github.com/MicroEJ/Demo-Protobuf3>`_

   *  -  ``XML``
      -  eXtensible Markup Language encoder and decoder (`kXML 3 <http://kxml.sourceforge.net/about.shtml>`_).
      -  `kxml2 <https://repository.microej.com/modules/org/kxml2/kxml2/>`_
      -  - `XmlPullParser class <https://repository.microej.com/javadoc/microej_5.x/apis/org/xmlpull/v1/XmlPullParser.html>`_ (decoder)
         - `XmlSerializer class <https://repository.microej.com/javadoc/microej_5.x/apis/org/xmlpull/v1/XmlSerializer.html>`_ (encoder)
      - - :ref:`XML Tutorial <tutorial_xml>`


Cloud Agent Libraries
~~~~~~~~~~~~~~~~~~~~~

.. list-table::
   :header-rows: 1
   :widths: 10 40 15 40

   *  -  Name
      -  Description
      -  Module Link
      -  Use

   *  -  ``AWS IoT Core``
      -  AWS IoT Core client, providing publish/subscribe functionalities.
      -  `aws-iot <https://repository.microej.com/modules/ej/library/iot/aws-iot/>`_
      -  - `AWS IoT Core README <https://repository.microej.com/modules/ej/library/iot/aws-iot/2.0.0/README-2.0.0.md>`_
         - `AWS IoT Core Example <https://github.com/MicroEJ/AWS>`_

   *  -  ``Google Cloud Platform Iot Core``
      -  Google Cloud Platform Iot Core client.
      -  `gcp-iotcore <https://forge.microej.com/artifactory/microej-developer-repository-release/googlecloud/iotcore/>`_
      -  - `Google Cloud Platform Getting Started <https://developer.microej.com/features/iot-connectivity/get-started-google-cloud-iot-core-connectivity/>`_
..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.