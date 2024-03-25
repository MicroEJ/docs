
.. _ack_create_project_:
.. |ACK_PLUGIN_VERSION| replace:: 0.3.6
.. |SDK_VERSION| replace:: 0.16.0
.. |SUPPORT_LIB_VERSION| replace:: 2.0.1

Project Setup
=============

This chapter will guide you through the process of creating a project for having an application compatible with both Android and MicroEJ VEE.

The recommended project structure to get started is to have a basic multi-project build that contains a root project and two subprojects: one subproject for the Android/Wear OS application
and one subproject for the MicroEJ Application.
The MicroEJ Application defines code that will run on both MicroEJ VEE and Android, while the Android application includes wrapper code and logic specific to Android.

What follows is the directory and file structure of a typical project:

.. code-block:: text

   ├── android-app/
   │   ├── src
   │   ├── microej.properties       # MicroEJ Application Options for Android/Wear OS
   │   └── build.gradle.kts
   ├── microej-app/
   │   ├── src
   │   ├── configuration/
   │   |    └── common.properties   # MicroEJ Application Options for MicroEJ VEE
   │   └── build.gradle.kts
   ├── build.gradle.kts
   └── settings.gradle.kts


.. _ack_create_android_app_:

Create or Import an Android project
-----------------------------------

The Android documentation covers the process of creating apps for diverse form factors, including smartphones and wearable devices.
Read `Create a Project <https://developer.android.com/studio/projects/create-project>`_ and follow the guidelines before proceeding.
If you are creating a project from scratch, we recommend using the ``Empty Activity`` template.

.. note::

   The project template in Android Studio defines a default ``repositories`` configuration in the ``settings.gradle.kts`` file of the project like below:

   .. code-block:: kotlin
      
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

   Please note that this will override the ``repositories`` configuration defined during the :ref:`installation process <ack_installation_>`, based on Gradle initialization scripts.
   Set the configuration according to your preference, but we suggest removing these lines at first from the settings file to get started.


Assuming that a Gradle project with an Android application is now opened in Android Studio, do the following:

- Open the ``build.gradle.kts`` file at the root of the project.
- Add these lines to the ``plugins`` block:

  .. parsed-literal::
      id("com.microej.gradle.application") version "|SDK_VERSION|" apply false
      id("com.microej.android.gradle.plugins.android") version "|ACK_PLUGIN_VERSION|" apply false



.. _ack_create_microej_app_:

Create or Import a MicroEJ Application
--------------------------------------

The next step is adding the module that contains the MicroEJ Application to the Gradle project.

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
      The ``build.gradle.kts`` file has to be updated to make it a MicroEJ Application module:
      
      - Open the ``build.gradle.kts`` file.
      - Erase its whole content.
      - Add the ``com.microej.gradle.application`` plugin in the ``build.gradle.kts`` file:

        .. code-block:: kotlin

            plugins {
               id("com.microej.gradle.application")
            }
      - Add the following ``microej`` block in the ``build.gradle.kts`` file:

        .. code-block:: kotlin

            microej {
               applicationEntryPoint = "com.mycompany.Main"
            }

        where the property ``applicationEntryPoint`` is set to the Full Qualified Name of the main class of the application.
        This class must define a ``main()`` method and is the entry point of the application.
      
      - Declare the dependencies required by your application in the ``dependencies`` block of the ``build.gradle.kts`` file. 
        The EDC library is always required in the build path of an Application project, as it defines the minimal runtime environment for embedded devices:
      
        .. code-block:: kotlin

            dependencies {
                implementation("ej.api:edc:1.3.5")
            }
      

   .. tab:: Import an existing MicroEJ Application

      If you have already developed a MicroEJ Application, you can import it in the project.

      .. note::
         If the MicroEJ Application has been created with the :ref:`SDK 5 <sdk_user_guide>` or lower, it is required to first migrate it to :ref:`SDK 6 <sdk_6_user_guide>`.
         Read the comprehensive :ref:`Migration Guide <sdk_6_migrate_mmm_project>` before proceeding.

      - Click on :guilabel:`File` > :guilabel:`New` > :guilabel:`Import Module...`.
      - Browse to the source directory of the Gradle project.
      - Set the module name.
      - Click on :guilabel:`Finish`.

        .. note::
            Android Studio may use the Groovy DSL to include the imported module.
            The result is the creation of a ``setting.gradle`` file that shadows the configuration in the ``settings.gradle.kts`` file.
            If that occurs, merge the relevant content of the ``setting.gradle`` file into the existing ``settings.gradle.kts`` and remove the ``setting.gradle``.

- Set the ``microejConflictResolutionRulesEnabled`` property to ``false`` in the ``build.gradle.kts`` file:

  .. code-block:: kotlin

      microej {
         microejConflictResolutionRulesEnabled = false
         ...
      }

  .. note::
      The MicroEJ Gradle plugin comes with additional conflict resolution rules compared to Gradle's default behavior.
      This can make the build fail when working with Android dependencies, so it is recommended to use Gradle's default conflict management in this case.
      These extra rules can be disabled by setting the ``microejConflictResolutionRulesEnabled`` property to ``false`` in the ``microej`` configuration block.
      Read :ref:`Manage Resolution Conflicts <sdk6_manage_resolution_conflicts>` for more details.
      
- Ensure that the Gradle settings file includes the Android and MicroEJ modules, like in this example:

  .. code-block:: kotlin

      include(":android-app")
      include(":microej-app")

- To synchronize your project files, select :guilabel:`Sync Now` from the notification bar that appears after making changes.

When the Gradle project has been reloaded, it should compile successfully, without any error.


Configure the Android Application
---------------------------------

The next steps show how to configure the Android or Wear OS application to declare the MicroEJ Application.

- Open the ``build.gradle.kts`` file of the Android application.
- Add the ``com.microej.android.gradle.plugins.android`` plugin:

  .. code-block:: kotlin

      plugins {
         id("com.android.application")
         id("com.microej.android.gradle.plugins.android")
         ...
      }
- Add a dependency to the MicroEJ support library depending on the target (Android or Wear OS).

.. tabs::

   .. tab:: Android

      .. parsed-literal:: 

         dependencies {
            implementation("com.microej.android.support:microej-application:|SUPPORT_LIB_VERSION|")
            ...
         }

      The support library ``microej-application`` allows running a MicroEJ Application in an Android Activity using the MicroEJ support engine.

   .. tab:: Wear OS

      .. parsed-literal:: 

         dependencies {
            implementation("com.microej.android.support:microej-wearos:|SUPPORT_LIB_VERSION|")
            implementation("androidx.wear.watchface:watchface:1.1.1")
            implementation("androidx.wear.watchface:watchface-guava:1.1.1")
            ...
         }

      The support library ``microej-wearos`` allows running a MicroEJ Application in a Wear OS WatchFaceService using the MicroEJ support engine.

- Add a dependency to the MicroEJ Application using the ``microejApp`` configuration, for example:

  .. code-block:: kotlin

      dependencies {
         microejApp(project(":microej-app")) 
         ...
      }

  where ``microej-app`` is the name of the subproject that contains the MicroEJ Application.

- Add a dependency to a VEE Port, for example:
  
  .. code-block:: kotlin
   
      dependencies {
         microejVee("com.mycompany:veeport:1.0.0")
         ...
      }

  There are multiple options for providing a VEE Port in your project. Read :ref:`Select a VEE Port <sdk_6_select_veeport>` to explore the available options.

  .. note::
      It is required to select a VEE Port that's configured to build MicroEJ Applications for Android.
      Read the :ref:`VEE Port section <ack-vee-port_>` to learn how to configure a VEE Port for this purpose.

- Add a file named ``microej.properties`` at the root of the Android application.
  This file sets the MicroEJ Application Options when running on Android.
  It is similar in principle to :ref:`defining Application Options <sdk_6_define_option>` for the embedded device.
  Depending on the target device (Android or embedded device), the content may differ.

- Select :guilabel:`Sync Now` from the notification bar to synchronize your project files.


Start the MicroEJ Application
-----------------------------

The final step involves calling the entry point of the MicroEJ Application from within the Android or Wear OS application.

.. tabs::

   .. tab:: Android

      Assuming that the Android application declares an activity in the ``AndroidManifest.xml``:

      - Open the corresponding activity Java/Kotlin file.
      - Make ``MicroEJActivity`` the superclass of this class.
      - Override the method ``getApplicationMainClass()`` and make it return the Full Qualified Name of the main class of the MicroEJ Application.

      This is an example of a simple activity:

      .. tabs::

         .. tab:: Kotlin

            .. code-block:: kotlin

               class MainActivity : MicroEJActivity() {
                  override fun getApplicationMainClass(): String {
                     return "com.mycompany.Main";
                  }
               }

         .. tab:: Java

            .. code-block:: java

               public class MainActivity extends MicroEJActivity {
                  @Override
                  protected String getApplicationMainClass() {
                     return "com.mycompany.Main";
                  }
               } 

         When the activity is created, it instantiates the main class of the MicroEJ Application and invokes its ``main()`` method.


   .. tab:: Wear OS

      Assuming that the Wear OS application declares a watch face service in the ``AndroidManifest.xml``:

      - Open the corresponding watch face service Java/Kotlin file.
      - Make ``MicroEJWatchFaceService`` the superclass of this class.
      - Override the method ``getApplicationMainClass()`` and make it return the Full Qualified Name of the main class of the MicroEJ Application.

      This is an example of a simple activity:

      .. tabs::

         .. tab:: Kotlin

            .. code-block:: kotlin

               class MyWatchFaceService : MicroEJWatchFaceService() {
                  override fun getApplicationMainClass(): String {
                     return "com.mycompany.Main";
                  }
               }

         .. tab:: Java

            .. code-block:: java

               public class MyWatchFaceService extends MicroEJWatchFaceService {
                  @Override
                  protected String getApplicationMainClass() {
                     return "com.mycompany.Main";
                  }
               } 

         When the watch face service is created, it instantiates the main class of the MicroEJ Application and invokes its ``main()`` method.
   
Select :guilabel:`Sync Now` from the notification bar to synchronize your project files.

Run on MicroEJ VEE and Android
------------------------------

The application can now be deployed to both MicroEJ VEE and Android environments.

The deployment of an application designed to use the Android Compatibility Kit has nothing specific compared to other MicroEJ or Android applications.
This means that you can refer to the dedicated documentation for this matter:

- for MicroEJ VEE: refer to sections :ref:`Run On Simulator <sdk_6_run_on_simulator>`, :ref:`Build Executable <sdk_6_build_executable>` and :ref:`Run On Device <sdk_6_run_on_device>`.
- for Android: refer to the official `Android documentation <https://developer.android.com/studio/run>`_.
- for Wear OS: refer to the official `Wear OS documentation <https://developer.android.com/training/wearables/get-started/creating#run-emulator>`_.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.