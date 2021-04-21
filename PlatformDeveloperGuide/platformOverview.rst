

Modules Overview
----------------

.. _architecture_overview:

MicroEJ Architecture
~~~~~~~~~~~~~~~~~~~~

MicroEJ Architecture features the MicroEJ Core Engine built for a specific instructions set (ISA) and compiler.

The MicroEJ Core Engine is a tiny and fast runtime associated with a Scheduler and a Garbage Collector. 

MicroEJ Architecture provides implementations of the following Foundation Libraries :

-  `EDC <https://repository.microej.com/modules/ej/api/edc/>`_: Embedded Device Configuration.
-  `BON <https://repository.microej.com/modules/ej/api/bon/>`_ Beyond Profile (see :ref:`[BON] <esr-specifications>`).
-  `SNI <https://repository.microej.com/modules/ej/api/sni/>`_ Simple Native Interface (:ref:`[SNI] <esr-specifications>`).
-  `SP <https://repository.microej.com/modules/ej/api/sni/>`_ Shielded Plug (:ref:`[SP] <esr-specifications>`).
-  `KF <https://repository.microej.com/modules/ej/api/sni/>`_ Kernel & Features (:ref:`[KF] <esr-specifications>`).

:ref:`The following figure <fig_jpf-runtime-components>` shows the components involved.

.. _fig_jpf-runtime-components:
.. figure:: images/jpf-runtime-components.*
   :alt: MicroEJ Architecture Runtime Modules: Tools, Libraries and APIs
   :align: center
   :scale: 75%

   MicroEJ Architecture Modules

Three Low Level APIs allow the MicroEJ Architecture to link with (and port
to) external code, such as any kind of RTOS or legacy C libraries: 

-  Simple Native Interface (see :ref:`[SNI] <esr-specifications>`)
-  Low Level MicroEJ Core Engine (see :ref:`LLMJVM <LLMJVM-API-SECTION>`)
-  Low Level Shielded Plug (see :ref:`LLSP <LLSP-API-SECTION>`)

See :ref:`MicroEJ Architecture Import <architecture_import>` for usage.

.. _pack_overview:

MicroEJ Packs
~~~~~~~~~~~~~

On top of a MicroEJ Architecture can be imported MicroEJ Packs which provide additional features such as:

-  :ref:`Serial Communications <pack_ecom_comm>`,
-  :ref:`Graphical User Interface <pack_gui>`,
-  :ref:`Networking <pack_net>`,
-  :ref:`File System <pack_fs>`,
-  etc.

Each MicroEJ Pack is optional and can be selected on demand during the
:ref:`MicroEJ Platform configuration <platform_configuration_modules>` step.

.. _build_process_overview:

Process Overview
----------------

This section summarizes the steps required to build a MicroEJ Platform
and obtain a binary file to deploy on a board.

:ref:`The following figure <fig_overall-process>` shows the overall process. The first
three steps are performed within the MicroEJ Platform builder. The
remaining steps are performed within the C IDE.

.. _fig_overall-process:
.. figure:: images/process-overview5.*
   :alt: Overall Process
   :scale: 80%
   :align: center

   Overall Process

The steps are as follow:

1. Create a new MicroEJ Platform configuration project. This project
   describes the MicroEJ Platform to build (MicroEJ Architecture,
   metadata, etc.).

2. Select which modules provided by the MicroEJ Architecture will be
   installed in the MicroEJ Platform.

3. Build the MicroEJ Platform according to the choices made in steps 1
   and 2.

4. Compile a MicroEJ Application against the MicroEJ Platform in order
   to obtain an application file to link in the BSP.

5. Compile the BSP and link it with the MicroEJ Application that was
   built previously in step 4 to produce a MicroEJ Firmware.

6. Final step: Deploy MicroEJ Firmware (i.e. the binary application)
   onto a board.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
