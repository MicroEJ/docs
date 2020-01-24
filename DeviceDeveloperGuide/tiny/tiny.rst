.. _core-tiny:

================
Tiny application
================


Principle
=========

The Tiny application capability of the MicroEJ core engine allows to
build a main application optimized for size. This capability is suitable
for environments requiring a small memory footprint.


Installation
============

Tiny application is an option disabled by default. To enable Tiny
application of the MicroEJ core engine, set the property
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
