.. _mjvm_impl:

Implementation
==============

The platform implements the [SNI] specification. It is created and
initialized with the C function ``SNI_createVM``. Then it is started and
executed in the current RTOS task by calling ``SNI_startVM``. The
function ``SNI_startVM`` returns when the MicroEJ application exits. The
function ``SNI_destroyVM`` handles the platform termination.

The file ``LLMJVM_impl.h`` that comes with the platform defines the API
to be implemented. The file ``LLMJVM.h`` that comes with the platform
defines platform-specific exit code constants. (See
`??? <#LLMJVM-API-SECTION>`__.)

Initialization
--------------

The Low Level MJVM API deals with two objects: the structure that
represents the platform, and the RTOS task that runs the platform. Two
callbacks allow engineers to interact with the initialization of both
objects:

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

Example
-------

The following example shows how to create and launch the MJVM from the C
world. This function (``mjvm_main``) should be called from a dedicated
RTOS task.

.. code:: c

   #include <stdio.h>
   #include "mjvm_main.h"
   #include "LLMJVM.h"
   #include "sni.h"

   void mjvm_main(void)
   {
       void* vm;
       int32_t err;
       int32_t exitcode;
       
       // create VM
       vm = SNI_createVM();

       if(vm == NULL)
       {
           printf("VM initialization error.\n");
       }
       else
       {
           printf("VM START\n");
           err = SNI_startVM(vm, 0, NULL);

           if(err < 0)
           {
               // Error occurred
               if(err == LLMJVM_E_EVAL_LIMIT)
               {
                   printf("Evaluation limits reached.\n");
               }
               else
               {
                   printf("VM execution error (err = %d).\n", err);
               }
           }
           else
           {
               // VM execution ends normally
               exitcode = SNI_getExitCode(vm);
               printf("VM END (exit code = %d)\n", exitcode);
           }

           // delete VM
           SNI_destroyVM(vm);
       }
   }

Debugging
---------

The internal MJVM function called ``LLMJVM_dump`` allows you to dump the
state of all MicroEJ threads: name, priority, stack trace, etc. This
function can be called at any time and from an interrupt routine (for
instance from a button interrupt).

This is an example of a dump:

.. code:: txt

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

See `??? <#stack_trace_reader>`__ for additional info related to working
with VM dumps.
