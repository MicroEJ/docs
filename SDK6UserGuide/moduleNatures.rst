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

**Plugin Name**: ``com.microej.gradle.library``

**Documentation**: :ref:`libraries`

**Template**: `Add-On Library Project Template <https://github.com/MicroEJ/Tool-Project-Template-Add-On-Library/tree/1.7.0>`__

**Tasks**:

This plugin adds the following tasks to your project:

- tasks of the `Gradle Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html>`__
- :ref:`sdk6_module_natures.tasks.adp`
- :ref:`sdk6_module_natures.tasks.loadVee`
- :ref:`sdk6_module_natures.tasks.checkModule`
- :ref:`sdk6_module_natures.tasks.execTool`

.. graphviz:: graphAddonLibraryModule.dot

**Configuration**:

This module nature inherits from the configuration of all its tasks.

.. _sdk6_module_natures.application:

Application
-----------

**Plugin Name**: ``com.microej.gradle.application``

**Documentation**: :ref:`standalone_application`, :ref:`sandboxed_application`, :ref:`kernel-developer-guide`

**Template**: `Application Project Template <https://github.com/MicroEJ/Tool-Project-Template-Application/tree/1.7.0>`__

**Tasks**:

This plugin adds the following tasks to your project:

- tasks of the `Gradle Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html>`__
- :ref:`sdk6_module_natures.tasks.adp`
- :ref:`sdk6_module_natures.tasks.loadVee`
- :ref:`sdk6_module_natures.tasks.runOnSimulator`
- :ref:`sdk6_module_natures.tasks.checkModule`
- :ref:`sdk6_module_natures.tasks.buildApplicationObjectFile`
- :ref:`sdk6_module_natures.tasks.buildExecutable`
- :ref:`sdk6_module_natures.tasks.buildWPK`
- :ref:`sdk6_module_natures.tasks.buildVirtualDevice`
- :ref:`sdk6_module_natures.tasks.loadKernelExecutable`
- :ref:`sdk6_module_natures.tasks.buildFeature`
- :ref:`sdk6_module_natures.tasks.runOnDevice`
- :ref:`sdk6_module_natures.tasks.execTool`
- :ref:`sdk6_module_natures.tasks.generateApplicationWrapper`
- :ref:`sdk6_module_natures.tasks.compileWrapperJava`
- :ref:`sdk6_module_natures.tasks.buildFeatureFromWPK`
- :ref:`sdk6_module_natures.tasks.shrinkRuntimeEnvironment`

.. graphviz:: graphApplicationModule.dot

.. _sdk6_module_natures.jse_lib:

Java SE Library
---------------

**Plugin Name**: ``com.microej.gradle.jse-library``

**Template**: `Java SE Library Template <https://github.com/MicroEJ/Tool-Project-Template-JavaSE-Library/tree/1.6.0>`__

**Tasks**:

This plugin adds the following tasks to your project:

- tasks of the `Gradle Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html>`__
- :ref:`sdk6_module_natures.tasks.checkModule`

.. graphviz:: graphJavaSeLibraryModule.dot

**Configuration**:

This module nature inherits from the configuration of all its tasks.

.. _sdk6_module_natures.mock:

Mock
----

**Plugin Name**: ``com.microej.gradle.mock``

**Documentation**: :ref:`mock`

**Template**: `Mock Project Template <https://github.com/MicroEJ/Tool-Project-Template-Mock/tree/1.7.0>`__

**Tasks**:

This plugin adds the following tasks to your project:

- tasks of the `Gradle Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html>`__
- :ref:`sdk6_module_natures.tasks.checkModule`
- :ref:`sdk6_module_natures.tasks.buildMockRip`

.. graphviz:: graphMockModule.dot

**Configuration**:

This module nature inherits from the configuration of all its tasks.

.. _sdk6_module_natures.runtime-environment:

Runtime Environment
-------------------

**Plugin Name**: ``com.microej.gradle.runtime-environment``

**Documentation**: :ref:`runtime_environment`

**Template**: `Runtime Environment Template <https://github.com/MicroEJ/Tool-Project-Template-Runtime-Environment/tree/1.6.0>`__

**Tasks**:

This plugin adds the following tasks to your project:

- tasks of the `Gradle Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html>`__
- :ref:`sdk6_module_natures.tasks.checkModule`
- :ref:`sdk6_module_natures.tasks.shrinkRuntimeEnvironment`
- :ref:`sdk6_module_natures.tasks.compileRuntimeEnvironment`
- :ref:`sdk6_module_natures.tasks.builRuntimeEnvironmentJar`

.. graphviz:: graphRuntimeEnvironmentModule.dot

**Configuration**:

This module nature inherits from the configuration of all its tasks.

.. _sdk6_module_natures.veeport:

VEE Port
--------

**Plugin Name**: ``com.microej.gradle.veeport``

**Documentation**: :ref:`vee-porting-guide`

**Template**: `VEE Port Template <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/tree/1.5.0>`__

**Tasks**:

This plugin adds the following tasks to your project:

- :ref:`sdk6_module_natures.tasks.checkModule`
- :ref:`sdk6_module_natures.tasks.buildVeePort`
- :ref:`sdk6_module_natures.tasks.buildVeePortConfiguration`
- :ref:`sdk6_module_natures.tasks.extractLibrariesSources`
- :ref:`sdk6_module_natures.tasks.javadoc`
- :ref:`sdk6_module_natures.tasks.javadocJar`

.. graphviz:: graphVeePortModule.dot

**Configuration**:

This module nature inherits from the configuration of all its tasks.

.. _sdk6_module_natures.module-repository:

Module Repository
-----------------

**Plugin Name**: ``com.microej.gradle.module-repository``

**Documentation**: :ref:`sdk6_module_repository`

**Template**: `Module Repository Project Template <https://github.com/MicroEJ/Tool-Project-Template-Module-Repository>`__

**Tasks**:

This plugin adds the following tasks to your project:

- :ref:`sdk6_module_natures.tasks.checkModule`
- :ref:`sdk6_module_natures.tasks.buildModuleRepository`
- :ref:`sdk6_module_natures.tasks.checkModuleRepository`

.. graphviz:: graphModuleRepositoryModule.dot

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

The ``loadVee`` task is used internally by the SDK and it is not intended to be executed by the user.

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
- :ref:`sdk6_module_natures.mock`
- :ref:`sdk6_module_natures.runtime-environment`
- :ref:`sdk6_module_natures.veeport`
- :ref:`sdk6_module_natures.module-repository`

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
   * - ``checkersRootDir``
     - Path of the directory to use as root directory for the checkers.
     - Project directory.

For example:

.. code::

  microej {
    checkers = "readme,license"
  }

.. _sdk6_module_natures.tasks.buildApplicationObjectFile:

buildApplicationObjectFile
^^^^^^^^^^^^^^^^^^^^^^^^^^

**Description**: Build the object file of the Application.

**Inputs**:

- The extracted VEE Port folder
- The project classpath which contains the MicroEJ dependent application classes and resources
- The Full Qualified Name of the Application EntryPoint
- The folder containing the application configuration (``configuration``)

**Outputs**:

- The object file (.o) of the Application and the archive of the build files (``build/application/object/bsp/lib/microejapp.o``)
- The Zip file containing the generated build files (``build/application/applicationObjectBuildFiles.zip``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

The ``buildApplicationObjectFile`` task is used internally by the SDK and it is not intended to be executed by the user.

.. _sdk6_module_natures.tasks.buildExecutable:

buildExecutable
^^^^^^^^^^^^^^^

**Description**: Builds the Executable of an Application.

**Inputs**:

- The extracted VEE Port folder
- The folder containing the application configuration (``configuration``)
- The object file (.o) of the Application

**Outputs**:

- The directory in which the Executable file and the build files are generated (``build/application/executable``)

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

**Description**: Builds the Virtual Device of an Application.

**Inputs**:

- The extracted VEE Port folder
- The WPK of the Application
- The project build classpath
- The WPK of the Applications that must be pre-installed in the Virtual Device

**Outputs**:

- The Zip file of the Virtual Device (``build/libs/<application_name>-virtualDevice.zip``)

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

The ``loadKernelExecutable`` task is used internally by the SDK and it is not intended to be executed by the user.

.. _sdk6_module_natures.tasks.buildFeature:

buildFeature
^^^^^^^^^^^^

**Description**: Builds the Feature file of an Application.

**Inputs**:

- The Kernel Virtual Device 
- The folder containing the Kernel Executable file (``build/kernelExecutable``)
- The project classpath
- The path of the folder where the Feature file must be generated (``build/application/feature``)

**Outputs**:

- The generated Feature file (``build/application/feature/application.fo``)
- The Zip file containing the generated build files (``build/libs/<application_name>-buildFiles.zip``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.runOnDevice:

runOnDevice
^^^^^^^^^^^

**Description**: Runs the Executable on a Device.

**Inputs**:

- The extracted VEE Port folder
- The folder containing the Executable file (``build/application/executable``)
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

**Options**:


.. list-table::
   :widths: 25 25

   * - **Option**
     - **Description**
   * - ``name``
     - ``Name of the Tool.``
   * - ``toolProperty``
     - ``Option of the Tool.``

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.addon_lib`
- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.generateApplicationWrapper:

generateApplicationWrapper
^^^^^^^^^^^^^^^^^^^^^^^^^^

**Description**: Generates the :ref:`gradle_application_wrapper_chapter` to be able to run the Application on a VEE Port and a Kernel.

**Inputs**:

- The Application EntryPoint
- The configuration directory of the project
- The project classpath which contains the MicroEJ dependent application classes and resources

**Outputs**:

- The directory in which the Wrapper Java class has been generated (``build/generated/microej-app-wrapper/java``)
- The directory in which the Wrapper Kernel resources have been generated (``build/generated/microej-app-wrapper/kernel-resources``)
- The directory in which the Wrapper Feature resources have been generated (``build/generated/microej-app-wrapper/feature-resources``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

The ``generateApplicationWrapper`` task is used internally by the SDK and it is not intended to be executed by the user.

.. _sdk6_module_natures.tasks.compileWrapperJava:

compileWrapperJava
^^^^^^^^^^^^^^^^^^

**Description**: Compiles the :ref:`gradle_application_wrapper_chapter` to be able to run the Application on a VEE Port and a Kernel.

**Inputs**:

- The directory containing the Wrapper Java class (``build/generated/microej-app-wrapper/java``)

**Outputs**:

- The directory in which the compiled wrapper class is generated (``build/generated/microej-app-wrapper/classes``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

The ``compileWrapperJava`` task is used internally by the SDK and it is not intended to be executed by the user.

.. _sdk6_module_natures.tasks.shrinkRuntimeEnvironment:

shrinkRuntimeEnvironment
^^^^^^^^^^^^^^^^^^^^^^^^

**Description**: Shrinks the Java source files according to the provided :ref:`Kernel APIs <kernel.api>`.

**Inputs**:

- Project Kernel API (``src/main/resources/kernel.api``)
- Project Java sources (``src/main/java``)
- The Kernel API files of the Runtime classpath.

**Outputs**:

- The directory in which shrunk Java sources are generated (``build/runtimeEnvironment/shrunkSources``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.runtime-environment`
- :ref:`sdk6_module_natures.application`

The ``shrinkRuntimeEnvironment`` task is used internally by the SDK and it is not intended to be executed by the user.

.. _sdk6_module_natures.tasks.compileRuntimeEnvironment:

compileRuntimeEnvironment
^^^^^^^^^^^^^^^^^^^^^^^^^

**Description**: Compiles the Runtime Environment :ref:`Kernel APIs <kernel.api>`.

**Inputs**:

- The directory in which shrunk Java sources are generated (``build/runtimeEnvironment/shrunkSources``)
- The project classpath

**Outputs**:

- The directory in which shrunk Java classes are generated (``build/runtimeEnvironment/shrunkClasses``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.runtime-environment`

The ``compileRuntimeEnvironment`` task is used internally by the SDK and it is not intended to be executed by the user.

.. _sdk6_module_natures.tasks.builRuntimeEnvironmentJar:

buildRuntimeEnvironmentJar
^^^^^^^^^^^^^^^^^^^^^^^^^^

**Description**: Builds the Runtime Environment Jar file.

**Inputs**:

- The directory in which shrunk Java classes are generated (``build/runtimeEnvironment/shrunkClasses``)

**Outputs**:

- The Jar file of the Runtime Environment (``build/libs/<project_name>-<project_version>-runtime-environment.jar``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.runtime-environment`

The ``buildRuntimeEnvironmentJar`` task is used internally by the SDK and it is not intended to be executed by the user.

.. _sdk6_module_natures.tasks.buildFeatureFromWPK:

buildFeatureFromWPK
^^^^^^^^^^^^^^^^^^^

**Description**: Builds the Feature binary file from a dependent Application.

**Inputs**:

- The Kernel Virtual Device 
- The folder containing the Kernel Executable file (``build/kernelExecutable``)
- The WPK of the dependent Application
- The path of the folder where the Feature file must be generated (``build/application/wpkFeature``)

**Outputs**:

- The generated Feature file (``build/application/wpkFeature/application.fo``)
- The Zip file containing the generated build files (``build/libs/wpkFeature-buildFiles.zip``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.buildVeePort:

buildVeePort
^^^^^^^^^^^^

**Description**: Builds the VEE Port.

**Inputs**:

- The project configuration file (``configuration.properties``)
- The project dropins folder
- The project microui folder (``extensions/microui``)
- The project classpath which contains the Architecture, Packs, Mocks, Front Panels, Tools and Libraries

**Outputs**:

- The Zip file of the VEE Port (``build/veePort.zip``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.veeport`

.. _sdk6_module_natures.tasks.buildVeePortConfiguration:

buildVeePortConfiguration
^^^^^^^^^^^^^^^^^^^^^^^^^

**Description**: Zips the VEE Port Configuration.

**Inputs**:

- The project configuration file (``configuration.properties``)
- The project dropins folder
- The project microui folder (``extensions/microui``)
- The project classpath which contains the Architecture, Packs, Mocks, Front Panels, Tools and Libraries

**Outputs**:

- The Zip file of the VEE Port Configuration (``build/<project_name>.zip``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.veeport`

.. _sdk6_module_natures.tasks.extractLibrariesSources:

extractLibrariesSources
^^^^^^^^^^^^^^^^^^^^^^^

**Description**: Extracts all Libraries source Jars to generate the Javadoc of the VEE Port.

**Inputs**:

- The VEE Port's Libraries exposed to the consumer

**Outputs**:

- The directory containing the sources of all provided Libraries (``build/librariesSources``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.veeport`

.. _sdk6_module_natures.tasks.javadoc:

javadoc
^^^^^^^

**Description**: Generates VEE Port aggregated javadoc.

**Inputs**:

- The directory containing the sources of all provided Libraries (``build/librariesSources``)

**Outputs**:

- The directory containing the aggregated javadoc (``build/docs/javadoc``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.veeport`

.. _sdk6_module_natures.tasks.javadocJar:

javadocJar
^^^^^^^^^^

**Description**: Assembles a jar archive containing the aggregated javadoc.

**Inputs**:

- The directory containing the aggregated javadoc (``build/docs/javadoc``)

**Outputs**:

- The directory containing the Jar file of the aggregated javadoc (``build/libs``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.veeport`

.. _sdk6_module_natures.tasks.buildModuleRepository:

buildModuleRepository
^^^^^^^^^^^^^^^^^^^^^

**Description**: Builds the Module Repository.

**Inputs**:

- The dependencies of the project.

**Outputs**:

- The archive file containing the Module Repository (``build/libs/<project_name>.zip``)

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.module-repository`

.. _sdk6_module_natures.tasks.checkModuleRepository:

checkModuleRepository
^^^^^^^^^^^^^^^^^^^^^

**Description**: Checks the consistency of a Module Repository.

**Inputs**:

- The Module Repository archive file.
- The list of the dependencies to skip. If not set, the check is executed on all dependencies.

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.module-repository`

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
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
