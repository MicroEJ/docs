.. _apiTrace:

API Trace
#########

Description
===========

- The Trace API allows users to record events for debugging and monitoring purposes.
  It gives access to ``Tracer`` objects that are named and can produce a limited number of different event types.

- A record is an event type identified by an ``eventID`` and can have a list of values.
- It can be a single event or a period of time with a start and an end.

- MicroEJ gives access to two Trace APIs:
  
  - A **Java API** that can be used to trace Java application. The Javadoc is available 
    `here <https://repository.microej.com/javadoc/microej_5.x/foundation/ej/trace/Tracer.html>`_.
    
    To add the library to your project, add the following dependency line in your module.ivy file:
      
      .. code:: xml
        
        <dependency org=“ej.api” name=trace rev=“x.y.z”/>
  
  - A **C API** implemented in the file ``LLTRACE_impl.h``.
    This file is available in the ``platform-bsp`` project of the sources of the platform.

- To activate the trace system on the platform, the property ``core.trace.enabled`` need to be set to true.
  It can be done by right clicking on the project and going to ``Run As > Run Configurations`` then in the tab ``Configuration``.
  Select the Category ``Runtime`` and check the option ``Enable execution traces``.

- Multiple ways are available to start and stop the trace system:
  
  - from the **Java API**, the methods ``Tracer.startTrace()`` and ``Tracer.stopTrace()``,
  
  - from the **C API**, the methods ``LLTRACE_IMPL_start(void)`` and ``LLTRACE_IMPL_stop(void)``,
  
  - from the **launcher configuration** of the application. 
    This option can be accessed by right clicking on the project and going to ``Run As > Run Configurations`` then in the tab ``Configuration``.
    Select the Category ``Runtime`` and check the option ``Start execution traces automatically``.

Implementation
==============

- By default, the Trace API displays a message in the standard output for every ``recordEvent(...)`` and ``recordEventEnd(...)`` method calls. 

- It does not print a timestamp when displaying the trace message, it only print the ID of the recorded event followed by the value given in parameters.

- The default implementation can be overridden by implementing the ``LLTRACE_impl.h`` file.

- An implementation of this API is mapped to **SEGGER SystemView** concepts.

  - 

  - This allow to visualize the different trace directly in **SEGGER SystemView**.

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
