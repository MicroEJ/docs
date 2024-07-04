.. _section_vg_simulation:

==========
Simulation
==========

Principle
=========

The VG Pack embeds an extension of :ref:`UI Pack's Front Panel mock <section_ui_simulation>` to implement the equivalent of the five embedded modules (Matrix, Path, Gradient, Image and Font).

The implementation simulates the same characteristics and limitations as the embedded modules. 

.. _section_vg_frontpanel_extension:

Extension
=========

The Front Panel is configured to decode the images encoded for a specific GPU (see :ref:`section_vg_image_generator`).
When a custom :ref:`section_vg_image_generator_extension` is used, the Front Panel must be extended to decode the images.
This extension can be also used to simulate the limlitations of the MicroVG implementation over a GPU (unsupported blend modes, MicroUI drawings in a BufferedVectorImage, etc.). XXX_TODO

In the VEE Port's Front Panel project:

1. Add the dependency:

   .. code-block:: xml

      <dependency org="com.microej.pack.vg" name="vg-pack" rev="x.y.z">
         <artifact name="vg-frontpanel" type="jar"/>
      </dependency>

   Where ``x.y.z`` is the VG Pack version used to build the VEE Port (minimum ``1.6.0``).

2. Implements the interface ``ej.microvg.image.ImageDecoder``; the name of the class must be ``[Prefix]ImageDecoder`` where ``[Prefix]`` is the name that will be set in the VEE Port configuration file (see :ref:`section_microvg_installation`).
3. XXX_TODO BVI limitations, VG limitations ?
4. Rebuild the VEE Port.

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
