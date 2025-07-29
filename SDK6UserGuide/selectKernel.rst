.. _sdk_6_select_kernel:

Select a Kernel
===============

Building the Feature file of an Application with the SDK requires a Kernel.

Use one of the following available options to provide it to your project. 

Using a Module Dependency
~~~~~~~~~~~~~~~~~~~~~~~~~

When your Kernel is published in an artifact repository, 
you can define the Kernel by declaring a module dependency in the ``build.gradle.kts`` file, with the ``microejVee`` configuration::
   
   dependencies {
      microejVee("com.mycompany:mykernel:1.0.0")
   }

Using a Project Dependency
~~~~~~~~~~~~~~~~~~~~~~~~~~

When your Kernel is a subproject of a multi-project, 
you can define the Kernel by declaring a project dependency in the ``build.gradle.kts`` file, with the ``microejVee`` configuration::
   
   dependencies {
      microejVee(project(":mykernel"))
   }
  
Using a Local Kernel
~~~~~~~~~~~~~~~~~~~~

.. warning::

   A local Kernel can not be used if the transitive resolution of the Kernel is enabled, refer to :ref:`sdk_6_kernel_transitivity` for more information.

When your Kernel has been built locally, 
you can use its Virtual Device and its Executable by declaring a file dependency in the ``build.gradle.kts`` file, with the ``microejVee`` configuration::

   dependencies {
      microejVee(files("C:\\path\\to\\my\\kernel\\virtual\\device", "C:\\path\\to\\my\\kernel\\executable.out"))
   }

.. note::

   This file, as well as other Gradle configuration files, respects the Java properties file convention: 
   the OS path	must use the UNIX path convention (path separator is ``/``). 
   The Windows paths must have been converted manually replacing ``\`` by ``/`` or by ``\\``.

.. _sdk_6_kernel_transitivity:

Resolve a Kernel transitively
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. warning::

   The transitive resolution of a Kernel is not supported for Kernels built with SDK 5 or SDK 6 ``1.2.0`` or older and local Kernels.
   While this feature is optional for now, it will be enabled by default in the next SDK 6 major version, so it is highly recommended to update your Kernel if necessary.

By default, the Kernel is not fetched transitively by consumer projects, but starting from SDK 6 ``1.4.0``, it is possible to enable the transitivity of the Kernel by:

- Setting the project property ``feature.vee.transitivity.enabled`` to ``true`` in command line with the ``-P`` argument::
   
    ./gradlew runOnSimulator -Pfeature.vee.transitivity.enabled=true

- or by adding it in the ``gradle.properties`` file of your project::

    feature.vee.transitivity.enabled=true

When the feature is enabled, the Jar file of the Kernel and its transitive dependencies are fetched to build the compile classpath and runtime classpath of the project. 
For more information about the transitivity of the Kernel, refer to :ref:`gradle_vee_transitivity_chapter`.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
