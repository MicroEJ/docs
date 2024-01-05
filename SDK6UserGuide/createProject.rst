.. _sdk_6_create_project:

Create a Project
================

This chapter explains the different ways to create a new project.

.. note::
  The different project creation systems do not produce exactly the same project content and structure.
  Especially, the IntelliJ IDEA wizard produces a simple project whereas the Android Studio, Command Line Interface and Eclipse wizards create multi-projects builds.
  Both structures (single and multi projects) can be used, the recommended one depends on the context (components, size of the project, ...).
  Refer to `the official Gradle documentation <https://docs.gradle.org/current/userguide/multi_project_builds.html>`__ for more information.

.. tabs::

   .. tab:: Android Studio

      The creation of a project with Android Studio is done as follows:
      
      - Click on :guilabel:`File` > :guilabel:`New` > :guilabel:`Project...`.
      - Select :guilabel:`Generic` > :guilabel:`New MicroEJ project`.

      .. figure:: images/android-studio-create-project-01.png
         :alt: Project Creation in Android Studio
         :align: center
         :scale: 70%
      
         Project Creation in Android Studio

      - Click on the :guilabel:`Next` button.
      - Fill the name of the project in the :guilabel:`Name` field.
      - Fill the package name of the project in the :guilabel:`Package name` field.
      - Select the location of the project in the :guilabel:`Save location` field.
      - Select :guilabel:`Kotlin` for the :guilabel:`Build configuration language` field.
      
      .. note::
        The SDK uses Kotlin as the default Gradle build script DSL. 
        The use of the Groovy build script DSL is still possible but not officially supported.
            
      .. figure:: images/android-studio-create-project-02.png
         :alt: Project Creation in Android Studio
         :align: center
         :scale: 70%
      
         Project Creation in Android Studio
      
      - Click on :guilabel:`Next` button.
      - Fill the group of the artifact to publish in the :guilabel:`Group` field.
      - Fill the version of the artifact to publish in the :guilabel:`Version` field.
      - Select the module type among :guilabel:`Application` and :guilabel:`Addon-Library` in the drop-down list.
      - If you selected :guilabel:`Application` module type, you can check :guilabel:`This is a kernel application` checkbox if your Application is a Kernel.
      - Click on :guilabel:`Finish` button.
      
      .. figure:: images/android-studio-create-project-03.png
         :alt: Project Creation in Android Studio
         :align: center
         :scale: 70%
      
         Project Creation in Android Studio
      
      - Change the view from :guilabel:`Android` to :guilabel:`Project` in the selectbox at the top of the project's files tree:
      
      .. figure:: images/android-studio-create-project-04.png
         :alt: Project View in Android Studio
         :align: center
         :scale: 70%
      
         Project View in Android Studio

      .. note::
         The newly created Gradle project uses Gradle Wrapper with Gradle version ``8.2``.
         Refer to the :ref:`sdk_6_create_project_gradle_wrapper` section for more information.

      The project created by the wizard is a multi-project with a single subproject (named ``app``).
      This subproject is a MicroEJ Application or Add-On Library, depending on the module type that has been chosen.

      .. note::
         By default, Android Studio automatically saves any file change, 
         but requires the user to explicitly trigger the reload of a Gradle project when its configuration has changed.
         Therefore, when the configuration of a Gradle project has been updated, 
         you have to click on the :guilabel:`Sync Now` action which appears on the top-right of the editor:

         .. figure:: images/android-studio-reload-gradle-project.png
            :alt: Gradle Project reload in Android Studio
            :align: center
            :scale: 70%
      
            Gradle Project reload in Android Studio
        
         You can also configure Android Studio to automatically reload a Gradle project after a change.
         Refer to the :ref:`sdk_6_howto_gradle_autoreloading` section for more information.
      
      .. warning::
       When reloading your Gradle project, the build can fail if the SDK EULA has not been accepted.
       In that case, you must set the ``ACCEPT_MICROEJ_SDK_EULA_V3_1B`` environment variable to ``YES`` and
       restart Android Studio. For more information about SDK EULA, refer to the :ref:`sdk_6_licenses` chapter.

      When the Gradle project has been reloaded, it should compile successfully, without any error.
      You can then learn :ref:`how to launch the build of the project <sdk_6_build_project>`, 
      or :ref:`how to run it on the Simulator <sdk_6_run_on_simulator>` in the case of an Application.

   .. tab:: IntelliJ IDEA

      The creation of a project with IntelliJ IDEA is done as follows:
      
      - Click on :guilabel:`File` > :guilabel:`New` > :guilabel:`Project...`.
      - Select :guilabel:`MicroEJ` in :guilabel:`Generators` list on the left panel.
      - Fill the name of the project in the :guilabel:`Name` field.
      - Select the location of the project in the :guilabel:`Location` field.
      - Select the module type among :guilabel:`Application`, :guilabel:`Addon-Library` and :guilabel:`J2SE Library` buttons.
      - If you selected :guilabel:`Application` module type, you can check :guilabel:`This is a kernel application` checkbox if your Application is a Kernel.
      - Fill the version of the artifact to publish in the :guilabel:`Version` field.
      - Fill the group of the artifact to publish in the :guilabel:`Group` field.
      - Fill the name of the artifact to publish in the :guilabel:`Artifact` field.
      - Select the JVM used by Gradle in the :guilabel:`JDK` combobox.
      - Check the :guilabel:`Add sample code` checkbox.
      - Click on :guilabel:`Create` button.
      
      .. figure:: images/intellij-create-microej-project.png
         :alt: Project Creation in IntelliJ IDEA
         :align: center
         :scale: 70%
      
         Project Creation in IntelliJ IDEA

      .. note::
         The Gradle project created by the wizard uses Gradle Wrapper with Gradle version ``8.5``.
         Refer to the :ref:`sdk_6_create_project_gradle_wrapper` section for more information.

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

         You can also configure IntelliJ IDEA to automatically reload a Gradle project after a change.
         Refer to the :ref:`sdk_6_howto_gradle_autoreloading` section for more information.
      
      .. warning::
       When reloading your Gradle project, the build can fail if the SDK EULA has not been accepted.
       In that case, you must set the ``ACCEPT_MICROEJ_SDK_EULA_V3_1B`` environment variable to ``YES`` and
       restart IntelliJ IDEA. For more information about SDK EULA, refer to the :ref:`sdk_6_licenses` chapter.

      When the Gradle project is loaded, it should compile successfully, without any error.
      You can then learn :ref:`how to launch the build of the project <sdk_6_build_project>`, 
      or :ref:`how to run it on the Simulator <sdk_6_run_on_simulator>` in the case of an Application.

   .. tab:: Eclipse

      The creation of a project with Eclipse is done as follows:
      
      - Click on :guilabel:`File` > :guilabel:`New` > :guilabel:`Project...`.
      - Select the project type :guilabel:`Gradle` > :guilabel:`Gradle Project` and click on the :guilabel:`Next` button.
      
      .. figure:: images/eclipse-create-gradle-project-01.png
        :alt: Project Type Selection in Eclipse
        :align: center
        :scale: 70%
      
        Project Type Selection in Eclipse
      
      - Fill the name of the project in the :guilabel:`Name` field, for example ``myProject``, and click on the :guilabel:`Next` button.
      
      .. figure:: images/eclipse-create-gradle-project-02.png
        :alt: Project root folder in Eclipse
        :align: center
        :scale: 70%
      
        Project root folder in Eclipse
      
      - In the :guilabel:`Options` screen, leave the default values and click on the :guilabel:`Next` button.
      - Click on the :guilabel:`Next` button and finally on the :guilabel:`Finish` button.
      
      The SDK is only compatible with the Gradle version ``8.0.2`` or higher, so ensure that the project uses the right version :
      
      - Open the ``myProject/gradle/wrapper/gradle-wrapper.properties`` file.
      - Update the Gradle version if it is needed:
      
         .. code-block::
          
            distributionUrl=https\://services.gradle.org/distributions/gradle-8.0.2-bin.zip
      
      If you want to know more about the Gradle Wrapper, go to the :ref:`sdk_6_create_project_gradle_wrapper` section.
      
      The project created by Eclipse is a standard Java Library project (Gradle ``java-library`` plugin). 
      The ``build.gradle`` file has to be renamed and updated to make it a MicroEJ project:
      
      - Rename the ``build.gradle`` file to ``build.gradle.kts`` and open it.
      - Erase its whole content.
      - Add the MicroEJ plugin, depending on the module nature you want to build, for example for an Add-On Library::
      
          plugins {
              id("com.microej.gradle.addon-library") version "0.14.0"
          }
      
        or for an Application::
      
          plugins {
              id("com.microej.gradle.application") version "0.14.0"
          }
      
        .. note::
          The ``java-library`` plugin must not be added since it is automatically applied by the MicroEJ plugin.
      
        Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.
      
      - Declare the dependencies required by your project in the ``dependencies`` block. For example::
      
          dependencies {
              implementation("ej.api:edc:1.3.5")
          }
      
      - Delete the test class in the folder ``lib/src/test/java``.
      
      The ``settings.gradle`` file has to be renamed and updated as well:
      
      - Rename the ``settings.gradle`` file to ``settings.gradle.kts`` and open it.
      - Erase its whole content.
      - Add the following content::
      
          rootProject.name = "myProject"
          include("lib")
      
      .. note::
         By default, Eclipse requires the user to explicitly trigger the reload of a Gradle project when its content has changed.
         Therefore, when the content of a Gradle project has been updated, 
         you have to right-click on the project, then click on :guilabel:`Gradle` and :guilabel:`Refresh Gradle Project`:
      
         .. figure:: images/eclipse-reload-gradle-project.png
            :alt: Gradle Project reload in Eclipse
            :align: center
            :scale: 70%
      
            Gradle Project reload in Eclipse
        
         You can also configure Eclipse to automatically reload a Gradle project after a change.
         Refer to the :ref:`sdk_6_howto_gradle_autoreloading` section for more information.
      
      .. warning::
       When reloading your Gradle project, the build can fail if the SDK EULA has not been accepted.
       In that case, you must set the ``ACCEPT_MICROEJ_SDK_EULA_V3_1B`` environment variable to ``YES`` and
       restart Eclipse. For more information about SDK EULA, refer to the :ref:`sdk_6_licenses` chapter.
      
      When the Gradle project has been reloaded, it should compile successfully, without any error.
      You can then learn :ref:`how to launch the build of the project <sdk_6_build_project>`, 
      or :ref:`how to run it on the Simulator <sdk_6_run_on_simulator>` in the case of an Application.

   .. tab:: Command Line Interface

      The creation of a project can be done via the command line interface via the Gradle ``init`` task.
      This task guides you through multiple steps to configure and select the project template to use.
      Refer to `the official documentation <https://docs.gradle.org/current/userguide/build_init_plugin.html>`__ for the full list of templates and options.
      
      In order to create a MicroEJ project, the best way is to use the ``application`` template:
      
      - In a new empty directory, execute the command ``gradle init``.
      - Select the ``application`` project type.
      - Select the ``Java`` implementation language.
      - For the step ``Generate multiple subprojects for application?``, select ``no``.
      - Select build script DSL ``Kotlin``.
      
      .. note::
        The SDK uses Kotlin as the default Gradle build script DSL. 
        The use of the Groovy build script DSL is still possible but not officially supported.
      
      - For the test framework, select ``JUnit 4``.
      - Choose the name of the project (defaults to the name of the parent directory).
      - Choose the package name for the source files.
      - For the target version of Java, select ``7``.
      - Decide if you want to use Gradle new APIs and behavior in your build script.
        If you are new to Gradle, choose ``no``.
      
      .. note::
        These steps are the ones proposed when creating a project with Gradle ``8.2.1``. 
        Depending on the Gradle version used, the steps to create a project can be slightly different.
      
      The created project is a multi-project build containing a root project and a single subproject (named ``app``).
      The ``app`` subproject is a standard Java Application project (Gradle ``java`` plugin),
      so it must be updated to be a MicroEJ project:
      
      - Open the project in your favorite editor.
      - Open the ``app/build.gradle.kts`` file.
      - Erase its whole content.
      - :ref:`Configure the project <sdk_6_create_project_configure_project>` depending on the module nature you want to build.
      - Declare the dependencies required by your project in the ``dependencies`` block. For example::
      
            dependencies {
                implementation("ej.api:edc:1.3.5")
            }
      
      - Delete the test class in the folder ``app/src/test/java``.

.. _sdk_6_create_project_configure_project:

Configure a Project
-------------------

The SDK allows to build several types of modules.
Each type has its own Gradle plugin and configuration options.
Refer to the module type you want to build to configure your project:

- :ref:`Application <sdk_6_create_project_configure_application>`
- :ref:`Add-On Library <sdk_6_create_project_configure_addon_library>`
- :ref:`J2SE Library <sdk_6_create_project_configure_j2se_library>`


.. _sdk_6_create_project_configure_application:

Application Project
~~~~~~~~~~~~~~~~~~~

- Add the ``com.microej.gradle.application`` plugin in the ``build.gradle.kts`` file::

    plugins {
        id("com.microej.gradle.application") version "0.14.0"
    }

  .. note::
    The ``java`` plugin must not be added since it is automatically applied by the MicroEJ plugin.

- If your Application is a Standalone Application:

  - Create the Java main class in the ``src/main/java`` folder.
  - Define the property ``applicationMainClass`` in the ``microej`` configuration block of the ``build.gradle.kts`` file.
    It must be set to the Full Qualified Name of the Application main class, for example::

      microej {
        applicationMainClass = "com.mycompany.Main"
      }

- If your Application is a Kernel Application:

  - Create the Java main class in the ``src/main/java`` folder.
  - Define the property ``applicationMainClass`` in the ``microej`` configuration block of the ``build.gradle.kts`` file.
    It must be set to the Full Qualified Name of the Application main class, for example::

      microej {
        applicationMainClass = "com.mycompany.Main"
      }

  - Create a file named ``kernel.kf`` in the ``src/main/resources`` folder.
    This file is a property file which must contain at least the ``version`` property, 
    and optionally the ``name`` property (defaults to ``KERNEL``), for example::

      version=1.0.0
      name=MY-KERNEL

- If your Application is a :ref:`Sandboxed Application <sandboxed_application>`:

  - Create the Java class of the Feature Entry Point in the ``src/main/java`` folder, for example:

    .. code:: java
            
      package com.mycompany;
      
      import ej.kf.FeatureEntryPoint;
      
      public class MyApplication implements FeatureEntryPoint {
    
        @Override
        public void start() {
          System.out.println("Feature MyApplication started!");
        }
    
        @Override
        public void stop() {
          System.out.println("Feature MyApplication stopped!");
        }
      }

  - Create a file with the extension ``.kf`` in the ``src/main/resources`` folder, for example ``MyApplication.kf``.
    This file must at least contain the property ``entryPoint`` set to the Full Qualified Name of the Application Feature class, for example::

      entryPoint=com.mycompany.MyApplication
      version=0.1.0

Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

.. _sdk_6_create_project_configure_addon_library:

Add-On Library Project
~~~~~~~~~~~~~~~~~~~~~~

- Add the ``com.microej.gradle.addon-library`` plugin in the build script::

    plugins {
        id("com.microej.gradle.addon-library") version "0.14.0"
    }

  .. note::
    The ``java`` plugin must not be added since it is automatically applied by the MicroEJ plugin.

Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

.. _sdk_6_create_project_configure_j2se_library:

J2SE Library Project
~~~~~~~~~~~~~~~~~~~~

- Add the ``com.microej.gradle.j2se-library`` plugin in the build script::

    plugins {
        id("com.microej.gradle.j2se-library") version "0.14.0"
    }

  .. note::
    The ``java`` plugin must not be added since it is automatically applied by the MicroEJ plugin.

Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

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
