.. _sdk_6_howto_use_a_feature_entrypoint_class:

How To Use a FeatureEntryPoint class as my Application EntryPoint
=================================================================

An Application can require the use of advanced features, for example the `FeatureEntryPoint.stop()`_ method, 
in order to communicate with a Kernel.
To use such features, you must create a class implementing the ``ej.kf.FeatureEntryPoint`` interface.
The creation of a Feature class is done as follows:

- Create a new Application project, as described in :ref:`sdk_6_create_project`.
- Add the KF module in the ``dependencies`` block of the ``build.gradle.kts`` file of the project:

.. code:: java

   dependencies {
     implementation("ej.api:kf:1.7.0")
   }  

- Create the Java class of the Feature EntryPoint in the ``src/main/java`` folder, for example:

.. code:: java

   package com.mycompany;

   import ej.kf.FeatureEntryPoint;

   public class MyFeature implements FeatureEntryPoint {
       @Override
       public void start() {
         System.out.println("Feature MyFeature started!");
       }

       @Override
       public void stop() {
         System.out.println("Feature MyFeature stopped!");
       }       
   }

- Define the property ``applicationEntryPoint`` in the ``microej`` configuration block of the ``build.gradle.kts`` file.
  It must be set to the Full Qualified Name of the Feature class, for example::

    microej {
      applicationEntryPoint = "com.mycompany.MyFeature"
    }

.. _FeatureEntryPoint.stop(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/FeatureEntryPoint.html#stop--

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
