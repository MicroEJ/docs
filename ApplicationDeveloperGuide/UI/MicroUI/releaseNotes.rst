.. _section_mui_migrationguide:

===============
Migration Guide
===============

The MicroUI implementation is provided by the UI Pack.
According to the UI Pack used to build the VEE Port, the application has to be updated.

* Refer to the :ref:`table <section_ui_api>` that illustrates the implemented MicroUI API for each UI Pack.
* Refer to the latest `MicroUI API Changelog`_.
* Refer to the latest `Drawing API Changelog`_.

The following chapters describe the changes to perform in the application according the UI Pack used to build the VEE Port.

.. _MicroUI API Changelog: https://repository.microej.com/modules/ej/api/microui
.. _Drawing API Changelog: https://repository.microej.com/modules/ej/api/drawing

From 13.x to 14.x
=================

Consider the new semantic of the content of the back buffer after a flush: the past is not systematically restored, see :ref:`section_brs`.
The application code may be affected by this update.
Ensure that a clip is set before each initial drawing and that it has the same size as what is drawn (at least that every pixels in the clip is drawn).

From 12.x to 13.x
=================

* Update `ej.api#microui`_ dependency to the latest available version ``3.4.0``.
* Add `ej.api#drawing`_ dependency.

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: java

         implementation("ej.api:microui:3.4.0")
         implementation("ej.api:drawing:1.0.4")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependencies>
            <dependency org="ej.api" name="microui" rev="3.4.0"/>
            <dependency org="ej.api" name="drawing" rev="1.0.4"/>         
         </dependencies>


.. _ej.api#microui: https://repository.microej.com/modules/ej/api/microui
.. _ej.api#drawing: https://repository.microej.com/modules/ej/api/drawing

From 10.x to 12.x
=================

* In MicroEJ application launcher > ``Configuration`` tab > :ref:`MicroUI <section_ui_options_microui>`: check ``Use Flying Images`` when the application is using the flying images (property ``com.microej.library.microui.flyingimage.enabled``).
* In MicroEJ application launcher, increase the :ref:`Managed Heap <option_managed_heap>`: it now contains MicroUI images metadata (size, format, clip etc.). The icetea heap has been automatically decreased.

From 9.x to 10.x
================

* In MicroEJ application launcher > ``Configuration`` tab > :ref:`MicroUI <section_ui_options_microui>`: set the image heap size (property :ref:`ej.microui.memory.imagesheap.size <section_ui_options_imagesheapsize>`).

..
   | Copyright 2021-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
