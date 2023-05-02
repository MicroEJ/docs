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

Verbose Mode
------------

If you need more information about the execution of the Application with the Simulator, 
the verbose mode can be enabled by using the ``--info`` Gradle option::

   gradle runOnSimulator --info

.. _sdk_6_debug_on_simulator:

Debug on Simulator
------------------

.. warning::
   IntelliJ IDEA cannot be used as the debugger client for the moment, use Eclipse instead.

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

.. _sdk_6_run_or_debug_on_with_multiple_vee_ports:

Run or Debug an Application with multiple VEE Ports
---------------------------------------------------

Only one VEE Port can be used to run or debug an Application on the Simulator.
If multiple VEE Ports are defined, the task fails with a message listing all the VEE Ports that can be used::

   More than one VEE Port have been defined.
   A VEE Port must be selected using the 'veePort' property ('-PveePort="veePortName"'). The following VEE Ports are available:
   - "veePort1"
   - "veePort2"
 
To run or debug an Application, you must select the VEE Port to use by setting the ``veePort`` property to the 
:ref:`unique name <sdk_6_vee_port_unique_name>` of the VEE Port when calling 
the ``runOnSimulator`` or ``debugOnSimulator`` task::

   gradle runOnSimulator -PveePort="veePortName"

If you want to add the property in IntelliJ IDEA : 

- Go to ``Run`` > ``Edit Configurations...``
- Click on the ``+`` button and select ``Gradle``
- Choose a name for the new configuration in the ``Name`` input field
- Add the task name with the ``veePort`` property in the ``Run`` dialog : ``runOnSimulator -PveePort="veePortName"``:

  .. figure:: images/intellij-runOnSimulator-run-configuration.png
     :alt: IntelliJ runOnSimulator Run Configuration Window
     :align: center
     :scale: 100%

     IntelliJ runOnSimulator Run Configuration Window

- Click on ``OK``
- Run the task by double clicking on the newly created Run Configuration in the Gradle view:

  .. figure:: images/intellij-runOnSimulator-run-configuration-gradle-view.png
     :alt: IntelliJ runOnSimulator Run Configuration in Gradle view
     :align: center
     :scale: 100%

     IntelliJ runOnSimulator Run Configuration in Gradle view

If you want to add the property in Eclipse : 

- Go to ``Run`` > ``Run Configurations...``
- Create a new Gradle Configuration
- Choose a name for the new configuration in the ``Name`` input field
- In the ``Gradle Tasks``, add the ``runOnSimulator`` task :

  .. figure:: images/eclipse-runOnSimulator-gradle-tasks.png
     :alt: Eclipse runOnSimulator task Gradle Tasks tab
     :align: center
     :scale: 100%
     
     Eclipse runOnSimulator task Gradle Tasks tab

- Go to the ``Project Settings`` tab
- Check ``Override project settings``
- Select ``Gradle Wrapper``
- Add the property as a Program Argument :

  .. figure:: images/eclipse-runOnSimulator-project-settings.png
     :alt: Eclipse runOnSimulator task Project Settings tab
     :align: center
     :scale: 100%
     
     Eclipse runOnSimulator task Project Settings tab

- Click on ``Run``
  
..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
