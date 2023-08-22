.. _sdk_6_build_project:

Build a Project
===============

Generally speaking, building a project means compiling the source files, executing the tests and generating the module artifact.
Depending on the nature of the project, the build can include other specific phases.
Refer to the :ref:`sdk6_module_natures` page for a complete description of the build phases.

The build of a project is done by executing the Gradle ``build`` task.

.. tabs::

   .. tab:: CLI

      It can be executed with the command line interface::
      
          $ ./gradlew build
      
   .. tab:: Eclipse

      It can be executed from Eclipse by double-clicking on the ``build`` task in the Gradle tasks view:

      .. image:: images/eclipse-build-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: IntelliJ IDEA

      It can be executed from IntelliJ IDEA by double-clicking on the ``build`` task in the Gradle tasks view:

      .. image:: images/intellij-build-gradle-project.png
         :width: 30%
         :align: center

Gradle stores the artifacts produced by the build in the ``build/libs`` folder.

.. note::

   If the build fails with a message related to the ``Artifact Checker`` such as::

      The Artifact Checker found the following problems:
   
   Fix the listed problems or skip the Artifact Checker by adding the following line in the build script file::

      project.gradle.startParameter.excludedTaskNames.add("checkModule")

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
