.. _module_natures:

Module Natures
==============

.. _module_nature_skeleton_mapping:

The following table describes the :ref:`project skeleton <mmm_module_skeleton>` name for most common MicroEJ Module Natures.

.. list-table:: MicroEJ Module Natures Summary
   :widths: 20 10 50
   :header-rows: 1

   * - Module Nature
     - Skeleton Name
     - Direct Wizard
   * - :ref:`Add-On Library <module_natures.addon_lib>`
     - `microej-javalib`
     - :guilabel:`File` > :guilabel:`New` > :guilabel:`MicroEJ Add-On Library Project`
   * - :ref:`Mock <module_natures.mock>`
     - `microej-mock`
     - 
   * - :ref:`Module Repository <module_natures.module_repository>`
     - `artifact-repository`
     - 
   * - :ref:`Sandboxed Application <module_natures.sandboxed_application>`
     - `application`
     - :guilabel:`File` > :guilabel:`New` > :guilabel:`MicroEJ Sandboxed Application Project`
   * - :ref:`Standalone Application <module_natures.standalone_application>`
     - `firmware-singleapp`
     - :guilabel:`File` > :guilabel:`New` > :guilabel:`MicroEJ Standalone Application Project`

.. _module_natures.addon_lib:

Add-On Library
~~~~~~~~~~~~~~

A MicroEJ Add-On Library is a MicroEJ library that is implemented on top of MicroEJ Foundation Libraries (100% full Java code).

Go to the :ref:`MicroEJ Libraries <libraries>` section for more details.

.. _module_natures.mock:

Mock
~~~~

A Mock is a jar file containing some Java classes that simulate natives for the Simulator.
Mocks allow applications to be run unchanged in the Simulator while still (apparently) interacting with native code.

Go to the :ref:`Mock <mock_module>` section for more details.

.. _module_natures.module_repository:

Module Repository
~~~~~~~~~~~~~~~~~

A module repository is a module that bundles a set of modules in a portable ZIP file.
It is used to contain all the dependencies required to build and package the applications.

Go to the :ref:`module_repository` section for more details.

.. _module_natures.sandboxed_application:

Sandboxed Application
~~~~~~~~~~~~~~~~~~~~~

A MicroEJ Sandboxed Application is a MicroEJ Application that can run over a Multi-Sandbox Firmware.
It can be linked either statically or dynamically.
If it is statically linked, it is then called a System Application as it is part of the initial image and cannot be removed.

Go to the :ref:`sandboxed_application` section for more details.

.. _module_natures.standalone_application:

Standalone Application
~~~~~~~~~~~~~~~~~~~~~~

A MicroEJ Standalone Application is a MicroEJ Application that is directly linked to the C code to produce a MicroEJ Firmware.
Such application must define a main entry point, i.e. a class containing a public static void main(String[]) method.

Go to the :ref:`standalone_application` section for more details.

.. _module_natures_platform_selection:

MicroEJ Platform Selection
~~~~~~~~~~~~~~~~~~~~~~~~~~

Many modules natures require a MicroEJ Platform for building the module or for running tests.

There are 4 different ways to provide a MicroEJ Platform for a module project:

-  Set the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.file`` to a MicroEJ Platform file (``.zip``, ``.jpf`` or ``.vde``):
-  Set the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.dir`` to an already imported :ref:`Source Platform <source_platform_import>`.
-  Declare a :ref:`module dependency <mmm_module_dependency>`:

   .. code:: xml

      <dependency org="myorg" name="myname" rev="1.0.0" conf="platform->default" transitive="false"/>

-  Copy a MicroEJ Platform file to the dropins folder. The default dropins folder location is ``[module_project_dir]/dropins``. It can be changed using the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.dropins``.


..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
