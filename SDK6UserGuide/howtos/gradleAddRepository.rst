.. _sdk_6_howto_gradle_add_repository:

How To Add a Repository
=======================

The :ref:`SDK 6 installation process <sdk_6_configure_repositories>` asks to create a Gradle Init Script file to declare modules and plugins repositories.
You may need to use additional repositories or replace the default ones, 
for example to fetch a module only available in your company's repository.
This page presents the different options to do that.

If you need more details on this topic, 
refer to `the official Gradle documentation on repository declaration <https://docs.gradle.org/current/userguide/declaring_repositories.html>`__.

How To Add a Modules Repository
-------------------------------

The different ways to add a modules repository are:

- add a ``repositories`` block in the ``build.gradle.kts`` file of the project:

  .. code-block:: kotlin

    repositories {
      maven {
        name = "myModulesRepository"
        url = uri("https://my.company/my-modules-repository")
      }
    }

  The repositories defined here are fetched **after** the ones defined in the Gradle init script.

  For a multi-project, the repositories must be declared in a ``build.gradle.kts`` file located in the root folder 
  to make them available in all the subprojects.

- update the Gradle Init Script to add, replace or delete a repository.
  The version of this script provided in the installation process is a recommended version to be applied to quickly setup an environment.
  However, it can be modified to adapt it to your need, especially for the list of repositories.
  The modules repositories are defined in the block ``settingsEvaluated > allprojects > repositories``, 
  and are applied to all the Gradle builds executed on the machine.


How To Add a Plugins Repository
-------------------------------

The different ways to add a plugins repository are:

- add a ``pluginManagement > repositories`` block in the ``settings.gradle.kts`` file of the project or the multi-project:

  .. code-block:: kotlin
    
    pluginManagement {
      repositories {
        maven {
          name = "myPluginsRepository"
          url = uri("https://my.company/my-plugind-repository")
        }
      }
    }

  The repositories defined here are fetched **before** the ones defines in the init script.

- update the Gradle Init Script to add, replace or delete a repository.
  The version of this script provided in the installation process is a recommended version to be applied to quickly setup an environment.
  However, it can be modified to adapt it to your need, especially for the list of repositories.
  The plugins repositories are defined in the block ``settingsEvaluated > allprojects > pluginManagement > repositories``, 
  and are applied to all the Gradle builds executed on the machine.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
