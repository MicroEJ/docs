.. _wasm.wasi:

WASI
=======

WebAssembly System Interface (WASI) provides a modular and secure system interface designed to enable WASM module to interact with the underlying operating system in a platform-independent manner.

We provide a ``WASI Add-on Library`` which implements a subset of `WASI 0.1 APIs <https://github.com/WebAssembly/WASI/blob/main/legacy/preview1/docs.md>`_.

All the implemented functions are exported under the module name ``wasi_snapshot_preview1``.

The APIs are extended to support certain POSIX functions that are not available in `wasi-libc <https://github.com/WebAssembly/wasi-libc>`_ such as ``socket``, ``bind``, ``connect`` etc.

To use the WASI Add-on Library, add the following to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.library.wasm:wasi:1.0.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.library.wasm" name="wasi" rev="1.0.0"/>


The sections below list the WASI APIs and the high level WASI-based POSIX APIs that are currently supported.

WASI APIs
---------

.. list of supported WASI APIs

+-----------------+----------------------------------------------------------------------------------------------+
| **Group**       | **WASI APIs**                                                                                |
+-----------------+----------------------------------------------------------------------------------------------+
|| **FileSystem** || ``path_open``, ``fd_readdir``, ``fd_close``, ``fd_read``, ``fd_pread``, ``fd_write``,       |
||                || ``fd_pwrite``, ``fd_seek``, ``fd_fdstat_get``, ``fd_fdstat_set_flags``, ``fd_prestat_get``, |
||                || ``fd_prestat_dir_name``, ``fd_tell``, ``fd_filestat_get``, ``path_unlink_file``,            |
||                || ``path_remove_directory``, ``path_filestat_get``                                            |
+-----------------+----------------------------------------------------------------------------------------------+
| **Sockets**     | ``sock_accept``, ``sock_shutdown``, ``poll_oneoff``, ``sock_recv``, ``sock_send``            |
+-----------------+----------------------------------------------------------------------------------------------+
| **Clocks**      | ``clock_time_get``, ``clock_res_get``                                                        |
+-----------------+----------------------------------------------------------------------------------------------+
| **Process**     | ``proc_exit``                                                                                |
+-----------------+----------------------------------------------------------------------------------------------+

High-Level WASI-Based POSIX APIs
--------------------------------

.. list of supported high-level WASI-based POSIX APIs

+-----------------+-----------------------------------------------------------------------------------------------+
| **Group**       | **High-Level WASI-Based POSIX APIs**                                                          |
+-----------------+-----------------------------------------------------------------------------------------------+
|| **FileSystem** || ``open``, ``fopen``, ``fdopendir``, ``close``, ``fclose``, ``read``, ``write``, ``fread``,   |
||                || ``fwrite`, ``lseek``, ``stat``, ``fstat``, ``readdir``, ``fstatat``, ``fileno``, ``fflush``, |
||                || ``access``                                                                                   |
+-----------------+-----------------------------------------------------------------------------------------------+
| **Sockets**     | ``send``, ``recv``, ``shutdown``, ``close``                                                   |
+-----------------+-----------------------------------------------------------------------------------------------+
| **Clocks**      | ``clock_getres``, ``clock_gettime`` ``gettimeofday``                                          |
+-----------------+-----------------------------------------------------------------------------------------------+
| **Process**     | ``exit``                                                                                      |
+-----------------+-----------------------------------------------------------------------------------------------+
| **StdIO**       | ``printf``                                                                                    |
+-----------------+-----------------------------------------------------------------------------------------------+

High-Level Extended WASI POSIX APIs
-----------------------------------

.. list of supported high-level extended WASI POSIX APIs

+-------------+-----------------------------------------------+
| **Group**   | **High-Level Extended WASI POSIX APIs**       |
+-------------+-----------------------------------------------+
| **Sockets** | ``socket``, ``bind``, ``listen``, ``connect`` |
+-------------+-----------------------------------------------+
| **Miscs**   | ``dup``, ``dup2``, ``pipe``                   |
+-------------+-----------------------------------------------+

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.