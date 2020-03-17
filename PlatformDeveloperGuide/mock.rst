====
Mock
====


Principle
=========

The HIL engine is a Java standard-based engine that runs Mocks. A Mock
is a jar file containing some Java classes that simulate natives for the
Simulator. Mocks allow applications to be run unchanged in the Simulator
while still (apparently) interacting with native code.


Functional Description
======================

As with [SNI], HIL is responsible for finding the method to execute as a
replacement for the native Java method that the MicroEJ Simulator tries
to run. Following the [SNI] philosophy, the matching algorithm uses a
naming convention. When a native method is called in the MicroEJ
Simulator, it requests that the HIL engine execute it. The corresponding
Mock executes the method and provides the result back to the MicroEJ
Simulator.

.. figure:: images/hil3.*
   :alt: The MicroEJ Simulator Executes a Native Java Method ``foo()``.
   :width: 80.0%
   :align: center

   The MicroEJ Simulator Executes a Native Java Method ``foo()``.


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

To implement the native method ``getSensorValue(int sensorID)``, you
need to create a MicroEJ standard project containing the same ``Sensor``
class on the same ``example`` package. To do so, open the Eclipse menu
``File > New > Project... > Java > Java Project`` in order to create a
MicroEJ standard project.

The following code is the required ``Sensor`` class of the created Mock
project:

.. code:: java

   package example;

   import java.util.Random;

   /**
    * Java standard class included in a Mock jar file.
    * It implements the native method using a Java method.
    */
   public class Sensor {

       /**
        * Constants
        */
       private static final int SENSOR_ERROR = -1;
       private static final int POTENTIOMETER_ID = 3;
       
       private static final Random RANDOM = new Random();
       
       /**
        * Implementation of native method "getSensorValue()"
        * 
        * @param sensorID Sensor ID
        * @return Simulated sensor value
        */
       public static int getSensorValue(int sensorID) {
           if( sensorID == POTENTIOMETER_ID ) {
               // For the simulation, Mock returns a random value
               return RANDOM.nextInt();
           }
           return SENSOR_ERROR;
       }
       
   }


Mocks Design Support
====================

Interface
---------

The MicroEJ Simulator interface is defined by static methods on the Java
class ``com.is2t.hil.NativeInterface``.

Array Type Arguments
--------------------

Both [SNI] and HIL allow arguments that are arrays of base types. By
default the contents of an array are NOT sent over to the Mock. An
"empty copy" is sent by the HIL engine, and the contents of the array
must be explicitly fetched by the Mock. The array within the Mock can be
modified using a regular assignment. Then to apply these changes in the
MicroEJ Simulator, the modifications must be flushed back. There are two
methods provided to support fetch and flush between the MicroEJ
Simulator and the HIL:

-  ``refreshContent``: initializes the array argument from the contents
   of its MicroEJ Simulator counterpart.

-  ``flushContent``: propagates (to the MicroEJ Simulator) the contents
   of the array that is used within the HIL engine.

.. figure:: images/hil4.*
   :alt: An Array and Its Counterpart in the HIL Engine.
   :width: 80.0%
   :align: center

   An Array and Its Counterpart in the HIL Engine.

Below is a typical usage.

::

   public static void foo(char[] chars, int offset, int length){
           NativeInterface ni = HIL.getInstance();
           //inside the Mock
           ni.refreshContent(chars, offset, length);
           chars[offset] = 'A';
           ni.flushContent(chars, offset, 1);
   }

Blocking Native Methods
-----------------------

Some native methods block until an event has arrived [SNI]. Such
behavior is implemented in a Mock using the following three methods:

-  ``suspendCurrentJavaThread(long timeout)``: Tells the MicroEJ
   Simulator that the green thread should block after returning from the
   current native. This method does not block the Mock execution. The
   green thread is suspended until either a Mock thread calls
   ``resumeJavaThread`` or the specified amount of milliseconds has
   elapsed.

-  ``resumeJavaThread(int id)``: Resumes the green thread with the given
   ID. If the thread is not suspended, the resume stays pending, and the
   next call to ``suspendCurrentJavaThread`` will not block the thread.

-  ``getCurrentJavaThreadID()``: Retrieves the ID of the current Java
   thread. This ID must be given to the ``resumeJavaThread`` method in
   order to resume execution of the green thread.

::

   public static byte[] Data = new byte[BUFFER_SIZE];
   public static int DataLength = 0;

   //Mock native method
   public static void waitForData(){
         NativeInterface ni = HIL.getInstance();
         //inside the Mock
         //wait until the data is received
         setWaitingThread(ni.getCurrentJavaThreadID());
         if(DataLength == 0){
               ni.suspendCurrentJavaThread(0);
         }
   }

   //Mock data reader thread
   public static void notifyDataReception()
         NativeInterface ni = HIL.getInstance();
         DataLength = readFromInputStream(Data);
         ni.resumeJavaThread(getWaitingThread());
   }

Resource Management
-------------------

In Java, every class can play the role of a small read-only file system
root: The stored files are called "Java resources" and are accessible
using a path as a String.

The MicroEJ Simulator interface allows the retrieval of any resource
from the original Java world, using the ``getResourceContent`` method.

::

   public static void bar(byte[] path, int offset, int length) {
         NativeInterface ni = HIL.getInstance();
         ni.refreshContent(path, offset, length);
         String pathStr = new String(path, offset, length);
         byte[] data = ni.getResourceContent(pathStr);
         ...
   }

Synchronous Terminations
------------------------

To terminate the whole simulation (MicroEJ Simulator and HIL), use the
stop() method.

::

   public static void windowClosed() {
         HIL.getInstance().stop();
   }


Dependencies
============

The MicroEJ Platform architecture provides some APIs (HIL APIs) to
develop a Mock that will be ready to be used against the Simulator. The
classpath variable that allows you to access to the HIL Engine API is
``HILENGINE-2.0.1``. MicroEJ projects that build Mocks should put that
library on their build path.


Installation
============

The Mock creator is responsible for building the Mock jar file using
his/her own method (Eclipse build, ``javac``, etc.).

Once built, the jar file must be put in this specific platform
configuration project folder in order to be included during the platform
creation : ``dropins/mocks/dropins/``.


Use
===

Once installed, a Mock is used automatically by the Simulator when the
MicroEJ Application calls a native method which is implemented into the
Mock.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
