.. _gradle_vee_transitivity_chapter:

VEE Port transitivity
=====================

Starting from SDK 6 ``1.4.0``, it is possible to enable the :ref:`transitive resolution of the VEE Port <sdk_6_vee_port_transitivity>`.
This allows to include the transitive dependencies of the VEE Port in the compile classpath and runtime classpath of the project,
depending on the configuration used to define the Libraries in your VEE Port (``microejPack``, ``api``, ``implementation``):

- The Libraries defined with ``microejPack`` and ``api`` and their transitive dependencies are added to the compile classpath and runtime classpath of the project.
- The Libraries defined with ``implementation`` and their transitive dependencies are added to the runtime classpath of the project.

For example, if your VEE Port provides the following Libraries::

   dependencies {
      microejPack("org.example:lib1:1.0.0")
      api("org.example:lib2:1.0.0")
      implementation("org.example:lib3:1.0.0")
   }

the ``lib3`` library will be added to the runtime classpath of your project, and the ``lib1`` and ``lib2`` will be added to both compile classpath and runtime classpath.

.. note::

   In a VEE Port project, the ``microejPack`` configuration can be used to define an SDK 5 Pack or an SDK 6 Library. 
   The ``api`` and ``implementation`` configurations are used to define SDK 6 Libraries only.

If the provided VEE Port is used only for :ref:`testsuites <sdk_6_testsuite_vee_configuration>`, the Libraries provided by the VEE Port are used 
to build the runtime classpath of the testsuites, not to compile the project.

.. warning::

   It is important to note that a VEE Port allowing to resolve transitively its Libraries is required, so if your project uses:

   - a VEE Port built with SDK 6 ``1.2.0`` or older
   - a VEE Port built with SDK 5

   it is highly recommended to update your VEE Port project to SDK 6 ``1.3.0`` or higher as the feature will be enabled by default in the next SDK 6 major version.
   This limitation does not concern VEE Ports available locally :ref:`in a directory <sdk_6_select_veeport_local_directory>` or 
   :ref:`as an archive <sdk_6_select_veeport_local_archive>`.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
