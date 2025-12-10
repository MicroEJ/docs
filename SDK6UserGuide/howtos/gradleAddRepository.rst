.. _sdk_6_howto_gradle_add_repository:

How To Add a Repository
=======================

The :ref:`SDK 6 installation process <sdk_6_configure_repositories>` asks to create a Gradle Init Script file 
to declare modules and plugins repositories.
You may need to use additional repositories or replace the default ones, 
for example to fetch a module only available in your company's repository.
This page presents the different options to do that.

If you need more details on this topic, 
refer to `the official Gradle documentation on repository declaration <https://docs.gradle.org/current/userguide/declaring_repositories.html>`__.

.. note::

  In addition to the solutions described in the following sections, it is also possible to directly update the Gradle Init Script to add, replace or delete a repository.
  The version of this script provided in the :ref:`installation process <sdk_6_configure_repositories>` is a recommended version to be applied to quickly setup an environment.
  However, it can be modified to adapt it to your need, especially for the list of repositories.
  The module repositories are defined in the block ``beforeSettings > dependencyResolutionManagement > repositories`` 
  and the plugin repositories are defined in the block ``beforeSettings > pluginManagement > repositories``. 
  They are applied to all the Gradle builds executed on the machine.

How To Add a Module Repository ...
----------------------------------

... in addition to the Init Script Repositories
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If the Module Repositories declared in the Gradle Init Script are declared in a ``dependencyResolutionManagement`` block, 
you can declare additional repositories for your project in the ``settings.gradle.kts`` file with:

  .. code-block:: kotlin

    dependencyResolutionManagement {
      repositories {
        maven {
          name = "myModuleRepository"
          url = uri("https://my.company/my-module-repository")
        }
      }
    }

With this configuration, Gradle starts by fetching the modules from the repositories declared in the Init Script, 
then from the ones declared in the ``settings.gradle.kts`` project file.

... to replace the Init Script Repositories
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you want to declare the list of repositories directly in your project, no matter what is defined in the Gradle Init Script, 
you must declare them directly in the ``build.gradle.kts`` file of your project:

  .. code-block:: kotlin

    repositories {
      maven {
        name = "myModuleRepository"
        url = uri("https://my.company/my-module-repository")
      }
    }

If you want to apply this configuration to all the subprojects of a multi-project, 
the repositories must be declared in a ``build.gradle.kts`` file located in the root folder, 
inside a ``subprojects`` block (or ``allprojects`` depending on your needs):

  .. code-block:: kotlin

    subprojects {
      repositories {
        maven {
          name = "myModuleRepository"
          url = uri("https://my.company/my-module-repository")
        }
      }
    }


How To Add a Plugin Repository
------------------------------

To add a plugin repository, add a ``pluginManagement > repositories`` block in the ``settings.gradle.kts`` file of your project:

  .. code-block:: kotlin
    
    pluginManagement {
      repositories {
        maven {
          name = "myPluginRepository"
          url = uri("https://my.company/my-plugin-repository")
        }
      }
    }

The repositories defined here are fetched **after** the ones defines in the Gradle Init Script.

.. note::

  To be noted that if no plugin repository is defined (in either the Init Script or the project), 
  Gradle uses the `Gradle Plugin Portal <http://plugins.gradle.org/>`__.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
