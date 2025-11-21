.. _sdk_6_offline_repository:

Creating and Using an Offline Repository
========================================

Developing MicroEJ projects requires the Gradle plugins used for the build, 
as well as the modules (Add-On Libraries, Foundation Libraries, ...) used by the project code.
All these artifacts must be available in artifact repositories.

MicroEJ provides them as online repositories which can be used directly, 
thanks to the configuration described in the :ref:`sdk_6_configure_repositories` section.
However, it is not always possible to rely on these online repositories.
Gradle allows to use repositories packaged as a set of local folders and files, called Offline Module Repositories.

This tutorial explains how to create and use Offline Module Repositories for your MicroEJ project.

Offline Repository for the Gradle Plugins
-----------------------------------------

The first step is to create an Offline Repository for the Gradle plugins.
The artifacts of the Gradle plugins are available in the SDK 6 Forge repository.

- Go to the `SDK 6 repository <https://forge.microej.com/ui/repos/tree/General/microej-sdk6-repository-release>`__.
- Click on the :guilabel:`Download` button:

.. figure:: images/forge-sdk6-repository-download.png
    :alt: Download SDK 6 Gradle Plugins Repository
    :align: center
    :scale: 70%

    Download SDK 6 Gradle Plugins Repository

- In the upcoming popup, check the :guilabel:`Include Checksum Files` checkbox.
- Click on :guilabel:`Download`.

Now that the Offline Repository of the Gradle plugins has been retrieved, you can configure your projects to use it:

- Unzip the downloaded archive at the location of your choice, for example in the ``C:\sdk6-repository`` folder.
- Add the following repository definition at the beginning of :ref:`your repositories configuration script <sdk_6_configure_repositories>`:

.. code:: java

  fun RepositoryHandler.offlineMicroEjSdk() {
    val sdk6Uri = uri("C:\\sdk6-repository")

    /* Offline SDK 6 repository for Maven/Gradle modules */
    maven {
      name = "offlineSDKRepositoryMaven"
      url = sdk6Uri
    }
   
    /* Offline SDK 6 repository for Ivy modules */
    ivy {
      name = "offlineSDKRepositoryMaven"
      url = sdk6Uri
      patternLayout {
         artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
         ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
         setM2compatible(true)
      }
    }
  }

- Add the previously created repository declaration inside the `repositories` block of both `dependencyResolutionManagement` and `pluginManagement` blocks:

.. code:: java

  dependencyResolutionManagement {
    repositories {
      ...
      offlineMicroEjSdk()
      ...
    }
  }

  pluginManagement {
    repositories {
      ...
      offlineMicroEjSdk()
      ...
    }
  }


Offline Module Repository
-------------------------

There are 2 ways to create an Offline Module Repository containing the required modules:

- download an existing online repository.
- create an offline module repository project to create a custom repository.

Download an existing online repository
######################################

A quick way to get an Offline Module Repository for the modules is to download an existing online repository.
MicroEJ provides several :ref:`module repositories <module_repositories>`, the main one being the :ref:`Central Repository <central_repository>`.

If this online repository, or another one, contains all the module required for your project, download it. 
For example for the Central Repository, go to `its location <https://forge.microej.com/ui/repos/tree/General/microej-central-repository-release>`__ 
and click on the :guilabel:`Download` button.

Now go to :ref:`this section <sdk_6_use-offline-module-repository>` to configure your project to use it.

Custom Offline Module Repository
################################

If you need a custom Offline Module Repository (for example because the available online repositories 
does not contain all the modules required by your project, or you want to control exactly what contains the repository),
you can create your own.
Refer to :ref:`this page <sdk6_module_repository>`.

Once done, go to :ref:`this section <sdk_6_use-offline-module-repository>` to configure your project to use it.

.. _sdk_6_use-offline-module-repository:

Use an Offline Module Repository
#################################

When the Offline Module Repository of the modules has been retrieved or created, you can configure your projects to use it:

- Unzip the Offline Module Repository archive at the location of your choice, for example in the ``C:\module-repository`` folder.
- Depending on the SDK used to build the repository, add it to your project as follows:
    
.. tabs::

  .. tab:: SDK 6

    Add the following line in the ``build.gradle.kts`` file of your project to declare the repository:
  
    .. code:: java

      apply(file("C:\\module-repository\\module-repository.gradle.kts"))

  .. tab:: SDK 5

    Add the following repositories declaration in :ref:`your repositories configuration script <sdk_6_configure_repositories>`, 
    inside the ``repositories`` block:
  
    .. code:: java

      repositories {

        ...

        maven {
            name = "offlineModulesRepositoryMaven"
            url = uri("C:\\modules-repository")
        }
        ivy {
            name = "offlineModulesRepositoryIvy"
            url = uri("C:\\modules-repository")
            patternLayout {
                artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                setM2compatible(true)
            }
        }

        ...
      
      }

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
