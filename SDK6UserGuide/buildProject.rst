.. _sdk_6_build_project:

Build a Project
===============

Generally speaking, building a project means compiling the source files, executing the tests and generating the module artifact.
Depending on the nature of the project, the build can include other specific phases.
Refer to the :ref:`sdk6_module_natures` page for a complete description of the build phases.

The steps to build a project are:

- define the VEE Port in the build file of the project.
  The VEE Port is required to execute the tests and to allow to run the Application with the Simulator.
  Refer to the :ref:`sdk_6_select_veeport` page to know the different ways to provide a VEE Port for a module project.

- launch the Gradle ``build`` task.
  It can be executed with the command line interface::

    $ gradle build

  or from Eclipse and IntelliJ IDEA, by double-clicking on the ``build`` task in the Gradle tasks view:

  .. tabs::
  
     .. tab:: Eclipse
  
        .. image:: images/eclipse-build-gradle-project.png
           :width: 50%
           :align: center
  
     .. tab:: IntelliJ IDEA
  
        .. image:: images/intellij-build-gradle-project.png
           :width: 30%
           :align: center

Gradle stores the artifacts produced by the build in the ``build/libs`` folder.

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
