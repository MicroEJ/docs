===========
File System
===========


Principle
=========

The FS module defines a low-level File System framework for embedded
devices. It allows you to manage abstract files and directories without
worrying about the native underlying File System kind.


Functional Description
======================

The MicroEJ application manages File System elements using
File/Directory abstraction. The FS implementation made for each MicroEJ
Platform is responsible for surfacing the native File System specific
behavior.


Dependencies
============

-  ``LLFS_impl.h`` and ``LLFS_File_impl.h`` implementations (see
   :ref:`LLFS-API-SECTION`).


Installation
============

FS is an additional module. In the platform configuration file, check
:guilabel:`FS` to install it. When checked, the properties file ``fs`` > ``fs.properties`` are required during platform creation in
order to configure the module.

The properties file must / can contain the following properties:

-  ``fs`` [optional, default value is "Custom"]: Defines the kind of
   File System native stack used in the C project.

   -  ``Custom``: select this configuration to make a specific File
      System portage.

   -  ``FatFS``: select this configuration to use FatFS native File
      System-compliant settings.

-  ``root.dir`` [optional, for a FatFS File System. Mandatory, for a
   Custom File System.]: Defines the native File System root volume
   (default value is "/" for FatFS).

-  ``user.dir`` [optional, for a FatFS File System. Mandatory, for a
   Custom File System.]: Defines the native File System user directory
   (default value is "/usr" for FatFS).

-  ``tmp.dir`` [optional, for a FatFS File System. Mandatory, for a
   Custom File System.]: Defines the native File System temporary
   directory (default value is "/tmp" for FatFS).

-  ``file.separator`` [optional, for a FatFS File System. Mandatory, for
   a Custom File System.]: Defines the native File System file separator
   (default value is "/" for FatFS).

-  ``path.separator`` [optional, for a FatFS File System. Mandatory, for
   a Custom File System.]: Defines the native File System path separator
   (default value is ":" for FatFS).


Use
===

A classpath variable named ``FS-2.0`` is available.
