.. _multisandbox:

=============
Multi-Sandbox
=============


Principle
=========

The Multi-Sandbox capability of the MicroEJ Core Engine allows a
main application (called Standalone Application) to install and execute
at runtime additional applications (called Sandboxed Applications).

The MicroEJ Core Engine implements the :ref:`[KF] specification <kf_specification>`. A Kernel is a
Standalone Application generated on a Multi-Sandbox-enabled
platform. A Feature is a Sandboxed Application generated against a specific Kernel.

A Sandboxed Application may be dynamically downloaded at runtime or
integrated at build-time within the executable application.

Functional Description
======================

The Multi-Sandbox process extends the overall process described in
:ref:`the overview of the platform process <build_process_overview>`.

.. figure:: images/process-multiapp-overview.*
   :alt: Multi-Sandbox Process
   :align: center
   :scale: 80%

   Multi-Sandbox Process

Once a Kernel has been generated, additional Sandboxed Application code
(Feature) can be built against the Kernel . 
The binary application file produced (``application.fo``) is compatible only
for the Kernel on which it was generated. Generating a new Kernel
requires that you generate the Features again on this Kernel.

For more details on the build flow, please refer to :ref:`Multi-Sandbox Kernel link <kernel_link>` and :ref:`Sandboxed Application link <application_link>` sections.

Memory Considerations
=====================

Multi-Sandbox memory overhead of Core Engine runtime
elements are described in :ref:`Memory Considerations table <memory-considerations>`.


Dependencies
============

-  ``LLKERNEL_impl.h`` implementation (see :ref:`feature_memory_installation` section).


Installation
============

Multi-Sandbox capability is an additional Core Engine module, disabled by default.

To enable the Multi-Sandbox capability of the MicroEJ Core Engine, in the platform
configuration file, check :guilabel:`Multi Applications`.


Use
===

The `KF API Module`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project to use :ref:`[KF] <kf_specification>` library.

::

   <dependency org="ej.api" name="kf" rev="1.4.4"/>

This library provides a set of options. Refer to the chapter
:ref:`application_options` which lists all available options.

.. _KF API Module: https://repository.microej.com/modules/ej/api/kf/


.. _feature_memory_installation:

Feature Installation
====================

Feature installation is the process of linking a ``.fo`` file in memory.
It is triggered by a call to the `Kernel.install(InputStream)`_ method. It consists of:

- transferring the Feature content (code and resources) to the target memory location,
- applying relocations to code (e.g., resolving final addresses in instructions such as method call, static field access, ...).

The ``LLKERNEL_impl.h`` Abstraction Layer interface provides Low Level APIs for allocating and transferring Feature content in different memory areas.

There are two kinds of installation:

- In-place installation: The Feature content is allocated in RAM.
- Custom installation: The Feature content is copied to any byte-addressable memory, including ROM.

Both installation modes require a certain amount of RAM:

- code relocations are allocated in the Java heap,
- the rest is allocated in a memory area called the Kernel Working Buffer (see below).

In-Place Installation
---------------------

This is the fastest way to go with Feature installation since it only requires connecting a ``malloc/free`` implementation.

.. figure:: images/multisandbox-link-inplace-overview.png
   :alt: In-Place Feature Installation Steps
   :align: center
   :scale: 70%

   In-Place Feature Installation Steps

In-Place Feature installation only applies in RAM: the whole Feature content (code and resources) is allocated in the Kernel Working Buffer. 
When the Core Engine or the device restarts the Kernel Working Buffer is reset, thus there is no persistent Feature. 

.. figure:: images/multisandbox-link-inplace-memories.png
   :alt: In-Place Feature Installation Memory Map
   :align: center
   :scale: 70%

   In-Place Feature Installation Memory Map

The In-Place installation flow is described in the following sequence diagram:

.. figure:: images/multisandbox-link-inplace-installation-flow.png
   :alt: In-Place Feature Installation Flow
   :align: center
   :scale: 100%

   In-Place Feature Installation Flow

The In-Place uninstallation flow is described in the following sequence diagram:

.. figure:: images/multisandbox-link-inplace-uninstallation-flow.png
   :alt: In-Place Feature Uninstallation Flow
   :align: center
   :scale: 100%

   In-Place Feature Uninstallation Flow

Custom Installation
-------------------

Custom Feature Installation allows to install a Feature in any byte-addressable memory. 
The Abstraction Layer implementation is responsible for providing the following elements:

- the address location where the Feature will be installed,
- the implementation to copy a chunk of bytes to the target location.


.. figure:: images/multisandbox-link-custom-overview.png
   :alt: Custome Feature Installation Steps
   :align: center
   :scale: 70%

   Custom Feature Installation Steps



.. figure:: images/multisandbox-link-custom-memories.png
   :alt: Custom Feature Installation Memory Map
   :align: center
   :scale: 70%

   Custom Feature Installation Memory Map

The custom installation flow is described in the following sequence diagram:

.. figure:: images/multisandbox-link-custom-installation-flow.png
   :alt: Custom Feature Installation Flow
   :align: center
   :scale: 100%

   Custom Feature Installation Flow

The custom uninstallation flow is described in the following sequence diagram:

.. figure:: images/multisandbox-link-custom-uninstallation-flow.png
   :alt: Custom Feature Uninstallation Flow
   :align: center
   :scale: 100%

   Custom Feature Uninstallation Flow   


Feature Persistency
-------------------

If the Abstraction Layer implementation installs a Feature in a Read-Only memory, it will be available after the Core Engine or the device restarts.

.. figure:: images/multisandbox-link-boot-flow.png
   :alt: Feature Installation Boot Flow
   :align: center
   :scale: 100%

   Feature Installation Boot Flow


Advanced Options
----------------

InputStream Buffer Size
~~~~~~~~~~~~~~~~~~~~~~~

Feature ``.fo`` InputStream is read in a temporary byte array allocated in the Java Heap. 
The buffer size can be configured with the following option:

**Option Name**: ``com.microej.runtime.kf.link.transferbuffer.size``

**Default Value**: ``512`` (bytes)

Relocation Process Yield
~~~~~~~~~~~~~~~~~~~~~~~~

When a Feature file has a large amount of code, it may appear that the Core Engine blocks while applying relocations during the Feature installation.
The number of relocations to apply in batch can be configured with the following option:
 
**Option Name**: ``com.microej.runtime.kf.link.chunk.relocations.count``

**Default Value**: ``128``

Once the Core Engine has processed the given number of relocations, it yields the execution to other threads than the one that is calling the `Kernel.install(InputStream)`_ method.
A small number will give more smooth execution for threads but a slowest installation execution. A large number will make the Core Engine block for applying relocations but a faster installation execution.

.. _Kernel.install(InputStream): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#install-java.io.InputStream-

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
