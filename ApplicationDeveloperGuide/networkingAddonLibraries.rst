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
      -  - `Connectivity Example <https://github.com/MicroEJ/Example-IOT/tree/master/androidconnectivity>`_

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
         - `MQTT publish Example <https://github.com/MicroEJ/Example-IOT/tree/master/mqtt-publisher>`_  
         - `MQTT subscribe Example <https://github.com/MicroEJ/Example-IOT/tree/master/ssl-mqtt-subscriber>`_

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
         - `WebSocket client Example <https://github.com/MicroEJ/Example-IOT/tree/master/ssl-websocket>`_  

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

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.