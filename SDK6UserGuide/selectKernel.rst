.. _sdk_6_select_kernel:

Select a Kernel
===============

Building the Feature file of an Application with the SDK requires a Kernel.

There are 3 different ways to provide a Kernel in the build file of the project.

At least one of these is required to :ref:`build the Feature file <sdk_6_build_feature>` of an Application.

Build property kernelFiles
^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the build property ``kernelFiles`` in the ``microej`` configuration block to the path of a Kernel (``.out``)::

   microej {
     kernelFiles = listOf("C:\\path\\to\\my\\kernel.out")
   }

The ``kernelFiles`` property is defined as a list in order to provide multiple Kernels if it is needed.
See the :ref:`Select multiple Kernels <sdk_6_select_multiple_kernels>` section for more information.

Module dependency microejKernel
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Declare a module dependency with the conf ``microejKernel``:

   .. code:: java

      dependencies {
         microejKernel("com.mycompany:mykernel:1.0.0")
      }
   
   .. note::

      For dependencies stored in an Ivy repository, Gradle fetches them with the configuration ``default``.
      If several artifacts are published with this configuration, the build will fail because it doesn't know which artifact to choose.
      You can select the right artifact by adding information on the one to fetch in the ``artifact`` block, for example::

         microejKernel("com.mycompany:mykernel:1.0.0") {
            artifact {
               name = "artifact-name"
               type = "out"
            }
         }

      This will select the artifact with the name ``artifact-name`` and with the type ``out``.
      
      Refer to `the Gradle documentation <https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.DependencyHandler.html>`__ 
      to learn all the options to select dependencies.

Dropins folder
^^^^^^^^^^^^^^

Copy a Kernel to the ``dropins`` folder. The default dropins folder location is ``[module_project_dir]/dropins``. It can be changed using the build property ``dropinsDir``::

   microej {
      dropinsDir = "C:\\path\\to\\dropins"
   }


.. _sdk_6_select_multiple_kernels:

Select multiple Kernels
-----------------------

If multiple :ref:`Kernels are defined <sdk_6_select_kernel>` for a project, they are all used.
For example, you can set the ``kernelFiles`` to the path of a Kernel, 
declare a dependency with the ``microejKernel`` configuration and copy a file to the ``dropins`` folder.

To add several Kernels using the ``kernelFiles`` property, the paths must be separated by a comma. 
For example::

   microej {
     kernelFiles = listOf("C:\\path\\to\\my\\kernel1.out","C:\\path\\to\\my\\kernel2.out")
   } 

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
