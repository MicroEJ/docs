.. _sdk_6_select_kernel:

Select a Kernel
===============

Building the Feature file of an Application with the SDK requires a Kernel.

Use one of the following available options to provide it to your project. 

.. _sdk_6_select_kernel_module:

Using a Module Dependency
~~~~~~~~~~~~~~~~~~~~~~~~~

When your Kernel is published in an artifact repository, 
you can define the Kernel by declaring a module dependency in the ``build.gradle.kts`` file, with the ``microejVee`` configuration::
   
   dependencies {
      microejVee("com.mycompany:mykernel:1.0.0")
   }

.. _sdk_6_select_kernel_in_multiproject:

Kernel project inside a multi-project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When the Kernel project is in the same multi-project than the component which needs it (an Application for example), 
the Kernel project should be declared as a project dependency.

For example if the multi-project contains an Application subproject named ``my-app`` and a Kernel subproject called ``my-kernel``,
the Kernel project must be declared as a dependency in the ``build.gradle.kts`` file of the ``my-app`` subproject as follows::

    dependencies {

        microejVee(project(":my-kernel"))

    }

.. _sdk_6_select_kernel_outside_multi-project:

Local Kernel project outside a multi-project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When the Application or the Library which needs the Kernel is not in the same multi-project than the Kernel, 
the Kernel project can be imported thanks to the `Gradle Composite Build <https://docs.gradle.org/current/userguide/composite_builds.html>`_ feature.

This allows to consider the Kernel project as part of the Application project, 
so all changes done to the Kernel are automatically considered when building or running the Application.

This is done by adding the following line in the ``settings.gradle.kts`` file of the Application project::

  includeBuild("[kernel-project-absolute-path]")

Then declaring the Kernel as a dependency in the ``build.gradle.kts`` file of the Application project::

    dependencies {

        microejVee("com.mycompany:my-kernel:1.0.0")

    }

The dependency must use the module notation (``"group:name:version"``), where the group and name match with the ones declared in the Kernel project.
The group is defined in the ``build.gradle.kts`` file of the ``my-kernel`` project by the ``group`` property.
The name is defined in the ``settings.gradle.kts`` file when the ``my-kernel`` project is included. 
For example, the name of the Kernel is ``my-custom-kernel`` if the ``my-kernel`` subproject is included with::

  include("my-custom-kernel")
  project(":my-custom-kernel").projectDir = file("my-kernel")

Otherwise the name of the subproject folder is used, so ``my-kernel`` in the recommended structure. 

.. _sdk_6_select_local_kernel:

Using a Local Kernel
~~~~~~~~~~~~~~~~~~~~

When your Kernel has been built locally, 
you can use its Virtual Device and its Executable by declaring a file dependency in the ``build.gradle.kts`` file, with the ``microejVee`` configuration::

   dependencies {
      microejVee(files("C:\\path\\to\\my\\kernel\\virtual\\device", "C:\\path\\to\\my\\kernel\\executable.out"))
   }

This is generally the case when the VEE Port has been built locally

- in SDK 6, by executing the ``buildVirtualDevice`` and ``buildExecutable`` Gradle tasks on the Kernel project. 
  In this case, the Virtual directory is located in the ``build/virtualDevice`` of the project and the Executable is located in the ``build/application/executable`` folder.

.. warning::

   It is recommended to :ref:`include the Kernel project <sdk_6_select_kernel_outside_multi-project>` instead of using a file dependency to ensure that any change done to 
   the Kernel project is considered when building your Application without having to manually rebuild the Virtual Device and the Executable.
 
- in SDK 5, by executing a ``Build Module`` on the Kernel project. 
  In this case, the Virtual Device archive file and the Executable are located in the ``target~/artifacts`` folder of the Kernel project.

.. note::

   The ``build.gradle.kts`` file, as well as other Gradle configuration files, respects the Java properties file convention: 
   the OS path	must use the UNIX path convention (path separator is ``/``). 
   The Windows paths must have been converted manually replacing ``\`` by ``/`` or by ``\\``.

.. _sdk_6_kernel_transitivity:

Resolve a Kernel transitively
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. warning::

   The transitive resolution of a Kernel is not supported for Kernels built with SDK 5 or SDK 6 ``1.2.0`` or older provided 
   as :ref:`module <sdk_6_select_kernel_module>` or :ref:`project <sdk_6_select_kernel_in_multiproject>`.
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
