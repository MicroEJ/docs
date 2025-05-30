.. _sdk_6_import_project:

Import a Project
================

This chapter explains how to import a project in an IDE.

.. tabs::

   .. tab:: IntelliJ IDEA

      In order to import an existing Gradle project in IntelliJ IDEA, follow the following steps:
      
      - If you are in the Welcome Screen, click on the :guilabel:`Open` button. 
        Otherwise click either on :guilabel:`File` > :guilabel:`Open...` or on :guilabel:`File` > :guilabel:`New` > :guilabel:`Project From Existing Sources...`.
      - Select the root directory of the project and click on the :guilabel:`OK` button.

      .. figure:: images/intellij-import-project.png
         :alt: Project Import in IntelliJ IDEA
         :align: center
         :scale: 70%
      
         Project Import in IntelliJ IDEA

      - If you are asked to choose a project model, select :guilabel:`Gradle`. 

      .. raw:: html

         <div style="display:block;margin-bottom:24px;">
            <table>
               <tr>
                  <td style="width:50%;text-align:center;vertical-align:middle;" alt="Project Model Selection when Opening in IntelliJ IDEA">
                     <img src="../_images/intellij-import-gradle-project-01.png">
                  </td>
                  <td style="width:50%;text-align:center;vertical-align:middle;" alt="Project Model Selection when Importing in IntelliJ IDEA">
                     <img src="../_images/intellij-import-gradle-project-02.png">
                  </td>
               </tr>
               <tr>
                  <td style="width:50%;text-align:center;font-size:18px;font-style:italic;">
                     Fig 1. Project Model Selection when Opening in IntelliJ IDEA
                  </td>
                  <td style="width:50%;text-align:center;font-size:18px;font-style:italic;">
                     Fig 2. Project Model Selection when Importing in IntelliJ IDEA
                  </td>
               </tr>
            </table>
         </div>

      .. |image1| image:: images/intellij-import-gradle-project-01.png
      .. |image2| image:: images/intellij-import-gradle-project-02.png

      - Click on the :guilabel:`Create` button.

      The Gradle project should now be opened in IntelliJ IDEA.

   .. tab:: Android Studio

      In order to import an existing Gradle project in Android Studio, follow the following steps:
      
      - If you are in the Welcome Screen, click on the :guilabel:`Open` button. 
        Otherwise click either on :guilabel:`File` > :guilabel:`Open...` or on :guilabel:`File` > :guilabel:`Import Project...`.
      - Select the root directory of the project and click on the :guilabel:`OK` button.

      .. figure:: images/android-studio-import-project.png
         :alt: Project Import in Android Studio
         :align: center
         :scale: 70%
      
         Project Import in Android Studio
      
      The Gradle project should now be opened in Android Studio.

   .. tab:: Eclipse

      In order to import an existing Gradle project in Eclipse, follow these steps:
      
      - Click on :guilabel:`File` > :guilabel:`Import...`.
      - Select the project type :guilabel:`Gradle` > :guilabel:`Existing Gradle Project` and click on the :guilabel:`Next` button.
      
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
      
      - Click on the :guilabel:`Next` button and finally on the :guilabel:`Finish` button.
      
      The Gradle project should now be opened in Eclipse.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
