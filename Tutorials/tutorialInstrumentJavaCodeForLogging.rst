Instrument Java Code for Logging
================================

This document explains how to add logging and tracing to MicroEJ applications and libraries with three different solutions. The aim is to help developers to report precise execution context for further debugging and monitoring.


Intended Audience
-----------------

The audience for this document is application developers who are looking for ways to add logging to their MicroEJ applications and libraries.

It should also be of interest to Firmware engineers how are looking for adjusting the log level while keeping low memory footprint and good performances.


Introduction
------------

One straightforward way to add logs in Java code is to use the Java basic print methods: ``System.out.println(...)``. 
However, this is not desirable when writing production-grade code, where it should be possible to adjust the log level:

- without having to change the original source code,
- at build-time or at runtime, as application logging will affect memory footprint and performances

Overview
--------

In this tutorial, we will describe 3 ways for logging data: 
   
- Using `Trace <https://repository.microej.com/artifacts/ej/api/trace>`_ library, a real-time event recording library designed for performance and interaction analysis.
- Using `Message <https://repository.microej.com/artifacts/ej/library/runtime/message/>`_ library: a lightweight and simple logging library.
- Using `Logging <https://repository.microej.com/artifacts/ej/library/eclasspath/logging/>`_ library: a complete and highly configurable standard logging library. 

Through this tutorial, we will illustrate the usage of each library by instrumenting the following code snippet:

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

Finally, the last section describes some techniques to remove logging related code in order to reduce the memory footprint.

Log with the Trace Library
--------------------------

The library `ej.api.trace <https://repository.microej.com/artifacts/ej/api/trace>`_ provides a way of tracing integer events.
Its features and principles are described in the :ref:`event-tracing` section.

Here is a short example of how to use this library to log the entry/exit of the ``switchState()`` method:

#. Add the following dependency to the ``module.ivy``: ``<dependency org="ej.api" name="trace" rev="1.1.0"/>``

#. Start by initializing a `Tracer <https://repository.microej.com/javadoc/microej_5.x/apis/ej/trace/Tracer.html>`_ object:

      .. code-block:: java

         private static final Tracer tracer = new Tracer("Application", 100);
      
      In this case, ``Application`` identifies a category of events that defines a maximum of ``100`` different event types.

#. Next, activate the trace system:

      .. code-block:: java
         :emphasize-lines: 2

         public static void main(String[] args) {
            Tracer.startTrace();

            currentState = ApplicationState.UNINSTALLED;
            switchState(ApplicationState.INSTALLED);
         }

#. Use the methods ``Tracer.recordEvent(...)`` and ``Tracer.recordEventEnd(...)`` to record the entry/exit events in the method:

      .. code-block:: java
         :emphasize-lines: 4,9

         private static final int EVENT_ID = 0;

         public static void switchState(ApplicationState newState) {
            tracer.recordEvent(EVENT_ID);

            previousState = currentState;
            currentState = newState;

            tracer.recordEventEnd(EVENT_ID);
         }
   
   The `Tracer <https://repository.microej.com/javadoc/microej_5.x/apis/ej/trace/Tracer.html>`_ object records the entry/exit of method ``switchState`` with event ID ``0``.
   
This produces the following output:

      .. code-block::

         [TRACE: Application] Event 0x0()
         [TRACE: Application] Event End 0x0()

.. note::

   The default Platform implementation of the ``Trace`` library prints the events to the console.
   See :ref:`trace_implementations` for other available implementations such as `SEGGER SystemView <https://www.segger.com/products/development-tools/systemview/>`_ tool.
   
Log with the Message Library
----------------------------


The library `ej.library.runtime.message <https://repository.microej.com/artifacts/ej/library/runtime/message/>`_ was designed to enable logging while minimizing RAM/ROM footprint and CPU usage.
For that, logs are based on message identifiers, which are stored on integers instead of using of constant Strings.
An external documentation must be maintained to describe each message identifier and its expected arguments.
Combined with the category, the printed message identifier value allows the user to find the corresponding error/warning/info description.

Principles:

- The `MessageLogger <https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/message/MessageLogger.html>`_ type allows for logging messages solely based on integers that identify the message content.
- Log a message by using methods ``MessageLogger.log(...)`` methods, by specifying the log level, the message category, and the message identifier.
  Use optional arguments to add any useful information to the log, such as a `Throwable <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Throwable.html>`_ or contextual data.
- Log levels are very similar to those of the ``Logging`` library. The class `ej.util.message.Level <https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/message/Level.html>`_ lists the available levels.
- Loggers rely on the `MessageBuilder <https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/message/MessageBuilder.html>`_ type for message creation. 
  The messages built by the `BasicMessageBuilder <https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/message/basic/BasicMessageBuilder.html>`_ follow this pattern: ``[category]:[LEVEL]=[id]``. 
  The builder appends the specified `Object <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html>`_ arguments (if any) separated by spaces, then the full stack trace of the `Throwable <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Throwable.html>`_ argument (if any).

Here is a short example of how to use this library to log the entry/exit of the ``switchState()`` method:

#. To use this library, add this dependency line in the ``module.ivy``: ``<dependency org="ej.library.runtime" name="message" rev="2.1.0"/>``

#. Call the message API to log some info:
   
   .. code-block:: java 
      :emphasize-lines: 9

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


Log with the Logging Library
----------------------------

The library `ej.library.eclasspath.logging <https://repository.microej.com/artifacts/ej/library/eclasspath/logging/>`_ implements a subset of the standard Java `java.util.logging <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/package-summary.html>`_ package and follows the same principles:

-  There is one instance of `LogManager <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/LogManager.html>`_ by application that manages the hierarchy of loggers.
-  Find or create `Logger <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Logger.html>`_ objects using the method `Logger.getLogger(String) <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Logger.html#getLogger-java.lang.String->`_.
   If a logger has already been created with the same name, this logger is returned, otherwise a new logger is created. 
-  Each `Logger <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Logger.html>`_ created with this method is registered in the ``LogManager`` and can be retrieved using its String ``ID``.
-  A minimum level can be set to a `Logger <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Logger.html>`_ so that only messages that have at least this level are logged. The class `java.util.logging.Level <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Level.html>`_ lists the available standard levels.
-  The ``Logger`` API provides multiple methods for logging:
    
    -  ``log(...)`` methods that send a `LogRecord <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/LogRecord.html>`_ to the registered `Handler <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Handler.html>`_ instances. 
       The `LogRecord <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/LogRecord.html>`_ object wraps the String message and the log level. 
    -  Log level-specific methods, like ``severe(String msg)``, that call the aforementioned ``log(...)`` method with the correct level.

-  The library defines a default `Handler <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Handler.html>`_ implementation, called `DefaultHandler <https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/logging/handler/DefaultHandler.html>`_,
   that prints the message of the `LogRecord <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/LogRecord.html>`_ on the standard error output stream.
   It also prints the stack trace of the `Throwable <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Throwable.html>`_ associated with the `LogRecord <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/LogRecord.html>`_ if there is one.

Here is a short example of how to use this library to log the entry/exit of the ``switchState()`` method:

#. Add the following dependency to the ``module.ivy``: ``<dependency org="ej.library.eclasspath" name="logging" rev="1.1.0"/>``

#. Call the logging API to log some info text:

   .. code-block:: java
      :emphasize-lines: 5,6,7
     
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

   Unlike the two other libraries discussed here, the ``Logging`` library is entirely based on Strings (log IDs and messages). 
   Note that String operations can lead to performance issues and that String objects use significant ROM space. 
   When possible, prefer using a logging solution that uses primitive types over Strings.


Remove Logging Related Code
---------------------------

This section describes some techniques to remove logging related code, which saves memory footprint when logging is disabled at runtime.
This is typically useful when building two Firmware flavors: one for production and one for debug.

Wrap with a Constant If Statement
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A boolean :ref:`constant <section.classpath.elements.constants>` declared in an ``if`` statement can be used to fully remove portions of code. 
When this boolean constant is detected to be ``false``, the wrapped code becomes unreachable and is not embedded.

.. note::
    More information about the usage of constants and ``if`` code removal can be found in the :ref:`Classpath <if_constant_removal>` section.


#. Let's consider a constant ``com.mycompany.logging`` declared as ``false`` in a resource file named ``example.constants.list``.

    .. image:: images/tuto_microej_trace_constant.png
        :align: center


#. Wrap the log code by an ``if`` statement, as follows:
   
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

      

Shrink Code Using ProGuard
~~~~~~~~~~~~~~~~~~~~~~~~~~

`ProGuard <https://www.guardsquare.com/en/products/proguard>`_ is a tool that shrinks, optimizes, and obfuscates Java code.

It optimizes bytecode as well as it detects and removes unused instructions. Therefore it can be used to remove log messages in a production binary.
   
A dedicated How-To is available at https://github.com/MicroEJ/How-To/tree/master/Proguard-Get-Started.
It describes how to configure ProGuard to remove elements of code from the `Logging <https://repository.microej.com/artifacts/ej/library/eclasspath/logging/>`_ library.

