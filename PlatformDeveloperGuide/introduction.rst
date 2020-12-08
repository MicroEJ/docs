Introduction
============

Scope
-----

This document explains how the core features of MicroEJ Architecture are
accessed, configured and used by the MicroEJ Platform builder. It
describes the process for creating and augmenting a MicroEJ
Architecture. This document is concise, but attempts to be exact and
complete. Semantics of implemented Foundation Libraries are described in
their respective specifications. This document includes an outline of
the required low level drivers (LLAPI) for porting the MicroEJ
Architectures to different real-time operating systems (RTOS).

MicroEJ Architecture is state-of-the-art, with embedded MicroEJ runtimes
for MCUs. They also provide simulated runtimes that execute on
workstations to allow software development on "virtual hardware."

Intended Audience
-----------------

The audience for this document is software engineers who need to
understand how to create and configure a MicroEJ Platform using the
MicroEJ Platform builder. This document also explains how a MicroEJ
Application can interoperate with C code on the target, and the details
of the MicroEJ Architecture modules, including their APIs, error codes
and options.

.. _architecture_overview:

MicroEJ Architecture Modules Overview
-------------------------------------

MicroEJ Architecture features the MicroEJ Core Engine: a tiny and fast
runtime associated with a Garbage Collector. It provides four built-in
Foundation Libraries :

-  :ref:`[BON] <esr-specifications>`
-  EDC
-  :ref:`[SNI] <esr-specifications>`
-  :ref:`[SP] <esr-specifications>`

:ref:`The following figure <fig_jpf-runtime-components>` shows the components involved.

.. _fig_jpf-runtime-components:
.. figure:: images/jpf-runtime-components.*
   :alt: MicroEJ Architecture Runtime Modules: Tools, Libraries and APIs
   :align: center
   :scale: 75%

   MicroEJ Architecture Runtime Modules: Tools, Libraries and APIs

Three APIs allow the device architecture runtime to link with (and port
to) external code, such as any kind of RTOS or legacy C libraries. These
three APIs are

-  Simple Native Interface (:ref:`[SNI] <esr-specifications>`)

-  Low Level MicroEJ Core Engine (LLMJVM)

-  Low Level Shielded Plug (LLSP)

MicroEJ Architecture features additional Foundation Libraries and
modules to extend the kernel:

-  serial communication,

-  UI extension (User Interface)

-  networking

-  file system

-  etc.

Each additional module is optional and selected on demand during the
MicroEJ Platform configuration.


..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
