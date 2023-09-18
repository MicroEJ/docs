.. _sdk_6_import_project:

Import a Project
================

This chapter explains how to import a project in an IDE.

.. tabs::

   .. tab:: Android Studio

      In order to import an existing Gradle project in Android Studio, follow the following steps:
      
      - Click on ``File`` > ``New`` > ``Import Project...``.
      - Select the root directory of the project and click on the ``OK`` button.
      
      The Gradle project should now be imported in Android Studio.

   .. tab:: IntelliJ IDEA

      In order to import an existing Gradle project in IntelliJ IDEA, follow the following steps:
      
      - Click on ``File`` > ``New`` > ``Project From Existing Sources...``.
      - Select the root directory of the project and click on the ``OK`` button.
      - Select ``Import project from external model`` and choose ``Gradle``. 
      
      .. figure:: images/intellij-import-gradle-project-01.png
         :alt: Project Import in IntelliJ IDEA
         :align: center
         :scale: 70%
      
         Project Import in IntelliJ IDEA
      
      - Click on the ``Create`` button.
      
      The Gradle project should now be imported in IntelliJ IDEA.
      
      .. note::
         A message ``Project JDK is not defined`` is displayed at the top of the editor.
         This message can be ignored.
         It warns that the project does not have a JDK defined, which is expected since a MicroEJ project does not rely on a standard JDK.
      
         .. figure:: images/intellij-project-sdk-message.png
            :alt: Project JDK message in IntelliJ IDEA
            :align: center
            :scale: 70%
      
            Project JDK message in IntelliJ IDEA

   .. tab:: Eclipse

      In order to import an existing Gradle project in Eclipse, follow these steps:
      
      - Click on ``File`` > ``Import...``.
      - Select the project type ``Gradle > Existing Gradle Project`` and click on the ``Next`` button.
      
      .. figure:: images/eclipse-import-gradle-project-01.png
         :alt: Project Type Selection in Eclipse
         :align: center
         :scale: 70%
      
         Project Type Selection in Eclipse
      
      - Select the root directory of the project.
      
      .. figure:: images/eclipse-import-gradle-project-02.png
         :alt: Project root folder in Eclipse
         :align: center
         :scale: 70%
      
         Project root folder in Eclipse
      
      - Click on the ``Next`` button and finally on the ``Finish`` button.
      
      The Gradle project should now be imported in Eclipse.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
