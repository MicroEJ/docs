.. _event-tracing:

Event Tracing
#############

Description
===========

Event Tracing allows to record integer based events for debugging and monitoring purposes without affecting execution performance too heavily.
Basically, it gives access to ``Tracer`` objects that are named and can produce a limited number of different event types.

A record is an event type identified by an ``eventID`` and can have a list of values.
It can be a single event or a period of time with a start and an end.

Event Tracing can be accessed from two APIs:
  
- A Java API, provided by the `Trace API module <https://repository.microej.com/modules/ej/api/trace/>`_.
  The following dependency must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ Application project:
      
  .. code:: xml
      
     <dependency org="ej.api" name="trace" rev="1.1.0"/>
  
- A C API, provided by the Platform header file named ``LLTRACE_impl.h``.

.. _event_enable_recording:

Event Recording
===============

Events are recorded if and only if:

- the MicroEJ Core Engine trace system is enabled,
- and trace recording is started.

To enable the MicroEJ Core Engine trace system, set the :ref:`Application Option <application_options>` named ``core.trace.enabled`` to ``true`` (see also :ref:`launch configuration <architecture_options_group_trace>`).

Then, multiple ways are available to start and stop the trace recording:
  
- by setting the :ref:`Application Option <application_options>` named ``core.trace.autostart`` to ``true`` to automatically start at startup (see also :ref:`launch configuration <architecture_options_group_trace>`),
- using the Java API methods ``ej.trace.Tracer.startTrace()`` and ``ej.trace.Tracer.stopTrace()``,
- using the C API functions ``LLTRACE_IMPL_start(void)`` and ``LLTRACE_IMPL_stop(void)``.

Java API Usage
==============

The detailed Trace API documentation is available `here <https://repository.microej.com/javadoc/microej_5.x/foundation/ej/trace/Tracer.html>`__.

First, you need to instantiate a ``Tracer`` object by calling its constructor with two parameters.
The first parameter, ``name``, is a String that will represent the ``Tracer`` object group's name.
The second parameter, ``nbEventTypes``, is an integer representing the maximum number of event types available for the group.

.. code-block:: java

   Tracer tracer = new Tracer("MyGroup", 10);

Then, you can record an event by calling the ``recordEvent(int eventId)`` method. 
The event ID needs to be in the range ``0`` to ``nbEventTypes-1`` with ``nbEventTypes`` the maximum number of event types set when initializing the ``Tracer`` object.
Methods named ``recordEvent(...)`` always needs the event ID as the first parameter and can have up to ten integer parameters as custom values for the event.

To record the end of an event, call the method ``recordEventEnd(int eventID)``. 
It will trace the duration of an event previously recorded with one of the ``recordEvent(int)`` methods.
The ``recordEventEnd(...)`` method can also have another integer parameter for a custom value for the event end. One can use it to trace the returned value of a method.

The Trace API also provides a String constant ``Tracer.TRACE_ENABLED_CONSTANT_PROPERTY`` representing the :ref:`Constant <section.classpath.elements.constants>` value of ``core.trace.enabled`` option.
This constant can be used to :ref:`remove at build time <if_constant_removal>` portions of code when the trace system is disabled. 
To do that, just surround tracer record calls with a if statement that checks the constant's state. 
When the constant is set to ``false``, the code inside the if statement will not be embedded with the application and thus will not impact the performances.

.. code-block:: java
  
  if(Constants.getBoolean(Tracer.TRACE_ENABLED_CONSTANT_PROPERTY)) {
    // This code is not embedded if TRACE_ENABLED_CONSTANT_PROPERTY is set to false.       
    tracer.recordEventEnd(0);
  }

Examples:

- Trace a single event:

  .. code-block:: java
      
    private static final Tracer tracer = new Tracer("Application", 100);

    public static void main(String[] args) {
      Tracer.startTrace();
      tracer.recordEvent(0);
    }

  Standard Output: 

  .. code-block:: xml

    VM START
    [TRACE] [1] Declare group "Application"
    [TRACE] [1] Event 0x0

- Trace a method with a start event showing the parameters of the method and an end event showing the result:
  
  .. code-block:: java

    private static final Tracer tracer = new Tracer("Application", 100);

    public static void main(String[] args) {
      Tracer.startTrace();
      int a = 14;
      int b = 54;
      add(a, b);
    }

    public static int add(int a, int b) {
      tracer.recordEvent(1, a, b);
      int result = a + b;
      tracer.recordEventEnd(1, result);
      return result;
    }

  Standard Output: 

  .. code-block:: xml

    VM START
    [TRACE] [1] Declare group "Application"
    [TRACE] [1] Event 0x1 (14 [0xE],54 [0x36])
    [TRACE] [1] Event End 0x1 (68 [0x44])

.. _trace_implementations:

Platform Implementation
=======================

By default, when enabled, the Trace API displays a message in the standard output for every ``recordEvent(...)`` and ``recordEventEnd(...)`` method calls. 

It does not print a timestamp when displaying the trace message because it can drastically affect execution performances.
It only prints the ID of the recorded event followed by the values given in parameters.

A Platform can connect its own implementation by overriding the functions defined in the ``LLTRACE_impl.h`` file.

MicroEJ provides an implementation that redirects the events to :ref:`systemview` tool, 
the real-time recording and visualization tool from `Segger <https://www.segger.com/>`_. It is perfect for a finer understanding of the runtime behavior by showing events sequence and duration.

A implementation example for the `NXP OM13098 development board <https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc54000-cortex-m4-/lpcxpresso54628-development-board:OM13098>`_ with SystemView support is available `here <https://developer.microej.com/packages/referenceimplementations/U3OER/2.0.1/OM13098-U3OER-fullPackaging-eval-2.0.1.zip>`__.
Please contact :ref:`our support team <get_support>` for more information about how to integrate this Platform module.
    
