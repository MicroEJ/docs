.. _core_engine_implementation:

==============
Implementation
==============

The Core Engine implements the :ref:`[SNI] specification <runtime_sni>`. 
It is created and initialized with the C function ``SNI_createVM``.
Then it is started and executed in the current task by calling ``SNI_startVM``.
The function ``SNI_startVM`` returns when the Application exits or if
an error occurs (see section :ref:`core_engine_error_codes`).
The function ``SNI_destroyVM`` handles the Core Engine termination 
and must be called after the return of the function ``SNI_startVM``.

Only one instance of the Core Engine can be created in the system, 
and both ``SNI_createVM`` and ``SNI_destroyVM`` should only be called once. 
When restarting the Core Engine, don't call ``SNI_createVM`` or ``SNI_destroyVM`` 
before calling ``SNI_startVM`` again.
For more information, refer to the :ref:`core_engine_restart` section.

The file ``LLMJVM_impl.h`` that comes with the Architecture defines the API
to be implemented. See section :ref:`LLMJVM-API-SECTION`.

Initialization
==============

The Low Level Core Engine API deals with two objects: the
structure that represents the Core Engine, and the task that runs the
Core Engine. Two callbacks allow engineers to interact with the
initialization of both objects:

-  ``LLMJVM_IMPL_initialize``: Called once the structure representing
   the Core Engine is initialized.

-  ``LLMJVM_IMPL_vmTaskStarted``: Called when the Core Engine starts its
   execution. This function is called within the task of the
   Core Engine.

Scheduling
==========

To support the green thread round-robin policy, the Core Engine assumes
there is an RTOS timer or some other mechanism that counts (down) and
fires a call-back when it reaches a specified value. The Core Engine
initializes the timer using the ``LLMJVM_IMPL_scheduleRequest`` function
with one argument: the absolute time at which the timer should fire.
When the timer fires, it must call the ``LLMJVM_schedule`` function,
which tells the Core Engine to execute a green thread context switch (which
gives another MicroEJ thread a chance to run).

When several MicroEJ threads with the same priority are eligible for execution,
the round-robin algorithm will automatically switch between these threads after a certain amount of time, 
called the `time slice`. 
The time slice is expressed in milliseconds, and its default value is ``20`` ms. 
It can be configured at link time with the symbol
``_java_round_robin_period``, defined in the :ref:`linker configuration file <linker_lscf>` 
``linkVMConfiguration.lscf`` located in the VEE Port folder ``/MICROJVM/link/``.
To override the content of this file, create, in the VEE Port configuration project,
a folder named ``/dropins/MICROJVM/link/``, and copy into this folder the file
``linkVMConfiguration.lscf`` retrieved from an existing VEE Port.
Since a symbol cannot be null, the actual time slice value in milliseconds is
``_java_round_robin_period - 1``. Set the symbol to 1 (i.e., time slice to 0) 
to disable the round-robin scheduling.

.. warning::
	Modifying the time slice value is an advanced configuration that
	can impact the performances.
	
	Decreasing the time slice will increase the number of context switches.
	Therefore scheduler will use more CPU time.
	
	Increasing the time slice can create a latency with intensive threads
	monopolizing the CPU.

Idle Mode
=========

When the Core Engine has no activity to execute, it calls the
``LLMJVM_IMPL_idleVM`` function, which is assumed to put the Core Engine task
into a sleep state. ``LLMJVM_IMPL_wakeupVM`` is called
to wake up the Core Engine task. When the Core Engine task really starts to
execute again, it calls the ``LLMJVM_IMPL_ackWakeup`` function to
acknowledge the restart of its activity.

Time
====

The Core Engine defines two different times:

-  the application time: the difference, measured in milliseconds,
   between the current time and midnight, January 1, 1970, UTC.

-  the monotonic time: this time always moves forward and is not impacted 
   by application time modifications (NTP or Daylight Savings Time updates).
   It can be implemented by returning the running time since the start of 
   the device.

The Core Engine relies on the following C functions to provide those times
to the Application:

-  ``LLMJVM_IMPL_getCurrentTime``: must return the monotonic time in 
   milliseconds if the given parameter is ``1``, otherwise must return the 
   application time in milliseconds. 
   This function is called by the method `java.lang.System.currentTimeMillis()`_
   It is also used by the Core Engine 
   scheduler, and should be implemented efficiently.

-  ``LLMJVM_IMPL_getTimeNanos``: must return a monotonic time in
   nanoseconds.

-  ``LLMJVM_IMPL_setApplicationTime``: must set the difference between
   the current time and midnight, January 1, 1970, UTC.
   Implementations may apply this time to the whole underlying system
   or only to the Core Engine (i.e., the value returned by
   ``LLMJVM_IMPL_getCurrentTime(0)``).

.. _java.lang.System.currentTimeMillis(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#currentTimeMillis--

.. _core_engine_error_codes:

Error Codes
===========

The C function ``SNI_createVM`` returns a negative value if an error 
occurred during the Core Engine initialization or execution.
The file ``LLMJVM.h`` defines the Core Engine error code constants.
The following table describes these error codes.

.. table:: Core Engine Error Codes

   +-------------+-------------------------------------------------------------+
   | Error Code  | Meaning                                                     |
   +=============+=============================================================+
   | 0           | The Application ended normally (i.e., all the               |
   |             | non-daemon threads are terminated or                        |
   |             | ``System.exit(exitCode)`` has been called).                 |
   |             | See section :ref:`edc_exit_codes`.                          |
   +-------------+-------------------------------------------------------------+
   | -1          | The ``microejapp.o`` produced by SOAR is not compatible     |
   |             | with the Core Engine (``microejruntime.a``).                |
   |             | The object file has been built from another                 |
   |             | Architecture.                                               |
   +-------------+-------------------------------------------------------------+
   | -2          | Internal error. Invalid link configuration in the           |
   |             | Architecture or the VEE Port.                               |
   +-------------+-------------------------------------------------------------+
   | -3          | Evaluation version limitations reached: termination of      |
   |             | the application. See section :ref:`limitations`.            |
   +-------------+-------------------------------------------------------------+
   | -5          | Not enough resources to start the very first MicroEJ        |
   |             | thread that executes ``main`` method. See section           |
   |             | :ref:`option_java_heap`.                                    |
   +-------------+-------------------------------------------------------------+
   | -12         | Number of threads limitation reached. See sections          |
   |             | :ref:`limitations` and :ref:`option_number_of_threads`.     |
   +-------------+-------------------------------------------------------------+
   | -13         | Fail to start the Application because the                   |
   |             | specified managed heap is too large or too small.           |
   |             | See section :ref:`option_java_heap`.                        |
   +-------------+-------------------------------------------------------------+
   | -14         | Invalid Application stack configuration. The                |
   |             | stack start or end is not eight-byte aligned, or stack      |
   |             | block size is too small. See section                        |
   |             | :ref:`option_number_of_stack_blocks`.                       |
   +-------------+-------------------------------------------------------------+
   | -16         | The Core Engine cannot be restarted.                        |
   +-------------+-------------------------------------------------------------+
   | -17         | The Core Engine is not in a valid state because             |
   |             | of one of the following situations:                         |
   |             |                                                             |
   |             | - ``SNI_startVM`` called before ``SNI_createVM``.           |
   |             |                                                             |
   |             | - ``SNI_startVM`` called while the                          |
   |             |   Appplication is running.                                  |
   |             |                                                             |
   |             | - ``SNI_createVM`` called several times.                    |
   +-------------+-------------------------------------------------------------+
   | -18         | The memory used for the managed heap or immortal heap       |
   |             | does not work properly. Read/Write memory checks            |
   |             | failed. This may be caused by an invalid external RAM       |
   |             | configuration. Verify ``_java_heap`` and                    |
   |             | ``_java_immortals`` sections locations.                     |
   +-------------+-------------------------------------------------------------+
   | -19         | The memory used for the  Application static                 |
   |             | fields does not work properly. Read/Write memory checks     |
   |             | failed. This may be caused by an invalid external RAM       |
   |             | configuration. Verify ``.bss.soar`` section location.       |
   +-------------+-------------------------------------------------------------+
   | -20         | KF configuration internal error. Invalid link               |
   |             | configuration in the Architecture or the VEE Port.          |
   +-------------+-------------------------------------------------------------+
   | -21         | Number of monitors per thread limitation reached.           |
   |             | See sections :ref:`limitations` and                         |
   |             | :ref:`Options<option_maximum_number_of_monitors_per_thread>`|
   |             | .                                                           |
   +-------------+-------------------------------------------------------------+
   | -22         | Internal error. Invalid FPU configuration in the            |
   |             | Architecture.                                               |
   +-------------+-------------------------------------------------------------+
   | -23         | The function ``LLMJVM_IMPL_initialize`` defined in the      |
   |             | Abstraction Layer implementation returns an error.          |
   +-------------+-------------------------------------------------------------+
   | -24         | The function ``LLMJVM_IMPL_vmTaskStarted`` defined in the   |
   |             | Abstraction Layer implementation returns an error.          |
   +-------------+-------------------------------------------------------------+
   | -25         | The function ``LLMJVM_IMPL_shutdown`` defined in the        |
   |             | Abstraction Layer implementation returns an error.          |
   +-------------+-------------------------------------------------------------+


.. _core_engine_restart:

Restart the Core Engine
======================= 

The Core Engine supports the restart of the Application after the end of its execution. 
The application stops when all non-daemon threads are terminated or when ``System.exit(exitCode)`` is called. 
When the application ends, the C function ``SNI_startVM`` returns.

To restart the application, call again the ``SNI_startVM`` function (see the following pattern).

.. code:: c
	
	// create Core Engine (called only once)
	vm = SNI_createVM();
	...
	// start a new execution of the Application at each iteration of the loop
	while(...){
		...
		core_engine_error_code = SNI_startVM(vm, argc, argv);
		...
		// Get exit status passed to System.exit() 
		app_exit_code = SNI_getExitCode(vm);
		...
	}
	... 
	// delete Core Engine (called before stopping the whole system)
	SNI_destroyVM(vm);


.. note::

   Please note that while the Core Engine supports restart, :ref:`MicroUI <section_microui>` does not. 
   Attempting to restart the Application on a VEE Port with UI support may result in undefined behavior.


.. note::

   Please note that ``SNI_createVM`` and ``SNI_destroyVM`` should only be called once. 
   When restarting the Core Engine, don't call ``SNI_createVM`` or ``SNI_destroyVM`` before calling ``SNI_startVM`` again.

.. _vm_dump:

Dump the States of the Core Engine
==================================

The internal Core Engine function called ``LLMJVM_dump`` allows
you to dump the state of all MicroEJ threads: name, priority, stack
trace, etc. This function must only be called from the MicroJvm virtual machine thread context and only from a native function or callback.
Calling this function from another context may lead to undefined behavior and should be done only for debug purpose.

This is an example of a dump:

.. code-block::

      =================================== VM Dump ====================================
      Java threads count: 3
      Peak java threads count: 3
      Total created java threads: 3
      Last executed native function: 0x90035E3D
      Last executed external hook function: 0x00000000
      State: running
      --------------------------------------------------------------------------------
      Java Thread[1026]
      name="main" prio=5 state=RUNNING max_java_stack=456 current_java_stack=184
      
      java.lang.MainThread@0xC0083C7C:
          at (native) [0x90003F65]
          at com.microej.demo.widget.main.MainPage.getContentWidget(MainPage.java:95)
              Object References:
                  - com.microej.demo.widget.main.MainPage@0xC00834E0
                  - com.microej.demo.widget.main.MainPage$1@0xC0082184
                  - java.lang.Thread@0xC0082194
                  - java.lang.Thread@0xC0082194
          at com.microej.demo.widget.common.Navigation.createRootWidget(Navigation.java:104)
              Object References:
                  - com.microej.demo.widget.main.MainPage@0xC00834E0
          at com.microej.demo.widget.common.Navigation.createDesktop(Navigation.java:88)
              Object References:
                  - com.microej.demo.widget.main.MainPage@0xC00834E0
                  - ej.mwt.stylesheet.CachedStylesheet@0xC00821DC
          at com.microej.demo.widget.common.Navigation.main(Navigation.java:40)
              Object References:
                  - com.microej.demo.widget.main.MainPage@0xC00834E0
          at java.lang.MainThread.run(Thread.java:855)
              Object References:
                  - java.lang.MainThread@0xC0083C7C
          at java.lang.Thread.runWrapper(Thread.java:464)
              Object References:
                  - java.lang.MainThread@0xC0083C7C
          at java.lang.Thread.callWrapper(Thread.java:449)
      --------------------------------------------------------------------------------
      Java Thread[1281]
      name="UIPump" prio=5 state=WAITING timeout(ms)=INF max_java_stack=120 current_java_stack=117
      external event: status=waiting
      
      java.lang.Thread@0xC0083628:
          at ej.microui.MicroUIPump.read(Unknown Source)
              Object References:
                  - ej.microui.display.DisplayPump@0xC0083640
          at ej.microui.MicroUIPump.run(MicroUIPump.java:176)
              Object References:
                  - ej.microui.display.DisplayPump@0xC0083640
          at java.lang.Thread.run(Thread.java:311)
              Object References:
                  - java.lang.Thread@0xC0083628
          at java.lang.Thread.runWrapper(Thread.java:464)
              Object References:
                  - java.lang.Thread@0xC0083628
          at java.lang.Thread.callWrapper(Thread.java:449)
      --------------------------------------------------------------------------------
      Java Thread[1536]
      name="Thread1" prio=5 state=READY max_java_stack=60 current_java_stack=57
      
      java.lang.Thread@0xC0082194:
          at java.lang.Thread.runWrapper(Unknown Source)
              Object References:
                  - java.lang.Thread@0xC0082194
          at java.lang.Thread.callWrapper(Thread.java:449)
      ================================================================================
      
      ============================== Garbage Collector ===============================
      State: Stopped
      Last analyzed object: null
      Total memory: 15500
      Current allocated memory: 7068
      Current free memory: 8432
      Allocated memory after last GC: 0
      Free memory after last GC: 15500
      ================================================================================
      
      =============================== Native Resources ===============================
      Id         CloseFunc  Owner            Description
      --------------------------------------------------------------------------------
      ================================================================================

See Stack Trace Reader documentation for :ref:`SDK 6 <sdk6.section.stacktrace.reader.tool>` or :ref:`SDK 5 <stack_trace_reader>` for additional info related to working with VM dumps.

.. _vm_dump_fault_handler:

Dump The State Of All MicroEJ Threads From A Fault Handler
----------------------------------------------------------

It is recommended to call the ``LLMJVM_dump`` API as a last resort in a fault handler.
Calling ``LLMJVM_dump`` is undefined if the VM is not paused.
The call to ``LLMJVM_dump`` MUST be done last in the fault handler.

.. _vm_dump_debugger:

Trigger VM Dump From Debugger
-----------------------------


To trigger a VM dump from the debugger, set the PC register to the ``LLMJVM_dump`` physical memory address.

The symbol for the ``LLMJVM_dump`` API is defined in the header file ``LLMJVM.h``.
Search for this symbol in the appropriate C toolchain ``.map`` file.

.. note::

   ``LLMJVM_dump`` (in ``LLMJVM.h``) needs to be called explicitly.
   A linker optimization may remove the symbol if it is not used anywhere in the code.

Requirements:

* Embedded debugger is attached and the processor is halted in an exception handler.
* A way to read stdout (usually UART).

.. _core_engine.check_integrity:

Check Internal Structure Integrity
==================================

The internal Core Engine function called ``LLMJVM_checkIntegrity`` checks the internal structure integrity of the Core Engine and returns its checksum.

- If an integrity error is detected, the ``LLMJVM_on_CheckIntegrity_error`` hook is called and this method returns ``0``.
- If no integrity error is detected, a non-zero checksum is returned.

This function must only be called from the Core Engine thread context and only from a native function or callback.
Calling this function multiple times in a native function should always produce the same checksum.
If the returned checksums are different, a corruption must have occurred.

Please note that returning a non-zero checksum does not mean the Core Engine data has not been corrupted,
as it is not possible for the Core Engine to detect the complete memory integrity.

The internal structures of the Core Engine that can be altered legitimately by a native function do not impact the checksum calculation. 
The following internal structures may be modified without affecting the checksum:

- basetype fields in Java objects or content of Java arrays of base type,
- internal structures modified by a ``LLMJVM`` function call (e.g., set a pending Java exception, suspend or resume the Java thread, register a resource, ...).

This function affects the performances and should only be used for debug purpose.
A typical use of this API is to verify that a native implementation does not corrupt the internal structures:

.. code-block:: c

    #include <stdio.h>
    #include "LLMJVM.h"
    
    void Java_com_mycompany_MyClass_myNativeFunction(void) {
        int32_t crcBefore = LLMJVM_checkIntegrity();
        myNativeFunctionDo();
        int32_t crcAfter = LLMJVM_checkIntegrity();
        if(crcBefore != crcAfter){
            // Corrupted Core Engine internal structures
            while(1);
        }
    }
    
    // Hook called by the Core Engine when an integrity error is detected
    void LLMJVM_on_CheckIntegrity_error(uint32_t errorCode, void* errorAddress) {
        printf("Integrity error detected at address %p (error code: %d)\n", errorAddress, errorCode);
    }

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.