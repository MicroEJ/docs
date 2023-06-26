.. _sdk_6_create_project:

Create a Project
================

This chapter explains the different ways to create a new project.

.. note::
  The different project creation systems do not produce exactly the same project content and structure.
  Especially, the IntelliJ IDEA wizard produces a simple project whereas the CLI and Eclipse wizards create multi-projects builds.
  Both structures (single and multi projects) can be used, the recommended one depends on the context (components, size of the project, ...).
  Refer to `the official Gradle documentation <https://docs.gradle.org/current/userguide/multi_project_builds.html>`__ for more information.

.. _sdk_6_create_project_cli:

Command Line Interface
----------------------

The creation of a project can be done via the command line interface via the Gradle ``init`` task.
This task guides you through multiple steps to configure and select the project template to use.
Refer to `the official documentation <https://docs.gradle.org/current/userguide/build_init_plugin.html>`__ for the full list of templates and options.

In order to create a MicroEJ project, the best way is to use the ``application`` template:

- In a new empty directory, execute the command ``gradle init``.
- Select the ``application`` project type.
- Select the ``Java`` implementation language.
- For the step ``Split functionality across multiple subprojects?``, select ``no``.
- Select build script DSL ``Kotlin``.

.. note::
  MicroEJ uses Kotlin as the default Gradle build script DSL. 
  The use of the Groovy build script DSL is still possible but not officially supported.

- Decide if you want to use Gradle new APIs and behavior in your build script.
  If you are new to Gradle, choose ``no``.
- For the test framework, select ``JUnit 4``.
- Choose the name of the project (defaults to the name of the parent directory).
- Choose the package name for the source files.

.. note::
  These steps are the ones proposed when creating a project with Gradle ``8.0.2``, which is the minimum version required by the SDK. 
  Depending on the Gradle version used, the steps to create a project can be slightly different.

The created project is a multi-project build containing a root project and a single subproject (named ``app``).
The ``app`` subproject is a standard Java Application project (Gradle ``java`` plugin),
so it must be updated to be a MicroEJ project:

- Open the project in your favorite editor.
- Open the ``app/build.gradle.kts`` file.
- Erase its whole content.
- Add the MicroEJ plugin, depending on the module nature you want to build, for example for an Add-On Library::

    plugins {
        id("com.microej.gradle.addon-library") version "0.7.0"
    }

  or for an Application::

    plugins {
        id("com.microej.gradle.application") version "0.7.0"
    }

  .. note::
    The ``java`` plugin must not be added since it is automatically applied by the MicroEJ plugin.

  Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

- Declare the dependencies required by your project in the ``dependencies`` block. For example::

      dependencies {
          implementation("ej.api:edc:1.3.5")
      }

- Delete the test class in the folder ``app/src/test/java``.

Eclipse
-------

.. warning::
   Only the IntelliJ IDEA IDE is fully supported for the moment, so it is recommend to use it instead of Eclipse.
   The support of Eclipse will come soon. 

..
  The creation of a project with Eclipse is done as follows:

  - Click on ``File`` > ``New`` > ``Project...``.
  - Select the project type ``Gradle > Gradle Project`` and click on the ``Next`` button.

  .. figure:: images/eclipse-create-gradle-project-01.png
    :alt: Project Type Selection in Eclipse
    :align: center
    :scale: 70%

    Project Type Selection in Eclipse

  - Fill the name of the project in the ``Name`` field and click on the ``Next`` button.

  .. figure:: images/eclipse-create-gradle-project-02.png
    :alt: Project root folder in Eclipse
    :align: center
    :scale: 70%

    Project root folder in Eclipse

  - In the ``Options`` screen, leave the default values and click on the ``Next`` button.
  - Click on the ``Next`` button and finally on the ``Finish`` button.

    

  The project created by Eclipse is a multi-project build containing a root project and a single subproject (named ``lib``).
  The ``lib`` subproject is a standard Java Library project (Gradle ``java-library`` plugin).
  The ``build.gradle.kts`` file of the ``lib`` subproject has to be updated to make it a MicroEJ project:

  ...

  **OR**

The Eclipse creation wizard for Gradle Project is quite limited, 
and produces a multi-project build with a Java Library subproject (Gradle ``java-library`` plugin).
It requires several modifications to make it a MicroEJ project.
Therefore, the recommended way to create a project is to use the :ref:`Gradle CLI <sdk_6_create_project_cli>`,
then to :ref:`import the project in Eclipse <sdk_6_import_project_eclipse>`.


IntelliJ IDEA
-------------

The creation of a project with IntelliJ IDEA is done as follows:

- Click on ``File`` > ``New`` > ``Project...``.
- Fill the name of the project in the ``Name`` field.
- Select the location of the project in the ``Location`` field.
- Select the language ``Java`` in the ``Language`` field.
- Select ``Gradle`` for the ``Build system`` field.
- Select build script DSL ``Kotlin``.

.. note::
  MicroEJ uses Kotlin as the default Gradle build script DSL. 
  The use of the Groovy build script DSL is still possible but not officially supported.

- Check the ``Add sample code`` checkbox.
- Click on ``Create`` button.

.. figure:: images/intellij-create-gradle-project.png
   :alt: Project Creation in IntelliJ IDEA
   :align: center
   :scale: 70%

   Project Creation in IntelliJ IDEA

The project created by IntelliJ IDEA is a standard Java project (Gradle ``java`` plugin). 
The SDK is only compatible with the Gradle version ``8.0.2`` or higher, so ensure that the project uses the right version :

- Open the ``gradle/wrapper/gradle-wrapper.properties`` file.
- Update the Gradle version if it is needed:

   .. code-block::
    
      distributionUrl=https\://services.gradle.org/distributions/gradle-8.0.2-bin.zip

If you want to know more about the Gradle Wrapper, go to the :ref:`sdk_6_create_project_gradle_wrapper` section.
  

The ``build.gradle.kts`` file has to be updated to make it a MicroEJ project:

- Open the ``build.gradle.kts`` file.
- Erase its whole content.
- Add the MicroEJ plugin, depending on the module nature you want to build, for example for an Add-On Library::

    plugins {
        id("com.microej.gradle.addon-library") version "0.7.0"
    }

  or for an Application::

    plugins {
        id("com.microej.gradle.application") version "0.7.0"
    }

  .. note::
    The ``java`` plugin must not be added since it is automatically applied by the MicroEJ plugin.

  Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

- Declare the dependencies required by your project in the ``dependencies`` block. For example::

      dependencies {
          implementation("ej.api:edc:1.3.5")
      }

.. note::
   By default, IntelliJ IDEA automatically saves any file change, 
   but requires the user to explicitly trigger the reload of a Gradle project when its configuration has changed.
   Therefore, when the configuration of a Gradle project has been updated, 
   you have to click on the reload icon button which appears on the right of the editor:

   .. figure:: images/intellij-reload-gradle-project.png
      :alt: Gradle Project reload in IntelliJ IDEA
      :align: center
      :scale: 70%

      Gradle Project reload in IntelliJ IDEA

When the Gradle project has been reloaded, it should compile successfully, without any error.
You can then learn :ref:`how to launch the build of the project <sdk_6_build_project>`, 
or :ref:`how to run it on the Simulator <sdk_6_run_on_simulator>` in the case of an Application.

.. note::
   A message ``Project JDK is not defined`` is displayed at the top of the editor.
   This message can be ignored.
   It warns that the project does not have a JDK defined, which is expected since a MicroEJ project does not rely on a standard JDK.

   .. figure:: images/intellij-project-sdk-message.png
      :alt: Project JDK message in IntelliJ IDEA
      :align: center
      :scale: 70%

      Project JDK message in IntelliJ IDEA

.. _sdk_6_create_project_gradle_wrapper:

Gradle Wrapper
--------------

It is recommended to use the Gradle Wrapper to execute a build.
The Wrapper is a script that ensures that the required version of Gradle is downloaded and used during the build of a project.

When creating a project following one of the project creation systems described in the :ref:`sdk_6_create_project` section, 
the Wrapper files are automatically generated in the ``gradle/wrapper`` folder of the project.
It is also possible to add the Wrapper to an existing project by executing the ``wrapper`` task::

  gradle wrapper

The Gradle version used by the project can then be updated in the ``gradle/wrapper/gradle-wrapper.properties`` file. 
The SDK requires Gradle ``8.0.2`` or higher::

  distributionUrl=https\://services.gradle.org/distributions/gradle-8.0.2-bin.zip

To use the Wrapper during a build, use ``gradlew`` or ``./gradlew`` depending on your OS instead of ``gradle`` in the command line:

.. tabs::

   .. tab:: Windows

      gradlew build

   .. tab:: Linux

      ./gradlew build

In the following chapters of the documentation, the Linux command ``./gradlew`` is used in all examples to execute a build.

Refer to `the official Gradle documentation <https://docs.gradle.org/current/userguide/gradle_wrapper.html>`__ for more information about the Wrapper.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
