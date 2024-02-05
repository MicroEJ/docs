.. _sdk_6_run_on_device:

Run on Device
=============

The SDK allows to deploy an Application on a Device thanks to the Gradle ``runOnDevice`` task.
The prerequisites of this task are:

- The Application main class or Feature class must be configured, as described in :ref:`sdk_6_create_project_configure_project`.

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

   .. tab:: Eclipse

      By double-clicking on the ``runOnDevice`` task in the Gradle tasks view:

      .. image:: images/eclipse-runOnDevice-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: Command Line Interface

      From the command line interface::
      
          $ ./gradlew runOnDevice

The build should be successful and the output should end with::

   Execution of script '<RUN_SCRIPT_PATH>' done.
   BUILD SUCCESSFUL

where ``RUN_SCRIPT_PATH`` is the absolute path to the ``run.[sh|bat]`` script of the VEE Port.

The Application Executable is now deployed on the Device.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
