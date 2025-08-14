.. _metrology_api:

Metrology
=========

Introduction
------------

The Metrology Library provides APIs for retrieving metrology data and managing metrology-related configurations.

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

.. warning::

        The Metrology API is not KF-compatible. Using it in a multi-application context may cause unexpected behavior. It is recommended to use the Energy Framework API to interact with the Metrology API.


Static Configurations
~~~~~~~~~~~~~~~~~~~~~

The following methods allow you to retrieve static meter configurations:

- `ej.energy.metrology.Metrology.getMeterForm()int`
- `ej.energy.metrology.Metrology.getMeterServiceCurrent()int`
- `ej.energy.metrology.Metrology.getMeterServiceVoltage()int`

Event API
~~~~~~~~~

This API is based on the :ref:`Event Pack <pack_event>` and provides notifications for Metrology data.
It is suitable for retrieving processed data, like mean values, over periods of 1 second or more.

Streaming API
~~~~~~~~~~~~~

The `waitStreamBuffer` method is a blocking call that returns when a streaming buffer is full.
The application can lock the buffer during processing to prevent its data from being overwritten by the native process. 
The buffer must be released after processing.

Classes Summary
~~~~~~~~~~~~~~~

* `Metrology`: Access static configurations, register event listeners, and wait for streamed data.
* `MetrologyEventListener`: Interface to implement for receiving Metrology events.

.. _metrology_configuration:

Configuration
-------------

The :ref:`Metrology Pack <pack_metrology>` can be configured by defining the following :ref:`Application Options <application_options>`.

You can configure a DLMS server as the data source in the simulator by setting::

        com.microej.energy.metrology.mock.dlms=true

The following properties must be provided for the Metrology mock to communicate with a DLMS server::

        com.microej.energy.metrology.mock.dlms.objects=<MetrologyId>,<classId>,<obisCode>,<index>;etc...
        com.microej.energy.metrology.mock.dlms.client.address=[0-9*]
        com.microej.energy.metrology.mock.dlms.server.logical.address=[0-9*]
        com.microej.energy.metrology.mock.dlms.server.physical.address=[0-9*]
        com.microej.energy.metrology.mock.dlms.server.host=<host ip or name>
        com.microej.energy.metrology.mock.dlms.server.port=[0-9*]

Set the immortal memory size to accommodate streaming buffers::

        core.memory.immortal.size=[0-9*]

For streaming data source::
        
        com.microej.energy.metrology.mock.stream.data.file=</streaming/data/file/path>

Example
-------

Event Data
~~~~~~~~~~

The following snippet demonstrates how to register a Metrology listener:

.. code-block:: java

        String[] names = new String(){"Parameter1","Parameter2",...};
	Metrology.setParameterNames(names); // Sets names and max number of parameters
        
        OnMetrologyEventListener listener = new OnMetrologyEventListener();
        Metrology.setListener(listener); // Register the listener

Processing the data:

.. code-block:: java

        private static class OnMetrologyEventListener implements MetrologyEventListener {

	@Override
	public void onParametersReceived(final float[] parametersValues) {
		
                //Process the values here

        }

Streaming Data
~~~~~~~~~~~~~~~

The following snippet waits for streaming data and processes it:

.. code-block:: java

        byte[] buffer; // local buffer pointer, no buffer content copy
        while (PROCESS) { // PROCESS the process condition
	    buffer = Metrology.waitStreamBuffer();// Get next data buffer.
	    Metrology.lockStreamBuffer(); // Lock native buffer to prevent data overwrite.            

            //Process the stream buffer here

            Metrology.unlockStreamBuffer(); // Unlock native buffer.
        } 

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
