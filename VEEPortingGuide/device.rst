==================
Device Information
==================


Principle
=========

The Device Foundation Library provides access to the device information. This
includes the architecture name and a unique identifier of the device for
this architecture.


Dependencies
============

-  ``LLDEVICE_impl.h`` implementation (see
   :ref:`LLDEVICE-API-SECTION`).


Installation
============

Device is an additional module. 
To enable it, the Device Information :ref:`Pack <pack_overview>` module must be installed in your VEE Port:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         microejPack("com.microej.pack.audio:audio-pack:1.0.0")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.pack.audio" name="audio-pack" rev="1.0.0"/>

      Then, using the VEE Port Editor (see :ref:`platform_module_configuration`), enable the `Device Information` library.

When installed, the Device Information Pack module can be configured.

.. tabs::

   .. tab:: SDK 6

     In SDK 6, the configuration is done in the properties file ``configuration.properties`` of the VEE Port project.
	  All the properties names listed below must be prefixed by ``com.microej.runtime.device.``.
	  For example the ``architecture`` properties is defined by the ``com.microej.runtime.device.architecture`` property.

   .. tab:: SDK 5

	  In SDK 5, the configuration is done in the properties file ``device/device.properties``.


The list below describes the properties that can be defined in the configuration file:

-  ``architecture`` [optional, default value is "Virtual Device"]: Defines the value returned by the
   `ej.util.Device.getArchitecture()`_ method on the Simulator.
-  ``id.length`` [optional]: Defines the size of the ID returned by the
   `ej.util.Device.getId()`_ method on the Simulator.

.. _ej.util.Device.getArchitecture(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/Device.html#getArchitecture--
.. _ej.util.Device.getId(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/Device.html#getId--

Use
===

The `Device API Module`_ must be added to the project build file to use the Device Information library:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.api:device:1.0.2")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="ej.api" name="device" rev="1.0.2"/>

.. _Device API Module: https://repository.microej.com/modules/ej/api/device/

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
