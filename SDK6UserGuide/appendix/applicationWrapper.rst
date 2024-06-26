.. _gradle_application_wrapper_chapter:

Application Wrapper
===================

The unification of the Application EntryPoints allows to build and run an Application regardless of 
the VEE provided by the user (a VEE Port or a Kernel). To ensure that an Application can run on different kinds of VEE, 
a wrapper class is generated. For example, 
if your Application EntryPoint is a class containing a ``public static void main(String[args])`` method:

.. code:: java

   package com.mycompany;

   public class MyClass {
       public static void main(String[] args) {
         System.out.println("Hello World!");
       } 
   }

A wrapper class implementing the ``ej.kf.FeatureEntryPoint`` interface is created:

.. code:: java

   package com.mycompany;

   import ej.kf.FeatureEntryPoint;

   public class MyClassWrapper implements FeatureEntryPoint {
       @Override
       public void start() {
         com.mycompany.MyClass.main(new String[0]);
       }

       @Override
       public void stop() {
       }       
   }

Then, the execution of the Application depends on the VEE provided in the ``build.gradle.kts`` file of your project:

- If a VEE Port or a Mono-Sandbox Kernel has been provided, the ``MyClass`` main class of the Application is executed.
- If a Multi-Sandbox Kernel has been provided, the Application is executed as a Feature of the Kernel.  

In addition to the wrapper class, the following resource files are generated:

- The Feature Definition Files (``feature.kf``, ``feature.cert``), if they do not already exist, to use your Application as a Sandboxed Application. 
- The Kernel Definition Files (``kernel.kf``, ``kernel.cert``), if they do not already exist, to use your Application as a Kernel Application. 

Refer to the :ref:`kf-feature-definition` section for more information about Feature and Kernel Definition Files.

If your Application requires advanced features, it is also possible to :ref:`use a FeatureEntryPoint class as Application EntryPoint <sdk_6_howto_use_a_feature_entrypoint_class>`.
In that case the created wrapper class is a class containing a ``public static void main(String[args])`` method that calls the
``start()`` method of your Application EntryPoint class:

.. code:: java

   package com.mycompany;

   public class MyClassWrapper {
       public static void main(String[] args) {
         new com.mycompany.MyClass.start();
       }    
   }
   
and the Kernel and Feature Definition files are generated.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
