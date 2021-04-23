====
ECOM
====


Principle
=========

The Embedded COMmunication Foundation Library (ECOM) is a generic
communication library with abstract communication stream support (a
communication framework only). It allows you to open and use streams on
communication devices such as a COMM port.

This library also provides a device manager, including a generic device
registry and a notification mechanism, which allows plug&play-based
applications.

This library does not provide APIs to manipulate some specific options
for each communication method, but it does provide some generic APIs
which abstract the communication method. After the opening step, the
MicroEJ Application can use every communications method (COMM, USB etc.)
as generic communication in order to easily change the communication
method if needed.


Functional Description
======================

:ref:`The diagram below <fig_ecom-flow>` shows the overall process to open a
connection on a hardware device.

.. _fig_ecom-flow:
.. figure:: images/ecom-core_process.*
   :alt: ECOM Flow
   :align: center
   :scale: 80%

   ECOM Flow

1. Step 1 consists of opening a connection on a hardware device. The
   connection kind and its configuration are fixed by the parameter
   ``String connectionString`` of the method ``Connection.open``.

2. Step 2 consists of opening an ``InputStream`` on the connection. This
   stream allows the MicroEJ Application to access the "RX" feature of
   the hardware device.

3. Step 3 consists of using the ``InputStream`` APIs to receive in the
   MicroEJ Application all hardware device data.

4. Step 4 consists of opening an ``OutputStream`` on the connection.
   This stream allows the MicroEJ Application to access the "TX" feature
   of the hardware device.

5. Step 5 consists of using the ``OutputStream`` APIs to transmit some
   data from the MicroEJ Application to the hardware device.

Note that steps 2 and 4 may be performed in parallel, and do not depend
on each other.


.. _section_ecom_dm:

Device Management API
=====================

A device is defined by implementing ``ej.ecom.Device``. It is identified
by a name and a descriptor (``ej.ecom.HardwareDescriptor``), which is
composed of a set of MicroEJ properties. A device can be
registered/unregistered in the ``ej.ecom.DeviceManager``.

A device registration listener is defined by implementing
``ej.ecom.RegistrationListener``. When a device is registered to or
unregistered from the device manager, listeners registered for the
device type are notified. The notification mechanism is done in a
dedicated Java thread. The mechanism can be enabled or disabled (see
:ref:`application_options`).


Dependencies
============

No dependency.


Installation
============

ECOM Foundation Library is an additional library. In the platform
configuration file, check :guilabel:`Serial Communication` > :guilabel:`ECOM` to install
the library.


Use
===

The `ECOM API Module <https://repository.microej.com/modules/ej/api/ecom/>`_ 
must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project in order to allow access to the ECOM library.

::

   <dependency org="ej.api" name="ecom" rev="1.1.4"/>

This foundation library is always required when developing a MicroEJ Application which
communicates with some external devices. It is automatically embedded as
soon as a sub communication library is added in the classpath.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
