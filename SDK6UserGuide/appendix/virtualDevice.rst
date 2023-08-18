.. _virtual_device_chapter:

Virtual Device
==============

This chapter describes the structure of a :ref:`section.virtual.device`.

.. _virtual_device_structure:

Structure
---------

A Virtual Device is structured as follows:

.. code-block::

   |- virtualDevice
   |   |- installed-applications
   |   |- javaLibs
   |   |- MICROJVM
   |   |- main-application
   |   |- mocks
   |   |- options
   |   |   |- target.properties 
   |   |- resources
   |   |- S3
   |   |- scripts
   |   |   |- init-vd 
   |   |   |   |- vd-init.xml 
   |   |- tools
   |   |- architecture.properties
   |   |- release.properties
   |   |- veePort.properties
   |   |- workbenchExtension*.jar

The Virtual Device contains the Simulation part files of the VEE Port used to build it: 

- the ``javaLibs/`` folder, that contains the Foundation Libraries which are common to MICROJVM and S3

- the ``linker/`` folder, that contains the Linker jar files. This folder is not embedded in the Virtual Device if an Architecture ``8.0.0`` is used

- the ``MICROJVM/`` folder, that contains the VEE Port's files required to build a Feature file (``.fo``)

- the ``mocks/`` folder, that contains the Jar files of the mocks for Foundation Libraries

- the ``resources/`` folder, that contains the OS specific libraries

- the ``S3/`` folder, that contains the Simulator, HIL and Foundation Libraries specific to the Simulator 

- the ``scripts/`` folder, that contains launch and initialization scripts

- the ``tools/`` folder

- the ``workbenchExtension*.jar`` files

The following elements are also embedded in the Virtual Device:

- a Kernel Application, whose WPK file is extracted in the ``main-application`` folder of the Virtual Device

- the WPK files of System Applications that are extracted in their own folder, in the ``installed-applications/`` folder that is empty by default

.. note::

   System Applications can only be embedded in a Multi-Sandboxed Virtual Device.
   In case of a Mono-Sandboxed Virtual Device, the ``installed-applications/`` folder is always empty.

- the ``options/target.properties``, that contains the properties of the VEE Port used to build the Virtual Device

- the ``scripts/init-vd/vd-init.xml`` script, that allows to enable or not the Virtual Device. If the Virtual Device is not enabled, the Application main class specified by the user is launched on the VEE Port

You can refer to the :ref:`sdk_6_build_virtual_device` page to know how to build a Virtual Device.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
