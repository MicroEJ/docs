.. _tinysandbox:

============
Tiny-Sandbox
============


Principle
=========

The Tiny-Sandbox capability of the MicroEJ Core Engine allows to
build a main application optimized for size. This capability is suitable
for environments requiring a small memory footprint.


Installation
============

Tiny-Sandbox is an option disabled by default. To enable Tiny-Sandbox of the MicroEJ Core Engine, set the property
``mjvm.standalone.configuration`` in ``configuration.xml`` file as
follows:

``<property name="mjvm.standalone.configuration" value="tiny"/>``

See section :ref:`platformCustomization` for more info on the
``configuration.xml`` file.


Limitations
===========

In addition to general :ref:`limitations`:

-  The maximum application code size (classes and methods) cannot exceed
   ``256KB``. This does not include application resources, immutable
   objects and internal strings which are not limited.

-  The option :guilabel:`SOAR` > :guilabel:`Debug` > :guilabel:`Embed all type names` has no effect.
   Only the fully qualified names of types marked as required types are
   embedded.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
