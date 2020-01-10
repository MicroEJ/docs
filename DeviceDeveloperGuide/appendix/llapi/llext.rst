.. _LLEXT_RES-API-SECTION:

LLEXT_RES: External Resources Loader
====================================

Principle
---------

This LLAPI allows to use the External Resource Loader. When installed,
the External Resource Loader is notified when the MJVM is not able to
find a resource (an image, a file etc.) in the resources area linked
with the MJVM.

When a resource is not available, the MJVM invokes the External Resource
Loader in order to load an unknown resource. The External Resource
Loader uses the LLAPI EXT_RES to let the BSP loads or not the expected
resource. The implementation has to be able to load several files in
parallel.

Naming Convention
-----------------

The Low Level API, the ``LLEXT_RES`` API, relies on functions that need
to be implemented. The naming convention for such functions is that
their names match the ``LLEXT_RES_IMPL_*`` pattern.  

Header Files
------------

One header file is provided:

-  LLEXT_RES_impl.h

   Defines the set of functions that the BSP must implement to load some
   external resources.
