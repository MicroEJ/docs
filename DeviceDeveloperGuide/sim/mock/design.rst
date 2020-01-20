Mocks Design Support
====================

Interface
---------

The MicroEJ simulator interface is defined by static methods on the Java
class ``com.is2t.hil.NativeInterface``.

Array Type Arguments
--------------------

Both [SNI] and HIL allow arguments that are arrays of base types. By
default the contents of an array are NOT sent over to the mock. An
"empty copy" is sent by the HIL engine, and the contents of the array
must be explicitly fetched by the mock. The array within the mock can be
modified using a regular assignment. Then to apply these changes in the
MicroEJ simulator, the modifications must be flushed back. There are two
methods provided to support fetch and flush between the MicroEJ
simulator and the HIL:

-  ``refreshContent``: initializes the array argument from the contents
   of its MicroEJ simulator counterpart.

-  ``flushContent``: propagates (to the MicroEJ simulator) the contents
   of the array that is used within the HIL engine.

.. figure:: mock/images/hil4.svg
   :alt: An Array and Its Counterpart in the HIL Engine.
   :width: 80.0%

   An Array and Its Counterpart in the HIL Engine.

Below is a typical usage.

::

   public static void foo(char[] chars, int offset, int length){
           NativeInterface ni = HIL.getInstance();
           //inside the mock
           ni.refreshContent(chars, offset, length);
           chars[offset] = 'A';
           ni.flushContent(chars, offset, 1);
   }

Blocking Native Methods
-----------------------

Some native methods block until an event has arrived [SNI]. Such
behavior is implemented in a mock using the following three methods:

-  ``suspendCurrentJavaThread(long timeout)``: Tells the MicroEJ
   simulator that the green thread should block after returning from the
   current native. This method does not block the mock execution. The
   green thread is suspended until either a mock thread calls
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
         //inside the mock
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

The MicroEJ simulator interface allows the retrieval of any resource
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

To terminate the whole simulation (MicroEJ simulator and HIL), use the
stop() method.

::

   public static void windowClosed() {
         HIL.getInstance().stop();
   }
