.. _application_options:

Application Options
###################

Introduction
============

To run a MicroEJ Standalone Application on a MicroEJ Platform, a set of options
must be defined. Options can be of different types:

- Memory Allocation options (e.g set the Java Heap size). These options are usually called link-time options.
- Simulator & Debug options (e.g. enable periodic Java Heap dump).
- Deployment options (e.g. copy ``microejapp.o`` to a suitable BSP location).
- Foundation Library specific options (e.g. embed UTF-8 encoding).

The following section describes options provided by MicroEJ Architecture.
Please consult the appropriate MicroEJ Pack documentation for options related to other Foundation Libraries (MicroUI, NET, SSL, FS, ...) integrated to the Platform.

Notice that some options may not be available, in the following cases:

- Option is specific to the MicroEJ Core Engine capability (*tiny*/*single*/*multi*) which is integrated in the targeted Platform.
- Option is specific to the target (MicroEJ Core Engine on Device or Simulator).
- Option has been introduced in a newer version of the MicroEJ Architecture which is integrated in the targeted Platform.
- Options related to :ref:`Board Support Package (BSP) connection <bsp_connection_application_options>`.

.. _define_option:

Defining an Option
==================

A MicroEJ Standalone Application option can be defined either from a launcher or from a properties file.
It is also possible to use both together. Most of MicroEJ Architecture and MicroEJ Pack options come with a preset value, which is taken into
account if no user option is defined.

Using a Launcher
----------------

To set an option in a launcher, perform the following steps:

1. In MicroEJ Studio/SDK, select :guilabel:`Run` > :guilabel:`Run Configurations...`,
2. Select the launcher of the application under :guilabel:`MicroEJ Application` or create a new one,
3. Select the :guilabel:`Configuration` tab,
4. Find the desired option and set it to the desired value.

It is recommended to index the launcher configuration to your version control system. To export launcher options to filesystem, perform the following steps:

1. Select the :guilabel:`Common tab`,
2. Select the :guilabel:`Shared file:` option and browse an export path directory,
3. Press :guilabel:`Apply button`. A file named ``[launcher_configuration_name].launch`` is generated in the directory.

Finally, to export options defined in a ``.launch`` file to a properties file, perform the following steps:

1. Select the ``[launcher_configuration_name].launch`` file,
2. Select :guilabel:`File` > :guilabel:`Export` > :guilabel:`MicroEJ` > :guilabel:`Launcher as Properties File`,
3. Browse an output ``.properties`` files,
4. Press :guilabel:`Finish` button.

Using a Properties File
-----------------------

Options can be also be defined in properties files. In case an option is defined in multiple properties files, 
the option of the first loaded file is taken into account and the same option defined in the other files is ignored (a loaded option cannot be overridden).

When a MicroEJ Standalone Application is built using the ``firmware-singleapp`` :ref:`skeleton <mmm_module_skeleton>`, 
options are loaded from properties files located in the ``build`` folder. 

The properties files are loaded in the order defined hereafter:

1. The file ``sim/sim.properties`` (optional), for Simulator options only (Virtual Device build).
2. The file ``emb/emb.properties`` (optional), for Device options only (Firmware build).
3. All files named ``*.properties`` files (no order). Usually, the ``build`` folder contains a single file named ``common.properties`` which defines options for both Simulator and Device.

The figure below shows the expected tree of the ``build`` folder:

.. figure:: images/build-properties.png
   :alt: Build Options Folder
   :align: center

   Build Options Folder

It is recommended to index the properties files to your version control system.

To set an option in a properties file, open the file in a text editor and add a line to set the desired option to the desired value. For example: ``soar.generate.classnames=false``.

To use the options declared in properties files in a launcher, perform the following steps:

1. In MicroEJ Studio/SDK, select :guilabel:`Run` > :guilabel:`Run Configurations...`,
2. Select the launcher of the application,
3. Select the :guilabel:`Execution` tab,
4. Under :guilabel:`Option Files`, press :guilabel:`Add...` button,
5. Browse the ``sim.properties`` file for Simulator or the ``emb.properties`` file for Device (if any) and press :guilabel:`Open` button,
6. Add the ``common.properties`` file and press :guilabel:`Open` button.

.. note::

   An option set in a properties file can not be modified in the ``Configuration`` tab.
   Options are loaded in the order the properties files are added (you can use ``Up`` and ``Down`` buttons to change the file ordering).
   In ``Configuration`` tab, hovering the pointer over an option field will show the location of the properties file that defines the option.

.. include:: sectionArchitectureOptions.rst

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
