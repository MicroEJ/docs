.. _sdk_6_run_on_simulator:

Run on Simulator
================

In order to execute an Application on the Simulator, the SDK provides the Gradle ``runOnSimulator`` task.
The prerequisites of this task are:

- the property ``applicationMainClass`` must be defined in the ``microej`` configuration block of the Gradle build file of the project.
  It must be set to the Full Qualified Name of the Application main class, for example::

   microej {
     applicationMainClass = "com.mycompany.Main"
   }

- the target VEE Port must be defined.
  Refer to the :ref:`sdk_6_select_veeport` page to know the different ways to provide a VEE Port for a module project.

Once these prerequisites are fulfilled, the Application can be started with the Simulator with the command line interface::

    $ gradle runOnSimulator

or from Eclipse and IntelliJ IDEA, by double-clicking on the ``runOnSimulator`` task in the Gradle tasks view:

.. tabs::

   .. tab:: Eclipse

      .. image:: images/eclipse-run-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: IntelliJ IDEA

      .. image:: images/intellij-run-gradle-project.png
         :width: 30%
         :align: center

With a simple Hello World Application, the output should be::

   =============== [ Initialization Stage ] ===============
   =============== [ Converting fonts ] ===============
   =============== [ Converting images ] ===============
   =============== [ Launching on Simulator ] ===============
   Hello World!
   =============== [ Completed Successfully ] ===============
   
   SUCCESS


Verbose mode
------------

If you need more information about the execution of the Application with the Simulator, 
the verbose mode can be enabled by using the ``--info`` Gradle option::

   gradle runOnSimulator --info

.. _sdk_6_debug_on_simulator:

Debug on Simulator
------------------

.. warning::
   IntelliJ IDEA cannot be used as the debugger client for the moment, so it is recommend to use Eclipse instead.

The SDK allows to run an Application with the Simulator in debug mode thanks to the Gradle task ``debugOnSimulator``::

   gradle debugOnSimulator

This task activates the debug mode on the port ``12000`` by default. 
The port can be changed by using the System Property ``debug.port``::

   gradle debugOnSimulator -Ddebug.port=8000

Once started, the Simulator waits for the connection of a debugger.

If you want to connect the Eclipse debugger:

- add a breakpoint in your Application code.
- click on ``Run > Debug Configurations...``.
- select ``Remote Java Application``.
- click on the ``New launch configuration`` button.
- give a name to the launcher in the ``Name`` field.
- set the debug host and port.
- click on the ``Debug`` button.


..
   If you want to connect the IntelliJ IDEA debugger:

   - add a breakpoint in your Application code.
   - click on ``Run > Debug...``.
   - click on ``Edit Configurations...``.
   - click on the ``+`` button in the top bar and select ``Remote JVM Debug``.
   - give a name to the launcher in the ``Name`` field.
   - set the debug host and port.
   - click on the ``Debug`` button.

The debugger should connect to the Simulator and you should be able to debug your Application.

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
