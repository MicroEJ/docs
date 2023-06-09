.. _multisandbox_firmware_creation:

Kernel Creation
===============

This chapter requires a minimum understanding of :ref:`mmm` and :ref:`module_natures`. 

Create a new Project
--------------------

First create a new :ref:`module project <mmm_module_skeleton>` using the ``build-firmware-multiapp`` skeleton.

A new project is generated into the workspace:

.. _fms-project:
.. image:: png/firmware-multiapp-skeleton-project.png
   :align: center
   :width: 334px
   :height: 353px

Configure a VEE Port
--------------------

Before building the Kernel, a target VEE Port must be configured. See
:ref:`platform_selection`.

Build the Executable and Virtual Device
---------------------------------------

In the Package Explorer, right-click on the project and select
:guilabel:`Build Module`. The build of the Executable and Virtual
Device may take several minutes. Once the build has succeeded, the folder
:guilabel:`myfirmware` > :guilabel:`target~` > :guilabel:`artifacts` contains the firmware output artifacts
(see :ref:`in_out_artifacts`) :

-  ``mymodule.out``: The Executable to be programmed on device.

-  ``mymodule.kpk``: The Kernel package to be imported in a MicroEJ Forge instance.

-  ``mymodule.vde``: The Virtual Device to be imported in the SDK.

-  ``mymodule-workingEnv.zip``: This file contains all files produced by
   the build phase (intermediate, debug and report files).

.. _fms-artifacts:
.. image:: png/firmware-multiapp-skeleton-artifacts.png
   :align: center
   :width: 335px
   :height: 866px

.. _define_apis:

Expose APIs
-----------

A Kernel must define the set of classes, methods and static fields all applications are allowed to use.

.. note::

   According to the :ref:`Kernel and Features specification <kf_specification>`, no API is open by default to Sandboxed Applications.

This can be done either by declaring :ref:`Kernel APIs <kernel.api>` or by definining a :ref:`Runtime Environment <runtime_environment>`.

The main difference is from the Application development point of view. 
In the first case, the Application project still declares standard module dependencies.
This is the good starting point for quickly building a Kernel with Applications based on the MicroEJ modules as-is.
In the second case, the Application project declares the runtime environment dependency. 
This is the preferred way in case you intend to build and maintain a dedicated Applications ecosystem.

A Kernel API or a Runtime Environment module is added as a dependency with the configuration ``kernelapi->default``.

.. code:: xml

   <dependency org="com.microej.kernelapi" name="edc" rev="1.0.6" conf="kernelapi->default"/>

.. _system_application_input_ways:

Add Pre-installed Applications
------------------------------

Your device may come with pre-installed applications.
To mimic this behavior on a Virtual Device, add a new dependency with the configuration ``systemapp-vd->application``.

.. code:: xml

   <dependency org="com.mycompany" name="myapp" rev="0.1.0" conf="systemapp-vd->application"/>


.. _Kernel.install(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#install-java.io.InputStream-

Build the Executable in the Workspace
-------------------------------------

It is possible to build the Executable using :ref:`concepts-microejlaunches` rather than the regular module build.
This speeds-up the build time thanks to MicroEJ Module Manager workspace resolution and Eclipse incremental compilation.

- Import the Kernel project and all Sandboxed Application projects in the same workspace,
- Prepare a MicroEJ Application launch for the Kernel as a regular :ref:`standalone_application`,
- Prepare a MicroEJ Application launch for each Sandboxed Application using `Build Dynamic Feature` settings.

The following figure shows the overall build flow:

.. _build_flow_workspace:
.. figure:: png/build_flow_zoom_workspace.png
   :alt: Kernel Build Flow using MicroEJ Launches
   :align: center
   :scale: 80%

   Kernel Build Flow using MicroEJ Launches

Kernel Application Configuration
--------------------------------

.. _kernel_module_configuration:

Module Configuration
~~~~~~~~~~~~~~~~~~~~

The ``build-firmware-multiapp`` build type defines additional
configurations, used to specify the different kind of firmware inputs
(see :ref:`in_out_artifacts`) as dependencies.

The following table lists the different configuration mapping usage
where a dependency line is declared:

::

   <dependency org="..." name="..." rev="..." conf="[Configuration Mapping]"/>

.. tabularcolumns:: |p{4.3cm}|p{3cm}|p{8cm}|
.. table:: Configurations Mapping for ``build-firmware-multiapp`` Build Type

   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | Configuration Mapping         | Dependency Kind               | Usage                                                                                                                                                                           |
   +===============================+===============================+=================================================================================================================================================================================+
   | ``vdruntime->default``        | Add-On Library (``JAR``)      | Embedded in the Virtual Device only, not in the Executable                                                                                                                      |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``default->default;``         | Add-On Library (``JAR``)      | Embedded in both the Executable and the Virtual Device                                                                                                                          |
   | ``vdruntime->default``        |                               |                                                                                                                                                                                 |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``platform->default``         | VEE Port                      | VEE Port dependency used to build the Executable and the Virtual Device. There are other ways to select the VEE Port (see :ref:`platform_selection`)                            |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``kernelapi->default``        | Runtime Environment (``JAR``) | See :ref:`runtime_environment`                                                                                                                                                  |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
   | ``systemapp-vd->application`` | Application (``WPK``)         | Included to the Virtual Device as pre-installed Application.                                                                                                                    |
   +-------------------------------+-------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

**Example of minimal firmware dependencies.**

The following example defines a Kernel that exposes all APIs of ``EDC`` library.

.. code:: xml

   <dependencies>
       <dependency org="ej.api" name="edc" rev="1.2.0" conf="provided" />
       <!-- Runtime API (set of Kernel API files) -->
       <dependency org="com.microej.kernelapi" name="edc" rev="1.0.0" conf="kernelapi->default"/>
   </dependencies>

Build Options
~~~~~~~~~~~~~~

The :ref:`Kernel Application module nature <module_natures.kernel_application>` section describes all options available for building a Kernel module.

Build only a Virtual Device with a pre-existing Kernel
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Copy/Paste the ``.kpk`` file into the folder ``dropins``

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
