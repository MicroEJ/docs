.. _sdk_6_run_on_device:

Run on Device
=============

The SDK allows to deploy an Application on a Device thanks to the Gradle ``runOnDevice`` task.
The prerequisites of this task are:

- The Application EntryPoint must be configured, as described in :ref:`sdk_6_create_project_configure_project`.

- The target VEE Port must be defined.
  Refer to the :ref:`sdk_6_select_veeport` page to know the different ways to provide a VEE Port for a module project.

- The Device must be connected to the developer's computer.

- The configuration required by the VEE Port must be set. Refer to the VEE Port documentation to check the required configuration.

Once these prerequisites are fulfilled, the Application can be deployed on the Device:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      By double-clicking on the ``runOnDevice`` task in the Gradle tasks view:

      .. image:: images/intellij-runOnDevice-gradle-project.png
         :width: 30%
         :align: center

      |

      .. warning::
         Android Studio does not allow to run multiple Gradle tasks in parallel.
         If you still want to execute several Gradle tasks simultaneously, 
         you can launch them from a terminal with the Gradle Command Line Interface (CLI).

   .. tab:: Eclipse

      By double-clicking on the ``runOnDevice`` task in the Gradle tasks view:

      .. image:: images/eclipse-runOnDevice-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: Visual Studio Code

      By double-clicking on the ``runOnDevice`` task in the Gradle tasks view:

      .. image:: images/vscode-runOnDevice-gradle-project.png
         :width: 25%
         :align: center

   .. tab:: Command Line Interface

      From the command line interface::
      
          $ ./gradlew runOnDevice

The build should be successful and the output should end with::

   Execution of script '<RUN_SCRIPT_PATH>' done.
   BUILD SUCCESSFUL

where ``RUN_SCRIPT_PATH`` is the absolute path to the ``run.[sh|bat]`` script of the VEE Port.

The Application Executable is now deployed on the Device.

Deploying the Executable without building it
--------------------------------------------

When executing the ``runOnDevice`` task, the Executable is always rebuilt, 
even if nothing has changed in the project.
This ensures that the Executable is always up-to-date, no matter if the BSP has changed or not.

If you want to deploy the Executable on the device without building it (so simply 
deploying the Executable file already available in the project ``build`` folder), 
you can exclude the ``buildExecutable`` task::

   $ ./gradlew runOnDevice -x buildExecutable

You can execute such a command in IDEs by creating custom configurations, 
as explained in :ref:`sdk_6_howto_create_custom_configuration_in_ide`.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
