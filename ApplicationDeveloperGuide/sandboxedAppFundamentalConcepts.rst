.. _sandboxed_application_fundamental_concepts:

Fundamental Concepts
====================

Multi-Sandboxing is based on the :ref:`the Kernel & Features Specification <kf_specification>` (KF).

It allows an application code to be split between multiples parts: 

- the main application, called the Kernel,
- zero or more applications called Features.

Therefore, a Kernel Application relates to the *Kernel* concept and a Sandboxed Application relates to the *Feature* concept.

Some fundamental points:

- The Kernel is mandatory. It is assumed to be reliable, trusted and cannot be modified.
- A Feature is an application "extension" managed by the Kernel.
- A Feature is fully controlled by the Kernel: it can be installed (dynamically or statically pre-installed), started, stopped and
  uninstalled at any time independent of the system state (particularly, a Feature never depends on
  another Feature to be stopped).
- A Feature is optional, potentially not-trusted, maybe unreliable and
  can be executed without jeopardizing the safety of the Kernel execution and other Features.
- Resources accesses (RAM, hardware peripherals, CPU time, ...) are under control of the Kernel.

.. note::

   You can go further by reading :ref:`the Kernel & Features Specification <kf_specification>`.


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
