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
      - Add a task and a property if needed in the ``Run`` dialog, for example ``runOnSimulator -P"debug.mode"=true``.
      
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
      - Add a property as a Program Argument if needed, for example ``-P"debug.mode"=true``.
      
      .. figure:: images/eclipe-run-configuration-project-settings.png
         :alt: Configuration Project Settings tab in Eclipse
         :align: center
         :scale: 70%
      
         Configuration Project Settings tab in Eclipse
            
      - Click on :guilabel:`Run` to launch the Configuration.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
