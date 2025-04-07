.. _c_module_async_worker:

============
Async Worker
============

Overview
========

This C module is based on :ref:`c_module_osal` and allows to create asynchronous jobs.

Integrate Async Worker in your VEE Port
=======================================

Prerequisites
-------------

OSAL must be integrated in your VEE Port. Please refer to :ref:`c_module_osal` documentation.

Add Async Worker sources in your VEE Port
-----------------------------------------

To integrate Async Worker in your VEE Port, add the following sources:

- `microej_async_worker.c <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/blob/NXPVEE-MIMXRT1170-EVK-3.0.0/bsp/vee/port/util/src/microej_async_worker.c>`_
- `microej_async_worker.h <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/blob/NXPVEE-MIMXRT1170-EVK-3.0.0/bsp/vee/port/util/inc/microej_async_worker.h>`_
