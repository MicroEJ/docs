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

Create a Module Repository Project
----------------------------------

A Module Repository project can be created as follows:

.. tabs::

    .. tab:: IntelliJ IDEA
       
        - Click :guilabel:`File` > :guilabel:`New` > :guilabel:`Project from Version Control...`.
        - Select :guilabel:`Repository URL`.
        - Select :guilabel:`Git` as Version control.
        - Fill the URL of the `Module Repository Project Template <https://github.com/MicroEJ/Tool-Project-Template-Module-Repository>`__ Github Repository.
        - Fill the Directory in which the Project Template must be cloned.
        - Click on :guilabel:`Clone` button.

        .. figure:: images/intellij-version-control-module-repo.png
            :alt: Version Control Window in IntelliJ IDEA
            :align: center
            :scale: 70%

            Version Control Window in IntelliJ IDEA
      
        - When the Gradle project is loaded, rename the project and change its group and version in the ``build.gradle.kts`` build script.
        - Select :guilabel:`View` > :guilabel:`Tool Windows` > :guilabel:`Terminal`.
        - In the integrated terminal, run the following command at the root of the project to remove the Git Repository:

          .. tabs::

             .. tab:: Windows

                .. code-block:: java

                  rm -r -Force .git*


             .. tab:: Linux/macOS

                .. code-block:: java

                  rm -rf .git*

    .. tab:: Android Studio
       
        - Click :guilabel:`File` > :guilabel:`New` > :guilabel:`Project from Version Control...`.
        - Select :guilabel:`Repository URL`.
        - Select :guilabel:`Git` as Version control.
        - Fill the URL of the `Module Repository Project Template <https://github.com/MicroEJ/Tool-Project-Template-Module-Repository>`__ Github Repository.
        - Fill the Directory in which the Project Template must be cloned.
        - Click on :guilabel:`Clone` button.

        .. figure:: images/android-studio-version-control-module-repo.png
            :alt: Version Control Window in Android Studio
            :align: center
            :scale: 70%

            Version Control Window in Android Studio
      
        - When the Gradle project is loaded, rename the project and change its group and version in the ``build.gradle.kts`` build script.
        - Select :guilabel:`View` > :guilabel:`Tool Windows` > :guilabel:`Terminal`.
        - In the integrated terminal, run the following command at the root of the project to remove the Git Repository:

          .. tabs::

             .. tab:: Windows

                .. code-block:: java

                  rm -r -Force .git*


             .. tab:: Linux/macOS

                .. code-block:: java

                  rm -rf .git*

    .. tab:: Eclipse
            
        - Open a new terminal.
        - Clone the `Module Repository Project Template <https://github.com/MicroEJ/Tool-Project-Template-Module-Repository>`__ Github Repository::

             git clone https://github.com/MicroEJ/Tool-Project-Template-Module-Repository.git
      
        - Remove the Git Repository from the project:

          .. tabs::

             .. tab:: Windows

                .. code-block:: java

                  rm -r -Force .git*


             .. tab:: Linux/macOS

                .. code-block:: java

                  rm -rf .git*

        - Rename the project and change its group and version in the ``build.gradle.kts`` build script.
        - In Eclipse, click on :guilabel:`File` > :guilabel:`Import...`.
        - Select the project type :guilabel:`Gradle` > :guilabel:`Existing Gradle Project` and click on the :guilabel:`Next` button.

        .. figure:: images/eclipse-import-gradle-project-01.png
            :alt: Project Type Selection in Eclipse
            :align: center
            :scale: 70%

            Project Type Selection in Eclipse

        - Select the root directory of the project.

        .. figure:: images/eclipse-import-gradle-project-02.png
            :alt: Project root folder in Eclipse
            :align: center
            :scale: 70%

            Project root folder in Eclipse

        - Click on the :guilabel:`Next` button and finally on the :guilabel:`Finish` button.

    .. tab:: Visual Studio Code
       
        - Select :guilabel:`View` > :guilabel:`Command Palette...`.
        - Run the ``Git: Clone`` command in the Command Palette.

        .. figure:: images/vscode-command-palette.png
            :alt: Command Palette in VS Code
            :align: center
            :scale: 70%

            Command Palette in VS Code
      
        - Fill the URI of the `Module Repository Project Template <https://github.com/MicroEJ/Tool-Project-Template-Module-Repository>`__ Github Repository in the Search Bar.
        - Click on :guilabel:`Clone from URL`.

        .. figure:: images/vscode-search-bar-module-repo-template.png
            :alt: Search Bar in VS Code
            :align: center
            :scale: 70%

            Search Bar in VS Code
      
        - In the upcoming popup, choose a folder and click on the ``Select as Repository Destination`` button.
        - When the Gradle project is loaded, rename the project and change its group and version in the ``build.gradle.kts`` build script.
        - Select :guilabel:`Terminal` > :guilabel:`New Terminal`.
        - In the integrated terminal, run the following command at the root of the project to remove the Git Repository:

          .. tabs::

             .. tab:: Windows

                .. code-block:: java

                  rm -r -Force .git*


             .. tab:: Linux/macOS

                .. code-block:: java

                  rm -rf .git*

    .. tab:: Command Line Interface
            
        - Clone the `Module Repository Project Template <https://github.com/MicroEJ/Tool-Project-Template-Module-Repository>`__ Github Repository::

             git clone https://github.com/MicroEJ/Tool-Project-Template-Module-Repository.git
      
        - Remove the Git Repository from the project:

          .. tabs::

             .. tab:: Windows

                .. code-block:: java

                  rm -r -Force .git*


             .. tab:: Linux/macOS

                .. code-block:: java

                  rm -rf .git*

        - Rename the project and change its group and version in the ``build.gradle.kts`` build script.

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

When a dependency is not resolved transitively, you must either explicitly declare its transitive dependencies in your project, 
or configure the Repository as a :ref:`Partial Repository <sdk_6_partial_repository>`.
To ensure that repository users won't have any resolution issues, a :ref:`sdk6_module_repository_check` is enabled by default.

.. warning::

   Only Module dependencies are supported in a Module Repository project. To add a module available as project or included build, 
   you must first publish it to be able to add it to the repository. 

.. _sdk_6_partial_repository:

Configure a Partial Repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A Partial Repository is a Repository which does not contain all the required modules. 
It is designed to complete one or several other repositories.
For example, if you decide to use the MicroEJ Central Repository in addition to your custom Module Repository, 
you can include only the modules not available in the MicroEJ Central Repository.
So if one module depends on ``edc``, you can declare it with:

.. code-block:: kotlin

    dependencies {
        microejModule("com.mycompany:my-lib:1.0.0") {
            isTransitive = false
        }
    }

At resolution time, the ``my-lib`` dependency is resolved from the custom Module Repository and the ``edc`` library is resolved from the MicroEJ Central Repository.

To configure your Module Repository as a Partial Repository, you must create a file named ``module-repository.gradle.kts`` at the root of the Module Repository project.
This file must contain the list of repositories to use at resolution time. 
So it should at least contain the custom Module Repository, and any additional Repository. 
For example if you need to add the MicroEJ Central Repository, the file content should be:

.. code-block:: kotlin

    repositories {
        // Custom Module Repository
        maven {
            name = "moduleRepositoryMaven"
            url = uri(buildscript.sourceFile!!.parentFile)
        }
        ivy {
            name = "moduleRepositoryIvy"
            url = uri(buildscript.sourceFile!!.parentFile)
            patternLayout {
                artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                setM2compatible(true)
            }
        }

        // MicroEJ Central Repository
        maven {
            name = "microEJCentral"
            url = uri("https://repository.microej.com/modules")
        }
        ivy {
            name = "microEJCentralIvy"
            url = uri("https://repository.microej.com/modules")
            patternLayout {
                artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                setM2compatible(true)
            }
        }
    }

This file is directly packaged in the Module Repository archive, 
so it is the one to apply in order to use the custom Module Repository, as explained in :ref:`sdk6_use_offline_module_repository`.
It is also used to :ref:`check the Module Repository consistency <sdk6_use_offline_module_repository>`.

.. warning::

    Do not forget to declare the custom Module Repository, otherwise it won't be used at resolution time.

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

By default, the Production version of an Architecture is not included in a Module Repository.
You can specify to include the Production Architecture in the ``microej`` block of the ``build.gradle.kts`` file:

.. code-block:: kotlin

    microej {
        withArchitectureProductionVersion("com.microej.architecture.CM4.CM4hardfp_GCC48:flopi4G25:8.2.0")
    }

    dependencies {
        microejModule("com.microej.architecture.CM4.CM4hardfp_GCC48:flopi4G25:8.2.0")
    }

.. _sdk_6_exclude_artifacts:

Exclude Artifacts
~~~~~~~~~~~~~~~~~

When a module is added as dependency of a Module Repository project, it is possible to define a list of its artifacts that must be excluded from the Repository.
You can specify the artifacts to exclude in the ``microej`` block of the ``build.gradle.kts`` file.
For example, the sources and javadoc Jar files of an Application can be excluded as follows:

.. code-block:: kotlin

    microej {
        excludeArtifacts("org.example:my-app:1.0.0", "sources,javadoc")
    }

    dependencies {
        microejModule("org.example:my-app:1.0.0")
    }

The following artifacts can be excluded from the Module Repository using the ``excludeArtifacts`` method:

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

Other types of artifacts cannot be excluded using the ``excludeArtifacts`` method. If you want to exclude a specific artifact of a dependency, 
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

.. _sdk_6_include_ivy_descriptors:

Include the Ivy Descriptor of a Module
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Most SDK 6 modules are published with an Ivy descriptor file to ensure that they can be consumed by SDK 5 projects.
By default, this file is not included in a Module Repository, but it is possible to add it by calling the ``withDependenciesIvyDescriptor`` method in 
the ``microej`` block of the ``build.gradle.kts`` file:

.. code-block:: kotlin

    microej {
        withDependenciesIvyDescriptor()
    }

.. _sdk6_module_repository_check:

Module Repository Check
-----------------------

The Module Repository check consists in verifying that each declared module can be fetched from the repository.
Especially, it ensures that all module's transitive dependencies are also available.

For example, if your project provides the ``basictool`` library with ``isTransitive = false``, the following error may be raised::

    > Module Repository check failed
      Some dependencies are missing from the Module Repository
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

The Module Repository check can be run by executing the Gradle ``checkModuleRepository`` task::

    ./gradlew checkModuleRepository

This task is executed by default when :ref:`building a Module Repository <sdk_6_build_module_repository>`. 
It is also possible to disable the Module Repository for a dependency in the ``microej`` block of the ``build.gradle.kts`` file:

.. code-block:: kotlin

    microej {
        skipModuleRepositoryCheck("ej.library.runtime:basictool:1.8.0")
    }

    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0")
    }

If you don't want to check the Module Repository project, you can also :ref:`skip the task <sdk_6_howto_gradle_skip_task>`.

The checkers supported by the :ref:`sdk6_module_natures.tasks.checkModule` task are also executed on all 
dependencies of a Module Repository project by default. The checkers can be enabled or disabled on specific dependencies by calling 
the following methods when declaring a dependency:

.. list-table:: 
   :widths: 25 65
   :header-rows: 1

   * - Name
     - Description
   * - ``microej.runCheckers``
     - This method takes a dependency and a comma-separated list of the names of the checkers to execute as parameters. 
       All checkers are executed by default.
   * - ``microej.skipCheckers``
     - This method takes a dependency and a comma-separated list of the names of the checkers to exclude as parameters. 
       Ignored if the dependency is also used as parameter of the ``runCheckers`` method.

It is possible to enable or disable the checkers of a dependency in the ``microej`` block of the ``build.gradle.kts`` file.
For example:
   
.. code-block:: kotlin

    microej {
        skipCheckers("ej.library.runtime:basictool:1.8.0", "readme,license,changelog")
    }

    dependencies {
        microejModule("ej.library.runtime:basictool:1.8.0")
    }

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

.. _sdk6_use_offline_module_repository:

Use an Offline Module Repository
--------------------------------

When the Module Repository has been created, you can configure your projects to use it:

- Unzip the Module Repository archive at the location of your choice, for example in the ``C:\module-repository`` folder.
- Apply the ``module-repository.gradle.kts`` script found in the Module Repository unzipped folder in the ``build.gradle.kts`` file of your project to declare the repository:

.. code:: kotlin

  apply(file("C:\\module-repository\\module-repository.gradle.kts"))


If your project is a multi-project, the ``module-repository.gradle.kts`` script must be applied in the ``build.gradle.kts`` file at the root of the multi-project to make the repository available 
for all subprojects:

.. code:: kotlin

   allprojects {
        apply(file("C:\\module-repository\\module-repository.gradle.kts"))
   }

..
   | Copyright 2020-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
