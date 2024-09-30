.. _tinysandbox:

============
Tiny-Sandbox
============


Principle
=========

The Tiny-Sandbox capability of the Core Engine allows to
build a Standalone Application optimized for size. This capability is suitable
for environments requiring a small memory footprint.

.. _tinysandbox_installation:

Installation
============

Tiny-Sandbox is an option disabled by default. 
To enable the Tiny-Sandbox capability of the Core Engine, set the property ``com.microej.runtime.capability`` to ``tiny`` 
in the ``configuration.properties`` file (SDK 6) or in the ``mjvm/mjvm.properties`` file (SDK 5) of the VEE Port project.
See the example below:

.. code-block::

  com.microej.runtime.capability=tiny


.. note::

   Before :ref:`Architecture 8.1.0 <changelog-8.1.0>`, enabling the Tiny-Sandbox capability
   was done by setting the property ``mjvm.standalone.configuration`` in the ``configuration.xml`` file as follows:

   .. code-block::
   
      <property name="mjvm.standalone.configuration" value="tiny"/>

   See section :ref:`platformCustomization` for more info on the ``configuration.xml`` file.


Limitations
===========

In addition to general :ref:`limitations`:

-  The maximum application code size (classes and methods) cannot exceed
   ``256KB``. This does not include application resources, immutable
   objects and internal strings which are not limited.

-  The option :guilabel:`SOAR` > :guilabel:`Debug` > :guilabel:`Embed all type names` has no effect.
   Only the fully qualified names of types marked as required types are
   embedded.

-  Incompatible with dynamic linkers enabling Address Space Layout Randomization (ASLR).

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
