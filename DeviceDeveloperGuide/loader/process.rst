Functional Description
======================

The External Resources Loader is an optional module. When not installed,
only internal resources are available for the MicroEJ application. When
the External Resources Loader is installed, the MJVM tries first to
retrieve the expected resource from its available list of internal
resources, before asking the BSP to load it (using ``LLEXT_RES_impl.h``
functions).
