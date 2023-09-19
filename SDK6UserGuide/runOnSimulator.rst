.. _sdk_6_run_on_simulator:

Run on Simulator
================

In order to execute an Application on the Simulator, the SDK provides the Gradle ``runOnSimulator`` task.
The prerequisites of this task are:

- The Application main class or Feature class must be configured, as described in :ref:`sdk_6_create_project_configure_project`.

- The target VEE Port or Virtual Device must be defined.
  Refer to the :ref:`sdk_6_select_veeport` page to know the different ways to provide a VEE Port or a Virtual Device for a module project.
  It is important to note that if the Application has a Feature class (and not a main class), it can only be run on a :ref:`Virtual Device <sdk_6_build_virtual_device>`.

Once these prerequisites are fulfilled, the Application can be started with the Simulator:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      By double-clicking on the ``runOnSimulator`` task in the Gradle tasks view:

      .. image:: images/intellij-run-gradle-project.png
         :width: 30%
         :align: center

   .. tab:: Eclipse

      By double-clicking on the ``runOnSimulator`` task in the Gradle tasks view:

      .. image:: images/eclipse-run-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: Command Line Interface

      From the command line interface::
      
          $ ./gradlew runOnSimulator


With a simple Hello World Application, the output should be::

   =============== [ Initialization Stage ] ===============
   =============== [ Converting fonts ] ===============
   =============== [ Converting images ] ===============
   =============== [ Launching on Simulator ] ===============
   Hello World!
   =============== [ Completed Successfully ] ===============
   
   SUCCESS

Verbose Mode
------------

If you need more information about the execution of the Application with the Simulator, 
the verbose mode can be enabled by using the ``--info`` Gradle option::

   ./gradlew runOnSimulator --info

.. _sdk_6_debug_on_simulator:

Debug on Simulator
------------------

.. warning::
   Android Studio and IntelliJ IDEA cannot be used as the debugger client for the moment, use Eclipse instead.

The SDK allows to run an Application with the Simulator in debug mode by setting the System property ``debug.mode`` to ``true`` 
when executing the runOnSimulator task::

   ./gradlew runOnSimulator -P"debug.mode"=true

The debug mode is activated on the port ``12000`` by default. 
The port can be changed by using the System Property ``debug.port``::

   ./gradlew runOnSimulator -P"debug.mode"=true -P"debug.port"=8000

Once started, the Simulator waits for the connection of a debugger.

If you want to connect the Eclipse debugger:

- Add a breakpoint in your Application code.
- Click on ``Run > Debug Configurations...``.
- Select ``Remote Java Application``.
- Click on the ``New launch configuration`` button.
- Give a name to the launcher in the ``Name`` field.
- Set the debug host and port.
- Click on the ``Debug`` button.


..
   If you want to connect the IntelliJ IDEA debugger:

   - Add a breakpoint in your Application code.
   - Click on ``Run > Debug...``.
   - Click on ``Edit Configurations...``.
   - Click on the ``+`` button in the top bar and select ``Remote JVM Debug``.
   - Give a name to the launcher in the ``Name`` field.
   - Set the debug host and port.
   - Click on the ``Debug`` button.

The debugger should connect to the Simulator and you should be able to debug your Application.
  
..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
