.. _chapter.gnss:

====
GNSS
====

Principle
=========

The GNSS Foundation Library.

Functional Description
======================

Interaction with the GNSS API goes through a GNSS manager. This manager works around a state machine. 
To perform read operations to retrieve GNSS data, the machine must be in a STARTED state. 
Transitions between the states are controlled by the user.
:ref:`The following graph <fig_gnss-state-machine>`: details the different states, their function and transitions.

.. _fig_gnss-state-machine:
.. figure:: images/gnss-state-machine.*
   :alt: GNSS state machine.
   :align: center
   :scale: 75%

   GNSS State Machine.

Turning the GNSS Engine ON
~~~~~~~~~~~~~~~~~~~~~~~~~~

After each calls, the method `getState()` can be called on the GNSS manager instance to check weither or not the state has been successfully changed.

.. code-block:: java
    
    // Retrieve the GNSS instance
    GnssManager gnssManager = GnssManager.getInstance();
	
    // Initialize the manager and native components
    gnssManager.initializeManager();

    // Switch the GNSS Engine ON
    gnssManager.switchOn();

Retrieving GNSS data
~~~~~~~~~~~~~~~~~~~~

.. code-block:: java

    // Read data
    gnssManager.readPosition();

    // Check timestamp of latest data read to confirm a fix was found.
    long timestamp = gnssManager.getTime();

    // Retrieve alitude data from engine   
    gnssManager.getAltitude()

Turning the GNSS Engine OFF
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: java
    
    // Retrieve the GNSS instance
    GnssManager gnssManager = GnssManager.getInstance();
	
    // Switch the GNSS Engine OFF
    gnssManager.switchOff();

    // Close every native components and the manager.
    gnssManager.closeManager();

.. note::

    `readPosition()` call will throw an IOException if an error occured during data reading, however, timestamp will still be updated.


Use
===

The `GNSS API Module`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project to use the Event Queue Foundation Library.

.. code-block:: xml

   <dependency org="ej.api" name="gnss" rev="2.0.0"/>

To use this API, your VEE Port must implement a compatible version. 
Please refer to the :ref:`VEE Porting Guide <pack_gnss>` to port GNSS for your project.

.. _GNSS API Module: https://forge.microej.com/artifactory/microej-developer-repository-release/ej/api/gnss/

..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
