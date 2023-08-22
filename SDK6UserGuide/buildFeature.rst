.. _sdk_6_build_feature:

Build a Feature file
====================

To build the Feature file (``.fo``) of an Application, the SDK provides the Gradle ``buildFeature`` task.
The prerequisites to use this task are:

- A target VEE Port that uses an Architecture version ``7.17`` minimum must be defined.
  Refer to the :ref:`sdk_6_select_veeport` page to learn how to provide a VEE Port for a module project.

- A Kernel must be defined.
  Refer to the :ref:`sdk_6_select_kernel` page to learn how to provide a Kernel for a module project.

Once these prerequisites are fulfilled, the Feature file can be built:

.. tabs::

   .. tab:: CLI

      From the command line interface::

          $ ./gradlew buildFeature
      
   .. tab:: Eclipse

      By double-clicking on the ``buildFeature`` task in the Gradle tasks view:

      .. image:: images/eclipse-buildFeature-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: IntelliJ IDEA

      By double-clicking on the ``buildFeature`` task in the Gradle tasks view:

      .. image:: images/intellij-buildFeature-gradle-project.png
         :width: 30%
         :align: center


.. note::

   When multiple Kernels are provided in the build file of the project, a Feature file is generated for each Kernel.

.. _sdk_6_buildFeature_with_multiple_vee_ports:

Build a Feature file with multiple VEE Ports
--------------------------------------------

Only one VEE Port can be used to build the Feature file of an Application.
If multiple VEE Ports are defined, the task fails with a message listing all the VEE Ports that can be used::

   More than one VEE Port have been defined.
   A VEE Port must be selected using the 'veePort' property ('-PveePort="veePortName"'). The following VEE Ports are available:
   - "veePort1"
   - "veePort2"
 
To build the Feature file, you must select the VEE Port to use by setting the ``veePort`` property to the 
:ref:`unique name <sdk_6_vee_port_unique_name>` of the VEE Port when calling 
the ``buildFeature`` task:

.. tabs::

   .. tab:: CLI

      To add the property from the command line interface::

         ./gradlew buildFeature -PveePort="veePortName"
      
   .. tab:: IntelliJ IDEA

      To add the property in IntelliJ IDEA : 

      - Go to ``Run`` > ``Edit Configurations...``.
      - Click on the ``+`` button and select ``Gradle``.
      - Choose a name for the new configuration in the ``Name`` input field.
      - Add the task name with the ``veePort`` property in the ``Run`` dialog : ``buildFeature -PveePort="veePortName"``:
      
        .. figure:: images/intellij-buildFeature-run-configuration.png
           :alt: IntelliJ buildFeature Run Configuration Window
           :align: center
           :scale: 100%
      
           IntelliJ buildFeature Run Configuration Window
      
      - Click on ``OK``.
      - Run the task by double clicking on the newly created Run Configuration in the Gradle view:
      
        .. figure:: images/intellij-buildFeature-run-configuration-gradle-view.png
           :alt: IntelliJ buildFeature Run Configuration in Gradle view
           :align: center
           :scale: 100%
      
           IntelliJ buildFeature Run Configuration in Gradle view

   .. tab:: Eclipse

      To add the property in Eclipse : 

      - Go to ``Run`` > ``Run Configurations...``.
      - Create a new Gradle Configuration.
      - Choose a name for the new configuration in the ``Name`` input field.
      - In the ``Gradle Tasks``, add the ``buildFeature`` task:
      
        .. figure:: images/eclipse-buildFeature-gradle-tasks.png
           :alt: Eclipse buildFeature task Gradle Tasks tab
           :align: center
           :scale: 100%
           
           Eclipse buildFeature task Gradle Tasks tab
      
      - Go to the ``Project Settings`` tab.
      - Check ``Override project settings``.
      - Select ``Gradle Wrapper``.
      - Add the property as a Program Argument:
      
        .. figure:: images/eclipse-buildFeature-project-settings.png
           :alt: Eclipse buildFeature task Project Settings tab
           :align: center
           :scale: 100%
           
           Eclipse buildFeature task Project Settings tab
      
      - Click on ``Run``.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
