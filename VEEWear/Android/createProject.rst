
.. _create_ack_project_:



Create a Project
================

This chapter will guide you through the process of creating a project for having an application compatible with both Android and MicroEJ VEE.

Project Structure
~~~~~~~~~~~~~~~~~

The recommended project structure is to have a basic multi-project build that contains a root project and two subprojects: one subproject for the Android/Wear OS application and one subproject for the MicroEJ application.
The MicroEJ application defines the code that will run in both target environments, while the Android/Wear OS application contains the wrapper code and logic specific to Android.

What follows is the directory and file structure of a project:

.. code-block:: text

   ├── android-app/
   │   ├── src
   │   ├── microej.properties       # MicroEJ application options for Android/Wear OS
   │   └── build.gradle.kts
   ├── gradle/
   ├── microej-app/
   │   ├── src
   │   ├── configuration/
   │   |    └── common.properties   # MicroEJ application options for MicroEJ VEE
   │   └── build.gradle.kts
   ├── build.gradle.kts
   ├── gradlew 
   ├── gradlew.bat
   └── settings.gradle.kts



MicroEJ Application
~~~~~~~~~~~~~~~~~~~


Android Application
~~~~~~~~~~~~~~~~~~~




..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.