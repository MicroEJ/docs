.. include:: uiReplaces.rst

.. _section_microvg:

=======
MicroVG
=======


Principle
=========

`MicroVG library`_ is an extension of the MicroUI library and provides vector drawing capabilities.

.. _section_vg_architecture:

Architecture
============

`MicroVG library`_ is the entry point to perform some vectorial drawings on display. 
This library contains only a minimal set of basic APIs. As a result, high-level libraries can be used to have more expressive power. 
In addition to this restricted set of APIs, the MicroVG implementation has been designed to minimize the EDC, BON, and MicroUI footprint. 

Native Calls
============

Like MicroUI, the MicroVG implementation for MicroEJ uses native methods to perform some actions (manipulate matrices, perform drawings, decode and render fonts, etc.). 
The library implementation has been designed not to block native methods (wait until the end of the drawing, etc.), which can lock the complete MicroEJ Core Engine execution. 

Refer to the :ref:`MicroUI implementation <section_microui_native_calls>` to have more details about the native calls.

.. _section_microvg_installation:

Installation
============

The `MicroVG`_ :ref:`Pack <pack_overview>` module must be installed in your VEE Port:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         microejPack("com.microej.pack.vg:vg-pack:[VG Pack version]")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.pack.vg" name="vg-pack" rev="[VG Pack version]" conf="default->default"/>

.. note:: The latest version of the VG Pack is |VGPACKVERSION|.

The VG Pack will be automatically available after a VEE Port rebuild.

.. _MicroVG:
.. _MicroVG library: https://repository.microej.com/modules/com/microej/pack/vg/vg-pack/

When installed, the MicroVG Pack module must be configured.

.. tabs::

   .. tab:: SDK 6

     In SDK 6, the configuration is done in the properties file ``configuration.properties`` of the VEE Port project.
	  All the properties names listed below must be prefixed by ``com.microej.pack.microvg.``.
	  For example the ``implementation`` properties is defined by the ``com.microej.pack.microvg.implementation`` property.

   .. tab:: SDK 5

	  In SDK 5, the configuration is done in the properties file ``microvg/microvg.properties``.

This configuration allows to configure the :ref:`section_vg_image_generator` and the front panel to fit a specific GPU.
This properties file must contain a property named ``implementation``.
Two values are currently available: 

* ``nema``: to be compatible with the :ref:`Think Silicon Nema VG<section_vg_c_module_microvg_nema>` GPU.
* ``vglite``: to be compatible with the :ref:`Vivante VGLite<section_vg_c_module_microvg_vglite>` GPU.

Example:

.. tabs::

   .. tab:: SDK 6

      .. code-block:: XML

         com.microej.pack.microvg.implementation=nema

   .. tab:: SDK 5

      .. code-block:: XML

         implementation=nema

A custom extension can be used to target another GPU. 
The name of the property ``implementation`` is used to identify the :ref:`section_vg_image_generator_extension` and the :ref:`Front Panel Extension<section_vg_frontpanel_extension>`.

Use
===

See :ref:`MicroVG <section_app_microvg>` chapter in Application Developer Guide.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
