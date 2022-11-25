Introduction
============

MicroUI Foundation Library provides access to a pixel-based display and inputs.

The aim of this library is to enable the creation of user interface in Java by reifying hardware capabilities.

To use the MicroUI Foundation Library, add `MicroUI API module`_ to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: java

         implementation("ej.api:microui:3.1.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.api" name="microui" rev="3.1.0"/>
	

Drawing Foundation Library extends MicroUI drawing APIs [#note_microui_2]_ with more complex ones such as:

- thick line, arc, circle and ellipse
- polygon
- image deformation and rotation

To use the Drawing Foundation Library, add `Drawing API module`_ to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: java

         implementation("ej.api:drawing:1.0.3")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.api" name="drawing" rev="1.0.3"/>


.. [#note_microui_2] These APIs were formerly included in MicroUI ``2.x``

.. _MicroUI API module: https://repository.microej.com/modules/ej/api/microui/
.. _Drawing API module: https://repository.microej.com/modules/ej/api/drawing/

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
