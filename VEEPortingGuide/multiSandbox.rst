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

Once a Kernel has been generated, additional MicroEJ Application code
(Feature) can be built against the Kernel . 
The binary application file produced (``application.fo``) is compatible only
for the Kernel on which it was generated. Generating a new Kernel
requires that you generate the Features again on this Kernel.

For more details, please refer to the :ref:`Kernel Developer Guide <kernel-developer-guide>`,
especially :ref:`Multi-Sandbox Kernel link <kernel_link>` and :ref:`Sandboxed Application link <application_link>` sections.

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

The `KF API Module`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project to use :ref:`[KF] <kf_specification>` library.

::

   <dependency org="ej.api" name="kf" rev="1.4.4"/>

This library provides a set of options. Refer to the chapter
:ref:`application_options` which lists all available options.

.. _KF API Module: https://repository.microej.com/modules/ej/api/kf/

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
