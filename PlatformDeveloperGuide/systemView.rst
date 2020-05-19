==========
SystemView
==========

Principle
=========

SystemView is a real-time recording and visualization tool for embedded systems that reveals the true runtime behavior of an application, going far deeper than the system insights provided by debuggers. This is particularly effective when developing and working with complex embedded systems comprising multiple threads and interrupts: SystemView can ensure a system performs as designed, can track down inefficiencies, and show unintended interactions and resource conflicts, with a focus on the details of every single system tick.

A specific SystemView extension made by MicroEJ allows to traces the OS tasks and the MicroEJ Java threads at the same time. This chapter explains how to add SystemView feature in a platform and how to setup it.

.. note:: SystemView for MicroEJ is compatible with FreeRTOS 9 and FreeRTOS 10. 

References
==========

* https://www.segger.com/products/development-tools/systemview/
* https://www.segger.com/downloads/jlink/UM08027

Installation
============

SystemView consists on installing several items in the BSP. The following steps describe them and must be performed in right order. In case of SystemView is already available in the BSP, apply only modifications made by MicroEJ on SystemView files and SystemView for FreeRTOS files to enable MicroEJ Java threads monitoring.

1. Download and install SystemView: http://segger.com/downloads/systemview/.
2. Apply SystemView for FreeRTOS patch as described in documentation (https://www.segger.com/downloads/jlink/UM08027); patch is available in installation folder ``SEGGER\SystemView\Src\Sample\FreeRTOSVxx``.
3. Add ``SEGGER\SystemView\Src\Sample\FreeRTOSVxx\Config\SEGGER_SYSVIEW_Config_FreeRTOS.c`` in your BSP.
4. Add SystemView for MicroEJ CCO files in your BSP: ``com.microej.clibrary.thirdparty.systemview-1.3.0`` (or check the differences between pre-installed SystemView and CCO files)
5. Add SystemView for MicroEJ for FreeRTOS CCO files in your BSP: ``com.microej.clibrary.thirdparty.systemview-freertosxx-1.1.0`` (or check the differences between pre-installed SystemView and CCO files)
6. Install the implementation of MicroJvm monitoring over SystemView by adding CCO files in your BSP: ``com.microej.clibrary.llimpl.trace-systemview-2.1.0``
7. Make FreeRTOS compatible with SystemView: open  ``FreeRTOSConfig.h`` and:

   * add ``#define INCLUDE_xTaskGetIdleTaskHandle 1``
   * add ``#define INCLUDE_pxTaskGetStackStart 1``
   * add ``#define INCLUDE_uxTaskPriorityGet 1``
   * add ``#include "SEGGER_SYSVIEW_FreeRTOS.h"`` at the end of file

8. Enable SystemView on startup (before creating first OS task): call ``SEGGER_SYSVIEW_Conf();``
9. Add a call to ``SYSVIEW_setMicroJVMTask(pvCreatedTask);`` just after creating the OS task which launch the MicroJvm. The handler to give is the one filled by ``xTaskCreate`` function.

MicroJvm Task
=============

The MicroJvm task is an OS task and has got a particular role: it manages the MicroEJ Java threads. As soon as the MicroEJ application is started (when calling ``SNI_startVM``), the jobs performed during the MicroJvm task (events, semaphores etc.) are dispatched to the current MicroEJ Java thread. By consequence, this task is useless when the MicroEJ application is running.

SystemView for MicroEJ disables the visibility of the MicroJvm task when the MicroEJ application is running. It simplifies the SystemView client debugging.

Task and Thread Names
=====================

To make a distinction between the OS tasks and the MicroEJ Java thread, a prefix is added to the task/thread name: "[OS] " or "[MEJ] ".

.. _fig_sv_names:
.. figure:: images/sv_names.*
   :alt: OS and Thread Names
   :align: center

   OS and Thread Names

.. note:: SystemView limits the number of characters to 32. The prefix length is included in these 32 characters and by consequence the original task/thread name can be cropped.

Task and Thread Priorities
==========================

SystemView lists the tasks and threads according their priorities. However the priority notion has not the same signification when talking about tasks or threads: a thread priority depends on the MicroJvm task priority. 

By consequence a thread with the priority ``5`` must not be included between a task with the priority ``4`` and other task with priority ``6``. It depends on MicroJvm task priority: 

* if this task priority is ``3``, the thread has got a lower priority than task with priority ``4``. 
* if this task priority is ``7``, the thread has got a higher priority than task with priority ``6``. 

To allow SystemView making this distinction, the priorities sent to SystemView client respect the following rules:

* it is an OS task: ``priority_sent = task_priority * 100``.
* it is a MicroEJ Java thread: ``priority_sent = MicroJvm_task_priority * 100 + thread_priority``.

Use
===

MicroEJ platforms can generate specific events that allow monitoring current Java thread executed, Java exceptions, Java allocations, etc.

To enable MEJ32 tracing, in MicroEJ SDK:

1. Click on your MicroEJ application project
2. Run -> Run Configurations
3. Select your configuration
4. In the configuration tab:
5. Target -> Debug
6. Check: "Enable execution traces" and "Start execution traces automatically"

..
   | Copyright 2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
