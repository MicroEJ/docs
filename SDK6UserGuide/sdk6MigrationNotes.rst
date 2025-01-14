.. _sdk_6_migration_notes:

Migration Notes
---------------

.. note::

   When updating the plugin version, it is recommended to perform a ``clean`` on your project(s).
   For multi-projects, run the ``clean`` command on the root project.

---------------------
From 0.19.0 to 0.20.0
---------------------

This section applies if SDK 6 ``0.20.0`` is used on a project that was created using SDK 6 ``0.19.0`` 
or lower.

Minimum Gradle version
~~~~~~~~~~~~~~~~~~~~~~

The minimum required version of Gradle is now ``8.6.``.
`Upgrade the Gradle Wrapper version <https://docs.gradle.org/current/userguide/gradle_wrapper.html#sec:upgrading_wrapper>`__ of your project.

New SDK EULA
~~~~~~~~~~~~

A new SDK EULA must be approved before using the SDK (version ``3.1-C``).
Refer to :ref:`sdk_6_eula_acceptation` page to learn how to approve it.

Plugins and Configurations renaming
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following plugins and configurations have been renamed:

- plugin ``com.microej.gradle.j2se-library`` to ``com.microej.gradle.jse-library``.
- plugin ``com.microej.gradle.runtime-api`` to ``com.microej.gradle.runtime-environment``.
- configuration ``microejRuntimeApi`` to ``microejRuntimeEnvironment``.

The previous plugins and configurations are still supported but are deprecated and will be removed in the next major version.
It is recommended to update your project now.

Virtual Device Build
~~~~~~~~~~~~~~~~~~~~

The Virtual Device of an Application is not built by default anymore when calling the ``build`` task.
You can call the ``buildVirtualDevice`` task to build it, 
or add the following code in your ``build.gradle.kts`` file to continue to build it when calling the ``build`` task::

   microej {
      produceVirtualDeviceDuringBuild()
   }

---------------------
From 0.15.0 to 0.16.0
---------------------

This section applies if SDK 6 ``0.16.0`` is used on a project that was created using SDK 6 ``0.15.0`` 
or lower.

Unification of Application EntryPoint
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The creation of a Sandboxed Application and a Standalone Application have been unified.
To create an Application, the following steps must be done:

- Create the Java main class in the ``src/main/java`` folder.
- Define the property ``applicationEntryPoint`` in the ``microej`` configuration block of the ``build.gradle.kts`` file.
  It must be set to the Full Qualified Name of the Application main class::

   microej {
      applicationEntryPoint = "com.mycompany.Main"
   }   

- Define a VEE (VEE Port or Kernel) by declaring a dependency in the ``build.gradle.kts`` file::

   dependencies {
      microejVee("com.mycompany:myVee:1.0.0")
   }

If your Application requires the use of advanced features, you must create a Feature class, for example::
            
    package com.mycompany;
      
    import ej.kf.FeatureEntryPoint;
      
    public class MyFeature implements FeatureEntryPoint {
    
      @Override
      public void start() {
        System.out.println("Feature MyFeature started!");
      }
    
      @Override
      public void stop() {
        System.out.println("Feature MyFeature stopped!");
      }
    }

and set the property ``applicationEntryPoint`` to the Full Qualified Name of the Feature class::

   microej {
      applicationEntryPoint = "com.mycompany.MyFeature"
   }   

---------------------
From 0.14.0 to 0.15.0
---------------------

This section applies if SDK 6 ``0.15.0`` is used on a project that was created using SDK 6 ``0.14.0`` 
or lower.

Unification of VEE dependency declaration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``microejVeePort`` configuration, used to define a VEE Port, and the ``microejKernel`` configuration, used to define a Kernel,
have been unified into the ``microejVee`` configuration.

- To use a VEE Port or a Kernel published in an artifact repository, declare a Module dependency in the ``build.gradle.kts`` file::

   dependencies {
      microejVee("com.mycompany:myVee:1.0.0")
   }

- To use a VEE Port directory available locally, declare a file dependency in the ``build.gradle.kts`` file::

   dependencies {
      microejVee(files("C:\\path\\to\\my\\veePort\\source"))
   }

- To use a VEE Port archive available locally, declare a file dependency in the ``build.gradle.kts`` file::

   dependencies {
      microejVee(files("C:\\path\\to\\my\\veePort\\file.zip"))
   }

- To use a Kernel Virtual Device and Executable available locally, declare a file dependency in the ``build.gradle.kts``::

   dependencies {
      microejVee(files("C:\\path\\to\\my\\kernel\\executable.out", "C:\\path\\to\\my\\kernel\\virtual\\device"))
   }

---------------------
From 0.11.1 to 0.12.0
---------------------

This section applies if SDK 6 ``0.12.0`` is used on a project that was created using SDK 6 ``0.11.1`` 
or lower.

Use of File Dependencies to Define a Local VEE Port or a Kernel Executable
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``veePortPath`` and the ``kernelFile`` properties have been replaced by file dependencies.

- To use a VEE Port archive available locally, declare a file dependency in the ``build.gradle.kts`` file, with the ``microejVeePort`` configuration::

   dependencies {
      microejVeePort(files("C:\\path\\to\\my\\veePort\\file.zip"))
   }

- To use a VEE Port directory available locally, declare a file dependency in the ``build.gradle.kts`` file, with the ``microejVeePort`` configuration::

   dependencies {
      microejVeePort(files("C:\\path\\to\\my\\veePort\\source"))
   }

- To use a kernel Virtual Device and Executable available locally, declare a file dependency in the ``build.gradle.kts`` file, with the ``microejKernel`` configuration::

   dependencies {
      microejKernel(files("C:\\path\\to\\my\\kernel\\executable.out", "C:\\path\\to\\my\\kernel\\virtual\\device"))
   }

---------------------
From 0.10.0 to 0.11.0
---------------------

This section applies if SDK 6 ``0.11.0`` is used on a project that was created using SDK 6 ``0.10.0`` 
or lower.

Gradle mechanism usage for Multiple VEE Ports Support
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Using multiple VEE Ports in a project uses Gradle mechanism now instead of relying on in-house feature.
This implies:
- the ``veePortPaths`` property has been renamed to ``veePortPath`` and accepts a String value::

   microej {
      veePortPath = "C:\\path\\to\\my\\veePort\\source"
   }

- the ``kernelFiles`` property has been renamed to ``kernelFile`` and accepts a String value::

   microej {
      kernelFile = "C:\\path\\to\\my\\kernel\\file"
   }

Refer to the :ref:`sdk_6_howto_build_executable_with_multiple_vee_ports` section to learn how to support multiple VEE Ports using the Gradle mechanisms.

-------------------
From 0.8.0 to 0.9.0
-------------------

This section applies if SDK 6 ``0.9.0`` is used on a project that was created using SDK 6 ``0.8.0`` 
or lower.

Merge of the veePortDirs and veePortFiles properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The build properties ``veePortDirs`` and ``veePortFiles`` have been merged into a single property ``veePortPaths``.
To define a local VEE Port, set the build property ``veePortPaths`` in the ``microej`` configuration block 
to the path of the VEE Port file (``.zip`` or ``.vde``) or to the source folder of the VEE Port::

   microej {
     veePortPaths = listOf("C:\\path\\to\\my\\veePort\\source")
   }

The ``veePortPaths`` property is defined as a list in order to provide multiple VEE Port files or source folders if it is needed::

   microej {
     veePortPaths = listOf("C:\\path\\to\\my\\veePort1\\source", "C:\\path\\to\\my\\veePort2\\file.zip")
   }

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
