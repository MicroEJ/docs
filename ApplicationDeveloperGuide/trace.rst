.. _apiTrace:

API Trace
#########

Description
===========

The Trace API allows users to record events for debugging and monitoring purposes.
It gives access to ``Tracer`` objects that are named and can produce a limited number of different event types.

A record is an event type identified by an ``eventID`` and can have a list of values.
It can be a single event or a period of time with a start and an end.

MicroEJ gives access to two Trace APIs:
  
  - A **Java API** that can be used to trace Java application. The Javadoc is available 
    `here <https://repository.microej.com/javadoc/microej_5.x/foundation/ej/trace/Tracer.html>`_.
    
    - To add the library to your project, add the following dependency line in your module.ivy file:
        
      .. code:: xml
        
        <dependency org=“ej.api” name=trace rev=“x.y.z”/>
  
  - A **C API** implemented in the file ``LLTRACE_impl.h``.
    This file is available in the ``platform-bsp`` project defined in the sources of the platform.

To activate the trace system on the platform, the property ``core.trace.enabled`` needs to be set to true.
  
  - Right click on the project and go to ``Run As > Run Configurations``,
  - In the tab ``Configuration``, select the category ``Runtime``,
  - Check the option ``Enable execution traces``.

Multiple ways are available to start and stop the trace system:
  
  - from the **Java API**, the methods ``Tracer.startTrace()`` and ``Tracer.stopTrace()``,
  
  - from the **C API**, the functions ``LLTRACE_IMPL_start(void)`` and ``LLTRACE_IMPL_stop(void)``,
  
  - from the **launcher configuration** of the application: 
    - Right click on the project and go to ``Run As > Run Configurations``,
    - In the tab ``Configuration``, select the Category ``Runtime``,
    - Check the option ``Start execution traces automatically``.

To record an event, use the method ``recordEvent(int eventId)``. The event ID needs to be in the range ``0 to nbEventTypes-1``.
The methods ``recordEvent(...)`` always needs the eventID as the first parameter and can have up to ten int parameters as custom values for the event.

To record the end of an event, use the method ``recordEventEnd(int eventID)``. It will trace the duration of an event previously recorded with one of the ``recordEvent(int)`` methods.
The ``recordEventEnd(...)`` method can also have another int parameter for a custom value for the event end. It can be used to trace the returned value of a method.

This library gives access to a String constant ``TRACE_ENABLED_CONSTANT_PROPERTY`` representing the :ref:`BON Constant <section.classpath.elements.constants>` ``core.trace.enabled``.

  - This **BON Constant** can be used to remove, at build time, portions of code when trace is disabled. To do that, just surround tracer record calls with a if statement that checks the state of the constant. When the constant is set to false, the code inside the if statement will not be embedded with the application and thus, will not impact the performances.

    .. code-block:: java
      
      if(Constants.getBoolean(Tracer.TRACE_ENABLED_CONSTANT_PROPERTY)) {
        // This code is not embedded if TRACE_ENABLED_CONSTANT_PROPERTY is set to false.       
        tracer.recordEventEnd(0);
      }

Implementation
==============

By default, the Trace API displays a message in the standard output for every ``recordEvent(...)`` and ``recordEventEnd(...)`` method calls. 

It does not print a timestamp when displaying the trace message because it can drastically impact the performances.
It only prints the ID of the recorded event followed by the values given in parameters.

The default implementation can be overridden by implementing the ``LLTRACE_impl.h`` file.

An implementation of this API mapped to **SEGGER SystemView** concepts is available.

  - This allows to visualize the different traces directly in **SEGGER SystemView**.

  - The **SystemView** module is added to the targetted platform and initialized in the main function of the platform.

  - Then a low-level API named ``LLTRACE_sysview.c`` implements the functions defined in ``LLTRACE_impl.h`` using the **SystemView** library.

Examples
========
- Trace a single event.

  .. code-block:: java
      
    private static final Tracer tracer = new Tracer("Application", 100);

    public static void main(String[] args) {
      Tracer.startTrace();
      tracer.recordEvent(0);
    }

  Ouput on serial port (standard ouput): 

  .. code-block:: xml

    VM START
    [TRACE] [1] Declare group "Application"
    [TRACE] [1] Event 0x0

- Trace a method with a start showing the parameters of the method and an end showing the result.
  
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

  Ouput on serial port (standard ouput): 

  .. code-block:: xml

    VM START
    [TRACE] [1] Declare group "Application"
    [TRACE] [1] Event 0x1 (14 [0xE],54 [0x36])
    [TRACE] [1] Event End 0x1 (68 [0x44])
