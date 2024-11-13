.. _sdk6_memorymapanalyzer:

===================
Memory Map Analyzer
===================

Principle
=========

When the Executable of an Application is built, a Memory Map file is generated. 
This file can be visualized with the Memory Map Analyzer, an Eclipse IDE plug-in. 
It displays the memory consumption of different features in the RAM and ROM.

.. figure:: images/mma_process.png
   :alt: Memory Map Analyzer Process
   :align: center
   :scale: 80%

   Memory Map Analyzer Process

Use
===

When the Executable file of an Application has been produced, 
the Memory Map file is available at ``build/executable/application/SOAR.map``.

.. figure:: images/memory-map-file.png
   :alt: Retrieve Map File
   :align: center

   Memory Map File

You can visualize it by following these steps:

- Make sure :ref:`the Eclipse IDE is installed with the required plugin <sdk6_microejtools>`, then launch it.
- Click on :guilabel:`File` > :guilabel:`Open File...`.
- Select the Memory Map file.

.. figure:: images/RI1.png
   :alt: Consult Full Memory
   :align: center
   :width: 1171px
   :height: 457px

   Consult Full Memory

You can select an item (or several) to show the memory used by this item(s) on the right, 
or select ``All`` to show the memory used by all items. 
This special item performs the same action as selecting all items in the list.

You can also select an item in the list, and expand it to see all symbols used by the item. 
This view is useful in understanding why a symbol is embedded.

.. figure:: images/RIDetailedView.png
   :alt: Detailed view
   :align: center
   :width: 1216px
   :height: 753px

   Detailed View

Troubleshooting
===============

Memory Map Analyzer may fail while opening a Memory Map file saying `Could not read this file`.


.. figure:: images/memory_map_analyzer_couldnt_read.png
   :alt: "Could not read this file" Error
   :align: center
   :scale: 80%

   Error displayed when Memory Map file could not be read

This may happen if the Memory Map Analyzer cannot find a VEE Port to interpret the Memory Map file.
To workaround this, you can open your Memory Map file with a text editor and add the following line::

   <property name="jpf.dir" value="/path/to/your/vee"/>

If a line defining the ``jpf.dir`` already exists, check if the value corresponds to a valid path.

.. note::

   The path must be the directory of a built VEE Port. If you build a Kernel Application, the
   VEE Port will be available in the ``build/vee`` directory of your Gradle project.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
