
.. _ack_create_project_:


Create a Project
================

This chapter will guide you through the process of creating a project for having an application compatible with both Android and MicroEJ VEE.

The recommended project structure to get started is to have a basic multi-project build that contains a root project and two subprojects: one subproject for the Android/Wear OS application
and one subproject for the MicroEJ application.
The MicroEJ application defines the code that will run in both target environments, while the Android/Wear OS application contains the wrapper code and logic specific to Android.

What follows is the directory and file structure of a standard project:

.. code-block:: text

   ├── android-app/
   │   ├── src
   │   ├── microej.properties       # MicroEJ application options for Android/Wear OS
   │   └── build.gradle.kts
   ├── gradle/
   ├── microej-app/
   │   ├── src
   │   ├── configuration/
   │   |    └── common.properties   # MicroEJ application options for MicroEJ VEE
   │   └── build.gradle.kts
   ├── build.gradle.kts
   ├── gradlew 
   ├── gradlew.bat
   └── settings.gradle.kts


.. _ack_create_android_app_:

Create or Import an Android project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Android documentation covers the process of creating apps for diverse form factors, including smartphones and Wear devices.
Read `Create a Project <https://developer.android.com/studio/projects/create-project>`_ and follow the guidelines before proceeding.

.. note::

   The project template in Android Studio defines a default ``repositories`` configuration in the ``settings.gradle.kts`` file of the project like below::

      pluginManagement {
         repositories {
            google()
            mavenCentral()
            gradlePluginPortal()
         }
      }
      dependencyResolutionManagement {
         repositoriesMode.set(RepositoriesMode.FAIL_ON_PROJECT_REPOS)
         repositories {
            google()
            mavenCentral()
         }
      }

   Please note that this will shadow the ``repositories`` configuration defined during the :ref:`installation process <ack_installation_>`, using initialization scripts.
   Set the configuration according to your preference, but we suggest removing these lines at first from the settings file to get started.


Assuming that a Gradle project with an Android application is opened in Android Studio, do the following:

- Open the ``build.gradle.kts`` file at the root of the project.
- Add these lines to the ``plugins`` block::

   id("com.microej.gradle.application") version "0.11.1" apply false
   id("com.microej.android.gradle.plugins.android") version "0.3.1" apply false


Next is to add the module that contains the MicroEJ application to the project.

.. _ack_create_microej_app_:

Create or Import a MicroEJ Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. tabs::

   .. tab:: Create a MicroEJ Application

      - Click on :guilabel:`File` > :guilabel:`New` > :guilabel:`New Module...`.
      - Select :guilabel:`Java or Kotlin Library`.
      - Set the name of the module in the :guilabel:`Library Name` field.
      - Set the package name of the module in the :guilabel:`Package name` field.
      - Enter a name for the main Java class of the application in the :guilabel:`Class name` field.
      - Select the language ``Java`` in the :guilabel:`Language` field.
      - Select ``Kotlin DSL`` in the :guilabel:`Build configuration language` field.
      - Click on :guilabel:`Finish`.

      The module created by Android Studio is a standard Java module (Gradle ``java-library`` plugin). 
      The ``build.gradle.kts`` file has to be updated to make it a MicroEJ module:
      
      - Open the ``build.gradle.kts`` file.
      - Erase its whole content.
      - Add the ``com.microej.gradle.application`` plugin in the ``build.gradle.kts`` file::

         plugins {
            id("com.microej.gradle.application")
         }
      - Add the following ``microej`` block in the ``build.gradle.kts`` file::


            microej {
               applicationMainClass = "com.mycompany.Main"
               microejConflictResolut0ionRulesEnabled = false
            }

      where the property ``applicationMainClass`` is set to the Full Qualified Name of the main class of the application.
      This class defines a ``main()`` method and is the entry point of the application.
      
      .. note::
         The MicroEJ Gradle plugin comes with additional conflict resolution rules compared to Gradle's default behavior.
         This can make the build fail when working with Android dependencies, so it is recommended to use Gradle's default conflict management in this case.
         These extra rules can be disabled by setting the ``microejConflictResolutionRulesEnabled`` property to ``false`` in the ``microej`` configuration block.
         Read :ref:`Manage Resolution Conflicts <sdk6_manage_resolution_conflicts>` for more details.

      - Declare the dependencies required by your application in the ``dependencies`` block of the ``build.gradle.kts`` file. 
        The EDC library is always required in the build path of an Application project, as it defines the minimal runtime environment for embedded devices::
      
            dependencies {
                implementation("ej.api:edc:1.3.5")
            }

      - To synchronize your project files, select :guilabel:`Sync Now` from the notification bar that appears after making changes.
      
      When the Gradle project has been reloaded, it should compile successfully, without any error.

   .. tab:: Import an existing MicroEJ Application

      If you have already developed a MicroEJ application, you can import it in the project.

      .. note::
         If the MicroEJ project has been created with the SDK 5 or lower, it is required to first migrate it to SDK 6.
         Read the comprehensive :ref:`Migration Guide <sdk_6_migrate_mmm_project>` before proceeding.

      - Click on :guilabel:`File` > :guilabel:`New` > :guilabel:`Import Module...`.
      - Browse to the source directory of the Gradle project.
      - Set the module name.
      - Click on :guilabel:`Finish`.

      .. note::
         Android Studio may use the Groovy DSL to define the imported module.
         The result is the creation of a ``setting.gradle`` file that shadows the configuration in the ``settings.gradle.kts`` file.
         In this case, merge the content of the ``setting.gradle`` file into the ``settings.gradle.kts`` and remove the ``setting.gradle``.

      - To synchronize your project files, select :guilabel:`Sync Now` from the notification bar that appears after making changes.
      
      When the Gradle project has been reloaded, it should compile successfully, without any error.


Configure the Android Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The next steps show how to configure the Android application to declare the MicroEJ application.

.. tabs::

   .. tab:: Android

      - Open the ``build.gradle.kts`` file of the Android application.
      - Add the ``com.microej.android.gradle.plugins.android`` plugin::

         plugins {
            id("com.android.application")
            id("com.microej.android.gradle.plugins.android")
            ...
         }
      - Add a dependency to the MicroEJ support library ``microej-application``::

         dependencies {
            implementation("com.microej.android.support:microej-application:2.0.0")
            ...
         }

      The support library allows running a MicroEJ Application on Android using the MicroEJ support engine.

      - Add a dependency to the MicroEJ application::

         dependencies {
            microejApp(project(":microej-app")) 
            ...
         }

      where ``microej-app`` is the name of the subproject that contains your MicroEJ application.

      - Add a dependency to a VEE Port, for example::

         dependencies {
            microejVeePort("com.mycompany:veeport:1.0.0")
            ...
         }
      
      There are multiple options for providing a VEE Port in your project. Read :ref:`Select a VEE Port <sdk_6_select_veeport>` to explore the available options.

      .. note::
         It is required to select a VEE Port that holds an Android runtime implementation for native APIs (e.g., MicroEJ Foundation libraries).
         Read XXX to learn how to configure your VEE Port for Android.
   
      - Select :guilabel:`Sync Now` from the notification bar to synchronize your project files.
           

   .. tab:: Wear OS

      - Open the ``build.gradle.kts`` file of the Wear OS application.
      - Add the ``com.microej.android.gradle.plugins.android`` plugin::

         plugins {
            id("com.android.application")
            id("com.microej.android.gradle.plugins.android")
            ...
         }
      - Add a dependency to the MicroEJ support library ``microej-wearos``::

         dependencies {
            implementation("com.microej.android.support:microej-wearos:2.0.0")
            ...
         }

      The support library allows running a MicroEJ Application on Wear OS using the MicroEJ support engine.

      - Add a dependency to the MicroEJ application::

         dependencies {
            microejApp(project(":microej-app")) 
            ...
         }

      where ``microej-app`` is the name of the subproject that contains your MicroEJ application.

      - Add a dependency to a VEE Port, for example::

         dependencies {
            microejVeePort("com.mycompany:veeport:1.0.0")
            ...
         }
      
      There are multiple options for providing a VEE Port in your project. Read :ref:`Select a VEE Port <sdk_6_select_veeport>` to explore the available options.

      .. note::
         It is required to select a VEE Port that holds an Android runtime implementation for native APIs (e.g., MicroEJ Foundation libraries).
         Read XXX to learn how to configure your VEE Port for Android.

      - Select :guilabel:`Sync Now` from the notification bar to synchronize your project files.


Run the MicroEJ Application Code
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The final step consists of running the MicroEJ application code from the Android application.

.. tabs::

   .. tab:: Android

      


   .. tab:: Wear OS


..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.