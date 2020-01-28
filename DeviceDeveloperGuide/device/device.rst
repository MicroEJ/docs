==================
Device Information
==================


Principle
=========

The Device library provides access to the device information. This
includes the architecture name and a unique identifier of the device for
this architecture.


Dependencies
============

-  ``LLDEVICE_impl.h`` implementation (see
   :ref:`LLDEVICE-API-SECTION`).


Installation
============

Device Information is an additional module. In the platform
configuration file, check :guilabel:`Device Information` to install it. When
checked, the property file ``device > device.properties`` may be 
defined during platform creation to customize the module.

The properties file must / can contain the following properties:

-  ``architecture`` [optional, default value is "Virtual Device"]:
   Defines the value returned by the
   ``ej.util.Device.getArchitecture()`` method on the simulator.

-  ``id.length`` [optional]: Defines the size of the ID returned by the
   ``ej.util.Device.getId()`` method on the simulator.


Use
===

A classpath variable named ``DEVICE-1.0`` is available.
