.. _sdk_6_build_executable:

Build an Executable
===================

In order to build the Executable of an Application, the SDK provides the Gradle ``buildExecutable`` task.
The prerequisites to use this task are:

- the property ``applicationMainClass`` must be defined in the ``microej`` configuration block of the Gradle build file of the project.
  It must be set to the Full Qualified Name of the Application main class, for example::

   microej {
     applicationMainClass = "com.mycompany.Main"
   }

- A target VEE Port that uses an Architecture version ``7.17`` minimum must be defined.
  Refer to the :ref:`sdk_6_select_veeport` page to know the different ways to provide a VEE Port for a module project.

Once these prerequisites are fulfilled, the Executable can be built with the command::

    $ gradle buildExecutable

or from Eclipse and IntelliJ IDEA, by double-clicking on the ``buildExecutable`` task in the Gradle tasks view.

.. tabs::

   .. tab:: Eclipse

      .. image:: images/eclipse-buildExecutable-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: IntelliJ IDEA

      .. image:: images/intellij-buildExecutable-gradle-project.png
         :width: 50%
         :align: center

In case of :ref:`Full BSP Connection <bsp_connection>`, the Executable file is generated in the ``build/output/application/veePortName`` folder of the project,
where ``veePortName`` is the :ref:`unique name <sdk_6_vee_port_unique_name>` of the target VEE Port.

.. _sdk_6_buildExecutable_with_multiple_vee_ports:

Build an Executable with multiple VEE Ports
-------------------------------------------

If multiple VEE Ports are defined, the Executable file is built for each VEE Port sequentially.
It is possible to define properties specific to a VEE Port by adding the properties files in 
the ``configuration/veePortName`` folder,
where ``veePortName`` is the :ref:`unique name <sdk_6_vee_port_unique_name>` of the VEE Port.

If you want to build the Executable for only one VEE Port, you must select it by setting the ``veePort`` property 
when calling the ``buildExecutable`` task::

   gradle buildExecutable -PveePort="veePortName"

If you want to add the property in IntelliJ IDEA : 

- Go to ``Run`` > ``Edit Configurations...``
- Click on the ``+`` button and select ``Gradle``
- Choose a name for the new Configuration
- Add the task name with the ``veePort`` property in the Run dialog : ``buildExecutable -PveePort="veePortName"``:

  .. figure:: images/intellij-buildExecutable-configuration.png
     :alt: IntelliJ buildExecutable Configuration Window
     :align: center
     :scale: 100%

     IntelliJ buildExecutable Configuration Window

- Click on ``OK``
- Run the task by double clicking on the newly created Run Configuration in the Gradle task view:

  .. figure:: images/intellij-buildExecutable-configuration-gradle-view.png
     :alt: IntelliJ buildExecutable Configuration in Gradle tasks view
     :align: center
     :scale: 100%

     IntelliJ buildExecutable Configuration in Gradle tasks view

If you want to add the property in Eclipse : 

- Go to ``Run`` > ``Run Configurations...``
- Create a new Gradle Configuration
- Choose a name for the new configuration in the ``Name`` input field
- In the ``Gradle Tasks`` tab, add the ``buildExecutable`` task :

  .. figure:: images/eclipse-buildExecutable-gradle-tasks.png
     :alt: Eclipse buildExecutable task Gradle Tasks tab
     :align: center
     :scale: 100%
     
     Eclipse buildExecutable task Gradle Tasks tab

- Go to the ``Project Settings`` tab
- Check ``Override project settings``
- Select ``Gradle Wrapper``
- Add the property as a Program Argument :

  .. figure:: images/eclipse-buildExecutable-project-settings.png
     :alt: Eclipse buildExecutable task Project Settings tab
     :align: center
     :scale: 100%
     
     Eclipse buildExecutable task Project Settings tab

- Click on ``Run``
  
The name of each VEE Port can be found by executing the ``buildExecutable`` task with the verbose mode enabled::

   gradle buildExecutable --info

The list of the VEE Ports is displayed before building the Executable::

   The Executable will be built for each of the following VEE Ports:
   - "veePort1"
   - "veePort2"



..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
