.. _LLFS-API-SECTION:

LLFS: File System
=================

Naming Convention
-----------------

The Low Level File System API (LLFS), relies on functions that need to
be implemented by engineers in a driver. The names of these functions
match the ``LLFS_IMPL_*`` and the ``LLFS_File_IMPL_*`` pattern.

Header Files
------------

Two C header files are provided:

-  LLFS_impl.h

   Defines a set of functions that the BSP must implement to initialize
   the FS native component. It also defines some functions to manage
   files, directories and retrieve information about the underlying File
   System (free space, total space, etc.).

-  LLFS_File_impl.h

   Defines a set of functions that the BSP must implement to do some I/O
   operations on files (open, read, write, close, etc.).
