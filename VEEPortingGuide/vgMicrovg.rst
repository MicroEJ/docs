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

The `MicroVG library`_ is an additional module. 
In the platform configuration's :ref:`module description file <mmm_module_description>`, add the VG Pack dependency:

.. code-block:: XML

   <dependency org="com.microej.pack.vg" name="vg-pack" rev="1.1.1" conf="default->default"/>

The VG Pack will be automatically available after a platform rebuild.

.. _MicroVG library: https://repository.microej.com/modules/com/microej/pack/vg/vg-pack/

Use
===

See :ref:`MicroVG <section_app_microvg>` chapter in Application Developer Guide.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
