Installation
============

Device Information is an additional module. In the platform
configuration file, check ``Device Information`` to install it. When
checked, the property file ``device
            > 
            device.properties`` may be defined during platform creation
to customize the module.

The properties file must / can contain the following properties:

-  ``architecture`` [optional, default value is "Virtual Device"]:
   Defines the value returned by the
   ``ej.util.Device.getArchitecture()`` method on the simulator.

-  ``id.length`` [optional]: Defines the size of the ID returned by the
   ``ej.util.Device.getId()`` method on the simulator.
