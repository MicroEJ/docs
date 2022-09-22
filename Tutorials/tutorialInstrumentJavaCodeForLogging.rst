.. _tutorial_instrument_java_code_for_logging:

Instrument Java Code for Logging
================================

This document explains how to add logging and tracing to MicroEJ applications and libraries with three different solutions. The aim is to help developers to report precise execution context for further debugging and monitoring.


Intended Audience
-----------------

The audience for this document is application developers who are looking for ways to add logging to their MicroEJ applications and libraries.

It should also be of interest to Firmware engineers how are looking for adjusting the log level while keeping low memory footprint and good performances.


Introduction
------------

One straightforward way to add logs in Java code is to use the Java basic print methods: `System.out.println(...)`_. 

However, this is not desirable when writing production-grade code, where it should be possible to adjust the log level:

- without having to change the original source code,
- at build-time or at runtime, as application logging will affect memory footprint and performances

.. _System.out.println(...): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#out

Overview
--------

In this tutorial, we will describe 3 ways for logging data: 
   
- Using `Trace`_ library: a real-time event recording library designed for performance and interaction analysis.
- Using `Message`_ library: a lightweight and simple logging library.
- Using `Logging`_ library: a complete and highly configurable standard logging library. 

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

.. _Trace: https://repository.microej.com/modules/ej/api/trace
.. _Message: https://repository.microej.com/modules/ej/library/runtime/message/
.. _Logging: https://repository.microej.com/modules/ej/library/eclasspath/logging/

.. _log_trace_library:

Log with the Trace Library
--------------------------

The ``ej.api.trace`` `Trace`_ library provides a way of tracing integer events.
Its features and principles are described in the :ref:`event-tracing` section.

Here is a short example of how to use this library to log the entry/exit of the ``switchState()`` method:

#. Add the following dependency to the ``module.ivy``: 

   .. code-block:: xml

      <dependency org="ej.api" name="trace" rev="1.1.0"/>

#. Start by initializing a `Tracer`_ object:

   .. code-block:: java

      private static final Tracer tracer = new Tracer("Application", 100);
      
   In this case, ``Application`` identifies a category of events that defines a maximum of ``100`` different event types.

#. Next, start trace recording:

   .. code-block:: java
      :emphasize-lines: 2

      public static void main(String[] args) {
         Tracer.startTrace();

         currentState = ApplicationState.UNINSTALLED;
         switchState(ApplicationState.INSTALLED);
      }

#. Use the methods `Tracer.recordEvent(...)`_ and `Tracer.recordEventEnd(...)`_ to record the entry/exit events in the method:

   .. code-block:: java
      :emphasize-lines: 4,9

      private static final int EVENT_ID = 0;

      public static void switchState(ApplicationState newState) {
         tracer.recordEvent(EVENT_ID);

         previousState = currentState;
         currentState = newState;

         tracer.recordEventEnd(EVENT_ID);
      }
   
   The `Tracer`_ object records the entry/exit of method ``switchState`` with event ID ``0``.
   
#. Finally, to enable the MicroEJ Core Engine trace system, set the ``core.trace.enabled`` :ref:`option <application_options>` to ``true``. 
   This can be done from a :ref:`launch configuration <define_option_in_launcher>`: check :guilabel:`Runtime` > :guilabel:`Enable execution traces` option.

   .. image:: images/tuto_microej_trace_property.png
      :align: center

This produces the following output:

.. code-block::

   [TRACE: Application] Event 0x0()
   [TRACE: Application] Event End 0x0()

.. note::

   The default Platform implementation of the `Trace`_ library prints the events to the console.
   See :ref:`trace_implementations` for other available implementations such as :ref:`systemview` tool.

.. _Tracer: https://repository.microej.com/javadoc/microej_5.x/apis/ej/trace/Tracer.html
.. _Tracer.recordEvent(...): https://repository.microej.com/javadoc/microej_5.x/apis/ej/trace/Tracer.html#recordEvent-int-
.. _Tracer.recordEventEnd(...): https://repository.microej.com/javadoc/microej_5.x/apis/ej/trace/Tracer.html#recordEventEnd-int-

.. _log_message_library:

Log with the Message Library
----------------------------

The ``ej.library.runtime.message`` `Message`_ library was designed to enable logging while minimizing RAM/ROM footprint and CPU usage.
For that, logs are based on message identifiers, which are stored on integers instead of using of constant Strings.
In addition to a message identifier, the category of the message allows the user to find the corresponding error/warning/info description.
An external documentation must be maintained to describe all message identifiers and their expected arguments for each category.

Principles:

- The `MessageLogger`_ type allows for logging messages solely based on integers that identify the message content.
- Log a message by using methods `MessageLogger.log(...)`_ methods, by specifying the log level, the message category, and the message identifier.
  Use optional arguments to add any useful information to the log, such as a `Throwable`_ or contextual data.
- Log levels are very similar to those of the ``Logging`` library. The class `ej.util.message.Level`_ lists the available levels.
- Loggers rely on the `MessageBuilder`_ type for message creation. 
  The messages built by the `BasicMessageBuilder`_ follow this pattern: ``[category]:[LEVEL]=[id]``. 
  The builder appends the specified `Object`_ arguments (if any) separated by spaces, then the full stack trace of the `Throwable`_ argument (if any).

Here is a short example of how to use this library to log the entry/exit of the ``switchState()`` method:

#. To use this library, add this dependency line in the ``module.ivy``:

   .. code-block:: xml 
   
      <dependency org="ej.library.runtime" name="message" rev="2.1.0"/>

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

   .. code-block::
      
      Application:I=2 UNINSTALLED INSTALLED

.. _MessageLogger: https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/message/MessageLogger.html
.. _MessageLogger.log(...): https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/message/MessageLogger.html#log-char-java.lang.String-int-java.lang.Throwable-java.lang.Object...-
.. _Throwable: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Throwable.html
.. _ej.util.message.Level: https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/message/Level.html
.. _MessageBuilder: https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/message/MessageBuilder.html
.. _BasicMessageBuilder: https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/message/basic/BasicMessageBuilder.html
.. _Object: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html

.. _log_logging_library:

Log with the Logging Library
----------------------------

The ``ej.library.eclasspath.logging`` `Logging`_ library implements a subset of the standard Java `java.util.logging`_ package and follows the same principles:

- There is one instance of `LogManager`_ by application that manages the hierarchy of loggers.
- Find or create `Logger`_ objects using the method `Logger.getLogger(String)`_.
  If a logger has already been created with the same name, this logger is returned, otherwise a new logger is created. 
- Each `Logger`_ created with this method is registered in the ``LogManager`` and can be retrieved using its String ``ID``.
- A minimum level can be set to a `Logger`_ so that only messages that have at least this level are logged. The class `java.util.logging.Level`_ lists the available standard levels.
- The `Logger`_ API provides multiple methods for logging:

  - `log(...)`_ methods that send a `LogRecord`_ to the registered `Handler`_ instances. 
    The `LogRecord`_ object wraps the String message and the log level. 
  - Log level-specific methods, like `severe(String msg)`_, that call the aforementioned ``log(...)`` method with the correct level.

- The library defines a default `Handler`_ implementation, called `DefaultHandler`_,
  that prints the message of the `LogRecord`_ on the standard error output stream.
  It also prints the stack trace of the `Throwable`_ associated with the `LogRecord`_ if there is one.

Here is a short example of how to use this library to log the entry/exit of the ``switchState()`` method:

#. Add the following dependency to the ``module.ivy``: 

   .. code-block:: xml

      <dependency org="ej.library.eclasspath" name="logging" rev="1.1.0"/>

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

.. code-block::
      
   main INFO: The application state has changed from UNINSTALLED to INSTALLED.


.. note::

   Unlike the two other libraries discussed here, the `Logging`_ library is entirely based on Strings (log IDs and messages). 
   String operations can lead to performance issues and String objects use significant ROM space. 
   When possible, prefer using a logging solution that uses primitive types over Strings.

.. _java.util.logging: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/package-summary.html
.. _LogManager: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/LogManager.html
.. _Logger: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Logger.html
.. _Logger.getLogger(String): https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Logger.html#getLogger-java.lang.String-
.. _java.util.logging.Level: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Level.html
.. _log(...): https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Logger.html#log-java.util.logging.Level-java.lang.String-
.. _LogRecord: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/LogRecord.html
.. _Handler: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Handler.html
.. _severe(String msg): https://repository.microej.com/javadoc/microej_5.x/apis/java/util/logging/Logger.html#severe-java.lang.String-
.. _DefaultHandler: https://repository.microej.com/javadoc/microej_5.x/apis/ej/util/logging/handler/DefaultHandler.html


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
      :emphasize-lines: 7,11

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


When using the Trace API (``Trace``), you can use the `Tracer.TRACE_ENABLED_CONSTANT_PROPERTY`_ constant that represents the value of the ``core.trace.enabled`` :ref:`option <application_options>`.

Follow the same principle as before:

      .. code-block:: java
         :emphasize-lines: 4,11

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

      
.. _Tracer.TRACE_ENABLED_CONSTANT_PROPERTY: https://repository.microej.com/javadoc/microej_5.x/apis/ej/trace/Tracer.html#TRACE_ENABLED_CONSTANT_PROPERTY

Shrink Code Using ProGuard
~~~~~~~~~~~~~~~~~~~~~~~~~~

`ProGuard <https://www.guardsquare.com/en/products/proguard>`_ is a tool that shrinks, optimizes, and obfuscates Java code.

It optimizes bytecode as well as it detects and removes unused instructions. Therefore it can be used to remove log messages in a production binary.
   
A dedicated How-To is available at https://github.com/MicroEJ/How-To/tree/master/Proguard-Get-Started.
It describes how to configure ProGuard to remove elements of code from the `Logging`_ library.

..
   | Copyright 2021-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
