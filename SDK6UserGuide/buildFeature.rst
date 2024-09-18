.. _sdk_6_build_feature:

Build a Feature file
====================

To build the Feature file (``.fo``) of an Application, the SDK provides the Gradle ``buildFeature`` task.
The prerequisites to use this task are:

- The Application EntryPoint must be configured, as described in :ref:`sdk_6_create_project_configure_project`.
- A Multi-Sandbox Kernel must be defined.
  Refer to the :ref:`sdk_6_select_kernel` page to learn how to provide a Kernel for a module project.

Once these prerequisites are fulfilled, the Feature file can be built:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      By double-clicking on the ``buildFeature`` task in the Gradle tasks view:

      .. image:: images/intellij-buildFeature-gradle-project.png
         :width: 30%
         :align: center

      |

      .. warning::
         Android Studio does not allow to run multiple Gradle tasks in parallel.
         If you still want to execute several Gradle tasks simultaneously, 
         you can launch them from a terminal with the Gradle Command Line Interface (CLI).

   .. tab:: Eclipse

      By double-clicking on the ``buildFeature`` task in the Gradle tasks view:

      .. image:: images/eclipse-buildFeature-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: Command Line Interface

      From the command line interface::

          $ ./gradlew buildFeature

The Feature file is generated in the ``build/application/feature`` folder of the project.

.. _sdk_6_trigger_feature_build:

Trigger Feature Build by Default
--------------------------------

The Feature of an Application is not built and published by default (when launching a ``./gradlew build`` or 
a ``./gradlew publish`` for example).
This default behavior can be changed by adding the ``produceFeatureDuringBuild()`` method 
in the ``microej`` configuration block of the Gradle build file of the project::

   microej {
     produceFeatureDuringBuild()
   }

.. _sdk_6_build_feature_from_wpk:

Build a Feature file from a WPK
-------------------------------

The SDK provides the Gradle ``buildFeatureFromWPK`` task which allows to build a Feature file from the WPK of an Application.
The prerequisites to use this task are:

- The WPK must be defined:

  - When the WPK is published in an artifact repository, you can use it by declaring a Module dependency::

     dependencies {
        microejApplication("com.mycompany:myapp:1.0.0")
     }  

  - When the WPK is built by a subproject of a multi-project, you can use it by declaring a Project dependency in the ``build.gradle.kts`` file, with the ``microejApplication`` configuration::

     dependencies {
        microejApplication(project(":myApplication"))
     }  

  - When the WPK is available locally, you can use it by declaring a File dependency in the ``build.gradle.kts`` file, with the ``microejApplication`` configuration::

     dependencies {
        microejApplication(files("C:\\path\\to\\my\\application.wpk"))
     }     

- A Multi-Sandbox Kernel must be defined.
  Refer to the :ref:`sdk_6_select_kernel` page to learn how to provide a Kernel for a module project.

Once these prerequisites are fulfilled, the Feature file can be built:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      By double-clicking on the ``buildFeatureFromWPK`` task in the Gradle tasks view:

      .. image:: images/intellij-buildFeatureFromWPK-gradle-project.png
         :width: 30%
         :align: center

      |

      .. warning::
         Android Studio does not allow to run multiple Gradle tasks in parallel.
         If you still want to execute several Gradle tasks simultaneously, 
         you can launch them from a terminal with the Gradle Command Line Interface (CLI).

   .. tab:: Eclipse

      By double-clicking on the ``buildFeatureFromWPK`` task in the Gradle tasks view:

      .. image:: images/eclipse-buildFeatureFromWPK-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: Command Line Interface

      From the command line interface::

          $ ./gradlew buildFeatureFromWPK


The Feature file is generated in the ``build/application/wpkFeature`` folder of the project.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
