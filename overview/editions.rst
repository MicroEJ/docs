MicroEJ Editions
================

Introduction
~~~~~~~~~~~~

MicroEJ offers a comprehensive toolset to build the embedded software of
a device. The toolset covers two levels in device software development:

-  MicroEJ SDK for device firmware development

-  MicroEJ Studio for application development

The firmware will generally be produced by the device OEM, it includes
all device drivers and a specific set of MicroEJ functionalities useful
for application developers targeting this device.

.. figure:: images/toolchain.png
   :alt: MicroEJ Development Tools Overview
   :align: center

   MicroEJ Development Tools Overview

Using the MicroEJ SDK tool, a firmware developer will produce two
versions of the MicroEJ binary, each one able to run applications
created with the MicroEJ Studio tool:

-  A MicroEJ Firmware binary to be flashed on OEM devices;

-  A Virtual Device which will be used as a device simulator by
   application developers.

Using the MicroEJ Studio tool, an application developer will be able to:

-  Import Virtual Devices matching his target hardware in order to
   develop and test applications on the Simulator;

-  Deploy the application locally on an hardware device equipped with
   the MicroEJ Firmware;

-  Package and publish the application on a MicroEJ Forge Instance,
   enabling remote end users to install it on their devices. For more
   information about MicroEJ Forge, please consult
   `<https://www.microej.com/product/forge>`_.


.. _get_sdk_version:

Determine the MicroEJ Studio/SDK Version
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In MicroEJ Studio/SDK, go to ``Help`` > ``About MicroEJ SDK`` menu.

In case of MicroEJ SDK ``4.1.x``, the MicroEJ SDK version is directly displayed, such as ``4.1.5``:

   .. figure:: images/about_sdk_4.x.png
      :alt: MicroEJ SDK 4.x About Window

In case of MicroEJ SDK ``5.x``, the value displayed is the MicroEJ SDK distribution, such as ``19.05`` or ``20.07``:

   .. figure:: images/about_sdk_dist_20.07.png
      :alt: MicroEJ SDK Distribution About Window

To retrieve the MicroEJ SDK version that is currently installed in this distribution, proceed with the following steps:

   - Click on the ``Installation Details`` button,
   - Click on the ``Installed Software`` tab,
   - Retrieve the version of entry named ``MicroEJ SDK`` (or ``MicroEJ Studio``).

   .. figure:: images/installation_details_sdk_dist_20.07.png
      :alt: MicroEJ SDK Distribution Installation Details Window
  

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
