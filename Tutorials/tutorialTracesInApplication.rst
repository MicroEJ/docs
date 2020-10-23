Add logging to MicroEJ applications
===================================

This document explains how to add logging and tracing to MicroEJ applications and libraries with three different solutions. The aim is to help developers to report precise execution context for further debugging and monitoring.


Intended Audience
-----------------

This document's intended audience is engineers who are in charge of adding logs and traces to MicroEJ applications and libraries.

It should also be of interest to all developers looking for best practices when coming to log messages while keeping a low ROM footprint and good overall performances.


Introduction
------------

One straightforward way to add traces in an application is to use the Java basic print methods: ``System.out.println(...)``. 
However, this is not desirable when writing production-quality code, where one typically wants to adjust the log level and provide useful well-formed data and metadata.

Having logs and traces in an application, though, means more code is embedded and executed.
This can impact the overall performances of the application by using more CPU usage at runtime. It also increases the ROM footprint of the application.


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


This tutorial refactors the following code snippet to illustrate how to log traces with three different libraries:

.. code-block:: java

      public class Main {

         enum ApplicationState {
            INSTALLED, STARTED, STOPPED, UNINSTALLED
         }

         private static ApplicationState currentState;
         private static ApplicationState previousState;

         public static void main(String[] args) {
            currentState = ApplicationState.UNINSTALLED;
            switchState(ApplicationState.INSTALLED);
         }

         public static void switchState(ApplicationState newState) {
            previousState = currentState;
            currentState = newState;
         }
      }

The last section describes how to reduce the footprint when the logs are disabled.



Trace API (ej.api.trace)
------------------------

The Trace API provides a way of tracing user-defined events.
Its features and principles are described in the :ref:`Event Tracing <event-tracing>` section of the :ref:`Application Developer Guide <application-developer-guide>`.

Here is a short example of how to use this API to log the entry/exit of the method ``switchState()``:

#. Add the following dependency to the ``module.ivy``: ``<dependency org="ej.api" name="trace" rev="1.1.0"/>``

#. Start by initializing a ``Tracer`` object:

      .. code-block:: java

         private static final Tracer tracer = new Tracer("Application", 100);
      
      In this case, ``Application`` identifies a category of events that defines a maximum of ``100`` different event types.

#. Next, activate the trace system:

      .. code-block:: java

         public static void main(String[] args) {
            Tracer.startTrace();

            currentState = ApplicationState.UNINSTALLED;
            switchState(ApplicationState.INSTALLED);
         }

#. Use the methods ``Tracer.recordEvent(...)`` and ``Tracer.recordEventEnd(...)`` to record the entry/exit events in the method:

      .. code-block:: java

         private static final int EVENT_ID = 0;

         public static void switchState(ApplicationState newState) {
            tracer.recordEvent(EVENT_ID);

            previousState = currentState;
            currentState = newState;

            tracer.recordEventEnd(EVENT_ID);
         }
   
   The ``Tracer`` object records the entry/exit of method ``switchState`` with event ID ``0``.
   
This produces the following output:

      .. code-block::

         [TRACE: Application] Event 0x0()
         [TRACE: Application] Event End 0x0()





.. note::

   The default platform implementation of the Trace API prints the events in the console. MicroEJ provides another implementation that redirects the events to `SystemView <https://www.segger.com/products/development-tools/systemview/>`_, the real-time recording and visualization tool from `Segger <https://www.segger.com/>`_. It allows for a finer understanding of the runtime behavior by showing events sequence and duration. A platform reference implementation for the `NXP OM13098 development board <https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc54000-cortex-m4-/lpcxpresso54628-development-board:OM13098>`_ with SystemView support is available `here <https://developer.microej.com/packages/referenceimplementations/U3OER/2.0.1/OM13098-U3OER-fullPackaging-eval-2.0.1.zip>`_. Please contact MicroEJ Support for more information about how to integrate this Platform module.


Logging library (ej.library.eclasspath.logging)
-----------------------------------------------

The library ``ej.library.eclasspath.logging`` implements standard Java ``java.util.logging`` package and follows the same principles:

-  There is one instance of ``LogManager`` by application that manages the hierarchy of loggers.
-  Find or create ``Logger`` objects using the method ``Logger.getLogger(String ID)``. If a logger has already been created with the same name, this logger is returned, otherwise a new logger is created. 
-  Each ``Logger`` created with this method is registered in the ``LogManager`` and can be retrieved using its String ``ID``.
-  A minimum level can be set to a ``Logger`` so that only messages that have at least this level are logged. The standard levels are listed in the class ``java.util.logging.Level``.
-  The ``Logger`` API provides multiple methods for logging:
    -  ``log(...)`` methods that send a ``LogRecord`` to the registered ``Handler`` instances. The ``LogRecord`` object wraps the String message and the log level. 
    -  Log level-specific methods, like ``severe(String msg)``, that call the aforementioned ``log(...)`` method with the correct level.
-  The library defines a default implementation of type ``Handler``, called ``DefaultHandler``, that prints the message of the ``LogRecord`` on the standard error output stream. It also prints the stack trace of the ``Throwable`` associated with the ``LogRecord`` if there is one.

Let's see how to use it on our short snippet:

#. Add the following dependency to the ``module.ivy``: ``<dependency org="ej.library.eclasspath" name="logging" rev="1.1.0"/>``

#. Call the logging API to log some info text:

   .. code-block:: java
     
      public static void switchState(ApplicationState newState) {
         previousState = currentState;
         currentState = newState;

         Logger logger = Logger.getLogger(Main.class.getName());
         logger.log(Level.INFO, "The application state has changed from " + previousState.toString() + " to "
               + currentState.toString() + ".");
      }


This produces the following output: 

   .. code-block:: java
      
      main INFO: The application state has changed from UNINSTALLED to INSTALLED.


.. note::

   Unlike the two other libraries discussed here, the library ``ej.library.eclasspath.logging`` is entirely based on Strings (log IDs and messages). Note that String operations can lead to performance issues and that String objects use significant ROM space. When possible, favor a logging solution that uses primitive types over Strings.


Message library (ej.library.runtime.message)
--------------------------------------------

The library ``ej.library.runtime.message`` was designed to enable logging while minimizing RAM/ROM footprint and CPU usage. For doing so, it favors the use of integer over strings.

Principles:

- The ``MessageLogger`` type allows for logging messages solely based on integers that identify the message content.
- Log a message by using methods ``MessageLogger.log(...)`` specifying the log level, the message category, and the message integer identifier.
  Use optional arguments to add any useful information to the log, such as a ``Throwable`` or contextual data.
- Log levels are very similar to those of the Logging library. The class ``ej.util.message.Level`` lists the standard levels.
- Combined with the category, the integer ID allows the user to find the corresponding error/warning/info description.
- Loggers rely on the ``MessageBuilder`` type for message creation. 
  The messages constructed by the ``BasicMessageBuilder`` follow this pattern: ``[category]:[LEVEL]=[id]``. The builder appends the specified ``Object`` arguments (if any) separated by spaces, then the full stack trace of a ``Throwable`` (if any).
- As the ID of the message is an integer, making the output not very human-readable, it is wise to maintain documentation that describes all IDs.

Usage example:

#. To use this library, add this dependency line in the ``module.ivy``: ``<dependency org="ej.library.runtime" name="message" rev="2.1.0"/>``

#. Call the message API to log some info:
   
   .. code-block:: java 

      private static final String LOG_CATEGORY = "Application";

      private static final int LOG_ID = 2;

      public static void switchState(ApplicationState newState) {
         previousState = currentState;
         currentState = newState;

         BasicMessageLogger.INSTANCE.log(Level.INFO, LOG_CATEGORY, LOG_ID, previousState, currentState);
      }     

This produces the following output:

   .. code-block:: java
      
      Application:I=2 UNINSTALLED INSTALLED


Remove traces for the production binary
---------------------------------------

There are multiple options for removing all logs and traces when building the production binary.

Wrap logging statements with a check against a static variable
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

A boolean constant declared in an ``if`` statement can be used to fully remove portions of code: when this boolean constant is evaluated as ``false``, the wrapped code becomes unreachable and, thus, is not embedded.


.. note::
    More information about the usage of constants and ``if`` code removal can be found in the :ref:`Classpath <if_constant_removal>` section of the :ref:`Application Developer Guide <application-developer-guide>`.



#. Let's consider a constant ``com.mycompany.logging`` declared as ``false`` in a resource file named ``example.constants.list``.

    .. image:: images/tuto_microej_trace_constant.png
        :align: center


#. Add an ``if`` code removal statement to remove a logging, as follows:
   
   .. code-block:: java 

      private static final String LOG_PROPERTY = "com.mycompany.logging";

      public static void switchState(ApplicationState newState) {
         previousState = currentState;
         currentState = newState;

         if (Constants.getBoolean(LOG_PROPERTY)) {
            Logger logger = Logger.getLogger(Main.class.getName());
            logger.log(Level.INFO, "The application state has changed from " + previousState.toString() + " to "
               + currentState.toString() + ".");
         }
      }


When using the Trace API (``ej.api.trace``), you can evaluate the value of the static field ``Tracer.TRACE_ENABLED_CONSTANT_PROPERTY`` that represents the constant ``core.trace.enabled``.
The value of this constant can be modified by going to :guilabel:`Launch` > :guilabel:`Launch configurations` then in the tab :guilabel:`Configuration` > :guilabel:`Runtime`, check/uncheck the option :guilabel:`Enable execution traces` to respectively set the value to ``true``/``false``.

         .. image:: images/tuto_microej_trace_property.png
             :align: center

Follow the same principle as before:

      .. code-block:: java 

         private static final int EVENT_ID = 0;

         public static void switchState(ApplicationState newState) {
            if (Constants.getBoolean(Tracer.TRACE_ENABLED_CONSTANT_PROPERTY)) {
               tracer.recordEvent(EVENT_ID);
            }

            previousState = currentState;
            currentState = newState;

            if (Constants.getBoolean(Tracer.TRACE_ENABLED_CONSTANT_PROPERTY)) {
               tracer.recordEventEnd(EVENT_ID);
            }
         }

      

Use ProGuard
~~~~~~~~~~~~

`ProGuard <https://www.guardsquare.com/en/products/proguard>`_ is a command-line tool that shrinks, optimizes, and obfuscates Java code.

It optimizes bytecode as well as it detects and removes unused instructions. Therefore it can be used to remove log messages in a production binary.
   
`MicroEJ Github <https://github.com/MicroEJ/>`_ provides a dedicated How-To showing how to `get started with ProGuard <https://github.com/MicroEJ/How-To/tree/1.8.3/Proguard-Get-Started>`_ and remove elements of code from the Logging library (ej.library.eclasspath.logging).



Congratulations!

At this point in the tutorial:

* You can add logging to your MicroEJ applications while meeting the constraints of embedded applications.
* You can fully turn off logging in your production builds.
