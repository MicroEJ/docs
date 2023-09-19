.. _sdk_6_build_feature:

Build a Feature file
====================

To build the Feature file (``.fo``) of an Application, the SDK provides the Gradle ``buildFeature`` task.
The prerequisites to use this task are:

- A target VEE Port or a Virtual Device that uses an Architecture version ``7.17`` minimum must be defined.
  Refer to the :ref:`sdk_6_select_veeport` page to learn how to provide a VEE Port or a Virtual Device for a module project.

- A Kernel must be defined.
  Refer to the :ref:`sdk_6_select_kernel` page to learn how to provide a Kernel for a module project.

Once these prerequisites are fulfilled, the Feature file can be built:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      By double-clicking on the ``buildFeature`` task in the Gradle tasks view:

      .. image:: images/intellij-buildFeature-gradle-project.png
         :width: 30%
         :align: center

   .. tab:: Eclipse

      By double-clicking on the ``buildFeature`` task in the Gradle tasks view:

      .. image:: images/eclipse-buildFeature-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: Command Line Interface

      From the command line interface::

          $ ./gradlew buildFeature

The Feature file is generated in the ``build/binary`` folder of the project.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
