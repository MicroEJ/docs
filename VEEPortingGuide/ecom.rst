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
   connection kind and its configuration are fixed by the String parameter
   of the method `Connector.open(String)`_.

2. Step 2 consists of opening an `InputStream`_ on the connection. This
   stream allows the MicroEJ Application to access the "RX" feature of
   the hardware device.

3. Step 3 consists of using the `InputStream`_ APIs to receive in the
   MicroEJ Application all hardware device data.

4. Step 4 consists of opening an `OutputStream`_ on the connection.
   This stream allows the MicroEJ Application to access the "TX" feature
   of the hardware device.

5. Step 5 consists of using the `OutputStream`_ APIs to transmit some
   data from the MicroEJ Application to the hardware device.

Note that steps 2 and 4 may be performed in parallel, and do not depend
on each other.

.. _InputStream: https://repository.microej.com/javadoc/microej_5.x/apis/java/io/InputStream.html
.. _OutputStream: https://repository.microej.com/javadoc/microej_5.x/apis/java/io/OutputStream.html
.. _Connector.open(String): https://repository.microej.com/javadoc/microej_5.x/apis/ej/ecom/io/Connector.html#open-java.lang.String-

.. _section_ecom_dm:

Device Management API
=====================

A device is defined by implementing `ej.ecom.Device`_. It is identified
by a name and a descriptor (`ej.ecom.HardwareDescriptor`_), which is
composed of a set of MicroEJ properties. A device can be
registered/unregistered in the `ej.ecom.DeviceManager`_.

A device registration listener is defined by implementing
`ej.ecom.RegistrationListener`_. When a device is registered to or
unregistered from the device manager, listeners registered for the
device type are notified. The notification mechanism is done in a
dedicated Java thread. The mechanism can be enabled or disabled (see
:ref:`application_options`).

.. _ej.ecom.Device: https://repository.microej.com/javadoc/microej_5.x/apis/ej/ecom/Device.html
.. _ej.ecom.HardwareDescriptor: https://repository.microej.com/javadoc/microej_5.x/apis/ej/ecom/HardwareDescriptor.html
.. _ej.ecom.DeviceManager: https://repository.microej.com/javadoc/microej_5.x/apis/ej/ecom/DeviceManager.html
.. _ej.ecom.RegistrationListener: https://repository.microej.com/javadoc/microej_5.x/apis/ej/ecom/RegistrationListener.html

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

The `ECOM API Module`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project to use the ECOM library.

::

   <dependency org="ej.api" name="ecom" rev="1.1.4"/>

This Foundation Library is always required when developing a MicroEJ Application which
communicates with some external devices. It is automatically embedded as
soon as a sub communication library is added in the classpath.

.. _ECOM API Module: https://repository.microej.com/modules/ej/api/ecom/

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
