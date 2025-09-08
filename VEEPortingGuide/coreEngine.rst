.. _core_engine:

===========
Core Engine
===========


The Core Engine is the core component of the Architecture.
It executes at runtime the Application code.

.. note::

   In the following explanations, the term `task` refers to native tasks scheduled by the underlying OS or RTOS, 
   while `thread` refers to MicroEJ threads scheduled by the Core Engine.

Block Diagram
=============

.. figure:: images/mjvm_block-diagram.png
   :alt: Core Engine Block Diagram
   :align: center
   :scale: 80%

   Core Engine Block Diagram

Link Flow
=========

:ref:`The following diagram <fig_mjvm_flow2>` shows the overall build flow. 
Application development is performed within MICROEJ SDK.
The remaining steps are performed within the C third-party IDE.

.. _fig_mjvm_flow2:
.. figure:: images/mjvm_flow2.*
   :alt: Core Engine Flow
   :align: center
   :scale: 80%

   Core Engine Flow

1. Step 1 consists in writing an Application against a set of
   Foundation Libraries available in the VEE Port.

2. Step 2 consists in compiling the Application code and the
   required libraries in an ELF library, using the SOAR.

3. Step 3 consists in linking the previous ELF file with the 
   Core Engine library and a third-party BSP (OS, drivers, etc.). This
   step requires a third-party linker provided by a C toolchain.

Architecture
============

The Core Engine and its components have been compiled for one
specific CPU architecture and for use with a specific C compiler.

Refer to the chapter :ref:`architectures_toolchains` for list of supported Architectures and the details of ABI and compiler options.

.. _core_engine_threading_integration:

Threading Integration
=====================

The Core Engine implements a :ref:`green thread model <runtime_gt>`. It runs in a single task. 

Green threads are threads that are internally managed by the Core Engine
instead of being natively managed by the underlying
OS/RTOS scheduler. 
The Core Engine defines a multi-threaded environment without relying on
any native OS capabilities.

Therefore, the whole Managed world runs in one single task, within
which the Core Engine re-creates a layer of (green) threads.
One immediate advantage is that the Java-world CPU consumption is fully
controlled by the task it is running in, allowing embedded
engineers to easily arbitrate between the different parts of their
application. In particular in an open-to-third-parties framework, the
maximum CPU time given to the Managed world is fully under control at no
risk, whatever the number and/or the activities of the threads.

The next illustration shows 4 tasks, with the last one running the Core Engine with 2 threads. 
When the last task is scheduled by the underlying OS, the Core Engine executes and schedules the threads.

.. figure:: images/mjvm_gt.png
   :alt: A Green Threads Architecture Example
   :align: center

   A Green Threads Architecture Example

The activity of the Core Engine is defined by the Application. When
the Application is blocked (i.e., when all the MicroEJ threads
sleep), the task running the Core Engine sleeps.

.. _core_engine_capabilities:

Capabilities
============

The Core Engine defines 3 exclusive capabilities:

-  Mono-Sandbox: capability to produce a monolithic Executable
   (default one).

-  Multi-Sandbox: capability to produce a extensible Executable on
   which new applications can be dynamically installed. See section
   :ref:`multisandbox`.

-  Tiny-Sandbox: capability to produce a compacted Executable
   (optimized for size). See section :ref:`tinysandbox`.

All the Core Engine capabilities may not be available on all
architectures. Refer to section :ref:`appendix_matrixcapabilities`
for more details.

To select the Core Engine capability, define the property ``com.microej.runtime.capability``
in the ``configuration.properties`` file (SDK 6) or in the ``mjvm/mjvm.properties`` file (SDK 5) 
of the VEE Port project, with one of the following values:

- ``mono`` for Mono-Sandbox (default value)

- ``multi`` for Multi-Sandbox

- ``tiny`` for Tiny-Sandbox

If the property ``com.microej.runtime.capability`` is not defined,
the Mono-Sandbox Core Engine capability is used.

.. _core_engine_implementation:

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
--------------

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
----------

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
---------

When the Core Engine has no activity to execute, it calls the
``LLMJVM_IMPL_idleVM`` function, which is assumed to put the Core Engine task
into a sleep state. ``LLMJVM_IMPL_wakeupVM`` is called
to wake up the Core Engine task. When the Core Engine task really starts to
execute again, it calls the ``LLMJVM_IMPL_ackWakeup`` function to
acknowledge the restart of its activity.

Time
----

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
-----------

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
   |             | :ref:`option_managed_heap`.                                 |
   +-------------+-------------------------------------------------------------+
   | -12         | Number of threads limitation reached. See sections          |
   |             | :ref:`limitations` and :ref:`option_number_of_threads`.     |
   +-------------+-------------------------------------------------------------+
   | -13         | Fail to start the Application because the                   |
   |             | specified Managed Heap is too large or too small.           |
   |             | See section :ref:`option_managed_heap`.                     |
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
   | -18         | The memory used for the Managed Heap or Immortals Heap       |
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


Example
-------

The following example shows how to create and launch the Core
Engine from the C world. This function (``microej_main``) should be called
from a dedicated task.

.. code:: c

	#include <stdio.h>
	#include "microej_main.h"
	#include "LLMJVM.h"
	#include "sni.h"

	#ifdef __cplusplus
	   extern "C" {
	#endif

	/**
	 * @brief Creates and starts a MicroEJ instance. This function returns when the MicroEJ execution ends.
	 * @param argc arguments count
	 * @param argv arguments vector
	 * @param app_exit_code_ptr pointer where this function stores the application exit code or 0 in case of error in the Core Engine. May be null.
	 * @return the Core Engine error code in case of error, or 0 if the execution ends without error.
	 */
	int microej_main(int argc, char **argv, int* app_exit_code_ptr) {
		void* vm;
		int core_engine_error_code = -1;
		int32_t app_exit_code = 0;
		// create Core Engine
		vm = SNI_createVM();

		if (vm == NULL) {
			printf("MicroEJ initialization error.\n");
		} else {
			printf("MicroEJ START\n");

			// Error codes documentation is available in LLMJVM.h
			core_engine_error_code = (int)SNI_startVM(vm, argc, argv);

			if (core_engine_error_code < 0) {
				// Error occurred
				if (core_engine_error_code == LLMJVM_E_EVAL_LIMIT) {
					printf("Evaluation limits reached.\n");
				} else {
					printf("MicroEJ execution error (err = %d).\n", (int) core_engine_error_code);
				}
			} else {
				// Core Engine execution ends normally
				app_exit_code = SNI_getExitCode(vm);
				printf("MicroEJ END (exit code = %d)\n", (int) app_exit_code);
			}

			// delete Core Engine
			SNI_destroyVM(vm);
		}

		if(app_exit_code_ptr != NULL){
			*app_exit_code_ptr = (int)app_exit_code;
		}

		return core_engine_error_code;
	}

	#ifdef __cplusplus
	   }
	#endif
   
.. _core_engine_restart:

Restart the Core Engine
-----------------------  

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

Dump the State of the Core Engine
---------------------------------

The internal Core Engine function called ``LLMJVM_dump`` allows
you to dump the state of all MicroEJ threads: name, priority, stack
trace, etc. This function must only be called from the Core Engine thread context and only from a native function or callback.
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

See Stack Trace Reader documentation for :ref:`SDK 6 <sdk6.section.stacktrace.reader.tool>` or :ref:`SDK 5 <stack_trace_reader>` for additional info related to working with Core Engine dumps.

.. _vm_dump_fault_handler:

Dump The State Of All MicroEJ Threads From A Fault Handler
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is recommended to call the ``LLMJVM_dump`` API as a last resort in a fault handler.
Calling ``LLMJVM_dump`` is undefined if the Core Engine is not paused.
The call to ``LLMJVM_dump`` MUST be done last in the fault handler.

.. _vm_dump_debugger:

Trigger Core Engine Dump From Debugger
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To trigger a Core Engine dump manually from the debugger, you need to set the PC (Program Counter) register 
to the physical memory address of the ``LLMJVM_dump`` function.

Follow these steps:

1. **Ensure LLMJVM_dump is not optimized out**

   Explicitly reference the ``LLMJVM_dump`` function in your BSP code. It is declared in the ``LLMJVM.h`` header file.

   .. note::

      If the function is not used anywhere, linker optimization may remove it, making it unavailable in the final binary.

2. **Locate the symbol in the map file**

   Search for the symbol ``__icetea__virtual__com_is2t_microjvm_IGreenThreadMicroJvm___dump`` in your C toolchain’s ``.map`` file. 
   This will give you the runtime memory address of the function.

3. **Trigger the dump via the debugger**

   In your debugger, set the **PC register** to the retrieved address. Then, resume execution to trigger the dump.


.. note::

   ``LLMJVM_dump`` is an alias defined in ``intern/LLMJVM.h`` header file. 
   If you cannot find the symbol listed above, 
   check the macro definition in that header file to determine the actual function name being referenced and exported.

Requirements:

* Embedded debugger is attached and the processor is halted in an exception handler.
* A way to read stdout (usually UART).

.. _core_engine.check_integrity:

Check Internal Structure Integrity
----------------------------------

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
- internal structures modified by a ``LLMJVM`` function call (e.g., set a pending Java exception, suspend or resume the thread, register a resource, ...).

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


Generic Output
==============

The `System.err`_ stream is connected to the `System.out`_ print
stream. See below for how to configure the destination of these streams.

.. _System.err: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#err
.. _System.out: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#out

.. _core_engine_link:

Link
====

Several sections are defined by the Core Engine. Each section must be linked by the third-party linker.
Read-Only (RO) sections can be placed in writable memories. 
In such cases, it is the responsibility of the BSP to prevent these sections from being written.

Starting from :ref:`Architecture 8.0.0 <changelog-8.0.0>`, sections have been renamed to follow the standard ELF naming convention.

.. tabs::

    .. tab:: Linker Sections (Architecture ``8.x``)

        .. table:: 
            :widths: 15 30 5 5
        
            +--------------------------------+-----------------------------------+-------------+------------+
            | Section name                   | Aim                               | Location    | Alignment  |
            |                                |                                   |             | (in bytes) |
            +================================+===================================+=============+============+
            | ``.bss.microej.heap``          | Application heap                  | RW          | 4          |
            +--------------------------------+-----------------------------------+-------------+------------+
            | ``.bss.microej.immortals``     | Application Immortals Heap         | RW          | 4          |
            |                                |                                   |             |            |
            +--------------------------------+-----------------------------------+-------------+------------+
            | ``.bss.microej.stacks``        | Application threads stack         | RW [1]_     | 8          |
            |                                | blocks                            |             |            |
            +--------------------------------+-----------------------------------+-------------+------------+
            | ``.bss.microej.statics``       | Application static fields         | RW          | 8          |
            +--------------------------------+-----------------------------------+-------------+------------+
            | ``.rodata.microej.resource.*`` | Application resources             | RO          | 16         |
            |                                | (one section per resource)        |             |            |
            +--------------------------------+-----------------------------------+-------------+------------+
            | ``.rodata.microej.soar``       | Application and library           | RO          | 16         |
            |                                | code                              |             |            |
            +--------------------------------+-----------------------------------+-------------+------------+
            | ``.bss.microej.runtime``       | Core Engine                       | RW [1]_     | 8          |
            |                                | internal structures               |             |            |
            +--------------------------------+-----------------------------------+-------------+------------+
            | ``.text.__icetea__*``          | Core Engine                       | RX          | ISA        |
            |                                | generated code                    |             | Specific   |
            +--------------------------------+-----------------------------------+-------------+------------+
            | ``.bss.microej.kernel``        | Core Engine Multi-Sandbox section |             |            |
            |                                | (Feature code chunk)              | RW          | 4          |
            +--------------------------------+-----------------------------------+-------------+------------+
   
        .. note::
            
            During its startup, the Core Engine automatically zero-initializes the sections ``.bss.microej.runtime``, ``.bss.microej.heap``, and ``.bss.microej.immortals``. 

    .. tab:: Linker Sections (Architecture ``7.x``)

        .. table:: 
            :widths: 15 30 5 5
                
            +-----------------------------+-----------------------------+-------------+------------+
            | Section name                | Aim                         | Location    | Alignment  |
            |                             |                             |             | (in bytes) |
            +=============================+=============================+=============+============+
            | ``_java_heap``              | Application heap            | RW          | 4          |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``_java_immortals``         | Application Immortals Heap   | RW          | 4          |
            |                             |                             |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.bss.vm.stacks.java``     | Application threads stack   | RW [1]_     | 8          |
            |                             | blocks                      |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.bss.soar``               | Application static fields   | RW          | 8          |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.rodata.resources``       | Application resources       | RO          | 16         |
            |                             |                             |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.text.soar``              | Application and library     | RO          | 16         |
            |                             | code                        |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``ICETEA_HEAP``             | Core Engine                 | RW [1]_     | 8          |
            |                             | internal structures         |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.text.__icetea__*``       | Core Engine                 | RX          | ISA        |
            |                             | generated code              |             | Specific   |
            +-----------------------------+-----------------------------+-------------+------------+

        .. note::
            
            During its startup, the Core Engine automatically zero-initializes the sections ``ICETEA_HEAP``, ``_java_heap``, and ``_java_immortals``. 

.. [1]
   Among all RW sections, those should be always placed into internal RAM for performance purpose.

Dependencies
============

The Core Engine requires an implementation of its low level APIs
in order to run. Refer to the chapter :ref:`core_engine_implementation` for more
information.


Installation
============

The Core Engine and its components are mandatory.  
By default, it is configured with Mono-Sandbox capability.
See the :ref:`core_engine_capabilities` section to update the Core Engine with Multi-Sandbox or Tiny-Sandbox capability.

Abstraction Layer
=================

Core Engine Abstraction Layer implementations can be found on `MicroEJ Github`_ for several RTOS.

.. _MicroEJ Github: https://github.com/orgs/MicroEJ/repositories?q=AbstractionLayer-Core&type=all&language=&sort=

.. _memory-considerations:

Memory Considerations
=====================

The memory consumption of main Core Engine runtime elements are described in :ref:`the table below <table-memory>`. 

.. _table-memory:
.. table:: Memory Considerations

   +-----------+-----------+-----------------+-----------------+-----------------+
   | Runtime   | Memory    | Size in bytes   | Size in bytes   | Size in bytes   |
   | element   |           | (Mono-sandbox)  | (Multi-Sandbox) | (Tiny-Sandbox)  |
   +===========+===========+=================+=================+=================+
   | Object    | RW        | 4               | 8 (+4)          | 4               |
   | Header    |           |                 |                 |                 |
   +-----------+-----------+-----------------+-----------------+-----------------+
   | Thread    | RW        | 168             | 192 (+24)       | 168             |
   +-----------+-----------+-----------------+-----------------+-----------------+
   | Call      | RW        | 12              | 20 (+8)         | 12              |
   | Frame     |           |                 |                 |                 |
   | Header    |           |                 |                 |                 |
   +-----------+-----------+-----------------+-----------------+-----------------+
   | Class     | RO        | 32              | 36 (+4)         | 32              |
   | Type      |           |                 |                 |                 |
   +-----------+-----------+-----------------+-----------------+-----------------+
   | Interface | RO        | 16              | 24 (+8)         | 16              |
   | Type      |           |                 |                 |                 |
   +-----------+-----------+-----------------+-----------------+-----------------+

.. note::
	To get the full size of an Object, search for the type in the :ref:`SOAR Information File <soar_info_file>` and read the attribute ``instancesize`` (this includes the Object header). 

.. note::
	To get the full size of a call frame, search for the method in the :ref:`SOAR Information File <soar_info_file>` and read the attribute ``stacksize`` (this includes the call frame header). 

Use
===

Refer to the :ref:`MicroEJ Runtime <runtime_core_libraries>` documentation.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
