.. _apiTrace:

API Trace
#########

--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- 

- Describe what is a record:
   
   - event type (identified by an eventId) + a list of values
   - a record can be:
      
      - a single event (no end)
      - a period of time with a start and an end

- Describe that we have a Java API (link to Javadoc + ivy dependency) and a C API 
  (C header file name)
- Describe what is a Tracer: identified by a name, has a limited number of event types
- Describe how to start/stop the trace system: with the Java API, with the C API, with 
  the launcher option ; how to activate the trace system (launcher).
- Describe how it is implemented:
   
   - Default implementation that displays a message in the standard output for 
     every record (does it print a timestamp?).
   - Implementation can be overridden by implementing the LLXXX_impl.h file
   - There is an implementation that uses SystemView and explain in this implementation 
     how the Trace concepts (Tracer, record, etc.) are mapped into SystemView concepts.

- Describe some usage examples:
   
   - Trace a single event
   - Trace a method execution with a start that traces the parameters, an end that traces 
     the result and explain that we can so trace the execution time of the function.

--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- 

Description
===========

- The Trace API allows users to record events for debugging and monitoring purposes.
  It gives access to ``Tracer`` objects that are named and can produce a limited number of different event types.

- A record is an event type identified by an eventID and can have a list of values.
- It can be a single event or a period of time with a start and an end.

- MicroEJ gives access to two Trace APIs:
  
  - A Java API that can be used to trace Java application. The Javadoc is available 
    `here <https://repository.microej.com/javadoc/microej_5.x/foundation/ej/trace/Tracer.html>`_.
    
    To add the library to your project, add the following dependency line in your module.ivy file:
      
      .. code:: xml
        
        <dependency org=“ej.api” name=trace rev=“x.y.z”/>
  
  - A C API implemented in the file ``LLTRACE_impl.h``.

- Multiple ways are available to start and stop the trace system:
  
  - from the **Java API**, the methods ``Tracer.startTrace()`` and ``Tracer.stopTrace()``,
  
  - from the **C API**, the methods ``LLTRACE_IMPL_start(void)`` and ``LLTRACE_IMPL_stop(void)``,
  
  - from the **launcher** of the application. 
    You can access this option by right clicking on the project and going to ``Run As > Run Configurations`` then in the tab ``Configuration``.
    Select the Category ``Runtime`` and check the option ``Enable execution traces``.

Implementation
==============

- By default, the Trace API displays a message in the standard output for every record.
- The default API implementation does not print a timestamp when displaying the trace message. 
- This default implementation can be overridden by implementing the ``LLTRACE_impl.h`` file.

Examples
========
- Trace a single event.

  .. code-block:: java
      
    private static final Tracer tracer = new Tracer("Application", 100);

    public static void main(String[] args) {
      Tracer.startTrace();
      tracer.recordEvent(0);
    }

  - Ouput on serial port (standard ouput): 

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

  - Ouput on serial port (standard ouput): 

  .. code-block:: xml

    VM START
    [TRACE] [1] Declare group "Application"
    [TRACE] [1] Event 0x1 (14 [0xE],54 [0x36])
    [TRACE] [1] Event End 0x1 (68 [0x44])

  - When using a serial port reader that can display the timestamp at each print, you can compute the execution time of the traced function.
