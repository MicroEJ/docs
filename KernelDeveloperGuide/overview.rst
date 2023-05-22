Overview
========

Introduction
------------

The Kernel Developer's Guide describes how to create a Kernel Application: a :ref:`Standalone Application <standalone_application>`
that can be extended (statically or dynamically) to run and control the execution of new
applications called :ref:`Sandboxed Applications <sandboxed_application>`).

The intended audience of this document are java developers and system
architects who plan to design and build their own firmware.

Here is a non-exhaustive list of the activities to be done by Kernel Developers:

-  Integrating the Kernel Application with a Platform to produce a Multi-Sandbox Executable and Virtual Device

-  :ref:`Defining the set of APIs <define_apis>` that will be exposed to Applications, optionally by maintaining a custom :ref:`Runtime Environment <runtime_environment>`

-  Managing lifecycles of applications (deciding when to install, start,
   stop and uninstall them)

-  Integrating applications (called System Applications)

-  Defining and applying permissions on system resources (rules &
   policies)

-  Managing connectivity

-  Controlling and monitoring resources

This document takes as prerequisite that a Platform is available
for the target device (see :ref:`vee-porting-guide`).
This document also assumes that the reader is familiar with the
development and deployment of Applications (see :ref:`application-developer-guide`)
and specifics of developing Sandboxed Applications (see :ref:`sandboxed_application`).

Terms and Definitions
---------------------

A *System Application* is a Sandboxed Application that is linked into
a Multi-Sandbox Executable.

A *Multi-Sandbox Platform* is a Platform with the Multi Sandbox
capability of the Core Engine enabled (see the chapter
*Multi-Sandbox* of the :ref:`vee-porting-guide`).
A Multi-Sandbox Executable can only be built with a Multi-Sandbox Platform.

A *Mono-Sandbox Executable* is produced by building and linking a Standalone
Application with a Platform.

A *Virtual Device* is the Multi-Sandbox Executable counterpart for developing
a Sandboxed Application. It provides the firmware
functional simulation part. Usually it also provides a mean to directly
deploy a Sandboxed Application on the target device running a Multi-Sandbox
Firmware (this is called *Local Deployment*). In case of dynamic
application deployment, the Virtual Device must be published on a MicroEJ
Forge instance in order to execute internal batch applications built for this
device.

Overall Architecture
--------------------

.. _fw_stack_overwiew:
.. figure:: png/overview.png
   :alt: Firmware Boundary Overview
   :align: center
   :scale: 60%

   Firmware Boundary Overview

.. _in_out_artifacts:
.. figure:: png/inputs_outputs.png
   :alt: Firmware Input and Output Artifacts
   :align: center
   :scale: 60%

   Firmware Input and Output Artifacts

Multi-Sandbox Build Flow
------------------------

Firmware Build Flow
~~~~~~~~~~~~~~~~~~~

The Firmware build is composed of two phases:

- the build of the Kernel,
- the build of the Sandboxed Application which is linked and appended to the Firmware as a System Application (repeatable).

.. _build_flow_generic:
.. figure:: png/build_flow_generic.png
   :alt: Firmware Build Flow (Kernel + System Applications)
   :align: center
   :scale: 80%

   Firmware Build Flow (Kernel + System Applications)

Virtual Device Build Flow
~~~~~~~~~~~~~~~~~~~~~~~~~

The Virtual Device is automatically built at the same time as the
Firmware (see :ref:`multisandbox_firmware_creation`). 

The Virtual Device builder performs the following steps:

-  Remove the embedded part of the platform (compiler, linker and
   runtime).

-  Append Add-On Libraries and System Applications into the runtime
   classpath. (See :ref:`ivy_confs` for specifying the
   dependencies).

-  Turn the Platform (SDK) license into Virtual Device license 
   so that it can be freely distributed.

-  Generate the Runtime Environment from the Kernel APIs.

.. figure:: png/build_flow_virtual_device.png
   :alt: Virtual Device Build Flow
   :align: center
   :scale: 75%

   Virtual Device Build Flow

Firmware Implementation Libraries
---------------------------------

Firmware implementations must cover the following topics:

-  The firmware's kernel entry point implementation, that deals with
   configuring the different policies, registering kernel services and
   converters, and starting applications.

-  The storage infrastructure implementation: mapping the ``Storage``
   service on an actual data storage implementation. There are multiple
   implementations of the data storage, provided in different artifacts
   that will be detailed in dedicated sections.

-  The applications management infrastructure: how application code is
   stored in memory and how the lifecycle of the code is implemented.
   Again, this has multiple alternative implementations, and the right
   module must be selected at build time to cover the specific
   firmware needs.

-  The simulation support: how the Virtual Device implementation
   reflects the firmware implementation, with the help of specific
   artifacts.

-  The Kernel API definition: not all the classes and methods used to
   implement the firmware's kernel are actually exposed to the
   applications. There are some artifacts available that expose some of
   the libraries to the applications, these ones can be picked when the
   firmware is assembled.

-  The Kernel types conversion and other KF-related utilities: Kernel
   types instances owned by one application can be transferred to
   another application through a Shared Interface. For that to be
   possible, a conversion proxy must be registered for this kernel type.

-  Tools libraries: tools that plug into the SDK,
   extending them with features that are specific to the firmware, like
   deployment of an application, a management console, ...

-  System Applications: pre-built applications that can be embedded 
   into a firmware. Some of them are user-land counter parts of the Kernel.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
