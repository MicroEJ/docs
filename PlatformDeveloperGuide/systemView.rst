.. _systemview:

==========
SystemView
==========

Principle
=========

SystemView is a real-time recording and visualization tool for embedded systems that reveals the true runtime behavior of an application, going far deeper than the system insights provided by debuggers. This is particularly effective when developing and working with complex embedded systems comprising multiple threads and interrupts: SystemView can ensure a system performs as designed, can track down inefficiencies, and show unintended interactions and resource conflicts, with a focus on the details of every single system tick.

A specific SystemView extension made by MicroEJ allows to traces the OS tasks and the MicroEJ Java threads at the same time. This chapter explains how to add SystemView feature in a platform and how to setup it.

A SystemView support is provided to use the software with a MicroEJ system. This documentation shows how to setup your BSP and your Java application.

.. note:: SystemView for MicroEJ is compatible with FreeRTOS 9 and FreeRTOS 10. 

.. note:: This SystemView section has been written for SystemView version V2.52a. A new version of this documentation will arrive later to support the latest SystemView version.

References
==========

* https://www.segger.com/products/development-tools/systemview/
* https://www.segger.com/downloads/jlink/UM08027

Installation
============

SystemView consists on installing several items in the BSP. The following steps describe them and must be performed in right order. In case of SystemView is already available in the BSP, apply only modifications made by MicroEJ on SystemView files and SystemView for FreeRTOS files to enable MicroEJ Java threads monitoring.

1. Download and install SystemView V2.52a: http://segger.com/downloads/systemview/.
2. Apply SystemView for FreeRTOS patch as described in documentation (https://www.segger.com/downloads/jlink/UM08027); patch is available in installation folder ``SEGGER\SystemView\Src\Sample\FreeRTOSVxx``.

.. note:: If you are using FreeRTOS V10.2.0, use the patch located here: https://forum.segger.com/index.php/Thread/6158-SOLVED-SystemView-Kernelpatch-for-FreeRTOS-10-2-0/?s=add3b0f6a33159b9c4b602da0082475afeceb89a

3. Check if the patch disabled SystemView systick events in ``port.c``, if not remove these lines manually:

.. figure:: images/sytemview_remove_systick.png
   :alt: Disable systick events (too many events are generated).
   :align: center
   :scale: 75
   :width: 921px
   :height: 734px

4. Add ``SEGGER\SystemView\Src\Sample\FreeRTOSVxx\Config\SEGGER_SYSVIEW_Config_FreeRTOS.c`` in your BSP.

This file can be modified to fit with your system configuration:
   
   * Update ``SYSVIEW_APP_NAME``, ``SYSVIEW_DEVICE_NAME`` and ``SYSVIEW_RAM_BASE`` defines to fit your system information.
   * To add MicroEJ tasks data in SystemView initialization:
  
      * Add these includes ``#include "LLMJVM_MONITOR_SYSVIEW.h"`` and ``#include "LLTRACE_SYSVIEW_configuration.h"``.
      * In function ``_cbSendSystemDesc(void)``, add this instruction: ``SEGGER_SYSVIEW_SendSysDesc("N="SYSVIEW_APP_NAME",D="SYSVIEW_DEVICE_NAME",O=FreeRTOS");`` before ``SEGGER_SYSVIEW_SendSysDesc("I#15=SysTick");``.
      * Replace the ``Global function`` section by this code:

      .. code-block:: C

         /*********************************************************************
         *
         *       Global functions
         *
         **********************************************************************
         */

         SEGGER_SYSVIEW_OS_API SYSVIEW_MICROEJ_X_OS_TraceAPI;

         static void SYSVIEW_MICROEJ_X_OS_SendTaskList(void){
            SYSVIEW_X_OS_TraceAPI.pfSendTaskList();
            LLMJVM_MONITOR_SYSTEMVIEW_send_task_list();
         }
         
         void SEGGER_SYSVIEW_Conf(void) {
            SYSVIEW_MICROEJ_X_OS_TraceAPI.pfGetTime = SYSVIEW_X_OS_TraceAPI.pfGetTime;
            SYSVIEW_MICROEJ_X_OS_TraceAPI.pfSendTaskList = SYSVIEW_MICROEJ_X_OS_SendTaskList;
            
            SEGGER_SYSVIEW_Init(SYSVIEW_TIMESTAMP_FREQ, SYSVIEW_CPU_FREQ,
                                 &SYSVIEW_MICROEJ_X_OS_TraceAPI, _cbSendSystemDesc);
            SEGGER_SYSVIEW_SetRAMBase(SYSVIEW_RAM_BASE);
         }

5. Add in your BSP the MicroEJ C component files for SystemView: ``com.microej.clibrary.thirdparty.systemview-1.3.0`` (or check the differences between pre-installed SystemView and C component files)
6. Add in your BSP the MicroEJ C component files for SystemView FreeRTOS support : ``com.microej.clibrary.thirdparty.systemview-freertosxx-1.1.1`` (or check the differences between pre-installed SystemView and C component files)
7. Install the implementation of MicroJvm monitoring over SystemView by adding C component files in your BSP: ``com.microej.clibrary.llimpl.trace-systemview-2.1.0``
8. Make FreeRTOS compatible with SystemView: open  ``FreeRTOSConfig.h`` and:

   * add ``#define INCLUDE_xTaskGetIdleTaskHandle 1``
   * add ``#define INCLUDE_pxTaskGetStackStart 1``
   * add ``#define INCLUDE_uxTaskPriorityGet 1``
   * comment the line ``#define traceTASK_SWITCHED_OUT()`` if defined 
   * comment the line ``#define traceTASK_SWITCHED_IN()`` if defined 
   * add ``#include "SEGGER_SYSVIEW_FreeRTOS.h"`` at the end of file

9. Enable SystemView on startup (before creating first OS task): call ``SEGGER_SYSVIEW_Conf();``
10. Right enabling SystemView on startup, prints the RTT block address to the serial port: ``printf("SEGGER_RTT block address: %p\n", &(_SEGGER_RTT));``.

.. note:: Particulary useful if SystemView does not find automatically the RTT block address.

11. Add a call to ``SYSVIEW_setMicroJVMTask((U32)pvCreatedTask);`` just after creating the OS task which launch the MicroJvm. The handler to give is the one filled by ``xTaskCreate`` function.

12. Copy the file ``/YourPlatformProject-bsp/projects/microej/trace/systemview/SYSVIEW_MicroEJ.txt`` to the SystemView install path such as: ``SEGGER/SystemView_V252a/Description/``. If you use MicroUI traces, you can also copy the file in section :ref:`microui_traces`



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



.. note:: If your target board uses a ST-Link to flash the firmware, follow instructions provided by SEGGER Microcontroller https://www.segger.com/products/debug-probes/j-link/models/other-j-links/st-link-on-board/ to re-flash the ST-LINK on board with a J-Link firmware.

Troubleshooting
===============


OVERFLOW events in SystemView
-----------------------------

Depending on the application, OVERFLOW events can be seen in System View. To mitigate this problem, the default `SEGGER_SYSVIEW_RTT_BUFFER_SIZE` can be increased
from the default 1kB to a more appropriate size of 4kB. Still, if OVERFLOW events are still visible, the user can further increase this configuration found in
``/YourPlatformProject-bsp/projects/microej/thirdparty/systemview/inc/SEGGER_SYSVIEW_configuration.h``.


RTT Control block not found
---------------------------

.. figure:: images/systemview_rtt_not_found.png
   :alt: RTT Block not found.
   :align: center
   :scale: 100
   :width: 277px
   :height: 147px

* Get RTT block address on serial uart by resetting the board (it's printed at the beginning of the firmware program).
* In SystemView `Target > Start recording`
* In RTT Control Block Detection, select `Address` and put the address retrieved
  * You can also try with `Search Range` option

Cannot flash a firmware with ST-Link after replacing back J-Link firmware by ST-Link
------------------------------------------------------------------------------------

.. figure:: images/systemview_st_link_pb.png
   :alt: RTT Block not found.
   :align: center
   :scale: 50
   :width: 1285px
   :height: 951px

- Use ST_Link utility program to update the ST_Link firmware, go to ``ST-LINK > Firmware update``.
- Then, try to flash again.

..
   | Copyright 2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
