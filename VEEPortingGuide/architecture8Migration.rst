.. _architecture8_migration:

Architecture 8.0.0 Migration
============================

This chapter describes the steps to migrate a VEE Port from Architecture ``8.0.0`` to Architecture ``8.1.0``.

As a reminder, refer to the :ref:`Architecture 8.1.0 Changelog <changelog-8.1.0>` section for the complete list of changes and updates.

.. _architecture8_migration_llkernel:

Migrate Your LLKERNEL Implementation
------------------------------------

This section only applies if your LLKERNEL was based on legacy :ref:`In-Place Installation mode <feature_inplace_installation>`. 
The following code is a ``LLKERNEL_impl.c`` template for migrating your current implementation using the new APIs.
The code logic based on a ``malloc/free`` implementation does not need to be changed.

.. code-block:: c

   #include <stdlib.h>
   #include <string.h>

   #include "LLKERNEL_impl.h"

   // Your implementation of malloc()
   #define KERNEL_MALLOC(size) malloc((size_t)size)

   // Your implementation of free()
   #define KERNEL_FREE(addr) free((void*)addr)

   // Your implementation of 'ASSERT(0)'
   #define KERNEL_ASSERT_FAIL() while(1)

   struct installed_feature{
      void* ROM_area;
      void* RAM_area;
   };

   int32_t LLKERNEL_IMPL_allocateFeature(int32_t size_ROM, int32_t size_RAM) {
      struct installed_feature* f = (struct installed_feature*)KERNEL_MALLOC(sizeof(struct installed_feature));
      f->ROM_area = KERNEL_MALLOC(size_ROM);
      f->RAM_area = KERNEL_MALLOC(size_RAM);
      return (int32_t)f;
   }

   void LLKERNEL_IMPL_freeFeature(int32_t handle) {
      struct installed_feature* f = (struct installed_feature*)handle;
      KERNEL_FREE(f->ROM_area);
      KERNEL_FREE(f->RAM_area);
      KERNEL_FREE(handle);
   }

   int32_t LLKERNEL_IMPL_getAllocatedFeaturesCount(void) {
      // No persistency support
      return 0;
   }

   int32_t LLKERNEL_IMPL_getFeatureHandle(int32_t allocation_index) {
      // No persistency support
      KERNEL_ASSERT_FAIL();
   }

   void* LLKERNEL_IMPL_getFeatureAddressRAM(int32_t handle) {
      struct installed_feature* f = (struct installed_feature*)handle;
      return f->RAM_area;
   }

   void* LLKERNEL_IMPL_getFeatureAddressROM(int32_t handle) {
      struct installed_feature* f = (struct installed_feature*)handle;
      return f->ROM_area;
   }

   int32_t LLKERNEL_IMPL_copyToROM(void* dest_address_ROM, void* src_address, int32_t size) {
      memcpy(dest_address_ROM, src_address, size);
      return LLKERNEL_OK;
   }

   int32_t LLKERNEL_IMPL_flushCopyToROM(void) {
      return LLKERNEL_OK;
   }

   int32_t LLKERNEL_IMPL_onFeatureInitializationError(int32_t handle, int32_t error_code) {
      // No persistency support
      KERNEL_ASSERT_FAIL();
      return 0;
   }


..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
