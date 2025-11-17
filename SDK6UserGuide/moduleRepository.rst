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
which is itself built by MicroEJ Corp. as a Module Repository.

.. _sdk_6_create_module_repository_project:

Create a Repository Project
---------------------------

A Module Repository project can be created as follows:

- Open a new Terminal.
- Create a new ``module-repository`` folder in the directory of your choice and go into this folder: ``cd module-repository``.
- Run ``gradle init`` command.
- Select ``Basic`` as type of build to generate.
- Enter the project's name of your choice.
- Select ``Kotlin`` as build script DSL.
- Enter ``no`` when asked to generate build using new APIs and behavior.
- Once the project is created, you can :ref:`import it <sdk_6_import_project>` in the IDE of your choice.
- In the ``build.gradle.kts`` file of the project, apply the ``module-repository`` plugin and define the group and the version of the project:

.. code-block:: kotlin

    plugins {
        id("com.microej.gradle.module-repository") version "1.5.0"
    }

    group = "org.example"
    version = "0.1.0-RC"

.. _sdk_6_include_modules:

Include Modules
---------------

Modules bundled into the Module Repository must be declared as dependencies of the project. A dependency is declared with the  ``microejModule`` configuration:

.. code-block:: kotlin

    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0")
    }

By default, a dependency is resolved transitively but it is possible to not fetch its transitive dependencies by specifying it in the dependency's declaration:

.. code-block:: kotlin

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
For example, to only fetch the Virtual Device of a Kernel, you must add the ``zip`` extension in the dependency:

.. code-block:: kotlin

    dependencies {
        microejModule("org.example:my-kernel:1.0.0@zip")
    }

You can also specify the name, type, extension or classifier of the artifact if they differ from the module. For example, 
declare the following dependency to fetch the ``imageGenerator`` artifact of the UI Pack:

.. code-block:: kotlin

    dependencies {
        microejModule("com.microej.pack.ui:ui-pack:14.0.1") {
            artifact {
                name = "imageGenerator"
                extension = "jar"
            }
        }
    }

It is also possible to include several artifacts in the same dependency, for example:

.. code-block:: kotlin

    dependencies {
        microejModule("com.microej.pack.ui:ui-pack:14.0.1") {
            artifact {
                name = "imageGenerator"
                extension = "jar"
            }
            artifact {
                name = "imageGenerator"
                classifier = "sources"
                extension = "jar"
            }
            artifact {
                name = "frontpanel"
                extension = "jar"
            }
        }
    }

.. _sdk6_include_production_architectures:

Include Production Architectures
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, the Production version of an Architecture is not included in a Module Repository. If you want to include it,
the ``microej.withArchitectureProductionVersion`` method must be called when declaring the Architecture as dependency:

.. code-block:: kotlin

    dependencies {
        microejModule("com.microej.architecture.CM4.CM4hardfp_GCC48:flopi4G25:8.2.0")?.let {
            microej.withArchitectureProductionVersion(it)
        }
    }

.. note::

   It is also possible to include the Production Architecture in the ``microej`` block of the ``build.gradle.kts`` file:

    .. code-block:: kotlin

        microej {
            withArchitectureProductionVersion("com.microej.architecture.CM4.CM4hardfp_GCC48:flopi4G25:8.2.0")
        }

        dependencies {
            microejModule("com.microej.architecture.CM4.CM4hardfp_GCC48:flopi4G25:8.2.0")
        }
        
   But this solution requires duplicating the dependency and the related information is scattered throughout the ``build.gradle.kts`` file,
   so it is recommended to include the Production Architecture in the dependency's declaration.

.. _sdk_6_exclude_artifacts:

Exclude Artifacts
~~~~~~~~~~~~~~~~~

When a module is added as dependency of a Module Repository project, it is possible to define a list of its artifacts that must be excluded from the Repository.
To exclude artifacts, the ``microej.excludeArtifacts`` method must be called when declaring the dependency. For example, 
the sources and javadoc Jar files of an Application can be excluded as follows:

.. code-block:: kotlin

    dependencies {
        microejModule("org.example:my-app:1.0.0")?.let {
            microej.excludeArtifacts(it, "sources,javadoc")
        }
    }

For dependencies which are not resolved transitively, the ``microej.excludeArtifacts`` method is called after the dependency's block:

.. code-block:: kotlin

    dependencies {
        microejModule("org.example:my-app:1.0.0") {
            isTransitive = false
        }.let {
            microej.excludeArtifacts(it, "sources,javadoc")
        }
    }

.. note::

   It is also possible to exclude the artifacts of a dependency in the ``microej`` block of the ``build.gradle.kts`` file:

    .. code-block:: kotlin

        microej {
            excludeArtifacts("org.example:my-app:1.0.0", "sources,javadoc")
        }

        dependencies {
            microejModule("org.example:my-app:1.0.0")
        }
        
   But this solution requires duplicating the dependency and the related information is scattered throughout the ``build.gradle.kts`` file,
   so it is recommended to exclude the artifacts in the dependency's declaration.

The following artifacts can be excluded from the Module Repository using the ``microej.excludeArtifacts`` method:

.. list-table:: 
   :widths: 25 65
   :header-rows: 1

   * - Name
     - Description
   * - ``sources``
     - Exclude the sources Jar file of a Java module. 
   * - ``javadoc``
     - Exclude the javadoc Jar file of a Java module.
   * - ``application-wpk``
     - Exclude the WPK of an Application.
   * - ``executable``
     - Exclude the Executable of an Application.
   * - ``virtual-device``
     - Exclude the Virtual Device of an Application.
   * - ``runtime-environment-api``
     - Exclude the Runtime API jar file of a Runtime Environment.
   * - ``evaluation-architecture``
     - Exclude the Evaluation version of an Architecture.

Other types of artifacts cannot be excluded using the ``microej.excludeArtifacts`` method. If you want to exclude a specific artifact of a dependency, 
you must explicitly declare all artifacts of the dependency which must be :ref:`included in the Repository<sdk_6_include_single_artifact>`.

.. _sdk_6_include_multiple_module_versions:

Include Multiple Versions of a Module
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each dependency of a Module Repository project are resolved separately from the others, 
so you can provide multiple versions of the same module by declaring each dependency with the same configuration. For example, 
the versions of a Library can be provided with:

.. code-block:: kotlin

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

To fix this issue, you must define the library with the transitivity enabled:

.. code-block:: kotlin

    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0")
    }

Alternatively, you can explicitly declare the transitive dependencies of the module:

.. code-block:: kotlin

    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0") {
            isTransitive = false
        }
        microejModule("ej.api:edc:1.3.3")
        microejModule("ej.api:bon:1.4.0")
    }

By default, the consistency checker and all other checkers supported by the :ref:`sdk6_module_natures.tasks.checkModule` task are executed on all 
dependencies of a Module Repository project. The checkers can be enabled or disabled on specific dependencies by calling 
the following methods when declaring the dependency:

.. list-table:: 
   :widths: 25 65
   :header-rows: 1

   * - Name
     - Description
   * - ``runCheckers``
     - This method takes a dependency and a comma-separated list of the names of the checkers to execute as parameters. 
       All checkers are executed by default.
   * - ``skipCheckers``
     - This method takes a dependency and a comma-separated list of the names of the checkers to exclude as parameters. 
       Ignored if the dependency is also used as parameter of the ``runCheckers`` method.

For example:

.. code-block:: kotlin
    
    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0")?.let {
            microej.runCheckers(it, "readme,license,changelog")
        }
        microejModule("ej.api:edc:1.3.3")?.let {
            microej.skipCheckers(it, "changelog,retrieve")
        }
    }

For dependencies which are not resolved transitively, the methods are called after the dependency's block:

.. code-block:: kotlin
    
    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0") {
            isTransitive = false
        }.let {
            microej.runCheckers(it, "readme,license,changelog")
        }
    }

.. note::

   It is also possible to enable or disable the checkers of a dependency in the ``microej`` block of the ``build.gradle.kts`` file:

    .. code-block:: kotlin

        microej {
            skipCheckers("ej.library.runtime:basictool:1.8.0", "readme,license,changelog")
        }

        dependencies {
            microejModule("ej.library.runtime:basictool:1.8.0")
        }
        
   But this solution requires duplicating the dependency and the related information is scattered throughout the ``build.gradle.kts`` file,
   so it is recommended to configure the checkers in the dependency's declaration.


The properties provided by the :ref:`sdk6_module_natures.tasks.checkModule` task can also be used but they are applied on the project 
itself, not its dependencies. For example, the Readme checker is skipped on the project but it is executed on the dependencies if the following 
property is defined::

    microej {
        skippedCheckers.set("readme")
    }

.. _sdk_6_build_module_repository:

Build the Repository
--------------------

The Module Repository can be built by executing the Gradle ``buildModuleRepository`` task::

    ./gradlew buildModuleRepository

The repository is generated in ``build/libs/<project_name>.zip``.

.. _sdk6_use_module_repository:

Use the Module Repository
-------------------------

When the Module Repository has been created, you can configure your projects to use it:

- Unzip the Module Repository archive at the location of your choice, for example in the ``C:\module-repository`` folder.
- Add the following repositories declaration in :ref:`your repositories configuration script <sdk_6_configure_repositories>`, 
  inside the ``repositories`` block:

.. code:: kotlin

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
