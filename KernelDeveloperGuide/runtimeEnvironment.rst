.. _runtime_environment:

===================
Runtime Environment
===================

Principle
---------

A Runtime Environment is a :ref:`module nature <module_natures>` for defining the set of APIs available to an Application developer on a Kernel.
It is built by aggregating a set of :ref:`Kernel APIs <kernel.api>`.

Building a Runtime Environment is one of the 2 solutions to define the APIs of a Kernel, as described in the section :ref:`define_apis`.
Having the set of APIs named and versioned in a Runtime Environment allows to maintain, share and document it outside of a specific Kernel implementation.

Once built, a Runtime Environment module contains the following elements:

- A JAR file with the whole library of APIs (``.class`` files and ``.java``), used by Application projects to compile Application code;
- A JAR file with the ``kernel.api`` file defined in the module (if any), 
  used by Kernel projects to fetch all the ``kernel.api`` files (by transitivity) to expose APIs when building the Firmware and the Virtual Device;
- A JAR file with the Javadoc of the APIs for documentation.

The following figure shows the overall build flow:

.. image:: png/runtime_environment_build_flow.png
   :align: center
   :scale: 75%


Create a new Runtime Environment Module
---------------------------------------

A Runtime Environment :ref:`module project <mmm_module_skeleton>` is created with the ``runtime-api`` skeleton.

.. code:: xml

   <info organisation="com.mycompany" module="myruntimeapi" status="integration" revision="1.0.0">
      <ea:build organisation="com.is2t.easyant.buildtypes" module="build-runtime-api" revision="3.0.+">
      </ea:build>
   </info>

Kernel APIs as dependencies
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Kernel APIs can be declared as dependencies of the module.
For example, the following dependencies declare a Runtime Environment that aggregates all classes, methods and fields
defined by ``EDC,KF,BON,Wadapps,MicroUI`` Kernel APIs modules.

.. code:: xml

   <dependencies>
      <dependency org="com.microej.kernelapi" name="edc" rev="1.0.6"/>
      <dependency org="com.microej.kernelapi" name="kf" rev="2.0.3"/>
      <dependency org="com.microej.kernelapi" name="bon" rev="1.1.1"/>
      <dependency org="com.microej.kernelapi" name="wadapps" rev="2.1.2"/>
      <dependency org="com.microej.kernelapi" name="microui" rev="3.1.0"/>
   </dependencies>

The libraries modules are fetched transitively from the Kernel APIs dependencies.
For example, the dependency ``com.microej.kernelapi#edc;1.0.6`` fetches the library ``ej.api#edc;1.2.3``.

It is also possible to force the version of the libraries to use by declaring them as direct dependencies.
In this example:

.. code:: xml

   <dependencies>
      <dependency org="com.microej.kernelapi" name="edc" rev="1.0.6"/>
      
      <dependency org="ej.api" name="edc" rev="1.3.4"/>
   </dependencies>

The Runtime Environment uses the version ``1.3.4`` of the EDC library instead of the version ``1.2.3`` fetched transitively by the dependency ``com.microej.kernelapi#edc;1.0.6``.

Kernel APIs as project file
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Kernel APIs can also be defined in a file in the Runtime Environment directly.
The file must be named ``kernel.api`` and stored in the ``src/main/resources`` folder.


Use a Runtime Environment in an Application
-------------------------------------------

Once a Runtime Environment is available, it can be used in the Applications as a dependency::

   <dependency org="com.mycompany" name="myruntimeapi" rev="1.0.0" conf="provided->runtimeapi"/>

It is important to note that in order to have a consistent development environment, 
it is highly recommended to declare the Runtime Environment module as **the only dependency** of the Application modules.
In the case an Application needs to use a library not included in the Runtime Environment, 
the recommended process is to add this library in the Runtime Environment.
Declaring additional dependencies in the Application could lead to inconsistent situations, for example by using an API not available at runtime.


Extend a Runtime Environment
----------------------------

Foundation and Add-On libraries can be extended by adding new methods to their existing classes thanks to the `Class Extender
tool <https://repository.microej.com/modules/com/microej/tool/class-extender/>`_. This tool works at binary level
and is able to inject methods from one class to another. Extensions can thus be independently compiled and be retrieved
by the Kernel and applied during a Multi-Sandbox Firmware build.

To make the extensions available to Application developers, the Runtime Environment has to be extended too. 

The following diagram illustrates the process of extending the default `String <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/String.html>`_ class from :ref:`[EDC] <runtime_edc>` from a Kernel developer point of view:

.. image:: png/graph_build_string_methods.png
   :align: center
   :scale: 100%

Two processes are taking place to apply extensions:

   1. The custom Runtime Environment is built using the ``build-runtime-api`` build type. It takes three components as input:

      - EDC Foundation Library API which contains the String class we want to extend,
      - a :ref:`Kernel API <kernel.api>` file definition in the ``src/main/resource`` folder which includes new methods,
      - a new ``String.java`` API source file in the ``src/main/java`` folder, which includes new methods with their Javadoc specification. 
        This class overrides the String class fetched from EDC dependency.

      Once built, a Runtime Environment module contains the following elements:

      - an Add-On library containing the new ``kernel.api``
      - the Runtime API containing the extended String API
      - the corresponding Javadoc including the extended methods

   2. An extended EDC implementation is built during Kernel build by calling the Class Extender tool. It takes two components:

      - the original EDC Foundation library implementation jar file
      - the String extension Add-On library jar file

      It overrides the original EDC Foundation library implementation jar file.

Class Extension Principle
~~~~~~~~~~~~~~~~~~~~~~~~~

A class extension is a Java class that implements methods to inject to a target class. The methods to inject must

   - be annotated with the `@Extend <https://repository.microej.com/javadoc/microej_5.x/apis/ej/basictool/annotation/Extend.html>`_ annotation which takes as parameter the fully qualified name of the class to extend
   - be declared as ``static``
   - (**if it is an instance method**) take a first parameter of the type of the class to extend.
     This parameter refers to the instance of the created object (the ``this``)
   - (**if it is a class method**) add ``isStatic=true`` to the `@Extend <https://repository.microej.com/javadoc/microej_5.x/apis/ej/basictool/annotation/Extend.html>`_ annotation parameters

A Class Extension can then be built as an Add-On library (``build-microej-javalib``)  MicroEJ Module. To apply an extension,
you need to add the dependency to the Kernel ``module.ivy``. `Class Extender tool <https://repository.microej.com/modules/com/microej/tool/class-extender/>`_
will then inject extension methods bytecode to the orginal classes during Firmware build.

Refer to the `Class Extender tool README <https://repository.microej.com/modules/com/microej/tool/class-extender/1.0.4/README-1.0.4.md>`_ for more information about class extension and integration to Firmware.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.