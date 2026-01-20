.. _get_support:

Get Support
===========

If any questions, the best starting point is to consult the `MicroEJ Forum <https://forum.microej.com/>`_
or the :ref:`faq`.
Feel free to create a new topic if there is no relevant content for your issue. 
MicroEJ Corp. engineers are listening to the forum activity, so you can expect to get a quick reply.


Otherwise, you can contact `our support team <https://www.microej.com/contact/#form_2>`_.

In both cases, please provide as much information as possible on your installed environment (the table below is an example):

.. list-table::
   :widths: 15 30

   * - **Delivery**
     - **Name**
   * - MICROEJ SDK
     - **SDK 6**: Gradle plugin version **1.4.0** (see :ref:`sdk_6_changelog`)
           
       **SDK 5**: SDK Distribution **24.01** / SDK Version **5.8.2** (see :ref:`get_sdk_version`)
   * - MicroEJ Architecture 
     - ARM Cortex-M4 / IAR Production version **8.4.0** (see :ref:`architecture_overview`) 
   * - Module Repository
     - https://repository.microej.com/packages/repository/3.51.0/central-repository-3.51.0.zip (see :ref:`central_repository`)
   * - C compiler
     - IAR Embedded Workbench for Arm **v9.60.0**
   * - Host Operating System
     - Windows **11** (see :ref:`system-requirements`)
     
.. _faq:

FAQ
---

.. dropdown:: What are the minimum requirements for processor, memory, and RAM?
    :animate: fade-in-slide-down

    MicroEJ can run on MCUs such as Cortex M0+ through Cortex M7, as well as on application processors such as ARMv7 or ARMv8.

    MEJ32 requires only 30KB of code and 1KB of RAM. Typical memory usage is defined by the application.


.. dropdown:: How does MicroEJ scale with multi-core CPUs?
    :animate: fade-in-slide-down

    MicroEJ supports heterogeneous multi-cores from Cortex-M0+ with RTOS to Cortex-A with Linux or QNX.


.. dropdown:: How are patches handled and how is the environment secured?
    :animate: fade-in-slide-down

    The Core technology is rarely patched due to its maturity and extensive testing.
    
    We release new editions on a 9-12 month cadence, with bug fixes delivered quickly.
    
    We have a process for reporting vulnerabilities, and they are tracked and reported in our changelog.


..
   | Copyright 2008-2026, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.