.. _sdk_6_howto_resolve_in_ide:

How To Resolve Dependencies in the IDE
======================================

When contributing to multiple interdependent projects, 
it is very convenient and more productive to test a change without rebuilding and publishing manually the updated projects.

Gradle allows to consider a local project as a dependency thanks to the `Composite Build feature <https://docs.gradle.org/current/userguide/composite_builds.html>`__.
For example, if you have a project named ``myApplication``, with the coordinates ``com.mycompany:myApplication:1.0.0``,
and a project named ``myLibrary``, with the coordinates ``com.mycompany:myLibrary:1.0.0``, structured as follows:

.. code-block::

   |- myApplication
   |   |- src
   |   |- build.gradle.kts
   |   |- settings.gradle.kts
   |- myLibrary
   |   |- src
   |   |- build.gradle.kts
   |   |- settings.gradle.kts

And the ``build.gradle.kts`` file of the ``myApplication`` project declaring a dependency to the ``myLibrary`` module::

   dependencies {
      implementation("com.mycompany:myLibrary:1.0.0")
   }

Without any additional configuration, Gradle will try to fetch the ``com.mycompany:myLibrary:1.0.0`` dependency from the declared repositories.
This means that when you do a change in the ``myLibrary`` project, it would require to build and publish it, 
then refresh dependencies on the ``myApplication`` project to get the update.
This is painful and time consuming.

In order to avoid this, Gradle allows to consider the ``myLibrary`` build as part of the ``myApplication`` build, 
meaning that when the ``myApplication`` project is built, the ``myLibrary`` project is also rebuilt if it has been changed, 
and is used as the dependency.
This can be configured by adding the following line in the ``settings.gradle.kts`` file of the ``myApplication`` project::

   includeBuild("../myLibrary")

The path given to the ``includeBuild`` method is the relative path of the project to include.

.. warning::
   The ``includeBuild`` method should be used to declare a dependency between two autonomous projects.
   To declare a dependency between two subprojects of a multi-project, a `Project dependency <https://docs.gradle.org/current/userguide/declaring_dependencies.html#sub:project_dependencies>`__ must be used.
   Refer to the :ref:`sdk6_multiproject_dependencies` section for more information.

Refer to the `Official Gradle documentation on the Composite Build feature <https://docs.gradle.org/current/userguide/composite_builds.html>`__ for more details.

.. _sdk6_multiproject_dependencies:

Dependencies Between Subprojects of a Multi-Project
---------------------------------------------------

Gradle allows to declare dependencies between subprojects of a `multi-project build <https://docs.gradle.org/current/userguide/multi_project_builds.html>`__ 
by declaring a `Project dependency <https://docs.gradle.org/current/userguide/declaring_dependencies.html#sub:project_dependencies>`__.

For example, if you have a multi-project named ``myProject`` composed of two subprojects ``myApplication`` and ``myLibrary``:

.. code-block::

   |- myProject
   |   |- myApplication
   |   |   |- src
   |   |   |- build.gradle.kts
   |   |   |- settings.gradle.kts
   |   |- myLibrary
   |   |   |- src
   |   |   |- build.gradle.kts
   |   |   |- settings.gradle.kts
   |   |- settings.gradle.kts

You can declare a Project dependency in the ``build.gradle.kts`` file of the ``myApplication`` subproject to 
make it depend on the ``myLibrary`` subproject::

   dependencies {
      implementation(project(":myLibrary"))
   }

When building the ``myApplication`` subproject, the ``myLibrary`` subproject is also rebuilt if it has been changed,
so contrary to a Module dependency (e.g. ``implementation("com.mycompany:myLibrary:1.0.0")``), 
you don't have to manually build and publish it, and then refresh dependencies on the ``myApplication`` project to get the update.

Refer to the `Official Gradle documentation about the different kinds of dependencies <https://docs.gradle.org/current/userguide/declaring_dependencies.html#sec:dependency-types>`__ 
for more details.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
