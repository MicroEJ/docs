.. _kernel.api:

Writing Kernel APIs
===================

This section lists different ways to help to write ``kernel.api`` files
(see XXX).

Default Kernel APIs Derivation
------------------------------

MicroEJ provides some predefined kernel API files.

The packaged file ``kernel.api`` can be extracted from the JAR file and
to be manually managed in order to keep only desired types, methods and
fields.

Build a kernel API artifact
---------------------------

-  Generates the skeleton project: Select
   :guilabel:`File` > :guilabel:`New` > :guilabel:`Other...` > :guilabel:`Easyant` > :guilabel:`Easyant Project`, select and
   configure the ``com.is2t.easyant.skeletons#microej-kernelapi;+``
   skeleton, and press :guilabel:`Finish` button.

-  Create the ``kernel.api`` file into the ``src`` folder.

-  Right-click on the project and select :guilabel:`Build with EasyAnt`.

MicroEJ provides a tool which generates a ``kernel.api`` file based on a
java classpath.

Kernel API Generator
--------------------

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
