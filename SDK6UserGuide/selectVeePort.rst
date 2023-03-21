.. _sdk_6_select_veeport:

Select a VEE Port
=================

Building or running an Application or a Test Suite with the SDK requires a VEE Port.

There are 4 different ways to provide a VEE Port in the build file of the project:

- Set the build property ``veePortFiles`` in the ``microej`` configuration block to the path of a VEE Port file (``.zip``, ``.jpf``, or ``.vde``)::

   microej {
     veePortFiles = listOf("C:\\path\\to\\my\\veePort\\file.zip")
   }

The ``veePortFiles`` property is defined as a list in order to provide multiple VEE Port files if it is needed.
See the :ref:`Select multiple VEE Ports <sdk_6_select_multiple_vee_ports>` section for more information.

- Set the build property ``veePortDirs`` in the ``microej`` configuration block to the path of the ``source`` folder of an already imported :ref:`Source VEE Port <source_platform_import>`::

   microej {
     veePortDirs = listOf("C:\\path\\to\\my\\veePort\\directory")
   }

The ``veePortDirs`` property is defined as a list in order to provide multiple VEE Port ``source`` folders if it is needed.
See the :ref:`Select multiple VEE Ports <sdk_6_select_multiple_vee_ports>` section for more information.

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

.. _sdk_6_select_multiple_vee_ports:

Select multiple VEE Ports
-------------------------

If multiple :ref:`VEE Ports are defined <sdk_6_select_veeport>` for a project, they are all used.
For example, you can set the ``veePortDirs`` to the path of a ``source`` folder of a VEE Port, 
declare 2 dependencies with the ``microejVeePort`` configuration and copy an archive file to the ``dropins`` folder.

To add several VEE Ports using the ``veePortFiles`` or the ``veePortDirs`` property, the paths must be separated by a comma. 
For example::

   microej {
     veePortFiles = listOf("C:\\path\\to\\my\\veePort1\\file.zip","C:\\path\\to\\my\\veePort2\\file.zip")
   } 

.. _sdk_6_vee_port_unique_name:

VEE Port unique name
--------------------

VEE Ports are referenced by a unique name following the pattern ``{name}-{toolchain}-{version}``, 
where ``name``, ``toolchain`` and ``version`` values are the ones defined in the ``release.properties`` file of the VEE Port. 
For example : `Platform-CM7hardfp_GCC48-0.1.0`

If multiple VEE Ports are defined, this name can be used to select the VEE Port on which 
you want to :ref:`run an Application <sdk_6_run_or_debug_on_with_multiple_vee_ports>` 
or :ref:`execute a testsuite <sdk_6_test_with_multiple_vee_ports>`.



..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.