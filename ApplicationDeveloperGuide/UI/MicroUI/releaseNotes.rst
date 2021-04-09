.. _section_mui_migrationguide:

===============
Migration Guide
===============

The MicroUI implementation is provided by the MicroEJ UI Pack.
According the MicroEJ UI Pack used to build the MicroEJ Platform, the application has to be updated.

* Refer to the :ref:`table <section_ui_api>` that illustrates the implemented MicroUI API for each MicroEJ UI Pack.
* Refer to the latest `MicroUI API Changelog <https://repository.microej.com/artifacts/ej/api/microui>`_.
* Refer to the latest `Drawing API Changelog <https://repository.microej.com/artifacts/ej/api/drawing>`_.

The following chapters describe the changes to perform in the application according the MicroEJ UI Pack used to build the MicroEJ Platform.

From 12.x to 13.x
=================

* Update `ej.api#microui <https://repository.microej.com/modules/ej/api/microui/>`_ dependency to the latest available version ``3.x``.
* Add `ej.api#drawing <https://repository.microej.com/modules/ej/api/drawing/>`_ dependency.

.. code-block:: xml

   <dependencies>
      <dependency org="ej.api" name="microui" rev="3.0.3"/>
      <dependency org="ej.api" name="drawing" rev="1.0.2"/>         
   </dependencies>

From 10.x to 12.x
=================

* In MicroEJ application launcher > ``Configuration`` tab > :ref:`MicroUI <section_ui_options_microui>`: check ``Use Flying Images`` when the application is using the flying images (property ``com.microej.library.microui.flyingimage.enabled``).
* In MicroEJ application launcher, increase the :ref:`Java heap <option_java_heap>`: it now contains MicroUI images metadata (size, format, clip etc.). The iceatea heap has been automatically decreased.

From 9.x to 10.x
================

* In MicroEJ application launcher > ``Configuration`` tab > :ref:`MicroUI <section_ui_options_microui>`: set the image heap size (property :ref:`ej.microui.memory.imagesheap.size <section_ui_options_imagesheapsize>`).

..
   | Copyright 2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
