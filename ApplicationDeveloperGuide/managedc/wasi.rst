.. _wasm.wasi:

WASI
=======

WebAssembly System Interface (WASI) provides a modular and secure system interface designed to enable WASM module to interact with the underlying operating system in a platform-independent manner.

We provide a ``WASI Add-on Library`` which implements a subset of `WASI 0.1 APIs specification <https://github.com/WebAssembly/WASI/blob/main/legacy/preview1/docs.md>`_.

All the implemented functions are exported under the module name ``wasi_snapshot_preview1``.

We have extended the APIs to support certain POSIX functions that are not available in `wasi-libc <https://github.com/WebAssembly/wasi-libc>`_ such as ``socket``, ``bind``, ``connect`` etc.

Usage
------

To use the WASI Add-on Library, add the following to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.library.runtime:wasi:0.1.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.library.runtime" name="wasi" rev="0.1.0"/>


In your application code, you must first call the WASI initialization method ``Wasi.init(byte[] memory, String... preopensDirectories)`` before using WASI.

The ``memory`` parameter must be set to your WASM module memory and the ``preopensDirectories`` to the list of directories pathnames you want to preopened if any.

If a directory is not preopened, it cannot be used by the WASM module.

Here is an example:

- C source code (``my_app.c``):

   .. code:: c

        #include <stdlib.h>
        #include <stdio.h>
        #include <time.h>      

        void print_time() {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            printf("%lld.%.9ld", (long long)ts.tv_sec, ts.tv_nsec);
        }


- Java source code (``MyApp.java``):

   .. code-block:: java
        :emphasize-lines: 17

        package com.mycompany;
        import ej.wasm.WasmFunction;
        import ej.wasm.WasmMemory;
        import ej.wasm.WasmModule;
        import ej.wasi.Wasi;
        import java.io.IOException;

        @WasmModule("my_app")
        public class MyApp {

            @WasmMemory
            private static byte[] Memory;

            public static void main(String[] args) throws IOException {
            
                // Initialize WASI with the memory of my_app module and no preopened directories
                Wasi.init(Memory, null);

                // Call and the "print_time" Wasm function
                printTime();
            }

            @WasmFunction("print_time")
            public static native synchronized void printTime();

        }

In this example, the implementation of The POSIX-compliant C functions ``clock_gettime(...)`` and ``printf(...)`` relies on the WASI functions ``clock_time_get(...)`` and ``fd_write(...)`` which are provided by the WASI Add-on Library.

.. note:: 

  WASI cannot be used in more than one WASM module in a `Standalone Application <standalone_application>`; otherwise calls to WASI methods will result in undefined behavior.

  In a `Sandboxed Application <sandboxed_application>`, WASI methods must not be exposed in the `Kernel API <kernel.api>` and each Application and the Kernel can use WASI in only one module.

  Using WASI in multiple modules within an Application or the Kernel will result in undefined behavior.


WASI APIs
---------

List of the currently suppported WASI APIs:

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

List of the currently supported high-level WASI-based POSIX APIs:

.. list of supported high-level WASI-based POSIX APIs

+-----------------+------------------------------------------------------------------------------------------------+
| **Group**       | **High-Level WASI-Based POSIX APIs**                                                           |
+-----------------+------------------------------------------------------------------------------------------------+
|| **FileSystem** || ``open``, ``fopen``, ``fdopendir``, ``close``, ``fclose``, ``read``, ``write``, ``fread``,    |
||                || ``fwrite``, ``lseek``, ``stat``, ``fstat``, ``readdir``, ``fstatat``, ``fileno``, ``fflush``, |
||                || ``access``                                                                                    |
+-----------------+------------------------------------------------------------------------------------------------+
| **Sockets**     | ``send``, ``recv``, ``shutdown``, ``close``                                                    |
+-----------------+------------------------------------------------------------------------------------------------+
| **Clocks**      | ``clock_getres``, ``clock_gettime`` ``gettimeofday``                                           |
+-----------------+------------------------------------------------------------------------------------------------+
| **Process**     | ``exit``                                                                                       |
+-----------------+------------------------------------------------------------------------------------------------+
| **StdIO**       | ``printf``                                                                                     |
+-----------------+------------------------------------------------------------------------------------------------+

High-Level Extended WASI POSIX APIs
-----------------------------------

List of the high-level extended WASI-based POSIX APIs that provide functionalities not available in the `wasi-libc <https://github.com/WebAssembly/wasi-libc>`_:

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