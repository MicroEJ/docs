.. _kernel_link:

Kernel Linking
==============

This chapter describes how a Kernel Application is linked.

Basically, a Kernel Application is linked as a Standalone Application.
The main difference is that a Kernel Application defines :ref:`Kernel APIs <kernel.api>`, and requires to embed additional information that will be used later to build a Sandboxed Application against this Kernel (by linking with the Kernel APIs). 
Such additional information is called the Kernel Metadata.

Link Flow
---------

The following figure shows the general process of linking a Firmware, applied to a Kernel Application.

.. figure:: png/link_kernel.png
   :alt: Kernel Link Flow
   :align: center
   :scale: 80%

   Kernel Link Flow

The Platform must be configured with :ref:`Multi-Sandbox capability <multisandbox>`.

By default, the Kernel Metadata is included in the ``.debug.soar`` section which also serves for debug purpose (:ref:`stack_trace_reader`, :ref:`Heap Dumper <heapdumper>`).
Particularly, it contains resolved absolute addresses of Kernel APIs.

.. _kernel_metadata_generation:

Kernel Metadata Generation
--------------------------

To :ref:`build a Sandboxed Application on Device <build_feature_on_device>`, the Kernel Metadata must be exported after the Firmware link from the ``.debug.soar`` section of the executable.
This step is not necessary to :ref:`build a Sandboxed Application Off Board <build_feature_off_board>`.

The Kernel Metadata can be exported from an existing Firmware executable file by using the Kernel Metadata Generator tool.
It produces a ``.kdat`` file that will be used to link the Sandboxed Applications on device.

.. figure:: png/kernel_metadata_generator.png
   :alt: Kernel Metadata Generator
   :align: center
   :scale: 80%

   Kernel Metadata Generator

The ``.kdat`` file is optimized for size. When linking a Sandboxed Application ``.fso`` file, only the required metadata will be loaded in Java heap.
It will be loaded from a standard `InputStream`_,
so that it can be stored to a non byte-addressable memory.

.. note::

   The Kernel Metadata ``.kdat`` file can also be integrated in a Firmware executable file using post-link tools such as binutils objcopy,
   provided a dedicated section has been reserved by the third-party linker.


.. _InputStream: https://repository.microej.com/javadoc/microej_5.x/apis/java/io/InputStream.html

.. _feature_portability_control:

Feature Portability Control
---------------------------

A Kernel can install ``.fo`` files that have been built on other Kernels, provided this Kernel complies with other Kernels according to a set of rules declared hereafter.
This is called `Feature Portability Control`, as the verification is performed during the new Kernel build, with no impact on the Feature dynamic installation.

Principle
~~~~~~~~~

During a Kernel build, SOAR can verify this Kernel preserves the portability of any ``.fo`` files built on a previous Kernel using :ref:`the Kernel metadata file <kernel_metadata_generation>`.
If the portability is preserved, the :ref:`UID <kernel_uid>` of the previous Kernel is embedded in the new Kernel, allowing ``.fo`` files built on the previous Kernel to be installed as well.
Otherwise, SOAR fails with an error indicating the broken rule(s).

.. figure:: png/feature_portability_control_principle.png
   :alt: Feature Portability Control Principle
   :align: center
   :scale: 80%

   Feature Portability Control Principle


Enable
~~~~~~

.. note::

   This is a new functionality that requires Architecture :ref:`8.0.0 <changelog-8.0.0>` or higher.

Add the following :ref:`Application Options <application_options>` to your Kernel project:

- ``com.microej.soar.kernel.featureportabilitycontrol.enabled``: ``true`` to enable Feature Portability Control. Any other value disables Feature Portability Control (the following option is ignored).
- ``com.microej.soar.kernel.featureportabilitycontrol.metadata.path``: Path to the Kernel Metadata file (``.kdat`` file).

Portability Rules
~~~~~~~~~~~~~~~~~

A Kernel Application can install a ``.fo`` file that has been built against another Kernel Application
if the Kernel Application code has not changed or if the modifications respect the portability rules. 
Here is the list of the modifications that can be done while preserving the portability:

- Modify method code, except if :ref:`soar_method_devirtualization` or :ref:`soar_method_inlining` has changed.
- Add a new type (including declared as Kernel API),
- Add a new static method (including declared as Kernel API),
- Add a new instance method in a type **not declared** as Kernel API,
- Add a new instance method with ``private`` visibility in a type **declared** as Kernel API,
- Add a new static field (including declared as Kernel API),
- Add a new instance field in a type **not declared** as Kernel API,
- Rename an instance field with ``private`` visibility in a type **declared** as Kernel API,
- Modify a Java type, method, or static field **not declared** as Kernel API (code, signature, hierarchy) 
- Remove a Java type, method, or static field **not declared** as Kernel API

Both Kernel Applications must be built from Platforms based on the same Architecture version.

Any other modifications will break the Feature portability. For example, the following modifications will not preserve the portability:

- Remove a Java type, method or static field **declared** as Kernel API,
- Add or remove an instance method in a type **declared** as Kernel API, even if the method is **not declared** as Kernel API,
- Add or remove an instance field in a type **declared** as Kernel API,
- Modify method or field signature **declared** as Kernel API (name, declaring type, static vs instance member, ...),
- Modify hierarchy of a type **declared** as Kernel API.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
