.. _gradle_vee_transitivity_chapter:

VEE transitivity
================

Starting from SDK 6 ``1.4.0``, it is possible to enable the transitive resolution of a :ref:`VEE Port <sdk_6_vee_port_transitivity>` or 
a :ref:`Kernel <sdk_6_kernel_transitivity>`. This allows to use the transitive dependencies of the provided VEE to compile and build the project.

VEE Port transitivity
~~~~~~~~~~~~~~~~~~~~~

When a VEE Port is resolved transitively, its transitive dependencies are added to the compile classpath and runtime classpath of the project depending on 
the configuration used to define the Libraries in the VEE Port (``microejPack``, ``api``, ``implementation``):

- The Libraries defined with ``microejPack`` and ``api`` and their transitive dependencies are added to the compile classpath and runtime classpath of the project.
- The Libraries defined with ``implementation`` and their transitive dependencies are added to the runtime classpath of the project.

For example, if your VEE Port provides the following Libraries::

   dependencies {
      implementation("org.example:lib1:1.0.0")
      microejPack("org.example:lib2:1.0.0")
      api("org.example:lib3:1.0.0")
   }

the ``lib1`` library will be added to the runtime classpath of your project, and the ``lib2`` and ``lib3`` libraries will be added to both the compile classpath and the runtime classpath.

.. note::

   In a VEE Port project, the ``microejPack`` configuration can be used to define an SDK 5 Pack or an SDK 6 Library. 
   The ``api`` and ``implementation`` configurations are used to define SDK 6 Libraries only.

If the provided VEE Port is used only for :ref:`testsuites <sdk_6_testsuite_vee_configuration>`, the Libraries provided by the VEE Port are used 
to build the runtime classpath of the testsuites, not to compile the project.

.. warning::

   It is important to note that a VEE Port built with SDK 6 ``1.3.0`` minimum is required to use transitivity, the following VEE Ports are not supported:

   - VEE Ports built with SDK 6 ``1.2.0`` or older
   - VEE Ports built with SDK 5

   It is highly recommended to update your VEE Port to SDK 6 ``1.3.0`` minimum if needed, as the feature will be enabled by default in the next SDK 6 major version. 
   This limitation does not concern VEE Ports available locally :ref:`in a directory <sdk_6_select_veeport_local_directory>` or 
   :ref:`as an archive <sdk_6_select_veeport_local_archive>`.

Kernel transitivity
~~~~~~~~~~~~~~~~~~~

When a Kernel is resolved transitively, its Jar file and its transitive dependencies are added to the compile classpath and runtime classpath of the project depending on 
the configuration used to define the Libraries in the Kernel:

- The Libraries defined with ``api`` and their transitive dependencies are added to the compile classpath and runtime classpath of the project.
- The Libraries defined with ``implementation`` and their transitive dependencies are added to the runtime classpath of the project.

For example, if your project depends on a Kernel which defined the following dependencies::

   dependencies {
      implementation("org.example:lib1:1.0.0")
      api("org.example:lib2:1.0.0")
   }

the ``lib1`` library will be added to the runtime classpath of your project, and the ``lib2`` library will be added to both the compile classpath and the runtime classpath.

This behavior is consistent with that of the `Gradle Java Library plugin <https://docs.gradle.org/current/userguide/java_library_plugin.html#sec:java_library_separation>`__.
However, it is important to note that the APIs of a Library defined with ``api`` in your Kernel will be exposed to Applications.

To ensure that a dependency defined in a Kernel is not exposed to Applications by mistake, it is highly recommended to use ``implementation`` instead of ``api`` 
(or ``compileOnly`` instead of ``compileOnlyApi``)  when declaring dependencies in your Kernel project. 


If the provided Kernel is used only for :ref:`testsuites <sdk_6_testsuite_vee_configuration>`, the Libraries provided by the Kernel are used 
to build the runtime classpath of the testsuites, but they are not used to compile the project.

.. warning::

   It is important to note that a Kernel built with SDK 6 ``1.3.0`` minimum is required to use transitivity, the following Kernels are not supported:

   - Kernels built with SDK 6 ``1.2.0`` or older
   - Kernels built with SDK 5

   It is highly recommended to update your Kernel to SDK 6 ``1.3.0`` minimum if needed, as the feature will be enabled by default in the next SDK 6 major version. 
   This limitation does not concern Kernels :ref:`available locally <sdk_6_select_local_kernel>`.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
