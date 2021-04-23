========
Watchdog
========


Overview
========

The Watchdog foundation library provides a way to handle platform watchdog timer.
A watchdog is particularly useful if you want to monitor different items of your
software system during the runtime. The figure below shows watchdog elements at each level of 
a MicroEJ project:

.. figure:: images/watchdog_sandwich.png
   :alt: Watchdog API integration
   :align: center
   :scale: 80%


Principle
=========

The Watchdog API is in **two parts**, the first part drives the **watchdog timer** itself.
The second part of the API implements a **checkpoint registration system** linked to the watchdog timer.

The checkpoint registration system allows the user to add checkpoints monitored by the platform watchdog timer.
Each checkpoint registered by the Watchdog API must attest their activity before the watchdog
timeout, otherwise a **hardware reset** is performed. 
The high level diagram below summarizes interactions between the user application, 
the Watchdog API and the Watchdog timer.

.. figure:: images/watchdog_highlevel_diagram.png
   :alt: Watchdog API high level description
   :align: center
   :scale: 80%


The particularity of this library is that it can be either used in Java, in C inside the BSP
or even both of them. The use of this library in the BSP in C is relevant when the user needs
to monitor an item of the software system which is outside of the MicroEJ Virtual Machine. 
The sequence diagram below shows a standard use of the Watchdog API in Java and in C.


.. figure:: images/watchdog_seq_diagram.png
   :alt: Watchdog API sequence diagram
   :align: center
   :scale: 80%

Dependencies
============

- This library needs to be used with the Watchdog Generic CCO developed for this purpose,
  its module name is ``watchdog-generic``.

- ``LLWATCHDOG_impl.h`` implemetend by the Watchdog Generic CCO (see :ref:`LLWATCHDOG-API-SECTION`).

- ``watchdog_helper.h`` implementation needed by the Watchdog Generic CCO (see :ref:`LLWATCHDOG-API-SECTION`).

Installation
============

Watchdog is an API composed of a ``Pack`` module and a ``CCO`` module.
You need both of them in your platform to install the API.

In the platform configuration project, the one with ``-configuration`` extension, add
the dependency to the two required modules in the file ``module.ivy``:

::

   <dependency org="com.microej.pack.monitoring" name="monitoring-pack" rev="1.0.0" />
   <dependency changing="true" org="com.microej.clibrary.llimpl" name="watchdog-generic" rev="2.0.0" transitive="false"/>

Then, you have to implement functions that match the ``LLWATCHDOG_IMPL_*_action`` pattern
which is required by the Watchdog Generic CCO.

If you use the Realtek ``AmebaD`` board, you can add in the platform configuration the dependency
to the CCO module ``watchdog-helper-realtek-amebad``, in order to retrieve implemented
functions required by the Watchdog Generic CCO. Thus, add this line to ``module.ivy``:

::

   <dependency changing="true" org="com.microej.clibrary.llimpl" name="watchdog-helper-realtek-amebad" rev="1.0.0" transitive="false"/>

Then, build the platform: right-click on ``-configuration`` project > ``Build module``.

Use in a Java application
=========================

The `Watchdog API Module <https://repository.microej.com/artifacts/ej/api/monitoring/>`_
must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project in order to allow access to the Watchdog library.

::

   <dependency org="ej.api.monitoring" name="watchdog" rev="1.0.1" transitive="false"/>


Code example in Java
====================

Here is an example that summarizes all features in a simple use case.
The checkpoint is performed in a TimerTask thread scheduled to run every 5 seconds.
To use TimerTask in your Java application, add the following dependency:

::

	<dependency org="ej.api" name="bon" rev="1.4.0" />

Then, you can use this example code:

.. code:: java

	// Test a simple watchdog use case
	public static void main(String[] args) {

		if (Watchdog.isResetCause()) {
			System.out.println("Watchdog triggered the last board reset!"); //$NON-NLS-1$
		} else {
			System.out.println("Watchdog DID NOT triggered the last board reset!"); //$NON-NLS-1$
		}

		Watchdog.init();
		System.out.println("Watchdog initialized to trigger after " + Watchdog.getWatchdogTimeoutMs() + " ms."); //$NON-NLS-1$

		TimerTask checkpointTask = new TimerTask() {

			private final int taskID = Watchdog.registerCheckpoint();

			@Override
			public void run() {
				// We attest our task activity using the checkpoint method.
				Watchdog.checkpoint(this.taskID); // Since this is our only checkpoint registered, the watchdog is
				// refreshed.
				System.out.println("Task performed watchdog checkpoint with the ID " + this.taskID); //$NON-NLS-1$
			}
		};

		// We schedule our task to be executed every 5 seconds.
		Timer timer = new Timer();
		final int DELAY = 0;
		final int PERIOD = 5000; // We assume that the watchdog timeout period is higher than 5000 milliseconds.
		timer.schedule(checkpointTask, DELAY, PERIOD);

		// Everything is ready, we launch the watchdog
		Watchdog.start();
		System.out.println("Watchdog started!");

		// Let the checkpointTask runs for a minute.

		final int WAIT_A_MINUTE = 60000; // 60 000 milliseconds to wait a minute
		try {
			Thread.sleep(WAIT_A_MINUTE);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		// Our program is finished. Now we stop the checkpointTask and the watchdog.
		timer.cancel();
		Watchdog.stop(); // This method also unregisters all checkpoints.
		System.out.println("Monitored task stopped and Watchdog stopped.");
	}



Use in C inside the BSP
=======================

Once the platform is configured to use the Watchdog API as explained in ``Installation``
section, you can use functions defined in ``LLWATCHDOG_impl.h``.

Note that compared to the Java API, you have to get error codes returned by functions
to check if the function is executed correctly since you have no access to
exceptions generated for the Java.

The watchdog Low Level API provides a set of functions with the same usage as in Java.
Here is the list of the watchdog Low Level API functions:

.. code:: c

   LLWATCHDOG_IMPL_init()                      // refer to ej.watchdog.Watchdog.init()
   LLWATCHDOG_IMPL_start()                     // refer to ej.watchdog.Watchdog.start()
   LLWATCHDOG_IMPL_stop()                      // refer to ej.watchdog.Watchdog.stop()
   LLWATCHDOG_IMPL_registerCheckpoint()        // refer to ej.watchdog.Watchdog.registerCheckpoint()
   LLWATCHDOG_IMPL_unregisterCheckpoint()      // refer to ej.watchdog.Watchdog.unregisterCheckpoint()
   LLWATCHDOG_IMPL_checkpoint()                // refer to ej.watchdog.Watchdog.checkpoint()
   LLWATCHDOG_IMPL_isResetCause()              // refer to ej.watchdog.Watchdog.isResetCause()
   LLWATCHDOG_IMPL_getWatchdogTimeoutMs()      // refer to ej.watchdog.Watchdog.getWatchdogTimeoutMs()


There is an additional function in ``LLWATCHDOG_impl.h`` compared to the Java API.
This is ``LLWATCHDOG_IMPL_refresh``, because a low level implementation of this function
is required for the library. However, the user does not need and should not use this function on his own.




Code example in C
=================

Here is an example that summarizes main features in a simple use case.
The checkpoint is performed in a FreeRTOS task scheduled to attest its activity to the watchdog every 5 seconds.

.. code:: C
      
   #include <stdio.h>
   #include <stdint.h>

   #include "FreeRTOS.h"
   #include "task.h"
   #include "queue.h"
   #include "semphr.h"

   #include "LLWATCHDOG_impl.h"

   #define MONITORED_TASK_STACK_SIZE 1024
   #define TASK_SLEEP_TIME_MS 5000 // We sleep for 5 seconds, assuming that the watchdog timeout is higher.

   /*-----------------------------------------------------------*/

   static void my_monitored_task( void *pvParameters ){
      // We get an ID from watchdog registration system for this new checkpoint
      int32_t checkpoint_id = LLWATCHDOG_IMPL_registerCheckpoint();

      for(;;){
         vTaskDelay( TASK_SLEEP_TIME_MS / portTICK_PERIOD_MS);
         LLWATCHDOG_IMPL_checkpoint(checkpoint_id); // Since this is our only checkpoint registered, the watchdog is refreshed.
         printf("MonitoredTask with ID = %d did watchdog checkpoint!\n\r", checkpoint_id);
      }
   }

   /*-----------------------------------------------------------*/

   int main( void ){
      xTaskHandle handle_monitored_task;

      /* Check if last reset was done by the Watchdog. */
      if(LLWATCHDOG_IMPL_isResetCause()){
         printf("Watchdog triggered the last reset, we stop the program now! \n\r");
         return -1;
      }

      /* Setup the Watchdog */
      if(WATCHDOG_ERROR == LLWATCHDOG_IMPL_init()){
   	   printf("Failed to init watchdog in main. \n\r");
      } else{
         printf("Watchdog initialized to trigger after %d ms \n\r", LLWATCHDOG_IMPL_getWatchdogTimeoutMs());
      }

      /* Start the Watchdog */
      if(WATCHDOG_ERROR == LLWATCHDOG_IMPL_start()){
         printf("Failed to start watchdog in main. \n\r");
      } else{
         printf("Watchdog started!\n\r");
      }

      /* Create the monitored task. */
      xTaskCreate( my_monitored_task, "MonitoredTask", MONITORED_TASK_STACK_SIZE, NULL, tskIDLE_PRIORITY, &handle_monitored_task);

      /* Start the scheduler. */
      printf("Starting scheduler...\n\r");
      vTaskStartScheduler();

      return 0;
   }

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
