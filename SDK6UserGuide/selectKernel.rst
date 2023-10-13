.. _sdk_6_select_kernel:

Select a Kernel
===============

Building the Feature file of an Application with the SDK requires a Kernel.

Use one of the following available options to provide it to your project. 

Using a Module Dependency
~~~~~~~~~~~~~~~~~~~~~~~~~

When your Kernel is published in an artifact repository, 
you can define the Kernel by declaring a module dependency in the ``build.gradle.kts`` file, with the ``microejKernel`` configuration::
   
   dependencies {
      microejKernel("com.mycompany:mykernel:1.0.0")
   }
 
Using a Local Kernel
~~~~~~~~~~~~~~~~~~~~

When your Kernel has been built locally, 
you can use its Virtual Device and its Executable by declaring a file dependency in the ``build.gradle.kts`` file, with the ``microejKernel`` configuration::

   dependencies {
      microejKernel(files("C:\\path\\to\\my\\kernel\\virtual\\device", "C:\\path\\to\\my\\kernel\\executable.out"))
   }

.. note::

   This file, as well as other Gradle configuration files, respects the Java properties file convention: 
   the OS path	must use the UNIX path convention (path separator is ``/``). 
   The Windows paths must have been converted manually replacing ``\`` by ``/`` or by ``\\``.

Using the Dropins Folder
~~~~~~~~~~~~~~~~~~~~~~~~

When your Kernel Virtual Device is available as an archive file and your Kernel Executable is available locally, 
you can use them by copying them to the ``dropins`` folder. 
The default dropins folder location is ``[module_project_dir]/dropins``. It can be changed using the build property ``dropinsDir``::

   microej {
      dropinsDir = "C:\\path\\to\\dropins"
   }

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
