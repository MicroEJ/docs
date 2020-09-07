.. _kernel.api:

Writing Kernel APIs
===================

This section lists different ways to help to write ``kernel.api`` files.

Default Kernel APIs Derivation
------------------------------

MicroEJ provides predefined kernel API files for the most common libraries provided by a Kernel. 
These files are packaged as MicroEJ modules under the `com/microej/kernelapi <https://repository.microej.com/artifacts/com/microej/kernelapi/>`_ organisation.

The packaged file ``kernel.api`` can be extracted from the JAR file and edited
in order to keep only desired types, methods and fields.

Build a Kernel API Module
-------------------------

- First create a new :ref:`module project <mmm_module_skeleton>` using the ``microej-kernelapi`` skeleton. 
-  Create the ``kernel.api`` file into the ``src`` folder.
-  Right-click on the project and select :guilabel:`Build Module`.

Kernel API Generator
--------------------

MicroEJ Kernel API Generator is a tool that help to generate a ``kernel.api`` file based on a
Java classpath.


In MicroEJ SDK, create a new MicroEJ Tool launch,
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
