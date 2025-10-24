.. _sdk6_module_repository:

Module Repository
=================

A Module Repository is a module that bundles a set of modules in a portable ZIP file. 
It is a tree structure where modules organizations and names are mapped to folders.

   .. figure:: images/module_repository.png
      :width: 30%
      :align: center

      Example of Module Repository Tree

A Module Repository takes its input modules from other repositories, usually the :ref:`MicroEJ Central Repository <central_repository>` 
which is itself built by MicroEJ Corp. as an Module Repository.

.. _sdk_6_create_module_repository_project:

Create a Repository Project
---------------------------

A Module Repository project can be created as follows:

- Open a new Terminal.
- Create a new ``module-repository`` folder in the directory of your choice.
- Run ``gradle init`` command.
- Select ``Basic`` as type of build to generate.
- Enter the project's name of your choice.
- Select ``Kotlin`` as build script DSL.
- Enter ``no`` when asked to generate build using new APIs and behavior.
- Once the project is created, you can :ref:`import it <sdk_6_import_project>` in the IDE of your choice.
- In the ``build.gradle.kts`` file of the project, apply the ``module-repository`` plugin and define the group and the version of the project::

    plugins {
        id("com.microej.gradle.module-repository") version "1.5.0"
    }

    group = "org.example"
    version = "0.1.0-RC"

.. _sdk_6_include_modules:

Include Modules
---------------

Modules bundled into the Module Repository must be declared as dependencies of the project. A dependency is declared with the  ``microejModule`` configuration::

    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0")
    }

By default, a dependency is resolved transitively but it is possible to not fetch its transitive dependencies by specifying it in the dependency's declaration::

    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0") {
            isTransitive = false
        }
    }

When a dependency is not resolved transitively, you must explicitly declare its transitive dependencies in your project.
To ensure that repository users won't have any resolution issues, a :ref:`sdk6_consistency_check` is enabled by default.

.. warning::

   Only Module dependencies are supported in a Module Repository project. To add a module available as project or included build, 
   you must first publish it to be able to add it to the repository. 

.. _sdk_6_include_single_artifact:

Include a Single Artifact
~~~~~~~~~~~~~~~~~~~~~~~~~

When a module is added as dependency of a Module Repository project, all its artifacts are fetched and added to the repository. However,
it is possible to select one artifact if you don't want to add all of them by specifying its extension in the dependency's declaration. 
For example, to only fetch the Virtual Device of a Kernel, you must add the ``zip`` extension in the dependency::

    dependencies {
        microejModule("org.example:my-kernel:1.0.0@zip")
    }

You can also specify the name of the artifact if it differs from the module's name. For example, 
declare the following dependency to fetch the ``imageGenerator`` artifact of the UI Pack::

    dependencies {
        microejModule("com.microej.pack.ui:ui-pack:14.0.1") {
            artifact {
                name = "imageGenerator"
                extension = "jar"
            }
         }
    }

.. _sdk_6_include_multiple_module_versions:

Include Multiple Versions of a Module
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each dependency of a Module Repository project are resolved separately from the others, 
so you can provide multiple versions of the same module by declaring each dependency with the same configuration. For example, 
the versions of a Library can be provided with::

    dependencies {
        microejModule("org.example:my-library:1.0.0")
        microejModule("org.example:my-library:1.2.0")
        microejModule("org.example:my-library:2.0.0")
    }

.. _sdk6_consistency_check:

Consistency Check
-----------------

The Module Repository consistency check consists in verifying that each declared module can be fetched from the repository.
Especially, it ensures that all module's transitive dependencies are also available.

For example, if your project provides the ``basictool`` library with ``isTransitive = false``, the following error may be raised::

    > The Artifact Checker found the following problems:
          - [x] [retrieve] ej.library.runtime:basictool:1.8.0: Some dependencies are missing from the Module Repository
          > Could not find ej.api:edc:1.3.3.
             Searched in the following locations:
               - <project_path>/build/tmp/checkModule/repository/ej/api/edc/1.3.3/edc-1.3.3.pom
               - <project_path>/build/tmp/checkModule/repository/ej/api/edc/1.3.3/ivy-1.3.3.xml
             Required by:
                 root project : > ej.library.runtime:basictool:1.8.0
          > Could not find ej.api:bon:1.4.0.
             Searched in the following locations:
               - <project_path>/build/tmp/checkModule/repository/ej/api/bon/1.4.0/bon-1.4.0.pom
               - <project_path>/build/tmp/checkModule/repository/ej/api/bon/1.4.0/ivy-1.4.0.xml
             Required by:
               root project : > ej.library.runtime:basictool:1.8.0
    }

To fix this issue, you must define the library with the transitivity enabled::

    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0")
    }

Alternatively, you can explicitly declare the transitive dependencies of the module::

    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0") {
            isTransitive = false
        }
        microejModule("ej.api:edc:1.3.3")
        microejModule("ej.api:bon:1.4.0")
    }

By default, the consistency checker and all checkers supported by the :ref:`sdk6_module_natures.tasks.checkModule` task are executed on a 
the dependencies of a Module Repository project. The checkers can be disabled if needed, for example::

    microej {
        skippedCheckers.set("retrieve, license")
    }

.. note::

   Enabling or disabling a checker is done on all dependencies, it is currently not possible to enable or not a checker on a single module.


.. _sdk_6_build_module_repository:

Build the Repository
--------------------

The Module Repository can be built by executing the Gradle ``buildModuleRepository`` task::

    ./gradlew buildModuleRepository

The repository is generated in ``build/module_repository.zip``.

.. _sdk6_use_module_repository:

Use the Module Repository
-------------------------

When the Module Repository has been created, you can configure your projects to use it:

- Unzip the Module Repository archive at the location of your choice, for example in the ``C:\module-repository`` folder.
- Add the following repositories declaration in :ref:`your repositories configuration script <sdk_6_configure_repositories>`, 
  inside the ``repositories`` block:

.. code:: java

  repositories {

    ...

    maven {
        name = "moduleRepositoryMaven"
        url = uri("C:\\module-repository")
    }
    ivy {
        name = "moduleRepositoryIvy"
        url = uri("C:\\module-repository")
        patternLayout {
            artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
            ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
            setM2compatible(true)
        }
    }

    ...

  }

.. warning::

   A Module Repository built with SDK 6 can be used by SDK 6 projects only. If you need to build a Module Repository for SDK 5 projects, 
   refer to :ref:`module_repository`.

..
   | Copyright 2020-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
