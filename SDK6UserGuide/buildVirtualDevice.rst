.. _sdk_6_build_virtual_device:

Build a Virtual Device
======================

In order to build the Virtual Device of an Application, the SDK provides the Gradle ``buildVirtualDevice`` task.
Refer to the :ref:`section.virtual.device` page for more information about the Virtual Device.

The prerequisites to use the ``buildVirtualDevice`` task are:

- The property ``applicationMainClass`` must be defined in the ``microej`` configuration block of the Gradle build file of the project.
  It must be set to the fully qualified name of the Application main class, for example::

   microej {
     applicationMainClass = "com.mycompany.Main"
   }

- A target VEE Port that uses an Architecture version ``7.17`` minimum must be defined.
  Refer to the :ref:`sdk_6_select_veeport` page to know the different ways to provide a VEE Port for a module project.

Once these prerequisites are fulfilled, the Virtual Device can be built with the command::

    $ ./gradlew buildVirtualDevice

or from Eclipse and IntelliJ IDEA, by double-clicking on the ``buildVirtualDevice`` task in the Gradle tasks view:

.. tabs::

   .. tab:: Eclipse

      .. image:: images/eclipse-buildVirtualDevice-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: IntelliJ IDEA

      .. image:: images/intellij-buildVirtualDevice-gradle-project.png
         :width: 30%
         :align: center


.. _sdk_6_buildVirtualDevice_with_multiple_vee_ports:

Build a Virtual Device with Multiple VEE Ports
----------------------------------------------

Only one VEE Port can be used to build the Virtual Device of an Application.
If multiple VEE Ports are defined, the task fails with a message listing all the VEE Ports that can be used::

   More than one VEE Port have been defined.
   A VEE Port must be selected using the 'veePort' property ('-PveePort="veePortName"'). The following VEE Ports are available:
   - "veePort1"
   - "veePort2"
 
To build a Virtual Device, you must select the VEE Port to use by setting the ``veePort`` property to the 
:ref:`unique name <sdk_6_vee_port_unique_name>` of the VEE Port when calling 
the ``buildVirtualDevice`` task::

   ./gradlew buildVirtualDevice -PveePort="veePortName"

If you want to add the property in IntelliJ IDEA: 

- Go to ``Run`` > ``Edit Configurations...``.
- Click on the ``+`` button and select ``Gradle``.
- Choose a name for the new configuration in the ``Name`` input field.
- Add the task name with the ``veePort`` property in the ``Run`` dialog : ``buildVirtualDevice -PveePort="veePortName"``:

  .. figure:: images/intellij-buildVirtualDevice-run-configuration.png
     :alt: IntelliJ buildVirtualDevice Run Configuration Window
     :align: center
     :scale: 100%

     IntelliJ buildVirtualDevice Run Configuration Window

- Click on ``OK``.
- Run the task by double clicking on the newly created Run Configuration in the Gradle view:

  .. figure:: images/intellij-buildVirtualDevice-run-configuration-gradle-view.png
     :alt: IntelliJ buildVirtualDevice Run Configuration in Gradle view
     :align: center
     :scale: 100%

     IntelliJ buildVirtualDevice Run Configuration in Gradle view

If you want to add the property in Eclipse: 

- Go to ``Run`` > ``Run Configurations...``.
- Create a new Gradle Configuration.
- Choose a name for the new configuration in the ``Name`` input field.
- In the ``Gradle Tasks``, add the ``buildVirtualDevice`` task:

  .. figure:: images/eclipse-buildVirtualDevice-gradle-tasks.png
     :alt: Eclipse buildVirtualDevice task Gradle Tasks tab
     :align: center
     :scale: 100%
     
     Eclipse buildVirtualDevice task Gradle Tasks tab

- Go to the ``Project Settings`` tab.
- Check ``Override project settings``.
- Select ``Gradle Wrapper``.
- Add the property as a Program Argument:

  .. figure:: images/eclipse-buildVirtualDevice-project-settings.png
     :alt: Eclipse buildVirtualDevice task Project Settings tab
     :align: center
     :scale: 100%
     
     Eclipse buildVirtualDevice task Project Settings tab

- Click on ``Run``.


..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
