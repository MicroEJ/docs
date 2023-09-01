.. _sdk_6_migration_notes:

Migration Notes
---------------

-------------------
From 0.8.0 to 0.9.0
-------------------

This section applies if MicroEJ SDK 6 ``0.9.0`` is used on a project that was created using MicroEJ SDK 6 ``0.8.0`` 
or lower.

Merge of the veePortDirs and veePortFiles properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The build properties ``veePortDirs`` and ``veePortFiles`` have been merged into a single property ``veePortPaths``.
To define a local VEE Port, set the build property ``veePortPaths`` in the ``microej`` configuration block 
to the path of the VEE Port file (``.zip`` or ``.vde``) or to the source folder of the VEE Port::

   microej {
     veePortPaths = listOf("C:\\path\\to\\my\\veePort\\source")
   }

The ``veePortPaths`` property is defined as a list in order to provide multiple VEE Port files or source folders if it is needed::

   microej {
     veePortPaths = listOf("C:\\path\\to\\my\\veePort1\\source", "C:\\path\\to\\my\\veePort2\\file.zip")
   }

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
