Threads
=======

Principle
---------

The MicroUI implementation for MicroEJ uses internal threads. These
threads are created during the MicroUI initialization step, and are
started by a call to ``MicroUI.start()``. Refer the the MicroUI
specification [MUI] for more information about internal threads.

List
----

-  DisplayPump: This thread manages all display events (``repaint``,
   ``show()``, etc. There is one thread per display.

-  InputPump: This thread reads the I/O devices inputs and dispatches
   them into the display pump(s).

Memory
------

The threads are always running. The user has to count them to determine
the number of concurrent threads the MJVM can run (see Memory options in
`??? <#workbenchLaunchOptions>`__).

Exceptions
----------

The threads cannot be stopped with a Java exception: The exceptions are
always checked by the framework.

When an exception occurs in a user method called by an internal thread
(for instance ``paint()``), the current ``UncaughtExceptionHandler``
receives the exception. The behavior of the default handler is to print
the stack trace.
