.. _outputfiles:

Build Output Files
==================

When building a MicroEJ Application, multiple files are generated next to the ELF file.
These files are generated in a folder which is named like the main type and which is located in the output folder specified in the run configuration.

The following image shows an example of output folder:

.. figure:: images/build-output-files.png
   :alt: Build Output Files
   :align: center

   Build Output Files

The SOAR Map File
~~~~~~~~~~~~~~~~~

The ``SOAR.map`` file lists every embedded symbol of the application (section, Java class or method, etc.) and its size in ROM or RAM.
This file can be opened using the :ref:`memorymapanalyzer`.

The embedded symbols are grouped into multiple categories. For example, the ``Object`` class and its methods are grouped in the ``LibFoundationEDC`` category.
For each symbol or each category, you can see its size in ROM (``Image Size``) and RAM (``Runtime Size``).

The SOAR groups all the Java strings in the same section, which appears in the ``ApplicationStrings`` category.
The same applies to the static fields (``Statics`` category), the types (``Types`` category), and the class names (``ClassNames`` category).

The SOAR Information File
~~~~~~~~~~~~~~~~~~~~~~~~~

The ``soar/<main class>.xml`` file can be opened using any XML editor.

This file contains the list of the following embedded elements:

- method (in ``selected_methods`` tag)
- :ref:`resource <section.classpath.elements.resources>` (in ``selected_resources`` tag)
- :ref:`system property <system_properties>` (in ``java_properties`` tag)
- string (in ``selected_internStrings`` tag)
- :ref:`type <section.classpath.elements.types>` (in ``selected_types`` tag)
- :ref:`immutable <section.classpath.elements.immutables>` (in ``selected_immutables`` tag)

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
