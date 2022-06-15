.. _chapter.application.deploy:

Run on the Device
=================

A Sandboxed Application can be deployed on a device in several ways:

- Local Deployment: the device is connected to the developer's computer and the SDK transfers the Application on it.
- Remote Deployment: the device connects to a Repository where the Application is stored, and deploys it over the network.

Local Deployment
----------------

Deploying a Application on a device through Local Deployment is the easiest way to test it since it only requires to:

- have the device with the Multi-Sandbox Firmware
- connect the device to the developer's computer

Once these prerequisite fullfilled:

- duplicate the Run Configuration created in the chapter :ref:`chapter.application.sim`,

.. figure:: images/sandboxed-application-duplicate-run-conf.png
   :alt: Duplicate Run Configuration
   :align: center

   Duplicate Run Configuration

- rename the duplicated Run Configuration, for example by prefixing by ``(Local)``,
- modify the ``Execution`` mode to ``Execute on Device``,
- select the option ``Local Deployment (Socket)`` in the ``Settings`` list``.
  Note that depending on the device capability, the virtual device may implement a local deployment over a Comm Port.

.. figure:: images/sandboxed-application-configure-run-conf.png
   :alt: Configure Run Configuration
   :align: center

   Configure Run Configuration

- go to the tab ``Configuration``,
- select the item ``Local Deployment (Socket)``,
- set the IP address of the device in the ``Host`` field,
- click on the ``Run`` button to deploy the Application on the board.

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

// TODO

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
