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
      - Keep the default Android SDK in the :guilabel:`Minimum SDK` field.
      - Select :guilabel:`Kotlin` for the :guilabel:`Build configuration language` field.
      
      .. note::
        Groovy build script DSL is not officially supported by the SDK, so the project created by the Wizard uses Kotlin regardless
        of the language selected by the user.
            
      .. figure:: images/android-studio-create-project-02.png
         :alt: Project Creation in Android Studio
         :align: center
         :scale: 70%
      
         Project Creation in Android Studio
      
      - Click on :guilabel:`Next` button.
      - Fill the group of the artifact to publish in the :guilabel:`Group` field.
      - Fill the version of the artifact to publish in the :guilabel:`Version` field.
      - Select the module type among :guilabel:`Application`, :guilabel:`Mock` and :guilabel:`Addon-Library` in the drop-down list.
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
         If you do not use the last version of Android Studio, make sure that Gradle Wrapper uses at least Gradle version ``8.6``.
         Refer to the :ref:`sdk_6_create_project_gradle_wrapper` section for more information.

      The project created by the wizard is a multi-project with a single subproject (named ``app``).
      This subproject is either an Application or an Add-On Library, depending on the module type that has been chosen.

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
       In that case, you must set the ``ACCEPT_MICROEJ_SDK_EULA_V3_1C`` environment variable to ``YES`` and
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
      - Select the module type among :guilabel:`Application`, :guilabel:`Mock` and :guilabel:`Addon-Library` buttons.
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
         The Gradle project created by the wizard uses Gradle Wrapper with Gradle version ``8.10.2``.
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
       In that case, you must set the ``ACCEPT_MICROEJ_SDK_EULA_V3_1C`` environment variable to ``YES`` and
       restart IntelliJ IDEA. For more information about SDK EULA, refer to the :ref:`sdk_6_licenses` chapter.

      When the Gradle project is loaded, it should compile successfully, without any error.
      You can then learn :ref:`how to launch the build of the project <sdk_6_build_project>`, 
      or :ref:`how to run it on the Simulator <sdk_6_run_on_simulator>` in the case of an Application.

   .. tab:: Eclipse

      The creation of a project with Eclipse is done as follows:
      
      - Click on :guilabel:`File` > :guilabel:`New` > :guilabel:`Project...`.
      - Select the project type :guilabel:`MicroEJ` > :guilabel:`MicroEJ Application Project`, :guilabel:`MicroEJ Mock` or :guilabel:`MicroEJ Add-onLibrary Project` and click on the :guilabel:`Next` button.
      
      .. figure:: images/eclipse-create-microej-project-01.png
        :alt: Project Type Selection in Eclipse
        :align: center
        :scale: 70%
      
        Project Type Selection in Eclipse
      
      - Fill the name of the project in the :guilabel:`Name` field, for example ``My Project``.
      - Fill the group of the artifact to publish in the :guilabel:`Organization` field.
      - Fill the name of the artifact to publish in the :guilabel:`Module` field.
      - Fill the version of the artifact to publish in the :guilabel:`Revision` field.
      - If you selected :guilabel:`Application` module type, you can check :guilabel:`This is a kernel application` checkbox if your Application is a Kernel.
      - Click on :guilabel:`Finish` button.
      
      .. figure:: images/eclipse-create-microej-project-02.png
        :alt: Project root folder in Eclipse
        :align: center
        :scale: 70%
      
        Application Creation in Eclipse
      
      .. note::
         The Gradle project created by the wizard uses Gradle Wrapper with Gradle version ``8.10.2``.
         Refer to the :ref:`sdk_6_create_project_gradle_wrapper` section for more information.

      .. warning::
       When reloading your Gradle project, the build can fail if the SDK EULA has not been accepted.
       In that case, you must set the ``ACCEPT_MICROEJ_SDK_EULA_V3_1C`` environment variable to ``YES`` and
       restart Eclipse. For more information about SDK EULA, refer to the :ref:`sdk_6_licenses` chapter.

      When the Gradle project is loaded, it should compile successfully, without any error.
      You can then learn :ref:`how to launch the build of the project <sdk_6_build_project>`, 
      or :ref:`how to run it on the Simulator <sdk_6_run_on_simulator>` in the case of an Application.

   .. tab:: Visual Studio Code
 
      The creation of a project with Visual Studio Code is done as follows:
      
      - Select :guilabel:`View` > :guilabel:`Command Palette...`.
      - Run the ``Git: Clone`` command in the Command Palette.
      
      .. figure:: images/vscode-command-palette.png
        :alt: Command Palette in VS Code
        :align: center
        :scale: 70%
      
        Command Palette in VS Code
      
      - Depending on the type of your project, fill the URI of the corresponding Github template repository in the Search Bar. 
        The available templates are:
      
         - `Application Project Template <https://github.com/MicroEJ/Tool-Project-Template-Application/tree/1.0.0>`__
         - `Add-On Library Project Template <https://github.com/MicroEJ/Tool-Project-Template-Add-On-Library/tree/1.0.0>`__
         - `Mock Project Template <https://github.com/MicroEJ/Tool-Project-Template-Mock/tree/1.0.0>`__
      
      - Click on :guilabel:`Clone from URL`.
      
      .. figure:: images/vscode-search-bar.png
        :alt: Search Bar in VS Code
        :align: center
        :scale: 70%
      
        Search Bar in VS Code
      
      - In the upcoming popup, choose a folder and click on the ``Select as Repository Destination`` button.
      - When the Gradle project is loaded, select :guilabel:`Terminal` > :guilabel:`New Terminal`.
      - In the integrated terminal, run the following command at the root of the project to remove the Git Repository:

      .. tabs::

         .. tab:: Windows

            .. code-block:: java

              rm -r -Force .git*


         .. tab:: Linux/macOS

            .. code-block:: java

              rm -rf .git*
              
      - Rename the project and change its group and version in the ``build.gradle.kts`` build script.

   .. tab:: Command Line Interface

      The creation of a project via Command Line Interface is done as follows:
      
      - Depending on the type of your project, retrieve the URI of the corresponding Github template repository. 
        The available templates are:
      
         - `Application Project Template <https://github.com/MicroEJ/Tool-Project-Template-Application/tree/1.0.0>`__
         - `Add-On Library Project Template <https://github.com/MicroEJ/Tool-Project-Template-Add-On-Library/tree/1.0.0>`__
         - `Mock Project Template <https://github.com/MicroEJ/Tool-Project-Template-Mock/tree/1.0.0>`__
      
      - Clone the repository::

         git clone <template-repository>
      
      - Remove the Git Repository from the project:

      .. tabs::

         .. tab:: Windows

            .. code-block:: java

              rm -r -Force .git*


         .. tab:: Linux/macOS

            .. code-block:: java

              rm -rf .git*

      - Rename the project and change its group and version in the ``build.gradle.kts`` build script.

.. _sdk_6_create_project_configure_project:

Configure a Project
-------------------

The SDK allows to build several types of modules.
Each type has its own Gradle plugin and configuration options.
Refer to the module type you want to build to configure your project:

- :ref:`Application <sdk_6_create_project_configure_application>`
- :ref:`Add-On Library <sdk_6_create_project_configure_addon_library>`
- :ref:`Mock <sdk_6_create_project_configure_mock>`
- :ref:`Java SE Library <sdk_6_create_project_configure_jse_library>`
- :ref:`Runtime Environment <sdk_6_create_project_configure_runtime_environment>`


.. _sdk_6_create_project_configure_application:

Application Project
~~~~~~~~~~~~~~~~~~~

- Add the ``com.microej.gradle.application`` plugin in the ``build.gradle.kts`` file::

    plugins {
        id("com.microej.gradle.application") version "0.20.0"
    }

  .. note::
    The ``java`` plugin must not be added since it is automatically applied by the MicroEJ plugin.

- Create the Java main class in the ``src/main/java`` folder.
- Define the property ``applicationEntryPoint`` in the ``microej`` configuration block of the ``build.gradle.kts`` file.
  It must be set to the Full Qualified Name of the Application main class, for example::

   microej {
     applicationEntryPoint = "com.mycompany.Main"
   }

Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

.. _sdk_6_create_project_configure_addon_library:

Add-On Library Project
~~~~~~~~~~~~~~~~~~~~~~

- Add the ``com.microej.gradle.addon-library`` plugin in the build script::

    plugins {
        id("com.microej.gradle.addon-library") version "0.20.0"
    }

  .. note::
    The ``java`` plugin must not be added since it is automatically applied by the MicroEJ plugin.

Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

.. _sdk_6_create_project_configure_mock:

Mock
~~~~

- Add the ``com.microej.gradle.mock`` plugin in the build script::

    plugins {
        id("com.microej.gradle.mock") version "0.20.0"
    }

  .. note::
    The ``java`` plugin must not be added since it is automatically applied by the MicroEJ plugin.

Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

.. _sdk_6_create_project_configure_jse_library:

Java SE Library Project
~~~~~~~~~~~~~~~~~~~~~~~

- Add the ``com.microej.gradle.jse-library`` plugin in the build script::

    plugins {
        id("com.microej.gradle.jse-library") version "0.20.0"
    }

  .. note::
    The ``java`` plugin must not be added since it is automatically applied by the MicroEJ plugin.

Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

.. _sdk_6_create_project_configure_runtime_environment:

Runtime Environment Project
~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Add the ``com.microej.gradle.runtime-environment`` plugin in the build script::

    plugins {
        id("com.microej.gradle.runtime-environment") version "0.20.0"
    }

  .. note::
    The ``java`` plugin must not be added since it is automatically applied by the MicroEJ plugin.

Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

.. _sdk_6_create_subproject_in_existing_project:

Create a subproject in an existing project
------------------------------------------

This section explains the different ways to add a module to an existing project.

.. warning::
   If you want to add a MicroEJ module to a non MicroEJ project, for example an Android project, 
   you must :ref:`configure the repositories <sdk_6_configure_repositories>` before creating the module.
   If the repositories used by your project are `centralized <https://docs.gradle.org/current/userguide/declaring_repositories_adv.html#sub:centralized-repository-declaration>`__ 
   in the :guilabel:`settings.gradle.kts` file of the project, the MicroEJ repositories defined in 
   :download:`this file <resources/microej.init.gradle.kts>` must be added to your :guilabel:`settings.gradle.kts` file.

.. tabs::

   .. tab:: Android Studio

      The creation of a module with Android Studio is done as follows:
      
      - Click on :guilabel:`File` > :guilabel:`New` > :guilabel:`New Module...`.
      - Select :guilabel:`MicroEJ Module` in :guilabel:`Templates` list on the left panel.
      - Fill the name of the module in the :guilabel:`Name` field.
      - Fill the group of the artifact to publish in the :guilabel:`Group` field.
      - Fill the version of the artifact to publish in the :guilabel:`Version` field.
      - Select the module type among :guilabel:`Application` and :guilabel:`Addon-Library` buttons.
      - If you selected :guilabel:`Application` module type, you can check :guilabel:`This is a kernel application` checkbox if your Application is a Kernel.
      - Click on :guilabel:`Finish` button.

      .. figure:: images/android-studio-create-microej-module.png
         :alt: Module Creation in Android Studio
         :align: center
         :scale: 70%
      
         Module Creation in Android Studio

   .. tab:: IntelliJ IDEA

      The creation of a module with IntelliJ IDEA is done as follows:
      
      - Click on :guilabel:`File` > :guilabel:`New` > :guilabel:`Module...`.
      - Select :guilabel:`MicroEJ` in :guilabel:`Generators` list on the left panel.
      - Fill the name of the module in the :guilabel:`Name` field.
      - Select the location of the module in the :guilabel:`Location` field.
      - Select the module type among :guilabel:`Application` and :guilabel:`Addon-Library` buttons.
      - If you selected :guilabel:`Application` module type, you can check :guilabel:`This is a kernel application` checkbox if your Application is a Kernel.
      - Fill the version of the artifact to publish in the :guilabel:`Version` field.
      - Fill the group of the artifact to publish in the :guilabel:`Group` field.
      - Fill the name of the artifact to publish in the :guilabel:`Artifact` field.
      - Select the JVM used by Gradle in the :guilabel:`JDK` combobox.
      - Check the :guilabel:`Add sample code` checkbox.
      - Click on :guilabel:`Create` button.
      
      .. figure:: images/intellij-create-microej-module.png
         :alt: Module Creation in IntelliJ IDEA
         :align: center
         :scale: 70%
      
         Module Creation in IntelliJ IDEA

      - Include the module to your project by adding the following line to the :guilabel:`settings.gradle.kts` file of the project::
      
            include("<module_name>")
      
      - Right-click on the module name in the Gradle tasks view and click on :guilabel:`Unlink Gradle Project`.
      - Reload of a Gradle project by clicking on the reload icon button which appears on the right of the editor:

         .. figure:: images/intellij-reload-gradle-project.png
            :alt: Gradle Project reload in IntelliJ IDEA
            :align: center
            :scale: 70%

            Gradle Project reload in IntelliJ IDEA

   .. tab:: Eclipse

      The creation of a module with Eclipse is done as follows:
      
      - Right-click on your project and click on :guilabel:`New` > :guilabel:`Folder`.
      - Select your project as parent folder.
      - Fill the name of the module in the :guilabel:`Folder name` field.
      - Click on :guilabel:`Finish` button.
      
      .. figure:: images/eclipse-create-microej-module.png
         :alt: Module Creation in Eclipse
         :align: center
         :scale: 70%
      
         Module Creation in Eclipse

      - Right-click on your newly created folder and click on :guilabel:`New` > :guilabel:`File`.
      - Enter ``build.gradle.kts`` in the :guilabel:`File name` field.
      - Click on :guilabel:`Finish` button and open the ``build.gradle.kts`` file.
      - Add the MicroEJ plugin, depending on the module nature you want to build, for example for an Add-On Library::
      
          plugins {
              id("com.microej.gradle.addon-library") version "0.20.0"
          }
      
        or for an Application::
      
          plugins {
              id("com.microej.gradle.application") version "0.20.0"
          }
      
        Refer to the page :ref:`sdk6_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.
      
      - Declare the dependencies required by your project in the ``dependencies`` block. For example::
      
          dependencies {
              implementation("ej.api:edc:1.3.5")
          }
            
      - Open the ``settings.gradle.kts`` file of your project and add the following content::
      
          include("<module_name>")
      
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
      
      - Right-click on the newly created module and click on :guilabel:`New` > :guilabel:`Source Folder`.
      - Enter ``src/main/java`` in the :guilabel:`Folder name` field.
      - Click on :guilabel:`Finish` button.
      
      .. figure:: images/eclipse-create-source-folder.png
         :alt: Source Folder Creation in Eclipse
         :align: center
         :scale: 70%
      
         Source Folder Creation in Eclipse

      - Follow the same steps to create the ``src/main/resources``, ``src/test/java`` and ``src/test/resources`` folders.

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
The SDK requires Gradle ``8.6`` or higher::

  distributionUrl=https\://services.gradle.org/distributions/gradle-8.6-bin.zip

To use the Wrapper during a build, use ``gradlew`` or ``./gradlew`` depending on your OS instead of ``gradle`` in the command line:

.. tabs::

   .. tab:: Windows

      gradlew build

   .. tab:: Linux

      ./gradlew build

In the following chapters of the documentation, the Linux command ``./gradlew`` is used in all examples to execute a build.

Refer to `the official Gradle documentation <https://docs.gradle.org/current/userguide/gradle_wrapper.html>`__ for more information about the Wrapper.


..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
