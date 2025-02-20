.. _sdk_6_howto_create_custom_configuration_in_ide:

How To Create a Custom Configuration in the IDE
===============================================

This chapter explains how to create a new Configuration in all the supported IDEs.

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      The creation of a new Configuration with Android Studio / IntelliJ IDEA is done as follows:
      
      - Click on :guilabel:`Run` > :guilabel:`Edit Configurations...`.
      - Click on :guilabel:`+` and Select :guilabel:`Gradle`.
      - Fill the name of the new Configuration in the :guilabel:`Name` field.
      - Add a task and an option or a property if needed in the ``Run`` dialog, for example ``runOnSimulator -Pdebug.mode=true``.
      
      .. figure:: images/intellij-run-configuration.png
         :alt: Configuration Creation in IntelliJ IDEA
         :align: center
         :scale: 70%
      
         Configuration Creation in IntelliJ IDEA
    
      - Click on :guilabel:`OK`.
      - Select the newly created Configuration in the drop-down list in the Navigation bar and click on the :guilabel:`run` button to launch it.
      
      .. figure:: images/intellij-navigation-bar.png
         :alt: Navigation bar in IntelliJ IDEA
         :align: center
         :scale: 70%
      
         Navigation bar in IntelliJ IDEA
            
      - The Configuration can also be launched by double-clicking on it in the Gradle tasks view.
      
      .. figure:: images/intellij-gradle-view.png
         :alt: Gradle view in IntelliJ IDEA
         :align: center
         :scale: 70%
      
         Gradle view in IntelliJ IDEA

   .. tab:: Eclipse

      The creation of a new Configuration with Eclipse is done as follows:
      
      - Click on :guilabel:`Run` > :guilabel:`Run Configurations...`.
      - Right-click on :guilabel:`Gradle Task` and click on :guilabel:`New Configuration`.
      - Fill the name of the new Configuration in the :guilabel:`Name` field.
      - Add a task's name in the ``Gradle Tasks`` tab, for example ``runOnSimulator``.
      
      .. figure:: images/eclipe-run-configuration-gradle-tasks.png
         :alt: Configuration Gradle Tasks tab in Eclipse
         :align: center
         :scale: 70%
      
         Configuration Gradle Tasks tab in Eclipse
    
      - Go to the ``Project Settings`` tab.
      - Check ``Override project settings``.
      - Add an option or a property as a Program Argument if needed, for example ``-Pdebug.mode=true``.
      
      .. figure:: images/eclipe-run-configuration-project-settings.png
         :alt: Configuration Project Settings tab in Eclipse
         :align: center
         :scale: 70%
      
         Configuration Project Settings tab in Eclipse

      .. warning::
         Some tasks require to define specific options to be executed. These options must be defined with the task's name in the ``Gradle Tasks`` tab.
         For example, to run the :ref:`Local Deployment Socket <sdk6_localDeployTool>`, the ``execTool`` task and its options must be specified:

         .. figure:: images/eclipe-run-configuration-execTool-task.png
            :alt: Configuration execTool Task tab in Eclipse
            :align: center
            :scale: 70%
      
            Configuration execTool Task tab in Eclipse

      - Click on :guilabel:`Run` to launch the Configuration.

   .. tab:: Visual Studio Code

      The creation of a new Configuration with Visual Studio Code is done as follows:
      
      - In the Gradle tasks view, right-Click on the task for which you want to create a new Configuration.
      - Click on ``Pin Task With Args``.
      
      .. figure:: images/vscode-new-configuration.png
         :alt: New Gradle Configuration in Visual Studio Code
         :align: center
         :scale: 70%
      
         New Gradle Configuration in Visual Studio Code
    
      - Fill the option or property in the Search Bar and press ``Enter``.

      .. warning::
         All task options must be defined **without** quotes in Visual Studio Code. For example, 
         to run the :ref:`Local Deployment Socket <sdk6_localDeployTool>`, the ``execTool`` task must be executed with the 
         ``--name=localDeploymentSocket`` option. 
         
         If quotes are used (``--name="localDeploymentSocket"``), Visual Studio Code does not correctly pass the option to Gradle and 
         the build fails with the following error:

         .. code-block:: console

            > MicroEJ Tool '"localDeploymentSocket"' not found in <path\to\project>\build\vee\scripts\
            Make sure that the correct MicroEJ VEE is selected.
      
      - The newly created Configuration is available in the Gradle tasks view.

      .. figure:: images/vscode-pinned_task.png
         :alt: Pinned Configuration in Visual Studio Code
         :align: center
         :scale: 70%
      
         Pinned Configuration in Visual Studio Code

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
