=============================
Simple Native Interface (SNI)
=============================


Principle
=========

SNI provides a simple mechanism for implementing native Java methods in
the C language.

SNI allows you to:

-  Call a C function from a Java method.

-  Access an Immortal array in a C function (see the [BON]
   specification to learn about immortal objects).

SNI does not allow you to:

-  Access or create a Java object in a C function.

-  Access Java static variables in a C function.

-  Call Java methods from a C function.

SNI provides some Java APIs to manipulate some data arrays between Java
and the native (C) world.


Functional Description
======================

SNI defines how to cross the barrier between the Java world and the
native world:

-  Call a C function from Java.

-  Pass parameters to the C function.

-  Return a value from the C world to the Java world.

-  Manipulate (read & write) shared memory both in Java and C : the
   immortal space.

.. _fig_sni-flow:
.. figure:: images/sni_flow.*
   :alt: SNI Processing
   :width: 60.0%
   :align: center

   SNI Processing

:ref:`The above illustration <fig_sni-flow>` shows both Java and C code
accesses to shared objects in the immortal space, while also accessing
their respective memory.


Example
=======

.. code:: java

   package example;

   import java.io.IOException;

   /**
    * Abstract class providing a native method to access sensor value.
    * This method will be executed out of virtual machine.
    */
   public abstract class Sensor {

       public static final int ERROR = -1;

       public int getValue() throws IOException {
           int sensorID = getSensorID();
           int value = getSensorValue(sensorID);
           if (value == ERROR) {
               throw new IOException("Unsupported sensor");
           }
           return value;
       }

       protected abstract int getSensorID();

       public static native int getSensorValue(int sensorID);
   }

   class Potentiometer extends Sensor {
       
       protected int getSensorID() {
           return Constants.POTENTIOMETER_ID; // POTENTIOMETER_ID is a static final
       }
   }

.. code:: c

   // File providing an implementation of native method using a C function
               #include <sni.h>
               #include <potentiometer.h>
               
               #define SENSOR_ERROR (-1)
               #define POTENTIOMETER_ID (3)
               
               jint Java_example_Sensor_getSensorValue(jint sensor_id){
               
                   if (sensor_id == POTENTIOMETER_ID)
                   {
                       return get_potentiometer_value();
                   }
                   return SENSOR_ERROR;
               }


Synchronization
===============

A call to a native function uses the same RTOS task as the RTOS task
used to run all Java green threads. So during this call, the MicroEJ
Core Engine cannot schedule other Java threads.

SNI defines C functions that provide controls for the green threads'
activities:

-  ``int32_t SNI_suspendCurrentJavaThread(int64_t timeout)``: Suspends the
   execution of the Java thread that initiated the current C call. This
   function does not block the C execution. The suspension is effective
   only at the end of the native method call (when the C call returns).
   The green thread is suspended until either an RTOS task calls
   ``SNI_resumeJavaThread``, or the specified number of milliseconds has
   elapsed.

-  ``int32_t SNI_getCurrentJavaThreadID(void)``: Permits retrieval of the ID
   of the current Java thread within the C function (assuming it is a
   "native Java to C call"). This ID must be given to the
   ``SNI_resumeJavaThread`` function in order to resume execution of the
   green thread.

-  ``int32_t SNI_resumeJavaThread(int32_t id)``: Resumes the green thread
   with the given ID. If the thread is not suspended, the resume stays
   pending.

.. _fig_sni-sync:
.. figure:: images/sni_sync.*
   :alt: Green Threads and RTOS Task Synchronization
   :width: 80.0%
   :align: center

   Green Threads and RTOS Task Synchronization

:ref:`The above illustration <fig_sni-sync>` shows a green thread (GT3) which has called
a native method that executes in C. The C code suspends the thread after
having provisioned its ID (e.g. 3). Another RTOS task may later resume
the Java green thread.


Dependencies
============

No dependency.


Installation
============

The SNI library is a built-in feature of the platform, so there is no
additional dependency to call native code from Java. In the platform
configuration file, check :guilabel:`Java to C Interface` > :guilabel:`SNI API` to
install the additional Java APIs in order to manipulate the data arrays.


Use
===

A classpath variable named ``SNI-1.2`` is available, which must be added
to the build path of the MicroEJ Application project, in order to allow
access to the SNI library.


..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
