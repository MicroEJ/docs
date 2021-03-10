.. _section_mui_migrationguide:

===============
Migration Guide
===============

The MicroUI implementation is provided by the MicroEJ UI Pack.
According the MicroEJ UI Pack used to build the MicroEJ Platform, the application has to be updated.

* Refer to the :ref:`table <section_ui_api>` that illustrates the implemented MicroUI API for each MicroEJ UI Pack.
* Refer to the latest `MicroUI API changelog <https://repository.microej.com/artifacts/ej/api/microui>`_.
* Refer to the latest `Drawing API changelog <https://repository.microej.com/artifacts/ej/api/drawing>`_.

The following chapters describe the changes to perform in the application according the UI pack used to build the MicroEJ platform.

From 12.x to 13.x
=================

* Update ``ej.api#microui`` dependency to ``3.0.0``.
* Add ``ej.api#drawing-1.0.0`` dependency.

From 10.x to 12.x
=================

* In MicroEJ application launcher > ``Configuration`` tab > ``MicroUI``: check ``Use Flying Images`` when the application is using the flying images.
* In MicroEJ application launcher, increase java heap: it now contains MicroUI images metadata (size, format, clip etc.). The iceatea heap has been automatically decreased.

From 9.x to 10.x
================

* In MicroEJ application launcher > ``Configuration`` tab > ``MicroUI``: set the image heap size (application mode).

From 8.x to 9.x
===============

* MWT has been removed from pack: update the application classpath in consequence

..
   | Copyright 2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
