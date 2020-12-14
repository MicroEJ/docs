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

Go to the :ref:`MicroEJ Libraries page <libraries>` for more details.

.. _module_natures.mock:

Mock
~~~~

A Mock is a jar file containing some Java classes that simulate natives for the Simulator.
Mocks allow applications to be run unchanged in the Simulator while still (apparently) interacting with native code.

Go to the :ref:`Mock page <mock_module>` for more details.

.. _module_natures.module_repository:

Module Repository
~~~~~~~~~~~~~~~~~

A module repository is a module that bundles a set of modules in a portable ZIP file.
It is used to contain all the dependencies required to build and package the applications.

Go to the :ref:`Module Repository page <module_repository>` for more details.

.. _module_natures.sandboxed_application:

Sandboxed Application
~~~~~~~~~~~~~~~~~~~~~

A MicroEJ Sandboxed Application is a MicroEJ Application that can run over a Multi-Sandbox Firmware.
It can be linked either statically or dynamically.
If it is statically linked, it is then called a System Application as it is part of the initial image and cannot be removed.

Go to the :ref:`Sandboxed Application page <sandboxed_application>` for more details.

.. _module_natures.standalone_application:

Standalone Application
~~~~~~~~~~~~~~~~~~~~~~

A MicroEJ Standalone Application is a MicroEJ Application that is directly linked to the C code to produce a MicroEJ Firmware.
Such application must define a main entry point, i.e. a class containing a public static void main(String[]) method.

Go to the :ref:`Standalone Application page <standalone_application>` for more details.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
