.. _training_debug_hardfault:

=================
Debug a HardFault
=================

Description
===========

In this training, you will get insights on how to debug a hardfault.

Intended Audience
=================

This training is designed for VEE Port developers who want to debug a hardfault.

Prerequisites
=============

To get the most out of this training, participants should have:

- A good knowledge of embedded software development on Microcontrollers.
- A good understanding of :ref:`sni_specification` concepts.

Introduction
============

When the application crashes, it can result from a HardFault triggered by the MCU.

The following sections explain:

1. What are exceptions, HardFaults, and the exception handler.
2. What to do in case of Memory Corruptions.
3. What to do when a HardFault occurs.

Useful Resources
----------------

* IAR System: Debugging a HardFault on Cortex-M https://mypages.iar.com/s/article/Debugging-a-HardFault-on-Cortex-M
* ESP-IDF Programming Guide: Fatal Errors https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/fatal-errors.html
* Using Cortex-M3/M4/M7 Fault Exceptions MDK Tutorial http://www.keil.com/appnotes/files/apnt209.pdf

Exceptions, HardFaults And Exception Handler
--------------------------------------------

*From ARM Architecture Reference Manual*

   An exception causes the processor to suspend program execution to handle an event, such as an externally generated interrupt or an attempt to execute an undefined instruction. Exceptions can be generated by internal and external sources.
   Normally, when an exception is taken, the processor state is preserved immediately, before handling the exception.
   This means that, when the event has been handled, the original state can be restored and program execution resumed from the point where the exception was taken.

For example, an *IRQ request* is an exception that can be recovered by handling the hardware request properly.
On the other hand, an *Undefined Instruction* exception suggests a more severe system failure that might not be recoverable.

The exceptions that cannot be recovered are named **HardFaults**.

*From ARM Architecture Reference Manual*

   When an exception is taken, processor execution is forced to an address that corresponds to the type of exception.
   This address is called the **exception vector** for that exception.

The code pointed by the exception vector is named **exception handler**.
Therefore, a dedicated exception handler can be configured for all exceptions, including HardFaults.

Possible exceptions can be:

* Data Abort exception (access to unknown address)
* Undefined Instruction exception (execute code that is not valid)
* ...

Check the hardware documentation for the complete list of exceptions.

What To Do In Exception Handlers?
---------------------------------

For all HardFault handlers, the following data are available and must be printed:

* Name and value of all registers available
* Name of the handler
* Address of the failing instruction

Optionally:

* Content of the stack
* Call function ``LLMJVM_dump`` (from ``LLMJVM.h``) to display the Core Engine state (see :ref:`vm_dump`)

Refer to the architecture documentation for how to configure the exception interrupt vector.

Memory Protection Unit (MPU)
----------------------------

A Memory Protection Unit (MPU) is a hardware unit that provides memory protection.
An MPU allows privileged software to define memory regions and their policy.
The policy describes who can access the memory.

For example, configure the heap and stack of a task to be accessible from the task itself only.
The MPU generates an exception if another task or a device driver attempts to access the memory region.

If applicable, configure the MPU should to protect the application.

* Check the RTOS documentation if it supports MPU. 

  For example, FreeRTOS includes FreeRTOS-MPU https://www.freertos.org/Security/04-FreeRTOS-MPU-memory-protection-unit.

* Configure the MPU to configure the access to the JVM heap and stack to prevent any other native threads from altering this area.
  Refer to :ref:`this section<core_engine_link>` for the list of section names defined by the Core Engine.

Memory Corruption
-----------------

Memory corruption can result in the following symptoms:

* The address of the failing instruction is in a data section.
* The trace is incomplete or incorrect.
* The address of the failing instruction is located in the Garbage Collector (GC).

The cause(s) of a memory corruption can be:

* A native (C) function has a bug and writes to an incorrect memory location
* A native stack overflow
* A native heap overflow
* A device incorrectly initialized or misconfigured.
* ...

When the HardFault occurs in the Core Engine task, one of its internal structures may be corrupted (such as the Managed heap or Threads stacks).
Add ``LLMJVM_checkIntegrity`` call in checkpoints of the BSP code to identify the timeslot of the memory corruption.
Typically, you can check a native with:

.. code-block:: java

   void Java_com_mycompany_MyClass_myNativeFunction(void) {
   	int32_t crcBefore = LLMJVM_checkIntegrity();
   	myNativeFunctionDo();
   	int32_t crcAfter = LLMJVM_checkIntegrity();
   	if(crcBefore != crcAfter){
   		// Corrupted memory in Core Engine internal structures
   		while(1);
   	}
   }

Investigation
-------------

Determine which memory regions are affected and determine which components are responsible for the corruption.

* List all the memories available and their specifics:

    * Access mode (addressable, DMA, ...)
    * Cache mechanism? L1, L2

* Is low-power enabled for CPU and peripherals? Is the memory disabled/changed to save power?
* Get the memory layout of the project:

    * What are the code sections for the BSP and the Application?
    * Where are the BSP stack and heap? What about the Application stack and heap?
    * Where is the Java immortals heap?
    * Where are the Java strings?
    * Where is the MicroEJ UI buffer?
    * Besides the Java immortals, what are the other intersection point between the Java application and the BSP? (e.g., a temporary RAM buffer for JPEG decoder).
    * Please refer to the :ref:`Core Engine Link section <core_engine_link>` to locate the Application sections, and to the :ref:`application_options` for their sizes.

* Implement a CRC of the *hot sections* when entering/leaving all natives. *Hot Sections* are memory sections used by both Java code and native code (e.g., C or ASM).

* Move the C stack at the beginning of the memory to trigger a crash when it overflows (instead of corrupting the memory).

When a HardFault Occurs
-----------------------

Extract Information and Coredump
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Attach an embedded debugger and get the following information:

* stack traces and registers information for each stack frame
* memory information

    * the whole memory, if possible
    * otherwise, get the *hot sections* 

        * BSP and Managed heap and stack
        * UI buffer
        * immortals heap
        * sections where the Java application and BSP are working together

* :ref:`vm_dump_debugger`

* Check which function is located at the address inside the PC register.

  * It can be done either in Debug mode or by searching inside the generated .map file.


Memory Dump Analysis
--------------------

* Run the Heap Dumper to check the application heap has not been corrupted.
* Make sure the native stack is not full (usually, there shall have the remaining initialization patterns in memory on top of the stack, such as ``0xDEADBEEF``)

Trigger a Core Engine Dump
--------------------------

``LLMJVM_dump`` function is provided by ``LLMJVM.h``.
This function prints a snapshot of the Core Engine's current state.
The output includes the list of threads and their stack traces.

See :ref:`this section<vm_dump>` to learn more about ``LLMJVM_dump``.

..
   | Copyright 2021-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.