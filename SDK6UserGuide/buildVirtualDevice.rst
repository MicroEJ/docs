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

   .. tab:: Command Line Interface

      From the command line interface::
      
          $ ./gradlew buildVirtualDevice

When the build is completed, the Virtual Device is available in the ``build/virtualDevice`` folder of the project.
It can then be used to :ref:`run an Application on the Simulator <sdk_6_run_on_simulator>` for example.

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
