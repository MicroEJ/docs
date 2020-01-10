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
dedicated MicroEJ thread. The mechanism can be enabled or disabled (see
`??? <#workbenchLaunchOptions>`__).
