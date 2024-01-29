.. _sdk_6_select_kernel:

Select a Kernel
===============

Building the Feature file of an Application with the SDK requires a Kernel.

Use one of the following available options to provide it to your project. 

Using a Module Dependency
~~~~~~~~~~~~~~~~~~~~~~~~~

When your Kernel is published in an artifact repository, 
you can define the Kernel by declaring a module dependency in the ``build.gradle.kts`` file, with the ``microejVee`` configuration::
   
   dependencies {
      microejVee("com.mycompany:mykernel:1.0.0")
   }
 
Using a Local Kernel
~~~~~~~~~~~~~~~~~~~~

When your Kernel has been built locally, 
you can use its Virtual Device and its Executable by declaring a file dependency in the ``build.gradle.kts`` file, with the ``microejVee`` configuration::

   dependencies {
      microejVee(files("C:\\path\\to\\my\\kernel\\virtual\\device", "C:\\path\\to\\my\\kernel\\executable.out"))
   }

.. note::

   This file, as well as other Gradle configuration files, respects the Java properties file convention: 
   the OS path	must use the UNIX path convention (path separator is ``/``). 
   The Windows paths must have been converted manually replacing ``\`` by ``/`` or by ``\\``.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
