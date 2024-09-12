.. _section_vg_simulation:

==========
Simulation
==========

Principle
=========

The VG Pack embeds an implementation of the :ref:`UI Pack's Front Panel mock <section_ui_simulation>` that implements the equivalent of the five embedded modules (Matrix, Path, Gradient, Image and Font). 
This implementation has to be extended to simulate the same characteristics and limitations as the embedded modules. 
The aim of this extension is to:

* decode the images encoded for a specific GPU (see :ref:`section_vg_image_generator`)
* simulate the limitations of the MicroVG implementation over a GPU (unsupported blend modes, MicroUI drawings in a ``BufferedVectorImage``, etc.).

Default Extensions
==================

Two extensions are available that simulate the Vivante VGLite (compatible with the :ref:`section_vg_c_module_microvg_vglite`) and Think Silicon NemaVG (compatible with the :ref:`section_vg_c_module_microvg_nema`) GPUs.
To select one of them, set the right name (respectively ``vglite`` and ``nema``) in the VEE Port configuration file (see :ref:`section_microvg_installation`).

.. _section_vg_frontpanel_extension:

Custom Extension
================

Overview
--------

A custom extension can be selected to simulate another GPU. 
This extension consists of the implementation of several interfaces and classes.
In the VEE Port's Front Panel project:

1. Add the dependency:

   .. code-block:: xml

      <dependency org="com.microej.pack.vg" name="vg-pack" rev="x.y.z">
         <artifact name="vg-frontpanel" type="jar"/>
      </dependency>

   Where ``x.y.z`` is the VG Pack version used to build the VEE Port (minimum ``1.6.0``).
2. Implement one or several interfaces / classes to simulate the embedded GPU (see next chapters).
3. Rebuild the VEE Port.

Image Decoder
-------------

To decode the images generarated by the :ref:`image generator<section_vg_image_generator_extension>`, implement the interface ``ej.microvg.image.ImageDecoder`` in the VEE Port's Front Panel project. 
The name of the class must be ``ej.microvg.image.[Prefix]ImageDecoder`` where ``[Prefix]`` is the name that will be set in the VEE Port configuration file (see :ref:`section_microvg_installation`).

.. note:: This implementation is mandatory to allow the use of encoded images.

Display Drawer
--------------

This feature allows to simulate the same limitations of the GPU to draw the MicroVG drawings (path, gradient, blend modes, etc.) in the display buffer (and in the ``BufferedImage`` with same format than the display buffer).

.. note:: This implementation is optional; by default, all the MicroVG drawings are implemented.

1. Extend the class ``ej.microvg.display.DisplayDrawer``; the name of the class must be ``ej.microvg.display.[Prefix]DisplayDrawer`` where ``[Prefix]`` is the name that will be set in the VEE Port configuration file (see :ref:`section_microvg_installation`).
2. Override the method ``drawPath()`` to simulate some limitations.

Buffered Vector Image
---------------------

On the embedded side, the MicroUI drawings (line, rectangle, etc.) must be explicitly implemented to be stored in a ``BufferedVectorImage`` (a drawing should not be stored if the GPU is not able to render it).
The Front Panel extension allows to simulate the same limitations.

.. note:: This implementation is optional; by default, all the MicroUI drawings in a BufferedVectorImage are disabled (whereas all the MicroVG drawings are enabled).

The Front Panel extension already provides an engine that implements all MicroUI drawings in a ``BufferedVectorImage``.
Each drawing of this extension can be used independently to simulate the behavior of the embedded side.

1. Implement the interface ``ej.microvg.bvi.BufferedVectorImageDrawer``; the name of the class must be ``ej.microvg.bvi.[Prefix]BufferedVectorImageDrawer`` where ``[Prefix]`` is the name that will be set in the VEE Port configuration file (see :ref:`section_microvg_installation`).
2. Implement one or several MicroUI drawing methods.
3. Call the corresponded engine's drawing method, for instance: ``LLVGEngine.Instance.getBufferedVectorImageDrawer().fillRectangle(xxx)``.

Installation
============

Refer to the chapter :ref:`section_microvg_installation` for more information about the front panel configuration.

Use
===

Launch a MicroVG application on the Simulator to run the Front Panel extension.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
