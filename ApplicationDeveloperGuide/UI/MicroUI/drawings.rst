.. _section.ui.drawing_logs:

Drawing Logs
============

When performing drawing operations, it may happen that the VEE port reports incidents that occurred during a drawing to the application.
To do so, graphics contexts hold flags that can be set by the VEE port and read by the application.

Usage overview
--------------

When the VEE port needs to report an incident, it will set *drawing log flags* in the graphics context describing its nature.
The application will then be able to read the flag values to know if an incident occurred.
This is meant to help the developer to debug the application if it does not display what is expected.
See :ref:`section.veeport.ui.drawings.drawing_logs` for more information on setting drawing log flags in the VEE port.

Incidents are split in two categories:

* *Warnings* are *non-critical* incidents that the application developer may ignore.
  When such an incident is reported, the flags are set in the graphics context so that the application can read them.
  However, if they are not explicitly read, the incident will be ignored silently.
* *Errors* are *critical* incidents that the application developer should not ignore when developing.
  As with warnings, *drawing log flags* will be set in the graphics context.
  Additionally, an exception will be thrown when the display is flushed so that the developer is aware of the incident.

Any incident may be either a warning or an error, depending on how the VEE port reported it.
The distinction is made through the value of the flag ``DRAWING_LOG_ERROR``.

Default behavior
----------------

When the VEE port reports an incident, it sets drawing log flags in the graphics context.
Additionally, if the incident was an error, it sets the special flag ``DRAWING_LOG_ERROR``.

Every time the display is flushed, the flags contained in its graphics context will be checked.
If the flag ``DRAWING_LOG_ERROR`` is set --- which means an error has been reported --- the ``flush`` function will throw a ``MicroUIException`` with the code ``DRAWING_ERROR``, and the values of the drawing log flags in its message.
Afterwards, the flags will be reset.

.. warning::

   This behavior can be disabled at build time.
   In this case, the flags will keep their values after the display is flushed, and no exception will be thrown.

   Therefore, the developer should **not** rely on the drawing log flags in the workflow of the application.
   They are meant to be used as a **debugging hint**.

If an exception is thrown, the application developer should use the flag values to find the cause of the error and fix it accordingly.

Explicit checks
---------------

MicroUI only checks the drawing log flags automatically during a display flush.
The developer may want to read the flag values between drawing operations to investigate the cause of an error.
Two functions are provided to do so:

* ``GraphicsContext.getAndClearDrawingLogFlags`` will return the current values of the flags and reset them.
* ``GraphicsContext.checkDrawingLogFlags`` behaves like ``GraphicsContext.getAndClearDrawingLogFlags``.
  However, it will also throw an exception if the flag ``DRAWING_LOG_ERROR`` is set, like is done when the display is flushed.

For example, if a VEE port that has no implementation to draw circles reports an error with the flag ``DRAWING_LOG_NOT_IMPLEMENTED``, the application would then behave as below.

.. code:: java

   // The VEE port has not implemented this function.
   Painter.drawCircle(gc, 1, 2, 3);

   // This throws a MicroUIException.
   Display.getDisplay().flush();

The application developer could force a check of the drawing log flags:

.. code:: java

   // The VEE port has not implemented this function.
   Painter.drawCircle(gc, 1, 2, 3);

   try {
      // This throws a MicroUIException.
      int flags = gc.checkDrawingLogFlags();
   } catch (MicroUIException e) {
      // This prints the value of DRAWING_ERROR (-13).
      System.out.println(e.getErrorCode());
   }

Or the developer could explicitly retrieve the value of the flags:

.. code:: java

   // The VEE port has not implemented this function.
   Painter.drawCircle(gc, 1, 2, 3);

   // This retrieves the values of drawing log flags.
   int flags = gc.getAndClearDrawingLogFlags();
   // This prints "80000001" (DRAWING_LOG_ERROR | DRAWING_LOG_NOT_IMPLEMENTED == 1 << 31 | 1 << 0).
   System.out.println(Integer.toHexString(flags));

Configuration
-------------

When releasing an application, the developer should disable the automatic check of drawing log flags performed when the display is flushed.
This will prevent exceptions from being thrown which would cause an unexpected crash.
It will also not clear the drawing log flags when the display is flushed.

This can be done by setting the :ref:`constant <section.classpath.elements.constants>` ``com.microej.library.microui.impl.check-drawing-errors-on-flush`` to ``false`` when building the application.
If it is not set, it defaults to ``true``.

Available constants
-------------------

MicroUI provides a set of constants to describe reported incidents.
They are defined and documented in the class ``GraphicsContext``.

.. list-table::
   :header-rows: 1
   :widths: 30 10 60

   * - Constant
     - Value
     - Description
   * - ``DRAWING_LOG_NOT_IMPLEMENTED``
     - ``1 << 0``
     - This function is not implemented.
   * - ``DRAWING_LOG_FORBIDDEN``
     - ``1 << 1``
     - This function must not be called in this situation.
   * - ``DRAWING_LOG_OUT_OF_MEMORY``
     - ``1 << 2``
     - The system ran out of memory.
   * - ``DRAWING_LOG_CLIP_MODIFIED``
     - ``1 << 3``
     - The VEE port modified clip values in the graphics context.
   * - ``DRAWING_LOG_LIBRARY_INCIDENT``
     - ``1 << 29``
     - An incident occurred in an underlying library.
   * - ``DRAWING_LOG_UNKNOWN_INCIDENT``
     - ``1 << 30``
     - An incident that does not match other flags occurred.
   * - ``DRAWING_LOG_ERROR``
     - ``1 << 31``
     - Special flag denoting critical incidents.

The special value ``DRAWING_SUCCESS`` (defined as ``0``) represents a state where no drawing log flags are set, so encountering this value means that no incident was reported.

New flag constants may be added in future versions of MicroUI.
Also, their actual values may change and the developer should not rely on them.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
