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
      :width: 719px
      :height: 174px

      New MicroEJ Standalone Application Project

-  Fill in the application template fields, the Project name field will
   automatically duplicate in the following fields. Click on :guilabel:`Finish`.
   A template project is automatically created and ready to use, this
   project already contains all folders wherein developers need to put
   content:

   -  ``src/main/java``: Folder for future sources

   -  ``src/main/resources``: Folder for future resources (images, fonts, etc.)

   -  ``META-INF``: Sandboxed Application configuration and resources

   -  ``module.ivy``: Ivy input file, dependencies description for the
      current project

-  Right click on the source folder ``src/main/java`` and select
   :guilabel:`New` > :guilabel:`Package`. Give a name: ``com.mycompany``.
   Click on :guilabel:`Finish`.

   .. figure:: images/newApp8.png
      :alt: New Package
      :align: center
      :width: 525px
      :height: 326px

      New Package

-  The package ``com.mycompany`` is available under ``src/main/java`` folder.
   Right click on this package and select :guilabel:`New` > :guilabel:`Class`.
   Give a name: ``Test`` and check the box ``public static void main(String[]
   args)``. Click on :guilabel:`Finish`.

   .. figure:: images/newApp9.png
      :alt: New Class
      :align: center
      :width: 542px
      :height: 634px

      New Class

-  The new class has been created with an empty ``main()`` method. Fill
   the method body with the following lines:

   ::

      System.out.println("hello world!");


   .. figure:: images/newApp10.png
      :alt: MicroEJ Application Content
      :align: center
      :width: 438px
      :height: 192px

      MicroEJ Application Content

   The test application is now ready to be executed. See next sections.

.. _section.run.on.simulator:

Run on the Simulator
--------------------

To run the sample project on Simulator, select it in the left panel then right-click
and select :guilabel:`Run` > :guilabel:`Run as` > :guilabel:`MicroEJ Application`.

.. figure:: images/sim1.png
   :alt: MicroEJ Development Tools Overview
   :align: center
   :width: 698px
   :height: 552px

   MicroEJ Development Tools Overview

MicroEJ SDK console will display Launch steps messages.

::

    =============== [ Initialization Stage ] ===============
    =============== [ Launching on Simulator ] ===============
    hello world!
    =============== [ Completed Successfully ] ===============

    SUCCESS

.. _device_build:

Run on the Hardware Device
--------------------------

Build the application
~~~~~~~~~~~~~~~~~~~~~

- Configure your :ref:`BSP connection <bsp_connection>` to define the deployment location of the application, the runtime library and the header files. The section :ref:`BSP connection options <bsp_connection_options>` specifies all options that can be set for each BSP connection and how to set them. 

- Open the run dialog (:guilabel:`Run` > :guilabel:`Run Configurations...`).

- Select the :guilabel:`MicroEJ Application` > :guilabel:`HelloWorld` that is created by the previous chapter.

- Open :guilabel:`Execution` tab and select :guilabel:`Execute on Device`.

- Set :guilabel:`Settings` checkbox to :guilabel:`Build & Deploy`.

.. figure:: images/basic-launcher.png
   :alt: Execution on Device
   :align: center
   :width: 698px
   :height: 552px

   Execution on Device

- Click :guilabel:`Run` : The application is compiled and the application, the runtime library and the header files are automatically deployed to the locations defined in your BSP connection settings. 

::

    =============== [ Deployment ] ===============
    MicroEJ files for the 3rd-party BSP project are generated to '<application-project>/<fully-qualified-name-of-main-class>/platform'.
    The MicroEJ application (microejapp.o) has been deployed to: '<relative_path>'.
    The MicroEJ platform library (microejruntime.a) has been deployed to: '<relative_path>'.
    The MicroEJ platform header files (*.h) have been deployed to: '<relative_path>'.
    =============== [ Completed Successfully ] ===============

    SUCCESS


Generate the application.out file 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The application link can be triggered by executing the :ref:`build script <bsp_connection_build_script>` file:

- Open :guilabel:`configuration` tab and select :guilabel:`Device` > :guilabel:`Deploy`. The options to deploy the application, runtime library and header files have already been set in the previous step. 
  
- If your BSP connection is not configured to execute the build script file (see :ref:`BSP connection options <bsp_connection_options>`), check :guilabel:`Execute the MicroEJ build script (build.bat) at a location known by the 3rd-party BSP project`.

.. figure:: images/bsp-options.png
   :alt: BSP connection options
   :align: center
   :width: 1300px
   :height: 743px

   BSP connection options

- Click :guilabel:`Apply` and :guilabel:`Run` : the final executable :guilabel:`application.out` file is generated in the directory from where the script has been executed and can now be deployed on your Device using the appropriate flash tool. 
  
..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
