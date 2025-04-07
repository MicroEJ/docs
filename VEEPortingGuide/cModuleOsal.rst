.. _c_module_osal:

===========================
OS Abstraction Layer (OSAL)
===========================

Overview
========

Some packs need to call APIs from the RTOS (queue, semaphore,...). In order to have generic packs, an OS Abstraction Layer (OSAL) is necessary to use these kind of functions.

Integrate OSAL in your VEE Port
===============================

If your OS is not mentionned in this documentation, please ask MicroEJ support.

FreeRTOS
--------

To integrate OSAL in a VEE Port based on FreeRTOS, add the following sources:

- `osal_FreeRTOS.c <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/blob/NXPVEE-MIMXRT1170-EVK-3.0.0/bsp/vee/port/util/src/osal_FreeRTOS.c>`_
- `osal_portmacro.h for FreeRTOS <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/blob/NXPVEE-MIMXRT1170-EVK-3.0.0/bsp/vee/port/util/inc/osal_portmacro.h>`_
- `osal.h <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/blob/NXPVEE-MIMXRT1170-EVK-3.0.0/bsp/vee/port/util/inc/osal.h>`__

Linux
-----

To integrate OSAL in a VEE Port based on Linux, add the following sources:

- `osal_posix.c <https://github.com/MicroEJ/AbstractionLayer-Linux/blob/3.1.0/vee/port/util/src/osal_posix.c>`_
- `osal_portmacro.h for Linux <https://github.com/MicroEJ/AbstractionLayer-Linux/blob/3.1.0/vee/port/util/inc/osal_portmacro.h>`_
- `osal.h <https://github.com/MicroEJ/AbstractionLayer-Linux/blob/3.1.0/vee/port/util/inc/osal.h>`__
