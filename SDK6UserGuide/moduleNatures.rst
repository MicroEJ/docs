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
- :ref:`sdk6_module_natures.tasks.loadVeePort`
- :ref:`sdk6_module_natures.tasks.loadApplicationConfiguration`
- :ref:`sdk6_module_natures.tasks.runOnSimulator`
- :ref:`sdk6_module_natures.tasks.loadTestApplicationConfiguration`
- :ref:`sdk6_module_natures.tasks.checkModule`

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
- :ref:`sdk6_module_natures.tasks.loadVeePort`
- :ref:`sdk6_module_natures.tasks.loadApplicationConfiguration`
- :ref:`sdk6_module_natures.tasks.runOnSimulator`
- :ref:`sdk6_module_natures.tasks.loadTestApplicationConfiguration`
- :ref:`sdk6_module_natures.tasks.checkModule`
- :ref:`sdk6_module_natures.tasks.loadExecutableConfiguration`
- :ref:`sdk6_module_natures.tasks.buildExecutable`
- :ref:`sdk6_module_natures.tasks.buildWPK`

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

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.addon_lib`
- :ref:`sdk6_module_natures.application`

**Configuration**:


.. _sdk6_module_natures.tasks.loadVeePort:

loadVeePort
^^^^^^^^^^^^

**Description**: Loads the VEE Port.

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
   * - ``veePortDirs``
     - Path of the root folder of the VEE Port to use in the build.
     - Not set
   * - ``veePortFiles``
     - Path of the VEE Port file to use in the build. 
     - Not set

For example:

.. code::

  microej {
    veePortDirs = listOf("C:\\path\\to\\my\\veePort\\directory")
  }

.. _sdk6_module_natures.tasks.loadApplicationConfiguration:

loadApplicationConfiguration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Description**: Loads the configuration for the Application to execute.

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
   * - ``applicationMainClass``
     - Full Qualified Name of the main class of the application. This option is required.
     - Not set

For example:

.. code::

  microej {
    applicationMainClass = "com.company.Main"
  }

.. _sdk6_module_natures.tasks.runOnSimulator:

runOnSimulator
^^^^^^^^^^^^^^

**Description**: Executes the Application with the Simulator.

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.addon_lib`
- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.loadTestApplicationConfiguration:

loadTestApplicationConfiguration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Description**: Loads the configuration for the Test Application to execute.

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.addon_lib`
- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.checkModule:

checkModule
^^^^^^^^^^^

**Description**: Checks the compliance of the module.

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

.. _sdk6_module_natures.tasks.loadExecutableConfiguration:

loadExecutableConfiguration
^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Description**: Loads the configuration to build the Executable of an Application.

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.buildExecutable:

buildExecutable
^^^^^^^^^^^^^^^

**Description**: Build the Executable of an Application.

**Module Natures**:

This task is used by the following module natures:

- :ref:`sdk6_module_natures.application`

.. _sdk6_module_natures.tasks.buildWPK:

buildWPK
^^^^^^^^

**Description**: Builds the WPK of the Application.

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
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
