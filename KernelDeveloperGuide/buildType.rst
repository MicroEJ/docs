Build Firmware
==============

Prerequisite of this chapter: minimum understanding of ivy and easyant.

Workspace Build
---------------

.. _build_flow_workspace:
.. figure:: png/build_flow_zoom_workspace.png
   :alt: Firmware Build Flow in MicroEJ SDK Workspace
   :align: center
   :width: 75.0%

   Firmware Build Flow in MicroEJ SDK Workspace

.. _firmware_build_type:

Headless Build
--------------

.. _build_flow_buildtype:
.. figure:: png/build_flow_zoom_buildtype.png
   :alt: Firmware Build Flow in MicroEJ SDK Workspace
   :align: center
   :width: 75.0%

.. _runtime_environment:

Runtime Environment
-------------------

All firmwares define a runtime environment which is the set of classes,
methods and fields all applications are allowed to use. In most of the
cases the runtime environment is an aggregation of several kernel APIs
built with the EasyAnt build type ``build-runtime-api``.

.. code:: xml

   <info organisation="myorg" module="mymodule" status="integration"
   revision="1.0.0">
      <ea:build organisation="com.is2t.easyant.buildtypes" module="build-runtime-api" revision="2.+">
      <ea:plugin org="com.is2t.easyant.plugins" module="clean-artifacts" revision="2.+" />
      <ea:property name="clean.artifacts.max.keep" value="2" />
      <ea:property name="runtime.api.name" value="RUNTIME"/>
      <ea:property name="runtime.api.version" value="1.0"/>
      </ea:build>
   </info>

The ``runtime.api.name`` property define the name of the runtime
environment (it is required by the build type) , and the
``runtime.api.version`` property define it version. If the property
``runtime.api.version`` is not provided the build type computes it using
the revision of the ivy module.

.. code:: xml

   <dependencies>
      <dependency org="com.microej.kernelapi" name="edc" rev="[1.0.4-RC0,1.0.5-RC0[" transitive="false"/>
      <dependency org="com.microej.kernelapi" name="kf" rev="[2.0.1-RC0,2.0.2-RC0[" transitive="false"/>
      <dependency org="com.microej.kernelapi" name="bon" rev="[1.0.4-RC0,1.0.5-RC0[" transitive="false"/>
      <dependency org="com.microej.kernelapi" name="wadapps" rev="[1.2.2-RC0,1.2.3-RC0[" transitive="false"/>
      <dependency org="com.microej.kernelapi" name="components" rev="[1.2.2-RC0,1.2.3-RC0[" transitive="false"/>
   </dependencies>

This runtime environment aggregate all classes, methods and fields
defined by ``edc,kf,bon,wadapps,components`` kernel APIs.

The documentation of a runtime environment is packaged into the Virtual
Device as HTML javadoc (:guilabel:`Help` > :guilabel:`MicroEJ Resource Center` > :guilabel:`Javadoc`).

.. _kernel.api:

Writing Kernel APIs
-------------------

This section lists different ways to help to write ``kernel.api`` files
(see XXX).

Default Kernel APIs Derivation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MicroEJ provides some predefined kernel API files.

The packaged file ``kernel.api`` can be extracted from the JAR file and
to be manually managed in order to keep only desired types, methods and
fields.

Build a kernel API artifact
~~~~~~~~~~~~~~~~~~~~~~~~~~~

-  Generates the skeleton project: Select
   :guilabel:`File` > :guilabel:`New` > :guilabel:`Other...` > :guilabel:`Easyant` > :guilabel:`Easyant Project`, select and
   configure the ``com.is2t.easyant.skeletons#microej-kernelapi;+``
   skeleton, and press :guilabel:`Finish` button.

-  Create the ``kernel.api`` file into the ``src`` folder.

-  Right-click on the project and select :guilabel:`Build with EasyAnt`.

MicroEJ provides a tool which generates a ``kernel.api`` file based on a
java classpath.

Kernel API Generator
~~~~~~~~~~~~~~~~~~~~

Create a new MicroEJ Tool launch,
:guilabel:`Run` > :guilabel:`Run Configurations` > :guilabel:`MicroEJ Tool`, choose your Platform,
select :guilabel:`Kernel API Generator` for the :guilabel:`Settings` options, and don't
forget to set the output folder.

.. _kapi-launch:
.. image:: png/kernelapi_launch.png
   :align: center
   :width: 1135px
   :height: 702px

Define the classpath to use in the
:guilabel:`Configuration` tab, and Press :guilabel:`Run`. 
A ``kernel.api`` file is
generated in the output folder and it contains all classes, methods and
fields found in the given classpath.


.. include:: kernelAPIgenerator_use.rst


Specify the runtime environment of the firmware
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

While building a firmware, two ways exist to specify the runtime
environment:

-  By using one or more ivy dependencies of ``kernel API`` artifacts. In
   this case we must set properties ``runtime.api.name`` and
   ``runtime.api.version``.

-  By using the ivy dependency ``runtimeapi`` artifact.

.. _resident_application_input_ways:

Resident Applications
---------------------

A MicroEJ Sandboxed Application can be dynamically installed from a MicroEJ Forge instance 
or can be directly linked into the Firmware binary at built-time. In this case, it is called
a Resident Application.

The user can specify the Resident Applications in two different ways:

-  Set the property ``build-systemapps.dropins.dir`` to a folder with
   contains all the resident applications.

-  Add ivy dependencyy on each resident application:

   .. code:: xml

      <dependency org="com.microej.app.wadapps" name="management" 
      rev="[2.2.2-RC0,3.0.0-RC0[" conf="systemapp->application"/>

All Resident Applications are also available for the Virtual Device, if
a resident application should only be available for the Firmware, use an
ivy dependency with the ivy configuration ``systemapp-fw`` instead of
``systemapp``, like:

.. code:: xml

   <dependency org="com.microej.app.wadapps" name="management" rev="[2.2.2-RC0,3.0.0-RC0[" conf="systemapp-fw->application"/>

Advanced
--------

Easyant module.ivy
~~~~~~~~~~~~~~~~~~

MicroEJ Firmwares are built with the easyant buildType
``build-firmware-multiapp``, below we explain the default ``module.ivy``
generated by the EasyAnt skeleton.

Ivy info
^^^^^^^^

.. code:: xml

   <info organisation="org" module="module" status="integration" 
   revision="1.0.0">
       <ea:build organisation="com.is2t.easyant.buildtypes" module="build-firmware-multiapp" revision="2.+"/>
       <ea:property name="application.main.class" value="org.Main" />
       <ea:property name="runtime.api.name" value="RUNTIME" />
       <ea:property name="runtime.api.version" value="0.1.0" />
   </info>
               

The property ``application.main.class`` is set to the fully qualified
name of the main java class. The firmware generated by the EasyAnt
skeleton defines its own runtime environment by using ivy dependencies
on several ``kernel API`` instead of relying on a runtime environment
artifact. As consequence, the ``runtime.api.name`` and
``runtime.api.version`` properties are specified in the firmware project
itself.

.. _ivy_confs:

Ivy Configurations
^^^^^^^^^^^^^^^^^^

The ``build-firmware-multiapp`` build type requires the following
configurations, used to specify the different kind of firmware inputs
(see :ref:`in_out_artifacts`) as Ivy dependencies.

.. code:: xml

   <configurations defaultconfmapping="default->default;provided->provided">
       <conf name="default" visibility="public"/>
       <conf name="provided" visibility="public"/>
       <conf name="platform" visibility="public"/>
       <conf name="vdruntime" visibility="public"/>
       <conf name="kernelapi" visibility="private"/>
       <conf name="systemapp" visibility="private"/>
       <conf name="systemapp-fw" visibility="private"/>
   </configurations>            

The following table lists the different configuration mapping usage
where a dependency line is declared:

::

   <dependency org="..." name="..." rev="..." conf="[Configuration Mapping]"/>

.. tabularcolumns:: |p{4.3cm}|p{3cm}|p{8cm}|
.. table:: Configurations Mapping for ``build-firmware-multiapp`` Build Type

   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | Configuration Mapping         | Dependency Kind               | Usage                                                                                                                                                                           |
   +===============================+===============================+=================================================================================================================================================================================+
   | ``provided->provided``        | Foundation Library (``JAR``)  | Expected to be provided by the platform. (e.g. ``ej.api.*`` artifact)                                                                                                           |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``default->default``          | Add-on Library (``JAR``)      | Embedded in the firmware only, not in the Virtual Device                                                                                                                        |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``vdruntime->default``        | Add-on Library (``JAR``)      | Embedded in the Virtual Device only, not in the firmware                                                                                                                        |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``default->default;``         | Add-on Library (``JAR``)      | Embedded in both the firmware and the Virtual Device                                                                                                                            |
   | ``vdruntime->default``        |                               |                                                                                                                                                                                 |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``platform->platformDev``     | Platform (``JPF``)            | Platform dependency used to build the firmware and the Virtual Device. There are other ways to select the platform (see :ref:`platform_selection`)                              |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``kernelapi->default``        | Runtime Environment (``JAR``) | See :ref:`runtime_environment`                                                                                                                                                  |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``systemapp->application``    | Application (``WPK``)         | Linked into both the firmware and the Virtual Device as resident application. There are other ways to select resident applications (see :ref:`resident_application_input_ways`) |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``systemapp-fw->application`` | Application (``WPK``)         | Linked into the firmware only as resident application.                                                                                                                          |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

**Example of minimal firmware dependencies.**

The following example firmware contains one system app (``management``),
and defines an API that contains all types, methods, and fields from
``edc,kf,wadapps,components``.

.. code:: xml

   <dependencies>
       <dependency org="ej.api" name="edc" rev="[1.2.0-RC0,2.0.0-RC0[" conf="provided" />
       <dependency org="ej.api" name="kf" rev="[1.4.0-RC0,2.0.0-RC0[" conf="provided" />
       <dependency org="ej.library.wadapps" name="framework" rev="[1.0.0-RC0,2.0.0-RC0[" />
       <dependency org="com.microej.library.wadapps.kernel" name="common-impl" rev="[3.0.0-RC0,4.0.0-RC0[" />
       <dependency org="com.microej.library.wadapps" name="admin-kf-default" rev="[1.2.0-RC0,2.0.0-RC0[" />
       <!-- Runtime API (set of Kernel API files) -->
       <dependency org="com.microej.kernelapi" name="edc" rev="[1.0.0-RC0,2.0.0-RC0[" conf="kernelapi->default"/>
       <dependency org="com.microej.kernelapi" name="kf" rev="[2.0.0-RC0,3.0.0-RC0[" conf="kernelapi->default"/>
       <dependency org="com.microej.kernelapi" name="wadapps" rev="[1.0.0-RC0,2.0.0-RC0[" conf="kernelapi->default"/>
       <dependency org="com.microej.kernelapi" name="components" rev="[1.0.0-RC0,2.0.0-RC0[" conf="kernelapi->default"/>
       <!-- System apps -->
       <dependency org="com.microej.app.wadapps" name="management" 
       rev="[2.2.2-RC0,3.0.0-RC0[" conf="systemapp->application"/>
   </dependencies>
                           

Change the set of properties used to build a firmware
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The easyant build type use the file ``build/common.properties`` to
configure the build process.

.. _platform_selection:

Change the platform used to build the firmware and the Virtual Device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To build a firmware and a Virtual Device a platform must be specified.
Four different ways are possible to do so:

-  Use an Ivy dependency.

   .. code:: xml

      <dependency org="myorg" name="myname" rev="1.0.0" conf="platform->platformDev" transitive="false"/>

-  Copy/Paste a platform file into the folder defined by the property
   ``platform-loader.target.platform.dropins`` (by default it value is
   ``dropins``).

-  Set the property ``platform-loader.target.platform.file``.

   .. code:: xml

      <ea:property name="platform-loader.target.platform.file" value="/path-to-a-platform-file/" />

-  Set the property ``platform-loader.target.platform.dir``.

   .. code:: xml

      <ea:property name="platform-loader.target.platform.dir" value="/path-to-a-platform-folder/" />

Build only a firmware
~~~~~~~~~~~~~~~~~~~~~

Set the property ``skip.build.virtual.device``

.. code:: xml

   <ea:property name="skip.build.virtual.device" value="SET" />

Build only a Virtual Device
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Set the property ``virtual.device.sim.only``

.. code:: xml

   <ea:property name="virtual.device.sim.only" value="SET" />

Build only a Virtual Device with a pre-existing firmware
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Copy/Paste the ``.kpk`` file into the folder ``dropins``

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
