.. _runtime_environment:

===================
Runtime Environment
===================

A Runtime Environment is a :ref:`module nature <module_natures>` for defining the set of APIs available to an Application developer on a Kernel.
It is built by aggregating a set of :ref:`Kernel APIs <kernel.api>`. It also allows to extend the classes of default modules with additional methods.

Having the set of APIs named and versioned allows to maintain, share and document it outside a specific Kernel implementation.

Create a new Runtime Environment Module
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A Runtime Environment :ref:`module project <mmm_module_skeleton>` is built with ``build-runtime-api`` skeleton.

.. code:: xml

   <info organisation="myorg" module="mymodule" status="integration" revision="1.0.0">
      <ea:build organisation="com.is2t.easyant.buildtypes" module="build-runtime-api" revision="2.+">
      <ea:property name="runtime.api.name" value="RUNTIME"/>
      <ea:property name="runtime.api.version" value="1.0"/>
      </ea:build>
   </info>

The build option ``runtime.api.name`` defines the name of the Runtime Environment (required). 
The build option ``runtime.api.version`` defines its version. If not set, it takes the declared module version.

For example, the following dependencies declare a Runtime Environment that aggregates all classes, methods and fields
defined by ``EDC,KF,BON,Wadapps,Components`` Kernel APIs modules.

.. code:: xml

   <dependencies>
      <dependency org="com.microej.kernelapi" name="edc" rev="1.0.4"/>
      <dependency org="com.microej.kernelapi" name="kf" rev="2.0.1"/>
      <dependency org="com.microej.kernelapi" name="bon" rev="1.0.4"/>
      <dependency org="com.microej.kernelapi" name="wadapps" rev="1.2.2"/>
      <dependency org="com.microej.kernelapi" name="components" rev="1.2.2"/>
   </dependencies>


Extend a Runtime Environment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Foundation and Add-On libraries can be extended by adding new methods to their existing classes thanks to the `Class Extender
tool <https://repository.microej.com/modules/com/microej/tool/class-extender/1.0.1/>`_. This tool works at binary level
and is able to inject methods from one class to another. Extensions can thus be independently compiled and be retrieved
by the Kernel and applied during a Multi-Sandbox Firmware build.

To make the extensions available to Application developers, Kernel APIs must be updated too. The ``runtime-api``
build-type takes base Java APIs, extended APIs and the new Kernel API and builds a custom Runtime API.

The following diagram illustrates the process of extending the default `String <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/String.html>`_ class from :ref:`[EDC] <runtime_edc>` from a Kernel developer point of view:

.. image:: png/graph_build_string_methods.png
   :align: center
   :width: 1280px
   :height: 783px

Two processes are taking place to apply extensions:

   1. A Custom Runtime API is built using the `runtime-api` build type. It takes three components as input:

      - EDC Foundation Library API which contains the String class we want to extend
      - a :ref:`kernel.api` file definition which includes new methods
      - a new ``String.java`` API source file which includes new methods (with their Javadoc specification)

      It builds a custom runtime API composed of three components:

      - an Add-On library containing the new ``kernel.api``
      - the Runtime API containing the extended String API
      - the corresponding Javadoc including the extended methods

   2. An extended EDC implementation is built during Firmware build calling the Class Extender tool. It takes two components:

      - the original EDC Foundation library implementation jar file
      - the String extension Add-On library jar file

      It overrides the original EDC Foundation library implementation jar file.

From an Application developper perspective, the Application only depends on the Runtime Environment that includes both original extended APIs.

.. image:: png/graph_build_string_methods_app_dev.png
   :align: center
   :width: 524px
   :height: 396px

Refer to the `Class Extender tool README <https://repository.microej.com/modules/com/microej/tool/class-extender/1.0.0/README-1.0.0.md>`_ for more information about class extension and integration to Firmware.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.