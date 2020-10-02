Application Trace
=================

The easiest way to add traces in an application is to use the Java base
print functions: ``System.out.println(...)``. But, it is not very
flexible when going into production while still wanting to maintain a
proper level of log for debug purposes.

Even though logging allows easier debugging and tracing of an
application, it also means more code is embedded and executed. It may
have an impact on the performances by having more CPU usage at runtime
and a bigger ROM footprint for the log messages. When measuring
performance of an application, be sure to remove or disable all traces
so it has no impact on the performances.

In the MicroEJ environment, two ways are posible for application logging: 
   
   - event based tracing using integer events,
   
   - textual tracing for more complex data.

This tutorial will show how to log traces of the following code snippet using three different libraries:

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

Event based tracing
-------------------

Api Trace
~~~~~~~~~
The API Trace is a Java library based over a low-level api that allow users 
to record events using named Tracer and a limited number of integer events.

- To use this library in your project add the following dependency line in your module.ivy: 

   ``<dependency org=“ej.api” name="trace" rev=“x.y.z”/>``

- More informations about the API are available on the MicroEJ documentation website, 
  in the :ref:`API Trace section <apiTrace>`.

- To use this API:

   - Start by initializing a ``Tracer`` object.

      .. code-block:: java

         private static final Tracer tracer = new Tracer("Application", 100);
      
      - In this case, out ``Tracer`` will be named ``Application`` and will be limited to 100 different event types.

   - Now activate the trace system.

      .. code-block:: java

         public static void main(String[] args) {
            Tracer.startTrace();

            currentState = ApplicationState.UNINSTALLED;
            switchState(ApplicationState.INSTALLED);
         }

   - Once initialized, you can use the methods Tracer.recordEvent(...) and Tracer.recordEventEnd(...) to record the elements of your choice.

      .. code-block:: java

         public static void switchState(ApplicationState newState) {
            tracer.recordEvent(0);

            oldState = currentState;
            currentState = newState;

            tracer.recordEventEnd(0);
         }
   
   - The logging output will be, directly printed in the console: 

      .. code-block::

         [TRACE: Application] Event 0x0()
         [TRACE: Application] Event End 0x0()

- The output can be redirected to any standard output and be used by third party like, for example, Segger's SystemView.

- A MicroEJ demo platform of the ``NXP OM13098`` board containing the SystemView support is available and downloadable 
  by `clicking here <https://developer.microej.com/packages/referenceimplementations/U3OER/2.0.1/OM13098-U3OER-fullPackaging-eval-2.0.1.zip>`_.

Textual tracing
---------------

In the MicroEJ SDK resources, two libraries allow the users to do textual tracing.

-  ``ej.library.eclasspath.logging``. It is based over the
   ``java.util.logging`` library and follows the same principles of
   LogManagers, Loggers, LogRecords and Handlers.

-  ``ej.library.runtime.message``. This library is based on a
   MessageBuilder and a MessageLogger.

Both libraries have the possibility to associate a level to the Logger
to allow only certain levels of messages to be logged.

ej.library.eclasspath.logging library
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To use this library, add the following dependency line in the project’s
module.ivy:

   ``<dependency org=“ej.library.eclasspath” name=“logging” rev=“x.y.z”/>``

-  In every application that uses this library, there is only one
   instance of a ``LogManager`` object.

-  Load or create a ``Logger`` object using the method
   ``Logger.getLogger(String ID)``.

-  Each ``Logger`` created with this method is saved in the
   ``LoggerManager`` and, if already created before, will be retrieved
   using their ID of type String.

-  Once created, it is possible to associate a minimum level to this
   ``Logger`` so that only messages that have at least this level are
   logged. The standard levels are listed in the class
   ``java.util.logging.Level``.

-  To send a request to log something, there are two possibilities.

   -  The first is to use the method ``myLogger.log(...)``. This method
      will send a ``LogRecord`` to the registered ``Handler`` instances
      to be logged.
   
   -  The second is to use the log level-specific methods. For example
      ``myLogger.severe(String msg)`` will create a ``LogRecord`` with
      the level ``Level.SEVERE`` and send it to the registered
      ``Handler`` instances.

-  The library defines a default implementation of type ``Handler``,
   called ``DefaultHandler``, that prints the message of the
   ``LogRecord`` on the standard error output stream. It also prints the
   stack trace of the ``Throwable`` associated to the ``LogRecord`` if
   there is one.

- Example:

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

            Logger logger = Logger.getLogger("ApplicationLogger");
            logger.log(Level.INFO, "The application state has changed from " + oldState.toString() + " to "
                  + currentState.toString() + ".");
         }
      }

   - The logging output will be, directly printed in the console: 

   .. code-block:: java
      
      applicationlogger INFO: The application state has changed from UNINSTALLED to INSTALLED.

ej.library.runtime.message library
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To use this library, add this dependency line in the project module.ivy:

   ``<dependency org=“ej.library.runtime” name=“message” rev=“x.y.z”/>``

-  A ``BasicMessageBuilder`` is implemented in the library. The messages
   that is built follows this format: >
   *Category*:*LevelCharacter*\ =\ *MessageIntID* argument1 argument2 …
   > Exception in thread “thread” *java.lang.Throwable*:
   *ThrowableMessage*

-  As the ID of the message is an integer, it is wise to maintain a
   documentation that describes all message IDs.

-  To log a message, instantiate a new ``MessageLogger`` object or use
   the INSTANCE constants in the base ``MessageLogger`` classes defined
   in the library (``BasicMessageLogger`` and ``FilterMessageLogger``).

-  Then, use the method ``MessageLogger.log(...)``. This log method
   needs at least three parameters:

   -  char level, the character corresponding to the level of the
      message to log. Standard levels are listed in the class
      ``ej.util.message.Level``.
   
   -  String category, the category of the message.
   
   -  int id, that represents the message. Combined with the category,
      it will allow the user to find the corresponding error
      description.

-  In addition to those parameters, a throwable can be added and / or a
   list of Objects. The list of Objects will be added to the logged
   message as the argument seen in the ``BasicMessageBuilder`` message
   composition seen above. The throwable will make the System throw an
   exception after logging the message.

-  The library ``ej.library.runtime.message`` takes less space than
   ``ej.library.eclasspath.logging`` when embedded and has a lower RAM /
   CPU consumption at runtime.

- Example 
   
   .. code-block:: java 

      public class Main {

         private static final String category = "Application";
         private static final int logID = 2;

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

            BasicMessageLogger.INSTANCE.log(Level.INFO, category, logID, oldState, currentState);
         }     
      }

   - The logging output will be, directly printed in the console: 

   .. code-block:: java
      
      Application:I=2 UNINSTALLED INSTALLED

Remove traces for the production binary
---------------------------------------
There is multiple possibilities to remove all traces for a production binary.

One possibility is to used constants to get rid of portion of code.

- A boolean constant declared in an if statement can be used to fully remove portion of code.

- When this boolean is resolved as false, the code become unreachable and thus, will not be embedded.

- You can find more information about the usage of constants in an if statement 
  by :ref:`clicking here <section.classpath.elements.Constants.ifRemoval>`.

- If we consider the constant ``com.mycompany.logging`` was declared as false in a file named ``example.constants.list``.

   - To remove the previous logging, add an if statement as follow:
   
      .. code-block:: java 

         public static void switchState(ApplicationState newState) {
            oldState = currentState;
            currentState = newState;

            if(Constants.getBoolean("com.mycompany.logging")) {
               String category = "Application";
               int logID = 2;
               BasicMessageLogger.INSTANCE.log(Level.INFO, category, logID, oldState, currentState);
            }
         }

   - When using the API ``ej.api.trace``, a boolean constant can be accessed named ``TRACE_ENABLED_CONSTANT_PROPERTY`` 
     representing the :ref:`BON Constant <section.classpath.elements.constants>` ``core.trace.enabled``.
      
      - This constant is true when traces are enable in the system and false otherwise.
     
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

      - The value of this constant can be modified by going to ``Launch > Launch configurations`` then in the tab ``Configuration``,
        under the option ``Runtime``, you can check the option ``Enable execution traces`` to set the value to true.

         .. image:: images/tuto_application_trace_enable_execution_traces.PNG

Another possibility is to use external tools.

-  For example, the ProGuard open source tool.

   -  ProGuard is a command-line tool that shrinks, optimizes and
      obfuscates Java code.
   
   -  It is able to optimize bytecode as well as detect and remove
      unused instructions. For example, it can be used to remove all log
      messages in a production binary.
   
   -  A How-To is available in the MicroEJ github for using ProGuard in 
      https://github.com/MicroEJ/How-To/tree/master/Proguard-Get-Started.
   
   -  This example is based on removing code of elements of the library 
      **ej.library.eclasspath.logging**.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.