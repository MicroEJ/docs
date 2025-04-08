.. _pack_fs:

===========
File System
===========

Overview
========

The FS (File System) Pack defines a low-level File System framework for embedded devices. It allows the MicroEJ Application to manage abstract files and directories without worrying about the native underlying File System kind.

Integrate the FS Pack into your VEE Port
========================================

Prerequisites
-------------

For the FS Pack to be compatible with your VEE Port, the following elements must be integrated into your VEE Port:

- Core Engine: refer to :ref:`vee_port_core_from_scratch` documentation.

- Async Worker: refer to :ref:`c_module_async_worker` documentation.

Integration steps
-----------------

1. Add the FS Pack module into your VEE Port:

   .. tabs::

      .. tab:: SDK 6 (build.gradle.kts)

         .. code-block:: kotlin

            microejPack("com.microej.pack:fs:6.0.4")

      .. tab:: SDK 5 (module.ivy)

         .. code-block:: xml

            <dependency org="com.microej.pack" name="fs" rev="6.0.4"/>

2. Configure the pack for your VEE Port

   .. tabs::

      .. tab:: SDK 6

         In SDK 6, Modify the `FS` section of the `VEE Port configuration file <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/blob/1.1.0/vee-port/configuration.properties>`_

      .. tab:: SDK 5

	      In SDK 5, the configuration is done in the properties file ``fs/fs.properties``. The properties are the same as in `SDK 6 VEE Port configuration file <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/blob/1.1.0/vee-port/configuration.properties>`_, but the prefix ``com.microej.runtime`` must be removed.

   The FS Pack defines two pre-configured File System types: ``Unix`` and ``FatFS``.
   Some characteristics don't need to be specified for these File System types, but they can be overridden if needed.
   For example, specifying a ``Unix`` File System type will automatically set the file separator to ``/``.

   If none of the pre-configured File System types correspond to the File System used in the C project, the ``Custom``
   type can be used. When this type is selected, all the File System characteristics must be specified in the properties file.

   Refer to :ref:`pack_fs_config` for more details on the FS pack parameters.

3. Add the Abstraction Layer implementation to your VEE Port. The following implementations are available:

    * `FatFS <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/tree/NXPVEE-MIMXRT1170-EVK-3.0.0/bsp/vee/port/fs>`_
    * `Linux (all abstraction layers are gathered in one repo) <https://github.com/MicroEJ/AbstractionLayer-Linux/tree/3.1.0/vee/port/fs>`_
    * LittleFS (on demand)
    * EmFile (on demand)
    * FileX (on demand)
    * SAFE Flash (on demand)

   Refer to :ref:`pack_fs_c_api` for more details on the FS pack Abstraction Layer API.

4. Run the `FS testsuite <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/tree/1.1.0/vee-port/validation/fs>`_ to test the Abstraction Layer implementation.

Use the FS API in your Application
==================================

Refer to :ref:`Application Developer Guide<fs_api>` for FS API usage.

Pack FS Description
===================

.. _pack_fs_config:

Configuration
-------------

Here are the parameters to configure the FS pack:

.. rli:: https://raw.githubusercontent.com/MicroEJ/Tool-Project-Template-VEEPort/refs/tags/1.1.0/vee-port/configuration.properties
   :language: properties
   :lines: 70-129
   :linenos:
   :lineno-start: 70

.. _pack_fs_c_api:

Abstraction Layer API
---------------------

Every implementation of the FS Abstraction Layer must implement the functions declared in ``LLFS_impl.h`` and ``LLFS_File_impl.h`` (Refer to :ref:`LLFS-API-SECTION`).

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
