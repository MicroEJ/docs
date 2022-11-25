.. _core_engine:

===================
MicroEJ Core Engine
===================


The MicroEJ Core Engine and its components represent the core of the Architecture.
It is used to compile and execute at runtime the MicroEJ Application code.


Functional Description
======================

:ref:`The following diagram <fig_mjvm_flow2>` shows the overall process. The first two
steps are performed within the MicroEJ Workbench. The remaining steps
are performed within the C IDE.

.. _fig_mjvm_flow2:
.. figure:: images/mjvm_flow2.*
   :alt: MicroEJ Core Engine Flow
   :align: center
   :scale: 80%

   MicroEJ Core Engine Flow

1. Step 1 consists in writing a MicroEJ Application against a set of
   Foundation Libraries available in the platform.

2. Step 2 consists in compiling the Application code and the
   required libraries in an ELF library, using the SOAR.

3. Step 3 consists in linking the previous ELF file with the 
   Core Engine library and a third-party BSP (OS, drivers, etc.). This
   step may require a third-party linker provided by a C toolchain.


Architecture
============

The Core Engine and its components have been compiled for one
specific CPU architecture and for use with a specific C compiler.

The architecture of the platform engine is called green thread
architecture, it runs in a single RTOS task. Its behavior consists in
scheduling MicroEJ threads. The scheduler implements a priority
preemptive scheduling policy with round robin for the MicroEJ threads
with the same priority. In the following explanations the term "RTOS
task" refers to the tasks scheduled by the underlying OS; and the term
"MicroEJ thread" refers to the Java threads scheduled by the Core Engine.

.. figure:: images/mjvm_gt.*
   :alt: A Green Threads Architecture Example
   :align: center
   :scale: 75%

   A Green Threads Architecture Example

The activity of the platform is defined by the Application. When
the Application is blocked (when all MicroEJ threads are
sleeping), the platform sleeps entirely: The RTOS task that runs the
platform sleeps.

The platform is responsible for providing the time to the MicroEJ world:
the precision is 1 millisecond.


Capabilities
============

The Core Engine defines 3 exclusive capabilities:

-  Mono-Sandbox: capability to produce a monolithic firmware
   (default one).

-  Multi-Sandbox: capability to produce a extensible firmware on
   which new applications can be dynamically installed. See section
   :ref:`multisandbox`.

-  Tiny-Sandbox: capability to produce a compacted firmware
   (optimized for size). See section :ref:`tinysandbox`.

All the Core Engine capabilities may not be available on all
architectures. Refer to section :ref:`appendix_matrixcapabilities`
for more details.


.. _core_engine_implementation:

Implementation
==============

The Core Engine implements the :ref:`[SNI] specification <runtime_sni>`. 
It is created and initialized with the C function ``SNI_createVM``.
Then it is started and executed in the current RTOS task by calling ``SNI_startVM``.
The function ``SNI_startVM`` returns when the Application exits or if
an error occurs (see section :ref:`core_engine_error_codes`).
The function ``SNI_destroyVM`` handles the platform termination.

The file ``LLMJVM_impl.h`` that comes with the platform defines the API
to be implemented. See section :ref:`LLMJVM-API-SECTION`.

Initialization
--------------

The Low Level Core Engine API deals with two objects: the
structure that represents the platform, and the RTOS task that runs the
platform. Two callbacks allow engineers to interact with the
initialization of both objects:

-  ``LLMJVM_IMPL_initialize``: Called once the structure representing
   the platform is initialized.

-  ``LLMJVM_IMPL_vmTaskStarted``: Called when the platform starts its
   execution. This function is called within the RTOS task of the
   platform.

Scheduling
----------

To support the green thread round-robin policy, the platform assumes
there is an RTOS timer or some other mechanism that counts (down) and
fires a call-back when it reaches a specified value. The platform
initializes the timer using the ``LLMJVM_IMPL_scheduleRequest`` function
with one argument: the absolute time at which the timer should fire.
When the timer fires, it must call the ``LLMJVM_schedule`` function,
which tells the platform to execute a green thread context switch (which
gives another MicroEJ thread a chance to run).

When several MicroEJ threads with the same priority are eligible for execution,
the round-robin algorithm will automatically switch between these threads after a certain amount of time, 
called the `time slice`. 
The time slice is expressed in milliseconds, and its default value is ``20`` ms. 
It can be configured at link time with the symbol
``_java_round_robin_period``, defined in the :ref:`linker configuration file <linker_lscf>` 
``linkVMConfiguration.lscf`` located in the Platform folder ``/MICROJVM/link/``.
To override the content of this file, create, in the Platform configuration project,
a folder named ``/dropins/MICROJVM/link/``, and copy into this folder the file
``linkVMConfiguration.lscf`` retrieved from an existing Platform.
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

When the platform has no activity to execute, it calls the
``LLMJVM_IMPL_idleVM`` function, which is assumed to put the RTOS task
of the platform into a sleep state. ``LLMJVM_IMPL_wakeupVM`` is called
to wake up the platform task. When the platform task really starts to
execute again, it calls the ``LLMJVM_IMPL_ackWakeup`` function to
acknowledge the restart of its activity.

Time
----

The platform defines two times:

-  the application time: the difference, measured in milliseconds,
   between the current time and midnight, January 1, 1970, UTC.

-  the monotonic time: this time always moves forward and is not impacted 
   by application time modifications (NTP or Daylight Savings Time updates).
   It can be implemented by returning the running time since the start of 
   the device.

The platform relies on the following C functions to provide those times
to the MicroEJ world:

-  ``LLMJVM_IMPL_getCurrentTime``: must return the monotonic time in 
   milliseconds if the given parameter is ``1``, otherwise must return the 
   application time in milliseconds. 
   This function is called by the method `java.lang.System.currentTimeMillis()`_
   It is also used by the platform
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
The file ``LLMJVM.h`` defines the platform-specific error code constants.
The following table describes these error codes.

.. table:: MicroEJ Core Engine Error Codes

   +-------------+-------------------------------------------------------------+
   | Error Code  | Meaning                                                     |
   +=============+=============================================================+
   | 0           | The MicroEJ Application ended normally (i.e., all the       |
   |             | non-daemon threads are terminated or                        |
   |             | ``System.exit(exitCode)`` has been called).                 |
   |             | See section :ref:`edc_exit_codes`.                          |
   +-------------+-------------------------------------------------------------+
   | -1          | The ``microejapp.o`` produced by SOAR is not compatible     |
   |             | with the MicroEJ Core Engine (``microejruntime.a``).        |
   |             | The object file has been built from another                 |
   |             | MicroEJ Platform.                                           |
   +-------------+-------------------------------------------------------------+
   | -2          | Internal error. Invalid link configuration in the           |
   |             | MicroEJ Architecture or the MicroEJ Platform.               |
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
   | -13         | Fail to start the MicroEJ Application because the           |
   |             | specified MicroEJ heap is too large or too small.           |
   |             | See section :ref:`option_java_heap`.                        |
   +-------------+-------------------------------------------------------------+
   | -14         | Invalid MicroEJ Application stack configuration. The        |
   |             | stack start or end is not eight-byte aligned, or stack      |
   |             | block size is too small. See section                        |
   |             | :ref:`option_number_of_stack_blocks`.                       |
   +-------------+-------------------------------------------------------------+
   | -16         | The MicroEJ Core Engine cannot be restarted.                |
   +-------------+-------------------------------------------------------------+
   | -17         | The MicroEJ Core Engine is not in a valid state because     |
   |             | of one of the following situations:                         |
   |             |                                                             |
   |             | - ``SNI_startVM`` called before ``SNI_createVM``.           |
   |             |                                                             |
   |             | - ``SNI_startVM`` called while the MicroEJ                  |
   |             |   Appplication is running.                                  |
   |             |                                                             |
   |             | - ``SNI_createVM`` called several times.                    |
   +-------------+-------------------------------------------------------------+
   | -18         | The memory used for the MicroEJ heap or immortal heap       |
   |             | does not work properly. Read/Write memory checks            |
   |             | failed. This may be caused by an invalid external RAM       |
   |             | configuration. Verify ``_java_heap`` and                    |
   |             | ``_java_immortals`` sections locations.                     |
   +-------------+-------------------------------------------------------------+
   | -19         | The memory used for the MicroEJ Application static          |
   |             | fields does not work properly. Read/Write memory checks     |
   |             | failed. This may be caused by an invalid external RAM       |
   |             | configuration. Verify ``.bss.soar`` section location.       |
   +-------------+-------------------------------------------------------------+
   | -20         | KF configuration internal error. Invalid link               |
   |             | configuration in the MicroEJ Architecture or the            |
   |             | MicroEJ Platform.                                           |
   +-------------+-------------------------------------------------------------+
   | -21         | Number of monitors per thread limitation reached.           |
   |             | See sections :ref:`limitations` and                         |
   |             | :ref:`Options<option_maximum_number_of_monitors_per_thread>`|
   |             | .                                                           |
   +-------------+-------------------------------------------------------------+
   | -22         | Internal error. Invalid FPU configuration in the            |
   |             | MicroEJ Architecture.                                       |
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
from a dedicated RTOS task.

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
    */
   void microej_main(int argc, char **argv)
   {
       void* vm;
       int32_t err;
       int32_t exitcode;
       
       // create VM
       vm = SNI_createVM();

       if(vm == NULL)
       {
           printf("MicroEJ initialization error.\n");
       }
       else
       {
           printf("MicroEJ START\n");
		   
		   // Error codes documentation is available in LLMJVM.h
           err = SNI_startVM(vm, argc, argv);

           if(err < 0)
           {
               // Error occurred
               if(err == LLMJVM_E_EVAL_LIMIT)
               {
                   printf("Evaluation limits reached.\n");
               }
               else
               {
                   printf("MicroEJ execution error (err = %d).\n", err);
               }
           }
           else
           {
               // VM execution ends normally
               exitcode = SNI_getExitCode(vm);
               printf("MicroEJ END (exit code = %d)\n", exitcode);
           }

           // delete VM
           SNI_destroyVM(vm);
       }
   }
   
   #ifdef __cplusplus
       }
   #endif

.. _vm_dump:

Dump the States of the Core Engine
----------------------------------

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

See :ref:`stack_trace_reader` for additional info related to working with VM dumps.

.. _vm_dump_fault_handler:

Dump The State Of All MicroEJ Threads From A Fault Handler
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is recommended to call the ``LLMJVM_dump`` API as a last resort in a fault handler.
Calling ``LLMJVM_dump`` is undefined if the VM is not paused.
The call to ``LLMJVM_dump`` MUST be done last in the fault handler.

.. _vm_dump_debugger:

Trigger VM Dump From Debugger
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


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
----------------------------------

The internal Core Engine function called ``LLMJVM_checkIntegrity`` checks the internal structure integrity of the MicroJvm virtual machine and returns its checksum.

- If an integrity error is detected, the ``LLMJVM_on_CheckIntegrity_error`` hook is called and this method returns ``0``.
- If no integrity error is detected, a non-zero checksum is returned.

This function must only be called from the MicroJvm virtual machine thread context and only from a native function or callback.
Calling this function multiple times in a native function must always produce the same checksum.
If the checksums returned are different, a corruption must have occurred.

Please note that returning a non-zero checksum does not mean the MicroJvm virtual machine data has not been corrupted,
as it is not possible for the MicroJvm virtual machine to detect the complete memory integrity.

MicroJvm virtual machine internal structures allowed to be modified by a native function are not taken into account for the checksum computation.
The internal structures allowed are:

- basetype fields in Java objects or content of Java arrays of base type,
- internal structures modified by a ``LLMJVM`` function call (e.g. set a pending Java exception, suspend or resume the Java thread, register a resource, ...).

This function affects performance and should only be used for debug purpose.
A typical use of this API is to verify that a native implementation does not corrupt the internal structures:

.. code-block:: java

   void Java_com_mycompany_MyClass_myNativeFunction(void) {
   		int32_t crcBefore = LLMJVM_checkIntegrity();
   		myNativeFunctionDo();
        int32_t crcAfter = LLMJVM_checkIntegrity();
        if(crcBefore != crcAfter){
        	// Corrupted MicroJVM virtual machine internal structures
        	while(1);
        }
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

Several sections are defined by the Core Engine. Each section
must be linked by the third-party linker.
Starting from Architecture ``8.x``, sections have been renamed to follow the standard ELF naming convention.

.. tabs::

    .. tab:: Linker Sections (Architecture ``8.x``)

        .. table:: 
        
            +--------------------------------+-----------------------------+-------------+------------+
            | Section name                   | Aim                         | Location    | Alignment  |
            |                                |                             |             | (in bytes) |
            +================================+=============================+=============+============+
            | ``.bss.microej.features``      | System Applications         | RW          | 4          |
            |                                | static fields               |             |            |
            +--------------------------------+-----------------------------+-------------+------------+
            | ``.bss.microej.heap``          | Application heap            | RW          | 4          |
            +--------------------------------+-----------------------------+-------------+------------+
            | ``.bss.microej.immortals``     | Application immortal heap   | RW          | 4          |
            |                                |                             |             |            |
            +--------------------------------+-----------------------------+-------------+------------+
            | ``.bss.microej.runtime``       | Core Engine                 | Internal RW | 8          |
            |                                | internal heap               |             |            |
            +--------------------------------+-----------------------------+-------------+------------+
            | ``.bss.microej.stacks``        | Application threads stack   | RW          | 8          |
            |                                | blocks                      |             |            |
            +--------------------------------+-----------------------------+-------------+------------+
            | ``.bss.microej.statics``       | Application static fields   | RW          | 8          |
            +--------------------------------+-----------------------------+-------------+------------+
            | ``.rodata.microej.features``   | System Applications code    | RO          | 4          |
            |                                | and resources               |             |            |
            +--------------------------------+-----------------------------+-------------+------------+
            | ``.rodata.microej.resource.*`` | Application resources       | RO          | 16         |
            |                                | (one section per resource)  |             |            |
            +--------------------------------+-----------------------------+-------------+------------+
            | ``.rodata.microej.soar``       | Application and library     | RO          | 16         |
            |                                | code                        |             |            |
            +--------------------------------+-----------------------------+-------------+------------+
            | ``.text.__icetea__*``          | Core Engine                 | RX          | ISA        |
            |                                | generated code              |             | Specific   |
            +--------------------------------+-----------------------------+-------------+------------+

        .. note::
            
            During its startup, the Core Engine automatically zero-initializes the sections ``.bss.microej.runtime``, ``.bss.microej.heap`` and ``.bss.microej.immortals``. 

    .. tab:: Linker Sections (Architecture ``7.x``)

        .. table:: 
                
            +-----------------------------+-----------------------------+-------------+------------+
            | Section name                | Aim                         | Location    | Alignment  |
            |                             |                             |             | (in bytes) |
            +=============================+=============================+=============+============+
            | ``.bss.features.installed`` | System Applications         | RW          | 4          |
            |                             | static fields               |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.bss.soar``               | Application static fields   | RW          | 8          |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.bss.vm.stacks.java``     | Application threads stack   | RW          | 8          |
            |                             | blocks                      |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``ICETEA_HEAP``             | Core Engine                 | Internal RW | 8          |
            |                             | internal heap               |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``_java_heap``              | Application heap            | RW          | 4          |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``_java_immortals``         | Application immortal heap   | RW          | 4          |
            |                             |                             |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.rodata.resources``       | Application resources       | RO          | 16         |
            |                             |                             |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.rodata.soar.features``   | System Applications code    | RO          | 4          |
            |                             | and resources               |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.text.soar``              | Application and library     | RO          | 16         |
            |                             | code                        |             |            |
            +-----------------------------+-----------------------------+-------------+------------+
            | ``.text.__icetea__*``       | Core Engine                 | RX          | ISA        |
            |                             | generated code              |             | Specific   |
            +-----------------------------+-----------------------------+-------------+------------+

        .. note::
            
            During its startup, the Core Engine automatically zero-initializes the sections ``ICETEA_HEAP``, ``_java_heap`` and ``_java_immortals``. 

Dependencies
============

The Core Engine requires an implementation of its low level APIs
in order to run. Refer to the chapter :ref:`core_engine_implementation` for more
information.


Installation
============

The Core Engine and its components are mandatory. In the
platform configuration file, check :guilabel:`Multi Applications` to install the
Core Engine in "Multi-Sandbox" mode. Otherwise, the "Single
application" mode is installed.

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
   | Stack     | RW        | 12              | 20 (+8)         | 12              |
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
	To get the full size of a Stack Frame, search for the method in the :ref:`SOAR Information File <soar_info_file>` and read the attribute ``stacksize`` (this includes the Stack Frame header). 

Use
===

The `EDC API Module`_ must 
be added to the :ref:`module.ivy <mmm_module_description>` of the Application 
Project. This MicroEJ module is always required in the build path of a MicroEJ project; 
and all others libraries depend on it. This library provides a set of options.
Refer to the chapter :ref:`application_options` which lists all available options.

::

   <dependency org="ej.api" name="edc" rev="1.3.3"/>

The `BON API Module`_
must also be added to the :ref:`module.ivy <mmm_module_description>` of the 
Application project in order to access the :ref:`[BON] library <runtime_bon>`.

::

   <dependency org="ej.api" name="bon" rev="1.4.0"/>


.. _EDC API Module: https://repository.microej.com/modules/ej/api/edc/
.. _BON API Module: https://repository.microej.com/modules/ej/api/bon/

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
