.. _sdk_6_build_executable:

Build an Executable
===================

In order to build the Executable of an Application, the SDK provides the Gradle ``buildExecutable`` task.
The prerequisites to use this task are:

- The Application EntryPoint must be configured, as described in :ref:`sdk_6_create_project_configure_project`.
- A target VEE Port that uses an Architecture version ``7.17`` minimum must be defined.
  Refer to the :ref:`sdk_6_select_veeport` page to know the different ways to provide a VEE Port for a module project.

Once these prerequisites are fulfilled, the Executable can be built:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      By double-clicking on the ``buildExecutable`` task in the Gradle tasks view:

      .. image:: images/intellij-buildExecutable-gradle-project.png
         :width: 30%
         :align: center

   .. tab:: Eclipse

      By double-clicking on the ``buildExecutable`` task in the Gradle tasks view:

      .. image:: images/eclipse-buildExecutable-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: Visual Studio Code

      By double-clicking on the ``buildExecutable`` task in the Gradle tasks view:

      .. image:: images/vscode-buildExecutable-gradle-project.png
         :width: 25%
         :align: center

   .. tab:: Command Line Interface

      From the command line interface::

          $ ./gradlew buildExecutable

In case of :ref:`Full BSP Connection <bsp_connection>`, the Executable file is generated in the ``build/output/application`` folder of the project.

.. _sdk_6_trigger_executable_build:

Trigger Executable Build by Default
-----------------------------------

The Executable of an Application is not built and published by default (when launching a ``./gradlew build`` or 
a ``./gradlew publish`` for example).
This default behavior can be changed by adding the ``produceExecutableDuringBuild()`` method 
in the ``microej`` configuration block of the Gradle build file of the project::

   microej {
     produceExecutableDuringBuild()
   }

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
