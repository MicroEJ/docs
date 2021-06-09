.. _tutorial_sni_non_blocking_call:

==========================================================
Make a Non-Blocking Call to a Java Native Method using SNI 
==========================================================

This tutorial describes all the steps to perform a non-blocking call to a Java method
implemented in C using the :ref:`Simple Native Interface (SNI) <sni>` mechanism.

Intended Audience
=================

The audience for this document is Platform engineers who want to
implement Low Level APIs for the Java Developers.

Prerequisites
=============

The following document assumes the reader already has a setup ready to run a MicroEJ application on a target device.

The following document also assumes the reader is familiar with the :ref:`Simple Native Interface (SNI) <sni>` mechanism.
If not, the `CallingCFromJava <https://github.com/MicroEJ/Example-Standalone-Java-C-Interface/tree/master/CallingCFromJava/>`_ 
GitHub example shows the minimum steps required to create a
Java program that makes a blocking call to a C function via the SNI interface.

Overview
========

This tutorial will show the minimum steps required to create a
Java program that makes a non-blocking call to a Java method
implemented in C, using the SNI interface.

In this example, the RTOS ``FreeRTOS`` is used in the BSP of the target device.

Requirements
============

A MicroEJ Platform with (at least):

- EDC-1.3
- BON-1.4
- SNI-1.4

Example code
============

Let's start from a MicroEJ Application that makes a blocking call to a Java method
implemented in C.

The following application:

- Creates a thread (timer task) that prints each second ``This timer fires each 1 sec`` in the console.
- Uses the main thread to call a native method that takes time to execute.

The MicroEJ Application code:

.. code:: java

    package example;

    import ej.bon.Timer;
    import ej.bon.TimerTask;

    public class NativeCCallExample {

        public static void main(String[] args) {

            // Create a timer that prints a text each second
            Timer timer;
            timer = new Timer();
            timer.schedule(new TimerTask() {
                @Override
                public void run() {
                    System.out.println("This timer fires each 1 sec");
                    System.out.flush();
                }
            }, 0, 1000);

            // Sleep some time before making the blocking call.
            try {
                Thread.sleep(3000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            System.out.println("[multiplyByTwoBlockingNative is called]");

            // Call the native C function that takes time to execute
            int ret = multiplyByTwoBlockingNative(2);

            System.out.println("[multiplyByTwoBlockingNative has finished, returned: " + ret + "]");
        }
        
        public static native int multiplyByTwoBlockingNative(int aValue);
    }

C implementation of the ``multiplyByTwoBlockingNative`` native:

.. code:: C

    #include "FreeRTOS.h"
    #include "task.h"    
    #include "sni.h"

    jint Java_example_NativeCCallExample_multiplyByTwoBlockingNative(jint aValue){
        vTaskDelay(4000); // Wait some time before returning the value
        return 2*a;
    }

Run the MicroEJ Application on the device
-----------------------------------------

Build & Run the MicroEJ application on the target device.

Expected results
----------------

The MicroEJ Application should produce the following logs:

.. note::

    A timestamp has been added in the console in order to highlight the blocking call.

.. code:: bash

    [12:00:11] MicroEJ START
    [12:00:11] This timer fires each 1 sec
    [12:00:12] This timer fires each 1 sec
    [12:00:13] This timer fires each 1 sec
    [12:00:14] [multiplyByTwoBlockingNative is called]         
    [12:00:18] This timer fires each 1 sec       # The application stopped during 4 seconds
    [12:00:18] [multiplyByTwoBlockingNative has finished, returned: 4]
    [12:00:19] This timer fires each 1 sec
    [12:00:20] This timer fires each 1 sec
    [12:00:21] This timer fires each 1 sec

The timestamp clearly shows that the execution has been stopped a while
when the call was made to the native C function.

Implement a non-blocking call
=============================

This section will explain how to update the example code, in order to
make a non-blocking call.

Here is a summary of what will be done: 

- In the C implementation of the of the Java native method:
  
  - Suspend the Java thread that called the Java native method (the other threads will still run).
  - Remove all the operations related to the data processing.
  - Create a new RTOS task and perform the processing in it.

- Resume the Java thread when the "processing" task is done and kill the task.
- Implement a callback function to return the computed value in the Java world.

Update the C native function implementation
-------------------------------------------

Step 1: Create a structure to embed the C native function argument
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this new implementation, the processing performed in the ``Java_example_NativeCCallExample_multiplyByTwoBlockingNative()``
function will be delegated to an other RTOS task.

The arguments of the ``Java_example_NativeCCallExample_multiplyByTwoBlockingNative()``
function must be passed to the new task through a structure.

.. code-block:: C

    typedef struct Data_t
    {
        int32_t java_thread_id;
        int32_t aValue;
    } ParametersData_t;

The structure must also contain a variable to save the ID of the Java thread that called the function. 
It will be used to resume this Java thread after the execution of the native function.

Step 2: Update the C native function
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The role of the ``Java_example_NativeCCallExample_multiplyByTwoBlockingNative()`` function is now to delegate
the processing to an other function executed in an other RTOS task.

- Allocate memory for the ``ParametersData_t`` structure and initialize its variables:

  .. code-block:: C
  
      ParametersData_t* pvParameters = pvPortMalloc(sizeof(ParametersData_t));
      int32_t java_thread_id = SNI_getCurrentJavaThreadID(); 
  
      if(NULL== pvParameters){
          SNI_throwNativeException(-1, "malloc failed");   
      } else {
          pvParameters->java_thread_id=java_thread_id;   
          pvParameters->aValue=aValue;
      }

- Create a new FreeRTOS task to perform the processing. Let's call the task function: ``multiplyByTwoBlockingNative_processing()``.

  .. code-block:: C
  
      xTaskCreate( multiplyByTwoBlockingNative_processing, "multiplyByTwoBlockingNative_processing", 1024, (void*) pvParameters, PROCESSING_TASK_PRIO, NULL ); 

- Suspend the calling Java thread and add a callback function.
  Let's call the callback function ``multiplyByTwoBlockingNative_callback()``.
  It will be called when the Java thread will be resumed:
    
  .. code-block:: C
  
      SNI_suspendCurrentJavaThreadWithCallback(0, (SNI_callback*)multiplyByTwoBlockingNative_callback, NULL);

The value returned by the ``Java_example_NativeCCallExample_multiplyByTwoBlockingNative()`` doesn't matter anymore.
The callback function will be in charge to return the value. 

The updated ``Java_example_NativeCCallExample_multiplyByTwoBlockingNative()`` function should look like this:

.. code:: C

    #include "FreeRTOS.h"
    #include "task.h"    
    #include "sni.h"

    #define PROCESSING_TASK_PRIO YOUR_PRIORITY

    jint Java_example_NativeCCallExample_multiplyByTwoBlockingNative(jint aValue){
        
        ParametersData_t* pvParameters = pvPortMalloc(sizeof(ParametersData_t));

        if(NULL== pvParameters){
            SNI_throwNativeException(-1, "malloc failed");  
            return -1; 
        }
         
        pvParameters->java_thread_id = SNI_getCurrentJavaThreadID();   
        pvParameters->aValue = aValue;
        
        xTaskCreate( multiplyByTwoBlockingNative_processing, "multiplyByTwoBlockingNative_processing", 1024, (void*) pvParameters, PROCESSING_TASK_PRIO, NULL ); 

        SNI_suspendCurrentJavaThreadWithCallback(0, (SNI_callback*)multiplyByTwoBlockingNative_callback, NULL);

        return 0; // Dummy value not used
    }

Step 3: Implement the processing task function
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Implement the ``void multiplyByTwoBlockingNative_processing(void * pvParameters)`` task function:

- Get the parameters to compute:

.. code:: C

    ParametersData_t* readParameters = (ParametersData_t*)pvParameters;

- Do the processing:

.. code:: C

    int32_t aValue = readParameters->aValue;
    vTaskDelay(4000); 
    int32_t result = 2*aValue;

- Resume the Java thread and return the result of the processing:

.. code:: C

    SNI_resumeJavaThreadWithArg(readParameters->java_thread_id, (void*)result);

- Free the memory and delete the task

.. code:: C

    vPortFree(pvParameters);
    vTaskDelete( xTaskGetCurrentTaskHandle() );

The ``void multiplyByTwoBlockingNative_processing(void * pvParameters)`` should look like this:

.. code:: C

    void multiplyByTwoBlockingNative_processing(void * pvParameters){

        // Get the parameters
        ParametersData_t* readParameters = (ParametersData_t*)pvParameters;
        int32_t aValue = readParameters->aValue;

        // Do the processing
        vTaskDelay(4000);
        int32_t result = 2*aValue;

        // Resume the Java thread
        SNI_resumeJavaThreadWithArg(readParameters->java_thread_id, (void*)result);

        // Free the parameters structure and delete the task
        vPortFree(pvParameters);
        vTaskDelete( xTaskGetCurrentTaskHandle() );
    }

Step 4 : Implement the callback function
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The callback function must have the same signature as the SNI native, in this case:
``jint multiplyByTwoBlockingNative_callback(jint aValue)``.

The callback function is automatically called by the Java thread when it is resumed.
Use the ``SNI_getCallbackArgs()`` function to retrieve the arguments given to an SNI callback
with the ``SNI_suspendCurrentJavaThreadWithCallback()`` function.

.. code:: C

    jint multiplyByTwoBlockingNative_callback(jint aValue)
    {
        int32_t result;
        SNI_getCallbackArgs(NULL, (void*)&result); // get the result of the reader_function()
        return (jint)result;
    }

Run the MicroEJ Application on the device
-----------------------------------------

Once those functions have been implemented in the BSP, 
build & run the MicroEJ application on the target device.

Expected results
----------------

The MicroEJ Application should produce the following logs:

.. note::

    A timestamp has been added in the console in order to highlight the non-blocking call.

.. code:: bash

    [12:36:36] This timer fires each 1 sec
    [12:36:37] This timer fires each 1 sec
    [12:36:38] This timer fires each 1 sec
    [12:36:39] [multiplyByTwoBlockingNative is called]
    [12:36:39] This timer fires each 1 sec
    [12:36:40] This timer fires each 1 sec
    [12:36:41] This timer fires each 1 sec
    [12:36:42] This timer fires each 1 sec
    [12:36:43] This timer fires each 1 sec
    [12:36:43] [multiplyByTwoBlockingNative has finished, returned: 4]
    [12:36:44] This timer fires each 1 sec
    [12:36:45] This timer fires each 1 sec

The call to the ``multiplyByTwoBlockingNative()`` method doesn't block the Java application
execution anymore!

..
   | Copyright 2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
