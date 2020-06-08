.. _blemock-troubleshooting:

Network setup
-------------

The network security key isn't correct
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Issue observed on Windows, try to use a smartphone instead.

I can't find the "BLE-Mock-Controller-[hexa device id]" access point
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The signal of this Wi-Fi access point may be weaker than the surrounding access 
points. Try to reduce the distance between the controller and your computer; and
rescan. If it's not possible, try using a smartphone instead (only a browser
will be required to set up the network configuration).

I want to override the network configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If the Wi-Fi credentials are not valid anymore, the controller restarts the
network setup phase. Yet, in case the credentials are valid but you want to
change them, erase the flash and reflash the firmware.

Simulation
----------

Error during the simulation : mock could not connect to controller
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This error means the mock (simulator) could not initialize the connection
with the controller. Please check that the device is connected to the network
(see logs in the serial port output) and that your computer is in the same
network.

.. _developer.microej.com: https://developer.microej.com/getting-started-sdk-esp32-wrover-5.html
.. _firmware: resources/blemock-controller.bin
..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.