.. _pack_fs:

===========
File System
===========

Overview
========

The FS Foundation Library defines a low-level File System framework for embedded
devices. It allows you to manage abstract files and directories without
worrying about the native underlying File System kind.

How to integrate this pack into a VEE Port
==========================================

1. Add the FS Pack module into your VEE Port:

   .. tabs::

      .. tab:: SDK 6 (build.gradle.kts)

         .. code-block:: kotlin

            microejPack("com.microej.pack:fs:6.0.4")

      .. tab:: SDK 5 (module.ivy)

         .. code-block:: xml

            <dependency org="com.microej.pack" name="fs" rev="6.0.4"/>

2. Configure the pack for your VEE Port in the `FS` section of the `Vee Port configuration file <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/blob/master/vee-port/configuration.properties>`_

   .. tabs::

      .. tab:: SDK 6

         In SDK 6, Modify the `FS` section of the `VEE Port configuration file <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/blob/master/vee-port/configuration.properties>`_

      .. tab:: SDK 5

	      In SDK 5, the configuration is done in the properties file ``fs/fs.properties``. The properties are the same as in `SDK 6 VEE Port configuration file <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/blob/master/vee-port/configuration.properties>`_, but the prefix ``com.microej.runtime`` must be removed.

   The FS module defines two pre-configured File System types: ``Unix`` and ``FatFS``.
   Some characteristics don't need to be specified for these File System types, but they can be overridden if needed.
   For example, specifying a ``Unix`` File System type will automatically set the file separator to ``/``.

   If none of the pre-configured File System types correspond to the File System used in the C project, the ``Custom``
   type can be used. When this type is selected, all the File System characteristics must be specified in the properties file.

   See the `Vee Port configuration file <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/blob/master/vee-port/configuration.properties>`_ for more details on the options.

3. Implement the abstration layer. Following implementations are available:

    * `FatFS <https://gitlab.cross/M0074_MicroEJ-Architecture-FS/M0074_CCO-FS-FatFs>`_
    * `LittleFS <https://gitlab.cross/M0074_MicroEJ-Architecture-FS/M0074_CCO-LittleFs>`_
    * `EmFile <https://gitlab.cross/M0074_MicroEJ-Architecture-FS/M0074_CCO-emFile>`_
    * `FileX <https://gitlab.cross/M0074_MicroEJ-Architecture-FS/M0074_CCO-FS-FileX>`_
    * `SAFE Flash <https://gitlab.cross/M0074_MicroEJ-Architecture-FS/M0074_CCO-FS-SafeFLASH>`_
    * `Linux (all abstraction layers are gathered in one repo) <https://github.com/MicroEJ/AbstractionLayer-Linux/tree/master/projects/microej/fs>`_

   Following functions must be implemented: 

   <C header>: ``LLFS_impl.h`` and ``LLFS_File_impl.h`` (see
   :ref:`LLFS-API-SECTION`).

4. Run the `FS testsuite <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/tree/master/vee-port/validation/fs>`_ to test the abstration layer implementation.

How to use this pack in an application
======================================

Refer to :ref:`fs_api` for FS API usage.

Functional Description
======================

The MicroEJ Application manages File System elements using
File/Directory abstraction. The FS implementation made for each MicroEJ
Platform is responsible for surfacing the native File System specific
behavior.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
