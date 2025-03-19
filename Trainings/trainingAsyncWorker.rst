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

This training is designed for VEE Port developers who want to explore blocking native method implementation in depth.

Prerequisites
=============

To get the most out of this training, participants should have:

- A good knowledge of C programming language.
- A good understanding of :ref:`training_c_managed_code_communication_unit1` training (especially the ``Blocking Functions and Asynchronous Code`` section).

Training Resources
==================

Unit 1: Async Worker Overview
-----------------------------

.. |async_worker_slides| raw:: html

   <a href="https://repository.microej.com/packages/training/DEV-M0127-PRE-MicroEJ_Async_Worker_1.0.pdf" target="_blank">Slides: Async Worker Overview</a>

- |async_worker_slides|

Unit 2: Implementation Guide
----------------------------

The `Async Worker C Component <https://repository.microej.com/modules/com/microej/clibrary/platform/bsp-microej-async-worker/>`_
is implemented in several VEE Port Examples.

Refer to the following guide to implement asynchronously SNI functions using Async Worker:

- `Async Worker Implementation Guide <https://github.com/MicroEJ/VEEPort-Espressif-ESP32-S3-DevKitC-1/blob/2.5.0/ESP32-S3-DevKitC1-Xtensa-FreeRTOS-bsp/projects/microej/util/inc/microej_async_worker.h>`_

..
   | Copyright 2024-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.