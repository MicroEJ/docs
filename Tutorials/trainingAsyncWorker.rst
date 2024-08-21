.. _training_async_worker:

===============================================
Delegate Blocking Operations using Async Worker
===============================================

Description
===========

In this training, you will get an introduction to
the Async Worker C Component that helps to delegate blocking operations 
from VEE RTOS context to another RTOS task context.

Intended Audience
=================

This training is for VEE Port Developers wishing to go into blocking native method implementation in depth. 

Prerequisites
=============

- Knowledge of C programming language.
- Knowledge of :ref:`sni` concepts.

Training Resources
==================

Unit 1: Async Worker Overview
-----------------------------

- :download:`Slides: Async Worker Overview <https://repository.microej.com/packages/training/DEV-M0127-PRE-MicroEJ_Async_Worker_1.0.pdf>`

Unit 2: Implementation Guide
----------------------------

The `Async Worker C Component <https://repository.microej.com/modules/com/microej/clibrary/platform/bsp-microej-async-worker/>`_
is implemented in several VEE Port Examples.

Refer to the following guide to implement asynchronously SNI functions using Async Worker:

- `Async Worker Implementation Guide <https://github.com/MicroEJ/VEEPort-Espressif-ESP32-S3-DevKitC-1/blob/2.5.0/ESP32-S3-DevKitC1-Xtensa-FreeRTOS-bsp/projects/microej/util/inc/microej_async_worker.h>`_

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.