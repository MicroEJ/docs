.. _wasm.wasi:

WASI Library
============

WebAssembly System Interface (WASI) provides a modular and secure system interface designed to enable Wasm module to interact with the underlying operating system in a platform-independent manner.

MicroEJ provides its own WASI Library which implements a subset of `WASI 0.1 APIs specification <https://github.com/WebAssembly/WASI/blob/main/legacy/preview1/docs.md>`_.

Moreover, some APIs have been extended to support certain POSIX functions that are not available in `wasi-libc <https://github.com/WebAssembly/wasi-libc>`_ such as ``socket``, ``bind``, ``connect``, etc.

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

The ``memory`` parameter must be set to your Wasm module memory and the ``preopensDirectories`` to the list of directories pathnames you want to preopened if any.

If a directory is not preopened, it cannot be used by the Wasm module.

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

  WASI cannot be used in more than one Wasm module in a `Standalone Application <standalone_application>`; otherwise calls to WASI methods will result in undefined behavior.

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
| **Clocks**      | ``clock_getres``, ``clock_gettime``, ``gettimeofday``                                          |
+-----------------+------------------------------------------------------------------------------------------------+
| **Process**     | ``exit``                                                                                       |
+-----------------+------------------------------------------------------------------------------------------------+
| **StdIO**       | ``printf``                                                                                     |
+-----------------+------------------------------------------------------------------------------------------------+
|| **Pthreads**   || ``pthread_create``, ``pthread_join``, ``pthread_attr_init``, ``pthread_attr_setstacksize``,   |
||                || ``pthread_attr_destroy``                                                                      +
+-----------------+------------------------------------------------------------------------------------------------+
| **Semaphores**  | ``sem_wait``, ``sem_post``, ``sem_destroy``                                                    +
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

.. _wasi.threads:

WASI Threads
------------

MicroEJ provides support of POSIX threads (pthreads) in Managed C through the implementations 
of `WebAssembly threads profile <https://github.com/WebAssembly/threads>`__ and `WASI threads specification <https://github.com/WebAssembly/wasi-threads>`__.

This allows running the following code:

.. code:: c

   #include <pthread.h>
   #include <semaphore.h>
   #include <stdio.h>
   #include <unistd.h>

   void* thread_entry_point(void *ctx) {
      // Called in a new pthread
      return 0;
   }

   int main() {
      pthread_attr_t new_thread_attr;
      pthread_t new_thread;

      // Initialize the stack size
      pthread_attr_init(&new_thread_attr);
      int res = pthread_attr_setstacksize(&new_thread_attr, 2048);
      if(res != 0){
         // Unable to set the stack size
         return -1;
      }

      pthread_create(&new_thread, &new_thread_attr, &thread_entry_point, NULL);

      // ...

      pthread_join(new_thread, NULL);

      return 0;
   }

.. note::

    By default, if not specified, the WASI libc stack size is ``128KB``. 
    It is strongly recommended to set the stack size at thread creation using the ``pthread_attr_setstacksize`` function.


Enable WASI Threads
~~~~~~~~~~~~~~~~~~~

- Compile and link your Wasm Module with these additional Clang options: ``--target=wasm32-wasi-threads -pthread``.
- In your Application, set the :ref:`option <application_options>` ``com.microej.runtime.core.wasithreads.enabled`` to ``true``.
- In your Wasm module, declare the binding to the ``wasi_thread_start`` function, and initialize WASI accordingly:

   .. code:: java

      package com.mycompany;

      import ej.wasm.WasmFunction;
      import ej.wasm.WasmMemory;
      import ej.wasm.WasmModule;
      import ej.wasi.*;
      import ej.wasi.thread.WasiThreadRedirection;

      import java.io.IOException;

      @WasmModule("my_app")
      public class MyApp {

          @WasmMemory
          private static byte[] Memory;

          // Define the binding to 'wasi_thread_start' function
          @WasmFunction
          private static final native void wasi_thread_start(int threadId, int args);

          public static void main(String[] args) {

              // Initialize WASI with the thread start redirection
              WasiThreadRedirection wtr = new WasiThreadRedirection() {
                  public void start(int threadId, int args) {
                      wasi_thread_start(threadId, args);
                  }
              };

              try {
                  Wasi.init(Memory, wtr);
              } catch (IOException e) {
                  // error during initialization
              }

              // ...
          }
      }

WASI Threads Limitations
~~~~~~~~~~~~~~~~~~~~~~~~

**Unique Wasm Module**

When WASI threads are enabled, an Application can embed at most one Wasm module.
With the :ref:`Multi-Sandbox capability <multisandbox>` enabled, this limit applies to each :ref:`class space <kf_class_space>`.

**Stack Management**

The Java ``synchronized`` keyword is no longer mandatory on methods bound to C functions, as multiple threads can now invoke C code. 
However, there is a key limitation: threads created from Java still share the same C main stack in linear memory.
As a result, Java threads must not execute C code simultaneously.
If two Java threads call a C function in parallel, it will result in C stack corruption.

In contrast, pthreads created in Managed C have their own stack, which is dynamically allocated in linear memory, allowing them to execute C code in parallel without restriction.

..
   | Copyright 2024-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.