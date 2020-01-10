.. _LLSP-API-SECTION:

LLSP: Shielded Plug
===================

Naming Convention
-----------------

The Low Level Shielded Plug API, the ``LLSP`` API, relies on functions
that need to be implemented. The naming convention for such functions is
that their names match the ``LLSP_IMPL_*`` pattern.  

Header Files
------------

The implementation of the SP for the PLATFORM assumes some support from
the underlying RTOS. It is mainly related to provide some
synchronization when reading / writing into Shielded Plug blocks.

-  ``LLSP_IMPL_syncWriteBlockEnter`` and
   ``LLSP_IMPL_syncWriteBlockExit`` are used as a semaphore by RTOS
   tasks. When a task wants to write to a block, it "locks" this block
   until it has finished to write in it.

-  ``LLSP_IMPL_syncReadBlockEnter`` and ``LLSP_IMPL_syncReadBlockExit``
   are used as a semaphore by RTOS tasks. When a task wants to read a
   block, it "locks" this block until it is ready to release it.

The [SP] specification provides a mechanism to force a task to wait
until new data has been provided to a block. The implementation relies
on functions ``LLSP_IMPL_wait`` and ``LLSP_IMPL_wakeup`` to block the
current task and to reschedule it.
