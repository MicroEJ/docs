.. _apiTrace:

API Trace
#########

Description
===========
The API Trace allow users to trace events for debug and monitoring.
It gives access to a Tracer object that are named and can produce a limited number of difirent event types.

By default, this API show the traces using the default output stream.

The library contains one class: `ej.trace.Tracer`.

- This class gives access to the String constant ``TRACE_ENABLED_CONSTANT_PROPERTY`` representing the System property ``core.trace.enabled``.
- A Tracer object can be initialized using two properties:

   - A String representing the name of the Tracer,
   - An int for the maximum number of event types.

- The event IDs available for this group are ``from 0 to nbEventTypes-1``.
- If the Tracer cannot be created, the method will throw an ``InternalError``.
- By default, the trace system is stopped. To start it, use the static method ``startTrace()``.
- To stop the trace system, use the static method ``stopTrace()``.
- The static method ``isTraceStarted()`` can be used to test whether the trace system is started or not.
- To record an event, use the method ``recordEvent(int eventId)``. The event ID need to be in range ``0 to nbEventTypes-1``.
- The method ``recordEvent(...)`` always need the eventID as the first parameter and can have up to ten int parameters as custom value for the event.
- To stop the record of an event, use the method ``recordEventEnd(int eventID)``. It will trace the duration of an event previously recorded with one of the ``recordEvent(int)`` methods.
- The ``recordEventEnd(...)`` method can also have another int parameter for a custom value for the event end.

Import the library
==================
To add the library to your project, add the following dependency line in your module.ivy file:

   <dependency org=“ej.api” name=trace rev=“x.y.z”/>

Example
=======
.. code-block:: java

    Tracer tracer = new Tracer("Application", 100);
    Tracer.startTrace();

    tracer.recordEvent(0);
    //Do things
    tracer.recordEventEnd(0);
