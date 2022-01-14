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
checked, the property file ``device/device.properties`` may be 
defined during platform creation to customize the module.

The properties file must / can contain the following properties:

-  ``architecture`` [optional, default value is "Virtual Device"]:
   Defines the value returned by the
   ``ej.util.Device.getArchitecture()`` method on the Simulator.

-  ``id.length`` [optional]: Defines the size of the ID returned by the
   ``ej.util.Device.getId()`` method on the Simulator.


Use
===

The `Device API Module <https://repository.microej.com/modules/ej/api/device/>`_ 
must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project to use the Device library.

::

   <dependency org="ej.api" name="device" rev="1.0.2"/>

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
