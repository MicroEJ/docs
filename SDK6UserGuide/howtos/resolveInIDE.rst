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

Refer to the `Official Gradle documentation on the Composite Build feature <https://docs.gradle.org/current/userguide/composite_builds.html>`__ for more details.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
