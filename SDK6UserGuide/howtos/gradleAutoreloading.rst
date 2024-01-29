.. _sdk_6_howto_gradle_autoreloading:

How To Automatically reload a Gradle project
============================================

By default, regardless of the IDE that you are using (Android Studio, IntelliJ IDEA or Eclipse), the reload of a Gradle project 
must be explicitly triggered by the user when the configuration of the project has changed. This allows to avoid
reloading the project too frequently, but the user must not forget to manually reload the project to apply changes.

It is also possible to configure your IDE to automatically reload your Gradle project: 

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      The auto-reload of a Gradle project with Android Studio / IntelliJ IDEA can be enabled as follows:
      
      - Click on :guilabel:`File` > :guilabel:`Settings...`.
      - Go to  :guilabel:`Build, Execution, Deployment` > :guilabel:`Build Tools`.
      - Check the :guilabel:`Reload changes in the build scripts` option and check the :guilabel:`Any changes` option.

      .. figure:: images/intellij-autoreload.png
         :alt: auto-reload option in Android Studio / IntelliJ IDEA
         :align: center
         :scale: 70%
      
         Auto-reload option in Android Studio / IntelliJ IDEA
      
      - Go to :guilabel:`Languages & Frameworks` > :guilabel:`Kotlin` > :guilabel:`Kotlin Scripting`.
      - Check all the :guilabel:`Auto Reload` options.

      .. figure:: images/intellij-kotlin-autoreload.png
         :alt: auto-reload Kotlin option in Android Studio / IntelliJ IDEA
         :align: center
         :scale: 70%
      
         Auto-reload Kotlin option in Android Studio / IntelliJ IDEA

   .. tab:: Eclipse

      The auto-reload of a Gradle project with Eclipse can be enabled as follows:
      
      - Click on :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`Gradle`.
      - Check the :guilabel:`Automatic Project Synchronization` option.

      .. figure:: images/eclipse-autoreload.png
         :alt: auto-reload option in Eclipse
         :align: center
         :scale: 70%
      
         Auto-reload option in Eclipse




..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
