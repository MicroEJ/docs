.. _core_engine_capabilities:

========================
Core Engine Capabilities
========================

The Core Engine defines 3 exclusive capabilities:

-  Mono-Sandbox: capability to produce a monolithic Executable
   (default one).

-  Multi-Sandbox: capability to produce a extensible Executable on
   which new applications can be dynamically installed. See section
   :ref:`multisandbox`.

-  Tiny-Sandbox: capability to produce a compacted Executable
   (optimized for size). See section :ref:`tinysandbox`.

All the Core Engine capabilities may not be available on all
architectures. Refer to section :ref:`appendix_matrixcapabilities`
for more details.

To select the Core Engine capability, define the property ``com.microej.runtime.capability``
in the ``configuration.properties`` file (SDK 6) or in the ``mjvm/mjvm.properties`` file (SDK 5) 
of the VEE Port project, with one of the following values:

- ``mono`` for Mono-Sandbox (default value)

- ``multi`` for Multi-Sandbox

- ``tiny`` for Tiny-Sandbox

If the property ``com.microej.runtime.capability`` is not defined,
the Mono-Sandbox Core Engine capability is used.

.. toctree::
   :maxdepth: 1

   multiSandbox
   tinySandbox
