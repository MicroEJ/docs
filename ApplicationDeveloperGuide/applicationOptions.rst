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

To set an option in a properties file, perform the following steps:

1. In your project, create a new ``.properties`` file.
2. Edit this file in a text editor and add a line to set the desired option to the desired value. For example: ``soar.generate.classnames=false``.

It is recommended to index the properties file to your version control system.

To use the properties file in a launcher, perform the following steps:

1. In MicroEJ Studio/SDK, select ``Run`` > ``Run Configurations...``.
2. Select the launcher of the application.
3. Select the ``Execution`` tab.
4. Under ``Option Files``, press ``Add...``.
5. Select the ``.properties`` file and press ``Open``.

Multiple launchers can use the same properties file.

.. include:: sectionArchitectureOptions.rst

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
