.. _application_options:

Application Options
###################

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

.. _setting_an_option:

Setting an Option
=================

Using a Launcher
----------------

To set an option in a launcher, perform the following steps:

1. In MicroEJ Studio/SDK, select ``Run`` > ``Run Configurations...``.
2. Select the launcher of the application.
3. Select the ``Configuration`` tab.
4. Find the desired option and set it to the desired value.

It is recommended to index the launcher configuration to your version control system.
To do this, select the ``Common tab`` and select the export path of the launcher in ``Shared file:`` field.

Using a Properties File
-----------------------

To create the properties files to use when building the application, perform the following steps:

1. At the root of your project, create a ``build`` folder.
2. In this folder, create an empty ``common.properties`` file which will be used to define options both for Simulator and for Device.
3. Create a ``sim`` folder and an empty ``sim.properties`` file inside, which will be used to define options for Simulator only.
4. Create a ``emb`` folder and an empty ``emb.properties`` file inside, which will be used to define options for Device only.

The figure below shows the expected tree of the ``build`` folder:

.. figure:: images/build-properties.png
   :alt: Build Options Folder
   :align: center

   Build Options Folder

It is recommended to index the properties files to your version control system.

To set an option in a properties file, open the file in a text editor and add a line to set the desired option to the desired value. For example: ``soar.generate.classnames=false``.

To use the properties files in a launcher, perform the following steps:

1. In MicroEJ Studio/SDK, select ``Run`` > ``Run Configurations...``.
2. Select the launcher of the application.
3. Select the ``Execution`` tab.
4. Under ``Option Files``, press ``Add...``.
5. Select the ``common.properties`` file and press ``Open``.
6. Also add the ``sim.properties`` file for Simulator or the ``emb.properties`` file for Device.

.. note::

   An option which is set in a properties file can not be modified in the ``Configuration`` tab.
   In that case, hovering the pointer over the option field will show the location of the properties file in which the option is set.

.. include:: sectionArchitectureOptions.rst

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
