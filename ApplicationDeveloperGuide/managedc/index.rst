.. _managedc:

============
 Managed C
============

MicroEJ provides the capability to develop parts of an application in C, known as Managed C. Essentially, a MicroEJ Application boots in Java and then run a mix of Java and Managed C code, etc.

.. figure:: images/managed-code.png
   :alt: MicroEJ Managed C Overview
   :scale: 75%
   :align: center

   MicroEJ Managed C Overview

|

.. note::
   This feature requires Architecture version ``8.3.0`` or higher, and is currently not supported in simulation.

Managed C code is enabled through the support of `WebAssembly Core Specification 1.0 <https://www.w3.org/TR/wasm-core-1/>`_, also known as Wasm, with :ref:`certain limitations <managedc.limitations>`. 
Therefore MicroEJ permits a part of an application to be written in any language which can be compiled to Wasm.

You can start exploring this functionality by following the instructions provided in the :ref:`Getting Started <managedc.getting_started>` page.

.. toctree::
   :maxdepth: 1
   :hidden:

   getting_started
   compilation
   communication
   wasi
   limitations
   troubleshooting
..
   | Copyright 2023-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
