.. _chapter.application.deploy:

Run on the Device
=================

A Sandboxed Application can be deployed on a device in several ways:

- Local Deployment: the device is connected to the developer's computer and the SDK transfers the Application on it.
- Remote Deployment: the device connects to a Repository where the Application is stored, and deploys it over the network.

In both cases, the Multi-Sandbox Firmware must be previously flashed on the device.
Please refer to the :ref:`kernel-developer-guide` to learn how to do it and to 
the `Resources Repository <https://repository.microej.com/index.php?resource=FIRM&topic=ALL&version=ANY&edition=ANY>`_ 
for the available Multi-Sandbox demo Firmwares.

Local Deployment
----------------

Deploying a Application on a device through Local Deployment is the easiest way to test it since it only requires to:

- have the device with the Multi-Sandbox Firmware
- connect the device to the developer's computer

Once these prerequisite are fullfilled:

- duplicate the Run Configuration created in the chapter :ref:`chapter.application.sim`,

.. figure:: images/sandboxed-application-duplicate-run-conf.png
   :alt: Duplicate Run Configuration
   :align: center

   Duplicate Run Configuration

- rename the duplicated Run Configuration, for example by prefixing by ``(Local)``,
- in the :guilabel:`Execution` tab, modify the :guilabel:`Execution` mode to :guilabel:`Execute on Device`,
- select the option :guilabel:`Local Deployment (Socket)` in the :guilabel:`Settings` list.
  Note that depending on the device capability, the virtual device may implement a local deployment over a Comm Port.

.. figure:: images/sandboxed-application-configure-run-conf.png
   :alt: Configure Run Configuration
   :align: center

   Configure Run Configuration

- go to the :guilabel:`Configuration` tab,
- select the item :guilabel:`Local Deployment (Socket)`,
- set the IP address of the device in the :guilabel:`Host` field,
- click on the :guilabel:`Run` button to deploy the Application on the board.

The Console output should be::

   =============== [ Initialization Stage ] ===============
   =============== [ Converting fonts ] ===============
   =============== [ Converting images ] ===============
   =============== [ Build Application ] ===============
   =============== [ Completed Successfully ] ===============
   =============== [ Deploy on 192.168.0.7:4000 ] ===============
   =============== [ Completed Successfully ] ===============
   
   SUCCESS

The Application is deployed on the device and automatically started.
You can use a Serial terminal to get the traces of the Application::

   KERNEL Hello World!
   => Starting Feature MyApplication
   Feature MyApplication started!

Remote Deployment
-----------------

An Application can also be deployed remotely, from a MicroEJ Forge instance.

This requires to create and publish the WPK file that is intended to
be published on the MicroEJ Forge instance.

To do so, in the SDK, right-click on the Sandboxed Application project and click on :guilabel:`Build Module`.

The WPK build process will display messages in the console, ending up the following message:

::

    [echo] project hello published locally with version 0.1.0-RC201907091602

    BUILD SUCCESSFUL

    Total time: 1 minute 6 seconds

The WPK file produced by the build process is located in a dedicated
``target~/artifacts`` folder in the project and is published to the 
target module repository declared in :ref:`MicroEJ Module Manager settings file <mmm_settings_file>`.

The module repository can be a `MicroEJ Forge instance <https://www.microej.com/product/forge/>`_.

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
