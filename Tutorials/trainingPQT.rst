.. _training_pqt:

============================
Qualify & Test your VEE Port
============================

Description
===========

This training describes how to validate the integration
of MICROEJ VEE on a device using PQT (Port Qualification Tools).

VEE Port Qualification is the process of validating the conformance of the Abstraction
Layer that implements the :ref:`Low Level APIs <low_level_api>` of a Foundation Library.

What you will learn:

- Reminder of Foundation Libraries architecture.
- Test Suite role in Abstraction Layer validation.
- Run a Test Suite on a Device

Intended Audience
=================

The audience for this document is for VEE Port developers 
who want to validate an Abstraction Layer implementation
or understand how to automatically run a Test Suite on their device.

Prerequisites
=============

- Good knowledge of the :ref:`overview` section.
- Good knowledge of the :ref:`chapter-glossary`.
- `ESP-WROVER-KIT V4.1 Evaluation Kit <https://docs.espressif.com/projects/esp-idf/en/stable/esp32/hw-reference/esp32/get-started-wrover-kit.html#get-started-esp-wrover-kit-v4-1-board-front>`_.

Training Resources
==================

Unit 1: Port Qualification Tool Overview
----------------------------------------

- :download:`Slides: PQT Overview <https://repository.microej.com/packages/training/DEV-M0018PQT_0002-PRE-Platform_Qualification_Tools_Overview-1.0.pdf>`

Unit 2: Run a Test Suite on a Device
------------------------------------

Step-by-step hands-on to run a VEE Port Test Suite on a device using the Port Qualification Tools:

- :ref:`run_fs_test_suite_on_esp32_wrover` (for MICROEJ SDK 5)

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.