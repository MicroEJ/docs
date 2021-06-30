.. _multisandbox:

=============
Multi-Sandbox
=============


Principle
=========

The Multi-Sandbox capability of the MicroEJ Core Engine allows a
main application (called Standalone Application) to install and execute
at runtime additional applications (called sandboxed applications).

The MicroEJ Core Engine implements the :ref:`[KF] specification <esr-specifications>`. A Kernel is a
Standalone Application generated on a Multi-Sandbox-enabled
platform. A Feature is a sandboxed application generated against a
Kernel.

A sandboxed application may be dynamically downloaded at runtime or
integrated at build-time within the executable application.

Note that the Multi-Sandbox is a capability of the MicroEJ Core
Engine. The MicroEJ Simulator always runs an application as a Standalone Application.


Functional Description
======================

The Multi-Sandbox process extends the overall process described in
:ref:`the overview of the platform process <build_process_overview>`.

.. figure:: images/process-multiapp-overview.*
   :alt: Multi-Sandbox Process
   :align: center
   :scale: 80%

   Multi-Sandbox Process

Once a Kernel has been generated, additional MicroEJ Application code
(Feature) can be built against the Kernel by :

-  Creating one launch configuration per feature.

-  Setting the :guilabel:`Settings` field in the :guilabel:`Execution` tab of each
   feature launch configuration to :guilabel:`Build Dynamic Feature`.

-  Setting the :guilabel:`Kernel` field in the :guilabel:`Configuration` tab of each
   feature launch configuration to the :guilabel:`...`.

using the MicroEJ Application launch named Build Dynamic Feature. The
binary application file produced (``application.fo``) is compatible only
for the Kernel on which it was generated. Generating a new Kernel
requires that you generate the Features again on this Kernel.

The Features built can be deployed in the following ways:

-  Downloaded and installed at runtime by software. Refer to the :ref:`[KF]
   specification <esr-specifications>` for ``ej.kf.Kernel`` install APIs.

-  Linked at build-time into the executable application. Features linked
   this way are then called Installed Features. The Kernel should have
   been generated with options for dimensioning the maximum size (code,
   data) for such Installed Features. Features are linked within the
   Kernel using the Firmware linker tool.


Firmware Linker
===============

A MicroEJ tool is available to link Features as Installed Features
within the executable application. The tool name is Firmware Linker. It
takes as input the executable application file and the Feature binary
code into which to be linked. It outputs a new executable application
file, including the Installed Feature. This tool can be used to append
multiple Features, by setting as the input file the output file of the
previous pass.


Memory Considerations
=====================

Multi-Sandbox memory overhead of MicroEJ Core Engine runtime
elements are described in :ref:`the table below <table_kf-overhead>`.

.. _table_kf-overhead:
.. table:: Multi-Sandbox Memory Overhead

   +-----------+-----------+-----------------------------------------------+
   | Runtime   | Memory    | Description                                   |
   | element   |           |                                               |
   +===========+===========+===============================================+
   | Object    | RW        | 4 bytes                                       |
   +-----------+-----------+-----------------------------------------------+
   | Thread    | RW        | 24 bytes                                      |
   +-----------+-----------+-----------------------------------------------+
   | Stack     | RW        | 8 bytes                                       |
   | Frame     |           |                                               |
   +-----------+-----------+-----------------------------------------------+
   | Class     | RO        | 4 bytes                                       |
   | Type      |           |                                               |
   +-----------+-----------+-----------------------------------------------+
   | Interface | RO        | 8 bytes                                       |
   | Type      |           |                                               |
   +-----------+-----------+-----------------------------------------------+


Dependencies
============

-  ``LLKERNEL_impl.h`` implementation (see :ref:`LLKF-API-SECTION`).


Installation
============

Multi-Sandbox is an additional module, disabled by default.

To enable Multi-Sandbox of the MicroEJ Core Engine, in the platform
configuration file, check :guilabel:`Multi Applications`.


Use
===

The `KF API Module <https://repository.microej.com/modules/ej/api/kf/>`_ 
must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project to use :ref:`[KF] <esr-specifications>` library.

::

   <dependency org="ej.api" name="kf" rev="1.4.4"/>

This library provides a set of options. Refer to the chapter
:ref:`application_options` which lists all available options.

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
