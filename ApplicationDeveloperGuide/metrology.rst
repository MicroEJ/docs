.. _metrology_api:

Metrology
=========

Introduction
------------

The Metrology Library provides APIs to retrieve metrology and metrology related data.

.. _metrology_api_usage:

Usage
-----

The Metrology Library is provided as a Foundation Library.

To use the `Metrology Library <https://repository.microej.com/modules/ej/api/metrology/>`_, add the following line to the project build file:

.. code-block:: kotlin

   implementation("ej.api:metrology:3.2.0")

Building or running an Application which uses the Metrology Library requires a SDK6 VEE Port that provides the :ref:`Metrology Pack <pack_metrology>`.

APIs
----

The Metrology API isn't KF compatible, use in a multi-application context may lead to unexpected results. 
It is recomended to use the Energy framework API to interact with the Metrology API.

Static Configurations
~~~~~~~~~~~~~~~~~~~~~

Meter static configuration can be retrieved with the following methods:

- `ej.energy.metrology.Metrology.getMeterForm()int`
- `ej.energy.metrology.Metrology.getMeterServiceCurrent()int`
- `ej.energy.metrology.Metrology.getMeterServiceVoltage()int`

Event API
~~~~~~~~~

This API is based on the :ref:`Event Pack <pack_event>` and allows notification of Metrology data.
It is appropriate to retrieve periodaically mean values, or process values over a period of time over 1 second. 

Streaming API
~~~~~~~~~~~~~

This API 

Classes Summary
~~~~~~~~~~~~~~~

* `Metrology`_: Get static configuration, register event listener and wait for streamed data.
* `MetrologyEventListener`_: Interface to implement to retrieve Metrology event.

.. _metrology_configuration:

Configuration
-------------

The :ref:`Metrology Pack <pack_metrology>` can be configured by defining the following :ref:`Application Options <application_options>`:

You can hook a DLMS server as data event data source on simulator, switch to a dlms source with:

- com.microej.energy.metrology.mock.dlms=true

You must provide the following properties in order for the Metrology mock to communicate with a DLMS server:

- com.microej.energy.metrology.mock.dlms.objects=<MetrologyId>,<classId>,<obisCode>,<index>;etc...
- com.microej.energy.metrology.mock.dlms.client.address=[0-9*]
- com.microej.energy.metrology.mock.dlms.server.logical.address=[0-9*]
- com.microej.energy.metrology.mock.dlms.server.physical.address=[0-9*]
- com.microej.energy.metrology.mock.dlms.server.host=<host ip or name>
- com.microej.energy.metrology.mock.dlms.server.port=[0-9*]

Configure the available immortal size to accomodate both streaming buffer:

- core.memory.immortal.size=[0-9*]

Streaming data source:

- com.microej.energy.metrology.mock.stream.data.file=</streaming/data/file/path>

Example
-------

Event Data
~~~~~~~~~~

The following snippet registers a Metrology listener:

.. code-block:: java

        String[] names = new String(){"Parameter1","Parameter2",...};
	Metrology.setParameterNames(names); //Sets names and max number of parameters
        
        OnMetrologyEventListener listener = new OnMetrologyEventListener();
        Metrology.setListener(listener);

The following snippet process data:

.. code-block:: java

        private static class OnMetrologyEventListener implements MetrologyEventListener {

	@Override
	public void onParametersReceived(final float[] parametersValues) {
		//Business logic here
        }

Streaming Data
~~~~~~~~~~~~~~~

The following snippet wait for streaming data and process it:

.. code-block:: java

        byte[] buffer;
        while (PROCESS) {
	    buffer = Metrology.waitStreamBuffer();// Get next data buffer.
	    Metrology.lockStreamBuffer(); // Lock native buffer to prevent data overwrite.            

            //Process the stream here

            Metrology.unlockStreamBuffer(); //Unlock native buffer.
        } 

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
