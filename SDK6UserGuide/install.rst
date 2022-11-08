.. _sdk_6_install:

Installation
============

This chapter will guide you through the installation process of the SDK on your workstation.

Install Gradle
--------------

The first step is to install Gradle by following `the official documentation <https://gradle.org/install/>`__.
Once done, you can verify your installation by opening a terminal and run the command ``gradle -v``.
It should display the Gradle version, for example:

.. code:: console

   $ gradle -v
   
   ------------------------------------------------------------
   Gradle 7.5.1
   ------------------------------------------------------------

Configure repositories
----------------------

In order to use the SDK Gradle plugins and modules in your project, 
the :ref:`Central <central_repository>` and :ref:`Developer <developer_repository>` repositories must be configured.
There are several ways to declare repositories.
For starting you can declare them globally to make them available in all your projects:

- create a file ``microej.gradle.kts`` in the folder ``<user.home>/.gradle/init.d`` (create the folders if they do not exist).
- copy the following content in this file::

   settingsEvaluated {

      allprojects {
         /**
          * Fetch repositories
          */
         repositories {
            ivy {
                name = "microEJCentral"
                url = uri("https://repository.microej.com/5/artifacts/")
                patternLayout {
                    artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                    ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                    setM2compatible(true)
                }
            }
            ivy {
                name = "microEJForgeCentral"
                url = uri("https://forge.microej.com/artifactory/microej-central-repository-release")
                patternLayout {
                    artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                    ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                    setM2compatible(true)
                }
            }
            ivy {
                name = "microEJForgeDeveloper"
                url = uri("https://forge.microej.com/artifactory/microej-central-repository-release")
                patternLayout {
                    artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                    ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                    setM2compatible(true)
                }
            }
         }
      }


      /**
       * Plugins repositories
       */
      pluginManagement {
         repositories {
            maven {
                name = "microEJCentral"
                url = uri("https://repository.microej.com/5/artifacts/")
            }
            maven {
                name = "microEJForgeCentral"
                url = uri("https://forge.microej.com/artifactory/microej-central-repository-release")
            }
            maven {
                name = "microEJForgeDeveloper"
                url = uri("https://forge.microej.com/artifactory/microej-central-repository-release")
            }
         }
      }
   }

At this stage, you can already build a project from the command line, 
for example by executing the command `gradle build` at the root of the project.
But let's continue the installation process to have a complete development environment.

Install the IDE
---------------

MicroEJ supports 2 IDEs for the development of projects: 
`Eclipse IDE <https://www.eclipse.org/downloads/packages/>`__ and `IntelliJ IDEA <https://www.jetbrains.com/idea/>`__.
Please follow their respective documentation to install one of them.

These 2 IDEs come with the Gradle plugin installed by default, so you don't have anything else to do then, 
you are ready to start developing MicroEJ projects.

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
