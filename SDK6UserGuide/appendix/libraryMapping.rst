.. _foundation_library_mapping:

Foundation Libraries Mapping
============================

When an operation is performed on an Application project (run on Simulator, build an Executable, ...), 
some checks and mappings are done on its Libraries.

Check Resolution Conflicts
--------------------------

During the resolution of the compile and runtime classpaths, the following conditions are checked:

- no dependency with 2 incompatible versions (different major version).
- no direct dependency has a transitive dependency with a higher minor version.

Refer to :ref:`sdk6_manage_resolution_conflicts` for more information.

Check Libraries Existence in the VEE Port
-----------------------------------------

Before launching an action on an Application project which uses a VEE Port or a Virtual Device (for example ``runOnSimulator`` or ``buildExecutable``),
the SDK checks that all the Foundation Libraries found in the calculated runtime classpath exist in the VEE Port or Virtual Device.
For example, in the following case:

  .. graphviz:: graphLibrariesMapping01.dot
    :align: center

the build fails with the following message::

   Unable to locate the 'my-foundation-lib-B' Foundation Library in the VEE Port. Make sure that the Library or the related Pack is declared as a dependency in the VEE Port project.

Check Libraries Compatibility in the VEE Port
---------------------------------------------

The SDK also checks the compatibility between the resolved Foundation Libraries dependencies and the ones available in the VEE Port of the Virtual Device.
If the version available in the VEE has a lower minor version, the run fails.

  .. graphviz:: graphLibrariesMapping02.dot
    :align: center

the build fails with the following message::

   com.mycompany:my-foundation-lib-A : the version 1.1.0 of the Library is not compatible with the version 1.0.0 provided by the VEE Port

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
