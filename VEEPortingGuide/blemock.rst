.. _blemock:

Bluetooth Mock
==============

Overview
--------

To run a MicroEJ Application that uses the `Bluetooth API Library <https://repository.microej.com/modules/ej/api/bluetooth/>`_ on MicroEJ Simulator, a Bluetooth Controller is required:

.. image:: images/blemock-controller.png
   :align: center

The Bluetooth Controller is a dedicated device that communicates with the Simulator to perform the Bluetooth operations of the Application.
This means that the Simulator delegates the Bluetooth operations (scanning, advertising, discovering services, connecting, etc.) to a real Bluetooth device.
This allows testing a Bluetooth application on any development environment.

The Bluetooth Controller firmware is provided for the inexpensive `ESP32-S3-DevKitC-1-N8R8 board <https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/user_guide.html>`_.

Requirements
------------

- An ESP32-S3-DevKitC-1-N8R8 board.
- A Bluetooth Controller firmware (see section below).
- The `Espressif Flash Download Tools <https://www.espressif.com/en/support/download/other-tools>`_.

Controller Firmwares
--------------------

There are multiple versions of the Controller firmware, each compatible with a specific range of Bluetooth Pack versions.

The following table indicates the firmware to use depending on the Bluetooth Pack version integrated in the VEE Port:

.. list-table::
   :widths: 10 10
   :header-rows: 1

   * - Bluetooth Pack Versions
     - Controller Firmware
   * - [2.0.0-2.3.0[
     - `1.0.0 <https://repository.microej.com/packages/ble-mock/Executable-Bluetooth-Mock-Controller-ESP32-S3-1.0.0.bin>`__
   * - [2.3.0-2.6.0[
     - `1.1.1 <https://repository.microej.com/packages/ble-mock/Executable-Bluetooth-Mock-Controller-ESP32-S3-1.1.1.bin>`__
   * - [2.6.0-3.0.0[
     - `2.0.0 <https://repository.microej.com/packages/ble-mock/Executable-Bluetooth-Mock-Controller-ESP32-S3-2.0.0.bin>`__

Usage
-----

To simulate a Bluetooth application, follow these three steps:

- Install the controller firmware
- Configure the Wi-Fi network
- Run the application on the Simulator

If you are facing any issues, check the :ref:`Troubleshooting <blemock-troubleshooting>` section.

Controller Firmware Installation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To install the controller firmware on the ESP32-S3 board, follow these steps:

- Plug in the ESP32-S3 board to your computer,
- Find the associated COM port,
- In the flash download tool:

  - select the ``ESP32-S3`` chip type
  - browse the firmware file (``Executable-Bluetooth-Mock-Controller-ESP32-S3-x.y.z.bin``)
  - set the target address to ``0``
  - set the SPI speed to ``80MHz`` and the SPI mode to ``DIO``
  - select the appopriate COM port and set the baudrate to ``460800``
  - start the flash download

With the flash download tool from Espressif, you should end with something similar to this :

.. figure:: images/blemock-flash-download-tool.png
   :alt: Bluetooth Controller Flash Download Tool Configuration
   :align: center
   :scale: 80%

   Bluetooth Controller Flash Download Tool Configuration

Wi-Fi Setup
~~~~~~~~~~~

To configure the Wi-Fi network used by the controller:

#. Connect your computer to the Wi-Fi network "BLE-Mock-Controller-[hexa device id]" mounted by the controller.
#. Open a browser and connect to ``http://192.168.4.1/`` to access the Wi-Fi setup
   interface :

   .. image:: images/blemock-wifi-setup-interface.png
      :align: center

#. Select the desired network and provide the required information if asked.
   If an error occurs during the connection, retry this step.
#. In case the ESP32-S3 board is successfully connected to the desired network, the
   web page should looks like this:

   .. image:: images/blemock-wifi-setup-last-screen.png
      :align: center

   Additionally, the serial output of the ESP32-S3 board shows connection status.
#. Connect your computer back to this network: your computer and the
   controller must be in the same network.
#. Reboot the ESP32-S3 board. At this point, the configuration is saved and the board will reconnect
   automatically every time it is powered up. If the board fails to connect, the configuration will
   be available again for re-configuration.

Simulation
~~~~~~~~~~

To configure the Bluetooth Controller for the simulation:

#. Get the IP address of the controller from its logs:

   .. image:: images/blemock-controller-ip.png
      :align: center
      :scale: 80%

#. Configure the application options:

   .. tabs::

         .. tab:: SDK 6

            Set the following :ref:`application options <sdk_6_define_option>`:

            .. code-block:: properties

               ###############################################################################
               # Bluetooth Options
               ###############################################################################

               # Set the Bluetooth simulation mode.
               # Supported values: 'stub' (default), 'net' (Bluetooth Controller)
               s3.bluetooth.mode=net
               
               # When using `net` mode, set the IP address of the Bluetooth Controller.
               s3.bluetooth.net.host=192.168.x.y

         .. tab:: SDK 5

            In the :ref:`Run configuration <concepts-microejlaunches>` panel, set the simulation mode
            to "Controller (over net)" and configure the connection options.

            .. figure:: images/blemock-configuration.png
               :alt: Bluetooth Mock Configuration
               :align: center
               :scale: 80%

               Bluetooth Mock Configuration

#. Run the application on the simulator.
   Note that when starting a new simulation, the Bluetooth Controller is reset to its initial state.

.. _blemock-troubleshooting:

Troubleshooting
---------------

Network Setup Errors
~~~~~~~~~~~~~~~~~~~~

I can't find the "BLE-Mock-Controller-[hexa device id]" access point
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The signal of this Wi-Fi access point may be weaker than the surrounding access 
points. Try to reduce the distance between the controller and your computer; and
rescan. If it's not possible, try using a smartphone instead (only a browser
will be required to set up the network configuration).

I want to override the network configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If the Wi-Fi credentials are not valid anymore, the controller restarts the
network setup phase. Yet, in case the credentials are valid but you want to
change them, erase the flash and reflash the firmware.

"Invalid parameter type: 0x47 expected 0x53" error
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Reboot the ESP32-S3 board. The controller restarts and connects to the Wi-Fi.

Simulation Errors
~~~~~~~~~~~~~~~~~

Error during the simulation: mock could not connect to controller
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This error means the mock process (Simulator) could not initialize the connection
with the controller. Please check that the ESP32-S3 board is connected to the network
(see logs in the serial port output) and that your computer is in the same
network.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.