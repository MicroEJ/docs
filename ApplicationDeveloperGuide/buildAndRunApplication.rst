Build and Run an Application
============================

.. _simulator_execution:

Create a MicroEJ Standalone Application
---------------------------------------

-  Create a project in your workspace. Select :guilabel:`File` > :guilabel:`New` >
   :guilabel:`Standalone Application Project`.

   .. figure:: images/newApp1.png
      :alt: New MicroEJ Standalone Application Project
      :align: center
      :scale: 100%

      New MicroEJ Standalone Application Project

-  Fill in the Application template fields, the project name field will
   automatically duplicate in the following fields. For this tutorial, the project name is ``hello``. Click on :guilabel:`Finish`.
   A template project is automatically created and ready to use, this
   project already contains all folders wherein developers need to put content:

   -  ``src/main/java``: Folder for future sources

   -  ``src/main/resources``: Folder for future resources (raw resources, images, fonts, nls)

   -  ``module.ivy``: :ref:`Module description file <mmm_module_description>`, dependencies description for the
      current project

-  A ``Main`` class already exists in the package ``com.mycompany`` and prints "Hello World!" :
  
   .. figure:: images/newApp10.png
      :alt: MicroEJ Application Content
      :align: center
      :scale: 100%

      MicroEJ Application Content

   The main Application is now ready to be executed. See next sections.

.. _section.run.on.simulator:

Run on the Simulator
--------------------

.. note::

   :ref:`A Platform must have been imported <platform_import>` to run the Application. If several Platforms have been imported, the target Platform can be selected in the :ref:`Launcher's Execution tab <launch_execution_tab>`.

To run the sample project on Simulator, select it in the left panel then right-click
and select :guilabel:`Run` > :guilabel:`Run as` > :guilabel:`MicroEJ Application`.

.. figure:: images/sim1.png
   :alt: MicroEJ Launcher Shortcut
   :align: center
   :scale: 100%

   MicroEJ Launcher Shortcut

MicroEJ SDK console will display Launch steps messages.

::

    =============== [ Initialization Stage ] ===============
    =============== [ Launching on Simulator ] ===============
    Hello World!
    =============== [ Completed Successfully ] ===============

    SUCCESS

.. _device_build:

Run on the Device
-----------------

Build the Application
~~~~~~~~~~~~~~~~~~~~~

- Open the run dialog (:guilabel:`Run` > :guilabel:`Run Configurations...`).

- Select the :guilabel:`MicroEJ Application` > :guilabel:`Hello Main` that is created by the previous chapter.

- Open :guilabel:`Execution` tab and select :guilabel:`Execute on Device`.

- Set :guilabel:`Settings` checkbox to :guilabel:`Build & Deploy`.

.. figure:: images/basic-launcher.png
   :alt: Execution on Device
   :align: center
   :scale: 100%

   Execution on Device

- Click :guilabel:`Run` : The Application is compiled and the Application, the runtime library and the header files are automatically deployed to the locations defined in your Platform :ref:`BSP connection <bsp_connection>` settings. 

::

    =============== [ Deployment ] ===============
    MicroEJ files for the 3rd-party BSP project are generated to '<application-project>/<fully-qualified-name-of-main-class>/platform'.
    The MicroEJ application (microejapp.o) has been deployed to: '<path-to-deployment-location>'.
    The MicroEJ platform library (microejruntime.a) has been deployed to: '<path-to-deployment-location>'.
    The MicroEJ platform header files (*.h) have been deployed to: '<path-to-deployment-location>'.
    =============== [ Completed Successfully ] ===============

    SUCCESS

Build the Executable File 
~~~~~~~~~~~~~~~~~~~~~~~~~

If your Platform has configured a :ref:`build script <bsp_connection_build_script>` file, the final Application linking can be triggered from the launcher:

- Open :guilabel:`Configuration` tab and select :guilabel:`Device` > :guilabel:`Deploy`. The options to deploy the Application, runtime library and header files have already been set in the previous step. 
  
- Check :guilabel:`Execute the MicroEJ build script (build.bat) at a location known by the 3rd-party BSP project`.

.. figure:: images/bsp-options.png
   :alt: BSP connection options
   :align: center
   :scale: 100%

   BSP Connection Application Options

.. note::

   The table :ref:`MicroEJ Application Options for BSP Connection <bsp_connection_application_options>` specifies the Application options that can be set depending on the BSP connection configured by the Platform.

- Click :guilabel:`Apply` and :guilabel:`Run` : the final executable :guilabel:`application.out` file is generated in the directory from where the script has been executed and can now be deployed on your Device using the appropriate flash tool. 


..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
