.. _sdk_6_select_veeport:

Select a VEE Port
=================

Building or running an Application or a Test Suite with the SDK requires a VEE Port.

Use one of the following available options to provide it to your project. 

.. note::

   Declaring a VEE Port in project dependencies only applies to the current project. 
   This configuration is not fetched transitively by consumer projects.
   Especially when configuring the VEE Port to test a library project, 
   application projects depending on this library will not "see" this test VEE Port, 
   they must configure a VEE Port on their own and are free to use a different one.
   
.. _sdk_6_select_veeport_module:

Using a Module Dependency
-------------------------

When your VEE Port is published in an artifact repository, 
you can define the VEE Port by declaring a module dependency in the ``build.gradle.kts`` file, with the ``microejVee`` configuration:

   .. code:: java

      dependencies {
         microejVee("com.mycompany:myveeport:1.0.0")
      }

and by :ref:`setting the Architecture Usage <sdk_6_architecture_usage_selection>` of the VEE Port.

This is generally the case for developers focused on Application and Library development.
They don't have (and don't need) the VEE Port project locally, they only need to use it.

   .. note::

      For dependencies stored in an Ivy repository, Gradle fetches them with the configuration ``default``.
      If several artifacts are published with this configuration, the build will fail because it doesn't know which artifact to choose.
      You can select the right artifact by adding information on the one to fetch in the ``artifact`` block, for example::

         microejVee("com.mycompany:myveeport:1.0.0") {
            artifact {
               name = "artifact-name"
               type = "zip"
            }
         }

      This will select the artifact with the name ``artifact-name`` and with the type ``zip``.
      
      Refer to `the Gradle documentation <https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.DependencyHandler.html>`__ 
      to learn all the options to select dependencies.

.. _sdk_6_select_veeport_in_multiproject:

VEE Port project inside a multi-project
---------------------------------------

When the VEE Port project is in the same multi-project than the component which needs it (an Application for example), 
the VEE Port project should be declared as a project dependency.

For example if the multi-project contains an Application subproject named ``my-app`` and a VEE Port subproject called ``vee-port``,
the VEE Port project must be declared as a dependency in the ``build.gradle.kts`` file of the ``my-app`` subproject as follows::

    dependencies {

        microejVee(project(":vee-port"))

    }

and the :ref:`Architecture Usage <sdk_6_architecture_usage_selection>` of the VEE Port must be set.

The VEE Port will be automatically built when it is required by the Application.
For example when running the Application on the Simulator (with the ``runOnSimulator`` task) 
or when building the Application Executable (with the ``buildExecutable``),
the VEE Port will be built before executing the requested task.

.. _sdk_6_select_veeport_outside_multi-project:

Local VEE Port project outside a multi-project
----------------------------------------------

When the Application or the Library which needs the VEE Port is not is the same multi-project than the VEE Port, 
the VEE Port project can be imported thanks to the `Gradle Composite Build <https://docs.gradle.org/current/userguide/composite_builds.html>`_ feature.

This allows to consider the VEE Port project as part of the Application project, 
so all changes done to the VEE Port are automatically considered when building or running the Application.

This is done by adding the following line in the ``settings.gradle.kts`` file of the Application project::

  includeBuild("[vee-port-project-absolute-path]")

Then declaring the VEE Port as a dependency in the ``build.gradle.kts`` file of the Application project::

    dependencies {

        microejVee("com.mycompany:vee-port:1.0.0")

    }

The dependency must use the module notation (``"group:name:version"``), where the group and name match with the ones declared in the VEE Port project.
The group is defined in the ``build.gradle.kts`` file of the ``vee-port`` project by the ``group`` property.
The name is defined in the ``settings.gradle.kts`` file when the ``vee-port`` project is included. 
For example, the name of the VEE Port is ``my-custom-vee-port`` if the ``vee-port`` subproject is included with::

  include("my-custom-vee-port")
  project(":my-custom-vee-port").projectDir = file("vee-port")

Otherwise the name of the subproject folder is used, so ``vee-port`` in the recommended structure. 


.. _sdk_6_select_veeport_local_directory:

Using a Local VEE Port Directory
--------------------------------

When your VEE Port is available in a local directory, 
you can use it by declaring a file dependency in the ``build.gradle.kts`` file, with the ``microejVee`` configuration::

   dependencies {
      microejVee(files("C:\\path\\to\\my\\veePort\\source"))
   }

This is generally the case when the VEE Port has been built locally

- in SDK 6, by executing the ``buildVeePort`` Gradle task on the VEE Port project. 
  In this case, the VEE Port directory is located at ``build/veePort/source`` in the project.
- in SDK 5, by executing a ``Build Module`` on the VEE Port configuration project. 
  In this case, the VEE Port is a sibling folder of the VEE Port configuration project, named after the VEE Port name.

.. note::

   This file, as well as other Gradle configuration files, respects the Java properties file convention: 
   the OS path	must use the UNIX path convention (path separator is ``/``). 
   The Windows paths must have been converted manually replacing ``\`` by ``/`` or by ``\\``.

.. _sdk_6_select_veeport_local_archive:

Using a Local VEE Port Archive
------------------------------

When your VEE Port is available locally as an archive file (``.zip`` or ``.vde``),
you can use it by declaring a file dependency in the ``build.gradle.kts`` file, with the ``microejVee`` configuration::

   dependencies {
      microejVee(files("C:\\path\\to\\my\\veePort\\file.zip"))
   }

This is generally the case when 

- the VEE Port has been built locally in SDK 6, by executing the ``buildVeePort`` Gradle task on the VEE Port project. 
  In this case, the VEE Port archive is located at ``build/veePort.zip`` in the project.
- the VEE Port has been built and published in SDK 5. 
  In this case, the VEE Port archive is available in an artifact repository and can be downloaded manually to be used in your Application or Library project.

.. note::

   The legacy ``JPF`` format of a VEE Port is not supported anymore in the SDK 6. 
   If you want to use a VEE Port ``.jpf`` file, you have to use :ref:`the SDK 5 <sdk_user_guide>`.

.. _sdk_6_architecture_usage_selection:

Architecture Usage Selection
----------------------------

When the selected VEE Port is :ref:`fetched from a repository <sdk_6_select_veeport_module>` or is a :ref:`subproject of a multi-project <sdk_6_select_veeport_in_multiproject>`, 
the default Architecture Usage is ``eval`` (no matter what is configured in the VEE Port project).
It is possible to change the Architecture Usage in the project which needs it (an Application for example) 
by setting the ``architectureUsage`` property in the ``microej`` block in the ``build.gradke.kts`` file::

   microej {
      architectureUsage = "prod"
   }

Set the property to ``prod`` to use a Production Architecture and to ``eval`` to use an Evaluation Architecture.
If not set, the ``eval`` value is used.

.. warning::

   When the VEE Port is a local archive or folder (``microejVee(files(...))``), the Architecture Usage is defined when the VEE Port is built and can no longer be changed.
   In SDK 6 (with the ``buildVeePort`` task), the Architecture Usage is defined by setting the ``architectureUsage`` property in the ``build.gradke.kts`` file of the VEE Port project.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
