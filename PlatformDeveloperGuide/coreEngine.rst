.. _core_engine:

===================
MicroEJ Core Engine
===================


The MicroEJ Core Engine (also called the platform engine) and its
components represent the core of the platform. It is used to compile and
execute at runtime the MicroEJ Application code.


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

2. Step 2 consists in compiling the MicroEJ Application code and the
   required libraries in an ELF library, using the SOAR.

3. Step 3 consists in linking the previous ELF file with the MicroEJ
   Core Engine library and a third-party BSP (OS, drivers, etc.). This
   step may require a third-party linker provided by a C toolchain.


Architecture
============

The MicroEJ Core Engine and its components have been compiled for one
specific CPU architecture and for use with a specific C compiler.

The architecture of the platform engine is called green thread
architecture, it runs in a single RTOS task. Its behavior consists in
scheduling MicroEJ threads. The scheduler implements a priority
preemptive scheduling policy with round robin for the MicroEJ threads
with the same priority. In the following explanations the term "RTOS
task" refers to the tasks scheduled by the underlying OS; and the term
"MicroEJ thread" refers to the Java threads scheduled by the MicroEJ Core Engine.

.. figure:: images/mjvm_gt.*
   :alt: A Green Threads Architecture Example
   :align: center
   :scale: 75%

   A Green Threads Architecture Example

The activity of the platform is defined by the MicroEJ Application. When
the MicroEJ Application is blocked (when all MicroEJ threads are
sleeping), the platform sleeps entirely: The RTOS task that runs the
platform sleeps.

The platform is responsible for providing the time to the MicroEJ world:
the precision is 1 millisecond.


Capabilities
============

MicroEJ Core Engine defines 3 exclusive capabilities:

-  Mono-sandbox: capability to produce a monolithic firmware
   (default one).

-  Multi-Sandbox: capability to produce a extensible firmware on
   which new applications can be dynamically installed. See section
   :ref:`multisandbox`.

-  Tiny application: capability to produce a compacted firmware
   (optimized for size). See section :ref:`core-tiny`.

All MicroEJ Core Engine capabilities may not be available on all
architectures. Refer to section :ref:`appendix_matrixcapabilities`
for more details.


.. _core_engine_implementation:

Implementation
==============

The MicroEJ Core Engine implements the :ref:`[SNI] specification <esr-specifications>`. 
It is created and initialized with the C function ``SNI_createVM``.
Then it is started and executed in the current RTOS task by calling ``SNI_startVM``.
The function ``SNI_startVM`` returns when the MicroEJ Application exits or if
an error occurs (see section :ref:`core_engine_error_codes`).
The function ``SNI_destroyVM`` handles the platform termination.

The file ``LLMJVM_impl.h`` that comes with the platform defines the API
to be implemented. See section :ref:`LLMJVM-API-SECTION`.

Initialization
--------------

The Low Level MicroEJ Core Engine API deals with two objects: the
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

-  the application time: The difference, measured in milliseconds,
   between the current time and midnight, January 1, 1970, UTC.

-  the system time: The time since the start of the device. This time is
   independent of any user considerations, and cannot be set.

The platform relies on the following C functions to provide those times
to the MicroEJ world:

-  ``LLMJVM_IMPL_getCurrentTime``: Depending on the parameter (``true``
   / ``false``) must return the application time or the system time.
   This function is called by the MicroEJ method
   ``System.currentTimeMillis()``. It is also used by the platform
   scheduler, and should be implemented efficiently.

-  ``LLMJVM_IMPL_getTimeNanos``: must return the system time in
   nanoseconds.

-  ``LLMJVM_IMPL_setApplicationTime``: must set the difference between
   the current time and midnight, January 1, 1970, UTC.


.. _core_engine_error_codes:

Error Codes
-----------

The C function ``SNI_createVM`` returns a negative value if an error 
occurred during the MicroEJ Core Engine initialization or execution.
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

The following example shows how to create and launch the MicroEJ Core
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

Debugging
---------

The internal MicroEJ Core Engine function called ``LLMJVM_dump`` allows
you to dump the state of all MicroEJ threads: name, priority, stack
trace, etc. This function can be called at any time and from an
interrupt routine (for instance from a button interrupt).

This is an example of a dump:

.. code-block::

   ============ VM Dump ============
   2 java threads
   ---------------------------------
   Java Thread[3]
   name="SYSINpmp" prio=5 state=WAITING

   java/lang/Thread:
       at com/is2t/microbsp/microui/natives/NSystemInputPump.@134261800
    [0x0800AC32]
       at com/is2t/microbsp/microui/io/SystemInputPump.@134265968
    [0x0800BC80]
       at ej/microui/Pump.@134261696
    [0x0800ABCC]
       at ej/microui/Pump.@134265872
    [0x0800BC24]
       at java/lang/Thread.@134273964
    [0x0800DBC4]
       at java/lang/Thread.@134273784
    [0x0800DB04]
       at java/lang/Thread.@134273892
    [0x0800DB6F]
   ---------------------------------
   Java Thread[2]
   name="DISPLpmp" prio=5 state=WAITING

   java/lang/Thread:
       at java/lang/Object.@134256392
    [0x08009719]
       at ej/microui/FIFOPump.@134259824
    [0x0800A48E]
       at ej/microui/io/DisplayPump.134263016
    [0x0800B0F8]
       at ej/microui/Pump.@134261696
    [0x0800ABCC]
       at ej/microui/Pump.@134265872
    [0x0800BC24]
       at ej/microui/io/DisplayPump.@134262868
    [0x0800B064]
       at java/lang/Thread.@134273964
    [0x0800DBC4]
       at java/lang/Thread.@134273784
    [0x0800DB04]
       at java/lang/Thread.@134273892
    [0x0800DB6F]
   =================================

See :ref:`stack_trace_reader` for additional info related to working
with VM dumps.


Generic Output
==============

The ``System.err`` stream is connected to the ``System.out`` print
stream. See below for how to configure the destination of these streams.


.. _core_engine_link:

Link
====

Several sections are defined by the MicroEJ Core Engine. Each section
must be linked by the third-party linker.

.. table:: Linker Sections

   +-----------------------------+-----------------------------+-------------+------------+
   | Section name                | Aim                         | Location    | Alignment  |
   |                             |                             |             | (in bytes) |
   +=============================+=============================+=============+============+
   | ``.bss.features.installed`` | Resident applications       | RW          | 4          |
   |                             | statics                     |             |            |
   +-----------------------------+-----------------------------+-------------+------------+
   | ``.bss.soar``               | Application static          | RW          | 8          |
   +-----------------------------+-----------------------------+-------------+------------+
   | ``.bss.vm.stacks.java``     | Application threads stack   | RW          | 8          |
   |                             | blocks                      |             |            |
   +-----------------------------+-----------------------------+-------------+------------+
   | ``ICETEA_HEAP``             | MicroEJ Core Engine         | Internal RW | 8          |
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
   | ``.rodata.soar.features``   | Resident applications code  | RO          | 4          |
   |                             | and resources               |             |            |
   +-----------------------------+-----------------------------+-------------+------------+
   | ``.shieldedplug``           | Shielded Plug data          | RO          | 4          |
   +-----------------------------+-----------------------------+-------------+------------+
   | ``.text.soar``              | Application and library     | RO          | 16         |
   |                             | code                        |             |            |
   +-----------------------------+-----------------------------+-------------+------------+

.. note::
	Sections ``ICETEA_HEAP``, ``_java_heap`` and ``_java_immortals`` are zero-initialized at MicroEJ Core Engine startup. 

Dependencies
============

The MicroEJ Core Engine requires an implementation of its low level APIs
in order to run. Refer to the chapter :ref:`core_engine_implementation` for more
information.


Installation
============

The MicroEJ Core Engine and its components are mandatory. In the
platform configuration file, check :guilabel:`Multi Applications` to install the
MicroEJ Core Engine in "Multi-Sandbox" mode. Otherwise, the "Single
application" mode is installed.


Use
===

The `EDC API Module <https://repository.microej.com/modules/ej/api/edc/>`_ must 
be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ Application 
Project. This MicroEJ module is always required in the build path of a MicroEJ project; 
and all others libraries depend on it. This library provides a set of options.
Refer to the chapter :ref:`application_options` which lists all available options.

::

   <dependency org="ej.api" name="edc" rev="1.3.3"/>

The `BON API Module <https://repository.microej.com/modules/ej/api/bon/>`_
must also be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project in order to access the :ref:`[BON] library <esr-specifications>`.

::

   <dependency org="ej.api" name="bon" rev="1.4.0"/>

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
