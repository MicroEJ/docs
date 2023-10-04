.. _sdk_6_select_kernel:

Select a Kernel
===============

Building the Feature file of an Application with the SDK requires a Kernel.

There are 2 different ways to provide a Kernel in the build file of the project.

At least one of these is required to :ref:`build the Feature file <sdk_6_build_feature>` of an Application.

Build property kernelExecutableFile
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the build property ``kernelExecutableFile`` in the ``microej`` configuration block to the path of a Kernel (``.out``)::

   microej {
     kernelExecutableFile = "C:\\path\\to\\my\\kernel.out"
   }

Dropins folder
^^^^^^^^^^^^^^

Copy a Kernel to the ``dropins`` folder. The default dropins folder location is ``[module_project_dir]/dropins``. It can be changed using the build property ``dropinsDir``::

   microej {
      dropinsDir = "C:\\path\\to\\dropins"
   }

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
