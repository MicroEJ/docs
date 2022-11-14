.. _sdk_6_create_project:

Create a Project
================

This chapter explains the different ways to create a new project.

Command Line Interface
----------------------

The creation of a project can be done via the command line interface via the Gradle ``init`` task.
This task guides you through multiple steps to configure and select the project template to use.
Please refer to `the official documentation <https://docs.gradle.org/current/userguide/build_init_plugin.html>`__ for the full list of templates and options.

In order to create a MicroEJ project, the best way is to use the ``basic`` template:

- execute the command ``gradle init``.
- select the ``basic`` project type.
- select your prefered build script DSL language.
- decide if you want to use new APIs and behavior.
- choose the name of the project (defaults to the name of the parent folder).
- once the project is created, open it in your favorite editor.
- add the MicroEJ plugin in the ``build.gradle.kts`` file, depending on the module nature you want to build, for example for an Add-On Library::

    plugins {
        id("com.microej.gradle.library") version "0.3.0"
    }

  Please refer to the page :ref:`gradle_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

Eclipse
-------

IntelliJ IDEA
-------------

The creation of a project with IntelliJ IDEA is done as follows:

- click on ``File`` > ``New`` > ``Project...``.
- fill the name of the project in the ``Name`` field.
- select the location of the project in the ``Location`` field.
- select the language ``Java`` in the ``Language`` field.
- select ``Gradle`` for the ``Build system`` field.
- select your prefered language for the field ``Gradle DSL``.
- click on ``Create`` button.

.. figure:: images/intellij-create-gradle-project.png
   :alt: Project Creation in IntelliJ IDEA
   :align: center
   :scale: 70%

   Project Creation in IntelliJ IDEA

The project created by IntelliJ IDEA is a standard Java project (Gradle ``java`` plugin).
The ``build.gradle.kts`` file has to be updated to make it a MicroEJ project:

- use the MicroEJ Gradle plugin, depending on the module nature you want to build, for example for an Add-On Library::

    plugins {
        id("com.microej.gradle.library") version "0.3.0"
    }

  Please refer to the page :ref:`gradle_module_natures` for a complete list of the available MicroEJ natures and their corresponding plugins.

- remove the ``repositories`` block.
- replace the content of the ``dependencies`` block by the dependencies required by your project. For example::

    dependencies {
        implementation("ej.api:edc:1.3.5")
    }

- remove the block related to the ``test`` task.

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
