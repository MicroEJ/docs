.. _sdk_6_select_veeport:

Select a VEE Port
=================

Building or running an Application or a Test Suite with the SDK requires a VEE Port.

There are 4 different ways to provide a VEE Port in the build file of the project:

- Set the build property ``veePortFile`` in the ``microej`` configuration block to the path of a VEE Port file (``.zip``, ``.jpf``, or ``.vde``)::

   microej {
     veePortFile = "C:\\path\\to\\my\\veePort\\file.zip"
   }

- Set the build property ``veePortDir`` in the ``microej`` configuration block to the path of the ``source`` folder of an already imported :ref:`Source VEE Port <source_platform_import>`::

   microej {
     veePortDir = "C:\\path\\to\\my\\veePort\\directory"
   }

.. note::

   This file, as well as other Gradle configuration files, respects the Java properties file convention: 
   the OS path	must use the UNIX path convention (path separator is ``/``). 
   The Windows paths must have been converted manually replacing ``\`` by ``/`` or by ``\\``.

- Declare a module dependency with the conf ``microejVeePort``:

   .. code:: java

      dependencies {
         microejVeePort("com.mycompany:myveeport:1.0.0")
      }

   .. note::

      For dependencies stored in an Ivy repository, Gradle fetches them with the configuration ``default``.
      If several artifacts are published with this configuration, the build will fail because it doesn't know which artifact to choose.
      You can select the right artifact by adding information on the one to fetch in the ``artifact`` block, for example::

         microejVeePort("com.mycompany:myveeport:1.0.0") {
            artifact {
               name = "artifact-name"
               type = "zip"
            }
         }

      This will select the artifact with the name ``artifact-name`` and with the type ``zip``.
      
      Refer to `the Gradle documentation <https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.DependencyHandler.html>`__ 
      to learn all the options to select dependencies.
      
- Copy a VEE port archive file to the ``dropins`` folder. The default dropins folder location is ``[module_project_dir]/dropins``. It can be changed using the build property ``veePortDropinsDir``::

   microej {
      veePortDropinsDir = "C:\\path\\to\\dropins"
   }

At least 1 of these 4 ways is required to build an Application with a VEE Port.
If several ways are used, the following rules are applied:

- If ``veePortFile`` or ``veePortDir`` is set, the other options are ignored.
- If the module project defined several VEE Ports, the build fails. For example, the following cases are not allowed:

  - Setting a VEE Port with the option ``veePortFile`` and another one with the option ``veePortDir``
  - Declaring a VEE Port as a dependency and adding a VEE Port in the ``dropins`` folder
  - Declaring 2 VEE Ports as Dependencies
  - Adding 2 VEE Ports in the ``dropins`` folder

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.