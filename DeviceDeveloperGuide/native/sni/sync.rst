Synchronization
===============

A call to a native function uses the same RTOS task as the RTOS task
used to run all Java green threads. So during this call, the MicroEJ
core engine cannot schedule other Java threads.

SNI defines C functions that provide controls for the green threads'
activities:

-  int32_t SNI_suspendCurrentJavaThread(int64_t timeout): Suspends the
   execution of the Java thread that initiated the current C call. This
   function does not block the C execution. The suspension is effective
   only at the end of the native method call (when the C call returns).
   The green thread is suspended until either an RTOS task calls
   SNI_resumeJavaThread, or the specified number of milliseconds has
   elapsed.

-  int32_t SNI_getCurrentJavaThreadID(void): Permits retrieval of the ID
   of the current Java thread within the C function (assuming it is a
   "native Java to C call"). This ID must be given to the
   SNI_resumeJavaThread function in order to resume execution of the
   green thread.

-  int32_t SNI_resumeJavaThread(int32_t id): Resumes the green thread
   with the given ID. If the thread is not suspended, the resume stays
   pending.

.. figure:: sni/images/sni_sync.svg
   :alt: Green Threads and RTOS Task Synchronization
   :width: 80.0%

   Green Threads and RTOS Task Synchronization

`figure_title <#sni_sync>`__ shows a green thread (GT3) which has called
a native method that executes in C. The C code suspends the thread after
having provisioned its ID (e.g. 3). Another RTOS task may later resume
the Java green thread.
