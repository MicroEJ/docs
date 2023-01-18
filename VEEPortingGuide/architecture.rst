.. _architecture_overview:

====================
MicroEJ Architecture
====================

MicroEJ Architecture features the MicroEJ Core Engine built for a specific instructions set (ISA) and compiler.

The MicroEJ Core Engine is a tiny and fast runtime associated with a Scheduler and a Garbage Collector. 

MicroEJ Architecture provides implementations of the following Foundation Libraries :

- Embedded Device Configuration (see :ref:`[EDC] <runtime_edc>`).
- Beyond Profile (see :ref:`[BON] <runtime_bon>`).
- Simple Native Interface (see :ref:`[SNI] <runtime_sni>`).
- Kernel & Features (see :ref:`[KF] <runtime_kf>`).
- Shielded Plug (see :ref:`[SP] <sp>`).

:ref:`The following figure <fig_jpf-runtime-components>` shows the components involved.

.. _fig_jpf-runtime-components:
.. figure:: images/jpf-runtime-components.*
   :alt: MicroEJ Architecture Runtime Modules: Tools, Libraries and APIs
   :align: center
   :scale: 75%

   MicroEJ Architecture Modules

Three Low Level APIs allow the MicroEJ Architecture to link with (and port
to) external code, such as any kind of RTOS or legacy C libraries: 

-  Simple Native Interface (see :ref:`[SNI] <runtime_sni>`)
-  Low Level MicroEJ Core Engine (see :ref:`LLMJVM <LLMJVM-API-SECTION>`)
-  Low Level Shielded Plug (see :ref:`LLSP <LLSP-API-SECTION>`)

For further information on Architecture installation and releases, you can check these chapters:

.. toctree::
   :maxdepth: 1

   architectureNamingConvention
   architectureChangelog

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
