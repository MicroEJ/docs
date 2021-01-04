Debug a "UI Freeze"
===================

When an application User Interface freezes and becomes unresponsive,
in most cases, one of the following conditions applies:

- An unrecoverable system failure occurred, like a HardFault, and the
  RTOS tasks are not scheduled anymore.
- The RTOS task that runs the MicroEJ runtime is never given CPU time
  (suspended or blocked).
- The RTOS task that runs the MicroEJ runtime is executing
  never-ending native code (infinite loop in native implementation for
  example).
- A Java method is executing a long running operation in the MicroUI
  thread (also called Display Pump thread).
- The application code is unable to receive or process user input
  events.

This tutorial explains how to instrument the code in order to locate
the issue when the UI freeze occurs.

This tutorial assumes the freeze only occurs on the device.  If the
issue is reproducible on Simulator, using the debugger is probably the
easiest way to find out the issue.

Bottom-Up approach
------------------

Check RTOS Scheduler Liveness
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Let's start at low level by figuring out if the RTOS is scheduling the
tasks correctly.  If possible, use a debugger, if not use the heart
beat task described here.

Make one of the RTOS task act like a heart beat: create a dedicated
task and make it report in some way at a regular pace (print a message
on standard output, blink a LED, etc.).

If the heart beat is still running when the UI freeze occurs, we can
go a step further and check whether the MicroEJ runtime is still
scheduling Java threads or not.

If you use task priorities for the RTOS tasks management, ensure that
the priority of the RTOS task is equal or lower than the priority of
the MicroEJ runtime task.

If the RTOS task of the heart beat doesn't run when:

- the priority is the highest than any other tasks, then the RTOS
  scheduler is not scheduling anything.
- the priority is the same as the MicroEJ runtime and other tasks with
  a higher priority exist, then one or more RTOS tasks are causing
  starvation by taking all the resources.

..
   @startuml
   if (Heart Beat task runs\nwith highest priority) then (no)
     #pink:RTOS scheduler not working;
     kill
   else (yes)
     if (Heart Beat task runs\nwith same priority\nas MicroEJ Runtime) then (no)
       #pink:MicroEJ Runtime is starving;
       kill
     else (yes)
       :MicroEJ Runtime is running;
       kill
     endif
   endif
   @enduml  

.. image:: images/tuto_microej_debug_ui_freeze_rtos_task_heart_beat_priority.png

Check Java Scheduler Liveness
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As a reminder, the architecture of the MicroEJ runtime is called green
thread architecture, it defines a multi-threaded environment without
relying on any native RTOS capabilities. Therefore, the whole Java world
runs in one single RTOS task. Read more about this architecture in the
`Platform Developer
Guide <https://docs.microej.com/en/latest/PlatformDeveloperGuide/coreEngine.html>`__.
A quick way to check if the Java threads are scheduled correctly is, here again, to
make one of the threads print a heart beat message. Copy/paste the
following snippet in the ``main()`` method of the application:

.. code-block:: java

   TimerTask task = new TimerTask() {

       @Override
       public void run() {
           System.out.println("Alive");
       }
   };
   Timer timer = new Timer();
   timer.schedule(task, 10_000, 10_000);

This code creates a new Java thread that will print the message ``Alive``
on the standard output every 10 seconds.

If the ``Alive`` printouts stop when the UI freeze occurs (assuming no
one cancelled the ``Timer``), then it means that the MicroEJ Runtime
stopped scheduling the Java threads.

Here are a few suggestions:

- The RTOS task that runs the MicroEJ runtime might be suspended or
  blocked. Check if some API call is suspending the task or if a
  shared resource could be blocking it.

- When a Java native method is called, it calls its C counterpart
  function in the RTOS task that runs the MicroEJ runtime. While the C
  function is running, no other Java methods can run : the Java world
  awaits for the C function to finish. As a consequence, if the C
  function never returns, no Java thread can ever run again. Spot any
  suspect native functions and trace every entry/exit to detect faulty
  code.

Please refer to :ref:`implementation_details` if you encounter issues
to implement the heart beat.

Check UI Thread Liveness
~~~~~~~~~~~~~~~~~~~~~~~~

Now, what if the ``Alive`` heart beat runs while the UI is frozen?
Java threads are getting scheduled but the UI thread (also called
Display Pump thread), does not process display events.

Let's make the heart beat snippet above execute in the UI
thread. Simply wraps the ``System.out.println("Alive")`` with a
``callSerially``:

.. code-block:: java

   TimerTask task = new TimerTask() {

       @Override
       public void run() {
           System.out.println("TimerTask Alive");
           Display.getDefaultDisplay().callSerially(new Runnable() {
           
               @Override
               public void run() {
                   System.out.println("UI Alive");
               }
           });
       }
       
       @Override
       public void uncaughtException(Timer timer, Throwable e) {
           // Default implementation of this method would cancel the task. 
           // Let's just ignore uncaught exceptions for debug purposes.
           e.printStackTrace();
       }
   };
   Timer timer = new Timer();
   timer.schedule(task, 10_000, 10_000);

In case this snippet prints ``TimerTask Alive`` but not ``UI alive`` when
the freeze occurs, then there are few options:

-  The application might be processing a long operation in the UI
   thread, for example:

   -  infinite/indeterminate loops
   -  network/database access
   -  heavy computations
   -  ``Thread.sleep()``/``Object.wait()``
   -  ``SNI_suspendCurrentJavaThread()`` in native call

   When doing so, any other UI-related operation will not be processed
   until completion, leading the display to being unresponsive. Any code
   that runs in the UI thread might be responsible. Look for code
   executed as a result of calls to:

   -  ``repaint()``: code in ``renderContent()``
   -  ``revalidate()``/``revalidateSubTree()``: code in
      ``validateContent()`` and ``setBoundsContent()``
   -  ``handleEvent()``
   -  ``callSerially()``: code wrapped in such calls will be executed
      in the UI thread

-  The UI thread has terminated.

As a general rule, avoid running long operations in the UI thread,
follow the general pattern and use a dedicated thread/executor instead:

.. (QUESTION: use a sequence diagram to be more explicit?)

.. code-block:: java

   ExecutorService executorService = ServiceLoaderFactory.getServiceLoader().getService(ExecutorService.class, SingleThreadExecutor.class);
   executorService.execute(new Runnable() {

       @Override
       public void run() {
       
           // (... long non-UI operation ...)
           
           // optional: update the UI upon completion
           Display.getDefaultDisplay().callSerially(new Runnable() {
                       
           @Override
           public void run() {
                       // update display code (will be executed in UI thread)
           }
       });
       }
   });

Check Input Events Processing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Another case that is worth looking at is whether the application is
processing user input events like it should. The UI may look "frozen"
only because it doesn't react to input events. Replace the desktop
instance with the one below to log all user inputs.

.. code-block:: java

   Desktop desktop = new Desktop() {

       @Override
       public EventHandler getController() {
           EventHandler controller = super.getController();
           return new EventHandler() {
           @Override
               public boolean handleEvent(int event) {
               System.out.println("Desktop.handleEvent() received event of type " + Event.getType(event));
               return controller.handleEvent(event);
               }
           };
       }
   };

LLMJVM_dump
-----------

In addition to the tips described above, the ``LLMJVM_dump`` function
will give detailed information about the current state of Java
threads when the issue occurs.  See :ref:`this section<vm_dump>` to
learn more about ``LLMJVM_dump``.

.. _implementation_details:

Implementation Details
----------------------

Java Threads Creation
~~~~~~~~~~~~~~~~~~~~~

The number of threads in the MicroEJ Application must to be sufficient
to support the creation of additional threads when using ``Timer`` and
``Thread``.  The number of available threads can be updated in the
launch configuration of the application.

If it is not possible to increase the number of available threads (for
example because the memory is full), try to reuse another thread but
not the UI thread.

UART not available
~~~~~~~~~~~~~~~~~~

If the UART output is not available, use another method to signal that
the heart beat task is running (e.g. blink a LED).

Sources
-------

-  `MicroUI and
   multithreading <https://forum.microej.com/t/gui-microui-and-multithreading/652>`__
-  `MicroEJ Core
   Engine <https://docs.microej.com/en/latest/PlatformDeveloperGuide/coreEngine.html>`__
-  `SNI
   Specification <http://e-s-r.net/download/specification/ESR-SPE-0012-SNI_GT-1.2-H.pdf>`__
