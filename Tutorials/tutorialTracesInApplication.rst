Add logging to MicroEJ applications
===================================

This tutorial explains how to add logging and tracing to MicroEJ applications and libraries.

Several solutions are presented that aim at helping developers report precise execution context for further debugging and monitoring.


Intended Audience
-----------------

The audience for this document is engineers who are in charge of adding logs and traces to MicroEJ applications and libraries.

In addition, this tutorial should be of interest to all developers looking for best practices when coming to log messages while keeping a low ROM footprint and good overall performances.


Introduction
------------

One straightforward way to add traces in an application is to use the Java base print functions: ``System.out.println(...)``. 
However this is not desirable when writing production quality code, where one typically wants to adjust the log level and provide useful, well-formed data and metadata.
This tutorial discusses the different options available to the MicroEJ developer.

Having logs and traces in an application, though, means more code is embedded and executed.
This can have an impact on the overall performances of the application by using more CPU usage at runtime. It also increases the ROM footprint of the application.
This tutorial also addresses this point. 



Prerequisites
-------------

*  `MicroEJ SDK <https://developer.microej.com/get-started/>`_ ``4.1.5`` or higher.
*  Java Development Kit (JDK) ``1.8.x``.



Overview
--------

In the MicroEJ environment, there are three ways for logging in an application: 
   
   - Trace API
   - Logging library
   - Messages library


This tutorial will show how to log traces using these three different libraries on the following code snippet:

.. code-block:: java

      public class Main {

         enum ApplicationState {
            INSTALLED, STARTED, STOPPED, UNINSTALLED
         }

         private static ApplicationState currentState;
         private static ApplicationState oldState;

         public static void main(String[] args) {
            currentState = ApplicationState.UNINSTALLED;
            switchState(ApplicationState.INSTALLED);
         }

         public static void switchState(ApplicationState newState) {
            oldState = currentState;
            currentState = newState;
         }
      }

Finally, the last section will describe how to remove the logs from the code.



Trace API (ej.api.trace)
------------------------

The Trace API provides a way of tracing user-defined events.
Its features and principles are described in the :ref:`Event Tracing <event-tracing>` section of the :ref:`Application Developer Guide <application-developer-guide>`.

Here we'll show a short example on how to use this API to log the entry/exit of the method ``switchState()``:

#. Add the following dependency to your ``module.ivy``: ``<dependency org="ej.api" name="trace" rev="x.y.z"/>``

#. Start by initializing a ``Tracer`` object:

      .. code-block:: java

         private static final Tracer tracer = new Tracer("Application", 100);
      
      In this case, ``Application`` identifies a group of events that defines a maximum of ``100`` available event types.

#. Next, activate the trace system:

      .. code-block:: java

         public static void main(String[] args) {
            Tracer.startTrace();

            currentState = ApplicationState.UNINSTALLED;
            switchState(ApplicationState.INSTALLED);
         }

#. Use the methods Tracer.recordEvent(...) and Tracer.recordEventEnd(...) to record the entry/exit events in the method:

      .. code-block:: java

         public static void switchState(ApplicationState newState) {
            tracer.recordEvent(0);

            oldState = currentState;
            currentState = newState;

            tracer.recordEventEnd(0);
         }
   
   The ``Tracer`` object records the entry/exit of method ``switchState`` with event ID ``0``.
   
This will produce the following output:

      .. code-block::

         [TRACE: Application] Event 0x0()
         [TRACE: Application] Event End 0x0()





.. note::

   The default platform implementation of the Trace API prints the events in the console. MicroEJ provides an other implementation that redirects the events to `SystemView <https://www.segger.com/products/development-tools/systemview/>`_, the real-time recording and visualization tool from `Segger <https://www.segger.com/>`_. It allows for a finer understanding of the runtime behavior by showing events sequencing and duration. A platform reference implementation for the `NXP OM13098 development board <https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc54000-cortex-m4-/lpcxpresso54628-development-board:OM13098>`_ with SystemView support is available `here <https://developer.microej.com/packages/referenceimplementations/U3OER/2.0.1/OM13098-U3OER-fullPackaging-eval-2.0.1.zip>`_. Please contact MicroEJ Support for more information about how to integrate this Platform module.


Logging library (ej.library.eclasspath.logging)
-----------------------------------------------

Library ``ej.library.eclasspath.logging`` is based over the ``java.util.logging`` library and follows the same principles:

-  There is one instance of ``LogManager`` by application that manages the hierarchy of loggers.
-  Find or create ``Logger`` objects using the method ``Logger.getLogger(String ID)``. If a logger has already been created with the same name, this logger is returned, otherwise a new logger is created. 
-  Each ``Logger`` created with this method is registered in the ``LoggerManager`` and can be retrieved using its String ``ID``.
-  You can associate a minimum level to this ``Logger`` so that only messages that have at least this level are logged. The standard levels are listed in the class ``java.util.logging.Level``.
-  The ``Logger`` API provides multiple methods for logging:
    -  ``log(...)`` methods, that send a ``LogRecord`` with the level argument to the registered ``Handler`` instances.
    -  Log level-specific methods, like ``severe(String msg)``, that call the aforementioned ``log(...)`` method with correct level argument.
-  The library defines a default implementation of type ``Handler``, called ``DefaultHandler``, that prints the message of the ``LogRecord`` on the standard error output stream. It also prints the stack trace of the ``Throwable`` associated to the ``LogRecord`` if there is one.

Let's see how to use it on our short snippet:

#. Add the following dependency your ``module.ivy``: ``<dependency org="ej.library.eclasspath" name="logging" rev="x.y.z"/>``

#. Call the logging API to log some info text:

   .. code-block:: java
     
      public static void switchState(ApplicationState newState) {
         oldState = currentState;
         currentState = newState;

         Logger logger = Logger.getLogger(Main.class.getName());
         logger.log(Level.INFO, "The application state has changed from " + oldState.toString() + " to "
               + currentState.toString() + ".");
      }


This will produce the following output: 

   .. code-block:: java
      
      main INFO: The application state has changed from UNINSTALLED to INSTALLED.


Message library (ej.library.runtime.message)
--------------------------------------------

Library ``ej.library.runtime.message`` was designed to enable logging while minimizing RAM/ROM footprint and CPU usage. For doing so, it favors the use of integer over strings.

Principles:

- The ``MessageLogger`` type allows for logging messages solely based on integers that identify the message content.
- Log a message by using methods ``MessageLogger.log(...)``, specifying the log level, the message category and message integer identifer.
  Use optional arguments to add any useful information to your log such as a throwable or contextual data.
- Log levels are very similar to those of the Logging library. You will find the full level definition in type ``ej.util.message.Level``.
- Combined with the category, the integer ID will allow the user to find the corresponding error/warning/info description.
- Loggers rely on the ``MessageBuilder`` type for message creation. 
  The messages constructed by the ``BasicMessageBuilder`` follow this pattern: `[category]:[LEVEL]=[id]`. The builder will append specified ``Object`` arguments (if any) separated by spaces, then the full stack trace of a throwable (if any).
- As the ID of the message is an integer, making the output not very human-readable, it is wise to maintain a documentation that describes all message IDs.

Usage example:

#. To use this library, add this dependency line in the project module.ivy:

   ``<dependency org="ej.library.runtime" name="message" rev="x.y.z"/>``

#. Call the message API to log some info:
   
   .. code-block:: java 

      public static void switchState(ApplicationState newState) {
         oldState = currentState;
         currentState = newState;

         BasicMessageLogger.INSTANCE.log(Level.INFO, "Application", 2, oldState, currentState);
      }     

This will produce the following output:

   .. code-block:: java
      
      Application:I=2 UNINSTALLED INSTALLED


Remove traces for the production binary
---------------------------------------

There are multiple options for removing all logs and traces when building the production binary.

Wrap logging statements with a check against a static variable
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

A boolean constant declared in a ``if`` statement can be used to fully remove portions of code: when this boolean constant is evaluated as ``false``, the wrapped code becomes unreachable and, thus, will not be embedded.


.. note::
    You can find more information about the usage of constants and ``if`` code removal in the :ref:`Classpath <if_constant_removal>` section of the :ref:`Application Developer Guide <application-developer-guide>`.



#. Let's consider a constant ``com.mycompany.logging`` that we declared as ``false`` in a resource file named ``example.constants.list``.

    .. image:: images/tuto_microej_trace_constant.png
        :align: center


#. Add an ``if`` code removal statement to remove a logging, as follows:
   
   .. code-block:: java 

      public static void switchState(ApplicationState newState) {
         oldState = currentState;
         currentState = newState;

         if(Constants.getBoolean("com.mycompany.logging")) {
            BasicMessageLogger.INSTANCE.log(Level.INFO, "Application", 2, oldState, currentState);
         }
      }


When using the Trace API (ej.api.trace), you can evaluate the value of constant ``Tracer.TRACE_ENABLED_CONSTANT_PROPERTY`` that represents property ``core.trace.enabled``.
The value of this property can be modified by going to :guilabel:`Launch` > :guilabel:`Launch configurations` then in the tab :guilabel:`Configuration` > :guilabel:`Runtime`, you can check/uncheck the option :guilabel:`Enable execution traces` to respectively set the value to ``true``/``false``.

         .. image:: images/tuto_microej_trace_property.png
             :align: center

Follow same principle as before:

      .. code-block:: java 

         public static void switchState(ApplicationState newState) {
            if(Constants.getBoolean(Tracer.TRACE_ENABLED_CONSTANT_PROPERTY)) {
               tracer.recordEvent(0);
            }

            oldState = currentState;
            currentState = newState;

            if(Constants.getBoolean(Tracer.TRACE_ENABLED_CONSTANT_PROPERTY)) {
               tracer.recordEventEnd(0);
            }
         }

      

Use ProGuard
~~~~~~~~~~~~

`ProGuard <https://www.guardsquare.com/en/products/proguard>`_ is a command-line tool that shrinks, optimizes and obfuscates Java code.

It will optimize bytecode as well as detect and remove unused instructions. Therefore it can be used to remove log messages in a production binary.
   
`MicroEJ Github <https://github.com/MicroEJ/>`_ provides a dedicated How-To showing how to `get started with ProGuard <https://github.com/MicroEJ/How-To/tree/1.8.3/Proguard-Get-Started>`_ and remove elements of code from the Logging library (ej.library.eclasspath.logging).



Congratulations!

At this point of the tutorial:

* You can add logging to your MicroEJ applications while meeting the constraints of embedded applications
* You can fully turn off logging in your production builds.
