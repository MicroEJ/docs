.. _sdk_6_select_veeport:

Select a VEE Port
=================

Select one VEE Port
-------------------

Building or running an Application or a Test Suite with the SDK requires a VEE Port.

Use one of the following available options to provide it to your project. 

Using a Module Dependency
~~~~~~~~~~~~~~~~~~~~~~~~~

When your VEE Port is published in an artifact repository, 
you can define the VEE Port by declaring a module dependency in the ``build.gradle.kts`` file, with the ``microejVeePort`` configuration:

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

Using a Local VEE Port Directory
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When your VEE Port has been built locally and is therefore available in a local directory, 
you can use it by setting the ``veePortPath`` property in the ``microej`` configuration block of the ``build.gradle.kts`` file. 
Specify the path to the ``source`` folder of the VEE Port::

   microej {
     veePortPath = "C:\\path\\to\\my\\veePort\\source"
   }

.. note::

   This file, as well as other Gradle configuration files, respects the Java properties file convention: 
   the OS path	must use the UNIX path convention (path separator is ``/``). 
   The Windows paths must have been converted manually replacing ``\`` by ``/`` or by ``\\``.

Using a Local VEE Port Archive
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When your VEE Port is available locally as an archive,
you can use it by setting the ``veePortPath`` property in the ``microej`` configuration block of the ``build.gradle.kts`` file. 
Specify the path to a VEE Port file (``.zip`` or ``.vde``)::

   microej {
     veePortPath = "C:\\path\\to\\my\\veePort\\file.zip"
   }

.. note::

   The legacy ``JPF`` format of a VEE Port is not supported anymore in the SDK 6. 
   If you want to use a VEE Port ``.jpf`` file, you have to use :ref:`the SDK 5 <sdk_user_guide>`.

Using the Dropins Folder
~~~~~~~~~~~~~~~~~~~~~~~~

When your VEE Port is available as an archive file, you can use it by copying it to the ``dropins`` folder. 
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
