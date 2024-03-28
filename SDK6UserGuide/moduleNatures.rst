.. _sdk6_module_natures:

Module Natures
==============

This page describes the most common module natures as follows:

- **Plugin Name**: the build type name, derived from the module nature name: ``com.microej.gradle.[NATURE_NAME]``.
- **Documentation**: a link to the documentation.
- **Tasks**: tasks available from the module nature, with the graph of their relationships.
- **Configuration**: properties that can be defined to configure the module. Properties are defined inside the ``microej`` block of the ``build.gradle.kts`` file.

.. _sdk6_module_natures.addon_lib:

Add-On Library
--------------

**Plugin Name**: ``com.microej.gradle.addon-library``

**Documentation**: :ref:`libraries`

**Tasks**:

This plugin adds the following tasks to your project:

- tasks of the `Gradle Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html>`__
- :ref:`sdk6_module_natures.tasks.adp`
- :ref:`sdk6_module_natures.tasks.loadVee`
- :ref:`sdk6_module_natures.tasks.runOnSimulator`
- :ref:`sdk6_module_natures.tasks.checkModule`
- :ref:`sdk6_module_natures.tasks.execTool`

.. graphviz:: graphAddonLibraryModule.dot

**Configuration**:

This module nature inherits from the configuration of all its tasks.


.. _sdk6_module_natures.application:

Application
-----------

**Plugin Name**: ``com.microej.gradle.application``

**Documentation**: :ref:`standalone_application`

**Tasks**:

This plugin adds the following tasks to your project:

- tasks of the `Gradle Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html>`__
- :ref:`sdk6_module_natures.tasks.adp`
- :ref:`sdk6_module_natures.tasks.loadVee`
- :ref:`sdk6_module_natures.tasks.runOnSimulator`
- :ref:`sdk6_module_natures.tasks.checkModule`
- :ref:`sdk6_module_natures.tasks.buildExecutable`
- :ref:`sdk6_module_natures.tasks.buildWPK`
- :ref:`sdk6_module_natures.tasks.buildVirtualDevice`
- :ref:`sdk6_module_natures.tasks.loadKernelExecutable`
- :ref:`sdk6_module_natures.tasks.buildFeature`
- :ref:`sdk6_module_natures.tasks.runOnDevice`
- :ref:`sdk6_module_natures.tasks.execTool`
- :ref:`sdk6_module_natures.tasks.compileWrapperJava`

.. graphviz:: graphApplicationModule.dot


.. _sdk6_module_natures.j2se_lib:

J2SE Library
------------

**Plugin Name**: ``com.microej.gradle.j2se-library``

**Tasks**:

This plugin adds the following tasks to your project:

- tasks of the `Gradle Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html>`__
- :ref:`sdk6_module_natures.tasks.checkModule`

.. graphviz:: graphJ2seLibraryModule.dot

**Configuration**:

This module nature inherits from the configuration of all its tasks.


.. _sdk6_module_natures.mock:

Mock
----

**Plugin Name**: ``com.microej.gradle.mock``

**Tasks**:

This plugin adds the following tasks to your project:

- tasks of the `Gradle Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html>`__
- :ref:`sdk6_module_natures.tasks.checkModule`
- :ref:`sdk6_module_natures.tasks.buildMockRip`

.. graphviz:: graphMockModule.dot

**Configuration**:

This module nature inherits from the configuration of all its tasks.

.. _sdk6_module_natures.tasks:

Tasks
-----

This page describes the module nature tasks as follows:

- **Description**: description and link to the related documentation.
- **Module Natures**: list of :ref:`module_natures` using this task.
- **Configuration**: properties that can be defined to configure the task.

.. _sdk6_module_natures.tasks.adp:

adp
^^^

**Description**: Executes the Addon Processors.

**Inputs**:

- The project directory

**Outputs**:

- The directory for each ADP output type (``build/adp/all/main/java``, ``build/adp/all/main/resources``, ``build/adp/all/test/java``, ``build/adp/all/test/resources``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.addon_lib`
- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.loadVee:

loadVee
^^^^^^^

**Description**: Loads the VEE.

**Inputs**:

- The list of VEE archive files or folders.

**Outputs**:

- The directory where the VEE is copied/extracted (``build/vee``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.addon_lib`
- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.runOnSimulator:

runOnSimulator
^^^^^^^^^^^^^^

**Description**: Executes the Application with the Simulator.

**Inputs**:

- The extracted VEE folder
- The project classpath which contains the MicroEJ dependent application classes and resources
- The Full Qualified Name of the Application main class or Feature class
- The folder containing the application configuration (``configuration``)
- The System properties
- The debug mode
- The debug port

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.addon_lib`
- :ref:`sdk6_module_natures.application`

**Configuration**:

This task provides the following properties that can be defined in the ``microej`` extension:

.. list-table:: 
   :widths: 25 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default    
   * - ``applicationEntryPoint``
     - Full Qualified Name of the main class or the Feature class of the application. This option is required.
     - Not set

For example:

.. code::

  microej {
    applicationEntryPoint = "com.company.Main"
  }

.. _sdk6_module_natures.tasks.checkModule:

checkModule
^^^^^^^^^^^

**Description**: Checks the compliance of the module.

**Inputs**:

- The list of the checkers to execute, separated by comas. If not set, all the checkers are executed.
- The list of the checkers to skip, separated by comas.

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.addon_lib`
- :ref:`sdk6_module_natures.application`

**Configuration**:

This task is not bound by default on any lifecycle task, 
which means that it should be called explicitly if it must be executed.

This task provides the following properties that can be defined in the ``microej`` extension:

.. list-table:: 
   :widths: 25 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - ``checkers``
     - Comma-separated list of the names of the checkers to execute. 
       An empty list means that all checkers are executed.
     - ``""``
   * - ``skippedCheckers``
     - Comma-separated list of the names of the checkers to exclude. 
       Only one property of ``checkers`` and ``skippedCheckers`` can be defined.
     - ``""``

For example:

.. code::

  microej {
    checkers = "readme,license"
  }

.. _sdk6_module_natures.tasks.buildExecutable:

buildExecutable
^^^^^^^^^^^^^^^

**Description**: Builds the Executable of an Application.

**Inputs**:

- The extracted VEE Port folder
- The project classpath which contains the MicroEJ dependent application classes and resources
- The Full Qualified Name of the Application main class
- The folder containing the application configuration (``configuration``)

**Outputs**:

- The directory in which the Executable file and the build files are generated (``build/executable/application``)
- The Zip file containing the generated build files (``build/executable/buildFiles.zip``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.buildWPK:

buildWPK
^^^^^^^^

**Description**: Builds the WPK of the Application.

**Inputs**:

- The Application name
- The Application version
- The Full Qualified Name of the Application main class or Feature class
- The Application JAR file
- The Application Javadoc
- The Jar files of the Application classpath
- The folder containing the application configuration (``configuration``)

**Outputs**:

- The WPK of the Application (``build/libs/<application_name>.wpk``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.buildVirtualDevice:

buildVirtualDevice
^^^^^^^^^^^^^^^^^^

**Inputs**:

- The extracted VEE Port folder
- The WPK of the Application
- The project build classpath
- The WPK of the Applications that must be pre-installed in the Virtual Device

**Outputs**:

- The Zip file of the Virtual Device (``build/libs/<application_name>-virtualDevice.zip``)

**Description**: Build the Virtual Device of an Application.

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.loadKernelExecutable:

loadKernelExecutable
^^^^^^^^^^^^^^^^^^^^

**Description**: Loads the Kernel Executable file.

**Inputs**:

- The list of Kernel Executable files.

**Outputs**:

- The loaded Kernel Executable file is copied (``build/kernelExecutable/kernel.out``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.buildFeature:

buildFeature
^^^^^^^^^^^^

**Description**: Build the Feature file of an Application.

**Inputs**:

- The Kernel Virtual Device 
- The folder containing the Kernel Executable file (``build/kernelExecutable``)
- The project classpath
- The path of the folder where the Feature file must be generated (``build/feature/application``)

**Outputs**:

- The generated Feature file (``build/feature/application/application.fo``)
- The Zip file containing the generated build files (``build/"libs/<application_name>-feature.zip"``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.runOnDevice:

runOnDevice
^^^^^^^^^^^^

**Description**: Runs the Executable on a Device.

**Inputs**:

- The extracted VEE Port folder
- The folder containing the Executable file (``build/executable/application``)
- The configuration file with all the properties set to launch the build of the Executable (``build/properties/target.properties``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.buildMockRip:

buildMockRip
^^^^^^^^^^^^

**Description**: Builds the Mock RIP.

**Inputs**:

- The Mock JAR file

**Outputs**:

- the RIP file of the Mock (``build/libs/<project_name>-<project_version>.rip``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.mock`

.. _sdk6_module_natures.tasks.execTool:

execTool
^^^^^^^^

**Description**: Runs the given MicroEJ Tool.

**Inputs**:

- The extracted VEE Port folder
- The configuration file with all the properties set to launch the application (``build/properties/target.properties``)
- The folder containing the application configuration (``configuration``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.addon_lib`
- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.compileWrapperJava:

compileWrapperJava
^^^^^^^^^^^^^^^^^^

**Description**: Compiles Application wrapper class to be able to run the Application on a VEE Port and a Kernel.

**Inputs**:

- The project classpath which contains the MicroEJ dependent application classes and resources

**Outputs**:

- The directory in which the compiled wrapper class is generated (``build/generated/microej-app-wrapper/classes``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _gradle_global_build_options:

Global Properties
-----------------

The following properties are available in any module:

.. list-table::
   :widths: 1 5 3
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - ``microejConflictResolutionRulesEnabled``
     - Boolean to enabled or disabled the MicroEJ conflict resolution rules.
     - ``true``

For example:

.. code::

  microej {
    microejConflictResolutionRulesEnabled = false
  }

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
