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

Once these prerequisites are fulfilled, the Virtual Device can be built:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      By double-clicking on the ``buildVirtualDevice`` task in the Gradle tasks view:

      .. image:: images/intellij-buildVirtualDevice-gradle-project.png
         :width: 30%
         :align: center
      
   .. tab:: Eclipse

      By double-clicking on the ``buildVirtualDevice`` task in the Gradle tasks view:

      .. image:: images/eclipse-buildVirtualDevice-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: CLI

      From the command line interface::
      
          $ ./gradlew buildVirtualDevice

When the build is completed, the Virtual Device is available in the ``build/virtualDevice`` folder of the project.
It can then be used to :ref:`run an Application on the Simulator <sdk_6_run_on_simulator>` for example.

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
the ``buildVirtualDevice`` task:

.. tabs::
      
   .. tab:: Android Studio / IntelliJ IDEA

      To add the property in Android Studio or IntelliJ IDEA : 

      - Go to ``Run`` > ``Edit Configurations...``.
      - Click on the ``+`` button and select ``Gradle``.
      - Choose a name for the new configuration in the ``Name`` input field.
      - Add the task name with the ``veePort`` property in the ``Run`` dialog : ``buildVirtualDevice -PveePort="veePortName"``:
      
        .. figure:: images/intellij-buildVirtualDevice-run-configuration.png
           :alt: Android Studio and IntelliJ buildVirtualDevice Run Configuration Window
           :align: center
           :scale: 100%
      
           Android Studio and IntelliJ buildVirtualDevice Run Configuration Window
      
      - Click on ``OK``.
      - Run the task by double clicking on the newly created Run Configuration in the Gradle view:
      
        .. figure:: images/intellij-buildVirtualDevice-run-configuration-gradle-view.png
           :alt: Android Studio and IntelliJ buildVirtualDevice Run Configuration in Gradle view
           :align: center
           :scale: 100%
      
           Android Studio and IntelliJ buildVirtualDevice Run Configuration in Gradle view

   .. tab:: Eclipse

      To add the property in Eclipse: 
      
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

   .. tab:: CLI

      To add the property from the command line interface::

         ./gradlew buildVirtualDevice -PveePort="veePortName"

.. _sdk_6_buildVirtualDevice_add_application:

Add a Pre-Installed Application in a Virtual Device
---------------------------------------------------

When building a Virtual Device for a Kernel, Applications can be pre-installed inside.
These Applications can be loaded and started when the Kernel starts for example.

To install an Application in a Virtual Device for a Kernel, 
you must declare the Application as a dependency of the project in the build file, with the ``microejApplication`` configuration::

   dependencies {
      microejApplication("com.mycompany:myapp:1.0.0")
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

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
