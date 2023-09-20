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

The SDK allows to run an Application with the Simulator in debug mode by setting the System property ``debug.mode`` to ``true`` 
when executing the runOnSimulator task::

   ./gradlew runOnSimulator -P"debug.mode"=true

The debug mode is activated on the port ``12000`` by default. 
The port can be changed by using the System Property ``debug.port``::

   ./gradlew runOnSimulator -P"debug.mode"=true -P"debug.port"=8000


Once started, the Simulator waits for the connection of a debugger.

If you want to connect the IDE debugger:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      - Add a breakpoint in your Application code.
      - Click on ``Run > Edit Configurations...``.
      - Click on ``+`` button (``Add New Configuration``).
      - Select ``Remote JVM Debug``.
      - Click on the ``New launch configuration`` button.
      - Give a name to the launcher in the ``Name`` field.
      - Set the debug host and port.
      - Click on the ``Debug`` button.

   .. tab:: Eclipse

      - Add a breakpoint in your Application code.
      - Click on ``Run > Debug Configurations...``.
      - Select ``Remote Java Application``.
      - Click on the ``New launch configuration`` button.
      - Give a name to the launcher in the ``Name`` field.
      - Set the debug host and port.
      - Click on the ``Debug`` button.

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
the ``runOnSimulator`` task:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      To add the property in Android Studio or IntelliJ IDEA : 
      
      - Go to ``Run`` > ``Edit Configurations...``.
      - Click on the ``+`` button and select ``Gradle``.
      - Choose a name for the new configuration in the ``Name`` input field.
      - Add the task name with the ``veePort`` property in the ``Run`` dialog : ``runOnSimulator -PveePort="veePortName"``:
      
        .. figure:: images/intellij-runOnSimulator-run-configuration.png
           :alt: Android Studio and IntelliJ runOnSimulator Run Configuration Window
           :align: center
           :scale: 100%
      
           Android Studio and IntelliJ runOnSimulator Run Configuration Window
      
      - Click on ``OK``.
      - Run the task by double clicking on the newly created Run Configuration in the Gradle view:
      
        .. figure:: images/intellij-runOnSimulator-run-configuration-gradle-view.png
           :alt: Android Studio and IntelliJ runOnSimulator Run Configuration in Gradle view
           :align: center
           :scale: 100%
      
           Android Studio and IntelliJ runOnSimulator Run Configuration in Gradle view

   .. tab:: Eclipse

      To add the property in Eclipse: 
      
      - Go to ``Run`` > ``Run Configurations...``.
      - Create a new Gradle Configuration.
      - Choose a name for the new configuration in the ``Name`` input field.
      - In the ``Gradle Tasks``, add the ``runOnSimulator`` task:
      
        .. figure:: images/eclipse-runOnSimulator-gradle-tasks.png
           :alt: Eclipse runOnSimulator task Gradle Tasks tab
           :align: center
           :scale: 100%
           
           Eclipse runOnSimulator task Gradle Tasks tab
      
      - Go to the ``Project Settings`` tab.
      - Check ``Override project settings``.
      - Select ``Gradle Wrapper``.
      - Add the property as a Program Argument:
      
        .. figure:: images/eclipse-runOnSimulator-project-settings.png
           :alt: Eclipse runOnSimulator task Project Settings tab
           :align: center
           :scale: 100%
           
           Eclipse runOnSimulator task Project Settings tab
      
      - Click on ``Run``.

   .. tab:: Command Line Interface

      To add the property from the command line interface::

         ./gradlew runOnSimulator -PveePort="veePortName"

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
