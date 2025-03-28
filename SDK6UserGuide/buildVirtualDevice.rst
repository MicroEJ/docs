.. _sdk_6_build_virtual_device:

Build a Virtual Device
======================

In order to build the Virtual Device of an Application, the SDK provides the Gradle ``buildVirtualDevice`` task.
Refer to the :ref:`section.virtual.device` page for more information about the Virtual Device.

The prerequisites to use the ``buildVirtualDevice`` task are:

- The Application EntryPoint must be configured, as described in :ref:`sdk_6_create_project_configure_project`.
- A target VEE that uses an Architecture version ``7.17`` minimum must be defined:

  - If your VEE is a VEE Port, refer to the :ref:`sdk_6_select_veeport` page to know the different ways to provide a VEE Port for a module project.
  - If your VEE is a Kernel, refer to the :ref:`sdk_6_select_kernel` page to know the different ways to provide a Kernel for a module project.

Once these prerequisites are fulfilled, the Virtual Device can be built:

.. tabs::

   .. tab:: IntelliJ IDEA / Android Studio

      By double-clicking on the ``buildVirtualDevice`` task in the Gradle tasks view:

      .. image:: images/intellij-buildVirtualDevice-gradle-project.png
         :width: 30%
         :align: center

      |

      .. warning::
         Android Studio does not allow to run multiple Gradle tasks in parallel.
         If you still want to execute several Gradle tasks simultaneously, 
         you can launch them from a terminal with the Gradle Command Line Interface (CLI).

   .. tab:: Eclipse

      By double-clicking on the ``buildVirtualDevice`` task in the Gradle tasks view:

      .. image:: images/eclipse-buildVirtualDevice-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: Visual Studio Code

      By double-clicking on the ``buildVirtualDevice`` task in the Gradle tasks view:

      .. image:: images/vscode-buildVirtualDevice-gradle-project.png
         :width: 25%
         :align: center

   .. tab:: Command Line Interface

      From the command line interface::
      
          $ ./gradlew buildVirtualDevice

When the build is completed, the Virtual Device is available in the ``build/virtualDevice`` folder of the project.

.. note::
   If the provided VEE is a Kernel, the generated Virtual Device is an augmented version of the Kernel Virtual Device, 
   in which the Application is set as a :ref:`Pre-Installed Application <sdk_6_buildVirtualDevice_add_application>`.

The Virtual Device can then be used to :ref:`run an Application on the Simulator <sdk_6_run_on_simulator>` for example.

.. _sdk_6_buildVirtualDevice_add_application:

Add a Pre-Installed Application in a Virtual Device
---------------------------------------------------

When building a Virtual Device for a Kernel, Applications can be pre-installed inside.
These Applications can be loaded and started when the Kernel starts for example.

To install an Application in a Virtual Device for a Kernel, 
you must declare the Application as a dependency of the project:

- When the Application is published in an artifact repository, you can use it by declaring a Module dependency::

   dependencies {
      microejApplication("com.mycompany:myapp:1.0.0")
   }  

- When the Application is a subproject of a multi-project, you can use it by declaring a Project dependency in the ``build.gradle.kts`` file, with the ``microejApplication`` configuration::

   dependencies {
      microejApplication(project(":myApplication"))
   }  

- You can also use the Application WPK file directly by declaring a File dependency in the ``build.gradle.kts`` file, with the ``microejApplication`` configuration::

   dependencies {
      microejApplication(files("C:\\path\\to\\my\\application.wpk"))
   }     

.. warning::
   - Only modules with the :ref:`Application Module Nature <sdk6_module_natures.application>` can be declared this 
     way (modules built with the ``com.microej.gradle.application`` plugin).
     Declaring a module with another Module Nature would make the build fail.
   - The VEE Port used to create the Virtual Device has to be a Multi-Sandbox VEE Port to support the load of these 
     pre-installed Applications.


.. _sdk_6_buildVirtualDevice_add_kernel_api:

Add a Kernel API in a Virtual Device
------------------------------------

When building a Virtual Device for a Kernel, the Kernel must define the set of classes, methods and static fields all 
applications are allowed to use.
This can be done by declaring :ref:`Kernel APIs <kernel.api>` as a dependency in the build file::

   dependencies {
      implementation("com.microej.kernelapi:edc:1.2.0")
   }

.. _sdk_6_buildVirtualDevice_add_runtime_environment:

Add a Runtime Environment in a Virtual Device
---------------------------------------------

When building a Virtual Device for a Kernel, the set of classes, methods and static fields allowed to be used 
by all applications can be defined by declaring a :ref:`runtime_environment` as a dependency in the build file::

   dependencies {
      microejRuntimeEnvironment("com.mycompany:myruntime-environment:1.0.0")
   }

The transitive dependencies of the Runtime Environment are then embedded in the Virtual Device.

.. _sdk_6_buildVirtualDevice_add_tool:

Add a Tool in a Virtual Device
------------------------------

When building a Virtual Device, it is possible to define additional MicroEJ Tools to install inside, 
by adding a dependency with the ``microejTool`` configuration. For example, to install the :ref:`sdk6_localDeployTool` tool,
add the following dependency to the build file of the project::

   dependencies {
      microejTool("com.microej.tool.kernel:localdeploy-extension:1.0.0")
   }

.. _sdk_6_trigger_virtual_device_build:

Trigger Virtual Device Build by Default
---------------------------------------

The Virtual Device of an Application is not built and published by default (when launching a ``./gradlew build`` or 
a ``./gradlew publish`` for example).
This default behavior can be changed by adding the ``produceVirtualDeviceDuringBuild()`` method 
in the ``microej`` configuration block of the Gradle build file of the project::

   microej {
     produceVirtualDeviceDuringBuild()
   }

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
