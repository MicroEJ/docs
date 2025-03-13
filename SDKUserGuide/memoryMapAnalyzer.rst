.. warning::

  This documentation is for SDK 5. The latest major version is :ref:`SDK 6 <sdk_6_user_guide>`.
  SDK 5 is in maintenance mode since the release of :ref:`SDK 5.8.0 <changelog-5.8.0>`.
  Consequently, as stated in the :ref:`SDK End User License Agreement (EULA) <sdk_eula>`, the SDK will reach the end of its life by July 2028.
  Contact :ref:`our support team <get_support>` for assistance with migrating to the new SDK, or your sales representative if you require an extension of SDK maintenance as a service.

.. _memorymapanalyzer:

===================
Memory Map Analyzer
===================


Principle
=========

When a MicroEJ Application is linked with the MicroEJ Workbench, a
Memory MAP file is generated. The Memory Map Analyzer (MMA) is an
Eclipse plug-in made for exploring the map file. It displays the memory
consumption of different features in the RAM and ROM.


Functional Description
======================

.. figure:: images/mma_process.png
   :alt: Memory Map Analyzer Process
   :align: center
   :scale: 80%

   Memory Map Analyzer Process

In addition to the executable file, the MicroEJ Platform generates a map
file. Double click on this file to open the Memory Map Analyzer.


Dependencies
============

No dependency.


Installation
============

This tool is a built-in SDK tool.


Use
===

The map file is available in the MicroEJ Application project output
directory.

.. figure:: images/whereMapIs.png
   :alt: Retrieve Map File
   :align: center
   :width: 1176px
   :height: 462px

   Retrieve Map File

Select an item (or several) to show the memory used by this item(s) on
the right. Select "All" to show the memory used by all items. This
special item performs the same action as selecting all items in the
list.

.. figure:: images/RI1.png
   :alt: Consult Full Memory
   :align: center
   :width: 1171px
   :height: 457px

   Consult Full Memory

Select an item in the list, and expand it to see all symbols used by the
item. This view is useful in understanding why a symbol is embedded.

.. figure:: images/RIDetailedView.png
   :alt: Detailed view
   :align: center
   :width: 1216px
   :height: 753px

   Detailed View

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
